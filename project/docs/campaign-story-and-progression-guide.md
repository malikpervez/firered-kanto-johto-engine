# Kanto → Johto: story and progression guide

Updated October 20, 2026. **Current local preview: 37C.** This is the owner-facing route through the implemented story, with separate links to exact dialogue, choices, source labels and original screenshots. It is a documentation refresh, not a new game build or natural campaign playthrough.

Open [the start-to-finish HTML guide]([LOCAL_WORKSPACE]/_local/owner-review/index.html#journey).

## Current build and what changed

37C ROM SHA-256: `14ffbb4739e873eb259ce584e879c081a78ee65cdef59103f4a3e3a110265023`. **781,436 ROM bytes free** (about 763 KiB) within the unchanged 32 MiB cartridge. [Exact build manifest]([LOCAL_WORKSPACE]/_local/artifacts/johto-full-37c-firered/manifest.json).

36P remains the original feature/capture record for Pikachu moods; 37A and 37C are separate local previews. Historical test evidence is not relabeled as a new 37C pass.

- **37C — Pikachu rides on Trail’s back.** Uses the actual in-game Pikachu frames and palette. Four-way riding, mirrored right pose, walking return, retained affectionate dialogue and a normal Save/full-quit/fresh Continue executed. +880 ROM bytes versus 37A. [Review]([LOCAL_WORKSPACE]/_local/evidence/pikachu-bike-01/REVIEW.md).
- **37A — Trail and the title screen.** Player sprites, battle presentation and title assets integrated in a local preview, with original native captures. The title intentionally stays without Pikachu. Final pixel cleanup and the listed alternate action/battle cases remain pending. [Review]([LOCAL_WORKSPACE]/_local/evidence/trail-player-title-01/REVIEW.md).
- **36P — Pikachu’s closeness and situational moods.** Persistent companion policy plus 15 reaction outcomes. Captured and pending moods remain individually labeled; read exact text, triggers and original 36P screenshots. [Review]([LOCAL_WORKSPACE]/_local/evidence/pikachu-reactions-01/owner-review-36p/REVIEW.md).
- **36M — Friends, battles and campsite staging.** FG01–FG22, 14 opponents, departure/reunion and livelier scene movement. Bounded native checks address Lugia overlap and Fuji’s indoor continuation. Source-equal evidence keeps its originating build. [Review]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md).
- **33B — Jessie and James.** Genuine James walking art, separate Jessie/James portraits and the optional Celadon double battle. Jenny has no battle; current Jenny sheet and scene-bound Meowth are preserved. [Review]([LOCAL_WORKSPACE]/_local/evidence/story-presentation-04/owner-review-33b-03/REVIEW.md).
- **31E / 30F / 29 — The continuous campaign and earlier story threads.** Pikachu starter and optional Kanto gifts; independent rivals; Nao/Ho-Oh; Mewtwo/Mew; Rocket-created replicas and Shadow Lugia; the outdoor road and Surf crossing to New Bark. Original native result scopes remain attached. [Review]([LOCAL_WORKSPACE]/docs/johto-campaign-build-and-test-results.md).
- **35A — Content-preserving ROM optimization.** Retained byte-sharing and compiler optimization work recovered cartridge space without changing gameplay or saves. Historical recovery measurements stay in their report; 37C’s current measured headroom is shown above. [Review]([LOCAL_WORKSPACE]/docs/rom-optimization-results.md).
- **23 → 25B → 29 — Kanto’s maps, ambient Pokémon and visual repairs.** HnS-style terrain and ambient Pokémon were adapted around the FireRed campaign. The later Oak-lab/exit repairs and complete western-road tree edges supersede the earlier broken presentation. This does not claim every Kanto map was gameplay-tested. [Review]([LOCAL_WORKSPACE]/docs/candidate23-repair-and-tooling-audit.md).
- **Native6 foundation — One collection with independent regional progress.** The approved save foundation and bounded conversions support the continuous trainer and separate regional state. The original conversion allowlist and normal-save evidence remain explicit; arbitrary older saves are not automatically supported. [Review]([LOCAL_WORKSPACE]/docs/save-foundation-review.md).

## Reading the route

The numbered route below is a practical story order, not an extra enforced sequence. Native optional gym and sidequest ordering remains. Optional meetings can be skipped; advancing the Friends group retires earlier placements without fabricating receipts. Starter gifts remain available until their own native successful delivery. Kanto and Johto keep separate rival names, badges and progression.

Full implemented textboxes and images stay in their linked event reviews. This summary does not replace exact dialogue. Captures retain their original build and staged/natural labels.

## 01. A first partner, a glimpse of the sky

**Where:** Pallet Town → Route 1.

Trail begins as the same Kanto trainer who will eventually reach Johto. Eligible ordinary new games receive Pikachu in Oak’s lab. Blue receives Eevee. After their opening battle, the Route 1 rescue leads into the Ho-Oh flyby.

**Progression:**

1. Complete the native starter grant and naming, then the opening rival sequence. Both win and loss paths retain recovery and lab exit.
2. Help shelter the Pidgey on the first eligible Route 1 arrival, before receiving the Pokédex.
3. Collect Oak’s Parcel in Viridian and return it for the original Pokédex ceremony.

**Connected events:**

| ID | Event / actual entry label | Exact dialogue, images and result record |
| --- | --- | --- |
| ST01 | First partner — [`ST01_LabVisibility`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/starter_recruitment.inc:255) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/story-additions-02/story-review-31e/owner-review-02/story-review.md) |
| RB01 | Opening sky — [`RB_TryOpening`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rainbow_story.inc:40) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/story-additions-02/story-review-31e/owner-review-02/story-review.md) |
| RB02 | Oak records it — [`RB_OakBird`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rainbow_story.inc:118) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html) |

Existing saves retain their real starter and history. The flyby is a fresh-cohort event, not a scene retroactively invented for older trainers. Incompatible challenge/randomizer options retain the supported native starter flow.

## 02. The road north

**Where:** Viridian → Route 2 → Viridian Forest → Pewter.

The first badge journey runs alongside the strangers’ arrival. Seven adult friends appear in Viridian, Giratina leaves them stranded, and their first campsite begins taking shape. Nao introduces her bell and her search for the rainbow bird.

**Progression:**

1. Travel north through Viridian Forest and earn Brock’s Boulder Badge.
2. The campaign does not require meeting Nao, the Stranger, or the friends.

**Connected events:**

| ID | Event / actual entry label | Exact dialogue, images and result record |
| --- | --- | --- |
| FG01 | Seven people and one HDMI cable — [`FG01_Interact`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:94) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md) |
| MW01 | Viridian stranger — [`MW01_Visibility`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rainbow_story.inc:390) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html) |
| FG02 | Brian invents camping badly — [`FG02_Interact`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:229) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md) |
| B01 | Brian — Early — [`FG_Battle01`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:3047) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md) |
| RB03 | Nao in Pewter — [`RB_PewterVisibility`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rainbow_story.inc:142) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html) |

Pikachu does not receive a scripted exception to Ground immunity. A complete natural Brock route remains NOT RUN in the recorded character-story checks.

## 03. Partners along the way

**Where:** Mt. Moon → Route 4 → Cerulean → Route 24.

The fossil sequence remains intact. Jessie, James and Meowth get the wrong end of a net near the exit, the disguised Stranger asks about choice, and the friends gradually find willing partners. Two optional rescues make Bulbasaur and Charmander available.

**Progression:**

1. Finish Mt. Moon’s original fossil sequence and reach Cerulean.
2. Follow the native Nugget Bridge and Bill progression; challenge Misty on the normal campaign route.

**Connected events:**

| ID | Event / actual entry label | Exact dialogue, images and result record |
| --- | --- | --- |
| JT01 | Wrong end of the net — [`JT01_Visibility`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rocket_trio_story.inc:12) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/story-additions-02/story-review-31e/owner-review-02/story-review.md) |
| MW02 | Route4 stone — [`MW02_Visibility`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rainbow_story.inc:420) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html) |
| FG03 | The acoustics are incredible — [`FG03_Interact`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:368) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md) |
| B02 | Jon — Early — [`FG_Battle02`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:3083) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md) |
| FG04 | Everybody has a partner now — [`FG04_Interact`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:508) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md) |
| ST02 | Little guardian — [`ST02_Caretaker`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/starter_recruitment.inc:5) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/story-additions-02/story-review-31e/owner-review-02/story-review.md) |
| ST03 | Someone came back — [`ST03_Traveler`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/starter_recruitment.inc:48) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/story-additions-02/story-review-31e/owner-review-02/story-review.md) |

JT01 retires after Misty, Kanto completion, or a later trio meeting. ST02 care and ST03 shelter remain available after decline or failed native delivery. Bulbasaur is level 10; Charmander is level 12.

## 04. Harbor trouble and practice matches

**Where:** Vermilion → S.S. Anne → Route 11.

The original S.S. Anne and Lt. Surge progression continues. Jenny and the harbor helpers resolve a separate rescue; Squirtle can join after the Kanto Thunder Badge. The friends experiment with transport schedules and coaching.

**Progression:**

1. Complete the original Cut/S.S. Anne progression and earn the Thunder Badge.
2. Visit the dry dock for the optional Squirtle story after that badge.

**Connected events:**

| ID | Event / actual entry label | Exact dialogue, images and result record |
| --- | --- | --- |
| FG05 | Tim discovers the ferry schedule — [`FG05_Interact`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:648) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md) |
| FG06 | Two very different coaching styles — [`FG06_Interact`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:765) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md) |
| B03 | Nick — Early — [`FG_Battle03`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:3119) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md) |
| B04 | Lb — Early — [`FG_Battle04`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:3153) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md) |
| ST04 | Harbor helpers — [`ST04_Jenny`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/starter_recruitment.inc:91) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/story-additions-02/story-review-31e/owner-review-02/story-review.md) |

Squirtle is a one-time level 15 native gift after the rescue. Jenny has no battle. No Pokémon ownership check substitutes for the gift receipt.

## 05. Rocket’s copies and the people outside

**Where:** Celadon → Rocket Hideout.

Giovanni, the Hideout and the Silph Scope remain the native campaign. Nao has recovered her notebook. The Stranger questions trust, the friends try to find a room, and the trio’s researcher disguise leads to a separately optional Jessie/James double battle.

**Progression:**

1. Clear the native Rocket Hideout and recover the Silph Scope.
2. Erika and adjacent gym routes retain their native availability; this guide gives one readable route, not a new enforced gym order.

**Connected events:**

| ID | Event / actual entry label | Exact dialogue, images and result record |
| --- | --- | --- |
| RB05 | Recovered notebook — [`RB_CeladonNaoVisibility`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rainbow_story.inc:211) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html) |
| MW04 | Celadon trust — [`MW04_Visibility`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rainbow_story.inc:469) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html) |
| JT02 | Official researchers — [`JT_CeladonVisibility`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rocket_trio_story.inc:89) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/story-presentation-04/owner-review-33b-03/REVIEW.md) |
| FG07 | Manifesting a room — [`FG07_Interact`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:911) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md) |
| B05 | X — Early — [`FG_Battle05`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:3191) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md) |

The current JT02 battle is implemented after 31E’s comedy-only scene. It requires two usable Pokémon and no NPC escort; declining remains safe. Nao can prioritize an unfinished Fuji meeting before returning to the hotel.

## 06. A home, not a cage

**Where:** Lavender → Pokémon Tower → Fuji’s house.

The Silph Scope enables the original Tower rescue. Fuji’s real rescue and Poké Flute reward open the quieter Nao, Stranger and friends scenes. The friends’ conversation moves into Fuji’s house and returns outside.

**Progression:**

1. Rescue Mr. Fuji and receive the native Poké Flute.
2. Use the original Snorlax route progression when ready.

**Connected events:**

| ID | Event / actual entry label | Exact dialogue, images and result record |
| --- | --- | --- |
| RB04 | Fuji's answer — [`RB_FujiVisibility`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rainbow_story.inc:187) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html) |
| MW03 | A home, not a cage — [`MW03_Visibility`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rainbow_story.inc:446) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html) |
| FG08 | Quiet outside Lavender — [`FG08_Interact`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:1088) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md) |

Fuji’s original service and doorway are preserved. These optional conversations do not replace the Tower battle, rescue or reward.

## 07. Responsibility and the disguise slipping

**Where:** Fuchsia / Safari Zone → Saffron / Silph Co..

The native Safari, Surf, Strength, gyms and Silph campaign remain. The friends take on small responsibilities and conduct a disastrous interview. At Silph, the Stranger’s disguise briefly slips; Rocket’s copied-call equipment also connects to Nao’s later story.

**Progression:**

1. Follow the original Safari HM and Koga progression needed for travel.
2. Liberate Silph Co., receive its native rewards and continue Sabrina’s route.

**Connected events:**

| ID | Event / actual entry label | Exact dialogue, images and result record |
| --- | --- | --- |
| FG09 | The group gets actual responsibilities — [`FG09_Interact`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:1219) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md) |
| B06 | Tim — Early — [`FG_Battle06`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:3229) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md) |
| FG10 | A very bad job interview — [`FG10_Interact`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:1362) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md) |
| MW05 | Silph disguise slip — [`MW05_Visibility`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rainbow_story.inc:492) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html) |
| RB06 | Silph echo — [`RB_SilphEquipment`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rainbow_story.inc:236) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html) |

RB06 is actually spoken by the existing Silph scientist in Celadon after Silph liberation; it is not a new Silph building scene. Native optional gym order remains unchanged.

## 08. The quiet stranger reveals himself

**Where:** Cinnabar → Pokémon Mansion → early Sevii visit.

The Mansion journals keep their original account. After the Secret Key is found, Mewtwo reveals the identity behind the Stranger and leaves the eventual cave encounter as a choice. The friends see a hint of home reflected in the water.

**Progression:**

1. Find the original Mansion Secret Key and progress through Blaine.
2. Keep Bill’s native first Sevii trip, its existing tasks and return path.

**Connected events:**

| ID | Event / actual entry label | Exact dialogue, images and result record |
| --- | --- | --- |
| MW06 | Cinnabar reveal — [`MW06_Visibility`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rainbow_story.inc:518) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html) |
| FG11 | The television in the water — [`FG11_Interact`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:1461) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md) |

Mew remains a sparse observer, not a reward from this plot. The proposed new Sevii friends scene FG-A is not in 37C. Original Articuno, Zapdos and Moltres stay in Seafoam, the Power Plant and Mt. Ember.

## 09. Kanto Champion

**Where:** Viridian Gym → Route 22/23 → Indigo Plateau.

Blue remains the original competitive Kanto rival through the first championship. The native final gym, Victory Road, Elite Four, Champion sequence, credits and Pallet return remain the main story. Mewtwo’s Route 22 question can fall before or after the League.

**Progression:**

1. Earn the remaining native Kanto badges and clear the first Kanto League.
2. Oak’s Hall-of-Fame referral points the trainer toward Elm and Johto.

**Connected events:**

| ID | Event / actual entry label | Exact dialogue, images and result record |
| --- | --- | --- |
| MW07 | Route22 question — [`MW07_Visibility`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rainbow_story.inc:545) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html) |
| FG12 | Seven terrible spectators — [`FG12_Interact`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:1586) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md) |
| BL01 | A new field of study — [`CG_BlueLab`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/character_growth.inc:47) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/story-additions-02/story-review-31e/owner-review-02/story-review.md) |
| BL02 | The Pidgey notebook — [`CG_BlueRoute1`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/character_growth.inc:76) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/story-additions-02/story-review-31e/owner-review-02/story-review.md) |
| RB07 | Oak sends you west — [`RB_OakReferral`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rainbow_story.inc:121) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html) |

After losing the championship Blue is content and excited about science. BL01 is at Oak’s lab; BL02 is on Route 1 before the completed Elm introduction. These scenes do not remove his native battles or rematches. The later Sevii/Celio quest and Cerulean Cave can be completed before heading west or after returning; Johto’s championship is not an added Mewtwo prerequisite.

## 10. West, down to the water

**Where:** Indigo western road → Route 27 coast → New Bark.

Construction workers keep the westbound road closed until the native Kanto championship. It then opens as a forest road with coastal stairs. Surf west across the original New Bark water connection; the route also works in reverse.

**Progression:**

1. Return to Indigo’s western edge after the Kanto championship.
2. Follow the outdoor road downhill, descend to Route 27’s shore and Surf west to New Bark.
3. Bring the existing Surf capability; this route grants no HM, badge, Pokémon or level adjustment.

Johto initializes once without resetting Kanto. Native Kanto clear is the actual road gate; Oak supplies the story directions. The obsolete cave-only test slice is historical. FG-B’s proposed friends crossing is not implemented.

[Progression / evidence reference]([LOCAL_WORKSPACE]/docs/natural-johto-journey-results.md).

[Progression / evidence reference]([LOCAL_WORKSPACE]/docs/johto-campaign-integration-requirements.md).

## 11. A visiting Champion, not a new character

**Where:** New Bark → Cherrygrove → Mr. Pokémon → Violet.

Elm welcomes Oak’s visiting trainer and gives the adapted research errand without a second starter. The original Johto errand, stolen-partner/rival introduction and early badge journey continue with the same collection. The group reaches New Bark independently.

**Progression:**

1. Accept Elm’s introduction and follow the native Mr. Pokémon errand and return sequence.
2. Continue through the original Johto rival and Violet/Falkner progression.
3. Blue’s optional lab research follow-up is available back in Kanto once Elm has been met.

**Connected events:**

| ID | Event / actual entry label | Exact dialogue, images and result record |
| --- | --- | --- |
| RB08 | Elm's welcome — [`RB_ElmBird`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rainbow_story.inc:241) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html) |
| FG13 | No second character creation — [`FG13_Interact`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:1705) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md) |
| BL03 | Notes from two regions — [`CG_BlueLabAfterIntro`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/character_growth.inc:58) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/story-additions-02/story-review-31e/owner-review-02/story-review.md) |

Kanto and Johto rival names, badges and story state are independent. Blue’s Eevee→Umbreon selection belongs only to the new Pikachu cohort after BL03; the later actual enemy Umbreon battle remains NOT RUN. FG-C outside Sprout Tower is proposed only.

## 12. Finding their footing

**Where:** Ruins of Alph → Azalea → Ilex Forest → Goldenrod.

The native Slowpoke Well, Bugsy, rival, forest and Whitney progression remains. Xavier looks for meaning at the Ruins. Jon begins learning how to speak to his Pokémon, LB experiments with a move name, and the Rocket trio attempts another disguise.

**Progression:**

1. Resolve Slowpoke Well and continue the native Azalea/Ilex path.
2. Follow the existing Goldenrod gym and travel progression.

**Connected events:**

| ID | Event / actual entry label | Exact dialogue, images and result record |
| --- | --- | --- |
| FG14 | Xavier reads the room — [`FG14_Interact`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:1819) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md) |
| FG15 | Jon learns one useful volume — [`FG15_Interact`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:1934) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md) |
| FG16 | The move has a name — [`FG16_Interact`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:2052) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md) |
| B07 | Ham — Early — [`FG_Battle07`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:3263) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md) |
| JT03 | Fresh start, allegedly — [`JT_GoldenrodVisibility`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rocket_trio_story.inc:101) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/story-presentation-04/owner-review-33b-03/REVIEW.md) |

JT03 appears in the early Goldenrod window, before takeover. FG16 is suppressed during occupation and can also appear after the native Director rewards. Missing earlier scenes use late introductions rather than invented participation.

## 13. The towers, the lighthouse and the sea

**Where:** Ecruteak → Olivine → Cianwood.

Burned Tower’s native events release the beasts and unlock Nao’s explanation of the towers. Silver pauses for his exhausted partner. At the coast, healing Amphy stays the real objective; Nao notices care for the Pokémon already here and Tim becomes useful at the harbor.

**Progression:**

1. Follow the native Burned Tower/Ecruteak and Morty progression.
2. Continue the lighthouse, Cianwood medicine/Chuck and Amphy/Jasmine progression as their native gates allow.

**Connected events:**

| ID | Event / actual entry label | Exact dialogue, images and result record |
| --- | --- | --- |
| RB09 | Ecruteak truth — [`RB_NaoJohtoIntro`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rainbow_story.inc:273) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html) |
| SV01 | A small pause — [`CG_SilverEcruteakVisibility`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/character_growth.inc:94) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/story-additions-02/story-review-31e/owner-review-02/story-review.md) |
| FG17 | A reflection that waits — [`FG17_Interact`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:2178) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md) |
| RB10 | Amphy callback — [`RB_OlivineVisibility`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rainbow_story.inc:359) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html) |
| FG18 | Tim books the right trip — [`FG18_Interact`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:2281) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md) |

FG-D’s new Cianwood beach scene is not implemented. The guide does not turn the friends’ travel into player transport rewards.

## 14. Silence the signal

**Where:** Lake of Rage → Mahogany → Goldenrod Radio Tower.

The original red Gyarados, Mahogany hideout and Radio Tower battles retain their role. Nao’s copied recording is switched off through a later conversation. Silver waits at a Center, while the friends help frightened Pokémon after the takeover.

**Progression:**

1. Resolve native Lake of Rage/Mahogany progression, Pryce and the Radio Tower takeover.
2. After clearance, optional conversations provide the recording aftermath and the coastal Whirl warnings.

**Connected events:**

| ID | Event / actual entry label | Exact dialogue, images and result record |
| --- | --- | --- |
| RB11 | Lance signal thought — folded — [`RB_Recording`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rainbow_story.inc:291) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html) |
| RB12 | Silence the copy — [`RB_RadioAftermath`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rainbow_story.inc:660) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html) |
| RB13 | Welcome — [`RB_Welcome`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rainbow_story.inc:311) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html) |
| SV02 | Waiting at the counter — [`CG_SilverGoldenrodVisibility`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/character_growth.inc:136) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/story-additions-02/story-review-31e/owner-review-02/story-review.md) |
| FG19 | Nobody yells at the frightened Pokémon — [`FG19_Interact`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:2404) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md) |
| LG01 | Coastal warnings — [`BlackTide_CoastalWarning`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/johto/adapted/WhirlIslands_LugiaChamber_hns.inc:1009) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html) |

RB11 is folded into RB12; there is no separate implemented Lance scene. Nao’s Ready/Later welcome respects native Ho-Oh encounter state. FG-E at Lake of Rage is proposed only.

## 15. The last badge and a choice of opponents

**Where:** Ice Path → Blackthorn → Dragon’s Den.

The native path through Ice Path, Clair and Dragon’s Den remains. Seven final friend opponents become individually selectable after the eighth regional badge and the completed native Den follow-up. Silver’s later quiet question waits for his verified native milestone.

**Progression:**

1. Complete Clair and the original Dragon’s Den follow-up.
2. Continue Silver’s original later rival progression; SV03 appears only after that native milestone, not automatically on the first Den visit.

**Connected events:**

| ID | Event / actual entry label | Exact dialogue, images and result record |
| --- | --- | --- |
| FG20 | We actually know what we are doing — [`FG20_Interact`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:2505) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md) |
| SV03 | Another round — [`CG_SilverDenVisibility`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/character_growth.inc:170) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/story-additions-02/story-review-31e/owner-review-02/story-review.md) |
| FINAL_BRIAN | Brian — Final — [`FG_Battle08`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:3313) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md) |
| FINAL_X | X — Final — [`FG_Battle09`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:3353) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md) |
| FINAL_TIM | Tim — Final — [`FG_Battle10`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:3393) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md) |
| FINAL_LB | Lb — Final — [`FG_Battle11`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:3433) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md) |
| FINAL_NICK | Nick — Final — [`FG_Battle12`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:3477) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md) |
| FINAL_JON | Jon — Final — [`FG_Battle13`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:3517) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md) |
| FINAL_HAM | Ham — Final — [`FG_Battle14`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:3557) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md) |

The seven matches are optional. No gauntlet or all-wins requirement is introduced. FG-F’s new Ice Path rescue is not implemented.

## 16. Two legendary roads

**Where:** Baoba’s native choice → Ho-Oh or Lugia route.

Keep Baoba’s original Gold/Ho-Oh versus Silver/Lugia decision. The Ho-Oh route retains its original conditions. The Lugia route deliberately adds the Black Tide confrontation before Johto’s League; later Gold-route access uses its own native postgame conditions.

**Progression:**

1. Follow the existing Kimono/theater, key-item and branch gates.
2. Silver/Lugia: enter the eligible Whirl chamber, resolve all three replicas, then face Shadow Lugia.
3. Gold/Ho-Oh: retain Ho-Oh’s native route; later earned Whirl access can run Black Tide if the crisis has not already closed.

**Connected events:**

| ID | Event / actual entry label | Exact dialogue, images and result record |
| --- | --- | --- |
| LG02 | The manufactured birds attack Lugia — [`WhirlIslands_LugiaChamber_hns_MapScripts`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/johto/adapted/WhirlIslands_LugiaChamber_hns.inc:1) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html) |
| LG03 | Articuno replica: independent battle — [`BlackTide_Articuno`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/johto/adapted/WhirlIslands_LugiaChamber_hns.inc:765) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html) |
| LG04 | Zapdos replica: independent battle — [`BlackTide_Zapdos`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/johto/adapted/WhirlIslands_LugiaChamber_hns.inc:793) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html) |
| LG05 | Moltres replica: independent battle — [`BlackTide_Moltres`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/johto/adapted/WhirlIslands_LugiaChamber_hns.inc:821) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html) |
| LG06 | All three links go dark — [`BlackTide_LinksIfReady`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/johto/adapted/WhirlIslands_LugiaChamber_hns.inc:884) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html) |
| LG07 | Approach and face Shadow Lugia — [`WhirlIslands_LugiaChamber_EventScript_TalkToKimono`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/johto/adapted/WhirlIslands_LugiaChamber_hns.inc:36) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html) |
| LG08 | Restoration and once-only aftermath — [`BlackTide_LugiaWon`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/johto/adapted/WhirlIslands_LugiaChamber_hns.inc:224) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html) |
| JT04 | Even we know better — [`JT04_Visibility`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rocket_trio_story.inc:45) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/story-additions-02/story-review-31e/owner-review-02/story-review.md) |

The three attackers are Rocket-made replicas. Defeating OR catching each, in any order, breaks the links. Loss, escape or interruption never counts. Ordinary saving, healing and returning preserve earned outcomes. The final victory/capture restores Lugia and preserves the actual caught individual. Original birds and Navel Rock remain separate.

## 17. A second championship, the same trainer

**Where:** Native Johto League approach → Hall of Fame.

The original late Johto rival, League approach, Elite Four and Champion progression remains independent of Kanto’s championship. Optional friends or legendary captures do not substitute for clearing Johto’s own Hall of Fame.

**Progression:**

1. Complete the native Johto League approach and League.
2. Johto’s actual game-clear receipt enables the farewell and Nao’s later letter chain.

A staged late-game checkpoint verifies its particular event path; it is not proof that the full combined campaign has been played naturally.

## 18. Everybody goes home—when you say so

**Where:** New Bark campsite → later return visit.

After the Johto League, Giratina offers the group a way home. All seven friends leave with fourteen willing partners in successive groups only when Safe travels is chosen. A distinct later visit brings their reunion and rematches.

**Progression:**

1. Safe travels completes departure and only then records farewell completion.
2. One last battle opens the seven-opponent menu; victory or defeat returns to a later invitation, never automatic departure.
3. Stay a little longer keeps everyone, without a countdown or automatic Save.
4. Leave the map after departure and return later for FG22.

**Connected events:**

| ID | Event / actual entry label | Exact dialogue, images and result record |
| --- | --- | --- |
| FG21 | Everybody goes home — [`FG21_Interact`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:2639) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md) |
| FG22 | Visitors with too much luggage — [`FG22_Interact`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:2848) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md) |

No player Pokémon, item or progress is removed. No legendary capture is required. Giratina never becomes the player’s battle, gift, trade, egg or portal service. FG-G’s later Ecruteak epilogue is proposed only.

## 19. The roads remain open

**Where:** Kanto / Sevii / Johto.

Continue native postgame activities and collection across both regions. The optional Mewtwo story resolves at the original Cerulean Cave encounter; Nao’s letter and the Route 1 Pidgey echo close the rainbow story. These threads can be revisited independently of the friends’ departure.

**Progression:**

1. Meet the original Celio/Sevii cave-access conditions before Mewtwo.
2. MW08 offers Face/Leave before the native level 70 encounter; skipped Stranger scenes never block it.
3. After Johto clear and Nao’s welcome, read Oak’s letter, then interact with the Route 1 Pidgey.

**Connected events:**

| ID | Event / actual entry label | Exact dialogue, images and result record |
| --- | --- | --- |
| MW08 | Cerulean Cave choice — [`MW08_Intro`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rainbow_story.inc:617) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html) |
| MW09 | Cave-mouth reflection — [`MW09_Transition`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rainbow_story.inc:636) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html) |
| RB14 | Larger sky — [`RB_OakLetter`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rainbow_story.inc:128) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html) |

Mewtwo is listed here as an open sidequest, not gated behind the Johto League: only the original Kanto/Sevii access conditions apply. MW09 is an explicit cave-mouth interaction, not automatic exit narration. Original Sevii, Navel Rock and other existing content retain their gates. No extra Celebi/beast/Gen 3+ legendary chapter or third region is implemented in this pass.

## Event directory and exact trigger rules

These entries were reconciled to actual 37C labels. They describe implemented source; gameplay evidence remains scoped to the original linked report. RB11 is folded into RB12, not a separate playable event.

### RB01 — Opening sky

**Trigger:** Route1 map transition adopts supported state; FRESH_COHORT true, OPENING_SEEN false, original Oak-lab scene >=4, Dex not yet received. Sets VAR_TEMP_E1 for the frame table. Completion requires successful renderer; failed start retains retry.

**Status:** IMPLEMENTED. Historical 30-series native scope; see original per-event result. No 37C replay claimed.

**37C source:** [`RB_TryOpening`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rainbow_story.inc:40). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/story-additions-02/story-review-31e/owner-review-02/story-review.md).

Pidgey shelter and early Ho-Oh flyby after the original opening.

### RB02 — Oak records it

**Trigger:** Normal Oak interaction calls RB_OakStory. Supported adoption, Dex received, lab scene !=8, no higher Champion/Johto-letter dispatch; OPENING_SEEN must be set.

**Status:** IMPLEMENTED. Historical 30-series native scope; see original per-event result. No 37C replay claimed.

**37C source:** [`RB_OakBird`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rainbow_story.inc:118). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html).

Optional Oak account of the actual sighting.

### RB03 — Nao in Pewter

**Trigger:** Pewter transition: Dex received; pre-Kanto-Champion; before native Hideout-clear flag and before Poké Flute. Existing Nao introduction is not replayed.

**Status:** IMPLEMENTED. Historical 30-series native scope; see original per-event result. No 37C replay claimed.

**37C source:** [`RB_PewterVisibility`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rainbow_story.inc:142). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html).

Introduction and repeatable bird/home question.

### RB04 — Fuji's answer

**Trigger:** Fuji-house transition: original rescue and Poké Flute receipt, not Kanto Champion, Fuji-scene unseen. If Nao was missed, the normal introduction runs first.

**Status:** IMPLEMENTED. Historical 30-series native scope; see original per-event result. No 37C replay claimed.

**37C source:** [`RB_FujiVisibility`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rainbow_story.inc:187). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html).

Optional Nao/Fuji conversation after rescue and real Flute reward.

### RB05 — Recovered notebook

**Trigger:** Celadon Hotel: Hideout cleared; pre-Champion. If Flute acquired but Fuji scene unseen, Nao stays at Fuji until that optional priority is resolved. Otherwise Hotel actor becomes visible.

**Status:** IMPLEMENTED. Historical 30-series native scope; see original per-event result. No 37C replay claimed.

**37C source:** [`RB_CeladonNaoVisibility`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rainbow_story.inc:211). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html).

Nao already recovered her notebook; no item quest.

### RB06 — Silph echo

**Trigger:** Actual host is the existing Silph Co. scientist in CELADON CITY. His original stolen-Silph-Scope lines run first; new equipment text runs only when FLAG_HIDE_SILPH_ROCKETS is set.

**Status:** IMPLEMENTED. Historical 30-series native scope; see original per-event result. No 37C replay claimed.

**37C source:** [`RB_SilphEquipment`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rainbow_story.inc:236). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html).

Existing Silph scientist confirms Rocket call-reproduction equipment.

### RB07 — Oak sends you west

**Trigger:** Oak dispatch prioritizes supported story state/Dex and original lab state. After native Kanto Champion, OPENING_SEEN chooses westward memory; otherwise honest research text. The separate pre-existing JohtoReferral call remains authoritative for road directions.

**Status:** IMPLEMENTED. Historical 30-series native scope; see original per-event result. No 37C replay claimed.

**37C source:** [`RB_OakReferral`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rainbow_story.inc:121). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html).

Added bird context surrounds the existing Oak→Indigo western pass→Surf→Elm referral.

### RB08 — Elm's welcome

**Trigger:** Existing Elm intro owner calls RB_ElmBird. The added line appears only with OPENING_SEEN. Elm original state/briefing owns progression; no Nao prerequisite, second starter or new initializer.

**Status:** IMPLEMENTED. Historical 30-series native scope; see original per-event result. No 37C replay claimed.

**37C source:** [`RB_ElmBird`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rainbow_story.inc:241). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html).

A short sighting callback before the existing adapted visiting-Champion introduction.

### RB09 — Ecruteak truth

**Trigger:** Original beasts-release flag required. Ecruteak remains Nao priority until truth seen; after truth, before Radio Tower10 she may move to Olivine after Amphy. First interaction returns after truth; playback and Welcome occur on later talks.

**Status:** IMPLEMENTED. Historical 30-series native scope; see original per-event result. No 37C replay claimed.

**37C source:** [`RB_NaoJohtoIntro`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rainbow_story.inc:273). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html).

Late self-introduction and truth about Ho-Oh and the burned tower.

### RB10 — Amphy callback

**Trigger:** Olivine visibility requires original Amphy healed and Ecruteak truth seen; Radio Tower state<10. Repeatable; no new medicine, reward or saved answer.

**Status:** IMPLEMENTED. Historical 30-series native scope; see original per-event result. No 37C replay claimed.

**37C source:** [`RB_OlivineVisibility`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rainbow_story.inc:359). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html).

Care for the Pokémon already here; cosmetic bell response.

### RB11 — Lance signal thought — folded

**Trigger:** No standalone RB11/Lance actor, movement, trigger or receipt exists. Shared playback thought is exposed via RB12’s existing Radio Tower1F Lass/fan interaction or Ecruteak fallback after Tower clearance.

**Status:** FOLDED. Historical 30-series native scope; see original per-event result. No 37C replay claimed.

**37C source:** [`RB_Recording`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rainbow_story.inc:291). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html).

The intended signal/control thought is folded into RB12 rather than a separate Lance scene.

### RB12 — Silence the copy

**Trigger:** Direct Radio1F Lass/fan hook keeps original BEN/DJ dialogue first, then requires Goldenrod state>=10, Mahogany>=17 and RECORDING_STOPPED false. Ecruteak fallback runs after truth and Tower10 on a separate interaction, with no compulsory return trip.

**Status:** IMPLEMENTED. Historical 30-series native scope; see original per-event result. No 37C replay claimed.

**37C source:** [`RB_RadioAftermath`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rainbow_story.inc:660). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html).

Both choices stop the copied playback and preserve Nao’s notes.

### RB13 — Welcome

**Trigger:** Nao Ecruteak: truth and Tower10; playback aftermath must already be completed. Actual YES means Ready, NO means Later. Native Ho-Oh caught/defeated evidence selects rainbow. Native Ho-Oh1/2 defers ritual; Silver branch may show flyby. Renderer failure does not set WELCOME_SEEN.

**Status:** IMPLEMENTED. Historical 30-series native scope; see original per-event result. No 37C replay claimed.

**37C source:** [`RB_Welcome`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rainbow_story.inc:311). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html).

Ready/Later invitation and a finite Ho-Oh flyby or resolved-encounter rainbow.

### RB14 — Larger sky

**Trigger:** Original Johto League clear and WELCOME_SEEN allow one Oak letter. LETTER_READ makes Route1 Pidgey available until EPILOGUE_SEEN. Epilogue is an explicit talk interaction, not an automatic walk-through scene.

**Status:** IMPLEMENTED. Historical 30-series native scope; see original per-event result. No 37C replay claimed.

**37C source:** [`RB_OakLetter`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rainbow_story.inc:128). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html).

Optional Oak letter, then optional Pidgey epilogue on Route1.

### MW01 — Viridian stranger

**Trigger:** Dex receipt; own scene unseen; no full reveal/native Mewtwo closure. OPENING_SEEN selects bird-specific versus generic wording.

**Status:** IMPLEMENTED. Historical 30-series native scope; see original per-event result. No 37C replay claimed.

**37C source:** [`MW01_Visibility`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rainbow_story.inc:390). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html).

Questions the rescue or uses a generic honest alternative, followed by a sparse Mew glimpse.

### MW02 — Route4 stone

**Trigger:** Original durable fossil-completion flag, not Bag fossil possession. Own scene unseen, no MW06/full Mewtwo closure. Rock local13 levitates; stranger local12 and rock are removed afterwards.

**Status:** IMPLEMENTED. Historical 30-series native scope; see original per-event result. No 37C replay claimed.

**37C source:** [`MW02_Visibility`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rainbow_story.inc:420). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html).

Fossil-choice question and small psychic rock movement.

### MW03 — A home, not a cage

**Trigger:** Original Poké Flute receipt; own scene unseen; suppressed by MW06 or native Mewtwo closure. No permanent Fuji relocation.

**Status:** IMPLEMENTED. Historical 30-series native scope; see original per-event result. No 37C replay claimed.

**37C source:** [`MW03_Visibility`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rainbow_story.inc:446). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html).

Separate Lavender stranger/Fuji exchange with optional Mew glimpse.

### MW04 — Celadon trust

**Trigger:** Original Hideout-clear flag, independent of Nao/notebook; own scene unseen and no MW06/native closure.

**Status:** IMPLEMENTED. Historical 30-series native scope; see original per-event result. No 37C replay claimed.

**37C source:** [`MW04_Visibility`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rainbow_story.inc:469). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html).

Questions Poké Balls after opposing Rocket.

### MW05 — Silph disguise slip

**Trigger:** Silph1F; original Master Ball receipt; own scene unseen and no MW06/native closure. Local2 is hidden during reveal, intentionally restored for brief glitch dialogue, then removed at scene completion.

**Status:** IMPLEMENTED. Historical 30-series native scope; see original per-event result. No 37C replay claimed.

**37C source:** [`MW05_Visibility`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rainbow_story.inc:492). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html).

A temporary Mewtwo reveal, returned disguise, then possible Mew glimpse.

### MW06 — Cinnabar reveal

**Trigger:** Cinnabar; native Secret Key discovery hide flag, independent of current Key possession; scene unseen and native Mewtwo unresolved. Local15 is removed before reveal and remains absent through question/answer/glimpse. Original journals unchanged.

**Status:** IMPLEMENTED. Historical 30-series native scope; see original per-event result. No 37C replay claimed.

**37C source:** [`MW06_Visibility`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rainbow_story.inc:518). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html).

Journals context, unique Mewtwo reveal, invitation/choice responses and Mew observer.

### MW07 — Route22 question

**Trigger:** Requires MW06 seen; own scene unseen; native Mewtwo unresolved. Reads native Kanto Champion flag for wording; original rival trigger coordinates unchanged.

**Status:** IMPLEMENTED. Historical 30-series native scope; see original per-event result. No 37C replay claimed.

**37C source:** [`MW07_Visibility`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rainbow_story.inc:545). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html).

Different Champion question before/after Kanto League.

### MW08 — Cerulean Cave choice

**Trigger:** Original Celio/Sevii access remains authoritative. Existing Mewtwo interaction calls MW08_Intro; actual NO leaves without setting native fought state; YES runs original battle. Actual WON/CAUGHT set original FLAG_FOUGHT_MEWTWO; flee/teleport follow native escape/removal path, with transition restoring retry while fought remains unset.

**Status:** IMPLEMENTED. Historical 30-series native scope; see original per-event result. No 37C replay claimed.

**37C source:** [`MW08_Intro`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rainbow_story.inc:617). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html).

Optional familiar/unfamiliar introduction and Face/Leave before original level70 Mewtwo.

### MW09 — Cave-mouth reflection

**Trigger:** Native fought-Mewtwo set; MW09 unseen. Explicit BG sign interaction at Cerulean Cave1F x34,y22, any facing. Transition sets temp availability only; it is not an automatic exit narration.

**Status:** IMPLEMENTED. Historical 30-series native scope; see original per-event result. No 37C replay claimed.

**37C source:** [`MW09_Transition`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rainbow_story.inc:636). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html).

Neutral post-resolution reflection and optional Mew glimpse.

### LG01 — Coastal warnings

**Trigger:** Talk to Olivine Sailor1 or Cianwood PokefanM; VAR_GOLDENROD_CITY_STATE>=10; successful native story adoption.

**Status:** IMPLEMENTED. Historical 30-series native scope; see original per-event result. No 37C replay claimed.

**37C source:** [`BlackTide_CoastalWarning`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/johto/adapted/WhirlIslands_LugiaChamber_hns.inc:1009). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html).

Original Olivine sailor and Cianwood Pokéfan conversations append a Whirl warning after the native Radio Tower state reaches10. The warning itself grants no travel/item/branch progress.

### LG02 — The manufactured birds attack Lugia

**Trigger:** First safe Whirl chamber frame after native Lugia state2(Silver story) or4(earned later access); no final/exempt receipt; FLAG_LG_ATTACK_SEEN unset.

**Status:** IMPLEMENTED. Historical 30-series native scope; see original per-event result. No 37C replay claimed.

**37C source:** [`WhirlIslands_LugiaChamber_hns_MapScripts`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/johto/adapted/WhirlIslands_LugiaChamber_hns.inc:1). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html).

A once-only chamber scene stages three separately manufactured replicas striking Lugia. Rocket leaves, Lugia darkens, and the three independent encounters remain.

### LG03 — Articuno replica: independent battle

**Trigger:** Interact with local actor9 after attack seen; state2 or4; this replica unresolved; not legacy-exempt/final.

**Status:** IMPLEMENTED. Historical 30-series native scope; see original per-event result. No 37C replay claimed.

**37C source:** [`BlackTide_Articuno`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/johto/adapted/WhirlIslands_LugiaChamber_hns.inc:765). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html).

Resolve this Rocket replica by defeating OR catching it. Its original Kanto/Sevii encounter is independent. All three replicas can be approached in any order.

### LG04 — Zapdos replica: independent battle

**Trigger:** Interact with local actor10 after attack seen; state2 or4; this replica unresolved; not legacy-exempt/final.

**Status:** IMPLEMENTED. Historical 30-series native scope; see original per-event result. No 37C replay claimed.

**37C source:** [`BlackTide_Zapdos`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/johto/adapted/WhirlIslands_LugiaChamber_hns.inc:793). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html).

Resolve this Rocket replica by defeating OR catching it. Its original Kanto/Sevii encounter is independent. All three replicas can be approached in any order.

### LG05 — Moltres replica: independent battle

**Trigger:** Interact with local actor11 after attack seen; state2 or4; this replica unresolved; not legacy-exempt/final.

**Status:** IMPLEMENTED. Historical 30-series native scope; see original per-event result. No 37C replay claimed.

**37C source:** [`BlackTide_Moltres`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/johto/adapted/WhirlIslands_LugiaChamber_hns.inc:821). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html).

Resolve this Rocket replica by defeating OR catching it. Its original Kanto/Sevii encounter is independent. All three replicas can be approached in any order.

### LG06 — All three links go dark

**Trigger:** All three replica result pairs valid and nonzero; FLAG_LG_LINKS_OFF_SEEN unset; crisis not final/exempt. Called after a successful replica, by Keeper, or on final approach.

**Status:** IMPLEMENTED. Historical 30-series native scope; see original per-event result. No 37C replay claimed.

**37C source:** [`BlackTide_LinksIfReady`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/johto/adapted/WhirlIslands_LugiaChamber_hns.inc:884). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html).

The third independent success breaks Rocket control. Lugia remains in the Shadow state, becomes approachable, and the Keeper allows unlimited preparation.

### LG07 — Approach and face Shadow Lugia

**Trigger:** Interact with native Lugia actor1 after all replicas resolved and attack seen. Silver native state2→level50; later native state4→level70. Already-final/legacy-exempt routes bypass crisis prompt and corruption.

**Status:** IMPLEMENTED. Historical 30-series native scope; see original per-event result. No 37C replay claimed.

**37C source:** [`WhirlIslands_LugiaChamber_EventScript_TalkToKimono`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/johto/adapted/WhirlIslands_LugiaChamber_hns.inc:36). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html).

Silver retains the original Kimono ceremony after the replicas. Gold later access uses native state4 and direct approach. Both branches offer YES to face Lugia or NO to prepare first.

### LG08 — Restoration and once-only aftermath

**Trigger:** Only actual B_OUTCOME_WON or B_OUTCOME_CAUGHT after final battle; final/legacy paths skip repeating restoration narrative.

**Status:** IMPLEMENTED. Historical 30-series native scope; see original per-event result. No 37C replay claimed.

**37C source:** [`BlackTide_LugiaWon`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/johto/adapted/WhirlIslands_LugiaChamber_hns.inc:224). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html).

Native victory restores Lugia and lets it depart. Native capture restores the actual caught Lugia without replacement. A durable final bit closes the crisis; coastal/Keeper/remaining Kimono dialogue becomes recovery text.

### ST01 — First partner

**Trigger:** Native New Game cohort921; known adopted state; starter preflight accepts options; actual grant requires no933/noSYSGET and labstate2. Incompatible untouched type/randomizer options fall back to original supported choice path without changing existing history.

**Status:** IMPLEMENTED. Original 31-series evidence; JT02/JT03 presentation and battle updates use 33B. Unexecuted branches stay pending in the linked ledger.

**37C source:** [`ST01_LabVisibility`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/starter_recruitment.inc:255). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/story-additions-02/story-review-31e/owner-review-02/story-review.md).

New-game Pikachu partnership, native naming and original rival dispatch.

### ST02 — Little guardian

**Trigger:** Caretaker interaction; no Misty/badge/party-species requirement. Care receipt follows visible scene. Given receipt follows native delivery0/1 only.

**Status:** IMPLEMENTED. Original 31-series evidence; JT02/JT03 presentation and battle updates use 33B. Unexecuted branches stay pending in the linked ledger.

**37C source:** [`ST02_Caretaker`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/starter_recruitment.inc:5). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/story-additions-02/story-review-31e/owner-review-02/story-review.md).

Optional Cerulean care scene followed by actual Bulbasaur gift.

### ST03 — Someone came back

**Trigger:** Route24 VAR_MAP_SCENE_ROUTE24 exactly1 after original bridge/Rocket transaction; no timer/item requirement.

**Status:** IMPLEMENTED. Original 31-series evidence; JT02/JT03 presentation and battle updates use 33B. Unexecuted branches stay pending in the linked ledger.

**37C source:** [`ST03_Traveler`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/starter_recruitment.inc:48). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/story-additions-02/story-review-31e/owner-review-02/story-review.md).

Optional shelter scene and actual Charmander gift.

### ST04 — Harbor helpers

**Trigger:** Native KANTO FLAG_BADGE03_GET, independent of Johto badge. Earlier introduction does not grant gift. Native ship/Cut/Gym progression preserved.

**Status:** IMPLEMENTED. Original 31-series evidence; JT02/JT03 presentation and battle updates use 33B. Unexecuted branches stay pending in the linked ledger.

**37C source:** [`ST04_Jenny`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/starter_recruitment.inc:91). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/story-additions-02/story-review-31e/owner-review-02/story-review.md).

Vermilion introduction and post-Thunder Badge rescue/gift.

### JT01 — Wrong end of the net

**Trigger:** KantoRoute4 exit after native fossil232; before nativeCascade/Champion; no priorJT01/JT02/JT03. Known coordinator required. No choice, battle, theft or extra fossil reward; narration/in-place struggle conveys the net, not a net graphic.

**Status:** IMPLEMENTED. Original 31-series evidence; JT02/JT03 presentation and battle updates use 33B. Unexecuted branches stay pending in the linked ledger.

**37C source:** [`JT01_Visibility`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rocket_trio_story.inc:12). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/story-additions-02/story-review-31e/owner-review-02/story-review.md).

Optional MtMoon exit net mishap with visible Jessie/Meowth and James explicitly speaking from inside the tunnel.

### JT02 — Official researchers

**Trigger:** Celadon native Hideout cleared; own scene unseen. Jessie disguise changes only after affirmative question; James leaves in disguise because no qualified true James art.

**Status:** IMPLEMENTED. Original 31-series evidence; JT02/JT03 presentation and battle updates use 33B. Unexecuted branches stay pending in the linked ledger.

**37C source:** [`JT_CeladonVisibility`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rocket_trio_story.inc:89). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/story-presentation-04/owner-review-33b-03/REVIEW.md).

Researcher disguise scene followed by an independent optional Jessie/James double battle. Decline, retry, two-usable-Pokémon and escort checks remain separate from comedy completion.

### JT03 — Fresh start, allegedly

**Trigger:** Goldenrod native state1..5, suppressed during and after takeover6+. No required Pikachu/current-party test; James departs in disguise.

**Status:** IMPLEMENTED. Original 31-series evidence; JT02/JT03 presentation and battle updates use 33B. Unexecuted branches stay pending in the linked ledger.

**37C source:** [`JT_GoldenrodVisibility`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rocket_trio_story.inc:101). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/story-presentation-04/owner-review-33b-03/REVIEW.md).

Goldenrod trio scheme; prior meeting chooses honest callback.

### JT04 — Even we know better

**Trigger:** WhirlDescent optional interaction only after actualLGfinal919 and all3canonicalreplicaresults, with known coordinator and own929unseen. Legacyexemption/nativeLugia/caught/ownership alone do not qualify. No newLG receipts or captive gifts; restoration remains uninterrupted.

**Status:** IMPLEMENTED. Original 31-series evidence; JT02/JT03 presentation and battle updates use 33B. Unexecuted branches stay pending in the linked ledger.

**37C source:** [`JT04_Visibility`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rocket_trio_story.inc:45). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/story-additions-02/story-review-31e/owner-review-02/story-review.md).

Optional return-path rescue aftermath: actual Jessie/Meowth and ordinary Seel; James explicitly calls from the passage.

### BL01 — A new field of study

**Trigger:** First Kanto HOF/credits return; native Oak and rival/Dex scenes retain priority. Optional added actor, saved Kanto rival name.

**Status:** IMPLEMENTED. Original 31-series evidence; JT02/JT03 presentation and battle updates use 33B. Unexecuted branches stay pending in the linked ledger.

**37C source:** [`CG_BlueLab`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/character_growth.inc:47). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/story-additions-02/story-review-31e/owner-review-02/story-review.md).

Blue enthusiastically starts field science under Oak.

### BL02 — The Pidgey notebook

**Trigger:** BL01 seen, BL02 unseen; completed Johto introduction2 gives later lab scene priority. No timed errand or reward.

**Status:** IMPLEMENTED. Original 31-series evidence; JT02/JT03 presentation and battle updates use 33B. Unexecuted branches stay pending in the linked ledger.

**37C source:** [`CG_BlueRoute1`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/character_growth.inc:76). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/story-additions-02/story-review-31e/owner-review-02/story-review.md).

Optional Route1 observation and expressive answer.

### BL03 — Notes from two regions

**Trigger:** BL01 seen and normalized helper confirms seeded Johto labstate>=2. Same added lab Blue actor; no new battle. Umbreon line requires actualST01GIVEN933 and NEW_COHORT921; older history gets no line.

**Status:** IMPLEMENTED. Original 31-series evidence; JT02/JT03 presentation and battle updates use 33B. Unexecuted branches stay pending in the linked ledger.

**37C source:** [`CG_BlueLabAfterIntro`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/character_growth.inc:58). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/story-additions-02/story-review-31e/owner-review-02/story-review.md).

Blue shares regional research; newly authored cohort may acknowledge Umbreon.

### SV01 — A small pause

**Trigger:** Original BurnedTower beast-release/state4; beforeGoldenrod9/theater4/Route27state3; own scene unseen. Actual regional starter chooses appropriate early lineage.

**Status:** IMPLEMENTED. Original 31-series evidence; JT02/JT03 presentation and battle updates use 33B. Unexecuted branches stay pending in the linked ledger.

**37C source:** [`CG_SilverEcruteakVisibility`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/character_growth.inc:94). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/story-additions-02/story-review-31e/owner-review-02/story-review.md).

Silver tends his tired native starter-lineage partner.

### SV02 — Waiting at the counter

**Trigger:** After original Underground battle/trust dialogue writesGoldenrod9; beforetheater4/Route27state3. No native service/healing change or timer.

**Status:** IMPLEMENTED. Original 31-series evidence; JT02/JT03 presentation and battle updates use 33B. Unexecuted branches stay pending in the linked ledger.

**37C source:** [`CG_SilverGoldenrodVisibility`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/character_growth.inc:136). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/story-additions-02/story-review-31e/owner-review-02/story-review.md).

Silver waits for his partner at Goldenrod Center.

### SV03 — Another round

**Trigger:** After native VictoryRoad lesson writesRoute27state3 AND nativehideflag0x20A1 is set by the original Route42-to-Mahogany initialization. If native actor33 remains visible, this optional scene and partner are suppressed, preserving original actors/state.

**Status:** IMPLEMENTED. Original 31-series evidence; JT02/JT03 presentation and battle updates use 33B. Unexecuted branches stay pending in the linked ledger.

**37C source:** [`CG_SilverDenVisibility`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/character_growth.inc:170). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/story-additions-02/story-review-31e/owner-review-02/story-review.md).

Willing partner responds to Silver in Dragon’s Den.

### FG01 — Seven people and one HDMI cable

**Trigger:** Native Pokédex obtained; before first Kanto Hall of Fame; current group stage is FG01.

**Status:** IMPLEMENTED. 22 primary conversations / 51 choices / 28 battle outcomes in bounded native 36-series checks. See this event’s original build and staged scope.

**37C source:** [`FG01_Interact`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:94). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md).

FG01 is a one-time arrival. The main-conversation receipt suppresses later map-load/cold-Continue spawns. Both selected responses remove the group immediately at beat90; no animated walk to the Center is implemented. The next placement is FG02 on Route2. FG01_Repeat is a source entry for an existing arrival actor, not a promise that the group remains here after completion. B cancellation executed in the original L_native_gates_fg01_first case; both chosen answers also executed. The later retired-actor repeat attempt stopped at preflight with zero inputs and is excluded as a completed interaction.

### FG02 — Brian invents camping badly

**Trigger:** Native Pokédex obtained; before first Kanto Hall of Fame; current group stage is FG02.

**Status:** IMPLEMENTED. 22 primary conversations / 51 choices / 28 battle outcomes in bounded native 36-series checks. See this event’s original build and staged scope.

**37C source:** [`FG02_Interact`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:229). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md).

### FG03 — The acoustics are incredible

**Trigger:** Original Mt. Moon fossil received; before first Kanto Hall of Fame; current group stage is FG03.

**Status:** IMPLEMENTED. 22 primary conversations / 51 choices / 28 battle outcomes in bounded native 36-series checks. See this event’s original build and staged scope.

**37C source:** [`FG03_Interact`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:368). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md).

### FG04 — Everybody has a partner now

**Trigger:** Native Pokédex obtained and Cerulean visit; before first Kanto Hall of Fame; current group stage is FG04.

**Status:** IMPLEMENTED. 22 primary conversations / 51 choices / 28 battle outcomes in bounded native 36-series checks. See this event’s original build and staged scope.

**37C source:** [`FG04_Interact`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:508). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md).

### FG05 — Tim discovers the ferry schedule

**Trigger:** Native Pokédex obtained and Vermilion visit; before first Kanto Hall of Fame; current group stage is FG05.

**Status:** IMPLEMENTED. 22 primary conversations / 51 choices / 28 battle outcomes in bounded native 36-series checks. See this event’s original build and staged scope.

**37C source:** [`FG05_Interact`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:648). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md).

### FG06 — Two very different coaching styles

**Trigger:** Native Pokédex obtained and Route11 visit; before first Kanto Hall of Fame; current group stage is FG06.

**Status:** IMPLEMENTED. 22 primary conversations / 51 choices / 28 battle outcomes in bounded native 36-series checks. See this event’s original build and staged scope.

**37C source:** [`FG06_Interact`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:765). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md).

### FG07 — Manifesting a room

**Trigger:** Original Celadon Rocket clearance flag; before first Kanto Hall of Fame; current group stage is FG07.

**Status:** IMPLEMENTED. 22 primary conversations / 51 choices / 28 battle outcomes in bounded native 36-series checks. See this event’s original build and staged scope.

**37C source:** [`FG07_Interact`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:911). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md).

### FG08 — Quiet outside Lavender

**Trigger:** Original Poké Flute receipt; before first Kanto Hall of Fame; current group stage is FG08.

**Status:** IMPLEMENTED. 22 primary conversations / 51 choices / 28 battle outcomes in bounded native 36-series checks. See this event’s original build and staged scope.

**37C source:** [`FG08_Interact`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:1088). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md).

### FG09 — The group gets actual responsibilities

**Trigger:** Native Pokédex obtained and Fuchsia visit; before first Kanto Hall of Fame; current group stage is FG09.

**Status:** IMPLEMENTED. 22 primary conversations / 51 choices / 28 battle outcomes in bounded native 36-series checks. See this event’s original build and staged scope.

**37C source:** [`FG09_Interact`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:1219). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md).

### FG10 — A very bad job interview

**Trigger:** Original Saffron Rocket clearance AND Silph Master Ball receipt; before first Kanto Hall of Fame; current group stage is FG10.

**Status:** IMPLEMENTED. 22 primary conversations / 51 choices / 28 battle outcomes in bounded native 36-series checks. See this event’s original build and staged scope.

**37C source:** [`FG10_Interact`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:1362). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md).

### FG11 — The television in the water

**Trigger:** Original Mansion Secret Key pickup flag, independent of current item possession; before first Kanto Hall of Fame; current group stage is FG11.

**Status:** IMPLEMENTED. 22 primary conversations / 51 choices / 28 battle outcomes in bounded native 36-series checks. See this event’s original build and staged scope.

**37C source:** [`FG11_Interact`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:1461). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md).

### FG12 — Seven terrible spectators

**Trigger:** Kanto FLAG_SYS_GAME_CLEAR AND native Pallet Oak scene variable>=3, after his postcredits rating/referral dispatch; current group stage is FG12.

**Status:** IMPLEMENTED. 22 primary conversations / 51 choices / 28 battle outcomes in bounded native 36-series checks. See this event’s original build and staged scope.

**37C source:** [`FG12_Interact`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:1586). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md).

### FG13 — No second character creation

**Trigger:** Johto state seeded and existing Elm lab state>=2; before Johto Hall of Fame; current group stage is FG13.

**Status:** IMPLEMENTED. 22 primary conversations / 51 choices / 28 battle outcomes in bounded native 36-series checks. See this event’s original build and staged scope.

**37C source:** [`FG13_Interact`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:1705). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md).

### FG14 — Xavier reads the room

**Trigger:** Johto state seeded and existing Elm lab state>=2 plus actual Ruins visit; before Johto Hall of Fame; current group stage is FG14.

**Status:** IMPLEMENTED. 22 primary conversations / 51 choices / 28 battle outcomes in bounded native 36-series checks. See this event’s original build and staged scope.

**37C source:** [`FG14_Interact`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:1819). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md).

### FG15 — Jon learns one useful volume

**Trigger:** Johto Azalea state>=3 AND original Azalea Rockets hidden after Slowpoke Well; before Johto Hall of Fame; current group stage is FG15.

**Status:** IMPLEMENTED. 22 primary conversations / 51 choices / 28 battle outcomes in bounded native 36-series checks. See this event’s original build and staged scope.

**37C source:** [`FG15_Interact`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:1934). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md).

### FG16 — The move has a name

**Trigger:** Johto state seeded; Goldenrod state1..5 OR>=11; never during occupation states6..10; before Johto Hall of Fame; current group stage is FG16.

**Status:** IMPLEMENTED. 22 primary conversations / 51 choices / 28 battle outcomes in bounded native 36-series checks. See this event’s original build and staged scope.

**37C source:** [`FG16_Interact`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:2052). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md).

### FG17 — A reflection that waits

**Trigger:** Johto state seeded AND original released-beasts flag; before Johto Hall of Fame; current group stage is FG17.

**Status:** IMPLEMENTED. 22 primary conversations / 51 choices / 28 battle outcomes in bounded native 36-series checks. See this event’s original build and staged scope.

**37C source:** [`FG17_Interact`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:2178). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md).

### FG18 — Tim books the right trip

**Trigger:** Johto state seeded AND original Ampharos-healed receipt; before Johto Hall of Fame; current group stage is FG18.

**Status:** IMPLEMENTED. 22 primary conversations / 51 choices / 28 battle outcomes in bounded native 36-series checks. See this event’s original build and staged scope.

**37C source:** [`FG18_Interact`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:2281). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md).

### FG19 — Nobody yells at the frightened Pokémon

**Trigger:** Johto state seeded AND Goldenrod state>=11 after native Director rewards; before Johto Hall of Fame; current group stage is FG19.

**Status:** IMPLEMENTED. 22 primary conversations / 51 choices / 28 battle outcomes in bounded native 36-series checks. See this event’s original build and staged scope.

**37C source:** [`FG19_Interact`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:2404). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md).

### FG20 — We actually know what we are doing

**Trigger:** Johto state seeded, regional badge8 AND Blackthorn state>=4 after Clair Dragon’s Den TM/departure; current group stage is FG20.

**Status:** IMPLEMENTED. 22 primary conversations / 51 choices / 28 battle outcomes in bounded native 36-series checks. See this event’s original build and staged scope.

**37C source:** [`FG20_Interact`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:2505). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md).

### FG21 — Everybody goes home

**Trigger:** Johto state seeded AND actual JOHTO_FLAG_SYS_GAME_CLEAR (0x2893); farewell not completed; current group stage is FG21. No legendary-catch or friend-win prerequisite.

**Status:** IMPLEMENTED. 22 primary conversations / 51 choices / 28 battle outcomes in bounded native 36-series checks. See this event’s original build and staged scope.

**37C source:** [`FG21_Interact`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:2639). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md).

### FG22 — Visitors with too much luggage

**Trigger:** Johto state seeded AND actual regional game-clear receipt AND completed farewell AND reunion armed by a later map load outside the farewell campsite map, followed by return. Cold Continue on the departure map does not arm it.

**Status:** IMPLEMENTED. 22 primary conversations / 51 choices / 28 battle outcomes in bounded native 36-series checks. See this event’s original build and staged scope.

**37C source:** [`FG22_Interact`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:2848). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md).

### B01 — Brian — Early

**Trigger:** Optional at FG02. Native blackout handling and separate victory/loss follow-up state.

**Status:** IMPLEMENTED. Native win and loss executed in the original 36-series staged tests; portrait acceptance remains separate.

**37C source:** [`FG_Battle01`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:3047). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md).

Rattata Lv.6

### B02 — Jon — Early

**Trigger:** Optional at FG03. Native blackout handling and separate victory/loss follow-up state.

**Status:** IMPLEMENTED. Native win and loss executed in the original 36-series staged tests; portrait acceptance remains separate.

**37C source:** [`FG_Battle02`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:3083). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md).

Mankey Lv.12

### B03 — Nick — Early

**Trigger:** Optional at FG06. Native blackout handling and separate victory/loss follow-up state.

**Status:** IMPLEMENTED. Native win and loss executed in the original 36-series staged tests; portrait acceptance remains separate.

**37C source:** [`FG_Battle03`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:3119). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md).

Poliwag Lv.20

### B04 — Lb — Early

**Trigger:** Optional at FG06. Native blackout handling and separate victory/loss follow-up state.

**Status:** IMPLEMENTED. Native win and loss executed in the original 36-series staged tests; portrait acceptance remains separate.

**37C source:** [`FG_Battle04`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:3153). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md).

Jigglypuff Lv.20

### B05 — X — Early

**Trigger:** Optional at FG07. Native blackout handling and separate victory/loss follow-up state.

**Status:** IMPLEMENTED. Native win and loss executed in the original 36-series staged tests; portrait acceptance remains separate.

**37C source:** [`FG_Battle05`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:3191). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md).

Oddish Lv.27 / Paras Lv.27

### B06 — Tim — Early

**Trigger:** Optional at FG09. Native blackout handling and separate victory/loss follow-up state.

**Status:** IMPLEMENTED. Native win and loss executed in the original 36-series staged tests; portrait acceptance remains separate.

**37C source:** [`FG_Battle06`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:3229). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md).

Spearow Lv.32 / Krabby Lv.32

### B07 — Ham — Early

**Trigger:** Optional at FG16. Native blackout handling and separate victory/loss follow-up state.

**Status:** IMPLEMENTED. Native win and loss executed in the original 36-series staged tests; portrait acceptance remains separate.

**37C source:** [`FG_Battle07`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:3263). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md).

Psyduck Lv.35 / Sentret Lv.35

### FINAL_BRIAN — Brian — Final

**Trigger:** Optional at FG20, FG21, FG22. Native blackout handling and separate victory/loss follow-up state.

**Status:** IMPLEMENTED. Native win and loss executed in the original 36-series staged tests; portrait acceptance remains separate.

**37C source:** [`FG_Battle08`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:3313). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md).

Raticate Lv.55 / Slowbro Lv.56

### FINAL_X — X — Final

**Trigger:** Optional at FG20, FG21, FG22. Native blackout handling and separate victory/loss follow-up state.

**Status:** IMPLEMENTED. Native win and loss executed in the original 36-series staged tests; portrait acceptance remains separate.

**37C source:** [`FG_Battle09`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:3353). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md).

Bellossom Lv.56 / Parasect Lv.56

### FINAL_TIM — Tim — Final

**Trigger:** Optional at FG20, FG21, FG22. Native blackout handling and separate victory/loss follow-up state.

**Status:** IMPLEMENTED. Native win and loss executed in the original 36-series staged tests; portrait acceptance remains separate.

**37C source:** [`FG_Battle10`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:3393). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md).

Fearow Lv.56 / Kingler Lv.57

### FINAL_LB — Lb — Final

**Trigger:** Optional at FG20, FG21, FG22. Native blackout handling and separate victory/loss follow-up state.

**Status:** IMPLEMENTED. Native win and loss executed in the original 36-series staged tests; portrait acceptance remains separate.

**37C source:** [`FG_Battle11`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:3433). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md).

Wigglytuff Lv.56 / Murkrow Lv.56

### FINAL_NICK — Nick — Final

**Trigger:** Optional at FG20, FG21, FG22. Native blackout handling and separate victory/loss follow-up state.

**Status:** IMPLEMENTED. Native win and loss executed in the original 36-series staged tests; portrait acceptance remains separate.

**37C source:** [`FG_Battle12`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:3477). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md).

Poliwhirl Lv.56 / Graveler Lv.57

### FINAL_JON — Jon — Final

**Trigger:** Optional at FG20, FG21, FG22. Native blackout handling and separate victory/loss follow-up state.

**Status:** IMPLEMENTED. Native win and loss executed in the original 36-series staged tests; portrait acceptance remains separate.

**37C source:** [`FG_Battle13`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:3517). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md).

Primeape Lv.57 / Noctowl Lv.56

### FINAL_HAM — Ham — Final

**Trigger:** Optional at FG20, FG21, FG22. Native blackout handling and separate victory/loss follow-up state.

**Status:** IMPLEMENTED. Native win and loss executed in the original 36-series staged tests; portrait acceptance remains separate.

**37C source:** [`FG_Battle14`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:3557). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md).

Golduck Lv.56 / Furret Lv.55

## New Friends handoff: proposed, not playable in 37C

The October 19 Friends handoff is design input awaiting implementation: FG-A–FG-G, dialogue/voice rework, new final-battle lines, repeat-early-battle changes, bespoke Nao/Stranger art and other listed polish. Current 37C still has 22 scene receipts and required-zero bits 0x956–0x95F. The proposed new state allocation and 29-placement adoption must be audited before use.

| Draft ID | Proposed scene | Proposed location / gate | Current status |
| --- | --- | --- | --- |
| FG-A | Tim finds the resort | One Island / Ember Spa; Proposed first Sevii-trip completion | NOT IMPLEMENTED / gameplay NOT RUN |
| FG-B | The road nobody paved | Indigo western road; Proposed post-Oak westbound crossing | NOT IMPLEMENTED / gameplay NOT RUN |
| FG-C | The tower that sways | Violet / Sprout Tower exterior; Proposed Zephyr Badge | NOT IMPLEMENTED / gameplay NOT RUN |
| FG-D | Someone louder than Jon | Cianwood beach; Proposed Cianwood arrival | NOT IMPLEMENTED / gameplay NOT RUN |
| FG-E | The lake that was told to be angry | Lake of Rage shore; Proposed Mahogany hideout clearance | NOT IMPLEMENTED / gameplay NOT RUN |
| FG-F | Ham goes first | Ice Path safe entrance floor; Proposed post-Radio / pre-Clair window | NOT IMPLEMENTED / gameplay NOT RUN |
| FG-G | Up six | Ecruteak pond; Proposed visit after FG22 | NOT IMPLEMENTED / gameplay NOT RUN |

[Complete October 19 handoff]([LOCAL_WORKSPACE]/docs/friends-arc-and-asset-handoff.md) · [Draft new dialogue and final-battle lines]([LOCAL_WORKSPACE]/docs/friends-new-event-scripts.md).

No draft is inserted into the current event directory as an implemented scene. Current source was checked for the 22-scene constant, required-zero bits and absence of the proposed placement table/replacement farewell text. The sprite pilots and all optional art changes still need their own implementation/acceptance record.

## Saves, resource limits and unfinished qualification

- No full natural Kanto/Sevii/Johto campaign or Delta/device qualification is established.
- All screenshots retain their actual ROM/build and staged checkpoint labels. No new gameplay was run for this documentation refresh.
- SaveBlock1 remains 15,868 / 15,872 bytes: four bytes free. The protected 256-byte reserve is unchanged; the FireRed roamer fidelity defect remains open.
- General arbitrary-save compatibility, owner acceptance of all artwork, special-sector/Hall-of-Fame atomicity and the reports’ remaining graphics/runtime budget cases remain open.

The companion’s bike attachment adds 880 ROM bytes versus 37A, no static RAM or save field. Main save headroom is a different budget from ROM storage. Nothing in this documentation refresh consumes either.

## Evidence and maintenance

[Read-only reconciliation audit]([LOCAL_WORKSPACE]/_local/evidence/campaign-review-refresh-01/source-audit.json) pins the exact 37C ROM and current source entry labels. The historical event catalogs remain intact. The local HTML generator pins this guide and its structured navigation input.

Regenerate the offline room using the bundled Node command in [the review-room README]([LOCAL_WORKSPACE]/scripts/review_hub/README.md). Keep private screenshots, ROMs and saves under ignored `_local/`. No original evidence, game source, personal save or other workstream is changed by this refresh.
