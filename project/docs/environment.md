# B0 execution environment

Inspected October 8, 2026 (owner timezone America/New_York). Tester: Codex.

Workspace: `[LOCAL_WORKSPACE]`. It initially contained only `AGENTS.md`, `WORKSTREAM_B_REQUIREMENTS.md`, `B0_ACCEPTANCE_CHECKLIST.md`, `CODEX_KICKOFF_PROMPT.md`, and `START_HERE.md`. `git status` returned exit 128: no Git repository in this folder or its parents. The instructions identify this as B; no multiplayer source or service configuration was present. Workstream A was not inspected or changed.

Created a separate local Git control repository, with no commits, staging, or remote. `_local/` is ignored before acquiring source or binaries. Original instruction hashes and discovery command outputs are preserved in `_local/evidence/environment-initial.json`.

| Component | Observed value |
|---|---|
| OS | macOS 27.0, build 26A428 |
| Kernel / architecture | Darwin 27.0.0 / arm64 |
| Shell | `/bin/zsh`; upstream recipes use Bash with pipefail |
| Initial free storage | approximately 18 GiB, APFS data volume |
| Git | Apple Git 2.54.0 (Apple Git-157) |
| System Make | GNU Make 3.81; not used for baseline builds |
| Native compiler | Apple clang 21.0.0 (clang-2100.3.34.2) |
| Python | 3.9.6 |
| SDK | `/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk` |
| Initial ARM compiler / pkg-config / libpng / mGBA | absent from PATH / inspected standard installation locations |

Project-local tools are recorded in `toolchain.lock.json`, with acquisition identities and version checks. GNU Make 4.4.1 was chosen for reproducibility and the pinned Makefile's `.SHELLSTATUS` error checks (the wrapper requires Make >=4.2). An executed smoke check confirmed system Make 3.81 supports `$(or ...)`; it was not proven unable to select the target. No Homebrew package installation, privileged installer, shell-profile edit, or global tool replacement was performed. Each target build uses two jobs. Initial baseline builds ran sequentially; later reviewed experimental FireRed/HnS pairs run in separate trees concurrently, at four build jobs total. No shared target tree is reused.

Desktop mGBA 0.10.5 was acquired from the [official downloads page](https://mgba.io/downloads.html) and copied into `_local/tools/mGBA.app`, without installing into `/Applications`. Official archive URL: `https://github.com/mgba-emu/mgba/releases/download/0.10.5/mGBA-0.10.5-macos.dmg`; SHA-256: `443b490ec728293dfcde1cb9db160f73d94c457cb1864f3ce0407e60e174b09c`. The read-only disk image was unmounted after copying.

Codex opened its desktop window and inspected preferences via GUI controls. Observed: OpenGL display, frameskip 0, SDL audio, 44100 Hz, 1536-sample buffer, audio synchronization on, video synchronization off, target 60 FPS. `Load last state` was enabled, periodic state autosave disabled, Discord Rich Presence disabled. Preferences inspection was canceled without applying changes. Loading last state must be disabled for cold-reload acceptance. Application access is available; opening an empty emulator is not a ROM boot or gameplay test. Audio quality has not been measured.

For the subsequent fresh HnS native test, Codex applied state autoload OFF, cheats autoload OFF, periodic state autosave OFF, and the native 59.7275 FPS target, with saves alongside the dedicated session ROM. Actual RTC was chosen in the game's Recommended campaign setup; no host clock was changed. Final executed outcomes and save identities are in `docs/hns-native-results.md` / `docs/test-results.md`. Audio remains NEEDS OWNER TEST because the GUI tool does not provide audible output.

## Windows reproduction notes — NOT RUN

The pinned [Windows WSL guide](https://github.com/PokemonHnS-Development/pokehns-expansion/blob/167aa6d537b109bb229c231ddce4616974c4da71/docs/install/windows/WSL.md) and [INSTALL.md](https://github.com/PokemonHnS-Development/pokehns-expansion/blob/167aa6d537b109bb229c231ddce4616974c4da71/INSTALL.md) are the starting points. Inspect the actual Windows host and existing WSL before any installation. Have the owner approve system-level setup. Keep the source and target trees in a B-owned Linux filesystem directory; build one target per fresh tree with GNU Make and an ARMv4T-compatible ARM GCC toolchain, libpng, pkg-config, Python 3, Git, and host C/C++ compilers. Use the exact locked source SHA and preserve logs/hashes as here. Open copied outputs in official desktop mGBA on Windows with separate native-save directories and state autoload disabled.

No Windows/WSL build or Windows emulator test was executed in this session. macOS results cannot be labeled Windows passes.
