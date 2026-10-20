# The Road Beneath the Rainbow — engineering handoff

**Status:** authored design begun October 14, 2026, with October 15 additions including the [friends' full Kanto-to-Johto story](friends-from-the-other-side-story.md). **Implementation, build and gameplay tests in this writing task: NOT RUN.** This document accompanies the [complete story and dialogue](kanto-johto-rainbow-story.md) and [Black Tide / Shadow Lugia chapter](johto-shadow-lugia-story.md). Additional Gen 3+ legendary stories remain deferred except the expressly requested Giratina role below. The current request authorizes story writing; it does not execute an implementation milestone or message another task.

## Integration contract

Use the current merged FireRed/HnS campaign as the baseline. Add this story around original events, with small scene hooks and repeatable conversations. Preserve original dialogue required to understand quests, rewards, battles and gates, with the explicit Black Tide and October 15 starter exceptions below. RB/MW additions remain optional. **The owner now requires defeating or catching three Rocket-created bird replicas before the Whirl Islands Shadow Lugia battle.** This extends the existing Silver/Lugia path's pre-League progression; it is not universally optional. The original Kanto birds remain unchanged, superseding the briefly considered relocation plan.

The established journey is **Kanto League victory → Oak referral → return to Indigo → western pass → New Bark → Elm's adapted research introduction**. Original credits/Pallet return remain. Native Kanto `FLAG_SYS_GAME_CLEAR` controls the pass; the similarly named later-Sevii Champion flag does not. The [travel report](indigo-west-pass-results.md) records candidate26's bounded staged-checkpoint tests, not a naturally completed campaign. The [campaign requirements](johto-campaign-integration-requirements.md) govern trainer continuity, independent regional state and original content.

This package must preserve:

- The player's existing identity, team, starter history, PC, money, Bag, Pokédex, field permissions, and independent Johto rival/badges. New games use the Pikachu opening described below; existing saves are not rewritten. Preserve the Kanto rival's role and encounter gates; an Eevee team adaptation is a recommendation awaiting a final design decision.
- Oak's parcel/Dex sequence, Pokémon Tower/Fuji and Poké Flute reward, Celadon Hideout, Silph Co., both regional League flows, Elm/Mr. Pokémon/Silver, Amphy, Lake of Rage, Radio Tower, Kimono events, and original Sevii gates.
- Existing Ho-Oh/Lugia selection, Wings, tower access and native final encounter bookkeeping, level and retry policy, plus Black Tide's explicit additional Whirl Islands gate and corrupted presentation. RB/MW scenes grant no new items, Pokémon, badges, experience, money or field abilities. LG bird battles intentionally permit ordinary captures and normal battle experience; they do not supply scripted Pokémon gifts or progression items.
- Original Pokémon Mansion journals, Celio's Sevii network completion, Cerulean Cave guard and native Mewtwo encounter. Hidden Mew sightings do not add or repair a Mew acquisition route.
- Current native-save ownership, original map/layout identities, script actor identities and the protected reserve. No new server state, multiplayer work, source import, save-layout expansion or remote publication is included.

## October 15 addition — Pikachu and the Kanto starters

**Owner direction:** Pikachu is the default starter for new games, replacing the initial Bulbasaur/Charmander/Squirtle selection. All three original starters become obtainable through encounters during Kanto. **Proposed scene design:** see “A team that chooses you” in the [story treatment](kanto-johto-rainbow-story.md). This is a new design addendum; implementation and tests for these changes are **NOT RUN** here, and no other task has been messaged.

| Design ID | Hook | Result |
|---|---|---|
| ST01 — First partner | New game's Oak starter transaction | Grant Pikachu exactly once through the real starter/naming path; complete the adapted rival opening, then allow RB01. No extra original starter grant. |
| ST02 — Little guardian | Optional Cerulean caretaker interaction, before or after Misty | Short care scene, then accept/later Bulbasaur offer. No hidden Pikachu-friendship requirement. |
| ST03 — Someone came back | Optional Route 24 interaction after the original Nugget Bridge sequence | Short shelter scene, then accept/later Charmander offer. No clock timer, paid item or replacement bridge reward. |
| ST04 — Harbor helpers | Vermilion introduction; recruitment after the native Thunder Badge | Squirtle rescue scene and accept/later offer. Preserve ship, Cut and Gym progression. |

ST labels are conceptual, not allocated constants. ST02–04 are optional, independent, available on later visits and each grant at most one individual. They grant real Pokémon, an explicit exception to RB/MW's cosmetic-only rewards. Set receipt state only after successful native delivery. Use the verified native gift path: if it cannot deliver to party/PC, retain the offer and give an accurate instruction to make room. A decline, full party/storage or interruption must never lose the gift or consume its receipt. Do not use species ownership or Pokédex state as a gift receipt. Save/reload and region initialization must preserve actual receipts without replaying grants; allocation must follow the current registry audit, not assumed spare bits.

Retain Oak's parcel, Dex, original tutorial/progression and rival win/loss recovery. Audit every original starter-choice read before changing it: species indices, rival parties and later dialogue may depend on the old three-way choice. **Recommended but undecided:** Blue receives Eevee, with a coherent full Kanto team progression. Do not put an invented fourth index into a three-entry table or silently choose an evolution scheme. Silver's independent Johto starter relationship is unchanged; Elm does not grant a second starter.

Pikachu's role in RB01 is bounded scene staging. Permanent following, Yellow-style mood screens, refusal to evolve and mandatory party presence are not requested features. Existing saves retain their starter, rival history and party; do not replace or retroactively grant Pikachu. Define eligibility for the three new gifts on supported older saves without inferring previous receipt from owning the species. Later narrative must work if Pikachu is boxed, evolved or absent. Recruitment does not gate either League or the existing legendary arcs.

Before shipping, verify the actual early-game encounters and moves give a reasonable route through Brock with Pikachu as the starter. Do not invent a scripted Electric immunity bypass or claim the old three-starter balance is automatically adequate. Levels/moves and the rival choice need explicit design notes against the current build.

**Acceptance — all NOT RUN:** fresh Pikachu grant/naming; rival win and loss; lab exit and parcel/Dex; RB01 exactly once; natural route through Brock; each gift accepted/declined/revisited; party/storage full; interruption; gifts in different orders; ordinary Save/full quit/Continue after every grant; travel to Johto and back; supported older starters and rival histories unchanged. Verify no duplicated starter balls, gifts or receipt resets, and no new mandatory party requirement. Existing implementation evidence for RB/MW/LG does not validate this addendum.

## October 15 addition — recurring Rocket trio and rival development

The owner's accepted direction adds **Jessie, James and Meowth**, **Blue happily pursuing science under Oak after the first League defeat**, and **Silver gradually learning trust between his native battles**. Blue has no added struggle with losing, resentment or consolation-career arc. His suggested Eevee starter remains undecided. The [event-by-event story draft](kanto-johto-rainbow-story.md#recurring-characters--rocket-research-and-trust) specifies JT01–JT04, BL01–BL03 and SV01–SV03, with proposed triggers, draft dialogue and choice outcomes.

**All ten events are design-only:** no bound source file/label, exact build, implemented dialogue or executed gameplay evidence is supplied by this writing pass. Tests are **NOT RUN** and actual in-game images are **pending**. These labels allocate no flags, trainer IDs, actors or save fields. Do not silently infer implementation from another story package's build or screenshots.

- **JT:** optional recurring schemes and a post-Lugia humane moment. Preserve native Rocket bosses, rewards and clearance state. JT04 is available only after the actual LG finale resolves; it supplies no replica victory, control-link result or native Lugia completion. Its rescued ordinary Pokémon do not become gifts. No mandatory Pikachu presence, scripted party theft or inventory loss. The current drafts add no new battles; an occasional trio battle needs a specified team, staging, outcome/retry policy and separate validation.
- **BL:** start after the native Kanto Championship/Hall of Fame/credits flow. Use the player's saved Kanto rival name. Oak's parcel, Dex, National Dex and regional-referral dialogue retain priority. Preserve native rival battles and rematches; identify any contradictory post-Champion lines and make only the contextual dialogue changes needed for a confident researcher who still enjoys battling. No Viridian Gym succession or imported later-Kanto storyline.
- **SV:** bind growth stages to verified native Johto rival milestones, not badge totals or the number of times the player has beaten him. Early caring gestures must remain compatible with his following native dialogue. Stronger growth waits for the existing story's lesson and late development. Use the saved Johto rival name; preserve the stolen partner, native order, teams and independent state.
- **All three:** interactions are optional, nonblocking and grant no new items, Pokémon, badges or field access. Keep native service actors and movement paths clear. Later scenes must introduce themselves honestly if optional earlier scenes were missed. Choose safe one-actor placement rules; no simultaneous duplicates of either rival or the trio. New durable receipts, if necessary, need the existing state-registry audit and compatibility process.

The implementing task must provide the standing event review for **each** changed event: actual build-bound local screenshots beside the source path/script label, exact implemented text in textbox order, choices and outcomes, and executed status. Capture the disguise/reveal and rescue aftermath where relevant. Keep images and private evidence under ignored `_local/`, embed absolute paths, and identify every missing image or unexecuted branch. Existing unchanged evidence keeps its original build label; no unrelated replay is required.

Focused checks, **all NOT RUN here**: skipped and out-of-order optional meetings; Blue's first-League versus post-League dialogue and retained rematches; Silver's early/late stage suppression; Pikachu absent/evolved/boxed and older non-Pikachu saves; trio absent during protected dramatic scenes; JT04 before/after actual Lugia resolution; every listed choice; native-service priority; normal Save/full quit/Continue with no replayed grants or changed regional history.

## Event package

`RB01`–`RB14` below are **design labels, not engine constants**. Location names are semantic targets; the engineer must bind them to the exact selected build and redesigned map geometry. Do not paste guessed coordinates or numeric flags into source.

| ID | Hook and eligibility | Action / dialogue reference | Completion and repeat behavior |
|---|---|---|---|
| RB01 — Opening sky | Fresh opening: first safe Route 1 arrival after starter and initial rival resolution; valid party; no active script/transition | Chapter 1: Pidgey shelter beat, overhead Ho-Oh flyby westward, one text box. Target 15–25 seconds excluding player reading. | One completion bit. Never replay on ordinary re-entry or cold Continue. No battle, Wing, Pokédex registration or automatic save. |
| RB02 — Oak records it | After original parcel delivery and Dex sequence finishes; RB01 seen | Chapter 1 Oak lines, offered through normal follow-up conversation | Repeatable short account; no bit needed. Oak's original quest/Dex dispatch always wins priority. |
| RB03 — Nao in Pewter | Optional talk at a safe spot outside Museum; before Ecruteak truth stage | Chapter 2 introduction and ask-about-bird/home options | One introduction bit; repeat becomes short travel dialogue. No Museum fee or badge prerequisite added. |
| RB04 — Fuji's answer | Original Fuji rescue and reward sequence fully complete; optional house conversation | Chapter 3 | One seen bit. If Nao is unknown, introduce her in one sentence first. Never re-run or intercept the Poké Flute grant. |
| RB05 — Recovered notebook | Original Celadon Hideout cleared; optional Nao interaction outside its entrances | Chapter 4, notebook already in Nao's possession | One seen bit. No item pickup, Rocket trainer, key-item ID or bag-capacity dependency. |
| RB06 — Silph echo | Original Silph liberation complete; appropriate existing scientist's optional follow-up | Chapter 4 equipment confirmation, two or three short boxes | Derive from base progress; no bit. Retain original scientist services/rewards and dialogue first. |
| RB07 — Oak sends you west | Existing post-Kanto League referral and repeatable lab directions | Chapter 5; use “your description” only if RB01 seen; otherwise “a remarkable bird has been reported in Johto” | Reuse original referral ownership and gate. New mystery text cannot suppress credits, Dex dispatch, pass access or Sevii. |
| RB08 — Elm's welcome | Safe boundary in existing adapted Elm introduction | Chapter 5, then original research briefing | Original Elm state owns one-time behavior. No new grant or initializer; no requirement to talk to Nao first. |
| RB09 — Ecruteak truth | Original Burned Tower release scene completed; optional talk on safe Ecruteak grounds | Chapter 6. Catch up missed Nao/recordings context in at most four boxes | One truth bit. Do not release beasts again, require captures, or open tower gates. Later repeats direct player to their current original quest. |
| RB10 — Amphy callback | Original medicine/cure complete; optional safe lighthouse-area talk | Chapter 7 Nao exchange; two cosmetic answer options | Repeatable from original progress, no bit/choice storage. No additional medicine delivery. |
| RB11 — Lance callback | Existing Mahogany Rocket event complete, at an available original Lance dialogue hook | Chapter 7 signal line | No new Lance spawn or movement required. If the exact baseline has no suitable post-event hook, fold this thought into RB12's director dialogue. |
| RB12 — Silence the copy | Original Radio Tower takeover resolved and all native rewards/dialogue returned safely; optional interaction inside the restored tower | Chapter 8. Explain auxiliary playback; offer “Disconnect it” / “Let the director do it.” Both stop the loop and preserve the notes | One completion bit; neither option changes rewards or morality. If missed, Nao offers this same conversation in Ecruteak after base tower clearance; say the director recovered the unit. No compulsory return trip. |
| RB13 — Welcome | Original Radio Tower clear + RB09 truth + RB12 aftermath; explicitly talk to Nao and choose “Ready” | Chapter 9, tower grounds rather than locked roof; “Later” returns control | One completion bit. Bird flyby or resolved-encounter alternate below. No battle, time-of-day restriction, legendary unlock or forced travel. |
| RB14 — Larger sky | Original Johto League clear + RB13 complete; optional Oak talk, then optional Route 1 interaction | Chapter 10 letter, then Pidgey/sky scene | One letter bit + one epilogue bit. No additional Hall-of-Fame write or compulsory credits sequence. Repeat Oak talk is a short letter summary. |

Full chapter dialogue is writing copy, not engine-ready strings. Split into the target textbox's real line width and page limits, use its actual player-name substitution, and check font-supported punctuation. Preserve meaning when shortening.

## Additional Kanto package — The Quiet Stranger

`MW01`–`MW09` are also design-only labels. This package is part of the requested story proposal, with implementation still pending. The disguise is a scripted visual convention; it does not require a new battle form, ability, species or psychic-perception system. Use a consistent approved traveler graphic, a bounded reveal effect and the existing Mewtwo identity when available and qualified.

| ID | Hook and eligibility | Scene | Repeat / preservation rule |
|---|---|---|---|
| MW01 | Optional Viridian talk after parcel/Dex completion, before Cinnabar reveal | K1: questions the Pidgey rescue, or uses honest generic alternative if RB01 unseen | Mark this conversation seen; subsequent greeting is brief. Optional cosmetic Mew tail after player releases interaction. |
| MW02 | Optional safe Route 4 interaction after original Mt. Moon fossil event, before reveal | K2: restored Pokémon and choice; small psychic hint | Read original completion state, not whether a fossil is still in Bag. Preserve original fossil and scientist scripts. |
| MW03 | Optional Lavender interaction after Fuji rescue/reward, before reveal | K3: a home with an open door | Separate from RB04. Keep Fuji's normal actor placement; dialogue can be staged at the doorway without relocating him permanently. |
| MW04 | Optional Celadon interaction after Hideout clearance, before reveal | K4: Poké Balls and trust | Independent of Nao/notebook. No extra battle, key or Giovanni contact. |
| MW05 | Optional Silph interaction after native liberation/reward sequence, before reveal | K5: momentary disguise slip; Mew in distance | Preserve Master Ball/Lapras/service handling. Use a safe area after native scripts unlock. |
| MW06 | Optional Cinnabar interaction after the original Mansion Secret Key discovery, before native Mewtwo encounter resolves | K6: reveal and answer choices | One reveal bit. Keep original diaries untouched. Read completion independently of current Key possession; avoid claiming the player read a diary unless that is known. |
| MW07 | Optional Route 22 talk after MW06 | K7: Champion question before Kanto League clear; retrospective line afterward | Suppress once the native fought state closes the encounter; a flee alone does not do this. Never share original rival trigger coordinates or block the League route. |
| MW08 | Existing native Cerulean Cave Mewtwo interaction, only after its original access requirements | K8: familiar reveal if MW06 seen; self-contained introduction if not; Face / Leave prompt | Leave retains native availability. Face hands off to the unchanged native encounter. Replay the invitation until the encounter resolves; no new fight state or item. |
| MW09 | Safe later cave-exit interaction once native Mewtwo fought state is set | Neutral reflection and optional distant Mew glimpse | One epilogue bit. Do not infer capture versus defeat from the fought bit. No fake escape after capture, duplicate actor or invented retry. |

Use individual scene-seen facts where needed; native progression suppresses obsolete traveler appearances after MW06 and native Mewtwo resolution. Do not force a linear MW01→MW05 chain: players can visit optional Kanto locations in different orders. The reveal is understandable even if every earlier stranger scene was missed. Optional prior scenes are not prerequisites for battling Mewtwo.

Mewtwo's actor is unique within this story. Never show traveler and revealed forms together. On a save where the native fought state has closed the Mewtwo encounter, suppress earlier active-observer scenes and offer only neutral retrospective text. The inspected native script sets `FLAG_FOUGHT_MEWTWO` for capture and defeat, but not fleeing. A flee therefore does not permanently complete this arc or remove the native retry. Late adoption must not respawn a closed encounter or imply a caught Mewtwo has secretly left the player's PC. Neutral prompts must not claim earlier sightings that never occurred.

### Mew is scenery, not a new hunt

Use four to six brief, spaced glimpses across the selected stranger scenes. Exact selection is an asset/budget decision; K1, K3, K5, K6 and MW09 are the preferred beats. Mew watches from outside conversational space, without a question marker, battle interaction, item or achievement counter. The first appearances should be easy to miss; K6 can show enough of Mew to reward recognition.

Do not add a permanent Mew icon to every map or hide progression behind spotting it. Each glimpse belongs to its host scene, so no new collectible-state system is needed. Hide Mew with a dedicated transient actor/effect lifetime, never its existing native encounter flags. Do not globally alter unrelated sprites to simulate invisibility.

Candidate26 already selects Faraway Island maps with a native Mew hide-and-seek/level-50 encounter and an Old Sea Map-gated harbor route. Natural item acquisition/reachability is **not verified**: the apparent reward writer is in omitted later-Kanto content. This story neither promises Mew is obtainable nor supplies the missing item. If the native Mew encounter is already resolved, omit the wild-observer visual instead of resetting it or inventing another unique Mew. Check the actual native state, not party species alone.

### Mewtwo's original finale remains authoritative

Read-only candidate26 source inspection found the Cerulean Cave guard removal in Celio's completed Ruby/Sapphire network sequence, and native FireRed's level-70 Mewtwo encounter. Preserve those gates and outcomes. Do not use first Kanto League clear alone, add the duplicate HnS level-80 Mewtwo, require this story to unlock the cave, or require Sevii/Mewtwo before Oak sends the player to Johto.

Before implementing MW08, bind the exact caught/defeated/fled branches and safe post-battle hooks. Added text must run after native outcome bookkeeping and must not consume the encounter when “Leave for now” is selected. Show the catch-specific reflection only immediately after bookkeeping while the actual battle outcome remains available. At later exits or after cold Continue, use neutral reflection: the durable fought bit cannot distinguish capture from defeat. Do not infer capture from party/PC species or add a durable outcome receipt without a separately reviewed allocation. A catch remains a native battle outcome, not a scripted gift or story reward.

## Black Tide — required Shadow Lugia arc

See the [complete scene treatment](johto-shadow-lugia-story.md). Latest owner correction is authoritative: these are **separate evil/corrupted bird replicas made by Team Rocket**, used to create Shadow Lugia. Do not migrate, remove, reset or consume the original Articuno, Zapdos or Moltres encounters. Owning a Kanto bird is valid but irrelevant to resolving its Rocket replica.

### Native campaign integration

Keep Baoba's Gold/Silver selection. On the Silver/Lugia path, the existing Radio Tower/Wing and Kimono/Bell chain establishes the Lugia encounter. Introduce the attack at a safe exterior approach before the final chamber interaction. Defer the final chamber's normal appearance/ritual as needed until the bird links are stopped, retaining earned items, original Kimono battle completion and ceremonial choreography with context-appropriate dialogue. Do not replay grants or mutate native quest state to pretend a ritual or battle has finished.

The existing Reception Gate checks theater state at least 8 before the Johto League. The native Lugia story resolution writes that state. Therefore **three replicas → Shadow Lugia → the existing completion → League access** is the intended new Silver-path sequence. All bird arenas, healing/return routes and recovery interactions must be reachable before that League gate. Never gate a required replica behind the Johto Champion flag, Cerulean Cave/Sevii completion or a later-generation encounter.

On Gold/Ho-Oh, preserve the selected Ho-Oh story. Black Tide becomes available when Whirl Islands Lugia's native later encounter actually becomes accessible. Source contains a state-4/level-70 Lugia branch and a Hall-of-Fame rematch-clear writer, but exact natural access is **NOT RUN**. The omitted later-Kanto Pewter Silver Wing giver is not a valid promised route. Audit this before claiming the new arc works on both branches; do not auto-grant Wing/Bell, flip Baoba's choice or claim first Johto Championship alone is verified sufficient.

The new condition applies to **Whirl Islands' encounter**. Native FireRed Navel Rock remains a separate potential Lugia encounter with its own flags and ticket conditions; natural access is unverified. Do not silently disable it, merge its identity with Whirl Islands, or advertise a game-wide “no Lugia before the birds” guarantee. A broader unique-Lugia acquisition policy is a separate product decision.

### Event and result contract

All LG identifiers and state names are conceptual; allocate nothing from these names alone.

| ID | Eligibility and scene | Successful result / repeat policy |
|---|---|---|
| LG01 — Coastal warnings | Original Radio Tower resolved; safe optional Olivine/Cianwood sailor dialogue | Flavor only. Provides directions appropriate to current native availability. No Wing, Bell, early warp or quest-completion write. |
| LG02 — Attack on Lugia | Native Whirl Islands eligibility established; first safe approach; no active native ritual/battle | Show the three corrupted replicas attacking Lugia and causing the Shadow state. Record attack scene once. Return control with healing and exit routes available. |
| LG03 — Articuno replica | LG02 complete; ice encounter unresolved | Ordinary battle. Player win or successful capture records this replica resolved and disables its link. No original Kanto bird flag is read or written. |
| LG04 — Zapdos replica | LG02 complete; electric encounter unresolved | Same outcome contract, independent of other replica order. |
| LG05 — Moltres replica | LG02 complete; fire encounter unresolved | Same outcome contract. Any of the three can be last. |
| LG06 — Three links broken | All three replica results resolved; safe next dialogue/transition | One short loss-of-signal scene. Lugia remains Shadow; expose the final approach/ceremony. No native final-completion state yet. |
| LG07 — Shadow Lugia | Native encounter still eligible AND LG03/LG04/LG05 resolved AND LG final-resolved is false; player chooses Face rather than Prepare | Present corrupted Lugia; run selected native level/catch behavior. Player win or capture restores ordinary Lugia and completes through the native story/postgame branch. Bird results persist if player loses or flees. |
| LG08 — Coast restored | LG07 actually resolved, at a safe aftermath hook | Clear local storm effects, record story closure, use outcome-appropriate immediate text; repeat/late text is neutral. No additional legendary gift or duplicate battle. |

For each replica, proposed durable values are **unresolved / defeated / caught**. Only the actual player-win and successful-capture outcomes resolve it. Player loss/blackout, fleeing, teleporting, failed capture, interrupted battle and unknown outcomes do not. After an unresolved attempt, the same encounter remains retryable. A resolved replica never respawns or awards another capture/experience payout. All three results count equally toward Lugia; no requirement to catch all three or hold them in the party.

Use the new replica's event identity, not species ownership, Pokédex caught bits, native `FLAG_FOUGHT_ARTICUNO/ZAPDOS/MOLTRES`, or imported HnS bird hide/reset flags. Original Kanto/Sevii bird state is independent and must remain byte-preserved except normal shared Pokédex effects of legitimate catches. The rescued replicas are ordinary members of their respective species after conditioning breaks; a player may intentionally own both the original and a replica.

Captures use the actual native party/PC delivery path and preserve the caught individual's data. Do not delete the caught Pokémon and grant a replacement to simulate restoration. Full party routes to normal storage; inability to catch does not block defeating the bird. Final Lugia similarly preserves its caught individual, original level and battle result. Verify all loss/blackout branches explicitly: do not let a default fallthrough mark the new story or native final quest complete after a player loss.

### Shadow presentation and scope

The design requires distinct corrupted bird visuals and recognizable Shadow Lugia in the final battle. Restoration returns each captured Pokémon to ordinary presentation before normal party/PC use. The default design uses the existing species identities and native capture/experience systems, with encounter-specific presentation. Persistent Shadow forms, custom Shadow moves, a heart gauge, a purification service and permanent stat changes are **not designed or implicitly authorized** by this treatment.

A bounded candidate26 source check found `SPECIES_LUGIA_SHADOW = 1435` defined in `include/constants/species.h`, but no corresponding species-info/form/graphics/encounter implementation in that check. The ordinary Lugia entry and assets are present. **Do not instantiate that unused constant, invent a supported form, or treat the existence of an ID as asset readiness.** Corrupted sprites/palettes/effects and safe per-encounter rendering still need real implementation and validation. An ordinary Lugia sprite with explanatory text does not satisfy the requested Shadow Lugia presentation.

Replica levels, moves and any encounter-specific balance are an explicit implementation design item: qualify them against the existing level-50 story / level-70 postgame Lugia and the carried Kanto team. Do not silently rebalance ordinary Articuno/Zapdos/Moltres/Lugia globally. The story names encounter areas by function; actual positions must be selected from safe reachable map geometry. Any required new pocket or asset is a measured scope item, not an assumed existing map.

### Durable state and existing saves

In addition to RB/MW state, this arc needs separate logical attack-seen, three replica outcomes, links-off-seen and final-resolved facts. Derive remaining counts and active local weather from those facts. Exact packing, IDs and version handling require the existing save audit/registry process; no native padding, protected reserve or presumed spare regional variable is allocated here. Use the coordinator's existing coherent-save path. Source input labels must bind to the right regional/native namespace in the generated script packet.

Ordinary Save/full quit/Continue must preserve each result and restore a safe playable field. Scene/battle temporary state must not count as a completed win. A save after two resolved birds still needs only the third after reload. No automatic save or irreversible party change is introduced by a cinematic.

Native Hall-of-Fame logic can later reactivate Lugia. LG final-resolved must prevent a second Shadow crisis even if native encounter eligibility returns. Any preserved native later encounter uses ordinary Lugia presentation and its native policy. Never reset the replica outcomes or replay their catches, the corruption cinematic or the crisis-closure rewards. Apply any explicitly reviewed older-save exemption consistently rather than attempting the crisis on an already exempt encounter.

For supported existing saves, use reliable Whirl Islands encounter evidence rather than `VAR_COMPLETED_LUGIA = 3` alone, since Gold-branch suppression also uses that value. Do not respawn or confiscate an already caught/resolved Whirl Islands Lugia to force the new chapter. Define a reviewed retrospective/skip compatibility policy for those saves without pretending LG battles were played. Original Kanto bird catches never need migration or reset. A flee with native retry available is not final closure. Unknown or ambiguous older states need explicit compatibility treatment before adoption, not guessed history.

### Required checks — all NOT RUN

- Every one of the six replica encounter orders; mixed catches/wins; all caught; all defeated; both full-party storage and inability-to-catch cases. All-three gate must be exact.
- Flee, teleport, player blackout and interruptions at each encounter: no false success; no repeated reward from already resolved birds; normal return routes and healing remain usable.
- Normal Save/full quit/fresh Continue after introduction, one bird, two birds, all three and final victory/capture; all original Kanto bird flags, party/PC and regional progression preserved.
- Original Kanto/Sevii birds remain present under their original gates before and after this quest. Caught/traded original birds never satisfy replica objectives; replicas do not reset or hide originals.
- Silver-path natural reachability before the Johto League and correct native theater/League completion only after LG07. Gold-path actual later eligibility and no early branch/item grants.
- All final Lugia outcomes, including player loss: corrupted presentation, restoration, capture preservation and native story/postgame bookkeeping; prepare/leave and retries do not repeat the bird phase.
- Already-resolved or ambiguous supported older Lugia saves, branch-suppressed state 3, and separate Navel Rock state must not create false past encounters or duplicate story rewards.
- Exact-build ROM/RAM/save and sprite/palette budgets; bounded local weather/camera/actor cleanup; ordinary bird/Lugia rendering elsewhere unchanged.

## Ordering, catch-up and player control

**Original scripts take priority over optional RB/MW scenes.** LG deliberately inserts the documented Whirl Islands gate and presentation hooks; those must compose with original transactions and completion rather than compete with them. Do not chain unrelated scenes inside a native reward transaction, battle return, auto-save, naming screen, map transition or script lock. A safe later conversation is preferable to extending a crowded native cutscene. Each new script releases every lock and restores camera, follower visibility, weather, palette, music and temporary actors on every exit.

Kanto's middle routes are not a fixed linear itinerary. RB04 and RB05 must make sense in either order. A first Nao meeting in Lavender or Celadon includes her name and hometown, but never asserts the player met her in Pewter. `NAO_INTRODUCED` can be set by any of those introductions or RB09. Optional callbacks never advance or roll back original story state.

For a player arriving in Ecruteak after the Radio Tower is already clear, use this order across separate interactions: **brief introduction/truth → recovered-unit aftermath → explicit welcome invitation**. Set only the scenes actually completed. Catch-up does not mark missed Kanto scenes as seen. Nao can summarize the notebook theft even if RB05 was never played; that theft is her history, not a claimed player action.

Nao's active location is resolved from original progression plus the new scene states. Only one version is visible at a time. Johto-stage Nao takes priority over old Kanto placements; optional Amphy placement must not remove her from the Ecruteak finale or force backtracking. If an optional location is missed, its core information is recoverable through Ecruteak dialogue. NPC placements must not block doors, original movement paths, interactable objects or return routes.

The opening scene may be automatic on a fresh run. Other added scenes start by talking/interacting, except short additions within already existing Oak/Elm dialogue. Do not interrupt every Gym victory. Choices are expressive and reversible; no hidden kindness score, daily timer, rare catch requirement or bad ending.

## Ho-Oh and Lugia coexistence

Read-only inspection of the pinned HnS input finds a pre-existing branch: Radio Tower 5F awards Silver Wing for `VAR_LUGIA_OR_HOOH = 1`, Rainbow Wing for `= 2`. The original Tin Tower roof has distinct Ho-Oh story/postgame encounters and caught/ran outcomes. These observations are **source evidence**, not proof of current merged-build runtime behavior. Rebind and check the actual generated campaign before implementation.

The existing Route 39 shadow flyby and Baoba's **Gold/Silver choice** own that selection: Gold sets Ho-Oh, Silver sets Lugia. Preserve the player's choice even after RB01; do not automatically answer Gold, remove the original shadow or treat it as a repeated RB01. The later original ritual follows Dragon's Den/Clair, Blackthorn's Elm call, Elm's Master Ball referral, Silver at the theater and the Kimono battle chain. The Ho-Oh route grants Clear Bell; the inspected tower guard checks that item. RB13's post-Radio-Tower welcome does not advance any of those steps.

RB01 never gives a physical feather or `ITEM_RAINBOW_WING`. Use light and silhouette as the motif. Nao's ordinary practice bell never becomes a Bag item or replaces Clear Bell/Tidal Bell/Crystal Bells or another native ritual object.

RB13 is a distant, noninteractive sky scene in both legendary branches. The Lugia route keeps its original selected progression plus Black Tide's required replica phase; no new scene switches the branch to Ho-Oh. No new “Ho-Oh seen” entry is written to the Pokédex, and no native legendary flag is written by the flyby.

Before RB13, inspect the actual native Ho-Oh encounter state:

| Existing state | RB13 presentation |
|---|---|
| No evidence of an actual prior encounter and no native legendary scene active, including mere suppression by the Lugia choice | Distant Ho-Oh overhead; no landable/catchable actor and no roof access change. The Lugia branch alone is not evidence of a Ho-Oh meeting. |
| Actual prior Ho-Oh encounter established by reliable native outcome state | Rainbow light over the tower, with no additional wild Ho-Oh or distant cry. Nao says: “When I heard about your meeting, I thought I'd missed everything. But this is our home. We can still make it welcoming.” Morty says: “A welcome can remain after a guest has gone.” |
| Prior-encounter evidence is ambiguous in the selected save/build | Use the rainbow-only alternate with neutral text: “I thought we'd need a miracle for today to matter. I'm glad we did this.” No claim of a previous meeting or new wild appearance. |
| Native legendary ritual/battle/return script active | Defer RB13 until normal field control and a later interaction. |

Use verified native encounter semantics, not “species Ho-Oh appears in the player's party,” as the branch test. The original Lugia Kimono branch sets `VAR_COMPLETED_HO_OH = 3` without a Ho-Oh meeting, so that value alone cannot prove an encounter happened. Trading/boxing a Pokémon must not rewrite the local legend. Never synthesize a caught flag, respawn, item or regional receipt. A later optional Nao line can acknowledge a proven native encounter; battle logic remains entirely native.

## State and save plan

Proposed logical facts are: `OPENING_SEEN`, `NAO_INTRODUCED`, `FUJI_SCENE_SEEN`, `NOTEBOOK_SCENE_SEEN`, `ECRUTEAK_TRUTH_SEEN`, `RECORDING_STOPPED`, `WELCOME_SEEN`, `LETTER_READ`, `EPILOGUE_SEEN`. Nine logical booleans do **not** establish that nine free engine bits exist. These names are design-only, with no numeric allocation or registered content version.

The observer arc adds logical scene receipts for MW01–MW07 plus MW09; `MW06_SEEN` is also the reveal fact. MW08 uses the live battle result for immediate text and the native fought bit only for durable closure, without a duplicate caught state. This is at most eight further scene facts, not permission to allocate bytes. Dialogue choice results and Mew sightings need no durable storage. The current 240 Johto persistent-variable positions are already mapped, so do not assume a spare stage variable exists.

Audit unused capacity and every read/write reference before binding. Kanto events happen before Johto initialization: they must use durable storage that survives that initializer without causing early Johto seeding. Do not borrow temporary map variables, original Oak/Elm/Rocket flags, reserved bytes, native padding, or flags merely presumed unused. Any content-meaning/version change needs the registry and compatibility treatment required by the existing [save foundation](save-format-registry.md). This proposal does not allocate it.

Writes should use the current save coordinator and occur after the scene's effects are complete. Scene-local scratch variables and temporary actors are not durable state. Reloading the last ordinary save may replay unsaved dialogue normally; loading a save made after a completed scene must not replay it. No automatic save is added.

For supported older saves, define eligibility during an explicit compatibility review. Never infer “opening witnessed” from empty new bits. Prefer RB01 only for a fresh opening cohort; later players receive honest alternate dialogue and join at any currently eligible optional scene. An existing trainer returning to Route 1 must not be told this is their first day. Unknown save versions remain rejected under the existing policy.

## Assets, scope and capacity

RB/MW presentation: a recognizable distant Ho-Oh flyby; Pidgey staging; Nao's NPC representation; a small bell sound; a brief rainbow/light effect; a consistent stranger graphic; Mewtwo's reveal; small Mew glimpses. Reuse already approved, compiled resources where suitable, after checking their actual frame dimensions, palette use and ownership. Nao and the disguised stranger can use suitable distinct existing generic NPC graphics for the first content pass; unique portraits/art are later enhancements. Those scenes require no new music, animated film sequence, custom map, species or battle system. **LG adds new replica encounters, corrupted visuals and encounter staging**, whose actual assets and placement must be separately budgeted; the earlier RB/MW estimate does not establish that this larger package fits.

The opening prose describes a passing shower; implementation must restore the actual clock/weather state and support day and night without advancing time. At night use a brief prismatic glint rather than forcing daylight. New-game RB01 can stage the actual starter Pikachu, including with followers disabled, with no duplicate visible actor. Starter-neutral staging remains for supported older saves; never replace an unrelated follower or require Pikachu in later scenes. RB's opening/background bird actors must not become encounters or give items when interacted with; LG's replica actors are explicitly battle encounters.

The candidate26 [build record](indigo-west-pass-results.md) reports only **23,196 bytes of ROM free**, a **four-byte native main-save margin**, and a **protected 256-byte reserve**. These are a dated baseline, not available story allocations. Full prose size is not a reliable encoded-ROM estimate. Measure text, scripts, graphics, actor slots and palette/OBJ use against the exact next build. A recognized flying sprite/effect may require art work; report a missing resource rather than substituting an unrelated bird or calling an unrendered text box the requested flyby.

If the package does not fit, return a measured scope/budget decision. Do not remove original gameplay, consume protected reserve, expand cartridge/save capacity or silently omit the ending. A first implementation slice can be RB01/RB02 plus their persistence checks, followed by the Nao arc and complete resolution in a separately identified content build.

## Acceptance cases for the implementing task

All cases below are **NOT RUN** for this story proposal. Use fresh isolated B-owned native saves and record exact ROM/source identity. Staged checkpoints help isolate events but do not establish natural campaign reachability.

| Check | Expected result |
|---|---|
| Fresh Pikachu opening; supported older starters; follower on/off; day/night | ST01 grants once on new games; adapted rival sequence completes; older history retained; RB01 fires once for eligible fresh openings; recognizable Ho-Oh; control/effects restored; RB01 itself grants no item or Dex changes. |
| Opening then parcel/Dex progression | Original Oak triggers, parcel delivery, Pokédex and original gifts remain intact; added report appears only at a safe point. |
| Ordinary Save → full quit → fresh Continue after added milestones | Completed scene facts persist; identity, original campaign progress and collection remain intact; no repeated reward or initializer. |
| Lavender/Celadon in either order; skip Pewter | Nao introduces herself correctly; callbacks never claim unseen meetings; original battles/rewards remain usable. |
| Kanto Champion with new arc untouched | Oak/pass/Elm work under the original gate; no Sevii, National Dex or Ho-Oh prerequisite is added. |
| First Johto entry and repeated cross-region travel | Earlier story facts survive initialization; original independent regional progress and return routes persist. |
| Radio Tower, both legendary branches | Original takeover, director reward and subsequent quests complete; auxiliary loop has no extra Wing or branch write. |
| Late entry directly after Radio Tower / after Johto League | Catch-up gives truth, aftermath and invitation without false memories or required Kanto backtracking. |
| Welcome: eligible, choose Later, repeat talk, reload | Later exits safely; Ready completes once; finale never opens the roof or starts a battle. |
| Ho-Oh unresolved, actual prior encounter, ambiguous state; Lugia branch including Kimono completion | Correct visual alternate; no invented prior meeting from branch suppression, duplicate legendary actor, reset encounter, altered level/retry or false Pokédex record. |
| Route 39 Gold and Silver choices after RB01 | Both original options, earned Wing/Bell grants and Ho-Oh path remain intact; Whirl Islands additionally follows the documented LG gate without flipping the choice. |
| Observer scenes in different orders, or all skipped until Cinnabar/cave | Coherent introductions/reveal; original Mansion journals and campaign progress preserved; no retroactive scene completion. |
| Mewtwo native encounter before/after reveal; Leave / catch / defeat / flee; cold reload | Original Celio/cave gate and level-70 battle preserved; flee retains native retry; catch-specific text only uses live outcome; later text is neutral; no respawn, duplicate or forced catch. |
| Mew hidden glimpses, including native Mew already resolved | Cosmetic only; no Dex/Bag/caught/hide/Old Sea Map changes and no duplicate unique observer after resolution. |
| Native script overlap, battle/blackout/warp return and crowded maps | Added scenes defer; no stuck lock, actor conflict, broken movement, camera, follower, palette or weather state. |
| Johto League and Pallet epilogue | Native Hall of Fame/return preserved; letter precedes epilogue; optional scenes do not force a new save or end exploration. |
| Final compiled budgets and source review | Original map/story IDs and save layout preserved; measured resource use fits; new state has a reviewed allocation; no restricted materials or workflow files added. |

Record build/source checks separately from native gameplay. Final reporting should identify implemented event IDs, missing assets, measured budgets, exact save/content bindings, executed cases, unrun cases and owner-test needs. A successful build alone does not complete this event package.

## Active writing addition: Giratina and the seven friends

The owner's October 15 request supersedes the previous deferral. **Tim, Xavier (X), LB, Brian, Jon, Nick and Ham** now have a full proposed isekai comedy treatment in [Friends from the Other Side](friends-from-the-other-side-story.md): FG01–FG22, draft dialogue/choices, staged partner acquisition/evolution, seven introductory battle invitations and seven selectable final/rematch opponents. Their arrival, independent group growth, eventual homecoming and later visit span Kanto through the end of Johto. Sprites are still undecided.

The intentionally profane dialogue belongs to fictionalized adult versions of the friends. **"Nigga" may appear only in LB's dialogue addressed directly to Xavier, or Xavier's dialogue addressed directly to LB.** It must never address another friend, the player, an NPC or the group collectively; retain explicit recipient staging in the script. Do not infer their races or copy that usage into other characters. Tim's sex-worker/travel jokes stay non-graphic and refer to human adults; Pokémon and the main trainer are not sexual participants. LB's references must be accurate Drake titles that answer the preceding line, such as "it's all the same" → "First of all, NOTHING WAS THE SAME." Use the reference notes in the full draft; no lyrics or invented attributed quotations. Ordinary game characters retain their usual voices.

The owner's dialogue revision calls for sustained conversations across all FG scenes and expanded choice/outcome responses. Preserve each setup, response and payoff when splitting text into engine boxes. Do not reduce the scenes back to disconnected catchphrases or turn LB into a generic musician. Use optional follow-up interactions for pacing and budget where appropriate, and show any proposed substantial cuts for review. Longer dialogue does not authorize an unmeasured ROM/save expansion or removal of original content.

All new labels and state are design-only. Game source/script bindings, exact builds, implemented text and screenshots are pending; gameplay is **NOT RUN**. A future implementation must use the current audited save/state framework, preserve supported older saves and regional continuity, and measure scene/ROM/save capacity before allocating. No source, sprite, save, map or encounter edit is performed by this handoff.

The friends never block the main campaign, require a battle victory or take player Pokémon/items. Their battle wins/losses, successful acquisitions, current group stage and farewell/reunion state must not be conflated. Bind normal trainer rewards and blackout/retry behavior honestly. Set final teams from established partner history and actual campaign balance; seven individual opponents do not imply support for a seven-person battle.

Keep **Giratina nonobtainable**: no battle/capture, gift, egg, trade, party entry or story reward. Audit other active acquisition routes before claiming game-wide compliance. Its scripted return crossings expose no reusable player portal or Distortion World map. The friends' finale must work independently of the Ho-Oh/Lugia branch and optional legendary captures.

Apply the standing event review requirement to each FG event and battle: actual in-game images beside source labels, exact implemented textbox order, choices/outcomes, exact build and executed status. Captures and private evidence stay local in ignored _local/ paths with absolute image embeds. Missing art/captures and unexecuted branches must remain explicit; no older image is relabeled as current.

**Other Gen 3+ legendary story development remains deferred.** Do not expand Rayquaza, Latias/Latios, Deoxys, later-generation Regi or Arceus stories through this exception. Existing encounters are not removed. Shadow Lugia and the friends' scripted Giratina role are the expressly requested exceptions.

## Local source anchors for implementation review

These source observations used candidate26 and the preserved pinned input. Revalidate against the actual next implementation build; none is a new gameplay pass.

- [Route 39 choice](../_local/worktrees/johto-full-26-firered/data/maps/Route39_hns/scripts.inc), [Radio Tower Wing dispatch](../_local/evidence/johto-campaign-direction-01/pinned-script-inputs/data/maps/GoldenrodCity_RadioTower_5F_hns/scripts.inc), [tower guard](../_local/evidence/johto-campaign-direction-01/pinned-script-inputs/data/maps/EcruteakCity_SageOffice1_hns/scripts.inc), [native Ho-Oh encounter](../_local/evidence/johto-campaign-direction-01/pinned-script-inputs/data/maps/TinTower_RoofDay_hns/scripts.inc).
- [Celio progression](../_local/worktrees/johto-full-26-firered/data/maps/OneIsland_PokemonCenter_1F_Frlg/scripts.inc), [native Mewtwo encounter](../_local/worktrees/johto-full-26-firered/data/maps/CeruleanCave_B1F_Frlg/scripts.inc), [Mansion 3F journals](../_local/worktrees/johto-full-26-firered/data/maps/PokemonMansion_3F_Frlg/scripts.inc).
- [Native Mew scene](../_local/worktrees/johto-full-26-firered/data/maps/FarawayIsland_Interior_hns/scripts.inc), [Faraway harbor gate](../_local/worktrees/johto-full-26-firered/data/maps/OlivineCity_PortInside_hns/scripts.inc).
- [Whirl Islands Lugia](../_local/worktrees/johto-full-26-firered/data/maps/WhirlIslands_LugiaChamber_hns/scripts.inc), [Johto League gate](../_local/worktrees/johto-full-26-firered/data/maps/ReceptionGate_hns/scripts.inc), [separate Navel Rock Lugia](../_local/worktrees/johto-full-26-firered/data/maps/NavelRock_Base_Frlg/scripts.inc).
- [Original Articuno](../_local/worktrees/johto-full-26-firered/data/maps/SeafoamIslands_B4F_Frlg/scripts.inc), [original Zapdos](../_local/worktrees/johto-full-26-firered/data/maps/PowerPlant_Frlg/scripts.inc), [original Moltres](../_local/worktrees/johto-full-26-firered/data/maps/MtEmber_Summit_Frlg/scripts.inc), [species constants](../_local/worktrees/johto-full-26-firered/include/constants/species.h).
