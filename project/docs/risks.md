# Risks and preserved B0 decisions

**Current — candidate29, natural Indigo-to-Johto travel with repaired trees.** Native mGBA tree views **PASSED**. The Champion’s construction barrier disappears, and the outdoor road, coastal stairs, Surf crossing, New Bark landing, Elm introduction without a second starter, aide’s Potion, normal Save 7, full quit and cold Continue **PASSED** in candidate29. Identity, party, Pokédex, Potion ×1, HM03, native Kanto clear/eight badges and regional state were preserved exactly across that save/reload. **Return travel PASSED to Indigo11,8 after the cold reload, without repeating the introduction or Potion gift. The emulator is fully closed.** [Journey results and exact scope]([LOCAL_WORKSPACE]/docs/natural-johto-journey-results.md).

Candidate28’s Hall-of-Fame event, Oak referral and normal Save 6 **PASSED** from a staged eight-badge/Champion-room fixture; this does not establish a naturally completed League.

Candidate29 make and wrapper both exited 0; 22,204 ROM bytes remain. ROM SHA-256 `153db055de453e9a06cc0d5620108cb88dddfaed3fc299e44092d3198e329274`. Its 629 changed ROM bytes relative to candidate28 are confined to the three repaired map grids. [Build manifest]([LOCAL_WORKSPACE]/_local/artifacts/johto-full-29-firered/manifest.json).

Save layout and Workstream A remain unchanged. The four-byte main-save margin, roamer fidelity defect, Hall-of-Fame/special-sector atomicity and inherited graphics read spans remain open. Full campaigns, general save compatibility and player release remain unqualified. Earlier candidate23 completion/GO remains withdrawn.

## Historical candidate26

The following candidate26 record is preserved for its original scope; candidate29 above is current.

**Historical candidate26, Indigo’s western route to Johto.** Bounded desktop mGBA checks executed: the staged pre-Champion gate stays closed and returns the trainer; a staged Kanto Champion walks from Indigo through the pass into New Bark, meets Elm and receives the aide’s Potion, then saves normally, fully quits and cold-Continues. Repeat passage returns to Indigo without repeating the introduction. Independent preservation and repeat-entry reviews passed; the emulator is fully closed. [Travel results and exact scope]([LOCAL_WORKSPACE]/docs/indigo-west-pass-results.md). No full-campaign or player-release qualification is claimed.

Candidate26 ROM SHA-256 `c705c297ca34e86ec45d061ae9291073dcbfc3e545a3290b6d85a7816068ff13`;23,196 ROM bytes remain. Actual make exited0, the original wrapper exited2, and separate qualification exited0 after proving its sole changed C object differs by the one generated debug map-count byte2→3. This is an incremental build from verified25b, with no clean26 repeat. [Qualified build manifest]([LOCAL_WORKSPACE]/_local/artifacts/johto-full-26-firered/manifest.qualified.json).

The native6/FRJS1/content3/layout1 save identity, measured ARM layouts,256-byte regional reserve, static RAM and heap remain unchanged. The four-byte main-save margin, roamer fidelity, Hall-of-Fame/special-sector atomicity, inherited graphics read bounds and unknown runtime allocation peaks remain open. Staged checkpoints do not establish a natural League victory, complete campaigns or general save compatibility. Workstream A and publication boundaries remain unchanged.

Candidate25b’s Lab repairs and their executed fresh opening/starter/rival victory/exit and normal-save/cold checks remain preserved in the [Preserved25b repair audit]([LOCAL_WORKSPACE]/docs/candidate23-repair-and-tooling-audit.md). Earlier candidate23 completion/GO remains withdrawn. Save format/layout and Workstream A remain unchanged; the four-byte main-save margin and roamer fidelity defect stay open.

## Preserved historical records

These retain their original dates and executed scope. Earlier completion/GO and prepared-launcher wording is superseded by the current repair report above.

**Current handoff — October14, candidate23:** Kanto art/ambient scope complete for local development; GO for implementation handoff, HOLD for player release. [Current results and exact remaining limits]([LOCAL_WORKSPACE]/docs/kanto-redesign-and-ambient-results.md). Native occupied-party Save/cold check passed; no full campaign or broad compatibility claim. The historical milestone gates below are superseded only by the recorded later owner approvals.

**Current status — October 13, 2026:** B2's accepted two-map travel evidence remains frozen. The owner separately approved the FireRed-only save foundation and conversion of three B2 fixture copies, then resumed qualification. Implementation, conversion, host/ARM checks and fresh final04 native execution have recorded evidence; final05 native checks and review closeout are ongoing. See the [implementation contract](save-foundation-implementation.md), [conversion/host results](save-foundation-conversion-and-host-tests.md), [caller regression results](save-foundation-caller-regression-results.md) and [resume decision](decisions/2026-10-13-save-foundation-resume.md). Stop for review before independent Johto progression. No B3, campaign-completeness, general compatibility or release claim follows. Workstream A remains untouched.

The **four-byte FireRed main-block margin** and **roamer fidelity defect** remain open. The implemented FRJS1 foundation addresses FireRed's earlier extension-integrity/coherence design deficit, but its remaining native/runtime review must finish before regional progression. HnS retains its original format; special-sector atomicity, downgrade behavior and the three-input-only conversion scope remain explicit limits. The B2 013 missing-NPC failure remains recorded; final 014 reuses valid FRLG NPC art while retaining original HnS town/interior tiles. [C's targeted B2 notice](b2-c-dependency-notice.md) and [foundation notice](save-foundation-c-dependency-notice.md) preserve the frozen 010 package and unrelated art evidence.

**Earlier owner decision — October 9, 2026:** B1 audit and the frozen C inventory handoff were approved, with B0 limitations accepted for evaluation only. The B0 risks below remain historical evidence. See [the B1 authorization](decisions/2026-10-09-b1-audit-and-c-handoff.md), [B2 authorization](decisions/2026-10-09-b2-travel-slice.md) and separate [save-foundation approval](decisions/2026-10-10-save-foundation-implementation.md). Work beyond that bounded foundation and a full region merge remain subject to separate review.

## Preserved B1 findings with current disposition

| Priority | Audit finding | Disposition |
|---|---|---|
| 1 | Four-byte FireRed SaveBlock1 margin remains; the earlier B1/B2 extension was outside ordinary payload checksum protection and partial paths lacked a coherent regional-state design. | The approved FireRed-only 1,332-byte extension, 256-byte stored reserve, all-write-path transactions and three-fixture copy conversion are implemented and host/ARM-qualified. Final05 native/runtime checks and review closeout are ongoing; HOLD Johto progression. |
| 1 | HnS/FireRed persistent IDs overlap; HnS's later-Kanto travel logic resets Kanto progression. | No bulk campaign/script import; explicit regional state and ID mapping required. |
| 1 | Active overworld object budget is 16, below 25 trainers before NPCs/effects/followers. | Separate crowded-map engine design and runtime resource tests; no raised constants or multiplayer implementation. |
| 2 | Fame Checker and Teachy TV functionality disabled; other fidelity differences and postgame roamer mismatch remain. | Named restoration/accepted-difference decisions required; full campaign is NOT RUN. |
| 2 | Four literal HnS warp destinations fall outside its selected map set. | Source-only potential postgame/link defects; dynamic/script paths and gameplay behavior unqualified. |
| 2 | Browser qualification is partial: FireRed gameplay/two saves/one cold tab reopening executed; HnS browser, second reload/refresh/focus and desktop return deferred. | Owner accepted these deferred checks for the bounded B2 evaluation on October 9. Final 014 browser qualification is NOT RUN; resume only under an approved meaningful slice. A untouched; see browser results. |
| 2 | Static ROM/RAM allocations and art limits are measured; runtime peaks and full combined-region size remain unknown. | Final 014's two-map slice adds 85,248 linked-ROM bytes against 010 with unchanged static EWRAM/IWRAM. Budget each later package and preserve C's unaffected evidence; this does not measure full Johto or runtime peaks. |
| 2 | Save-foundation final04 observed one normal full save busy for 574 sampled frames, approximately 9.61 seconds. | Observed latency requires review; no accepted threshold or speedup claim. Final05 cycle attribution and bounded runtime observations remain separate from frame samples and physical hardware timing. |
| 2 | Unchanged upstream Trade Center readiness requires the later Sevii network progress bit even for two FireRed peers. | The early owned fixtures cannot qualify full post-trade timing through Parcel/capture alone. No flags granted or guard removed; retain NOT RUN for that native path. A reachable cable-battle partial-save check is separate. |
| 2 | Source/asset rights and inherited credit questions remain unresolved. | Local ignored inventory only; no publication approved. |

See the historical [B1 gate](b1-gate.md) for its reports and evidence categories. Later dispositions above are distinguished from those source findings; they do not transfer an old artifact's gameplay passes to the current build.

## Preserved B0 risks

**Owner update — October 9, 2026:** Audio is **PASS — OWNER-REPORTED** for the current B0 evaluation. See the [owner audio confirmation](decisions/2026-10-09-b0-owner-audio.md) for attribution and scope. This later confirmation supersedes earlier audio-pending statements below; Codex did not perform a new listening test. The prior frozen audit and native reports remain historical evidence. B0 remains HOLD for review of the four-byte save margin and FireRed roamer fidelity defect.

Source: `167aa6d537b109bb229c231ddce4616974c4da71`. Native arm64 macOS 27.0, locked local tools. This is an evaluation, not selection of the final combined-game engine.

| Priority | Open risk / evidence | Decision or next action |
|---|---|---|
| 1 | Pristine FireRed fails to compile. Narrow target repairs are individually reviewed; approved experimental builds must qualify their own artifacts. | Preserve every failed baseline, complete patch, log and real exit. Stop for broader restructuring, feature removal or another capacity change. |
| 1 | Approved FireRed reservation reduction measures **15,868 bytes / four bytes free**. Fifteen following offsets move by 84 bytes; live roamer and gameplay fields retain sizes. | Keep this limitation open. Fresh disposable saves only. No old-save compatibility or future-feature capacity claim. Sector/checksum/assertion retained. |
| 2 | LeafGreen remains 15,952 bytes (original 80-byte overflow); HnS/Emerald remain 15,760/15,752. ARM probes confirm unchanged non-FireRed offsets/sizes. | No LeafGreen build success or layout repair is claimed; do not broaden the approved reservation change. |
| 2 | Preserved FireRed 009 natural starter selection failed with an empty party. Final 010 initializes the existing monotype-OFF default; its fresh native starter test produced male Bulbasaur level 5 HP 19/19. | 009 failure remains retained; 010 FR-01–09 and both normal-save/cold-reload cycles PASS — EXECUTED for its fresh tested run; audio is PASS — OWNER-REPORTED. Gift/filter scripts, deliberate challenge choices and save layout remain intact. |
| 2 | FireRed One Island calls InitRoamer, whose non-HnS implementation selects Hoenn routes and Latias/Latios. | Keep the source-verified **FireRed roamer fidelity defect open**. Retaining the live slot or passing early gameplay cannot certify legendary-beast behavior. Postgame is NOT RUN. |
| 2 | FireRed selects 417 FRLG maps, zero HnS maps, Pallet/Oak/Kanto starters/Parcel and Sevii content in a shared Emerald Expansion engine. | Source identity and the fresh 010 Pallet/Oak/Bulbasaur/Parcel opening are executed. Complete gyms, Sevii access and campaign fidelity remain unqualified. |
| 2 | Shared day/night/RTC/palette code is preserved and enabled in configuration; the owner accepts it as a FireRed enhancement direction. | Record only executed observations. Full time/event/encounter regression remains NOT RUN; no new flags, save fields or policy in B0. |
| Resolved for current evaluation | GUI tools cannot hear audio; the project owner reports audio is all good on October 9, 2026. | PASS — OWNER-REPORTED; general current-evaluation confirmation, with no separate target/hash/scene/settings breakdown supplied. Historical ROMs are not retrospectively qualified. See the owner audio record. |
| 2 | Fresh patched HnS active movement met 601.2 conservative seconds with FPS snapshots 33.6–60.4. FireRed met 600.9 measured active seconds with timed FPS snapshots 50.8–60.6; an earlier menu showed 44.6. Both remained responsive without visible hangs. | Retain the observed variation and unknown cause. Do not claim constant full speed or change unrelated host processes/settings to improve a test result. |
| 2 | Patches can change diagnostic line literals and CheckTogepi code size, yielding a different HnS ROM. | Never transfer pristine native passes to patched artifacts. Execute separate fresh patched HnS regression and repeat clean builds. |
| 2 | Generator filters game_version, and map generation rewrites tracked heal-location data. | Use fresh isolated target trees; preserve generated diffs separately from reviewed patches. Never switch targets in an existing tree. |
| 2 | Default upstream debug menus enabled; mGBA state autoload initially enabled. | Record actual settings, disable state autoload and avoid debug commands/states/grants. Acceptance requires ordinary gameplay and normal game saves. |
| 2 | Source lacks a repository-wide license; credit-policy TODOs and conflicting gbafix notices remain. | Keep all upstream material, outputs and private evidence ignored. Resolve applicable rights/credits before publication. |
| 2 | Tool qualification limits: GNU Make self-tests have Apple-ar timestamp failures; pkgconf full suite lacks optional kyua. ARM smoke/libpng/zlib checks executed. | Preserve caveats and investigate if a corresponding build symptom appears. No global tool changes. |
| 2 | Linker headroom measures static allocation, not runtime peaks or combined-region capacity. | Report exact successful target measurements; do not infer Johto merging or multiplayer feasibility. |
| 3 | Full campaigns, cross-build migration, browser behavior, regional coexistence and 25-player capacity remain unqualified. Windows/WSL reproduction is NOT RUN. | Later milestones and any system installation need explicit approval. B0 smoke success does not qualify them. |

## Decisions and boundaries

- Keep a small independent control repository; all upstream checkouts, tools, outputs, saves and private evidence stay under ignored `_local/`. No control remote, staging or commits.
- Preserve pristine source, baseline failures and pristine HnS clean/native results separately from experimental results.
- Owner target-separation authorization is recorded in `docs/decisions/2026-10-08-b0-firered-repair.md`; the later bounded FireRed save exception is recorded in `docs/decisions/2026-10-08-b0-save-layout-exception.md`.
- The save exception supersedes only the specified original B0 layout prohibition. It does not establish a production format, choose the engine or authorize B1/Johto merging.
- Remaining target boundaries preserve common gameplay and actual regional data; no fake constants, placeholder returns or error suppression.
- Stop at the save-foundation qualification review before Johto progression; historical B0 limits remain preserved. No Workstream A/Discord implementation, NAS/network/global-tool change, hosted automation/workflow, deployment or remote write.


## October13 playable prototype priority

The owner directed faster progress and less repeated testing. The frozen0019/final05 foundation is GO for bounded development with cable/browser checks deferred, approximately9.63-second observed full saves, the four-byte main-block margin, roamer fidelity and separate special-sector atomicity still open. The [first playable Johto quest](b3-johto-prototype-requirements.md) is active; content2 adds specific meanings within the same physical save layout. Its old-ROM downgrade incompatibility and untested full campaign remain explicit. No A/C, remote, NAS/network or publication boundary changes.