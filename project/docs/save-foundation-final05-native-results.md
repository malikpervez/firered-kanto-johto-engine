# Save foundation final05 native results

October 13, 2026. These are bounded, executed desktop checks of patch `0019-firered-save-caller-completion.patch`, following the approved FireRed-only save foundation and conversion of three owned B2 test fixtures. They do not authorize Johto progression or a player release. Earlier fresh opening evidence remains tied to [final04](save-foundation-fresh-native-results.md); it is not relabelled as a final05 opening test.

## Exact candidate and environment

Pinned upstream commit: `167aa6d537b109bb229c231ddce4616974c4da71`. Patch SHA-256: `b398435b7ca39164a0bcc935579fcccb3fd465db1d4d28418b418fc6be612b46`.

| Target | ROM SHA-256 | Build manifest SHA-256 |
| --- | --- | --- |
| FireRed | `97eb56f51e542eea6a324d59c0c33d4e3b6b91858714174c23ce2db490004f76` | `d390054ca75497a773b51e4a9a49f708d452ccd0e1d828468edfc2b0f971800a` |
| HnS | `0cfac50a9db64c0a0a5cc87fbc667b16d9bfd42446fe14a1cf86badfa6608959` | `3057926fda0570c1737bfb33d0b875aa2966dce876800e875304b7a097859269` |

The [FireRed manifest](../_local/artifacts/save-foundation-05-firered/manifest.json) and [HnS manifest](../_local/artifacts/save-foundation-05-hns/manifest.json) preserve actual target selections, toolchain, complete patch, configuration fingerprints, logs, artifacts, and real build/wrapper exit codes of zero. Compilation is reported separately from the native checks below.

The official, locally pinned desktop mGBA **0.10.5** app was selected by its exact local path. All game actions used ordinary keyboard inputs through the desktop UI. Normal game Save and Continue were used. No emulator states, cheats, game memory edits, debug gifts, forced script calls, or save edits were used during these checks. Owner mute preference was retained; no new listening test is claimed. Each cold cycle used full application quit followed by an executed process-absence check before relaunch.

Before opening each additional fixture, exact ROM, manifest, original fixture, and allocated writable save bytes were verified. Separate immutable copies were created in their ignored local test folders. [Input bindings](../_local/evidence/save-foundation-resume-01/final05-native/direct-load-hns-input-binding.json), [chronological observations](../_local/evidence/save-foundation-resume-01/final05-native/direct-load-hns-gui-events.jsonl), and [closeout hashes](../_local/evidence/save-foundation-resume-01/final05-native/direct-load-hns-closeout.json) preserve this association. The session metadata's initial `NOT RUN` records are retained; these dated execution records provide the subsequent results.

## Executed FireRed checks

| Case | Executed result | Scope |
| --- | --- | --- |
| Converted returned-Kanto fixture, cycle 1 | **PASS — EXECUTED.** Normal Save at Pallet guide `(10,13)`, full quit, process absence, cold Continue `RED`, time `0:26`, zero badges, Pallet field and responsive Start menu; male Bulbasaur level 6, HP `21/21`, five empty party slots. | First normal full-save/cold-reload cycle on final05. |
| Same fixture, cycle 2 | **PASS — EXECUTED.** Ordinary development-travel prompt to New Bark, normal Save at `(5,23)`, full quit, process absence, cold Continue `RED`, time `0:27`, zero badges; New Bark guide field and responsive Start menu. | Second normal full-save/cold-reload cycle on final05. |
| Converted Kanto-before-travel fixture | **PASS — EXECUTED.** FireRed Charizard title; native Continue `RED`, time `0:13`, zero badges; Pallet guide field and Bulbasaur follower; party male Bulbasaur level 6, HP `21/21`, five empty slots. Full quit and process absence. | Direct native load only. No new normal Save or gameplay progression was executed in this case. |
| Converted Johto-cycle-01 fixture | **PASS — EXECUTED.** FireRed title; native Continue `RED`, time `0:15`, zero badges; New Bark guide outside House 1 and Bulbasaur follower; same visible party values. Full quit and process absence. | Direct native load only. No new normal Save or gameplay progression was executed in this case. |

The two full cycles were executed by the primary GUI operator and are preserved in the [two-cycle GUI record](../_local/evidence/save-foundation-resume-01/final05-native/returned-kanto-two-cycle-gui-record.json). The transient saved-success message was not captured; `SAVING` followed by field return, strict complete-bank inspection, and actual cold Continue establish the tested durability. Neither direct-load case is promoted to an additional save-cycle pass.

The [cycle 1 inspection](../_local/evidence/save-foundation-resume-01/final05-native/returned-kanto-cycle01-inspection.json) and [comparison](../_local/evidence/save-foundation-resume-01/final05-native/returned-kanto-cycle01-comparison.json) show two coherent valid FRJS1 banks and selected counter 4. Player/rival names, full trainer ID, full party bytes/count, flags, variables, Dex seen/caught state, roamer, position/location/layout, decoded money/coins/inventory, and PC storage match the converted baseline. Johto records remain blank and reserved bytes zero.

The [cycle 2 inspection](../_local/evidence/save-foundation-resume-01/final05-native/returned-kanto-cycle02-inspection.json) and [comparison](../_local/evidence/save-foundation-resume-01/final05-native/returned-kanto-cycle02-comparison.json) show counter 5 and two coherent valid banks. All of the protected state above remains equal, with the expected ordinary travel change to New Bark position `(5,23)` and location. Decoded money is 3,080, coins zero, and Potion quantity one. Visible trainer ID is 25,928. Strict inspections use the actual final05 ARM [field map](../_local/evidence/save-foundation-resume-01/arm-layout-final05-2026-10-13/native-field-map.json), SHA-256 `04c5df4bbe1d3bf7443ee6eca11fd342e0b2193c9f386214003ccf1ade41881e`.

The two direct-load session saves remain byte-identical to their immutable converted baselines after full quit. These checks supplement the earlier offline conversion/roundtrip evidence; they do not establish compatibility for unrelated saves or older ROMs.

## Executed independent HnS regression

An isolated writable copy of the immutable HnS `repair-09-native-01/cycle-02.sav` fixture was used. The original SHA-256 remains `a3a590c19b4215fc4f98cb23e7e808d0995a5b50fc68e16c43285417f2354822`.

| Check | Executed result |
| --- | --- |
| Title and native load | **PASS — EXECUTED.** Heart & Soul lighthouse title; Continue `CODEX`, time `2:01`, Pokédex two, zero badges; existing Route 29 field with follower. |
| Party and inventory | **PASS — EXECUTED.** Male Cyndaquil level 7, HP `23/23`; female Rattata level 3, HP `15/15`; four empty slots. Items pocket empty, Medicine Potion one, Poké Balls four. The first HP transcription read the pixel glyph as 28; the chronological correction, screenshots, and equal party bytes confirm 23. |
| Ordinary encounter and field behavior | **PASS — EXECUTED within this narrow case.** Walking triggered male Rattata level 2 and male Pidgey level 2 wild encounters. Both standard battle menus loaded and normal Run succeeded, with the party's HP retained. No attack, catch, or new campaign battle victory is claimed. Route 29 to New Bark Town connection was crossed through ordinary walking; the Save box identified New Bark Town. |
| Normal Save | **PASS — EXECUTED.** Normal Save confirmation; `SAVING`/power warning observed, followed by return to New Bark field. Save prompt time `2:06`; actual persisted Continue time `2:07` reflects elapsed game time. |
| Full quit and cold Continue | **PASS — EXECUTED.** Actual process absence, fresh app launch and native Continue `CODEX`, time `2:07`, Pokédex two, zero badges; New Bark field at the saved position; party remains Cyndaquil `23/23` and Rattata `15/15` with the same levels, genders and empty slots. |

The [before inspection](../_local/evidence/save-foundation-resume-01/final05-native/hns-before-native-inspection.json) and [after inspection](../_local/evidence/save-foundation-resume-01/final05-native/hns-after-native-inspection.json) executed successfully on immutable backups with final05 manifest/ROM/header/ARM bindings. HnS retains native version 5 and the existing 52-byte SaveBlock3. Both banks are coherent and checksummed; selected counter advances 2 to 3. The original fixture is unchanged.

The [state comparison](../_local/evidence/save-foundation-resume-01/final05-native/hns-native-state-comparison.json) confirms exact full party bytes, party count, player/rival identity (`CODEX`/`PATCH`), full trainer ID, gender, roamer/padding, caught state and PC storage retention. Decoded money remains 3,220 and coins zero. The separate [inventory comparison](../_local/evidence/save-foundation-resume-01/final05-native/hns-bag-semantic-comparison.json) uses an executed actual [ARM Bag/ItemSlot probe](../_local/evidence/save-foundation-resume-01/final05-native/hns-bag-arm-probe.json): four-byte slots, two-byte quantities, actual pocket offsets. Each save's quantities are decoded with its own encryption key. All pockets remain semantically equal, including the two key items, four Balls and one Potion.

Flags and all variables are **not** byte-identical in HnS. The complete differences are preserved and source-correlated in [natural field mutations](../_local/evidence/save-foundation-resume-01/final05-native/hns-natural-field-mutations.json). The five-day clock advance updates daily RNG/lottery, day, Birch and Frontier daily counters; ordinary walking updates friendship/poison counters; current daytime switches the day/night hiding flags and HnS encounter variable; the daily wild counter resets then reaches two for the actual encounters. Dex seen gains Pidgey national ID 16, while caught state is unchanged. These explanations are inferences from the exact changed bytes, actual actions and source writers, rather than a trace of every writer. HnS's story variables for New Bark/lab and badges did not change. No claim of all-variable preservation is made.

The active HnS save remains exactly equal to its post-save immutable checkpoint after cold verification. Two ordinary emulator menu screenshots preserve party observations before and after; they are private and ignored.

## Exact local outputs

All paths below are relative to `[LOCAL_WORKSPACE]/` and remain ignored.

| Output | Local path | Save SHA-256 |
| --- | --- | --- |
| FireRed cycle 1 | `_local/saves/firered/save-foundation-05-returned-kanto/normal-cycle-01.sav` | `aa19443f3b02d61bbcee62de9c71425b8dd4d6042ce27906b0204b54546902cb` |
| FireRed cycle 2 | `_local/saves/firered/save-foundation-05-returned-kanto/normal-cycle-02-new-bark.sav` | `5a632325cbbff5d42c0c1f6c865cf17ebc181c094ccbffddab7da4d67b44ac76` |
| Converted Kanto direct-load copy | `_local/saves/firered/save-foundation-05-kanto/firered-foundation-05-kanto.sav` | `0829e6fbd5dfe393d0bdade062af4c9ced69c45fda76100ee9f3cb324d450dbc` |
| Converted Johto direct-load copy | `_local/saves/firered/save-foundation-05-johto/firered-foundation-05-johto.sav` | `c129f8e6feeb4aabe8e28d283b72fec19534972d0dfd732a335d4fcab1814385` |
| HnS post-save checkpoint | `_local/saves/hns/save-foundation-05-native/after-normal-save-final05.sav` | `6b155c5c35b34e24a3eb7577704935f45ad2494a0b58161c62366dd710d5e969` |

ROM copies and session bindings are in the same session folders. Final artifacts are `_local/artifacts/save-foundation-05-firered/pokefirered.gba` and `_local/artifacts/save-foundation-05-hns/pokehns.gba`. All native saves above are 131,088 bytes: existing 128 KiB flash image plus mGBA's 16-byte trailer. The [closeout manifest](../_local/evidence/save-foundation-resume-01/final05-native/direct-load-hns-closeout.json) binds every supplemental backup and private screenshot.

## Limits retained for review

These results qualify the stated native load/full-save cases. They do not qualify full campaigns, Johto progression, all species/items, every save caller, real-hardware interrupted power, old-ROM downgrade, a browser adapter, or Workstream A networking. Final04's longer fresh opening and save observer remain separately bound to final04. No extra soak, ten-trip run, audio listening test, Hall of Fame, wireless session, or full native peer trade was executed here.

The [trade prerequisite source audit](../_local/evidence/save-foundation-resume-01/final05-native/native-trade-prerequisite-audit.json) finds an existing upstream same-FR readiness limitation. The partner version's low byte selects the FR/LG branch even for two FireRed games; both players must advertise the high progress bit. In the selected FireRed flag table this is `FLAG_IS_CHAMPION` at `0x844`, set after Celio's completed Sevii network link. Ordinary Parcel delivery and a second party member do not satisfy this gate. The two relevant functions are identical to pinned upstream and B2-04. This is an executed source finding, **not an executed native trade failure**. The earlier private trade plan's statement that no postgame was needed is superseded by this audit. No readiness flag or gameplay repair was made.

A source-reachable cable Single Battle can exercise the partial incremental postbattle save after ordinary Dex unlock. The owner deferred this native peer case on October 13 to prioritize progress toward a workable merged game: **NOT RUN — OWNER DEFERRED**. The [peer closeout](save-foundation-native-peer-status.md) preserves one trainer's completed ordinary staging and the second trainer's direct load without claiming a paired test. This route would not cover the full incremental posttrade family. Any later execution needs its own exact evidence.

The four-byte SaveBlock1 headroom and FireRed roamer fidelity defect remain open. This report supplies native evidence for the save-foundation review gate and does not advance regional progression or claim release/save compatibility. Workstream A, NAS, networking, remote repositories and publication were untouched.
