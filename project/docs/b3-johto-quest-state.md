# B3 first Johto errand

This is a small playable quest for the existing FireRed trainer: speak to Elm in New Bark Town, visit the guide in Cherrygrove City, and return to Elm for one Potion. The trainer, party, rival name, Pokédex, and native Kanto progression stay in their existing fields. This slice grants no second starter, Johto rival, badge, or campaign completion.

The implementation is FireRed only. The original HnS laboratory and Cherrygrove scripts remain intact in the alternate preprocessor branch. The original HnS starter, tour, and campaign triggers are excluded from the FireRed map variants.

## State contract

The existing regional allocation, schema 1, layout 1, 256-byte internal reserve, and 292-byte external save capacity remain unchanged. Content 2 registers this quest; the approved content 1 blank foundation remains readable. Content 2 can also remain blank until acceptance. Acceptance initializes Johto flags to 1 and event, trainer, and variable map revisions to 1.

All indices below belong to the Johto codec. They are not native Kanto or upstream HnS flag/variable numbers.

| Johto variable index 0 | Meaning | Cumulative event bits 0/1/2 |
| --- | --- | --- |
| 0 | Not started; Johto record remains uninitialized | `000` |
| 1 | Elm errand accepted | `001` |
| 2 | Cherrygrove guide visited | `011` |
| 3 | Potion successfully granted and reward claimed | `111` |

An initialized state 0 is invalid. All unused regional events, trainers, variables, badges, starter, rival, travel, and reserve bytes remain zero for this slice. The codec validates each registered state and its matching event mask before a load or save is accepted.

Declining Elm's offer or talking to the guide before acceptance does not initialize Johto. Repeated acceptance, guide visits, and completed dialogue do not reset progress. State queries validate live semantic data without requiring the last saved CRC or digest to match a subsequently changed RAM image.

## Reward and write behavior

Elm first calls the native `checkitemspace` for one `ITEM_POTION`, then the native `additem`. The claim special runs immediately after actual successful addition, before item-message routines can replace `VAR_RESULT`. Only a successful addition while quest state is 2 can advance to state 3. A full bag or failed addition leaves state 2, so making room allows a later attempt. The fixed item path avoids changing the Potion through the optional obtain-item randomizer. Native `msgreceiveditem` provides the normal item presentation after the claim.

The interaction holds the normal script lock. Item addition and regional state change occur in that interaction before normal saving becomes available. All regional mutations declare script save effects and notify the existing FireRed save coordinator immediately before writing. The implementation uses the existing `gSaveBlock3Ptr` image and bounded codec accessors; it adds no live save field, mutable global, allocation, or save-coordinator alias.

## Focused qualification

An executed host run compiled the actual quest C and regional codec C with AddressSanitizer and UndefinedBehaviorSanitizer and passed 39 focused assertions. It covered blank foundation adoption, pre-acceptance visits, acceptance and guide idempotence, failed item-result rejection, successful claim, repeated claim, invalid-state refusal, and notifications before each of the three real regional mutations. Integer, opaque save-pointer, script-effect, and event-data dependencies were supplied by a narrow harness. It did not execute the actual bag, game scripts, ARM layout, save coordinator, or emulator. Private commands, source hashes, logs, and exit codes are in `_local/evidence/b3-johto-01/quest-runtime/host-check-02/result.json`. The first run is preserved separately: its final harness-only expected effect-call totals were corrected; engine code did not change.

The [final0022 native results](b3-johto-prototype-results.md) now record the actual request/Guide/reward/repeat journey, normal Save/full quit/cold Continue, visible Potion2 and return to Pallet. Earlier foundation or B2 results are retained with their own identities. The following list was the test procedure; decline, pre-acceptance Guide and bag-full branches were not executed in the GUI and remain covered only by source/focused real-C evidence.

1. Use a fresh isolated copy of an owned foundation test save. Record trainer identity, party, rival name, Pokédex, bag Potion count, Kanto progression, and location before travel. Reach New Bark Town through the existing travel interaction.
2. Decline Elm once, then accept. Confirm the guide before acceptance leaves state 0 where feasible, acceptance produces state 1/mask 1, and re-talk gives a reminder rather than a starter. Walk Route 29 to Cherrygrove and talk to the guide; confirm state 2/mask 3 and inert repeat dialogue.
3. Return to Elm. Confirm a successful reward adds exactly one Potion and produces state 3/mask 7. Repeat dialogue and confirm no second Potion. Check bag-full behavior on an isolated fixture if required: no Potion and no claim until room is made; do not alter a personal save.
4. Perform one normal in-game save and cold reload. Confirm state 3, event mask 7, the single reward, and retained trainer/party/rival/Pokédex/Kanto state. Use the existing travel interaction to return to Kanto and confirm the same trainer and progression.

Build, source, map, and save evidence must bind to the actual frozen B3 candidate. The review remains bounded to this errand and stops before further Johto campaign work. Full Johto progression, release readiness, backward use of content 2 in the older foundation engine, and long-term save compatibility are not established by this slice.
