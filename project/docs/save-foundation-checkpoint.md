# Save foundation — owner pause checkpoint

**Historical checkpoint: resumed October13 by the owner.** See the [resume decision](decisions/2026-10-13-save-foundation-resume.md); the paused state below is preserved as the October10 record.

**October 10, 2026, America/New_York. Paused at the owner's request: “lets stop for today”.** All agents were interrupted. Both final clean builds had already completed; no build is left running. Desktop mGBA has an empty window with no ROM loaded. Native acceptance has not started. This is a preserved work checkpoint, not an accepted review gate or permission to add Johto progression.

## Completed and preserved

- The approved FireRed-only version-6/FRJS1 foundation is implemented in the complete [0018 patch](../patches/0018-firered-save-foundation.patch), applied alone to upstream `167aa6d537b109bb229c231ddce4616974c4da71`. Patch SHA-256: `77869031e9fafb2c4aa9787549a8a956be11c4032136a23b7a4dcc39d9764592`. [Implementation contract](save-foundation-implementation.md) and [format registry](save-format-registry.md).
- Final separate FireRed and HnS clean builds both returned make/wrapper exit **0**. Logs, effective configuration, source differences and hashes remain in their manifests below. They are compilation passes, not gameplay passes.
- Copies of exactly the three approved B2 fixtures were converted and made read-only; original hashes and bytes remain unchanged. [Conversion and host qualification report](save-foundation-conversion-and-host-tests.md).
- Actual C host checks passed: 170 codec checks; 92 bank probe/load cases; 1,190 coordinator assertions, including 300 simulated flash interruption scenarios; 24 additional cancellation checks. Their overlapping counts are not added into a single total. ASAN/UBSAN diagnostics were empty. These checks do not establish native IRQ timing or physical power-loss behavior.
- ARM layout/scratch evidence is preserved under `_local/evidence/save-foundation-01/arm-layout/`; the coordinator scratch is 5,476 bytes and SaveBlock3 growth is 1,280, within the approved combined 6,784-byte ceiling. FireRed's main block still has only four free bytes. Other target size probes retain their existing sizes. The full field-comparison audit was interrupted before closeout; its interim `all_expected_layout_changes_only` flag is false and requires review on resume. It is not recorded as a full layout pass.
- The frozen C010 handoff verified unchanged: 36,955 local package checks, no failures. [Targeted C notice](save-foundation-c-dependency-notice.md). Workstream A remains untouched. No commit, push, remote write, CI, service or NAS/network change occurred.

## Exact final outputs

| Output | Local path / SHA-256 |
|---|---|
| FireRed ROM | [_local/artifacts/save-foundation-04-firered/pokefirered.gba](../_local/artifacts/save-foundation-04-firered/pokefirered.gba), `87cbe649615e1aa71a75b604b78c2db2e0ca0fd621371f9df96e8a4ff7c296f9` |
| FireRed manifest | [manifest.json](../_local/artifacts/save-foundation-04-firered/manifest.json), `8c71198bf05ca799bb328379a82a5d30502cbd8bbd653ed79acd3ebfb10d5ae0` |
| HnS ROM | [_local/artifacts/save-foundation-04-hns/pokehns.gba](../_local/artifacts/save-foundation-04-hns/pokehns.gba), `9b228a6061a7aee72e80917fc6fa91d4eb72eb7a4c7c57c801c258476554ecb5` |
| HnS manifest | [manifest.json](../_local/artifacts/save-foundation-04-hns/manifest.json), `fa456b404b704760603e08bd93b3d9c64c847a8b18a6b12ea079d343ed3a0f6d` |
| Three immutable converted saves | `_local/saves/firered/save-foundation-converted-01/`; all six original/output hashes are in the conversion report |
| Final host qualification | [_local/evidence/save-foundation-01/c-engine-harness-final/RESULTS.md](../_local/evidence/save-foundation-01/c-engine-harness-final/RESULTS.md) |

The first 0015 build failed on an inline translated-message expression; the corrected static string is in the final patch. Superseded0016/0017 builds were deliberately interrupted, with make `-2` / wrapper `130`, to free capacity for definitive0018 builds. Their patches, manifests and logs remain preserved; interruption is not a new compiler defect. The final0018 clean build has not had a second clean repeat.

## Resume only when the owner asks

1. Complete the bounded native acceptance on the exact final ROM: fresh natural FireRed opening/starter/first save, then two normal Save/full-process-exit/cold-Continue cycles, once in each B2 region. Compare party, inventory, location, progression, rival and Pokédex state.
2. Load the converted B2 character on isolated writable copies, with visible and read-only state comparison. The immutable converted outputs and originals must remain untouched. Prepared writable copies exist in the separate `save-foundation-native-03-*-converted` session folders; their ROM hashes bind to final04 despite the session label03.
3. Run the separate HnS native regression. Complete linked-budget reporting, bounded runtime heap/stack observations and save/link timing qualification. A read-only Lua sampler is prepared, but runtime measurements are **NOT RUN**; installed mGBA lacks the probed range watchpoints/cycle API, so frame samples must not be claimed as rigorous worst-case peaks.
4. Produce the final build/native report and save-foundation review recommendation, update current navigation/status documents, and stop for owner review before any Johto progression.

Native opening, native saves/cold reloads, converted-save GUI loads, final HnS native regression and new runtime measurements are **NOT RUN**. No campaign completeness, release compatibility, roamer repair or general legacy-save conversion is claimed. The four-byte margin, roamer defect, special-sector atomicity and old-ROM downgrade limits remain open. Browser requalification remains owner-deferred. No work or automation is scheduled to resume automatically.
