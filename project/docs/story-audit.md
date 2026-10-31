# Story audit: the custom stories (October 2026)

The owner asked for a full audit of the custom stories, to see where they are lacking, then for work to enhance them,
tie them together and lengthen them. This page is that audit. It describes each arc as the scripts implement it, lists
what is lacking, and proposes work in three groups: **Tie**, **Enhance** and **Elongate**.

It was made from `v2-main` `d968d4b5` (ROM SHA-1 `c0afc7445ea8028bea0a3a0a0ecb9795c1e67328`). The scripts are the
source: `engine/data/scripts/rainbow_story.inc`, `friends_story.inc`, `character_growth.inc`, `rocket_trio_story.inc`,
`starter_recruitment.inc`, their C code (`src/rainbow_story.c`, `friends_*.c`, `character_story.c`,
`character_starter.c`) and the map scripts that call them. The campaign guide and the older design documents were
read too; where they differ from the scripts, the scripts win and the difference is listed below.

How it was checked:

* every story label: is anything calling it (a scan of all built scripts, maps and C code);
* every story flag: where it is set and where it is read;
* every story text: does it fit its box (pae's text measure, `pkmn_asset_editor.textbox`, run over the story files;
  `pae text check` covers only map scripts);
* which story beats have a replay test, and which are played by the story check;
* the Friends' C state machine (`FriendsStory_GetGate`, `FriendsStory_OnMapLoad`), by reading it.

Nothing here was played through by hand. The story check (399 steps) plays only the three opening beats.

## The arcs as they stand

### 1. The opening day: Pikachu, Ho-Oh, the stranger, Giratina

| Beat | Where | Trigger and state | What the player sees |
|---|---|---|---|
| ST01 Pikachu | Oak's lab | New game (`FLAG_ST01_NEW_COHORT`), lab scene 2 | Oak: give the wary Pikachu space. The player waits, Pikachu chooses them (YES/NO, NO waits). Blue takes Eevee. Sets `FLAG_ST01_GIVEN`. Blue's teams are rewritten to Eevee in C (`CharacterStarter_TryCreateBlueParty`). |
| RB01 Ho-Oh | Route 1 | First walk onto Route 1 after the Pokédex (`RB_Route1Transition`, `RB_Route1Frame`); `FLAG_RB_FRESH_COHORT` | A Pidgey struggles in the wind; the player (and Pikachu, if Pikachu is in the party) shelters it. Ho-Oh crosses the sky. "For a moment, even the wind was still." Sets `FLAG_RB_OPENING_SEEN`. |
| MW01 the stranger | Route 1, straight after RB01 | `MW01_Route1Scene`, when entered from Pallet's edge | A man walks down to the player: "You saw it too." The player searches the Pokédex: no entry. He asks if helping was reason enough (YES/NO: two answers). A pink shape (Mew) passes. Sets `FLAG_MW01_SEEN`. |
| FG01 the Friends | Viridian, south road | First entry after the Pokédex (`FG01_ArrivalCheck`, `FG01_Arrival`) | Violet flashes, Giratina tears the sky and drops seven adults from another world onto the road, then leaves. Long argument. They ask the player where they are (a choice that can't be cancelled) and walk north. Sets scene 1 seen (`FLAG_FRIENDS_ARRIVED_IN_VIRIDIAN`). |

These four are the only custom beats that play by themselves, and the only ones the story check plays (steps 2, 18
and 19).

### 2. Nao and the rainbow bird (RB)

Nao, a bell keeper's apprentice from Ecruteak, travels Kanto asking about the bird.

| Beat | Where | Trigger | What happens |
|---|---|---|---|
| RB02 | Oak's lab | Talk to Oak after the Pokédex, `FLAG_RB_OPENING_SEEN` | Oak: no Pokédex entry, so nobody recorded it. He writes the sighting down. Repeats each talk. |
| RB03 | Pewter (20,14) | After the Pokédex, before the Hideout, the Flute and the League | Nao introduces herself and her grandfather's cracked practice bell. If the player saw the bird, she says she crossed half of Kanto asking about it. Ask about the bird (Ho-Oh, "a possibility, not proof") or her home (Ecruteak's two towers). |
| RB04 | Fuji's house | Fuji rescued, Poké Flute, Fuji scene unseen | Nao asks why some stories get miracles; Fuji answers with the Pokémon who need a home today. Once. |
| RB05 | Celadon Hotel | Hideout cleared (after RB04 if the Flute is got) | Nao got her notebook back from a Rocket "collector". Someone added "Microphones..." and crossed out "wait". Once. |
| RB06 | Celadon, the Silph scientist | After Silph is freed | Rocket ordered devices to copy unusual calls. "A sound can attract a POKéMON. It cannot earn its trust." |
| RB07 | Oak's lab | After the Kanto League | Oak: "That bird flew west. ELM may help you understand why." Then the native Johto referral. Repeats each talk until Elm is met. |
| RB08 | Elm's lab | Elm's intro, `FLAG_RB_OPENING_SEEN` | Elm: Oak mentioned the sighting. |
| RB09 | Ecruteak (30,21) | Beasts released | First talk: the truth of the Burned Tower. If Nao was not met in Kanto, she introduces herself first. |
| RB10 | Olivine (30,36) | Amphy healed, truth seen, before the Radio Tower is freed | Nao is at the lighthouse town: care for the Pokémon already here. YES/NO, not stored. |
| RB12 | Radio Tower 1F (Lass) or Ecruteak | Radio Tower freed, Mahogany done | The director recovered Rocket's copy of Nao's recordings. Disconnect it yourself or leave it to him: both stop it. Sets `FLAG_RB_RECORDING_STOPPED`. (RB11, a Lance scene, was folded into this one.) |
| RB13 | Ecruteak | After RB12 | "Shall we ring the bells now?" YES: the neighbours gather, Nao's cracked bell rings, then Ho-Oh flies over (or a rainbow, if Ho-Oh was caught or beaten). Sets `FLAG_RB_WELCOME_SEEN`. |
| RB14 | Oak's lab, then Route 1 | Johto League, welcome seen | Oak reads Nao's letter: "The bells rang. Nothing was asked of the sky." Then a Pidgey on Route 1 shelters a younger bird. |

### 3. The Quiet Stranger: Mewtwo (MW)

A disguised Mewtwo watches how the player treats Pokémon. Each scene is once only and asks one question. No answer is
stored.

| Beat | Where | Trigger | Question |
|---|---|---|---|
| MW01 | Route 1 | After RB01 | Was helping reason enough? |
| MW02 | Route 4 (56,8) | Mt. Moon fossil | Who decides what a restored fossil becomes? A stone floats an inch. |
| MW03 | Lavender (10,16) | Poké Flute | A talk with Fuji: "It is a home, not a cage." Mew passes. |
| MW04 | Celadon (33,27) | Hideout cleared | You opposed Rocket, yet you carry Poké Balls. |
| MW05 | Silph Co. 1F | Master Ball from the president | The disguise wavers: a tail, a strange head. Mew at the window. |
| MW06 | Cinnabar (22,10) | Mansion's Secret Key | The veil falls: Mewtwo. Invite it, or leave it to choose? |
| MW07 | Route 22 | After MW06 | A Champion's power: before or after the League. |
| MW08 | Cerulean Cave | Native access (Sevii, Celio) | Familiar or unfamiliar greeting; Face (the native level 70 battle) or Leave. |
| MW09 | Cerulean Cave 1F mouth | Mewtwo fought | "There is room for more than one path through the world." Mew passes. |

Mew is a silent observer, a pink shape crossing the screen, in MW01, MW03, MW05, MW06 and MW09.

### 4. The Friends from the other side (FG01–FG22, battles B01–B07 and seven finals)

Seven adults (Brian, Xavier "X", Tim, LB, Nick, Jon, Ham) were pulled from a living room by Giratina. Their scenes
follow a C state machine: one stage at a time, set when the player enters the map of a later scene whose gate is open
(`FriendsStory_OnMapLoad`). A scene the player walks past is retired for good; the next one has "late introduction"
lines so nothing refers to a missed scene.

| Scene | Map | Gate | Thread |
|---|---|---|---|
| FG01 | Viridian | Pokédex | Arrival (above). |
| FG02 | Route 2 | Pokédex | Brian and Jon get Rattata and Mankey by not shouting. Battle B01 (Brian). |
| FG03 | Route 4 | Fossil | LB's Jigglypuff sings everyone asleep; Jon's third eyebrow. Battle B02 (Jon). |
| FG04 | Cerulean | Pokédex | Everybody has a partner. |
| FG05 | Vermilion | Pokédex | Tim and the ferry clerk. |
| FG06 | Route 11 | Pokédex | Two coaching styles. Battles B03 (Nick), B04 (LB). |
| FG07 | Celadon | Hideout cleared | X "manifests" a room: two hours of washing up. Battle B05 (X). |
| FG08 | Lavender, then Fuji's house | Poké Flute | Carrying mattresses for Fuji, quietly. |
| FG09 | Fuchsia | Pokédex | Feeding partners; Tim's Krabby. Battle B06 (Tim). |
| FG10 | Saffron | Silph freed and the Master Ball | A job interview that turns out to be Team Rocket. |
| FG11 | Cinnabar | Secret Key | A puddle shows Brian's living room, then a shadow closes it. |
| FG12 | Pallet | Kanto League, Oak's referral | They watched the League. "Next stop's Johto." |
| FG13 | New Bark | Elm met | Ham's Sentret. |
| FG14 | Ruins of Alph | Elm met | X and a researcher: what we saw versus what we guess. |
| FG15 | Azalea | Slowpoke Well | Jon learns to lower his voice. |
| FG16 | Goldenrod | Before or after the takeover | Naming moves. Battle B07 (Ham). |
| FG17 | Ecruteak | Beasts released | The pond shows Brian's home again; nobody leaves a partner behind. |
| FG18 | Olivine port | Amphy healed | Tim helps a stranger for nothing. |
| FG19 | Goldenrod | Radio Tower freed | Calming frightened Pokémon. |
| FG20 | Blackthorn | Badge 8 and Dragon's Den | Seven final opponents, one menu. |
| FG21 | New Bark | Johto League | Giratina opens the way home; Safe travels, one last battle, or stay. |
| FG22 | New Bark | After FG21 and a later visit | They come back to visit. |

### 5. Jessie, James and Meowth (JT)

| Beat | Where | Trigger | What happens |
|---|---|---|---|
| JT01 | Route 4, Mt. Moon's far mouth | Fossil, before the Cascade Badge, no other trio scene | Meowth tangled in their own net; James talks from inside the tunnel. |
| JT02 | Celadon pond garden | Hideout cleared | A fake survey ("would your POKéMON like to stand in this convenient cage?"), then an optional double battle that stays until won. |
| JT03 | Goldenrod | Goldenrod state 1–5 (before the takeover) | "New region. New disguises." Meowth: "And the same kid!" if they met before. |
| JT04 | Whirl Islands descent | Black Tide resolved | James freed a room of caged Pokémon: "I couldn't leave the cages shut." A freed Seel. |

### 6. The Kanto partners (ST02–ST04)

Optional gifts in Yellow's places: Bulbasaur (Cerulean caretaker, lv 10), Charmander (Route 24 traveler, lv 12, after
the bridge), Squirtle (Vermilion, Jenny, lv 15, after the Thunder Badge). Each is a small rescue scene, then the gift.

### 7. Blue (BL01–BL03)

After the Kanto League Blue becomes Oak's field researcher: BL01 at the lab, BL02 watching Pidgey on Route 1, BL03
comparing notes from both regions (and his Eevee became Umbreon in Johto, for the Pikachu start). His rematch lines in
the Champion's room carry the notebook too.

### 8. Silver and Gold (SV01–SV03, Elm's lab)

* **Elm's lab**: after the errand briefing Elm offers Chikorita, Cyndaquil and Totodile (level 5). Gold, a New Bark
  boy, walks in, takes the one the player's is strong against and battles (`TRAINER_JOHTO_GOLD_LAB_*`). "Next time,
  I'll win! See you around!" On the way back from Mr. Pokémon, the police scene: the third ball is gone (the one
  strong against the player's); the player names the thief, Silver. `JOHTO_VAR_STARTER_MON` drives Silver's teams.
* **SV01** Ecruteak, after the Burned Tower: Silver makes his tired partner rest. Two lines.
* **SV02** Goldenrod Center, after the Underground: Silver waits for his partner. "Wait with him?" Two lines.
* **SV03** Dragon's Den, after the Victory Road lesson: "Another round?" His partner jumps. Two lines.

### 9. Black Tide: Shadow Lugia (LG01–LG08)

Rocket makes copies of Articuno, Zapdos and Moltres and uses them, with relays, to turn Lugia into Shadow Lugia. After
the Radio Tower, an Olivine sailor and a Cianwood Pokéfan warn of three huge birds. In the Whirl chamber the replicas
attack (once); each can be beaten or caught, in any order; then the Kimono Girl (or the Keeper, on the later route)
helps the player face Shadow Lugia. Win or catch restores it. JT04 follows.

### 10. Pikachu, the companion

The Pikachu start gives a companion that walks behind the player with 15 moods (bond by steps, rain, night, towers,
Gyms, Centers). Apart from ST01 itself, its only line in a story scene is RB01's shelter.

## Where it is lacking

### Threads set up and never paid off

| Thread | Set up | What's missing |
|---|---|---|
| **Gold's rematch** | Elm's lab: "Next time, I'll win! See you around!" | Gold never appears again. He has no other script, object or trainer. The largest dropped thread in the game. |
| **Rocket's copied calls** | RB05 (notebook: "Microphones..."), RB06 (Silph devices) | Paid off by RB12 in Johto, but nothing links them to the Lake of Rage, where the native story has Rocket's signal force the red Gyarados to evolve: the clearest case of "a sound as a leash" in the game. |
| **The trio's turn** | JT01–JT03 are comedy | JT04 (James freed caged Pokémon) comes with no setup: the trio is never seen inside Rocket's Johto operation. |
| **The trio and Pikachu** | The design (`kanto-johto-rainbow-story.md`): "They pursue Pikachu when the player's history supports it" | No trio line mentions Pikachu. |
| **Giratina's tear over Viridian** | FG01: a giant ghost dragon over the town's south road | Nobody else in Kanto reacts: not Viridian, not Oak, not the stranger who was a few steps away on Route 1 a minute earlier. |
| **The Pokédex with no entry** | MW01: "Whoever built that machine decided what counts as known." | Paid off only by Oak (RB02). Blue, who becomes a researcher and watches Pidgey on Route 1 (BL02), never mentions the bird or the storm Pidgey. |
| **The Kanto starter three** | ST01 hides Oak's three balls; ST02–ST04 bring the three to the player anyway | Oak never notices. The caretaker, the traveler and Jenny never hear back (the design's "Kanto return conversations" hook). |
| **Fuji's two visitors** | RB04 (Nao) and MW03 (the stranger) both end on Fuji's "home, not a cage"; FG08 brings the Friends to his door the same day | Fuji never mentions one to another, and never hears how Nao's story ended (the design hook "Fuji asks how Nao is doing"). |
| **Nao's Kanto friendship** | Three meetings in Kanto; she says she keeps bells in Ecruteak | When the player reaches Ecruteak she goes straight into the Burned Tower story with no greeting. Oak, who recorded the sighting she was chasing, never mentions her. |

### Characters introduced and then dropped

* **Gold**: one scene (above).
* **The researcher at the Ruins** (FG14) and **the traveler at Olivine** (FG18): one-scene foils, fine as they are.
* **Nao between Celadon and Ecruteak**: after RB05 she stays at the Celadon Hotel for the rest of Kanto (Fuchsia,
  Saffron, Cinnabar, Viridian, the League) and has no Johto return beat until the Burned Tower.
* **The stranger after MW07**: if the player never reaches Cerulean Cave (it needs the Sevii errands), the arc stops
  on Route 22 with a question.

### Quiet stretches

Custom beats by region, in story order. A dash means nothing custom happens there.

| Kanto stretch | Custom beats |
|---|---|
| Pallet, Route 1, Viridian | ST01, RB01, MW01, FG01, RB02 |
| Route 2, Viridian Forest, Pewter (badge 1) | FG02, RB03 |
| Route 3, Mt. Moon | — (JT01, MW02, FG03 wait at Mt. Moon's far mouth) |
| Route 4, Cerulean, Route 24–25 (badge 2) | JT01, MW02, FG03, FG04, ST02, ST03 |
| Routes 5–6, Vermilion, S.S. Anne (badge 3) | FG05, ST04 |
| Route 11, Diglett's Cave | FG06 |
| Routes 9–10, Rock Tunnel, Power Plant | — |
| Lavender, Pokémon Tower | — until the Flute: then RB04, MW03, FG08 |
| Route 8, Celadon, Rocket Hideout (badge 4) | FG07, RB05, MW04, JT02 |
| Routes 12–18, Safari Zone, Fuchsia (badge 5) | FG09 only |
| Saffron, Silph Co. (badge 6) | FG10, MW05, RB06 (in Celadon) |
| Routes 19–21, Seafoam Islands | — |
| Cinnabar (badge 7) | MW06, FG11 |
| Viridian Gym (badge 8), Route 22–23, Victory Road | MW07 only |
| Indigo Plateau, Elite Four | — (Blue's changed rematch lines only) |
| After the League: Pallet, Route 1 | FG12, BL01, BL02, RB07 |
| **Sevii Islands 1–7** (Bill's errands, the Rocket Warehouse, Celio's machine) | — |
| Cerulean Cave | MW08, MW09 |

| Johto stretch | Custom beats |
|---|---|
| Indigo's west road, Route 27 coast | — (FG-B, a draft) |
| New Bark | RB08, Gold, FG13 (later FG21, FG22) |
| Routes 29–31, Cherrygrove, Mr. Pokémon | — |
| **Violet, Sprout Tower (badge 1)** | — (FG-C, a draft) |
| Route 32, Union Cave | — |
| Ruins of Alph | FG14 |
| Azalea, Slowpoke Well (badge 2), Ilex Forest | FG15 |
| Goldenrod (badge 3) | FG16, JT03, SV02 |
| Routes 35–37, National Park | — |
| Ecruteak, Burned Tower (badge 4) | RB09, SV01, FG17 |
| Olivine, lighthouse | RB10, FG18 |
| **Cianwood (badge 5)** | only LG01's warning, after the Radio Tower (FG-D, a draft) |
| **Mahogany, Lake of Rage, Rocket hideout (badge 7)** | — (FG-E, a draft) |
| Radio Tower takeover | RB12 and FG19 after it |
| **Ice Path, Blackthorn (badge 8)** | FG20 after Clair, SV03 in the Den (FG-F, a draft) |
| Whirl Islands | LG02–LG08, JT04 |
| Johto Victory Road, Johto League | — |
| After the Johto League | FG21, FG22, RB14 |
| Mt. Silver, Johto's postgame | — |

The longest silences: Kanto's Routes 12–21 and the whole Sevii chapter; Johto's start (New Bark to the Ruins: four
routes, a badge and a cave), and the badge 5–8 stretch (Cianwood, Mahogany, the Ice Path). In both regions the
League itself has no custom moment. The drafts FG-A–FG-G were written to fill the Friends' share of these gaps; no
other arc reaches them.

### Contradictions

Between the scripts and the docs:

* The campaign guide's header still says "Updated October 20, 2026, current local preview 37C", and its source links
  point at the old local worktree with line numbers that have moved.
* The guide lists MW01 as "Viridian stranger" in chapter 02; the scene moved to Route 1 (chapter 01) on 2026-10-25.
* The guide's FG01 entry says both answers "remove the group immediately at beat 90; no animated walk"; they now walk
  north into town first (`FG01_Movement_HeadNorth`).

Between scripts:

* Nao's Johto introduction for a player who never met her in Kanto (`RB_Text_JohtoIntro`): "I keep bells here. I have
  been collecting KANTOs stories." The apostrophe is missing, and it reads as if the player knew she had been away.
* JT02's prompt reads "Ask who sent them? / NO: Decline the survey." The YES answer is not named.
* The Friends' order is fragile. After the Poké Flute, FRLG lets a player free Silph Co. (FG10's gate) before going
  to Fuchsia. Walking out into Saffron then moves the Friends to stage 10, which retires FG09 (Fuchsia, and Tim's
  battle B06) for good, and FG08 too if they weren't spoken to in Lavender. This works as designed ("advancing
  retires earlier placements"), but scenes are lost on a common order. (The story check goes to Fuchsia first.)

### Flags and scripts

* No story label is unreachable except fall-through labels (`FG01_Repeat`, `FG01_Menu`, `FG01_Choice0`,
  `FG21_Repeat`). The October 19 handoff notes that FG22's late-introduction branch cannot run (the group must have
  been met to reach FG22).
* Every story flag that is set is read, but almost only to stop its own scene repeating or to move a character on.
  A later scene's *words* depend on an earlier scene in just these places: `FLAG_RB_OPENING_SEEN` (Oak, Elm, Nao),
  `FLAG_RB_NAO_INTRODUCED` (Nao's introductions), `FLAG_MW06_SEEN` (MW08's greeting), `FLAG_ST01_GIVEN` (the
  Pidgey shelter, Blue's Umbreon) and `FLAG_JT01/02_SEEN` (JT03's "the same kid"). No line depends on
  `FLAG_ST02/03/04_GIVEN`, `FLAG_RB_FUJI_SCENE_SEEN`, `FLAG_RB_NOTEBOOK_SCENE_SEEN`, `FLAG_MW01`–`05_SEEN`,
  `FLAG_SV0x_SEEN`, `FLAG_JT04_SEEN`, `FLAG_LG_FINAL_RESOLVED` (outside Black Tide and JT04) or the Friends' scene
  receipts (outside their own scenes). So the story rarely remembers.
* No YES/NO answer is stored (MW01, MW02, MW04, MW06, RB03, RB10, RB12, BL02, SV02). Later scenes can't reflect a
  choice. Storing answers needs save bits.
* The custom-story flag block `0x900`–`0x95F` is full. `0x91E`–`0x91F` and `0x956`–`0x95F` must stay zero (the
  adoption checks fail otherwise); the drafts plan to use `0x956`–`0x95C`. Free flags for new beats:
  * Johto: raw HnS flags `0x91B`–`0x95F` (`JOHTO_FLAG` ids `0x291B`–`0x295F`, 69 flags). HnS's own flags end at
    `0x91A`, Johto's daily clear stops at `0x291A`, no `JOHTO_FLAG_*` is defined there and nothing reads them. They
    are inside the regional save's event bits (index ≤ 1506 of 1539), so no layout change.
  * Kanto: FireRed's "unused?" blocks, e.g. `FLAG_0x0AF`–`FLAG_0x0B9`, `FLAG_0x1FF`–`FLAG_0x209`,
    `FLAG_0x4BD`–`FLAG_0x4C7`, with no references in scripts, maps or C. Each needs checking again when used.

### Reactions missing where the story expects them

* **Pikachu** reacts only to the storm Pidgey. It says nothing when the stranger (Mewtwo) walks up to the player, when
  Giratina tears the sky, when Mew passes, when Mewtwo drops the veil, or at Ho-Oh's welcome. The design treats
  Pikachu as the first partner, and a disguised Mewtwo is exactly what a Pikachu would bristle at.
* **The Friends** never react to the other arcs, though they share towns with them: Lavender with Fuji, Nao and the
  stranger on the same day (FG08, RB04, MW03); Ecruteak with Nao (FG17, RB09–RB13); Goldenrod with the trio (FG16,
  JT03); Saffron's Rocket interview (FG10) with Jessie and James's survey two towns away. (Changing Friends scenes
  overlaps the October 19 rework; see the plan.)
* **Rivals**: Blue never mentions the bird or the Pidgey he studies on the same route. Silver's three scenes never
  refer to each other. Gold sees the Kanto Champion and never hears of Silver's theft from the lab next door.
* **Oak** never notices the player brought his old three starters home.

### Arcs that end abruptly

* **Gold** after one battle.
* **Silver's** growth ends on two lines in Dragon's Den ("We'll be ready next time"), and is not tied to his native
  final battles.
* **The stranger** ends on a battle choice in Cerulean Cave and a line at the cave mouth. Mew never resolves; the
  design intends Mew as an observer, so this may be on purpose.
* **The trio** ends in the Whirl Islands, with no Kanto postgame return (Sevii's Rocket Warehouse would fit).

### Kanto and Johto echoes that aren't there

* Two made things: Mewtwo (made by people, in Kanto) and Rocket's replica birds (made by Rocket, in Johto). Mewtwo's
  cave scene could know about the replicas; the two never meet in the text.
* Two days in the sky: the opening (Ho-Oh, the stranger, Giratina) and Johto's ends (Ho-Oh's welcome, the Friends'
  departure through Giratina's door). Neither ending recalls the opening day.
* Two cracked things kept anyway: Nao's bell ("Grandpa heard the crack. He kept it anyway") and Brian's couch arm that
  "isn't broken". Small, but the same idea; fine to leave unspoken.
* Two Pidgey: the storm Pidgey (RB01), Blue's Pidgey notebook (BL02) and the epilogue Pidgey (RB14) are one image in
  three places; only RB14 closes it, and BL02 doesn't know about RB01.
* Two first partners: Oak's lesson with Pikachu ("a partnership begins by paying attention") has no echo in Elm's
  starter choice, which is a plain pick.

### Dialogue that is thin or reads badly

All story text fits its box (0 problems in the story files; `pae text check` reports one inherited issue, in
Blackthorn Gym's guide). The weaker places:

* Silver's three scenes are two lines each. (The design gives these exact lines on purpose; see the plan.)
* The seven final-battle invitations are one sentence repeated with seven names ("Ready for a match? We can wait if
  you would rather rest."). The October 19 handoff has per-friend versions.
* Nick has about a third of the Friends' lines (the handoff's count: 31%); the handoff plans to spread them.
* `RB_Text_JohtoIntro` and JT02's prompt (above).
* MW07 is one line either way.

### Tests

About a dozen of some 80 custom beats have a replay test on this branch: RB01 with MW01, FG01 (two), MW03, MW04,
JT02 (the survey, not the battle), FG09, FG10, ST01's battle, ST03's "cross the bridge first" line, ST04's first
line, and Gold's three lab battles. The rest were checked natively in the old 30- and 36-series builds (the campaign
guide's "historical native scope"), not on this branch. The story check plays the opening day and walks past every
other beat.

## The plan

Each proposal is one branch and one pull request. Sizes: **XS** a line or two, **S** a short scene or a few callback
lines, **M** a new scene with an object or a battle, **L** several scenes or C changes. "Owner" means it needs the
owner's decision first (a draft, the Kanto/Johto separation, the save layout, or a big change to the owner's own
story); those are not implemented.

### Tie

| # | Proposal | Where | State | Size | Risk | Owner? |
|---|---|---|---|---|---|---|
| T1 | **Nao's road home.** Oak, after the Kanto League, passes on that Nao came to ask about the sighting and has gone home to Ecruteak. In Ecruteak, Nao greets a player she met in Kanto before the Burned Tower story. Her cold Johto introduction is rewritten (and its typo fixed). After the welcome, Fuji in Lavender has heard from her (the design's "Fuji asks how Nao is doing"). | `RB_OakReferral`, `RB_NaoEcruteak`, Fuji's house | Reads `FLAG_RB_NAO_INTRODUCED`, `FLAG_RB_ECRUTEAK_TRUTH_SEEN`, `FLAG_RB_FUJI_SCENE_SEEN`, `FLAG_RB_WELCOME_SEEN`; no new flags | S | Low: callbacks only, off the story check's path | No (callbacks across the halves; no shared progress) |
| T2 | **The stranger notices the other visitors.** MW04 (Celadon) gains a line about the seven who fell over Viridian, if the player saw them land: Mewtwo knows what it is to arrive somewhere you don't belong. MW08 (Cerulean Cave), if Black Tide is resolved: Rocket made birds the way people made Mewtwo, and the player freed them. | `MW04_Talk`, `MW08_Intro` | Reads `FLAG_FRIENDS_ARRIVED_IN_VIRIDIAN`, `FLAG_LG_FINAL_RESOLVED` | S | Low | No |
| T3 | **Blue remembers the storm Pidgey.** BL02 gains a line if the player saw the opening: Oak wrote down that the player sheltered one; Blue thinks it is one of the birds he watches. | `CG_BlueRoute1` | Reads `FLAG_RB_OPENING_SEEN` | XS | Low | No |
| T4 | **Oak's old three come home.** Oak notices the player has Bulbasaur, Charmander or Squirtle from their rescues ("the three I kept on this table found you anyway"), after the League. | `RB_OakStory` | Reads `FLAG_ST02/03/04_GIVEN` | XS | Low | No |
| T5 | **Silver remembers.** SV03 gains a line if SV02 was seen (Silver remembers who stopped by at the Center), without assuming the answer. | `CG_SilverDen` | Reads `FLAG_SV02_SEEN` | XS | Low | No |
| T6 | **The trio eyes Pikachu**, as the design intended: JT01 and JT03 gain a Meowth line about the player's Pikachu, for the Pikachu start. | `JT01_Net`, `JT03_Disguises` | Reads `FLAG_ST01_GIVEN`, `checkspecies` | XS | Low | No |
| T7 | **Nao has heard of the seven.** Nao's repeat line in Ecruteak mentions travelers staring into the pond, if FG17 was seen. | `RB_NaoEcruteak` | `Special_FriendsStoryGetSeen` (scene 17) | XS | Low | No |
| T8 | **Fuji, the Friends and the stranger.** Fuji's lines in FG08 refer to Nao or the stranger. | FG08 | — | S | Low | **Owner**: changes a Friends scene (the October 19 rework covers FG08) |
| T9 | **The Friends meet the other arcs** (Nao at the pond, the trio in Goldenrod, Rocket at Saffron). | FG10, FG16, FG17 | — | M | Medium | **Owner**: Friends scenes are in the rework |

### Enhance

| # | Proposal | Where | State | Size | Risk | Owner? |
|---|---|---|---|---|---|---|
| E1 | **Pikachu in the opening day.** Pikachu's fur stands on end while the stranger talks (a hint of what he is), and it hides behind the player when Giratina tears the sky. Only for the Pikachu start. | `MW01_Route1Scene`, `FG01_Arrival` | Reads `FLAG_ST01_GIVEN`; no new flags | S | Medium: both are on the story check's path (steps 18–19), so the check must run again from step 18 (about 2.5 hours) | No |
| E2 | **Pikachu at the big moments** (off the check's path): MW05's wavering veil, MW06's reveal, Black Tide's attack, RB13's welcome. | those scenes | as E1 | S | Low | No |
| E3 | **Text polish**: JT02's prompt names both answers; MW07 gets a second line each way. | `JT02_Text_Question`, `MW07_Text_*` | — | XS | Low | No |
| E4 | **Viridian notices the tear**: one townsperson line after FG01. | Viridian | Reads scene 1 seen | XS | Low (a rebuilt map: a script change only, or a new person through `build.sh`) | No |
| E5 | **Fuller Silver scenes** (SV01–SV03 longer, tied to his native battles). | `character_growth.inc` | — | S | Low | **Owner**: the design gives these exact two-line scenes |
| E6 | **Per-friend final invitations and the dialogue rework** (Nick's share, the speaker tags, FG21's Tim beat). | `friends_story.inc` | — | M | Medium | **Owner**: the October 19 rework (draft) |
| E7 | **Remember the player's answers** (MW, RB, SV choices) so later scenes can answer them. | many | needs new flags | M | Medium | **Owner**: uses save bits; choose which answers matter |
| E8 | **Stop the Friends' order from losing scenes** (Silph before the Tower retires FG08 and FG09), e.g. let a skipped Kanto scene play at the next camp. | `friends_story.c` | Friends stage bits | M | Medium | **Owner**: changes the placement rule the drafts also rework |

### Elongate

| # | Proposal | Where | State | Size | Risk | Owner? |
|---|---|---|---|---|---|---|
| L1 | **Gold comes back, in Violet.** After the Zephyr Badge Gold waits outside Violet's Gym: Falkner beat him, twice. He asks how the Kanto Champion won and asks for a battle (optional). Whatever the result he leaves for Sprout Tower to train. He has heard about the theft at Elm's lab. Fills Johto's silent start and pays off "Next time, I'll win!". | Violet City (a Johto map) | One new Johto flag (raw `0x91B`, `JOHTO_FLAG` `0x291B`); three new trainers (one per starter Gold can have) | M | Low–medium: a new person and battle on a Johto map | No (an in-scope extension of Gold; the owner reviews it in the pull request) |
| L2 | **Gold's later beats**: a mid-Johto meeting (Ecruteak or Olivine, where he has heard Silver is near) and a last battle after the Johto League in New Bark. | Johto | Two more Johto flags, six trainers | M each | Low | No, after L1 is reviewed |
| L3 | **Nao at the Lake of Rage.** After the Mahogany hideout, Nao at the lake recognizes the signal that forced the red Gyarados to evolve: the same copied-call devices as her stolen recordings. Ties RB05, RB06 and RB12 to the native story. | Lake of Rage | One Johto flag | M | Low | No |
| L4 | **The trio's missing middle.** During the Radio Tower takeover (Goldenrod state 6–10) Jessie, James and Meowth are found in Rocket uniforms in the Underground warehouse, uneasy among the caged Pokémon, which sets up JT04. | Goldenrod Underground | One Johto flag | M | Medium: inside a native Rocket area | No |
| L5 | **The trio in Sevii**: at Five Island's Rocket Warehouse, Kanto's postgame. | Five Island | One Kanto flag | M | Low | No |
| L6 | **Sevii, stories carried by sea** (the design's hook): travelers on the islands argue about a rainbow seen offshore. | Sevii | none (repeatable) | S | Low | No |
| L7 | **The Friends' gaps**: FG-A (One Island), FG-B (the west road), FG-C (Violet), FG-D (Cianwood), FG-E (Lake of Rage), FG-F (Ice Path), FG-G (Ecruteak, postgame). | as drafted | `0x956`–`0x95C`, the 29-placement table | L | Medium | **Owner**: drafts |
| L8 | **The Leagues**: a short custom moment at each League (the Friends in the stands for Kanto's is FG12's joke; Nao's bell or Gold for Johto's). | Indigo, Johto League | per beat | M | Medium | **Owner**: touches the League sequence |

### Order

Highest value first, among the ones that don't need the owner: **T1** (the only character who crosses both halves
loses her thread at the crossing), **L1** (the largest dropped thread, in Johto's longest silence), **T2** with **T3**,
**T4**, **T5**, **T6** and **T7** (cheap callbacks that make the story remember), **E1** and **E2** (Pikachu), then
**L3**, **L2**, **L4**, **L5**, **L6** and **E3**, **E4**.

### For the owner

* The Friends' drafts (FG-A–FG-G, the 29 placements, the October 19 rework) fill most of the quiet stretches above.
  They are ready to schedule; nothing here implements them.
* E8: should a skipped Friends scene still play later (Silph before the Tower loses two scenes today)?
* E7: should the game remember the player's answers? It needs a few save bits.
* E5: should Silver's scenes grow beyond the design's two lines?
* L8: should the Leagues get a custom moment?
* Johto's difficulty (the October audit's first finding) affects every new Johto battle: Gold's teams in L1 and L2
  follow Johto's current levels (Falkner lv 8–11), not the player's Kanto team.
