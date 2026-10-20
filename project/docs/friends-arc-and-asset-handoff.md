# Friends Arc & Asset Handoff for Codex

October 19, 2026 · Owner: Malik. Exported from the Claude Doc "Friends Arc & Asset Handoff for Codex" (owner's editable copy: https://claude.ai/code/artifact/e33dabb6-6c67-46f6-a02a-c7e68f27b85a). If the two differ, ask the owner which is current. Companion file: [friends-new-event-scripts.md](friends-new-event-scripts.md).

This handoff tells Codex what to build next: fixed friend sprites, asset updates across the ROM, a reworked FG01–FG22, and seven new friend events that fill the map gaps. Full scripts for the new events and the rewritten final-battle lines are in `friends-new-event-scripts.md`.

## Scope and ground rules

Everything here fits the existing save layout. The seven new events use the ten spare Friends bits, and no new save bytes are needed.

**Build on:** the newest worktree (`pikachu-bike-37c-dev`, after 36P). Follow `AGENTS.md`: isolated build, no commits or pushes without approval, private art and evidence under ignored `_local/`.

**In scope**

1. Friend sprites: battle fronts plus full 9-frame walking sheets for all seven friends and Trail, built from the specs below. The pilot in `_local/art-handoffs/claude-friends-pilot-01/` is the starting point for Ham, Nick, LB, X and Trail.
2. Asset updates elsewhere in the ROM (Nao, the Stranger, Jenny, Giratina, the Black Tide replicas and others; see the asset table).
3. FG01–FG22 dialogue rework, using the rework notes below.
4. Seven new events (FG-A to FG-G) with the full scripts in `friends-new-event-scripts.md`.
5. The bug fixes from the earlier review that touch the friends: block or rework repeat early battles, fix `FG_FinalMenu`'s silent fallback, remove dead FG22 intro code, and merge the duplicate `FinalAfter` text.

**Do not change**

- Save structures, the protected 256-byte reserve or the four-byte SaveBlock1 margin.
- Original FireRed/HnS encounters, rewards or progression gates. Friends never block a route, gym or legendary event.
- Giratina stays unobtainable and never battles.
- Workstreams A and C.

**Capacity we're relying on**

| Resource | Available | This handoff uses |
| --- | --- | --- |
| Friends save bits `0x956`–`0x95F` (currently required zero) | 10 | 7 receipts (`0x956`–`0x95C`) |
| Placement field `0x94B`–`0x94F` (5 bits) | values 0–31 | 0–29 after reordering |
| Trainer IDs (768 capacity, friends use 626–639) | ~120 spare | 0 new |
| ROM headroom at 36P | 855,436 bytes | est. 60–90 KB (art + scripts) |

## Friend sprite specs

Each friend gets one signature read that survives at 1× on grass, indoor floors and cave tiles. The native-base method you approved for Brian and Trail stays; this adds the rules that pack-03 and the current pack-01 missed.

**Rules for every sheet**

- **Format:** overworld frames are 16×32, nine frames: down, up, left standing, then two walking frames for each direction. Right uses mirrored left. Battle fronts are 64×64, one pose. Both are 4bpp, 16 colors, index 0 transparent, colors snapped to GBA 5-bit values.
- **Value contrast:** clothing never shares the outline's value. The darkest clothing shade must be at least about 30 RGB steps above the outline color. That is the Ham problem.
- **One signature per friend:** a dominant color block or shape that no other friend uses on the same body area (table below).
- **Feet baseline:** the bottom pixel row of the feet matches Red's on every standing frame, so the friends don't float or sink in group formations.
- **Scale:** heads and bodies match the native FRLG trainers. Nick's current sheet is 32×32 per frame; confirm that's intentional (it doubles his OAM and VRAM cost) or rebuild him on a 16×32 base.

| Friend | Signature at 1× | Battle base / overworld base | Status | What still needs doing |
| --- | --- | --- | --- | --- |
| Brian | Knicks-blue jersey with orange trim, dark jeans, brown hair and beard | HnS Lt. Surge / FRLG Lt. Surge | Pilot, no pilot changes | Front: widen and heighten the head by about 2px; separate the crossed forearms with a highlight line. Walking frames. |
| X (Xavier) | Saturated blue hoodie, orange pants, dreadlocks | FRLG Oak / `psychic_m` | Pilot: hoodie saturated | Brian also wears blue and orange, so keep X's orange on the legs and Brian's on the jersey trim. Walking frames. |
| Tim | Bald highlight, blue gingham shirt, beard | FRLG Sailor / FRLG Balding Man | Pack-01, unchanged | Make the gingham a 2-color checker at 1× rather than noise. Walking frames. |
| LB | Bright white tank top, khaki cargo shorts | Emerald Brawly / FRLG Bruno | Pilot: tank brightened | Front pose is good. Walking frames. |
| Nick | Pink shirt with white dots, long brown hair, full beard | RSE Hiker / `fat_man_frlg` | Pilot: beard and belt line added | Hair volume still reads feminine. Pull the side hair behind the shoulders on the down frame and thicken the beard to the jaw. Settle the frame size. |
| Jon | Straw hat, red open vest, blue shorts | FRLG Tamer / FRLG Camper | Pack-01, unchanged | Owner's design reads as Monkey D. Luffy. Keep it if that's the joke. Otherwise swap the straw hat for a bucket hat or backwards cap and keep the red vest. |
| Ham | Charcoal tee and pants, near-black hair | Hoenn Cooltrainer M (mirrored) / FRLG Man | Pilot: clothes lifted to charcoal | Front: add one fold highlight on the pants. Walking frames. |
| Trail (player) | Navy cap with logo, rust jacket, white tee, green cargo pants | Red (mirrored) / Red | Pilot: cap brim fixed | Front face still picks up jacket orange near the mouth, so give the skin its own 3-step ramp. Walking frames and the bike/surf sets. |

**Acceptance check before integration:** render all eight down frames side by side at 1× on grass, Center floor and cave backgrounds (`lineup-down-1x-grass.png` shows the format). Each friend must be namable from color and silhouette alone. Then the owner signs off; passing format checks is not approval.

## Asset updates across the ROM

Two story characters still use generic NPC art, and that's the biggest visual gap outside the friends: Nao and the Stranger. The seven new friend events need no new art beyond the friend sheets.

| Priority | Asset | Current state | Update |
| --- | --- | --- | --- |
| 1 | **Nao** overworld (9 frames) | Generic NPC reused | Bespoke Ecruteak apprentice: dark hair in a low tie, plum or deep-red haori over plain clothes, small brass bell at the hip as a 2px highlight, satchel for the notebook. Base: FRLG Lass proportions. One palette. |
| 2 | **The Stranger** (Mewtwo disguise) overworld | Generic NPC reused | Plain grey long coat, raised collar, hat brim hiding the eyes; a faint lilac rim pixel on one edge as the only hint. Add one extra "veil wavering" frame: same pose with a tail-shaped lilac silhouette behind the coat, used by MW05 and MW06. |
| 3 | **James** in JT01 and JT04 | Speaks offscreen | Art already exists (33b). Script change only: place his actor on screen. |
| 4 | **Jenny** overworld | Owner approval pending | Review and approve or reject; no new art unless rejected. |
| 5 | **Black Tide replicas** after capture | Look identical to normal birds | No new art. Give caught replicas a distinct met location ("WHIRL ISLANDS RELAY") so the story stays with the Pokémon. |
| 6 | **Squirtle Squad leader** (ST04) | Normal Squirtle | Optional: a sunglasses variant of the Squirtle overworld sprite for the leader only, used in the harbor scene. One palette slot. |
| 7 | **Giratina presence** | Exact native frame and palette | Keep. Add a 2-frame shimmer (palette cycle on the existing frame) for FG01 and FG21 so the portal reads as active. |
| 8 | **Trail** bike and surf sheets | In progress (37a–37c worktrees) | Build from the Trail spec above once the standing sheet is approved. |
| 9 | **Title screen** | `title-screen-isekai-01` in progress | Not reviewed here; keep it on its own track. |

Nothing in this table changes collision, maps, encounter tables or save data.

## Voice bible

The current script's biggest voice problem is Nick: he has about 31% of all lines and narrates every scene. Spread the straight-man job around so each friend sounds like themselves.

| Friend | Sounds like | Sentence shape | Never | Arc: early → late |
| --- | --- | --- | --- | --- |
| Brian | Homebody, 2K brain. Everything is a living situation or a play call. Complains about walking, then quietly plans everyone's food. | Medium; deadpan; ends on a practical demand ("somewhere to sit") | Gets sentimental out loud without a joke on top | Wants a couch → builds Slowbro a bed |
| X (Xavier) | "Ground our energy," then immediately a budget, route and headcount. Hippie vocabulary on top of the most practical plan in the group. | Two beats: vibe phrase, then logistics | Mystical answers with no plan behind them | Has every plan → admits when a plan failed |
| Tim | Thailand and nightlife on the brain, cheerful and unbothered. Gets good at tickets and transport. | Short, upbeat, often a question | Graphic sex jokes; jokes about sex workers, Thai people or any Pokémon/child-coded character | Asks "what's in it for me" → helps a stranger for nothing |
| LB | Treats a phrase in someone else's line as the setup for an exact Drake album title. Defends the reference long after everyone moved on. Also just a guy with opinions who loves his Pokémon. | Normal talk most of the time; the reference lands, then the conversation continues | Lyrics; invented Drake quotes; a reference that doesn't fit the line before it; more than one reference per scene | Performs for the room → knows when someone needs a straight answer |
| Nick | Calm, obvious, kind; the 2K rival. Says the simple thing after everyone else overcomplicates it. | Shortest lines in the group | Explaining the scene to the player; summarizing what others just said | Keeps the group moving → patient battle coach |
| Jon | Loud, profane, confrontational with rules and objects. All-caps lines carry his volume. | Caps bursts; swears at things, not at Pokémon | Yelling at a Pokémon after FG15 | Shouts at Mankey → "We go together" |
| Ham | Sparse, delayed, strange interjections; acts before anyone else. | One line, often late, often wrong-sounding but right | Explaining himself; long speeches | Joke of the group → the one who already solved it |

**Dialogue rules (owner's, unchanged)**

- "nigga" only when LB directly addresses X, or X directly addresses LB. Never toward anyone else, the player or the group. All five current uses comply.
- **Presentation fix:** "(to XAVIER)" currently shows on screen as part of the speaker name. Drop the tag and make the address explicit in the line instead ("LB: X. Nigga, NOTHING WAS THE SAME.").
- Drake titles must be real album titles set up by the previous line: *Nothing Was the Same*, *Take Care*, *Thank Me Later*, *Views* are in use. New events add *If You're Reading This It's Too Late* and *For All the Dogs*, each with a setup line.
- Ham: "...cock" at most once per region. "I'm not a bitch" is at four uses; cut to two in the rework and add none.
- Tim's sexual references stay non-graphic, about consenting adults.
- Profanity is concentrated in Jon. Ordinary NPCs answer sincerely, which is the contrast that makes it funny.

**Scene shape:** a concrete problem, a real back-and-forth about it, one small action or realization, then a way back to the journey. Two or three friends lead each scene; the others get at most one line each. Target 20–28 text pages for a main path; the farewell (FG21) may run longer.

## Arc map

The arc grows from 22 to 29 events. The new events fill the four real gaps: Sevii, the Kanto-to-Johto crossing, the middle of Johto (Violet, Cianwood, Lake of Rage, Ice Path), and the postgame. Rows are in placement order; **new** marks the additions.

| # | Event | Region | Map and spot | Trigger (native progress) | Leads |
| --- | --- | --- | --- | --- | --- |
| 1 | FG01 Seven people and one HDMI cable | Kanto | Viridian outskirts clearing | Parcel delivered, Pokédex received | X, Brian, Jon |
| 2 | FG02 Brian invents camping badly | Kanto | Route 2 campsite | After FG01 placement | Brian, Jon |
| 3 | FG03 The acoustics are incredible | Kanto | Route 4, Mt. Moon exit rest area | Mt. Moon fossil taken | LB, Nick |
| 4 | FG04 Everybody has a partner now | Kanto | Cerulean picnic area (not the Bulbasaur garden) | Cerulean reached | X, Tim, Ham |
| 5 | FG05 Tim discovers the ferry schedule | Kanto | Vermilion public harbor | Vermilion reached | Tim, Brian |
| 6 | FG06 Two very different coaching styles | Kanto | Route 11 practice clearing | Vermilion access | Nick, LB |
| 7 | FG07 Manifesting a room | Kanto | Celadon street seating | Rocket Hideout cleared | X, Brian |
| 8 | FG08 Quiet outside Lavender | Kanto | Fuji's doorway, then interior | Fuji rescued, Poké Flute received | Jon, Ham |
| 9 | FG09 The group gets actual responsibilities | Kanto | Fuchsia-area public campsite | Fuchsia reached | Tim, Nick, Brian |
| 10 | FG10 A very bad job interview | Kanto | Saffron street | Silph liberated | Tim, X |
| 11 | FG11 The television in the water | Kanto | Cinnabar shoreline | Mansion Secret Key found | Brian, LB |
| 12 | **FG-A Tim finds the resort** (new) | Sevii | One Island, outside Ember Spa | First Sevii trip with Bill finished | Tim, Brian, Ham |
| 13 | FG12 Seven terrible spectators | Kanto | Pallet-side celebration | First Kanto Hall of Fame + credits | Jon, LB |
| 14 | **FG-B The road nobody paved** (new) | Kanto → Johto | Indigo western pass, outdoor road near the old construction barrier | Oak's Johto referral given, Champion barrier gone | X, Jon, Nick |
| 15 | FG13 No second character creation | Johto | New Bark public area | Elm introduction complete | Ham, Brian |
| 16 | **FG-C The tower that sways** (new) | Johto | Violet City, outside Sprout Tower | Zephyr Badge | X, Ham |
| 17 | FG14 Xavier reads the room | Johto | Ruins of Alph visitor area | Ruins accessible | X, LB |
| 18 | FG15 Jon learns one useful volume | Johto | Azalea outskirts | Slowpoke Well resolved | Jon |
| 19 | FG16 The move has a name | Johto | Goldenrod practice clearing | Before Radio Tower takeover | LB, Ham |
| 20 | FG17 A reflection that waits | Johto | Ecruteak public pond | Burned Tower scene done | Brian, X |
| 21 | FG18 Tim books the right trip | Johto | Olivine harbor | Amphy healed | Tim |
| 22 | **FG-D Someone louder than Jon** (new) | Johto | Cianwood beach, south of the Gym | Cianwood reached (Surf) | Jon, Brian |
| 23 | **FG-E The lake that was told to be angry** (new) | Johto | Lake of Rage shore, away from the Gyarados spot | Mahogany Rocket hideout cleared | LB, Tim, Nick |
| 24 | FG19 Nobody yells at the frightened Pokémon | Johto | Goldenrod public shelter | Radio Tower freed | Jon, Brian |
| 25 | **FG-F Ham goes first** (new) | Johto | Ice Path 1F, safe floor by the Route 44 entrance | Radio Tower freed; before Blackthorn Gym | Ham, Jon, LB |
| 26 | FG20 We actually know what we are doing | Johto | Blackthorn training clearing | Johto badge 8 + Dragon's Den | All (battles) |
| 27 | FG21 Everybody goes home | Johto | New Bark campsite | Johto League clear | All |
| 28 | FG22 Visitors with too much luggage | Johto | New Bark campsite, later visit | FG21 departure + map exit | Brian, X, LB |
| 29 | **FG-G Up six** (new) | Johto | Ecruteak pond (FG17's reflection) | FG22 seen + a later Ecruteak visit | Brian, Nick |

Each new event is optional, has no battle, grants nothing, and never blocks a path. If a player passes a placement without triggering it, the next placement retires it, same as today.

**Friends' teams at each new event:** FG-A uses the Kanto teams after FG09 (Rattata/Slowpoke, Oddish/Paras, Spearow/Krabby, Jigglypuff, Poliwag/Geodude, Mankey, Psyduck). FG-C adds Ham's Sentret. FG-D and later add Jon's Hoothoot and LB's Murkrow. FG-G uses the late teams.

## Rework notes for FG01–FG22

The plot of FG01–FG22 stays. The rework is about who speaks, how long scenes run, and a few payoffs that don't land. Line references are to `data/scripts/friends_story.inc`.

**Global passes**

1. **Reassign Nick.** Target about 15% of lines (from 31%). When a Nick line restates what just happened, cut it. When it moves the scene, give it to whoever owns that topic: logistics to X, food and rest to Brian, transport to Tim.
2. **Trim long scenes** to 20–28 pages on the main path: FG07 (45 pages), FG04 (43) and FG03 (42) first, then FG10 (38). Cut the third and fourth beat of any running gag.
3. **Ham's "I'm not a bitch":** keep FG13 ("I'm not letting it go hungry") and FG16 ("Psyduck, stare harder"). Replace the two battle uses (lines 5064 and 5266) with the lines below.
4. **Speaker tag fix:** remove "(to XAVIER)" and "(to LB)" from names; put the address in the line.
5. **Final battles:** replace the shared invitation and the shared `FinalAfter` text with the seven per-character versions in `friends-new-event-scripts.md`.

| Event | Main change |
| --- | --- |
| FG01 | Keep. Strong opener. Cut Nick's "Okay. Keep the cable" exchange to one line. |
| FG02 | Nick has 11 of 26 lines. Give the backpack-negotiation coaching to X ("Give him a minute and a snack. Then talk terms."). Nick keeps only the Mankey de-escalation. |
| FG03 | Cut to about 26 pages. LB's performance gag is the scene. Cut Jon's interruptions from 7 lines to 3 and give LB's Jigglypuff moment the room. |
| FG04 | Cut to about 26 pages. Each of the three partner moments (X/Oddish, Tim/Spearow, Ham/Psyduck) gets one exchange, not two. |
| FG05 | Keep; the clerk is a good straight man. Trim Nick's lines to two. |
| FG06 | Keep the two coaching styles; let Brian, not Nick, call the first loss "a learning game." |
| FG07 | Biggest cut, to about 28 pages. X's "manifesting" budget and the Paras shade moment stay. Cut the emergency-crackers back-and-forth to two lines and drop Nick's "He's the only one with a plan" (X already said it). |
| FG08 | Keep. Tone is right next to Pokémon Tower. |
| FG09 | Keep. Let Tim announce the dock job (his transport thread) instead of Nick. |
| FG10 | Trim the interview to one question per friend who speaks. |
| FG11 | Keep. This seeds the reflection thread that FG-B and FG17 pick up. |
| FG12 | Keep. Add one line that sets up FG-B: X: "Oak said there's a road west. Roads go places. Places have exits." |
| FG13 | Nick and Ham split lines evenly; good. Change Ham's arrival summary to acknowledge FG-B if it was seen ("We walked. Jon yelled at a mountain."). |
| FG14 | Keep. X's best scene. |
| FG15 | Keep Jon's arc; give two of Nick's 8 lines to Brian, who has been the one telling Jon to eat. |
| FG16 | Nick has 9 of 24 lines. Give the move-naming instructions to LB, whose Jigglypuff is the one learning. |
| FG17 | Keep. Add one line from X noting this is the second time the water showed Brian's living room (callback to FG11). |
| FG18 | Keep. Tim's best scene, and FG21 now pays it off. |
| FG19 | Keep; already evenly spread. |
| FG20 | Use the new per-character invitations. Nick's "Pick whoever you feel like" stays. |
| FG21 | Replace Tim's beat (line 4838) with the version below. Add 1–2 friend lines between the crossing groups (lines 2786–2833 have none). |
| FG22 | Delete the unreachable late-introduction branch (~2866–2880). Keep the LB/X *Nothing Was the Same* callback; drop the tag per the global fix. |

**FG21 replacement for Tim's beat** (it pays off FG18 instead of making him the butt of the joke):

> TIM: Hold up. Everybody check your stuff. Bags, chargers, Pokémon.
>
> JON: THERE ARE NO TICKETS, TIM.
>
> TIM: I know. I just like being the one who checks.
>
> XAVIER: He's been the one who checks since Olivine.
>
> TIM: Turns out I'm good at getting people places.
>
> TIM: Even you idiots.
>
> JON: ...WE'RE TAKING TIM TOO?
>
> TIM: I'm the travel agent, Jon. I'm going first.

**Ham battle-line replacements**

- Line 5064 (B07 Ham loses): `HAM: Psyduck says next time.`
- Line 5266 (final Ham beats the player): `HAM: Golduck stared harder.`

## Implementation notes

Keep receipt IDs and placement order separate. New events get new receipt bits, and placement follows the 29-row order in the arc map.

1. **Receipts:** FG-A to FG-G use bits `0x956`–`0x95C`, set only after the scene finishes. `0x95D`–`0x95F` stay required-zero.
2. **Placement:** the state registry describes the 5-bit placement as chapter 0–22, in FG order. Introduce an order table (`sFriendsPlacementOrder[29]`) that maps placement index to event. Existing saves at placement *n* must map to the same story point: convert on adoption, never by rewriting bits, and add host tests for every old value 0–22.
3. **Retiring:** keep the monotonic rule. A new event skipped because the player moved past it stays unseen, and the next scene's late-introduction text must not mention it.
4. **Battles:** none of the new events start a battle. Fix `Special_FriendsStoryCanBattle` so B01–B07 check their defeat flags. After a win, the menu either hides the battle or plays a rematch line with no payout.
5. **Text:** keep every line within the 208px window. Measure with the font width table (`GetStringWidth`), not character count; all-caps Jon lines are the risk. Use two-option `multichoice` menus with real labels, never YES/NO for an A-or-B question.
6. **Staging:** each new event uses at most four friend actors on screen at once, plus their two Pokémon where named. Reuse the existing camera and formation code.
7. **Native checks (each new event):** trigger from a clean approach; decline when blocked; every choice branch; leave mid-scene through no exit; Save → full quit → Continue keeps the receipt; a save from before the update adopts cleanly.
8. **Owner review:** follow the standing `AGENTS.md` format: per event, actual in-game captures beside exact dialogue, labels and test status.
