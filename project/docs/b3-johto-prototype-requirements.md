# First playable Johto progression prototype

**October 13, 2026. Status: implemented; focused native journey executed, prototype review gate.** The owner's [latest direction](decisions/2026-10-13-playable-johto-direction.md) prioritizes a workable combined game and fewer repeated tests. This bounded slice builds on accepted B2 travel and frozen save-foundation 0019/final05. It is development content, not the full Heart & Soul campaign or a player release. The [results](b3-johto-prototype-results.md) preserve the failed fresh build, successful retained-tree repairs and all tests not executed; a corrected independent clean repeat remains NOT RUN.

## Playable outcome

Keep FireRed's trainer, party, PC, inventory, money, Pokédex, rival and Kanto/Sevii progression. Use the existing labelled development travel between Pallet and New Bark Town. The trainer enters Elm's lab, accepts a request to visit Cherrygrove's Guide, walks across Route29, speaks to the Guide, and returns to Elm for **one Potion, once**. Revisits and ordinary saves/cold reloads retain that quest. A full bag leaves the reward pending until the item can actually be added.

Enable the existing HnS maps and graphics needed for New Bark/Lab, Route29, Cherrygrove and its basic interiors. Select only Route29's original day/night wild encounters for FireRed, using the shared encounter-time logic; retain every other target's encounter tables. No new species data is added. Keep the original HnS target's scripts and target selection unchanged. Unimplemented onward roads must have clear, traversable return boundaries; do not create dangling connections or silently import HnS's Kanto. Preserve existing FireRed/B2 map and layout numeric identities when adding maps. The original Kanto/Sevii content stays selected.

The existing FireRed party accompanies the trainer. No second starter, Johto rival, badges, field-move permissions, level caps, final travel unlocks or automatic resource reset is introduced. Elm's request is a small original development quest; it does not claim to be the original HnS opening.

## Save contract

Native version **6**, FRJS schema **1**, layout **1**, SaveBlock3 **1,332 bytes**, all native offsets/checksums, coherent-bank transaction, 256-byte stored reserve and 292-byte outside-format capacity remain unchanged. No new mutable global storage is added. The four-byte SaveBlock1 margin and FireRed roamer defect remain open.

Register content **2** for this bounded quest. Content **1** remains strictly blank and loadable; the current writer upgrades only compatible blank content1 snapshots to content2. Unknown identities remain unsupported. No new version5 inputs or conversion tooling policy is authorized. Work only on new copies of B-owned version6 saves. Old ROMs can reject progressed content2; preserve original saves and use separate ROM/save directories.

| Stable Johto identity | Meaning |
|---|---|
| Fixed record flag value1 | Johto initialized when Elm's request is accepted |
| Event/trainer/variable mapping revision1 | Precise mapping for this prototype, no generic HnS flag reuse |
| Variable index0 | 0 uninitialized, 1 accepted, 2 Guide visited, 3 reward claimed |
| Event bit0 | Request accepted |
| Event bit1 | Guide visited |
| Event bit2 | Potion successfully awarded |

Initialized valid states have variable1/2/3 with event byte1/3/7 respectively. Uninitialized content2 is entirely blank like content1. Other event bits, trainer bits, variables, badges, starter/rival metadata, travel slot and reserves remain zero. Existing Kanto flags/variables keep their original native meaning. Every live Johto writer notifies the existing save coordinator before mutation. The item reward uses the ordinary inventory API and records success only after actual insertion.

## Focused acceptance and evidence

1. One clean FireRed build from the pin plus a complete cumulative patch; preserve command, real exit, logs, configuration and artifact hashes. Compare map/layout IDs and resource totals against final05. Check other-target selection/guards for the changed files; broaden only for a relevant change or failure.
2. Targeted real-C checks for accepted content1, content2 quest transitions, contradictory/unknown states, idempotent initialization and untouched reserve. This qualifies the new state contract, not every old save family.
3. One native play session using ordinary controls: accept Elm's request, reach Cherrygrove's Guide, return, receive one Potion, repeat conversation without another reward, then normal Save/full-process exit/cold Continue. Inspect durable Johto state and trainer/party/PC/Dex/rival/inventory/Kanto progression. Return to Kanto through B2 travel and check retained trainer/progress.
4. Report checks exactly as executed, failed or not run. Bag-full handling requires source/targeted-test evidence; do not call it a GUI pass unless executed. No new broad opening/campaign, cable or browser soak is required for this slice.

Keep the frozen baselines and all artifacts/saves/private evidence local and ignored. B owns saves, campaigns, time/palette runtime, budgets and integration. C owns isolated art inventory/replacements. A/C repositories, services, dependencies, plans and credentials remain untouched. Provide C a targeted dependency notice for the added map selection and source/ID changes; unrelated asset work need not restart.

Stop at the prototype review gate before extending the quest into the eight-gym Johto campaign. A broader restructuring, lost required gameplay, physical save-layout or capacity change is a separate review condition. No commit, push, remote write, hosted workflow, automation, deployment or NAS/network change is implied.
