> **History.** This was the manual verification procedure for the 37C review snapshot. Development now follows
> [AGENTS.md](AGENTS.md): build with `make` in `engine/`, test with pae. `scripts/verify_source.py` checks the 37C
> snapshot and reports the files changed since (expected).

# Manual cloud verification

This is source/build/engineering testing. A complete game playthrough or Delta/device acceptance is not established by these commands. The cloud platform itself has not been operated by the exporting agent.

## 1. Source integrity — no compiler required

```sh
python3 scripts/verify_source.py
```

Checks all included engine bytes against the frozen 37C inventory. A mismatch is a failure to investigate; do not rewrite expected hashes.

## 2. Three omitted upstream inputs

Three tiny/embedded original multiboot programs are referenced by the upstream build: `data/mb_berry_fix.gba`, `data/mb_colosseum.gba`, `data/mb_ereader.gba`. They are not this project’s game ROM and are not uploaded. Restore them from the exact selected public upstream commit into ignored paths:

```sh
python3 scripts/bootstrap_upstream_inputs.py --fetch
python3 scripts/verify_source.py --require-embedded
```

Alternatively pass `--cache /path/to/an/existing/pinned/upstream-checkout` instead of `--fetch`. The script checks SHA-256 and length and refuses mismatched existing files. No emulator executables, game releases or BIOS are downloaded. If the cloud task has no GitHub read access/network, mark this setup BLOCKED rather than replacing/removing the inputs.

## 3. Toolchain and dependencies

The historical local build used **Arm GNU Toolchain 14.2.Rel1 (Build arm-14.52), GCC 14.2.1 20241119**, GNU Make 4.4.1, host C/C++, libpng/pkg-config, Python 3, Perl and Bash. Select GNU Make >=4.2 and a complete `arm-none-eabi` toolchain with newlib; preserve compiler version output.

Use the official Arm release for the cloud host architecture, installed only inside that task’s allowed tool directory. Reference: https://developer.arm.com/tools-and-software/gnu-toolchain . The exact macOS package/checksum does not validate a Linux package. Verify the publisher’s checksum for a separately selected Linux download. Do not reuse macOS executables on Linux.

Pinned upstream Ubuntu instructions are in `engine/docs/install/linux/UBUNTU.md`. They list build-essential, binutils-arm-none-eabi, gcc-arm-none-eabi, libnewlib-arm-none-eabi, Git, libpng-dev and Python 3. A distribution compiler may differ from the recorded version: disclose that as an alternate-toolchain build, not an identical reproduction. In a permitted disposable cloud container, Bash/Perl/pkg-config and these host dependencies must also be present. No package installation is automated by this repository.

## 4. Full fresh-copy FireRed build

Set `ARM_TOOLCHAIN` to the installed toolchain directory containing `bin/arm-none-eabi-gcc`.

```sh
python3 scripts/build_candidate.py --toolchain "$ARM_TOOLCHAIN" --run-id cloud-build-01 --jobs 2
```

If necessary pass `--make /path/to/GNU/make`; a private host dependency prefix can be supplied with `--host-prefix /path/to/prefix`. Run IDs must be new: no test overwrites an earlier run. The wrapper verifies all required source inputs, copies them to ignored `_local/runs/cloud-build-01/engine`, uses the recorded settings, and captures stdout/stderr separately plus the real make return code and available artifact hashes. It does not call a cleanup target or alter frozen `engine/`.

Compare ROM SHA-256 and linked headroom against `provenance/local-build-reference.json`. A hash mismatch must be explained using compiler/configuration/generated-input differences; it must not be called a matching build. ELF and MAP can carry host/path differences. Preserve failures and do not suppress errors or remove content to make a link fit. No ROM or generated object/log is committed.

## 5. Actual ARM layout regression

Run the full fresh-copy build first. Set `ARM_TOOLCHAIN` to the complete toolchain directory, containing `bin/arm-none-eabi-gcc` and `bin/arm-none-eabi-objcopy`. Use its generated headers with the actual source in that build copy; the test does not substitute fake map constants.

```sh
python3 scripts/check_arm_layout.py --toolchain "$ARM_TOOLCHAIN" --engine-root _local/runs/cloud-build-01/engine --run-id cloud-layout-01
```

This compiles the existing three probes against the actual current headers, comparing **397 structure/offset/constants** with the 37C expectations. Logs and assembly/object diagnostics are in ignored `_local/checks/cloud-layout-01/`. It does not serialize a real save or establish save compatibility.

## 6. Broader checks and findings

Upstream’s native battle test sources remain under `engine/test/`. Its `check` target requires a specially built and validated mGBA ROM-test runner/hydra, not a regular emulator app. Prebuilt emulator executables are intentionally excluded. Do not invoke a default `make check` and assume it tests this FireRed snapshot: target selection and test build isolation must be verified first. If a trusted runner is not available, report those tests NOT RUN. A source/ARM/build audit can proceed independently.

Audit the real C, script and data interfaces, including saves, map decoder spans, party/storage gifts, regional namespaces, replica battle outcomes, follower/sprite lifetimes, heap pressure and source/tool provenance. Return actionable findings with exact current file/line, trigger, causal chain, severity, validation and smallest repair proposal. Record blocked and unexecuted cases honestly. Do not turn review findings into code changes or a PR without owner direction.

The original local owner review has private screenshots and staged save traces; they remain excluded. Historical Markdown claims are not independent cloud execution. The public/native snapshot cannot recreate excluded personal or B-owned saved histories automatically.
