# Save foundation — fresh FireRed native results

**October 13, 2026, America/New_York. Candidate 04's bounded fresh native acceptance passed as executed.** This report covers the exact ROM below, from a natural New Game through the first normal save and one normal save/full-process-exit/cold-Continue cycle in each B2 region. Later candidate changes, converted-fixture GUI tests, HnS regression and the package review decision are reported separately. No Johto progression was added or exercised.

Tester: Codex through desktop mGBA **0.10.5** on the recorded native Mac. The run was approximately **14:20–14:56 EDT**. All game actions used the ordinary emulator/game UI. No cheat, save state, debug grant, save editor or game-memory/register write was used. A bounded Lua observer read memory/registers and wrote private observation text only; its limited measurements are distinguished below.

## Exact candidate and isolated session

| Binding | Value |
|---|---|
| Pinned upstream | `167aa6d537b109bb229c231ddce4616974c4da71` |
| Complete patch | [0018](../patches/0018-firered-save-foundation.patch), SHA-256 `77869031e9fafb2c4aa9787549a8a956be11c4032136a23b7a4dcc39d9764592` |
| Clean FireRed ROM | [_local/artifacts/save-foundation-04-firered/pokefirered.gba](../_local/artifacts/save-foundation-04-firered/pokefirered.gba), SHA-256 `87cbe649615e1aa71a75b604b78c2db2e0ca0fd621371f9df96e8a4ff7c296f9` |
| Build/configuration manifest | [manifest.json](../_local/artifacts/save-foundation-04-firered/manifest.json), SHA-256 `8c71198bf05ca799bb328379a82a5d30502cbd8bbd653ed79acd3ebfb10d5ae0` |
| Actual session ROM | [_local/saves/firered/save-foundation-native-03-fresh/firered-save-foundation-fresh.gba](../_local/saves/firered/save-foundation-native-03-fresh/firered-save-foundation-fresh.gba), byte-identical to clean 04 |
| Session binding and chronological GUI observations | [session.json](../_local/evidence/native/save-foundation-03-fresh/session.json), [gui-events.jsonl](../_local/evidence/native/save-foundation-03-fresh/gui-events.jsonl) |

The session label `03` is an existing folder label; its ROM is explicitly bound to **clean candidate 04**. It initially contained only the ROM, with no save or state. mGBA created its erased flash file at boot, then the game produced the normal saves below. Native save, screenshot and ROM paths stay inside this ignored local session folder:

`[LOCAL_WORKSPACE]/_local/saves/firered/save-foundation-native-03-fresh/`

Read-only configuration observation confirmed Load Last State off, Load Cheats off, periodic save states off, rewind off, native FPS target `59.72750056960583`, same-folder game saves, no supplied external GBA BIOS, Discord presence off and the owner's **mute=1** preference retained. The fresh trainer's ordinary text-speed option was moved from FAST to FASTER for the bounded test. Audio was not re-listened to.

## Executed gameplay and persistence

| Check | Observed result | Status |
|---|---|---|
| Natural original FireRed opening | Charizard/FireRed title; New Game and Options only; original controls/Oak/Nidoran introduction; male trainer named RED and rival named BLUE through the in-game keyboards | **PASS — EXECUTED** |
| Original opening maps | Bedroom/NES interaction; staircase to first floor; front door to Pallet; natural north-path grass warning and Oak's scripted escort to the original lab | **PASS — EXECUTED** |
| Starter selection | Bulbasaur preview/selection; “RED received the BULBASAUR from PROF. OAK”; BLUE received Charmander | **PASS — EXECUTED** |
| Original rival battle | Natural lab-exit challenge; male Bulbasaur level 5, 20/20 HP against female Charmander level 5; normal Tackle/Growl/Scratch turns; RED won and Bulbasaur reached level 6 | **PASS — EXECUTED** |
| Meaningful inventory baseline | Normal Route 1 clerk conversation granted a Potion; Medicine pocket showed Potion ×1; returned to Pallet naturally | **PASS — EXECUTED** |
| First normal full save | At Pallet (10,13): Save → Yes → SAVING → field; full mGBA quit; exact process absence; immutable backup; fresh process/Continue restored the same Pallet guide position | **PASS — EXECUTED** |
| New Bark cycle 01 | Development guide → Yes; real New Bark arrival (5,23), return guide visible; normal Save → Yes → overwrite own isolated file → SAVING → field; full quit/process absence; fresh process/cold Continue restored New Bark (5,23) | **PASS — EXECUTED** |
| Returned Kanto cycle 02 | After New Bark cold reload, return guide → Yes restored Pallet (10,13); normal Save/Yes/overwrite/SAVING/field; full quit/process absence; fresh process/Continue restored Pallet (10,13) | **PASS — EXECUTED** |
| Visible collection after both regional cold reloads | One male Bulbasaur level 6, **22/22 HP**, five empty party slots; Medicine Potion ×1; trainer RED, visible ID **40767**, money **3,080**, eight empty Kanto badge slots | **PASS — EXECUTED** |
| Rival, Dex and protected story data | Read-only inspection/comparison of the actual normal checkpoints retained BLUE, Dex seen `[1,4]`/caught `[1]`, complete saved party bytes, every native story flag, all native variables, roamer bytes and PC storage; decoded inventory/money/coins equal | **PASS — EXECUTED — checkpoint inspection** |

The Continue screens showed RED, badges `00` and saved play times `0:14`, `0:17` and `0:20`. Ongoing trainer-card time after Continue naturally advanced. The party's HP maximum differs from the older B2 trainer because this was a new naturally generated character; it stayed 22/22 throughout this test's save checkpoints/reloads.

One incidental Select/Backspace input reordered Tackle/Growl through the normal battle move menu before the first save. Subsequent attacks used Tackle. The complete saved party bytes, including this naturally produced move order, remain identical across the three checkpoints. This was an ordinary game UI action, not a save or memory edit.

Each full quit was independently checked with the exact mGBA process absent before relaunch. CUA's app inventory sometimes still reported a cached running entry; that stale entry was not used as proof of a cold exit. No process was terminated externally. After final verification, mGBA was fully quit again and handed back to the parent task.

## Immutable native checkpoints and read-only comparisons

All three backups are **131,088 bytes** and mode `0444`. The active writable session save remained separate and matched cycle 02 after the last cold-load-only verification. No later save was performed.

| Native checkpoint | SHA-256 | Selected bank / generation |
|---|---|---|
| [kanto-first-normal-save.sav](../_local/saves/firered/save-foundation-native-03-fresh/kanto-first-normal-save.sav) | `624a5d0d3c357b57135acdd79a0cda18053e4825d12d9af426eea9957aaae0c6` | 1 / 1; alternate erased |
| [johto-normal-cycle-01.sav](../_local/saves/firered/save-foundation-native-03-fresh/johto-normal-cycle-01.sav) | `4912a6b1136d0d5c043e8c63771d4417dfbbec959fad8bc5ef5cadaad1ef452b` | 0 / 2; both banks valid |
| [kanto-normal-cycle-02.sav](../_local/saves/firered/save-foundation-native-03-fresh/kanto-normal-cycle-02.sav) | `81914d7c77cb356b6a6bf7052e55346d75f09410c15c860806c5bc8b8fc9e5af` | 1 / 3; both banks valid |

The [actual ARM field map](../_local/evidence/save-foundation-01/arm-layout-resume-2026-10-13/native-field-map.json), SHA-256 `83da3126a9a1a748954aaa6932a255c684bf8aae99aa3a0e9fd6a86b855abd07`, binds the stored-field reads. [First save inspection](../_local/evidence/save-foundation-resume-01/native-inspection/fresh-kanto-first-normal-save.json), [Johto inspection](../_local/evidence/save-foundation-resume-01/native-inspection/fresh-johto-normal-cycle-01.json), [returned Kanto inspection](../_local/evidence/save-foundation-resume-01/native-inspection/fresh-kanto-normal-cycle-02.json) and their [Kanto-to-Johto](../_local/evidence/save-foundation-resume-01/native-inspection/fresh-kanto-to-johto-state-comparison.json)/[Kanto-return](../_local/evidence/save-foundation-resume-01/native-inspection/fresh-kanto-return-state-comparison.json) comparisons cover the actual checkpoint hashes above.

All selected banks validate through the format codec's bounded sector identity/rotation/generation, original payload checksums, version/FRJS header, complete extension CRC and canonical main digest checks. Every new Johto container, travel slot and stored reserve remains blank. The stored Pokémon image is compared in full; this is exact stored-byte retention alongside visible party checks, not an independent creature-decryption audit. Money **3,080**, coins **0** and the lone Potion slot are decoded using the pinned native XOR rule and measured ARM ItemSlot layout; coins were not opened in a game UI.

First-to-Johto and first-to-return comparisons show no changed variable words. Pallet position bytes `0a000d00` return exactly; New Bark position bytes are `05001700`. The native location changes from original Pallet `4400ff00ffffffff` to Johto `0000ff0005001700`, then returned Pallet `4400ff000a000d00`: the existing travel code naturally retains explicit return coordinates. It is not an unexpected identity/progression change. The Pokédex menu remains locked before the Parcel quest, so its raw actual state was checked without claiming a full unlocked-Pokédex UI regression.

Private screenshots beside the ROM are `firered-save-foundation-fresh-0.png` through `-5.png`: pre-save party, saved New Bark field, New Bark-reloaded trainer card, final Pallet-reloaded party, final inventory and final trainer card. Other opening/battle/save observations are shown in the CUA conversation and bound chronologically in the observation log; no nonexistent local screenshot path is claimed.

## Bounded runtime observation

The original [read-only sampler](../_local/evidence/save-foundation-01/arm-layout/readonly-final-runtime-sampler.lua) was retained unchanged. Its ROM assertion passed. An initial attempt closed/reopened the Scripting panel and lost accessible logs; those unobserved results are not used. A subsequent visible New Bark idle run actually displayed 1,800 frame samples with minimum observed SP `03007DDC`, maximum sampled heap allocation 11,648 bytes and minimum sampled free payload 104,224 bytes. [Observed idle record](../_local/evidence/native/save-foundation-03-fresh/observed-idle-sampler.json).

For the final Pallet save, a [separate local observer clone](../_local/evidence/native/save-foundation-03-fresh/readonly-final-runtime-sampler-file-evidence.lua), SHA-256 `cad45407c35dc1d3b442ea68281340216e98df2d751ddf795c3f6ebae308f34b`, appended private text with a flush per line. `io` availability and `fileOutput=true` were actually observed in mGBA before its panel was minimized. Subsequent file entries prove its callback kept running. [Manifest](../_local/evidence/native/save-foundation-03-fresh/runtime-sampler-manifest.json) and [actual retained log](../_local/evidence/native/save-foundation-03-fresh/runtime-frame-observations.log).

| Observed measure | Actual bounded result |
|---|---|
| ROM assertion | SHA-bound candidate 04; CRC32 `50954B26` |
| Logged samples before process quit | Last displayed periodic count **5,100**; callback capped at 14,400 frames, process exited earlier |
| Normal-save busy interval | Frame **15,922 → 16,496**, **574 observed frames**, result **1/OK**; approximately **9.61 seconds** at the native FPS target |
| Observed phase sequence | VALIDATING → FROZEN → BODY → HEADER → COMMITTING → IDLE; short intermediate phases need not appear at a frame boundary |
| Minimum sampled stack pointer | `03007C10` |
| Maximum sampled allocated heap payload | **16,256 bytes** |
| Minimum sampled free heap payload | **99,552 bytes** |
| Last periodic valid heap snapshots | **1,027** |

These are frame samples for this executed path, not instruction-level stack/heap worst-case peaks or exact CPU-cycle timing. The interval excludes user prompt time and is rounded by frame observations. Native cable-link timing was **NOT RUN by this fresh-session test**. The saved-image code and physical flash behavior are not qualified merely by these observations. The measured roughly ten-second save interval is a concrete latency observation requiring review; no unmeasured performance threshold is claimed passed.

## Review boundaries

Candidate 04 passed the bounded natural opening/starter/early battle and normal persistence checks above. This is development evidence, not a player release, full campaign, broad legacy-save compatibility, roamer repair or full day/night qualification. It does not qualify a later ROM by implication. Browser requalification remains owner-deferred. Converted-fixture GUI checks, separate HnS regression, final source/build binding, native-link/resource qualification and the overall save-foundation review decision remain with the parent closeout report.

Workstream A, Workstream C's frozen assets, services, NAS/network and remote repositories were untouched. Source, ROMs, saves and private evidence stay local and ignored. Stop before Johto progression until the named next slice is reviewed and approved.
