# B1 browser runtime assessment

**Current status: source review and partial browser execution completed; further tests stopped at owner direction.** The owner accepted this candidate for isolated B testing. [Executed results](b1-browser-test-results.md) record FireRed gameplay, two normal saves and one cold tab reopening; remaining checks are deferred. No A repository was inspected or production dependency selected. The original source assessment below uses its distinct source pin; the actual npm binary pin is recorded in the results.

## Concrete candidate for coordination

Propose the framework-independent `@thenick775/mgba-wasm` core from `thenick775/mgba`, source commit `d5e226c63725f79bc96c7f75e2c8cbf07af9f2cd`, observed on `feature/wasm`. This is a third-party mGBA fork and a proposed test candidate, not A's selected dependency or an approved production wrapper. Its pinned package declares version 2.5.1 and MPL-2.0. Published binary provenance and hashes must be established separately; the source version does not prove a package was built from this commit. [Pinned package metadata](https://github.com/thenick775/mgba/blob/d5e226c63725f79bc96c7f75e2c8cbf07af9f2cd/src/platform/wasm/package.json), [license](https://github.com/thenick775/mgba/blob/d5e226c63725f79bc96c7f75e2c8cbf07af9f2cd/LICENSE).

Its documented initialization and lifecycle APIs are enough for a small local compatibility harness. It requires same-origin files and cross-origin isolation headers for threads. A later test server must bind to loopback; these are local HTTP response headers, not approval to change A, the router or NAS. No server or runtime was started during the original source-only audit; later execution is reported separately. [Pinned runtime instructions](https://github.com/thenick775/mgba/blob/d5e226c63725f79bc96c7f75e2c8cbf07af9f2cd/src/platform/wasm/README.md).

## Inspected contract and limits

| Area | Source finding | Required executed check |
|---|---|---|
| Native saves | `getSave()` reads native file bytes; `.sav` uploads go to `/data/saves`. Upload accepts bytes without validating the game format. `loadGame` permits an explicit save path. | Compare lengths, hashes, sectors and gameplay fields across native → browser → native copies; determine suffix handling. |
| Persistence | `/data` is IDBFS; await `FSInit()` before use and `FSSync()` to persist changes. Upload completion is asynchronous. | Save in the game, export after the core has written the file, await storage sync, close/reopen and use Continue. Surface sync failures. |
| Save states | State upload/storage is separate from native saves. | Disable state autosave and automatic restoration before loading a ROM; never use states as save acceptance. |
| Input/focus | Button press/release and input enable APIs exist. | Release all held inputs on blur; check foreground/background transitions and key repeats. |
| Audio/speed | Audio controls and timing APIs exist. | Record browser/core versions, user-gesture audio activation, sustained speed and focus behavior. Owner's desktop audio report does not pass this test. |

These are API observations and test requirements, not executed browser outcomes. [Pinned JavaScript implementation](https://github.com/thenick775/mgba/blob/d5e226c63725f79bc96c7f75e2c8cbf07af9f2cd/src/platform/wasm/pre.js).

The C frontend enables rewind, automatic save states and automatic state restoration by default. A harness must explicitly disable them through the documented settings before loading, and record the effective settings. `quickReload()` alone does not demonstrate cold persistence. [Pinned frontend](https://github.com/thenick775/mgba/blob/d5e226c63725f79bc96c7f75e2c8cbf07af9f2cd/src/platform/wasm/main.c).

The build requests WebGL 2, pthreads with a five-worker pool and 256 MiB initial WebAssembly memory. These are browser-host requirements; they do not increase GBA ROM/RAM or object capacity. The package build script uses Docker. No Docker installation, image build, dependency installation or global tool change occurred. [Pinned build settings](https://github.com/thenick775/mgba/blob/d5e226c63725f79bc96c7f75e2c8cbf07af9f2cd/src/platform/wasm/CMakeLists.txt).

RTC cartridge handling exists in the pinned core: the clock samples a configured time source or host time and converts it using local time. Browser timezone, core auto-detection for these exact ROMs, clock continuity after reload and the game's day/night behavior remain untested. No runtime RTC setter is promised from the inspected JavaScript API. [Pinned RTC implementation](https://github.com/thenick775/mgba/blob/d5e226c63725f79bc96c7f75e2c8cbf07af9f2cd/src/gba/cart/gpio.c).

## Preserved execution procedure

The owner approved and then stopped the partial execution. This procedure is retained for a separately authorized resumption; it is not a current instruction to continue testing.

After the owner supplies A's read-only runtime contract or accepts this candidate for isolated B testing:

1. Pin and hash the actual loader/WASM/worker files and record their provenance, license notices, browser version and reported core version. Use one private test origin and local file selection; keep ROMs outside page source and published code.
2. Verify the exact 010 ROM hashes: FireRed `3e504731d9dd3c02ec273dc257c86f557caaf8c9b933d2f0ff73558c2e121a39`; HnS `4bb58fe3c06bc0b60146aa946cbc34f087efa607f525f68e0a1e99c0db9cde75`. Test targets separately. Preserve original native evidence and saves; use freshly named copies only.
3. Initialize storage, disable cheats, soft patches, rewind and both automatic state options. Await each file upload. Load with an explicit native-save path. Verify Continue, trainer/rival, Pokédex, party, inventory/money, location and progression against the copied native reference.
4. Test movement/menus/battle, audio, focus changes, ordinary speed and RTC observations. Make a legitimate in-game change, save normally, wait for native-save update, export bytes and await `FSSync()`. Hash the export and inspect its format without changing it.
5. Fully close/reopen the browser test session at the same origin, reload the exact ROM and choose Continue. Recheck the changed state. Test a second normal save/restart cycle. Refresh is an additional check, not a substitute for restart.
6. Copy the exported native save into a new desktop mGBA session for the same ROM. Fully cold-load through Continue and compare all requested fields. Record any footer, size or conversion issue before adapting bytes; no automatic truncation or guessed conversion.

| Check | Current result |
|---|---|
| Public pinned source/license/API review | EXECUTED — source evidence preserved |
| Actual binary provenance / runtime launch | EXECUTED; published package pin differs from initial assessed source |
| Browser title/input/gameplay/audio/speed | FireRed EXECUTED within reported scope; HnS owner-deferred |
| Focus / RTC/time/palette | Focus unqualified; limited clock/night palette observed, broad RTC pending |
| Native → browser → native save round trip | FireRed native → browser executed; desktop return/HnS deferred |
| Refresh and two cold-restart save cycles | FireRed two normal saves/one cold tab reopening executed; remainder deferred |

## Local evidence and decision

Read-only source retrieval evidence is under `[LOCAL_WORKSPACE]/_local/evidence/b1/browser-runtime-assessment/thenick775-mgba-d5e226c63725/`. `source-manifest.json` records original URLs, bytes and SHA-256 values; `commit.json` supplies Git tree `0d3abd635dda71273ded71cb8610f8985da88e3f`; `tree.json` retains the recursive API response. The response's top-level identity was separately recorded rather than confused with the commit object's tree identity. No downloaded code was executed.

**Browser acceptance is partial at owner stop.** Retain this candidate for development evaluation; no further test run is scheduled. Review [the B2 implementation proposal](b2-development-slice-requirements.md). No A change, full browser-compatibility or release certification is implied.
