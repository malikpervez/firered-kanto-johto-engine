# B0 local tool setup (executed macOS arm64 configuration)

These commands reproduce the B0 prerequisite selection on macOS arm64 with an **already installed** Xcode toolchain. The executed host was macOS 27.0, SDK 27.0 and Apple Clang 21.0.0. Windows and other hosts were not tested. All new files stay in ignored `_local/tools/`; no Homebrew install, `sudo`, system prefix or shell-profile edit is required.

The current workspace already contains these tools. To reproduce acquisition/building, use a separate B-owned workspace with an empty `_local/tools/`; do not overwrite existing logs or installations. The exact observed archive and installed-file hashes, commands, timestamps and results are in [`toolchain.lock.json`](../toolchain.lock.json). Prerequisite self-tests do not establish game behavior.

## Shell, downloads and integrity

Start Bash from the control-repository root. The logger below preserves stdout/stderr together and returns the command's real exit code. `set -e` stops on download, checksum, configuration, build or install failure. A failed download remains local for diagnosis; do not extract it.

```bash
bash
set -e
B0_TOOLS_ROOT="$(pwd -P)/_local/tools"
B0_HOST_PREFIX="$B0_TOOLS_ROOT/host"
B0_DOWNLOADS="$B0_TOOLS_ROOT/downloads"
mkdir -p "$B0_DOWNLOADS" "$B0_TOOLS_ROOT/src" \
  "$B0_TOOLS_ROOT/logs" "$B0_HOST_PREFIX"
export CC=/usr/bin/clang CXX=/usr/bin/clang++

run() {
  B0_LOG_NAME="$1"
  shift
  if "$@" > "$B0_TOOLS_ROOT/logs/$B0_LOG_NAME.log" 2>&1; then
    B0_COMMAND_RC=0
  else
    B0_COMMAND_RC=$?
  fi
  printf '%s\n' "$B0_COMMAND_RC" \
    > "$B0_TOOLS_ROOT/logs/$B0_LOG_NAME.exit-code"
  return "$B0_COMMAND_RC"
}

B0_ARM_ARCHIVE=arm-gnu-toolchain-14.2.rel1-darwin-arm64-arm-none-eabi.tar.xz
B0_ARM_URL="https://developer.arm.com/-/media/Files/downloads/gnu/14.2.rel1/binrel/$B0_ARM_ARCHIVE"
run download-arm curl --fail --location --retry 2 --max-time 180 \
  --output "$B0_DOWNLOADS/$B0_ARM_ARCHIVE" "$B0_ARM_URL"
run download-arm-checksum curl --fail --location --retry 2 --max-time 180 \
  --output "$B0_DOWNLOADS/$B0_ARM_ARCHIVE.sha256asc" "$B0_ARM_URL.sha256asc"
run download-make curl --fail --location --retry 2 --max-time 180 \
  --output "$B0_DOWNLOADS/make-4.4.1.tar.gz" \
  https://ftp.gnu.org/gnu/make/make-4.4.1.tar.gz
run download-pkgconf curl --fail --location --retry 2 --max-time 180 \
  --output "$B0_DOWNLOADS/pkgconf-2.5.1.tar.xz" \
  https://distfiles.ariadne.space/pkgconf/pkgconf-2.5.1.tar.xz
run download-libpng curl --fail --location --retry 2 --max-time 180 \
  --output "$B0_DOWNLOADS/libpng-1.6.59.tar.gz" \
  https://download.sourceforge.net/libpng/libpng-1.6.59.tar.gz
run download-zlib curl --fail --location --retry 2 --max-time 60 \
  --output "$B0_DOWNLOADS/zlib-1.3.2.tar.gz" \
  https://zlib.net/zlib-1.3.2.tar.gz

cat > "$B0_DOWNLOADS/b0-sha256.txt" <<'HASHES'
c7c78ffab9bebfce91d99d3c24da6bf4b81c01e16cf551eb2ff9f25b9e0a3818  arm-gnu-toolchain-14.2.rel1-darwin-arm64-arm-none-eabi.tar.xz
dd16fb1d67bfab79a72f5e8390735c49e3e8e70b4945a15ab1f81ddb78658fb3  make-4.4.1.tar.gz
cd05c9589b9f86ecf044c10a2269822bc9eb001eced2582cfffd658b0a50c243  pkgconf-2.5.1.tar.xz
86a3e4b501f7f50e392c4e456ea158893e9a595b1c63eb88c7bb9f6cf8772dad  libpng-1.6.59.tar.gz
bb329a0a2cd0274d05519d61c667c062e06990d72e125ee2dfa8de64f0119d16  zlib-1.3.2.tar.gz
HASHES
cd "$B0_DOWNLOADS"
run archive-checksums shasum -a 256 -c b0-sha256.txt
run arm-vendor-checksum shasum -a 256 -c "$B0_ARM_ARCHIVE.sha256asc"
run extract-arm tar -xf "$B0_ARM_ARCHIVE" -C "$B0_TOOLS_ROOT"
run extract-make tar -xf make-4.4.1.tar.gz -C "$B0_TOOLS_ROOT/src"
run extract-pkgconf tar -xf pkgconf-2.5.1.tar.xz -C "$B0_TOOLS_ROOT/src"
run extract-libpng tar -xf libpng-1.6.59.tar.gz -C "$B0_TOOLS_ROOT/src"
run extract-zlib tar -xf zlib-1.3.2.tar.gz -C "$B0_TOOLS_ROOT/src"
```

Arm's downloaded checksum matched. The libpng and zlib hashes matched their [official libpng](https://www.libpng.org/pub/png/libpng.html) and [official zlib](https://zlib.net/) pages. Make and pkgconf are pinned by the local download hashes; publisher signatures were not verified. Their sources are the [GNU Make distribution](https://ftp.gnu.org/gnu/make/) and the release location documented by [pkgconf](https://github.com/pkgconf/pkgconf). Hash verification must finish before extraction.

## Configure, build, inspect checks and install

The sequence below uses the exact executed configuration options and two build workers. GNU Make and pkgconf self-checks are explicitly collected without stopping the subsequent **local tool installation** because their observed limitations are documented below. Any different failure must be inspected before proceeding. These exceptions apply to tool self-tests, not game build failures.

```bash
cd "$B0_TOOLS_ROOT/src/make-4.4.1"
run make-configure ./configure --prefix="$B0_HOST_PREFIX" --without-guile
run make-build /usr/bin/make -j2
if run make-check /usr/bin/make check; then
  printf 'GNU Make self-check passed\n'
else
  printf 'GNU Make self-check failed; review make-check.log and exit-code\n'
fi
run make-install /usr/bin/make install

cd "$B0_TOOLS_ROOT/src/pkgconf-2.5.1"
run pkgconf-configure ./configure --prefix="$B0_HOST_PREFIX" \
  --disable-shared --enable-static \
  --with-pkg-config-dir="$B0_HOST_PREFIX/lib/pkgconfig"
run pkgconf-build /usr/bin/make -j2
if run pkgconf-check /usr/bin/make check; then
  printf 'pkgconf self-check passed\n'
else
  printf 'pkgconf self-check incomplete/failed; review pkgconf-check.log and exit-code\n'
fi
run pkgconf-install /usr/bin/make install
ln -s pkgconf "$B0_HOST_PREFIX/bin/pkg-config"

cd "$B0_TOOLS_ROOT/src/libpng-1.6.59"
run libpng-configure ./configure --prefix="$B0_HOST_PREFIX" \
  --disable-shared --enable-static
run libpng-build /usr/bin/make -j2
run libpng-check /usr/bin/make check
run libpng-install /usr/bin/make install

cd "$B0_TOOLS_ROOT/src/zlib-1.3.2"
run zlib-configure ./configure --prefix="$B0_HOST_PREFIX" --static
run zlib-build /usr/bin/make -j2
run zlib-check /usr/bin/make check
run zlib-install /usr/bin/make install
```

Libpng was built and self-tested against the installed Apple SDK zlib. The local zlib installation supplies `zlib.pc`, which macOS did not provide, and the final native host-tool linker searches the local prefix. All configure/build/install commands above succeeded. Installation of Make/pkgconf followed their recorded self-check limitations; the initial orchestration stopping after a check failure is not needed for reproduction.

| Executed tool check | Result and evidence |
|---|---|
| ARMv4T/Thumb compiler smoke | PASS — EXECUTED; `versions-and-smoke.log` records ARMv4T/Thumb-1 attributes |
| GNU Make 4.4.1 `make check` | FAIL — EXECUTED, exit 2; nine tests in `features/archives` disagreed with archive member timestamp expectations using Apple `ar`; other categories passed. Details remain in `make-check.log` and `src/make-4.4.1/makeerror-4.4.1-aarch64-apple-darwin27.0.0-rxsy.tar.gz` |
| pkgconf 2.5.1 `make check` | BLOCKED, exit 2; optional `kyua` test runner absent; `pkgconf-check.log` |
| libpng 1.6.59 `make check` | PASS — EXECUTED, exit 0; 36/36 tests; `libpng-check.log` |
| zlib 1.3.2 `make check` | PASS — EXECUTED, exit 0; `zlib-check.log` |
| Final activation/dependency lookup | PASS — EXECUTED, exit 0; `activation-validation.log` |

All log names in the table are relative to `_local/tools/logs/`. Apple GNU Make 3.81 was separately observed to support `$(or ...)`; Make 4.4.1 is the explicitly pinned choice, not evidence that this selector requires an upgrade.

## Shell activation and validation

Create activation after installation, using the actual project root. The file below affects only shells that explicitly source it.

```bash
cat > "$B0_TOOLS_ROOT/activate.sh" <<SH
B0_TOOLS_ROOT='$B0_TOOLS_ROOT'
export B0_ARM_TOOLCHAIN="\$B0_TOOLS_ROOT/arm-gnu-toolchain-14.2.rel1-darwin-arm64-arm-none-eabi"
export B0_HOST_PREFIX="\$B0_TOOLS_ROOT/host"
export B0_HOST_DEPS="\$B0_HOST_PREFIX"
export B0_MAKE="\$B0_HOST_PREFIX/bin/make"
export PATH="\$B0_HOST_PREFIX/bin:\$B0_ARM_TOOLCHAIN/bin:\$PATH"
export PKG_CONFIG_PATH="\$B0_HOST_PREFIX/lib/pkgconfig"
export PKG_CONFIG_LIBDIR="\$B0_HOST_PREFIX/lib/pkgconfig"
export PKG_CONFIG_ALLOW_SYSTEM_LIBS=1
export PKG_CONFIG_ALLOW_SYSTEM_CFLAGS=1
SH
source "$B0_TOOLS_ROOT/activate.sh"
run make-version "$B0_MAKE" --version
run arm-gcc-version arm-none-eabi-gcc --version
run arm-ld-version arm-none-eabi-ld --version
run pkgconf-version pkg-config --version
run dependency-versions pkg-config --modversion libpng zlib
run dependency-link-search pkg-config --libs-only-L libpng
run armv4t-smoke arm-none-eabi-gcc -mthumb -mthumb-interwork \
  -mabi=apcs-gnu -mtune=arm7tdmi -march=armv4t -std=gnu17 \
  -x c -c /dev/null -o "$B0_TOOLS_ROOT/armv4t-smoke.o"
run armv4t-attributes arm-none-eabi-readelf -A "$B0_TOOLS_ROOT/armv4t-smoke.o"
```

Expected versions: GCC 14.2.1 (20241119), binutils 2.43.1.20241119, Make 4.4.1, pkgconf 2.5.1, libpng 1.6.59 and zlib 1.3.2. `--libs-only-L libpng` must include the absolute local `host/lib` path. `PKG_CONFIG_ALLOW_SYSTEM_LIBS/CFLAGS` is necessary because pkgconf treats its own configured prefix as a system search path and otherwise suppresses these flags.

For existing B0 tools, source `[LOCAL_WORKSPACE]/_local/tools/activate.sh` and use the manual game wrapper documented in [`README.md`](../README.md). A direct upstream Make invocation needs `TOOLCHAIN="$B0_ARM_TOOLCHAIN"` on the command line because the pinned upstream Makefile assigns that variable internally. Build only one selected target per isolated tree.
