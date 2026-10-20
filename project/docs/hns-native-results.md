# HnS native B0 results — Codex

The pinned pristine HnS ROM completed the natural Johto opening, early battles/capture/healing, menus, and **two normal save/full-quit/cold-Continue cycles**. HNS-01 through HNS-08 are **PASS — EXECUTED**. HNS-09's active-play, visual and input components passed; its audible component remains **NEEDS OWNER TEST** because CUA returns images, not sound. This report does not pass FireRed or authorize the next milestone; see `docs/b0-gate.md`.

Run: `codex-01-hns`, October 8, 2026, tester **Codex through desktop CUA controls**, approximately 16:14–17:46 America/New_York (20:14–21:46 UTC). Host: macOS 27.0 build 26A428, arm64. Source: [PokemonHnS-Development/pokehns-expansion at 167aa6d537b109bb229c231ddce4616974c4da71](https://github.com/PokemonHnS-Development/pokehns-expansion/tree/167aa6d537b109bb229c231ddce4616974c4da71). Build: unmodified `baseline-01`, target `hns`, GNU Make 4.4.1 / ARM GNU Toolchain 14.2.Rel1 (GCC 14.2.1), exact configuration manifest below. Configuration-file fingerprint: `f0e57724c34228154aa68dd82e12c36e4ea8a5f6d000046ca1883fd6ed622d06`. No local gameplay patch.

| Identity | Exact local path / hash |
| --- | --- |
| Build manifest | `[LOCAL_WORKSPACE]/_local/artifacts/baseline-01-hns/manifest.json` |
| Tested session ROM | `[LOCAL_WORKSPACE]/_local/saves/hns/codex-01/hns-codex-01.gba` |
| ROM SHA-256 | `7ffd0c7572f0542f60381ec776d99f4e826ae2859d56403e56bcc82effcd88df` |
| Session identity | `[LOCAL_WORKSPACE]/_local/saves/hns/codex-01/session.json` |
| Native save | `[LOCAL_WORKSPACE]/_local/saves/hns/codex-01/hns-codex-01.sav` |
| Private written observations | `[LOCAL_WORKSPACE]/_local/evidence/native/codex-01-hns/observations.md` |
| Desktop emulator | `[LOCAL_WORKSPACE]/_local/tools/mGBA.app` — official mGBA 0.10.5 |

The session began fresh with no imported saves. Before play Codex disabled Load last state and Load cheats; periodic state autosave was off. Native saves were configured alongside the session ROM and verified there. Normal speed, target 59.7275 FPS, frameskip 0, OpenGL, audio synchronization on/video synchronization off, SDL audio 44100 Hz/buffer 1536/mute off; no external BIOS. No emulator save states, cheats, debug grants, flag editing, warps or R+Start/Select debug shortcuts were used.

Campaign setup used Recommended: Gen7 movepool, physical/special split/Fairy and reusable TMs on; actual **RTC**, randomizers/Nuzlocke/additional challenges off, EXP 1.0, items and Centers allowed. No host clock change. These are this candidate's defaults, not certification of vanilla Gen2 mechanics.

| ID | Result | Executed observation |
| --- | --- | --- |
| HNS-01 | PASS — EXECUTED | Cold boot displayed Expansion/HnS v2.0.6 and the Heart & Soul title. Created male CODEX; New Bark bedroom/wall-clock/Mom PokéGear and shoes scenes completed; entered the controllable town. |
| HNS-02 | PASS — EXECUTED | Accepted Elm's request and naturally selected middle-ball Cyndaquil♂ Lv5, Adamant/Blaze, HP19/19, Tackle35/35 and Leer30/30. Declined nickname; spoke Elm again for phone/task; aide granted Potion on exit. |
| HNS-03 | PASS — EXECUTED | Route29 → Cherrygrove Guide Gent tour → eastern Route30 → Mr Pokémon Mystery Egg/Oak Pokédex → Elm emergency call on house exit. Silver intercepted Cherrygrove east exit naturally. Defeated Totodile♀ Lv5 with five ordinary Tackles; starter grew to Lv7 and field control returned. Returned to lab, police/default SILVER naming and automatic egg handover; main exit aide granted five balls; Mom farewell completed. |
| HNS-04 | PASS — EXECUTED | Traversed New Bark/Route29/Cherrygrove/Route30 boundaries and ordinary ledges; entered/exited home, lab, route house, Center, Mart and Mr Pokémon house; talked to ordinary route NPCs and completed Guide Gent's movements. No observed invalid warp, collision, rendering error or script lockup. |
| HNS-05 | PASS — EXECUTED | Ordinary wins against Hoppip Lv3, Hoothoot Lv2 and Pidgey Lv3, plus ordinary Run from other encounters. After legitimate balls, caught Pidgey♀ Lv2 at full HP on the first ball. Dex registration/nickname decline returned to field. Cherrygrove Center and Elm healing machine exercised; final party HP23/23 and 14/14. |
| HNS-06 | PASS — EXECUTED | Opened/closed Bag, party/summaries, Johto Dex (seen8/owned2), PokéGear map/cursor and Call list (Elm/Mom), trainer card, and Start clock. RTC selected; setup about 4:13 PM, world 4:19 PM, pre-save1 up to 5:04 PM/post-reload1 5:07 PM, pre-save2 5:37 PM/post-reload2 5:40 PM. No crash. Broader RTC event regression not tested. |
| HNS-07 | PASS — EXECUTED | Normal save1, full application quit, process absence, native backup/hash, empty emulator relaunch/cold title and game's Continue. All recorded values and indoor lab location retained; Elm/aide/exit revisits gave routine dialogue and no repeated starter/police/Potion/balls scene. |
| HNS-08 | PASS — EXECUTED | Continued, legitimately gave the existing Potion to Pidgey and moved outdoors. Normal save2 explicitly displayed “CODEX saved the game”; full quit/backup/cold Continue retained changed location and held Potion, party/identity/inventory/money. Revisited lab/Elm/aide/exit; no repeated opening sequence or rewards, balls4 and medicine empty afterward. |
| HNS-09 | NEEDS OWNER TEST — audible component | **PASS — EXECUTED** for ≥10 minutes active play, visual/input/speed observations. Separately logged 607.4 seconds of completed ordinary held field controls alone; no observed hang, input loss or visual corruption. Codex did not hear audio. |

Native save comparisons (stat order: Attack / Defense / Special Attack / Special Defense / Speed):

| Visible field | Cycle1 before/after cold Continue | Cycle2 before/after cold Continue |
| --- | --- | --- |
| Trainer/progression | CODEX male, ID47542, money 3300 / mom savings 0, owned2, badges0; saved Continue time0:53 | Same identity/money/progression; saved Continue time1:23 |
| Location | New Bark lab, immediately south of healing machine, facing north | Outdoors New Bark, south of player's house/west of pond, facing right with Cyndaquil follower; same tile/landmarks restored |
| Cyndaquil | ♂Lv7 Adamant/Blaze, metLv5 NewBark, HP23/23, no item/status, Tackle35/35 Leer30/30; EXP272 and stats14/13/12/13/16 retained | Same recorded values retained |
| Pidgey | ♀Lv2 Careful/Keen Eye, metLv2 Route29, HP14/14, no item/status, Tackle35/35 Peck35/35; EXP9 and stats7/6/5/6/7 retained | Same values with legitimately held **Potion** retained |
| Inventory/events | Potion1, PokéBalls4; Exp.Share/GBPlayer only, Mystery Egg removed; egg/Oak/Silver/police/aide/Mom progression completed and no replay in lab revisits | Medicine empty, PokéBalls4, key items unchanged/egg absent; lab revisits and exit no replay, quantities still correct |

Both native files were **131088 bytes**. No save parser or binary modification was used. Backups were copied after full quit, preserving the active save:

| Backup | SHA-256 |
| --- | --- |
| `[LOCAL_WORKSPACE]/_local/saves/hns/codex-01/cycle-01.sav` | `4ddaba43ddfd28974ef656a161a2cf61f722c645db07af0f1ed85bc28929fd3a` |
| `[LOCAL_WORKSPACE]/_local/saves/hns/codex-01/cycle-02.sav` | `8d76f40285b8df1c33a3167413525f6630e1563fdd64f84945b53e088b72e2d9` |

Each Cmd+Q was followed by read-only process inspection (`pgrep -fl mGBA`, exit1/no output), then cold empty-window relaunch. Immediate CUA app inventories retained stale running status; they were not used as proof of process termination. The final B0 emulator was fully quit after the second comparison with **no third normal save**; active save still matches cycle2, cycle1 unchanged. Owner Continue therefore opens the cycle2 outdoor position. Independent read-only backup checks are preserved as `cycle-01-independent-hash.json` and `cycle-02-independent-hash.json` in the private evidence directory; they verify bytes/hashes, not gameplay.

Active-play accounting excludes wall-clock idle, menus, setup, tool overhead, repositioning and source reads. The final private block log records 4.2s initial movement +2×33.6s +3×32s +9×48s +8s = **607.4s** completed held Left/Right field movement on a runtime-observed clear New Bark row. End screenshots returned in CUA show normal field control; these images are in the tool transcript, **not saved screenshot files**. Earlier natural route/battle/dialogue play adds coverage but is not the timing proof. FPS observations were generally 59–60.5, timed blocks 59.5–60.4, with brief lower transition readings; this is a desktop smoke observation, not a performance benchmark.

No runtime defect was detected in the executed opening/save sequence. Observed differences requiring future fidelity review: expansion campaign options/Gen7 moves, Pokenav-style PokéGear, initial Exp.Share/GBPlayer key items, Pidgey Lv2 with Peck and a visible Fly action without a listed Fly move (action not invoked), Cyndaquil still Tackle/Leer at Lv7. Keyboard batches sometimes required a released frame or an additional press after a fade; no reproducible engine input defect was established.

Audio remains unresolved; use the exact named-human steps in `docs/native-test-procedure.md`. This test does not cover gyms, later Johto, Sevii, all RTC/day-night events, long shutdown clock behavior, cross-build saves or a merged world. Stop at the B0 review gate.
