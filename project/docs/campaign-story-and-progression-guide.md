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

Trail begins as the same Kanto trainer who will eventually reach Johto. Eligible ordinary new games receive Pikachu in Oak’s lab. Blue receives Eevee, the ball Oak kept for him (“Fine. EEVEE’s with me, then!”), loses the first battle because he and Eevee “only just met”, and when the Parcel comes back Oak asks how Pikachu is getting along; games that began with a classic starter keep FireRed’s lines. After the Parcel and the Pokédex, the first walk north onto Route 1 brings the Pidgey rescue and the Ho-Oh flyby; the Stranger comes down the road straight after it, sends the player to the new Pokédex (it has no entry for the bird) and asks his question.

**Progression:**

1. Complete the native starter grant and naming, then the opening rival sequence. Both win and loss paths retain recovery and lab exit.
2. Collect Oak’s Parcel in Viridian and return it for the original Pokédex ceremony.
3. Walking north again, help shelter the Pidgey on Route 1; Ho-Oh flies over and the Stranger follows (both play by themselves).

**Connected events:**

| ID | Event / actual entry label | Exact dialogue, images and result record |
| --- | --- | --- |
| ST01 | First partner — [`ST01_LabVisibility`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/starter_recruitment.inc:255) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/story-additions-02/story-review-31e/owner-review-02/story-review.md) |
| RB01 | Opening sky — [`RB_TryOpening`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rainbow_story.inc:40) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/story-additions-02/story-review-31e/owner-review-02/story-review.md) |
| RB02 | Oak records it — [`RB_OakBird`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rainbow_story.inc:118) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html) |

Existing saves retain their real starter and history. The flyby is a fresh-cohort event, not a scene retroactively invented for older trainers. Incompatible challenge/randomizer options retain the supported native starter flow.

## 02. The road north

**Where:** Viridian → Route 2 → Viridian Forest → Pewter.

The first badge journey runs alongside the strangers’ arrival. The first time the player enters Viridian after the Pokédex, distorted flashes tear the sky over the south road, Giratina drops seven adult friends onto it and leaves them stranded; they argue it out, ask the player where they are and head into town. Their first campsite begins taking shape on Route 2. Nao introduces her bell and her search for the rainbow bird.

**Progression:**

1. Travel north through Viridian Forest and earn Brock’s Boulder Badge.
2. The Stranger's first meeting (Route 1) and the friends' arrival (Viridian) play by themselves; their later scenes, and Nao, stay optional.

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

The native Safari, Surf, Strength, gyms and Silph campaign remain. The friends take on small responsibilities and conduct a disastrous interview. At Silph, the Stranger’s disguise briefly slips; Rocket’s copied-call equipment also connects to Nao’s later story. On the Silence Bridge (Route 12), the fisher CHIP, once beaten, saw something gold over the forest weeks ago, if the player saw the opening’s bird (KR-120).

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

The Mansion journals keep their original account. After the Secret Key is found, Mewtwo reveals the identity behind the Stranger and leaves the eventual cave encounter as a choice. The friends see a hint of home reflected in the water. Between Silph’s wavering veil (MW05) and the reveal (MW06), a swimmer off Route 21’s north shore saw a man in a coat standing on the water, heading for Cinnabar. A broken Rocket tape recorder lies by each bird’s room: CALL SAMPLE 1 by Articuno (Seafoam Islands B4F), 2 by Zapdos (the Power Plant), 3 by Moltres (Mt. Ember’s summit). On One Island a traveller, for a player who saw the opening’s bird, heard a gold bird crossed the sea weeks ago, heading west; their little brother drew it with a tail like a rainbow (KR-120).

**Progression:**

1. Find the original Mansion Secret Key and progress through Blaine.
2. Keep Bill’s native first Sevii trip, its existing tasks and return path.

**Connected events:**

| ID | Event / actual entry label | Exact dialogue, images and result record |
| --- | --- | --- |
| MW06 | Cinnabar reveal — [`MW06_Visibility`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rainbow_story.inc:518) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html) |
| FG11 | The television in the water — [`FG11_Interact`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:1461) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md) |

Mew remains a sparse observer, not a reward from this plot. **FG-A Tim finds the resort** (KR-124): once Bill's first Sevii trip is over (One Island's Center scene at 3 or more), while the Friends are still in Kanto (FG11, or FG12 after the League; FG13 retires it), Tim, Brian, Ham and Nick are on Kindle Road below Ember Spa with Spearow, a local and Slowpoke (`FGA_Interact`). Tim wants nightlife, the local says most people go to bed, and Tim ends up reading the ferry board and paying for the rooms; a choice ("Sounds like a vacation" / "You sound like a tour guide") and the four go into the spa. Optional, no battle, nothing given; receipt 0x956. A player who takes Bill's trip after the League still finds them (coordinator's call, 10 November). Original Articuno, Zapdos and Moltres stay in Seafoam, the Power Plant and Mt. Ember.

## 09. Kanto Champion

**Where:** Viridian Gym → Route 22/23 → Indigo Plateau.

Blue remains the original competitive Kanto rival through the first championship. The native final gym, Victory Road, Elite Four, Champion sequence, credits and Pallet return remain the main story. Mewtwo’s Route 22 question can fall before or after the League. After the friends’ FG11 and before the League, the Indigo Plateau Center’s guide adds that seven strange people asked where they could watch the LEAGUE on TV, and one of them was very loud (FG12’s set-up, KR-120). After the League, until the Rocket Warehouse is cleared, Jessie, James and Meowth stand outside it on Five Island: they heard the admin is still hiring, find out the pay is pride, and leave (KR-120).

**Progression:**

1. Earn the remaining native Kanto badges and clear the first Kanto League.
2. Home after the Hall of Fame: Mom watched it on TV and says Oak came looking for them. Outside the door Oak, who was at the Plateau, walks the Champion to his lab, where one scene carries the whole hand-off (KR-113): Oak built the Pokédex with only the Pokémon he knew in Kanto and asks for help recording the rest; Blue walks in (“You’re asking {PLAYER} for help and not your own grandson?”); in the Pikachu start Oak notices any of Bulbasaur, Charmander and Squirtle the player met on the road; the National Dex upgrade; room in it now, perhaps for the rainbow bird (a player who never told Oak about the Pidgey and the bird tells him here); Blue leaves to pack for Oak’s next field survey; then Oak sends the player to Elm in New Bark Town with the road there (or, if they met Elm first, says he heard), and passes on Nao’s news unless they found her in Ecruteak already (by name as a friend if they met in Kanto, as a bell keeper from Ecruteak if not). Each is told once. Later talks give the Pokédex rating and one reminder line; Pallet’s guide only points the way.

**Connected events:**

| ID | Event / actual entry label | Exact dialogue, images and result record |
| --- | --- | --- |
| MW07 | Route22 question — [`MW07_Visibility`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rainbow_story.inc:545) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html) |
| FG12 | Seven terrible spectators — [`FG12_Interact`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:1586) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md) |
| BL01 | A new field of study — [`CG_BlueLab`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/character_growth.inc:47) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/story-additions-02/story-review-31e/owner-review-02/story-review.md) |
| BL02 | The Pidgey notebook — [`CG_BlueRoute1`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/character_growth.inc:76) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/story-additions-02/story-review-31e/owner-review-02/story-review.md) |
| RB07 | Oak sends you west — [`RB_OakReferral`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rainbow_story.inc:121) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html) |

After losing the championship Blue is content and excited about science. BL01 is at Oak’s lab; BL02 is on Route 1 before the completed Elm introduction. These scenes do not remove his native battles or rematches. The later Sevii/Celio quest and Cerulean Cave can be completed before heading west or after returning; Johto’s championship is not an added Mewtwo prerequisite. Since 2026-11-09 (story copy C4, KR-115) Cerulean Cave’s guard also lets in a Kanto Champion who has heard Mewtwo on Route 22 (MW07); Celio’s errand stays the way in for a player who never met the stranger. Once the Ruby and the Sapphire are in, Celio’s Network Machine links the Sevii Islands with JOHTO through GOLDENROD, Bill’s hometown (FireRed’s link to Lanette in Hoenn is gone, and the machine starts no roamer): Celio, the machine and the Battle Girl in One Island’s Center say so (story copy H6, KR-112; replay tests `one island …`).

## 10. West, down to the water

**Where:** Indigo western road → Route 27 coast → New Bark.

Construction workers keep the westbound road closed until the native Kanto championship. It then opens as a forest road with coastal stairs. Surf west across the original New Bark water connection; the route also works in reverse.

**Progression:**

1. Return to Indigo’s western edge after the Kanto championship.
2. Follow the outdoor road downhill, descend to Route 27’s shore and Surf west to New Bark.
3. Bring the existing Surf capability; this route grants no HM, badge, Pokémon or level adjustment.

Johto initializes once without resetting Kanto. Native Kanto clear is the actual road gate; Oak supplies the story directions. The obsolete cave-only test slice is historical. **FG-B The road nobody paved** (KR-125): once the player is Champion and Oak has given the Johto directions, while the Friends are at FG12, X, Jon, Nick and Brian (and Mankey) are on League West Pass, south of the road (`FGB_Interact`). X has the plan (two days, one river, one town, four days of food), Jon yells at the mountain until Mankey yells with him, and Brian's living room shows in a puddle, as at Cinnabar; a choice ("Good luck out there" / "See you in Johto") and they head west. That's how the seven reach New Bark before FG13; when FG-B was seen, Ham says so in FG13 ("We walked. Jon yelled at a mountain.", the handoff's FG13 rework line). Optional, no battle, nothing given; receipt 0x957.

[Progression / evidence reference]([LOCAL_WORKSPACE]/docs/natural-johto-journey-results.md).

[Progression / evidence reference]([LOCAL_WORKSPACE]/docs/johto-campaign-integration-requirements.md).

## 11. A visiting Champion, not a new character

**Where:** New Bark → Cherrygrove → Mr. Pokémon → Violet.

Elm welcomes Oak’s visiting trainer and gives the adapted research errand. Before the errand he shows the three Pokémon native to Johto (Chikorita, Cyndaquil, Totodile, level 5) and the player takes one. Gold, a New Bark trainer, comes in for a partner of his own: he takes the one the player’s is strong against and battles the player. Cherrygrove’s boy has heard a CHAMPION from KANTO came to JOHTO and wonders what they’re like; on Route 31 the bug catcher WADE notices the companion PIKACHU (“You don’t see many around here”) before his battle (KR-120). The third is the one Silver later steals, the one strong against the player’s. After the Zephyr Badge Gold waits outside Violet’s Gym: Falkner has beaten him twice, and he asks the Kanto Champion for a battle. The original Johto errand, stolen-partner/rival introduction and early badge journey continue with the same collection. The group reaches New Bark independently.

**Progression:**

1. Accept Elm’s introduction, choose a Johto partner, battle Gold, then follow the native Mr. Pokémon errand and return sequence.
2. Continue through the original Johto rival and Violet/Falkner progression. After the Zephyr Badge, Gold’s optional rematch waits by Violet’s Gym until the second Johto badge.
3. Blue’s optional lab research follow-up is available back in Kanto once Elm has been met.

**Connected events:**

| ID | Event / actual entry label | Exact dialogue, images and result record |
| --- | --- | --- |
| RB08 | Elm's welcome — [`RB_ElmBird`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rainbow_story.inc:241) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html) |
| FG13 | No second character creation — [`FG13_Interact`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:1705) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md) |
| BL03 | Notes from two regions — [`CG_BlueLabAfterIntro`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/character_growth.inc:58) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/story-additions-02/story-review-31e/owner-review-02/story-review.md) |
| GD01 | Gold outside Violet’s Gym — [`CG_GoldViolet`](../../engine/data/scripts/character_growth.inc) | Replay tests `violet gold …` (eight) |

Kanto and Johto rival names, badges and story state are independent. Blue’s Eevee→Umbreon selection belongs only to the new Pikachu cohort after BL03; the later actual enemy Umbreon battle remains NOT RUN. **FG-C The tower that sways** (KR-126): once the Zephyr Badge is won, while the Friends are at FG13 (New Bark) or FG14 (the Ruins, which are open before the badge), X, Ham and LB sit in front of Sprout Tower, north of the pond (Gold waits by the Gym, south of it), with Sentret, Oddish and a Sage sweeping the step (`FGC_Interact`). X has budgeted three hours to understand the swaying pillar, Ham has sat still the whole time, and the Sage tells X a plan may sway without falling; a choice ("Sit with Ham" / "Leave them to it"), and the three stay seated until the player leaves Violet. Optional, no battle, nothing given; receipt 0x958.

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

Burned Tower’s native events release the beasts and unlock Nao’s explanation of the towers. A player Nao met in Kanto is greeted first (“PROF.OAK thought you might”); one she never met hears her introduction: she keeps the bells here, and came home from Kanto not long ago after asking about a bird. Silver pauses for his exhausted partner. Gold waits outside the Center: he beat Falkner at last, then found Silver coming out of the Burned Tower and lost to him, and saw him make his Pokémon rest before it battled again. At the coast, healing Amphy stays the real objective; Nao notices care for the Pokémon already here and Tim becomes useful at the harbor.

**Progression:**

1. Follow the native Burned Tower/Ecruteak and Morty progression. After the Burned Tower, Gold’s optional battle waits outside Ecruteak’s Center until the Fog Badge.
2. Continue the lighthouse, Cianwood medicine/Chuck and Amphy/Jasmine progression as their native gates allow.

**Connected events:**

| ID | Event / actual entry label | Exact dialogue, images and result record |
| --- | --- | --- |
| RB09 | Ecruteak truth — [`RB_NaoJohtoIntro`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rainbow_story.inc:273) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html) |
| SV01 | A small pause — [`CG_SilverEcruteakVisibility`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/character_growth.inc:94) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/story-additions-02/story-review-31e/owner-review-02/story-review.md) |
| GD02 | Gold outside Ecruteak’s Center — [`CG_GoldEcruteak`](../../engine/data/scripts/character_growth.inc) | Replay tests `ecruteak gold …` (nine) |
| FG17 | A reflection that waits — [`FG17_Interact`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:2178) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md) |
| RB10 | Amphy callback — [`RB_OlivineVisibility`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rainbow_story.inc:359) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html) |
| FG-D | Someone louder than Jon — [`FG_D_Interact`](../../engine/data/scripts/friends_story.inc) | Replay tests `cianwood the friends meet someone louder than jon`, `cianwood the friends answer what happened to jon`, `cianwood no friends before the fog badge`, `cianwood no friends after the johto league` |
| FG18 | Tim books the right trip — [`FG18_Interact`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:2281) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md) |

FG-D plays on Cianwood’s beach, by the water below the Pokémon Center, while the friends are at Ecruteak's or Olivine's placement. The guide does not turn the friends’ travel into player transport rewards.

## 14. Silence the signal

**Where:** Lake of Rage → Mahogany → Goldenrod Radio Tower.

The original red Gyarados, Mahogany hideout and Radio Tower battles retain their role. Nao’s copied recording is switched off through a later conversation. Silver waits at a Center, while the friends help frightened Pokémon after the takeover.

**Rocket’s power struggle (KR-110).** Giovanni quit at Viridian weeks ago, beaten by the player; in Johto his branch split instead of stopping. Archer wants him back and takes the Radio Tower to call him home on every radio; Ariana, the “interim boss” of Mahogany, wants Rocket strong without him; Proton runs the money; Petrel copies Giovanni’s voice to keep the grunts in line; the scientists, several from Silph, follow whoever funds the work. Kurt, Proton, the Violet gentleman, Silver in Azalea (a battle that carries on if the player loses: his “Some CHAMPION.” plays, the party is healed and the story goes on), the hideout and Radio Tower lines and the Pokégear broadcast each show a piece of it. Beaten, Archer disbands Rocket “like GIOVANNI did before me” and no longer answers for anyone who keeps the name; Ariana keeps it, and Black Tide is hers (LG01, LG02, LG06). The Five Island warehouse admin, met after the Radio Tower, has heard Archer quit too and calls it lies. In the Celebi scenes Giovanni recognises the child who beat him weeks ago, and Silver on Route 22 knows the kid who beat his father.

**Progression:**

1. Resolve native Lake of Rage/Mahogany progression, Pryce and the Radio Tower takeover.
2. After clearance, optional conversations provide the recording aftermath and the coastal Whirl warnings.

**Connected events:**

| ID | Event / actual entry label | Exact dialogue, images and result record |
| --- | --- | --- |
| RB11 | Lance signal thought — folded — [`RB_Recording`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rainbow_story.inc:291) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html) |
| RB16 | Copied calls at the Lake of Rage — [`RB_NaoLake`](../../engine/data/scripts/rainbow_story.inc) | Replay tests `lake of rage nao …` (five), `lake of rage no nao …` (three) |
| RB12 | Silence the copy — [`RB_RadioAftermath`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rainbow_story.inc:660) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html) |
| RB13 | Welcome — [`RB_Welcome`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rainbow_story.inc:311) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html) |
| RB15 | Fuji hears from Nao (back in Lavender) — [`RB_FujiNaoLetter`](../../engine/data/scripts/rainbow_story.inc) | Replay tests `lavender fuji hears from nao`, `lavender fuji keeps naos letter`, `lavender fuji asks about the flute after the letter`, `lavender fuji asks about the flute` |
| JT05 | Guard duty (the trio in Goldenrod’s warehouse during the takeover) — [`JT05_GuardDuty`](../../engine/data/scripts/rocket_trio_story.inc) | Replay tests `goldenrod warehouse …` (six) |
| SV02 | Waiting at the counter — [`CG_SilverGoldenrodVisibility`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/character_growth.inc:136) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/story-additions-02/story-review-31e/owner-review-02/story-review.md) |
| FG19 | Nobody yells at the frightened Pokémon — [`FG19_Interact`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:2404) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md) |
| LG01 | Coastal warnings — [`BlackTide_CoastalWarning`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/johto/adapted/WhirlIslands_LugiaChamber_hns.inc:1009) | [Original owner review]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html) |

RB11 is folded into RB12; there is no separate implemented Lance scene. Nao’s Ready/Later welcome respects native Ho-Oh encounter state. FG-E at Lake of Rage is proposed only.

## 15. The last badge and a choice of opponents

**Where:** Ice Path → Blackthorn → Dragon’s Den.

The native path through Ice Path, Clair and Dragon’s Den remains. Clair knows the player from Lance: “LANCE told me a KANTO trainer beat him. So you’re the one. Don’t expect me to be impressed.” (KR-120). Seven final friend opponents become individually selectable after the eighth regional badge and the completed native Den follow-up. Silver’s later quiet question waits for his verified native milestone.

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

**Where:** Route 26 → Reception Gate → Johto’s Victory Road → LAUREL PLATEAU → Hall of Fame.

The original late Johto rival, League approach, Elite Four and Champion progression remains independent of Kanto’s championship. Optional friends or legendary captures do not substitute for clearing Johto’s own Hall of Fame. Afterwards Gold waits outside Elm’s lab in New Bark with five badges, for one last battle: he didn’t shout once.

Johto’s plateau is LAUREL PLATEAU, Johto’s own League (KR-111): its sign, its map name and town-map place (a map section of its own, apart from Kanto’s INDIGO PLATEAU, which keeps its name), Elm’s directions after the eighth badge and the Blackthorn Center’s gentleman. The new hall borrowed Kanto’s strongest, and the people say so once each: the Center’s trainer tells the history (Johto’s trainers used to cross the mountains to Indigo; now Johto has a League of its own and Lance came home to be its Champion); Lance at the Lake of Rage remembers the player from Indigo Plateau and his Dragonite; Koga keeps Fuchsia’s Gym and a seat here; Bruno sits in both halls; Lance in the Champion’s room is Johto’s Champion with the team he keeps for it, and in the Hall of Fame two halls keep the player’s name. Oak at Olivine’s port greets a Champion of two Leagues.

**Progression:**

1. Complete the native Johto League approach and League.
2. Johto’s actual game-clear receipt enables the farewell, Nao’s later letter chain and Gold’s last battle outside Elm’s lab (optional).

**Connected events:**

| ID | Event / actual entry label | Exact dialogue, images and result record |
| --- | --- | --- |
| GD03 | Gold’s last battle in New Bark — [`CG_GoldNewBark`](../../engine/data/scripts/character_growth.inc) | Replay tests `new bark gold …` (seven) |

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

Mewtwo is listed here as an open sidequest, not gated behind the Johto League: only the original Kanto/Sevii access conditions apply. Since 2026-11-10 MW09 plays by itself as the player walks out of the cave's mouth (it was a spot to check). Original Sevii, Navel Rock and other existing content retain their gates. No extra Celebi/beast/Gen 3+ legendary chapter or third region is implemented in this pass.

## Event directory and exact trigger rules

These entries were reconciled to actual 37C labels. They describe implemented source; gameplay evidence remains scoped to the original linked report. RB11 is folded into RB12, not a separate playable event.

### RB01 — Opening sky

**Trigger:** Route1 map transition adopts supported state; FRESH_COHORT true, OPENING_SEEN false, Pokédex received (moved from before the Pokédex on 2026-10-25). Sets VAR_TEMP_E1 for the frame table. Completion requires successful renderer; failed start retains retry. MW01 follows in the same scene.

**Status:** IMPLEMENTED. Historical 30-series native scope; see original per-event result. No 37C replay claimed.

**37C source:** [`RB_TryOpening`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rainbow_story.inc:40). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/story-additions-02/story-review-31e/owner-review-02/story-review.md).

Pidgey shelter and early Ho-Oh flyby after the original opening.

### RB02 — Oak records it

**Trigger:** Normal Oak interaction calls RB_OakStory. Supported adoption, Dex received, before the Kanto League, OPENING_SEEN set. It plays once and mentions the Pidgey too (`FLAG_RB_OAK_HEARD_BIRD`, FireRed's unused `0x0B0`; KR-113); a player who never tells Oak before the League tells him in the National Dex scene, so Oak’s notes hold the sighting before BL02 and RB08.

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

**Trigger:** The end of the National Dex scene after the Kanto League (`PalletTown_ProfessorOaksLab_EventScript_OakSendsChampionToElm`, KR-113), once (`FLAG_OAK_GAVE_JOHTO_DIRECTIONS`). OPENING_SEEN chooses “that bird flew west, didn’t it? Toward JOHTO”; otherwise “one more thing”. A player who already met Elm hears that Oak heard instead of the road. A save whose scene played before KR-113 hears it once on its next talk. Later talks: the rating, then one reminder line.

**Status:** IMPLEMENTED. Historical 30-series native scope; see original per-event result. No 37C replay claimed.

**37C source:** [`RB_OakReferral`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rainbow_story.inc:121). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html).

The referral, the road (Indigo Plateau, the road west of the League, Route 27, Surf west to New Bark Town) and Nao’s news, told once in the scene. Nao’s news plays only if the player hasn’t met her in Ecruteak yet (`FLAG_RB_ECRUTEAK_TRUTH_SEEN`): “Oh! Your friend NAO came by while you were away. She asked why a bird like yours has no entry. I couldn’t tell her. She’s gone home to ECRUTEAK, in JOHTO. She hopes you’ll visit.” if `FLAG_RB_NAO_INTRODUCED` (without the bird line if the bird wasn’t seen), otherwise, with the bird seen, “Oh! A bell keeper came by while you were away. NAO, from ECRUTEAK. She has asked all over KANTO about a bird like yours. She’s gone home.” Replay tests `pallet oak passes on naos news`, `pallet oak tells of a bell keeper from ecruteak` (2026-10-31; since KR-113 they play the National Dex scene from its start and end on Nao’s news).

### RB08 — Elm's welcome

**Trigger:** Existing Elm intro owner calls RB_ElmBird. The added line appears only with OPENING_SEEN. Elm original state/briefing owns progression; no Nao prerequisite or new initializer (the Johto starter choice comes after this intro).

**Status:** IMPLEMENTED. Historical 30-series native scope; see original per-event result. No 37C replay claimed.

**37C source:** [`RB_ElmBird`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rainbow_story.inc:241). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html).

A short sighting callback before the existing adapted visiting-Champion introduction.

### RB09 — Ecruteak truth

**Trigger:** Original beasts-release flag required. Ecruteak remains Nao priority until truth seen; after truth, before Radio Tower10 she may move to Olivine after Amphy. Since 2026-11-09 (RB16), after the truth she is at the Lake of Rage instead while the Mahogany hideout is cleared and the tower not yet freed, Amphy healed or not (one Nao at a time); replay tests `ecruteak nao waits before the hideout`, `ecruteak nao is away at the lake of rage`. First interaction returns after truth; playback and Welcome occur on later talks.

**Status:** IMPLEMENTED. Historical 30-series native scope; see original per-event result. No 37C replay claimed.

**37C source:** [`RB_NaoJohtoIntro`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rainbow_story.inc:273). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html).

Late self-introduction and truth about Ho-Oh and the burned tower. Since 2026-10-31 (`RB_NaoReunion`, `RB_Text_JohtoIntro`): a player Nao met in Kanto is greeted before the truth (“You came all the way to ECRUTEAK! PROF.OAK thought you might. Now I can tell you the rest.”); one she never met hears “I’m NAO. I keep the bells here in ECRUTEAK. I came home from KANTO not long ago. I went asking about a bird.” (the old line, “I have been collecting KANTOs stories”, is gone; the story copy of 2026-11-09 dropped “I’ve just come home”, as the player is three badges in by then). Replay tests `ecruteak nao greets a friend from kanto`, `ecruteak nao tells a friend the rest`, `ecruteak nao introduces herself`, `ecruteak nao came home from kanto`.

### RB10 — Amphy callback

**Trigger:** Olivine visibility requires original Amphy healed and Ecruteak truth seen; Radio Tower state<10. Repeatable; no new medicine, reward or saved answer.

**Status:** IMPLEMENTED. Historical 30-series native scope; see original per-event result. No 37C replay claimed.

**37C source:** [`RB_OlivineVisibility`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rainbow_story.inc:359). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html).

Care for the Pokémon already here; cosmetic bell response. Since 2026-11-09 (story copy L3), one Nao at a time: while she is at the Lake of Rage (RB16: the Mahogany hideout cleared, the tower not yet freed) she isn’t in Olivine. Replay tests `olivine nao waits by the lighthouse before the hideout`, `olivine nao is away at the lake of rage`.

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

### RB15 — Fuji hears from Nao

**Trigger:** Talk to Mr. Fuji in his house after the Poké Flute is given, with `FLAG_RB_FUJI_SCENE_SEEN` (RB04) and `FLAG_RB_WELCOME_SEEN` (RB13, Johto). A callback across the regions: it reads Johto’s receipt. The first such talk he reads the letter, in place of his “Has my POKé FLUTE helped you?”, and sets `FLAG_RB_FUJI_LETTER_READ` (Kanto flag `0x0B1`, unused before); every later talk he says “MR. FUJI: NAO’s letter is on my table. I read it most mornings.”, then asks about the flute as before. Before the welcome he only asks about the flute.

**Status:** IMPLEMENTED 2026-10-31; read once since 2026-11-09 (story copy F1). Replay tests `lavender fuji hears from nao`, `lavender fuji keeps naos letter`, `lavender fuji asks about the flute after the letter`, `lavender fuji asks about the flute`.

**Source:** [`RB_FujiNaoLetter`](../../engine/data/scripts/rainbow_story.inc), called from `LavenderTown_VolunteerPokemonHouse_EventScript_AlreadyHavePokeFlute`.

“MR. FUJI: A letter came from NAO. She thanks me for the useful work. She says the bells rang at last. She asked nothing of the sky. She made a place it could come back to. That is all any home can do.” The design’s “Kanto return conversations” hook (Fuji asks how Nao is doing).

### RB16 — Copied calls at the Lake of Rage

**Trigger:** Lake of Rage, on entering (`RB16_Visibility`): Nao has told the truth in Ecruteak (`FLAG_RB_ECRUTEAK_TRUTH_SEEN`), the Mahogany hideout is cleared (`JOHTO_VAR_MAHOGANY_TOWN_STATE` ≥ 14) and the tower is not yet freed (`JOHTO_VAR_GOLDENROD_CITY_STATE` < 10). Nao (`LOCALID_LAKEOFRAGE_NAO`, appended to the lake’s events) stands on the south shore at 35,35, facing the water, east of the old man and clear of Lance’s scene and the west shore, at high and low tide alike. Talk to her. While she is there, Olivine (RB10) and Ecruteak (RB09) don’t show her (`RB_NaoAtLake`).

**Status:** IMPLEMENTED 2026-11-09 (story copy L3, decision 11; KR-118). Replay tests `lake of rage nao read the notebook`, `lake of rage nao tells of the notes`, `lake of rage nao never asked ho-oh`, `lake of rage nao keeps the lake quiet`, `lake of rage nao says the lake is quiet`, `lake of rage no nao before the hideout`, `lake of rage no nao after the tower`, `lake of rage no nao before ecruteak`; for one Nao at a time, `olivine nao waits by the lighthouse before the hideout`, `olivine nao is away at the lake of rage`, `ecruteak nao waits before the hideout`, `ecruteak nao is away at the lake of rage`.

**Source:** [`RB_NaoLake`](../../engine/data/scripts/rainbow_story.inc).

“{PLAYER}! In MAHOGANY they said the lake went wild when a radio started humming. I came to listen. I know that kind of sound.” If the player saw her notebook in Celadon (RB05, `FLAG_RB_NOTEBOOK_SCENE_SEEN`): “It’s what they wrote in my notebook. Microphones. A call that makes POKéMON answer.”; if not: “In KANTO, ROCKET took my bell notes. When I got them back, someone had written in them: Microphones. A call that makes POKéMON answer.” Then: “The GYARADOS didn’t come to that call. It forced them to change. ROCKET can’t agree who their boss is. But every one of them wanted that machine. I wanted a sound that would bring HO-OH back. I never asked if it would want to come.” and “The lake is quiet now. Let’s keep it that way.” The whole talk is recorded (`JOHTO_FLAG_RB16_SEEN`, Johto id `0x291C`: HnS raw flag `0x91C`, unused by any script or C, outside Johto’s daily flags `0x910`–`0x91A` and inside its stored events, so no save layout change); later talks give only the last line, until the tower is freed and she goes home to Ecruteak.

### MW01 — Viridian stranger

**Trigger:** Right after RB01's flyby on Route 1 (`MW01_Route1Scene`, called by `RB_Route1Frame`), when the player entered from Pallet's edge; own scene unseen; no full reveal/native Mewtwo closure. He walks down to the player, has them search the Pokédex for the bird (no entry), asks YES/NO, and leaves after Mew's glimpse. Until 2026-10-25 he waited east of Viridian's square after the Pokédex.

**Status:** IMPLEMENTED. Historical 30-series native scope; see original per-event result. No 37C replay claimed.

**37C source:** [`MW01_Visibility`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rainbow_story.inc:390). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html).

Questions the rescue or uses a generic honest alternative, followed by a sparse Mew glimpse. Since 2026-10-31 (story audit E1), as he reaches the player the companion Pikachu reacts first: “PIKACHU’s fur stands on end. It doesn’t take its eyes off him.” (shown whenever the companion walks with the player, `FLAG_SYS_POKEMON_GET`; nothing is written). Replay test `route 1 pikachu bristles at the stranger`; the existing `route 1 the stranger after ho-oh` still passes.

### MW02 — Route4 stone

**Trigger:** Original durable fossil-completion flag, not Bag fossil possession. Own scene unseen, no MW06/full Mewtwo closure. Rock local13 levitates; stranger local12 and rock are removed afterwards.

**Status:** IMPLEMENTED. Historical 30-series native scope; see original per-event result. No 37C replay claimed.

**37C source:** [`MW02_Visibility`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rainbow_story.inc:420). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html).

Fossil-choice question and small psychic rock movement.

### MW03 — A home, not a cage

**Trigger:** Original Poké Flute receipt; own scene unseen; suppressed by MW06 or native Mewtwo closure. The stranger (`LOCALID_LAVENDER_MW03_STRANGER`) waits near Mr. Fuji's door, at (9,16) past the Volunteer House sign, facing it; he blocks no path. No permanent Fuji relocation.

**Status:** IMPLEMENTED. Historical 30-series native scope; staged at Fuji's door 2026-11-09 (story copy D, KR-116). Replay tests `lavender fuji at his door`, `lavender gentleman`; `lavender the friends camp` plays FG08 with the stranger beside the door.

**37C source:** [`MW03_Visibility`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rainbow_story.inc:446). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html).

Talked to, the stranger turns to the door. It opens: a Psyduck wanders out, sniffs the air and goes back in. “STRANGER: Nothing keeps them here.” Mr. Fuji steps out to answer him (a scene-only actor, `LOCALID_LAVENDER_MW03_FUJI`; the Fuji in his house doesn't move): “Some leave when they're ready.” “And you allow that?” “It is a home, not a cage. I learned that late.” He goes back in and the door closes; the traveler has no reply; Mew's glimpse; the stranger leaves (`FLAG_MW03_SEEN`). Nothing else says Fuji made Mewtwo.

### MW04 — Celadon trust

**Trigger:** Original Hideout-clear flag, independent of Nao/notebook; own scene unseen and no MW06/native closure.

**Status:** IMPLEMENTED. Historical 30-series native scope; see original per-event result. No 37C replay claimed.

**37C source:** [`MW04_Visibility`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rainbow_story.inc:469). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html).

Questions Poké Balls after opposing Rocket. Since 2026-10-31 (story audit T2), if the player saw the Friends land in Viridian (`FLAG_FRIENDS_ARRIVED_IN_VIRIDIAN`) he first says: “Seven people fell out of the sky over VIRIDIAN. They ask their POKéMON before they reach for a BALL. I have watched.” A callback; nothing is written. His question names Rocket since 2026-11-09 (story copy F1), so “They called POKéMON property” no longer reads as the seven: “ROCKET called POKéMON property. You opposed them. Yet you carry POKé BALLS. Do you try to earn their trust?” Replay tests `celadon the stranger remembers the seven`, `celadon the stranger asks about rocket`, `celadon the stranger after the hideout and the seven`.

### MW05 — Silph disguise slip

**Trigger:** Silph1F; original Master Ball receipt; own scene unseen and no MW06/native closure. Local2 is hidden during reveal, intentionally restored for brief glitch dialogue, then removed at scene completion.

**Status:** IMPLEMENTED. Historical 30-series native scope; see original per-event result. No 37C replay claimed.

**37C source:** [`MW05_Visibility`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rainbow_story.inc:492). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html).

A temporary Mewtwo reveal, returned disguise, then possible Mew glimpse. Since 2026-11-09 (story copy F1, the middle of the Pikachu thread between Route 1 and Cinnabar), after “The traveler’s outline wavers: a long tail, an unfamiliar head.” and before the stranger speaks, the companion Pikachu (`FLAG_SYS_POKEMON_GET`): “PIKACHU’s ears flatten. It stares at the traveler’s shadow.” (`RB_PikachuStares`; `MW05_Text` is split in two round it). Nothing is written. Replay test `silph pikachu stares at the travelers shadow`.

### MW06 — Cinnabar reveal

**Trigger:** Cinnabar; native Secret Key discovery hide flag, independent of current Key possession; scene unseen and native Mewtwo unresolved. Local15 is removed before reveal and remains absent through question/answer/glimpse. The Mansion journals themselves are unchanged.

**Status:** IMPLEMENTED. Historical 30-series native scope; see original per-event result. No 37C replay claimed.

**37C source:** [`MW06_Visibility`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rainbow_story.inc:518). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html).

Journals context, unique Mewtwo reveal, invitation/choice responses and Mew observer. Since 2026-10-31 (story audit E1), the companion Pikachu closes the thread it opened on Route 1: as the veil falls, “PIKACHU bristles, just as it did on ROUTE 1.” (since 2026-11-09, story copy F1: “It knew all along.” winked at the player and is gone) (“PIKACHU bristles and steps between you and MEWTWO.” if the Route 1 meeting never happened, `FLAG_MW01_SEEN` unset), and after Mewtwo’s answer, “PIKACHU watches it go. Its fur slowly settles.” Nothing is written. Replay tests `cinnabar pikachu bristles at mewtwo`, `cinnabar pikachu settles as mewtwo leaves`, `cinnabar pikachu bristles without the route 1 meeting`. Since 2026-11-09 (story copy C1, KR-115) the stranger's first words quote the Mansion's B1F diary, so the reveal never leans on pages the player skipped: “STRANGER: Someone in that house wrote, “MEWTWO is far too powerful.” Those pages tell what they hoped to create. They cannot tell you who I will become.” Replay test `cinnabar the stranger quotes the mansion diary`.

### MW07 — Route22 question

**Trigger:** Requires MW06 seen; own scene unseen; native Mewtwo unresolved. Reads native Kanto Champion flag for wording; original rival trigger coordinates unchanged.

**Status:** IMPLEMENTED. Historical 30-series native scope; see original per-event result. No 37C replay claimed.

**37C source:** [`MW07_Visibility`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rainbow_story.inc:545). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html).

Different Champion question before/after Kanto League. Since 2026-11-09 (story copy C2/C3, KR-115) he no longer speaks as STRANGER: one narration line says the disguise is back (“The traveler's coat and hat are back. You know who wears them.”), he speaks as MEWTWO, and he tells the player where to find him. Before the League: “Others see a traveler. You do not. Good. They will call you CHAMPION soon. I wonder what you will ask of it. When they do, come to the cave at the edge of CERULEAN. I will wait.” After it: “You reached the summit. Did it change what you ask of those beside you? Come to the cave at the edge of CERULEAN. I will be waiting inside.” `FLAG_MW07_SEEN`, set as he leaves, is what Cerulean Cave’s guard reads (MW08). Replay tests `route 22 mewtwo asks you to come to his cave`, `route 22 mewtwo leaves for his cave`, `route 22 mewtwo waits in his cave after the league`.

### MW08 — Cerulean Cave choice

**Trigger:** Two ways into Cerulean Cave since 2026-11-09 (story copy C4, decision 7, KR-115): the guard in front of it (`CeruleanCity_EventScript_CeruleanCaveGuard`) lets a Kanto Champion (`FLAG_SYS_GAME_CLEAR`) who has heard MW07 (`FLAG_MW07_SEEN`) through: “This is CERULEAN CAVE. You're the new CHAMPION. Then I can let you through. Something in there has been quiet for weeks. Not asleep. Waiting. Take care of yourself in there.”, steps aside away from the player and sets `FLAG_HIDE_CERULEAN_CAVE_GUARD`, so he stays away. Anyone else hears FireRed's rule and he stays in the way. Celio's Sevii errand, which sets the same flag, stays the way in for a player who never met the stranger. Existing Mewtwo interaction calls MW08_Intro; actual NO leaves without setting native fought state; YES runs original battle. Actual WON/CAUGHT set original FLAG_FOUGHT_MEWTWO; flee/teleport follow native escape/removal path, with transition restoring retry while fought remains unset.

**Status:** IMPLEMENTED. Historical 30-series native scope; see original per-event result. No 37C replay claimed.

**37C source:** [`MW08_Intro`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rainbow_story.inc:617). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html).

Optional familiar/unfamiliar introduction and Face/Leave before original level70 Mewtwo. Since 2026-10-31 (story audit T2), with the familiar greeting and Black Tide resolved in Johto (`FLAG_LG_FINAL_RESOLVED`), Mewtwo adds: “Far to the west, ROCKET made birds the way I was made. You broke their chains. I heard.” A callback across the regions: it reads Johto’s receipt for dialogue only and writes nothing. Since 2026-11-09 (story copy F1, the order of its C5) the familiar greeting is split so this line comes before the battle offer: “MEWTWO: You found the quiet place I chose.”, the replica line, “MEWTWO: If we battle, let it be a choice we both make.”, then “Face MEWTWO now?”. Replay tests `cerulean cave mewtwo heard of the replicas`, `cerulean cave mewtwo offers a battle after the replicas`, `cerulean cave mewtwo offers a battle`, `cerulean cave mewtwo can be left after the replicas`. Since 2026-11-09 (story copy C5, KR-115), after MW07 he asked the player to come, so the greeting is “MEWTWO: You came. This is the quiet place I chose. Few would follow me here.” (then the replica line, the battle offer and the question as above); “You found the quiet place I chose.” stays for a player who saw only the reveal, and the unfamiliar presence for one who never met the stranger. Replay tests `cerulean cave mewtwo says you came`, `cerulean cave mewtwo you came then the replicas`; the gate's `cerulean cave guard lets the champion through`, `cerulean cave guard steps aside for the champion`, `cerulean cave guard steps aside from the west`, `cerulean cave celios errand opens it without mewtwo`, `cerulean cave guard stops a champion who never met mewtwo`, `cerulean cave guard stops mewtwos guest before the league`.

### MW09 — Cave-mouth reflection

**Trigger:** Native fought-Mewtwo set; MW09 unseen. Since 2026-11-10 (the owner: Mewtwo, caught, “comes out of his pokeball to engage with the player at the end of that arc”) it plays by itself when the player walks out of the mouth: coord events on Cerulean Cave 1F x34–36,y22, stepping south (walking in, it waits; `VAR_TEMP_E` from the transition). Before, it was a BG sign at x34,y22.

**Status:** IMPLEMENTED. Historical 30-series native scope; see original per-event result. No 37C replay claimed.

**37C source:** [`MW09_Transition`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rainbow_story.inc:636). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html).

Neutral post-resolution reflection and optional Mew glimpse. Since 2026-11-09 (story copy C6, KR-115) the companion Pikachu closes the thread it opened on Route 1: after the reflection, “PIKACHU looks back into the dark. Its fur stays smooth.” (whenever the companion walks with the player, `FLAG_SYS_POKEMON_GET`; nothing is written). Replay test `cerulean cave pikachu looks back at the mouth`.

Since 2026-11-10, when Mewtwo was caught and is in the party, Mewtwo comes out of its Poké Ball beside the player (an actor on 1F with Mewtwo's overworld sprite, the follower's ball-exit animation, the ball sound and its cry) and the farewell is a conversation: “At the mouth of the cave, the wind moves freely again.” / “MEWTWO: There is room for more than one path through the world.” / “I will walk this one with you, {PLAYER}.” / “You did not command. You asked. I answered.”, then “PIKACHU looks up at MEWTWO. Its fur stays smooth.”, and Mewtwo goes back into the ball. Beaten (or caught and in the PC) the reflection stays narration, as above. Running from Mewtwo leaves it in the cave (FireRed brings it back), so the farewell waits. Replay tests `cerulean cave mewtwo comes out of his ball at the mouth`, `cerulean cave mewtwo goes back into his ball`, `cerulean cave the farewell waits while walking in`, `cerulean cave no farewell before mewtwo is met`.

### LG01 — Coastal warnings

**Trigger:** Talk to Olivine Sailor1 or Cianwood PokefanM; VAR_GOLDENROD_CITY_STATE>=10; successful native story adoption.

**Status:** IMPLEMENTED. Historical 30-series native scope; see original per-event result. No 37C replay claimed.

**37C source:** [`BlackTide_CoastalWarning`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/johto/adapted/WhirlIslands_LugiaChamber_hns.inc:1009). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html).

Original Olivine sailor and Cianwood Pokéfan conversations append a Whirl warning after the native Radio Tower state reaches10: three huge birds striking in turns, and Rocket boats near the islands although Rocket quit (KR-110). The warning itself grants no travel/item/branch progress.

### LG02 — The manufactured birds attack Lugia

**Trigger:** First safe Whirl chamber frame after native Lugia state2(Silver story) or4(earned later access); no final/exempt receipt; FLAG_LG_ATTACK_SEEN unset.

**Status:** IMPLEMENTED. Historical 30-series native scope; see original per-event result. No 37C replay claimed.

**37C source:** [`WhirlIslands_LugiaChamber_hns_MapScripts`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/johto/adapted/WhirlIslands_LugiaChamber_hns.inc:1). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/rainbow-story-01/story-review-01/story-review.html).

A once-only chamber scene stages three separately manufactured replicas striking Lugia. The Rocket technician says Archer quit, Ariana didn’t, and the project answers to her now (KR-110). Rocket leaves, Lugia darkens, and the three independent encounters remain.

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

The third independent success breaks Rocket control. Lugia remains in the Shadow state, becomes approachable, and the Keeper allows unlimited preparation. From then on a Rocket log can be read where each replica stood: the calls copied (Seafoam Islands, Power Plant, Mt. Ember), Silph’s recording devices, three specimens, no retreat (GAP-30, KR-110).

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

**2026-11-09 (story copy H3, KR-112):** Jenny’s fire is a smoldering stack of crates on the quay, not a supply shed; the Squirtle soak the crates. Replay test `vermilion jenny the smoldering crates`.

Vermilion introduction and post-Thunder Badge rescue/gift.

### JT01 — Wrong end of the net

**Trigger:** KantoRoute4 exit after native fossil232; before nativeCascade/Champion; no priorJT01/JT02/JT03. Known coordinator required. No choice, battle, theft or extra fossil reward; narration/in-place struggle conveys the net, not a net graphic.

**Status:** IMPLEMENTED. Original 31-series evidence; JT02/JT03 presentation and battle updates use 33B. Unexecuted branches stay pending in the linked ledger.

**37C source:** [`JT01_Visibility`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rocket_trio_story.inc:12). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/story-additions-02/story-review-31e/owner-review-02/story-review.md).

Optional MtMoon exit net mishap with visible Jessie/Meowth and James explicitly speaking from inside the tunnel. Since 2026-11-09 (story copy T6, decision 10), after Meowth’s “Then help me out of it!” the trio notice the companion Pikachu and never try to take it: JESSIE “…Wait. That PIKACHU walks beside the kid, without a BALL.”, JAMES (still from the tunnel) “A PIKACHU like that? Headquarters would remember US!”, MEOWTH “Headquarters can’t even remember ME, and I can TALK!” Meowth’s struggle in the net (`applymovement2`) no longer sends Pikachu back into its ball, so it is beside the player while they say so. Replay tests `route 4 the trio notice pikachu`, `route 4 meowth can talk`.

### JT02 — Official researchers

**Trigger:** Celadon native Hideout cleared; own scene unseen. Jessie disguise changes only after affirmative question; James leaves in disguise because no qualified true James art.

**Status:** IMPLEMENTED. Original 31-series evidence; JT02/JT03 presentation and battle updates use 33B. Unexecuted branches stay pending in the linked ledger.

**37C source:** [`JT_CeladonVisibility`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rocket_trio_story.inc:89). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/story-presentation-04/owner-review-33b-03/REVIEW.md).

Researcher disguise scene followed by an independent optional Jessie/James double battle. Decline, retry, two-usable-Pokémon and escort checks remain separate from comedy completion.

### JT03 — Fresh start, allegedly

**Trigger:** Goldenrod native state1..5, suppressed during and after takeover6+. No required Pikachu/current-party test; James departs in disguise.

**Status:** IMPLEMENTED. Original 31-series evidence; JT02/JT03 presentation and battle updates use 33B. Unexecuted branches stay pending in the linked ledger.

**37C source:** [`JT_GoldenrodVisibility`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rocket_trio_story.inc:101). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/story-presentation-04/owner-review-33b-03/REVIEW.md).

Goldenrod trio scheme; prior meeting chooses honest callback. Since 2026-11-09 (story copy T6 and L4), Meowth’s callback is “And the same kid! With the same smug PIKACHU!” (a player who met them before) or “And an audience! With a PIKACHU, no less!”, and before the disguises come off Jessie sets up JT05: “Somebody in JOHTO is still hiring ROCKETS. We’ll be the best they’ve got!” Replay tests `goldenrod the trio know the kid and pikachu`, `goldenrod the trio meet a pikachu`, `goldenrod jessie says johto is still hiring`.

### JT04 — Even we know better

**Trigger:** WhirlDescent optional interaction only after actualLGfinal919 and all3canonicalreplicaresults, with known coordinator and own929unseen. Legacyexemption/nativeLugia/caught/ownership alone do not qualify. No newLG receipts or captive gifts; restoration remains uninterrupted.

**Status:** IMPLEMENTED. Original 31-series evidence; JT02/JT03 presentation and battle updates use 33B. Unexecuted branches stay pending in the linked ledger.

**37C source:** [`JT04_Visibility`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/rocket_trio_story.inc:45). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/story-additions-02/story-review-31e/owner-review-02/story-review.md).

Optional return-path rescue aftermath: actual Jessie/Meowth and ordinary Seel; James explicitly calls from the passage. Since 2026-11-09 (story copy L4), after “I couldn’t leave the cages shut.” a player who saw JT05 (`JOHTO_FLAG_JT05_SEEN`) hears James: “In GOLDENROD, I only fed them. This time I opened the doors.”, and Jessie’s line is, in every case, “ARCHER quit. ARIANA was still hiring. We were only inspecting company property.” Replay tests `whirl islands james fed them in goldenrod`, `whirl islands jessie says ariana was still hiring`.

### JT05 — Guard duty

**Trigger:** Goldenrod Underground’s warehouse (`GoldenrodCity_UndergroundStorage_hns`, its first room, beside the crates) during the takeover: `JOHTO_VAR_GOLDENROD_CITY_STATE` 6–9, `JOHTO_FLAG_JT05_SEEN` not set, known coordinator required (`JT05_Visibility`). Jessie, James and Meowth (all three on screen, James’s own walking art) stand guard in a row; behind James, in the lane between the crates and the wall, two caged Pokémon (Marill and Sentret, `FLAG_TEMP_1D`). Talk to any of the trio. No battle.

**Status:** IMPLEMENTED 2026-11-09 (story copy L4, decision 10; KR-117). Replay tests `goldenrod warehouse the trio on guard duty`, `goldenrod warehouse the trio stop a stranger`, `goldenrod warehouse the trio slip away`, `goldenrod warehouse the cages stay after the trio`, `goldenrod warehouse no cages once the tower is free`, `goldenrod warehouse no guards before the takeover`.

**Source:** [`JT05_GuardDuty`](../../engine/data/scripts/rocket_trio_story.inc); the warehouse’s on-transition script calls `JT05_Visibility`.

Jessie: “You again! This is a restricted storage area. We’re on guard duty. Real uniforms, real pay.” (“Hold it! …” for a player who never met them, `FLAG_JT01_SEEN`, `FLAG_JT02_SEEN` and `FLAG_JT03_SEEN` all unset). James: “ARCHER says the boss will be home as soon as he hears the broadcast.” Meowth: “And then the boss sees who stood watch. That’s the plan.” The Sentret whimpers (its cry): “A POKéMON in one of the cages whimpers. JAMES looks over.” and he turns to it: “…They said not to feed these until after the broadcast. It’s only a few BERRIES. Nobody needs to write that down.” Jessie: “James! Not in front of the kid!” Meowth: “Shh! Somebody’s coming!” They leave in a fade and the scene is recorded (`JOHTO_FLAG_JT05_SEEN`, Johto id `0x291D`: HnS raw flag `0x91D`, unused by any script or C, outside Johto’s daily flags `0x910`–`0x91A` and inside its stored events, so no save layout change). The cages stay until the tower is freed (state 10); talked to, each Pokémon only cries. JT04 reads the flag.

### BL01 — A new field of study

**Trigger:** First Kanto HOF/credits return, once the National Dex scene has played (the lab at 9; KR-113): Blue asked to join Oak’s next field survey as he left it, and opens with “Grandpa said yes!”. Optional added actor, saved Kanto rival name.

**Status:** IMPLEMENTED. Original 31-series evidence; JT02/JT03 presentation and battle updates use 33B. Unexecuted branches stay pending in the linked ledger.

**37C source:** [`CG_BlueLab`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/character_growth.inc:47). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/story-additions-02/story-review-31e/owner-review-02/story-review.md).

Blue enthusiastically starts field science under Oak.

### BL02 — The Pidgey notebook

**Trigger:** BL01 seen, BL02 unseen; completed Johto introduction2 gives later lab scene priority. No timed errand or reward.

**Status:** IMPLEMENTED. Original 31-series evidence; JT02/JT03 presentation and battle updates use 33B. Unexecuted branches stay pending in the linked ledger.

**37C source:** [`CG_BlueRoute1`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/character_growth.inc:76). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/story-additions-02/story-review-31e/owner-review-02/story-review.md).

Optional Route1 observation and expressive answer. Since 2026-11-02 (story audit T3), with the opening seen (`FLAG_RB_OPENING_SEEN`) Blue has read Oak’s notes on it: “Grandpa’s notes say you sheltered one here, in a storm. Maybe it’s one of these. I’m writing that down as a maybe!” A callback; nothing is written. Replay tests `route 1 blue remembers the storm pidgey`, `route 1 blue watches the pidgey after the storm`.

### GD01 — Gold outside Violet’s Gym

**Trigger:** Violet City, on entering: `JOHTO_FLAG_BADGE01_GET` set, `JOHTO_FLAG_BADGE02_GET` not set, `JOHTO_FLAG_GD01_SEEN` not set (`CG_GoldVioletVisibility`). Gold (`LOCALID_VIOLET_GOLD`, appended to Violet’s events) stands east of the Gym’s door, facing it. Talk to him.

**Status:** IMPLEMENTED 2026-10-31 (story audit proposal L1); two lines rewritten 2026-11-09 (story copy F1). Replay tests `violet gold waits after the zephyr badge`, `violet gold rematch`, `violet gold rematch from below`, `violet gold rematch from the east`, `violet gold asks how you stay so calm`, `violet gold heard about the break-in`, `violet gold not there before the badge`, `violet gold moved on after the hive badge`.

**Source:** [`CG_GoldViolet`](../../engine/data/scripts/character_growth.inc); trainers `TRAINER_JOHTO_GOLD_VIOLET_TOTODILE_HNS`, `…_CHIKORITA_HNS`, `…_CYNDAQUIL_HNS` (Geodude lv 8 and his starter lv 10, chosen by `JOHTO_VAR_STARTER_MON` as in Elm’s lab).

Gold: Falkner beat him twice, even after he caught a Geodude in Dark Cave for him. “Show me how a CHAMPION does it? I did say I’d win next time!” NO: he keeps watching the Gym door (ask again later). YES: the battle; after it “How do you stay so calm? I just keep shouting moves. FALKNER said that, too.”; once the police scene at Elm’s lab has played (`JOHTO_VAR_NEWBARKTOWN_LABSTATE` ≥ 5), where the player named the thief, “PROF.ELM told me about the break-in. You saw the thief, right? {RIVAL}. He took the one that sat next to mine on the table. If I see him, I’ll tell him what I think of that!”; then he walks off east to heal and try Falkner a third time. Winning sets `JOHTO_FLAG_GD01_SEEN` (Johto id `0x291B`: HnS raw flag `0x91B`, the first after HnS’s last flag `0x91A`, unused by any script or C and inside Johto’s stored events, so no save layout change). Losing is an ordinary loss; he waits to be asked again. He is gone after the second Johto badge whether or not the scene was played.

### GD02 — Gold outside Ecruteak’s Center

**Trigger:** Ecruteak City, on entering: `JOHTO_FLAG_RELEASED_BEASTS` set (the beasts have fled the Burned Tower), `JOHTO_FLAG_BADGE04_GET` not set, `JOHTO_FLAG_GD02_SEEN` not set (`CG_GoldEcruteakVisibility`). Gold (`LOCALID_ECRUTEAK_GOLD`, appended to Ecruteak’s events, `FLAG_TEMP_1C`) stands beside the Center’s door, facing it. Talk to him.

**Status:** IMPLEMENTED 2026-11-09 (story copy F2, L2). Replay tests `ecruteak gold waits after the burned tower`, `ecruteak gold remembers new bark`, `ecruteak gold battle after the burned tower`, `ecruteak gold leaves for the theater`, `ecruteak gold leaves from the east`, `ecruteak gold battle from below`, `ecruteak gold not there before the burned tower`, `ecruteak gold gone after the fog badge`, `ecruteak gold gone once played`.

**Source:** [`CG_GoldEcruteak`](../../engine/data/scripts/character_growth.inc); trainers `TRAINER_JOHTO_GOLD_ECRUTEAK_TOTODILE_HNS`, `…_CHIKORITA_HNS`, `…_CYNDAQUIL_HNS` (Geodude lv 20, Flaaffy lv 20 and his starter’s middle stage lv 22, chosen by `JOHTO_VAR_STARTER_MON` as in Elm’s lab; around the area’s average, as the owner asked on 10 November: the trainers of Routes 36 and 37 and the Burned Tower, Silver there, and Ecruteak’s Gym with Morty average lv 20.6).

With GD01 played, “{PLAYER}! I beat FALKNER! Third time, just like I said!”; without it, “{PLAYER}! Remember me? GOLD, from NEW BARK. I beat FALKNER!” Then: he found {RIVAL} coming out of the Burned Tower, told him what he thinks of thieves, was called weak and beaten, and saw Silver make his Pokémon rest before it battled again (SV01’s same city). “Battle me? I want to see if I’m any less weak!” NO: “Okay! I’ll be at the CENTER, getting ready.” (ask again later). YES: the battle (“Closer. I’m getting closer!”); after it he is off to see the Kimono Girls dance, then Morty, and walks off toward the theater. Winning sets `JOHTO_FLAG_GD02_SEEN` (Johto id `0x291E`, HnS raw `0x91E`, unused and inside Johto’s stored events). He is gone after the Fog Badge whether or not the scene was played.

### GD03 — Gold’s last battle in New Bark

**Trigger:** New Bark Town, on entering: `JOHTO_FLAG_SYS_GAME_CLEAR` set, `JOHTO_FLAG_GD03_SEEN` not set (`CG_GoldNewBarkVisibility`). Gold (`LOCALID_NEWBARK_GOLD`, appended to New Bark’s events, `FLAG_TEMP_1D`) stands beside Elm’s lab door. Talk to him.

**Status:** IMPLEMENTED 2026-11-09 (story copy F2, L2). Replay tests `new bark gold waits after the johto league`, `new bark gold last battle`, `new bark gold walks off west`, `new bark gold leaves from below`, `new bark gold battle from the east`, `new bark gold not there before the johto league`, `new bark gold gone once played`.

**Source:** [`CG_GoldNewBark`](../../engine/data/scripts/character_growth.inc); trainers `TRAINER_JOHTO_GOLD_NEWBARK_TOTODILE_HNS`, `…_CHIKORITA_HNS`, `…_CYNDAQUIL_HNS` (Golem lv 47, Heracross lv 47, Ampharos lv 47 and his starter’s final stage lv 49; around the average of the late-game area the player comes from, as the owner asked on 10 November: the trainers of Routes 26 and 27, Silver on Victory Road and the Elite Four and Lance at their first challenge average lv 47.4).

“{PLAYER}! You did it. CHAMPION of KANTO, and now JOHTO too! I have five BADGES now. Five! I’m going to catch up, you’ll see.” “One more battle? This time, I really mean to win.” NO: “Okay! I’ll be right here when you’re ready.” YES: the battle (“Not this time either!”); after it “I didn’t shout once that whole battle. Did you notice? See you around, {PLAYER}. Next time, I’ll win!” (his line from Elm’s lab), and he walks off west toward Route 29. Winning sets `JOHTO_FLAG_GD03_SEEN` (Johto id `0x291F`, HnS raw `0x91F`).

### KR-120 — The quiet stretches

**Status:** IMPLEMENTED 2026-11-09 (story copy F3: the small beats it spells out; FG-A–FG-F and L8 are not part of it). Nothing here is written except the trio’s receipt.

| Where | Who | When | Line | Source | Replay tests |
| --- | --- | --- | --- | --- | --- |
| One Island, by the harbour stairs | a traveller (appended, `LOCALID_ONE_ISLAND_TRAVELER`, `FLAG_TEMP_1E`) | `FLAG_RB_OPENING_SEEN` | “They say a gold bird crossed the sea weeks ago, heading west. My little brother drew it. He gave it a tail like a rainbow.” (L6) | `RB_OneIslandTraveler`, `rainbow_story.inc` | `one island traveller heard of the gold bird`, `one island no traveller without the opening` |
| Five Island Meadow, outside the Rocket Warehouse | Jessie, James, Meowth (appended, `FLAG_TEMP_1C`) | `FLAG_SYS_GAME_CLEAR`, warehouse not cleared (`FLAG_HIDE_FIVE_ISLAND_ROCKETS` unset), `FLAG_TRIO_FIVE_ISLAND_SEEN` unset | “JESSIE: Don’t mind us. We heard the ADMIN in there is still hiring.” “JAMES: We asked about the pay. He said ROCKET pays in pride.” “MEOWTH: We’ve been unpaid for years. We don’t need a uniform for that!” “JESSIE: Come on. We’re leaving.” They leave in a fade; sets `FLAG_TRIO_FIVE_ISLAND_SEEN` (FireRed’s unused flag 0x0BC) (L5) | `JT_FiveIslandWarehouse`, `rocket_trio_story.inc` | `five island trio still hiring`, `five island trio leave`, `five island no trio before the league`, `five island no trio after the warehouse`, `five island no trio once played` |
| Route 21 North, in the water off the north shore | a swimmer (appended, `LOCALID_ROUTE21_STRANGER_SWIMMER`, `FLAG_TEMP_1E`) | `FLAG_MW05_SEEN` set, `FLAG_MW06_SEEN` unset | “I saw a man in a coat out here. Standing on the water! Then I blinked, and he was gone. He was heading for CINNABAR.” | `MW_Route21Swimmer`, `rainbow_story.inc` | `route 21 swimmer saw a man on the water`, `route 21 no swimmer before silph`, `route 21 no swimmer after the reveal` |
| Seafoam Islands B4F, Power Plant, Mt. Ember summit, by each bird | a broken tape recorder (appended, the Pokédex prop sprite) | always | “A broken tape recorder lies by the wall. ROCKET’s mark is on it. The label reads: CALL SAMPLE 1.” (2 at the Power Plant, 3 at Mt. Ember) | `RB_TapeRecorderSample1`–`3`, `rainbow_story.inc` | `seafoam rocket tape call sample 1`, `power plant rocket tape call sample 2`, `mt ember rocket tape call sample 3` |
| Route 12, Silence Bridge | the fisher CHIP, after his battle | `FLAG_RB_OPENING_SEEN` | after his line about a better ROD: “Weeks ago, I saw something gold over the forest, way up high. I didn’t catch a thing that day. I kept looking up.” | `Route12_EventScript_Chip` (`trainers_frlg.inc`), `RB_Route12FisherGold` | `route 12 fisher saw something gold`, `route 12 fisher without the opening` |
| Indigo Plateau Pokémon Center | the guide (Gym Guy) | `FLAG_FRIENDS_FG11_SEEN` set, `FLAG_SYS_GAME_CLEAR` unset | after his advice: “Seven strange people asked where they could watch the LEAGUE on TV. One of them was very loud.” | `IndigoPlateau_PokemonCenter_1F_EventScript_GymGuy` | `indigo gym guy saw seven strange people`, `indigo gym guy before the seven came`, `indigo gym guy after the league` |
| Cherrygrove | the boy by the Mart | always (with the Pokédex) | after his own lines: “Did you hear? They say a CHAMPION from KANTO came to JOHTO. I wonder what they’re like.” | `CherryGroveCity_EventScript_Boy2` | `cherrygrove boy heard of a kanto champion` |
| Route 31 | the bug catcher WADE | his first battle | “Is that a PIKACHU? You don’t see many around here.” before his own intro | `Route31_Text_BugCatcherWade1_Seen` | `route 31 wade notices pikachu` |
| Blackthorn Gym | Clair | before her battle | after “The world’s best dragon master.”: “LANCE told me a KANTO trainer beat him. So you’re the one. Don’t expect me to be impressed.” | `BlackthornGym_Text_ClairIntroText` | `blackthorn clair knows the player from lance` |

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

Willing partner responds to Silver in Dragon’s Den. Since 2026-11-02 (story audit T5), if the player saw him waiting at Goldenrod’s Center (`FLAG_SV02_SEEN`, either answer), he adds before his last line: “That time at the CENTER in GOLDENROD... You didn’t have to stop by.” A callback; nothing is written. Replay tests `dragons den silver remembers the center`, `dragons den silver another round after the center`.

### FG01 — Seven people and one HDMI cable

**Trigger:** Native Pokédex obtained; before first Kanto Hall of Fame; current group stage is FG01. Since 2026-10-25 it plays by itself on entering Viridian (`FG01_Arrival`, from the town's frame table): distorted flashes, Giratina over the south road, the seven thrown down onto it, the camera framed on them; the player then walks up, answers (a choice that can't be cancelled) and the group walks north into town. The dialogue was rewritten in the same voices.

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

**2026-11-09 (story copy H1, KR-112):** the camp has the Poliwag’s puddle beside it (Route 4, 87–88,14–15) and the lines lose the cave: Nick’s “Don’t use the puddle yet”, Jon’s “leave the fucking clearing”. **2026-11-10:** the echo cliff is built over the camp (the owner: “Yeah”): the shelf’s edge rises into a wall at 78–88,7–10, its face looking down on the clearing, so the echo stays: LB “So you heard the echo”, Brian’s room “has a cliff, an echo and a working alarm system”. Replay tests `route 4 the friends camp by the puddle`, `route 4 the friends camp the echo cliff`, `route 4 the echo cliff over the camp`.

### FG04 — Everybody has a partner now

**Trigger:** Native Pokédex obtained and Cerulean visit; before first Kanto Hall of Fame; current group stage is FG04.

**Status:** IMPLEMENTED. 22 primary conversations / 51 choices / 28 battle outcomes in bounded native 36-series checks. See this event’s original build and staged scope.

**37C source:** [`FG04_Interact`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:508). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md).

**2026-11-09 (story copy H5, KR-112):** Nick says Tim’s Spearow “can fly around this square” (it was “this picnic area”). Replay test `cerulean the friends camp in the square`.

### FG05 — Tim discovers the ferry schedule

**Trigger:** Native Pokédex obtained and Vermilion visit; before first Kanto Hall of Fame; current group stage is FG05.

**Status:** IMPLEMENTED. 22 primary conversations / 51 choices / 28 battle outcomes in bounded native 36-series checks. See this event’s original build and staged scope.

**37C source:** [`FG05_Interact`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:648). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md).

**2026-11-09 (story copy H2, KR-112):** the clerk: “This is the square. The boat leaves from the pier.” A ferry board stands by the camp (Vermilion, 31,17): “VERMILION FERRY / Departures for the islands from the pier. Ask the clerk for fares.” Replay tests `vermilion the friends camp and the ferry clerk`, `vermilion ferry board`.

### FG06 — Two very different coaching styles

**Trigger:** Native Pokédex obtained and Route11 visit; before first Kanto Hall of Fame; current group stage is FG06.

**Status:** IMPLEMENTED. 22 primary conversations / 51 choices / 28 battle outcomes in bounded native 36-series checks. See this event’s original build and staged scope.

**37C source:** [`FG06_Interact`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:765). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md).

### FG07 — Manifesting a room

**Trigger:** Original Celadon Rocket clearance flag; before first Kanto Hall of Fame; current group stage is FG07.

**Status:** IMPLEMENTED. 22 primary conversations / 51 choices / 28 battle outcomes in bounded native 36-series checks. See this event’s original build and staged scope.

**37C source:** [`FG07_Interact`]([LOCAL_WORKSPACE]/_local/worktrees/pikachu-bike-37c-dev/data/scripts/friends_story.inc:911). [Exact dialogue / choices / original captures]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md).

**2026-11-09 (story copy H4, KR-112):** the restaurant owner comes to fetch them (“There you are!”); Brian measures “the bench by the pond”. Replay tests `celadon the friends camp the restaurant owner`, `celadon the friends camp later`.

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

### FG-D — Someone louder than Jon

**Trigger:** Cianwood City: Johto state seeded and the Fog Badge (`JOHTO_FLAG_BADGE04_GET`, the Surf that reaches Cianwood); before the Johto Hall of Fame; the Friends' stage at FG17 or FG18. Scene 26 plays beside the stage (#120's shared machinery): Cianwood never moves the stage, and the scene retires once the stage moves past FG18. The player reaches Cianwood before Amphy is healed (FG18's gate), so it opens at FG17 too, not only after FG18 as the handoff's table has it. Once seen, the group is gone after that visit. Jon, Brian and Tim stand on the beach by the water below the Pokémon Center (camp 32,49: Jon 31,47, Brian 32,47, Tim 33,47); the Blackbelt, Primeape and Hoothoot appear just below them (30–34,48).

**Status:** IMPLEMENTED 2026-11-10 (KR-121; the owner: "Yes just make sure you are following their personalities as I required originally"). Receipt `0x959`. Replay tests `cianwood the friends meet someone louder than jon`, `cianwood the friends answer what happened to jon`, `cianwood no friends before the fog badge`, `cianwood no friends after the johto league`.

**Source:** [`FG_D_Interact`](../../engine/data/scripts/friends_story.inc); the draft is in [friends-new-event-scripts.md](friends-new-event-scripts.md).

A Blackbelt counts his push-ups at the top of his voice. Jon asks if he's okay; Brian points out what that means, coming from Jon; Tim has been waiting months for this. The Blackbelt asks if Jon shouts with his Primeape. "Because I say it once and then I wait." Primeape throws three clean punches and looks back at him; the Blackbelt tries his next push-ups at a reasonable volume. Menu "That was impressive" (Jon: he'll start yelling again just to ruin it; Brian: that's his proud voice) / "What happened to Jon?" (Jon: "I'M RIGHT FUCKING HERE."; Tim: the loud Jon still lives in there, Primeape just doesn't need him). The menu stays on later talks during that visit.

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

The October 19 Friends handoff is design input: FG-A–FG-G, dialogue/voice rework, new final-battle lines, repeat-early-battle changes, bespoke Nao/Stranger art and other listed polish. The owner approved the FG-A–FG-F drafts on 10 November ("Yes just make sure you are following their personalities as I required originally"). Its state allocation was audited the same day: the new scenes are scenes 23–29 with the handoff's receipts 0x956–0x95C (scene 23 + n has receipt 0x956 + n). No code, script or open branch uses those bits; they sit in the saved Kanto flags with the Friends' others, after the stage (0x94B–0x94F), invitation (0x950), loss (0x951–0x954) and reunion (0x955) bits, and 0x95D–0x95F stay required-zero. The new scenes play beside the stage, which keeps its 0–22 placements and never holds 23–29: each opens while the stage is at the placement next to it and retires when the stage moves on. The handoff's 29-placement order table is not adopted: it would renumber the stage of every existing save.

| Draft ID | Proposed scene | Proposed location / gate | Current status |
| --- | --- | --- | --- |
| FG-A | Tim finds the resort | Kindle Road below Ember Spa; Bill's first Sevii trip over, Friends at FG11 or FG12 | BUILT (KR-124), replay-tested |
| FG-B | The road nobody paved | League West Pass; Champion, Oak's Johto directions given, Friends at FG12 | BUILT (KR-125), replay-tested |
| FG-C | The tower that sways | In front of Sprout Tower; Zephyr Badge, Friends at FG13 or FG14 | BUILT (KR-126), replay-tested |
| FG-D | Someone louder than Jon | Cianwood beach, below the Pokémon Center; after the Fog Badge | IMPLEMENTED 2026-11-10 (KR-121); see FG-D below |
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
