# B0 review gate: HOLD

**Later owner decision — October 9, 2026:** B0's recorded limitations are accepted for further evaluation and B1's audit plus the frozen B-to-C 010 inventory handoff are approved. See [the B1 authorization](decisions/2026-10-09-b1-audit-and-c-handoff.md). This historical B0 recommendation and its evidence are retained; later approval does not qualify a player release or authorize implementation. The earlier “B1 is not approved” statement at the end records the pre-decision boundary and is superseded only by this explicit audit/handoff authorization.

Candidate source: `167aa6d537b109bb229c231ddce4616974c4da71` (`Release-v2.0.6`). Complete experimental 010 SHA-256 `3e9b6b003557cbfacff59706ad04e4f7f2fdd58bc6162be995f91dc09742d5f3`; patch/config fingerprint `32faeccdf41db77505858cd2981a070c7f835f0eee3180fe1563cb4c0e343f00`. Native arm64 macOS 27.0, locked local tools, separate target trees.

**Both actual 010 clean builds and clean repeats passed, make/wrapper 0.** FireRed selects its own Kanto/Sevii campaign in the shared Emerald Expansion engine; its fresh Pallet/Oak/Bulbasaur/rival/Parcel opening executed. FR-01–09 passed, including wild battle/capture/healing/menus and both normal-save/full-quit/cold-Continue comparisons. The second cycle retained the legitimate Potion/location change and clerk revisit gave no duplicate Potion. Requested identity, rival name, Pokédex, party, inventory, location and progression checks passed in these fresh early-game sessions. FireRed visual/input testing reached 600.9 conservative active seconds with responsive controls/no visible hang, timed FPS snapshots 50.8–60.6 (earlier menu 44.6 separately recorded). FR-10 audio is PASS — OWNER-REPORTED; see the dated owner confirmation below.

HnS 010 is byte identical 009, whose separate fresh regression passed HNS-01–08, including opening errand/rival/capture and both normal-save/cold-reload cycles. Its visual/input check executed 601.2 conservative active seconds with responsive controls/no visible hang; active FPS snapshots 33.6–60.4. HNS-09 audio is covered by the same owner-reported confirmation in the current evaluation context. Frame-rate causes are unestablished; constant full speed is not claimed.

Preserved FireRed 009 passed the Pallet/CODEX/PATCH opening but failed natural starter selection: the party was empty, confirmed twice. FR-02 FAIL; FR-03–FR-10 BLOCKED, no normal saves. 010 supplies a narrowly reviewed missing existing default: monotype OFF 31 only for FireRed in its existing fresh-default initializer. New Game's incoming-choice snapshot/restore, filtering and gift scripts remain intact. Source diagnosis/compilation do not pass the fresh native retest. Exact 009 failure remains in `docs/firered-native-results.md`.

The owner-approved reservation experiment retains all live fields, sectors, checksums and the capacity assertion. Actual final 010 ARM probes measure FireRed 15,868/15,872 (**4 bytes free**), LeafGreen 15,952 (original 80-byte overflow unchanged), HnS 15,760, Emerald 15,752. Every measured member/size/offset matches 009 and approved 004. LeafGreen/Emerald are macro type-layout diagnostics with actual FireRed generated-map context, not successful game builds. This remains an experiment, not a production format or compatibility promise.

| Gate item | Current executed result |
|---|---|
| Pristine FireRed | FAIL — EXECUTED; unmodified baselines retained |
| Final FireRed/HnS clean builds 010 | PASS — EXECUTED: compilation only; both 0 |
| Approved FireRed capacity/layout checks | PASS — EXECUTED: actual ARM measurement/protection only |
| Other target layouts | Unchanged measured ARM layouts; no LeafGreen build success claimed |
| Final 010 clean repeats | PASS — EXECUTED; per-target artifacts/configuration/source/generated records match, all 0 |
| FireRed 010 native / two normal-save cycles | FR-01–09 PASS — EXECUTED; both cold cycles retained requested fields, changed Potion/location and no duplicate gift. FR-10 visual/input passed; audio PASS — OWNER-REPORTED |
| Exact final HnS native / two normal-save cycles | HNS-01–08 PASS — EXECUTED; both cold cycles retained requested fields, changed Potion/location and no duplicate pickup. HNS-09 visual/input duration executed; audio PASS — OWNER-REPORTED |
| Audio | PASS — OWNER-REPORTED, October 9, 2026; general confirmation applied to the current evaluation context, with no separate target/scene details supplied |
| Full campaigns, natural Sevii access/fidelity, combined regions, old/cross-build saves | NOT RUN / unqualified |
| Publication/boundary audit | Preliminary PASS — EXECUTED, 762/762 checks, real exit 0; both final active saves exactly match cycle 2. Frozen final inventory result is recorded separately below. |

Preliminary evidence: `_local/evidence/repair-analysis/final-audit-preparation/preliminary-02.json`, SHA-256 `7070ea1de9494acc7388f73dd9b52b2a6559be2cdfef980572fde901e8d2bf5e`. It independently checked 37 control and 443 private records, native input stability and targeted mGBA process absence. The first attempt remains preserved: its sole failure was a historical report heading changed by Codex; that report was restored exactly from its preserved original, with both heading versions retained. No gameplay result changed.

The frozen final boundary inventory and executed result are recorded in [the final audit](../_local/evidence/b0-save-experiment-final-boundary-audit.json). That audit records the completed pre-audio-confirmation snapshot. Later owner-audio documentation is recorded separately; preserved pre-update reports are under `_local/evidence/reports/pre-owner-audio-confirmation/`. Its frozen inventory does not cover these later documentation updates. The scoped audit does not certify full campaigns, audio, save compatibility or unrelated services.

**Owner update — October 9, 2026:** Audio is **PASS — OWNER-REPORTED** for the current B0 evaluation. See the [owner audio confirmation](decisions/2026-10-09-b0-owner-audio.md) for attribution and scope. This later confirmation supersedes earlier audio-pending statements below; Codex did not perform a new listening test. The prior frozen audit and native reports remain historical evidence. B0 remains HOLD for review of the four-byte save margin and FireRed roamer fidelity defect.

## Exact local outputs and evidence

- FireRed ROM: `[LOCAL_WORKSPACE]/_local/artifacts/repair-10-firered/pokefirered.gba`, 32 MiB, SHA-256 `3e504731d9dd3c02ec273dc257c86f557caaf8c9b933d2f0ff73558c2e121a39`. ELF/map/manifest alongside; manifest SHA-256 `fbf75c3a47c21c88ad6633b0f6a176b131b797897ff8bdd19f4161966f0f671e`. Actual header `POKEMON FIRE`/`BPRE`, 417 selected FRLG maps and zero HnS maps. The shared Emerald Expansion engine is not a retail/pret FireRed byte match.
- HnS ROM: `[LOCAL_WORKSPACE]/_local/artifacts/repair-10-hns/pokehns.gba`, 32 MiB, SHA-256 `4bb58fe3c06bc0b60146aa946cbc34f087efa607f525f68e0a1e99c0db9cde75`. ELF/map/manifest alongside; manifest SHA-256 `21ea87bf5c2343bf6a8e14815cea30a3ecb1500ac345d2ea1281045b88054edc`. 560 selected HnS maps.
- Both complete build stdout/stderr/configuration/commands/real exits/applied/generated diffs: matching 010 runs under `[LOCAL_WORKSPACE]/_local/evidence/builds/`.
- Actual 009→010 HnS comparison: `_local/evidence/repair-analysis/repair10-build-comparison/hns009-to010.json`, zero differing ROM bytes; ELF/map also identical. This associates exact-ROM evidence and does not claim an extra GUI run. The fresh native session stays bound to its 09 manifest.
- Final 010 field map: `_local/evidence/native/repair-10-compiled-fields/native-field-map.json`, actual successful target headers/no fallback. Full ABI: `_local/evidence/native/repair-10-full-abi/actual-final-abi-comparison.json`.
- Native sessions: HnS `_local/saves/hns/repair-09-native-01/` (completed; audio owner-confirmed); FireRed `_local/saves/firered/repair-10-native-01/` (completed; audio owner-confirmed). Each uses only a fresh private save; no personal/old progress is imported.
- Reports: `docs/build-report.md`, `docs/test-results.md`, `docs/firered-repaired-native-results.md`, `docs/hns-patched-native-results.md`, `docs/firered-save-experiment.md`, `docs/risks.md`, `docs/native-test-procedure.md`. README/manual wrapper and lock files reproduce the exact source/tools/configuration. Historical pristine HnS results remain in `docs/hns-native-results.md`.

## Review boundaries and open defects

Recommendation: **HOLD** for owner review of the four-byte save limitation/roamer fidelity defect. Audio is now owner-confirmed. Both early-game native runs are complete and mGBA is fully quit. This evaluation does not select a production engine. Review the reports before authorizing any later milestone.

The bounded save exception is already owner-approved and used: three unused FireRed roamer reservation slots reclaim 84 bytes. No live field, sector/checksum code or protective assertion was removed. Compiled-caller review found the unused Mauville TM block has no selected FireRed caller; its FireRed-only boundary preserves other targets/shared TM policy. Remaining HnS linker guards were reviewed individually. 010 adds only the existing default value, without a new UI/policy/flag/field/save migration/capacity change, starter bypass or feature removal.

Keep **four-byte save headroom** and **FireRed roamer fidelity** open. The selected One Island/non-HnS source uses Hoenn routes and Latias/Latios rather than the starter-dependent beast. Postgame and full campaigns are not certified. The owner reported audio is all good on October 9, 2026; the scope is recorded in the owner confirmation. Stop for owner review if another blocker requires broader restructuring, feature removal or another capacity change.

**B1 is not approved.** No engine selection, Johto merge, production save format, multiplayer/Discord, Workstream A/NAS/network/global installation, workflow/hosted automation, deployment or remote write. No staging/commits; control repository has no remote. Upstream trees/tools/ROMs/saves/private evidence remain ignored under `_local/`.
