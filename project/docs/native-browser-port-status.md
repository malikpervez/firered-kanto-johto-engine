# Source-native browser port checkpoint — 2026-10-16

## Player name-entry crash repair

The current package is `host-naming-04`, build `native-01-1c9920fb39873e75`. Earlier checkpoints below retain their original build identities.

The owner-reported memory-access crash reproduced at frame 2244 after confirming a player name. The symbolized stack led to `SpriteCB_Underscore` inside `AnimateSprites` and `CB2_NamingScreen`: the naming task had freed its state while the same frame's sprites and VBlank callback could still read it.

The exit now defers release to a dedicated main callback. It preserves the typed destination callback, clears naming interrupt callbacks, retires naming sprites and helper tasks outside task traversal, and frees the windows/state before handing control back. The focused fresh-flash regression passed through frame 2306 and displayed Oak's player-name confirmation; no renderer or sampled heap errors occurred. Private before/after evidence lives in `_local/ports/firered-native-01/build/name-entry-{before-03,after-04}/`.

The post-fix naming sequence was checked in Node/Wasm only. No duplicate browser playthrough, personal-save test, other naming-screen variant, or campaign acceptance was performed. Reload the local preview to load this package.

## New Game freeze repair

The repaired New Game package was `host-newgame-03`, build `native-01-e3be454d254f9f66`. The original host02 checkpoint below is retained as historical evidence.

Starting New Game reached the controls-screen renderer, where `GLYPH_COPY` performed undefined 32-bit shifts. In the WebAssembly output, aligned narrow glyphs could write into the next heap header. The following window allocation then looped through the damaged list indefinitely, blocking the browser thread. The old build reproducibly stopped after frame 630 in New Game state 7; a bounded profiler attributed 93.4% of samples to `AllocInternal`.

The port now handles full-width masks and aligned shifts explicitly and only writes a second tile word when pixels actually spill into it. Host allocation also validates and bounds list traversal, reporting corruption instead of spinning. The original 35a source and personal saves remain untouched.

Focused verification: the original glyph routine failed 62 of 265 pixel/reference cases, including seven surrounding-memory corruptions; the corrected routine passed all 265. The full corrected module passed the same fresh-flash New Game path through 720 frames, displayed and advanced the controls page, and retained valid sampled heap lists. The same build also reached and advanced the controls page in the in-app browser, and Pause responded without console errors. No campaign playthrough or save acceptance was run. Private evidence: `_local/ports/firered-native-01/build/newgame-freeze-{before-02,after-03}/` and `port/text/checks/01/`.

The owner authorized porting after specifying desktop WASD, iPhone browser/Home Screen support with traditional GBA touch controls, local normal saves with explicit Files backups, existing content first, and minimal assistant gameplay testing. This authorization advances the browser port beyond the original B0 scope. Existing workstream, publication and personal-save boundaries remain in force.

The isolated implementation and private evidence live under ignored `_local/ports/firered-native-01/`. It compiles candidate 35a C source directly to WebAssembly. It is not an ARM CPU emulator or a ROM wrapper. The original 35a source and saves remain separate.

## Delivered checkpoint

- Build `native-01-b8528a5ba11b1c15`: 400 game C objects, 1,126 converted data/music objects and 25 host units linked successfully. Regenerated original data objects matched all 1,126 original objects before conversion.
- Browser adapter: keyboard WASD/arrows, GBA-style touch input, WebAudio, pause/focus handling, native normal-save storage and explicit `.frsave.json` Files import/export. A backup contains the last confirmed in-game save, not a snapshot of the current scene.
- Host implementation: frame scheduling, memory/register/DMA support, required BIOS operations, custom asset decompression, RNG, typed script calls, current sound paths, RTC, native flash handling, and the current renderer for modes 0/1 with 1D sprites.
- All implementation, artifacts, gameplay artwork and screenshots remain ignored and local. No commit, push, PR, public deployment, hosted CI, Workstream A/C or system-wide installation was performed.

## Executed evidence

The bounded Node startup ran 480 frames from empty flash, produced PCM samples, and reported no renderer errors. One in-app browser start/pause displayed native startup artwork with no captured console errors. No personal save was loaded. Component and storage fixtures are recorded separately and do not establish gameplay or real browser persistence acceptance.

The local preview was started at `http://127.0.0.1:51686/` and left paused for the owner. That address is only available on this Mac while the process is running. It is not a public or iPhone-accessible deployment.

## Remaining work and owner use

This is the first running development build, not a full campaign acceptance claim. Real normal-save persistence/cold Continue, iPhone touch/audio/Files/Home Screen behavior, complete graphics parity and full-game offline caching remain unqualified. Unsupported renderer configurations currently stop with an explicit error. Logical ROM/WRAM address assumptions require further porting review; physical GCN/RFU/e-Reader links and downloaded ARM execution are unsupported.

Use **Resume** in the local preview to try this build. Save through the game's normal menu; **Save to Files** exports a separate backup after a valid normal save exists. Do not use personal legacy saves for this development checkpoint. Existing content and base-port blockers remain the priority before enhancements or new characters/events. Assistant testing should stay limited to brief startup and specific blocker reproduction.

For exact source/toolchain pins, commands, hashes, limitations and evidence, see the ignored port's `README.md`, `checkpoint.json`, `source-checkpoint.json`, `engine-changes.patch`, `browser-package.json`, and `build/startup-smoke-02/`.
