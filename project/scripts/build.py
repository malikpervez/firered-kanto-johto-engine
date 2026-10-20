#!/usr/bin/env python3
"""Manual B0 build; Python 3.9+, stdlib only. No remote writes.

Each invocation retains a new detached worktree, full logs, and a private
manifest. Existing run directories are never reused, cleaned, or deleted.
An explicit reviewed --patch instead uses a fresh local repair branch.
"""

import argparse
import datetime
import hashlib
import json
import os
from pathlib import Path
import platform
import re
import shlex
import shutil
import subprocess
import sys


SOURCE_URL = "https://github.com/PokemonHnS-Development/pokehns-expansion"
SOURCE_COMMIT = "167aa6d537b109bb229c231ddce4616974c4da71"
CONFIG_KEYS = (
    "GAME_VERSION TITLE GAME_CODE BUILD_NAME MAP_VERSION FILE_NAME ROM ELF MAP SYM "
    "OBJ_DIR TEST DEBUG RELEASE LTO COMPARE ANALYZE UNUSED_ERROR DEPRECATED_ERROR "
    "O_LEVEL DINFO NOOPT USE_LTO_ON_RELEASE TOOLCHAIN CC CXX ARMCC CC1 CPP "
    "CFLAGS CPPFLAGS ASFLAGS LDFLAGS LIBPATH SHELL"
).split()


class PreflightError(Exception):
    pass


def now():
    return datetime.datetime.now(datetime.timezone.utc).isoformat()


def digest(path):
    result = hashlib.sha256()
    with path.open("rb") as stream:
        for block in iter(lambda: stream.read(1024 * 1024), b""):
            result.update(block)
    return result.hexdigest()


def write_json(path, value):
    # Replace only this invocation's own manifest, never another run's files.
    temporary = path.with_suffix(".json.tmp")
    temporary.write_text(json.dumps(value, indent=2, sort_keys=True) + "\n", encoding="utf-8")
    temporary.replace(path)


def within(path, parent):
    path = path.resolve()
    try:
        path.relative_to(parent.resolve())
    except ValueError:
        raise PreflightError("Path escapes permitted directory: {}".format(path))
    return path


def make_safe_path(path):
    # The pinned upstream Makefile interpolates toolchain/PATH inside shells.
    # Reject shell metacharacters and whitespace rather than guessing escaping.
    if not re.fullmatch(r"[A-Za-z0-9_./:+-]+", str(path)):
        raise PreflightError("Pinned Makefile requires a simple path without whitespace/metacharacters: {}".format(path))
    return path


def absolute_path(value, label, executable=False):
    if not value or not Path(value).is_absolute():
        raise PreflightError("{} must be an explicit absolute path".format(label))
    path = make_safe_path(Path(value).resolve())
    if executable:
        if not path.is_file() or not os.access(str(path), os.X_OK):
            raise PreflightError("{} is not an executable file: {}".format(label, path))
    elif not path.is_dir():
        raise PreflightError("{} is not a directory: {}".format(label, path))
    return path


def capture(command, cwd, env, logfile, checks, label, required=True):
    started = now()
    try:
        result = subprocess.run(command, cwd=str(cwd), env=env,
                                stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
                                check=False)
        output = result.stdout.decode("utf-8", errors="replace")
        code = result.returncode
    except OSError as error:
        output, code = str(error), None
    with logfile.open("a", encoding="utf-8") as stream:
        stream.write("\n[{}] {}\n{}\n".format(started, label, shlex.join(command)))
        stream.write(output)
        stream.write("\n[{}] exit_code={}\n".format(now(), code))
    checks.append({"label": label, "command": command, "cwd": str(cwd),
                   "started_at": started, "ended_at": now(), "exit_code": code,
                   "output": output})
    if required and code != 0:
        raise PreflightError("{} failed (exit {}); see {}".format(label, code, logfile))
    return output.strip()


def git_state(git, source, env, logfile, checks, label):
    head = capture([str(git), "-C", str(source), "rev-parse", "HEAD"],
                   source, env, logfile, checks, label + " HEAD")
    status = capture([str(git), "-C", str(source), "status", "--porcelain=v1",
                      "--untracked-files=all"], source, env, logfile, checks,
                     label + " tracked/untracked state")
    return {"head": head, "porcelain": status, "clean": status == ""}


def fingerprint(worktree):
    files = ["Makefile", "config.mk", "ld_script_modern.ld", "libagbsyscall/Makefile"]
    files.extend(str(path.relative_to(worktree)) for path in worktree.glob("*_rules.mk"))
    files.append("make_tools.mk")
    files.extend(str(path.relative_to(worktree)) for path in (worktree / "include/config").rglob("*") if path.is_file())
    records = [{"path": name, "bytes": (worktree / name).stat().st_size,
                "sha256": digest(worktree / name)} for name in sorted(set(files))]
    encoded = json.dumps(records, sort_keys=True, separators=(",", ":")).encode("utf-8")
    return {"sha256": hashlib.sha256(encoded).hexdigest(), "files": records,
            "definition": "SHA256 of canonical JSON file path/size/SHA256 records"}


def prepare_environment(make, toolchain, host_deps):
    bins = [toolchain / "bin"]
    if host_deps:
        bins.append(host_deps / "bin")
    bins.extend([make.parent, Path(sys.executable).resolve().parent])
    bins.extend(Path(path) for path in ("/usr/bin", "/bin", "/usr/sbin", "/sbin"))
    # Ambient MAKEFLAGS, CC/CXX/CFLAGS, CI variables and credentials cannot change
    # the baseline. Preserve HOME's actual value; do not modify shell profiles.
    env = {key: os.environ[key] for key in ("HOME", "TMPDIR", "SYSTEMROOT") if key in os.environ}
    env.update({"PATH": os.pathsep.join(str(make_safe_path(path)) for path in dict.fromkeys(bins)),
                "LANG": "C", "LC_ALL": "C", "TZ": "UTC"})
    if host_deps:
        env["PKG_CONFIG_PATH"] = os.pathsep.join(str(host_deps / subdir) for subdir in ("lib/pkgconfig", "share/pkgconfig"))
        # A locally built pkgconf may classify its own prefix as a system path.
        # Upstream asks --libs-only-L, so retain the private library/include path.
        env["PKG_CONFIG_ALLOW_SYSTEM_LIBS"] = "1"
        env["PKG_CONFIG_ALLOW_SYSTEM_CFLAGS"] = "1"
    return env


def build(args):
    root = Path(__file__).resolve().parent.parent
    local = within(root / "_local", root)
    make_safe_path(root)
    run_name = "{}-{}".format(args.run_id, args.target)
    worktrees_root = within(local / "worktrees", local)
    artifacts_root = within(local / "artifacts", local)
    evidence_root = within(local / "evidence", local)
    tree = within(worktrees_root / run_name, worktrees_root)
    artifacts = within(artifacts_root / run_name, artifacts_root)
    evidence = within(evidence_root / "builds" / run_name, evidence_root)
    for path in (tree, artifacts, evidence):
        if path.exists() or path.is_symlink():
            raise PreflightError("Refusing existing run path: {}".format(path))
    # Atomically claim this run's evidence path; do not reuse prior evidence.
    evidence.mkdir(parents=True, exist_ok=False)
    artifacts.mkdir(parents=True, exist_ok=False)
    tree.parent.mkdir(parents=True, exist_ok=True)
    manifest_path = artifacts / "manifest.json"
    preflight_log = evidence / "preflight.log"
    build_log = evidence / "build.log"
    query_log = evidence / "configuration.log"
    checks = []
    manifest = {
        "schema": "firered-online-engine-b0-build-1", "run_id": args.run_id,
        "target": args.target, "source_url": SOURCE_URL, "source_commit": SOURCE_COMMIT,
        "patches": [], "baseline": "unmodified source", "started_at": now(),
        "host": {"system": platform.system(), "release": platform.release(),
                 "architecture": platform.machine(), "platform": platform.platform(),
                 "python": sys.version, "python_executable": str(Path(sys.executable).resolve())},
        "jobs": args.jobs, "worktree": str(tree), "artifact_directory": str(artifacts),
        "evidence_directory": str(evidence), "preflight_log": str(preflight_log),
        "configuration_log": str(query_log), "build_log": str(build_log),
        "build_exit_code": None, "build_started_at": None, "build_ended_at": None,
        "status": "PREFLIGHT RUNNING", "artifacts": [], "preflight_checks": checks,
    }
    exit_code = 2
    write_json(manifest_path, manifest)
    env = None
    git = None
    source = None
    try:
        make = absolute_path(args.make, "--make/B0_MAKE", executable=True)
        toolchain = absolute_path(args.toolchain, "--toolchain/B0_TOOLCHAIN")
        host_deps = absolute_path(args.host_deps, "--host-deps/B0_HOST_DEPS") if args.host_deps else None
        upstream_root = within(local / "upstream", local)
        source = within(Path(args.upstream) if args.upstream else upstream_root / "pokehns-expansion", upstream_root)
        make_safe_path(source)
        if not source.is_dir():
            raise PreflightError("Upstream clone is missing: {}".format(source))
        env = prepare_environment(make, toolchain, host_deps)
        manifest["environment"] = {key: env[key] for key in ("PATH", "LANG", "LC_ALL", "TZ", "PKG_CONFIG_PATH", "PKG_CONFIG_ALLOW_SYSTEM_LIBS", "PKG_CONFIG_ALLOW_SYSTEM_CFLAGS") if key in env}
        manifest["make"] = str(make)
        manifest["toolchain"] = str(toolchain)
        manifest["host_dependencies"] = str(host_deps) if host_deps else None
        git_name = shutil.which("git", path=env["PATH"])
        if not git_name:
            raise PreflightError("git is missing")
        git = Path(git_name).resolve()
        control_top = capture([str(git), "-C", str(root), "rev-parse", "--show-toplevel"],
                              root, env, preflight_log, checks, "Control repository boundary")
        if Path(control_top).resolve() != root:
            raise PreflightError("Control workspace is not a separate Git repository")
        for path in (tree, artifacts, evidence):
            capture([str(git), "-C", str(root), "check-ignore", "--", str(path)],
                    root, env, preflight_log, checks, "Private path ignored")
        manifest["reference_state_before"] = git_state(git, source, env, preflight_log, checks, "Reference before")
        if manifest["reference_state_before"]["head"] != SOURCE_COMMIT:
            raise PreflightError("Upstream HEAD differs from pinned {}".format(SOURCE_COMMIT))
        if not manifest["reference_state_before"]["clean"]:
            raise PreflightError("Upstream tracked/untracked source is dirty; pristine build refused")
        origin = capture([str(git), "-C", str(source), "remote", "get-url", "origin"],
                         source, env, preflight_log, checks, "Source origin")
        if origin.rstrip("/").removesuffix(".git") != SOURCE_URL:
            raise PreflightError("Source origin differs from the authorized candidate")
        manifest["source_origin"] = origin
        make_version = capture([str(make), "--version"], root, env, preflight_log, checks, "GNU Make version")
        match = re.search(r"GNU Make (\d+)\.(\d+)", make_version)
        if not match or tuple(map(int, match.groups())) < (4, 2):
            raise PreflightError("GNU Make >=4.2 is required to preserve upstream .SHELLSTATUS checks")
        for binary, version_args in (("git", ["--version"]), ("cc", ["--version"]),
                                     ("g++", ["--version"]), ("bash", ["--version"]),
                                     ("python3", ["--version"]), ("pkg-config", ["--version"])):
            resolved = shutil.which(binary, path=env["PATH"])
            if not resolved:
                raise PreflightError("Host dependency missing: {}".format(binary))
            capture([resolved] + version_args, root, env, preflight_log, checks, binary + " version")
        for binary in ("perl", "sed", "find", "sort", "cat", "uname", "grep"):
            resolved = shutil.which(binary, path=env["PATH"])
            if not resolved:
                raise PreflightError("Host dependency missing: {}".format(binary))
            checks.append({"label": binary + " availability", "path": resolved})
        pkg_config = shutil.which("pkg-config", path=env["PATH"])
        capture([pkg_config, "--exists", "libpng"], root, env, preflight_log, checks, "libpng dependency")
        capture([pkg_config, "--modversion", "libpng"], root, env, preflight_log, checks, "libpng version")
        capture([pkg_config, "--cflags", "--libs", "libpng"], root, env, preflight_log, checks, "libpng configuration")
        for binary in ("gcc", "cpp", "as", "ld", "objcopy", "objdump", "ar"):
            compiler = toolchain / "bin" / ("arm-none-eabi-" + binary)
            absolute_path(str(compiler), "ARM tool " + binary, executable=True)
            capture([str(compiler), "--version"], root, env, preflight_log, checks, "ARM " + binary + " version")
        compiler = toolchain / "bin/arm-none-eabi-gcc"
        for library in ("libgcc.a", "libnosys.a", "libc.a"):
            result = capture([str(compiler), "-mthumb", "-print-file-name=" + library],
                             root, env, preflight_log, checks, "ARM library " + library)
            if not Path(result).is_absolute() or not Path(result).is_file():
                raise PreflightError("ARM library missing: {} ({})".format(library, result))
            checks.append({"label": "ARM library hash", "path": result, "sha256": digest(Path(result))})
        patch_copy = None
        if args.patch:
            patches_root = within(root / "patches", root)
            patch = within(Path(args.patch), patches_root)
            if patch.suffix != ".patch" or not patch.is_file():
                raise PreflightError("--patch must name an existing .patch file under this control repository's patches/")
            patch_copy = evidence / "applied-repair.patch"
            shutil.copyfile(str(patch), str(patch_copy))
            manifest["patches"] = [{"path": str(patch), "applied_copy": str(patch_copy),
                                    "sha256": digest(patch_copy), "bytes": patch_copy.stat().st_size}]
            manifest["baseline"] = "patched source"
            manifest["repair_branch"] = "codex/{}-{}".format(args.target, args.run_id)
        worktree_command = [str(git), "-C", str(source), "worktree", "add"]
        worktree_command.extend(["-b", manifest["repair_branch"]] if patch_copy else ["--detach"])
        worktree_command.extend(["--", str(tree), SOURCE_COMMIT])
        capture(worktree_command,
                source, env, preflight_log, checks,
                "Create fresh isolated repair worktree" if patch_copy else "Create fresh isolated detached worktree")
        manifest["worktree_state_before"] = git_state(git, tree, env, preflight_log, checks, "Worktree before")
        if manifest["worktree_state_before"]["head"] != SOURCE_COMMIT or not manifest["worktree_state_before"]["clean"]:
            raise PreflightError("Fresh worktree is not clean at the exact source pin")
        if patch_copy:
            capture([str(git), "-C", str(tree), "apply", "--check", "--", str(patch_copy)],
                    tree, env, preflight_log, checks, "Check reviewed local repair patch")
            capture([str(git), "-C", str(tree), "apply", "--", str(patch_copy)],
                    tree, env, preflight_log, checks, "Apply reviewed local repair patch")
            manifest["worktree_state_after_patch"] = git_state(git, tree, env, preflight_log, checks, "Worktree after patch")
            patch_diff = evidence / "patch-source-files.diff"
            with patch_diff.open("wb") as stream:
                patch_diff_result = subprocess.run([str(git), "-C", str(tree), "diff", "--binary", "HEAD", "--"],
                                                   cwd=str(tree), env=env, stdout=stream,
                                                   stderr=subprocess.STDOUT, check=False)
            manifest["patch_source_diff"] = {"path": str(patch_diff), "sha256": digest(patch_diff),
                                             "exit_code": patch_diff_result.returncode,
                                             "bytes": patch_diff.stat().st_size}
            if patch_diff_result.returncode != 0:
                raise PreflightError("Could not preserve applied patch source diff")
        manifest["configuration_files"] = fingerprint(tree)
        manifest["patch_config_fingerprint"] = hashlib.sha256(json.dumps(
            {"configuration_sha256": manifest["configuration_files"]["sha256"],
             "patch_sha256": [patch["sha256"] for patch in manifest["patches"]]},
            sort_keys=True, separators=(",", ":")).encode("utf-8")).hexdigest()
        query = evidence / "configuration-query.mk"
        query.write_text("\n".join("$(info B0CFG|{}|$({}))".format(key, key) for key in CONFIG_KEYS)
                         + "\n.PHONY: b0-config\nb0-config:\n\t@:\n", encoding="utf-8")
        # SETUP_PREREQS=0 and NODEP=1 stop parse-time tool/map generation and
        # dependency scanning. Upstream still creates ignored object directories.
        query_command = [str(make), "-f", "Makefile", "-f", str(query),
                         "BUILD=" + args.target, "TOOLCHAIN=" + str(toolchain),
                         "SETUP_PREREQS=0", "NODEP=1", "b0-config"]
        query_output = capture(query_command, tree, env, query_log, checks, "Read effective configuration")
        configuration = {}
        for line in query_output.splitlines():
            if line.startswith("B0CFG|"):
                _, key, value = line.split("|", 2)
                configuration[key] = value
        expected = {"BUILD_NAME": args.target, "MAP_VERSION": args.target,
                    "GAME_VERSION": "FIRERED" if args.target == "firered" else "POKEMON_HNS",
                    "ROM": "poke" + args.target + ".gba", "TEST": "0", "DEBUG": "0", "RELEASE": "0", "LTO": "0"}
        for key, value in expected.items():
            if configuration.get(key) != value:
                raise PreflightError("Unexpected effective {}: {!r}, expected {!r}".format(key, configuration.get(key), value))
        if set(configuration) != set(CONFIG_KEYS):
            raise PreflightError("Configuration introspection omitted required values")
        manifest["effective_configuration"] = configuration
        manifest["configuration_query_command"] = query_command
        manifest["configuration_query_caveat"] = "BUILD selects the same target; SETUP_PREREQS=0 NODEP=1 apply only to query. Makefile still creates ignored object directories."
        command = [str(make), args.target, "-j" + str(args.jobs), "TOOLCHAIN=" + str(toolchain)]
        manifest["build_command"] = command
        manifest["build_cwd"] = str(tree)
        manifest["status"] = "BUILD RUNNING"
        manifest["build_started_at"] = now()
        write_json(manifest_path, manifest)
        print("Running: {}".format(shlex.join(command)), flush=True)
        print("Combined log: {}".format(build_log), flush=True)
        with build_log.open("wb") as stream:
            process = subprocess.Popen(command, cwd=str(tree), env=env, stdout=stream, stderr=subprocess.STDOUT)
            try:
                code = process.wait()
            except KeyboardInterrupt:
                process.send_signal(2)
                code = process.wait()
                manifest["interrupted"] = True
        manifest["build_exit_code"] = code
        manifest["build_ended_at"] = now()
        for key in ("ROM", "ELF", "MAP", "SYM"):
            name = configuration[key]
            if name != "poke" + args.target + {"ROM": ".gba", "ELF": ".elf", "MAP": ".map", "SYM": ".sym"}[key]:
                raise PreflightError("Unexpected output path from pinned Makefile: {}".format(name))
            output = within(tree / name, tree)
            if output.is_file():
                destination = artifacts / name
                shutil.copyfile(str(output), str(destination))
                manifest["artifacts"].append({"kind": key, "filename": name, "path": str(destination),
                                              "source_path": str(output), "bytes": destination.stat().st_size,
                                              "sha256": digest(destination)})
        roms = [record for record in manifest["artifacts"] if record["kind"] == "ROM" and record["bytes"] > 0]
        if code != 0:
            manifest["status"] = "FAIL — EXECUTED"
            exit_code = code if code > 0 else 128 - code
        elif len(roms) != 1:
            manifest["status"] = "FAIL — EXECUTED: make exited 0 but ROM absent or empty"
            exit_code = 3
        else:
            manifest["status"] = "PASS — EXECUTED: compilation only"
            exit_code = 0
    except PreflightError as error:
        manifest["error"] = str(error)
        manifest["status"] = "BLOCKED — PREFLIGHT" if manifest["build_started_at"] is None else "FAIL — WRAPPER/POSTBUILD"
        print(str(error), file=sys.stderr)
    except (OSError, subprocess.SubprocessError) as error:
        manifest["error"] = "{}: {}".format(type(error).__name__, error)
        manifest["status"] = "BLOCKED — PREFLIGHT" if manifest["build_started_at"] is None else "FAIL — WRAPPER/POSTBUILD"
        print(manifest["error"], file=sys.stderr)
    finally:
        if git and env and source:
            try:
                manifest["reference_state_after"] = git_state(git, source, env, preflight_log, checks, "Reference after")
                if tree.exists() and (tree / ".git").exists():
                    manifest["worktree_state_after"] = git_state(git, tree, env, preflight_log, checks, "Worktree after generated build")
                    # Generation may modify tracked files (notably heal_locations).
                    # Preserve the final difference from pinned HEAD privately.
                    # In repair mode it includes the separately preserved patch
                    # source diff as well as later generated-file changes.
                    diff_path = evidence / "generated-tracked.diff"
                    with diff_path.open("wb") as stream:
                        diff_result = subprocess.run([str(git), "-C", str(tree), "diff", "--binary", "HEAD", "--"],
                                                     cwd=str(tree), env=env, stdout=stream,
                                                     stderr=subprocess.STDOUT, check=False)
                    manifest["generated_tracked_diff"] = {"path": str(diff_path), "sha256": digest(diff_path),
                                                         "exit_code": diff_result.returncode,
                                                         "bytes": diff_path.stat().st_size,
                                                         "comparison": "Final worktree versus pinned HEAD; includes intentional patch when patches is nonempty"}
            except PreflightError as error:
                manifest["final_state_error"] = str(error)
        for key, path in (("preflight_log", preflight_log), ("configuration_log", query_log), ("build_log", build_log)):
            if path.is_file():
                manifest[key + "_sha256"] = digest(path)
        manifest["ended_at"] = now()
        manifest["wrapper_exit_code"] = exit_code
        write_json(manifest_path, manifest)
        print("{}\nManifest: {}".format(manifest["status"], manifest_path), flush=True)
    return exit_code


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--target", choices=("firered", "hns"), required=True)
    parser.add_argument("--run-id", required=True, help="Unique safe label, e.g. baseline-01; never reuse for this target")
    parser.add_argument("--jobs", type=int, default=2, help="Parallel make jobs, 1–8; default 2")
    parser.add_argument("--make", default=os.environ.get("B0_MAKE"), help="Absolute GNU Make executable (or B0_MAKE)")
    parser.add_argument("--toolchain", default=os.environ.get("B0_TOOLCHAIN") or os.environ.get("B0_ARM_TOOLCHAIN"), help="Absolute ARM toolchain root containing bin/ (or B0_TOOLCHAIN/B0_ARM_TOOLCHAIN)")
    parser.add_argument("--host-deps", default=os.environ.get("B0_HOST_DEPS"), help="Optional absolute private host dependency prefix (or B0_HOST_DEPS)")
    parser.add_argument("--upstream", help="Optional upstream clone path; must remain under _local/upstream")
    parser.add_argument("--patch", help="One explicitly reviewed .patch under this repository's patches/; fresh local repair branch")
    args = parser.parse_args()
    if not re.fullmatch(r"[A-Za-z0-9][A-Za-z0-9_-]{0,63}", args.run_id):
        parser.error("--run-id must be 1–64 letters, digits, underscores or hyphens, beginning with a letter/digit")
    if not 1 <= args.jobs <= 8:
        parser.error("--jobs must be between 1 and 8")
    try:
        return build(args)
    except PreflightError as error:
        print(str(error), file=sys.stderr)
        return 2


if __name__ == "__main__":
    sys.exit(main())
