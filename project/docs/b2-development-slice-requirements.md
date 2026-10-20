# B2 development travel slice requirements

**Approved October 9, 2026; completed October 10 and stopped for owner review.** This is the first visible combined-game milestone: start as the FireRed trainer, visit a tiny Johto area in the same ROM, save there and return to Kanto with the same trainer and collection. It replaced further baseline testing as the approved next work. [B1 results](b1-gate.md), [owner test-stop direction](decisions/2026-10-09-b1-owner-test-stop.md).

Final candidate 014 completed ten bounded round trips, the House1 NPC interaction, and normal save/full-quit/cold-Continue in both New Bark and returned Pallet. The natural opening/starter was executed once on B2 candidate 013; final 014 changes only two added NPC graphics selections, with source/ABI preservation documented rather than a repeated fresh-opening claim. Exact outcomes, saved-state comparisons and limits are in [native results](b2-native-results.md), [build report](b2-build-report.md) and [B2 review gate](b2-gate.md). Existing save format, four-byte headroom and the open roamer defect are unchanged. No independent Johto progression, save implementation or B3 is authorized.

## Approved bounded scope

Build on the frozen tested 010 FireRed candidate. Preserve its natural Pallet/Oak/starter opening, Kanto and Sevii map selection, gameplay fields and existing save layout. Add only `NewBarkTown_hns` and `NewBarkTown_House1_hns`, with the minimum graphics/layout dependencies needed for those two maps. Use a harmless NPC conversation in the house. Audit their actual compiled IDs, collision/warp data and dependencies before adaptation.

Provide clearly labelled **development travel** from Pallet Town to New Bark Town and back. This chooses no production unlock condition, skips no claimed campaign qualification, grants no second starter, resets no trainer/party/Dex/inventory/Kanto progress, and imports no HnS campaign initialization or later-Kanto reset scripts. Keep existing IDs stable wherever required by current saves; document every new compiled selection and translation.

This slice requests **no new save fields or format**. Current location and owned trainer/collection already have native fields; the prototype adds no independent Johto badges, quests, trainer completions or one-time rewards. The four-byte margin remains an open limitation. Before coding, verify that these exact requirements need no additional persistent allocation; stop if they do. This does not authorize treating unprotected extension bytes as safe new storage.

Accept the incomplete B1 browser matrix for this development slice only. Use desktop mGBA as the initial canonical validation environment. Resume browser qualification later against a meaningful unified slice, without modifying A. Existing roamer/original-interface defects remain named evaluation limitations; they must be resolved or explicitly decided before release qualification.

## Deliverables and finite acceptance

1. Preserve 010, then produce one complete reviewed local patch, configuration/build manifests, exact ROM paths/hashes, and a map/dependency/budget delta.
2. Execute the changed unified ROM's natural FireRed opening and starter once, then travel to the two-map Johto slice and interact with its NPC.
3. Execute ten bounded travel round trips as required by the original B2 checklist. Check arrival coordinates, collision, control release and return access. These checks address the new travel code; do not repeat unrelated B0 soak tests.
4. Save normally and cold-load through Continue in both regions, checking trainer/rival/Dex/party/items/location and retained Kanto progression. Use fresh disposable prototype saves. No retail/010/personal-save migration claim.
5. Prove existing Kanto/Sevii selections and live save fields were retained. Regress the separate HnS target only where shared changes affect it; preserve unchanged target evidence.
6. Supply C a precise affected-map/graphics/palette/resource notice. Keep its frozen 010 package immutable and do not restart unrelated art inventory or unchanged tests.

## Subsequent implementation stages

After this travel milestone, resolve the save foundation before independent Johto progression: specify protected, versioned regional state and every save path, then obtain approval for its exact allocation/integrity/recovery changes. The B1 audit's 1,332-byte extension/256-byte reserve remains a sizing proposal, not an approved production layout. FireRed roamer and original-system repairs also need their named scopes. Then adapt one contiguous Johto story segment with independent regional progression; do not import the entire campaign at once.

## Stop boundaries

Stop for review if the two-map slice requires a save-layout/capacity change, broader restructuring, required-feature removal, unsupported save conversion, engine replacement or materially larger content import. No multiplayer/Discord, Workstream A changes, NAS/network changes, global installation, GitHub Actions, hosted automation, deployment, commit or remote write. All source/output/save/private evidence stays local and ignored. Stop at B2 review after delivering the prototype; no automatic B3.

[Owner approval](decisions/2026-10-09-b2-travel-slice.md) authorizes the named two-map development integration and its bounded validation while accepting deferred B1 browser checks for evaluation only. It does not authorize save implementation, a production Johto unlock, independent Johto progression or a full region merge.
