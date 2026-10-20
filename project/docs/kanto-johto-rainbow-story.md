# The Road Beneath the Rainbow

Original additive story treatment for the combined FireRed Kanto → HnS Johto campaign. Written October 14, 2026; expanded with the owner's Mewtwo/Mew direction, Shadow Lugia chapter and seven-friend portal story. **Narrative proposal, not implemented gameplay.** Event conditions, persistence rules and implementation checks are in the [engineering handoff](kanto-johto-rainbow-event-handoff.md).

**October 15 starter direction:** new games begin with Pikachu, then offer Bulbasaur, Charmander and Squirtle through Kanto story encounters. This replaces the initial three-way starter choice in the design. The scenes below are a proposed adaptation of that direction; this document does not establish implementation status in another task.

## The story at a glance

On the first day of your journey, you stop to help a frightened Pidgey. As the clouds part, an enormous golden bird crosses the sky toward the western mountains. Nobody in Pallet can tell you exactly what you saw.

Across Kanto, you meet Nao, a young bell keeper from Ecruteak who believes that finding the right sound will bring that bird home. Your sighting gives her hope. Team Rocket sees something else: evidence that a Legendary Pokémon can be found, studied and controlled.

After becoming Kanto Champion, Oak sends you to Professor Elm. The journey west brings you into the landscape behind the stories: the Burned Tower, the three legendary beasts, and a city still waiting for Ho-Oh. As Rocket's schemes spread through Johto, Nao discovers how easily a wish to bring something back can become a refusal to let it choose.

The ending returns to the opening's small act of kindness. Ecruteak prepares a welcome without demanding an answer. Ho-Oh appears above the city. Whether you eventually catch it belongs to the existing game; the story resolves when Nao learns that a return does not have to mean possession.

The tone is adventurous, warm and occasionally mysterious. Gym victories remain exciting. Pokémon have personalities and agency. Loss is handled gently. The player is an observant trainer whose ordinary actions matter, rather than the subject of a new prophecy.

A second story runs through Kanto: **The Quiet Stranger**. Mewtwo, concealed as a traveler, watches how the player treats Pokémon. Hidden farther away, Mew watches both of them. Ho-Oh's story asks what makes a place worth returning to; Mewtwo's asks what makes a person worth trusting. They share a theme without turning every legendary into part of one conspiracy. The full Kanto arc follows Chapter 4 below.

The third arc is **[Black Tide](johto-shadow-lugia-story.md)**: Team Rocket creates corrupted replicas of Articuno, Zapdos and Moltres to attack Lugia and turn it into Shadow Lugia. Defeat or capture all three replicas to break Rocket's control links, then face Shadow Lugia. The original Kanto/Sevii birds remain intact. This new chapter deliberately adds a required condition to the Whirl Islands Lugia encounter; it supersedes the earlier optional-only Lugia outline.

## The people who carry it

**The player:** The same trainer throughout both regions, beginning new games with Pikachu and building their own team along the way. Supported existing saves retain their original starter and history. They begin with a question and eventually become someone other people trust with an answer.

**Nao — new original character:** An apprentice bell keeper and collector of local stories from Ecruteak. Practical, curious and impatient with vague legends. Her grandfather taught her to repair ordinary bells and listen for their imperfections. She privately fears that maintaining an empty tower is a way of waiting forever. She travels with his small, cracked practice bell; it has sentimental value, not supernatural power. Nao remains its owner throughout the story.

**Oak and Elm:** Oak takes the sighting seriously without pretending he can explain it. Elm connects observation with the responsibilities of caring for living Pokémon. Their existing research missions remain the backbone of the regional handoff.

**Mr. Fuji, Morty and Eusine:** Fuji gives the story its gentleness; Morty supplies Ecruteak's inherited history; Eusine offers a more restless perspective through his existing pursuit of Suicune. Their original roles and encounters remain intact.

**Team Rocket:** Existing Kanto and Johto antagonists. A small research effort involving copied bell recordings connects their regional operations. Black Tide adds a surviving replica-and-conditioning operation around the Whirl Islands. These are additional schemes; Giovanni, the Lake of Rage and the Radio Tower takeover retain their original roles.

**The Quiet Stranger — Mewtwo:** A reserved traveler in a plain coat. A psychic veil makes people overlook what is unusual about him; this disguise is our original adaptation, not a new battle transformation. He studies the player because their actions conflict with his expectations of humans. He neither arranges their hardships nor secretly wins their battles.

**The second observer — Mew:** Curious, elusive and usually invisible. A pink tail slipping behind a roofline or a ripple where nothing stands hints that Mew is nearby. Mew wants to see whether Mewtwo can move beyond suspicion. It does not assign the player a secret test or speak on Mewtwo's behalf.

**Jessie, James and Meowth:** A recurring Rocket trio with grand plans, poor coordination and affection for their own Pokémon. Their Kanto and Johto appearances add comedy and occasional sympathy alongside the existing Rocket operations.

**Blue — the Kanto rival:** Competitive during the original Kanto campaign. After losing the first League championship, he is content to develop as a scientist and follow Oak's footsteps. Research is a happy, deliberate direction. He can still enjoy a battle and congratulate the player. His saved rival name remains authoritative in the game.

**Silver — the Johto rival:** His existing journey toward trusting Pokémon gains small scenes between battles. Changed behavior comes before an open admission, and stronger signs of growth wait for the corresponding native story milestones.

## Kanto companion arc — A team that chooses you

The owner wants a Yellow-inspired beginning within the combined Kanto campaign: **Pikachu is the default starter; Bulbasaur, Charmander and Squirtle are met and can join later.** Keep the Red/Blue/FireRed journey through the Gyms, Team Rocket and League around this change. These are relationships encountered on the road, not four Pokémon handed over in Oak's lab.

### Pikachu — The first partner

Oak introduces the player to a wary Pikachu at the lab. Pikachu approaches only after the player gives it some space. Oak's lesson is simple: a partnership begins by paying attention. The starter grant, nickname opportunity and opening rival battle still complete before the first proper journey onto Route 1.

During the existing Pidgey rescue in Chapter 1, Pikachu settles beside the frightened bird while the player shields it from the wind. It is the first thing they accomplish together. Both look up as Ho-Oh passes overhead. This is short scene staging, not a requirement for a permanent follower system; the existing starter-neutral staging remains available for supported older saves.

**Rival recommendation, not yet settled:** give Blue Eevee to echo Yellow. That would require adapting his whole Kanto team progression coherently, rather than changing only the lab battle. His existing role and confrontations remain. Johto's Silver stays independent.

### Bulbasaur — The little guardian

*Cerulean City, a caretaker's garden; optional before or after Misty.*

Bulbasaur protects several recovering Pokémon and initially blocks the player from approaching. Help its caretaker settle a frightened resident and repair a knocked-over shelter. Bulbasaur watches the player work, then steps aside. When the player leaves, it follows to the gate. The caretaker offers it a chance to travel, and the player can accept or return later.

> **Caretaker:** It usually stands between strangers and the others. Today it stood beside you.

Use this visible act of care rather than an unexplained friendship threshold. Pikachu need not be in the current party, and the scene does not delay Misty's Gym.

### Charmander — Someone came back

*Route 24, beyond Nugget Bridge; optional after the original bridge sequence.*

A Charmander keeps returning to a roadside meeting place after its trainer has abandoned it. When rain begins, the player helps a nearby traveler get it under shelter. The traveler explains that they have already waited with it for days. The player stays through the short scene; no real-time waiting or consumable medicine is required. Once safe, Charmander chooses to leave with the player.

> **Traveler:** You can leave whenever you're ready, little one. You don't have to keep waiting here.

Accepting adds Charmander once. Declining leaves it safely with the traveler for a later visit. This gives the observer storyline another example of care without making Mewtwo responsible for the abandonment or requiring a new cameo.

### Squirtle — Trouble at the harbor

*Vermilion City; introduction on arrival, recruitment after the Thunder Badge.*

A small group of Squirtle has been stealing dockworkers' supplies. Their leader treats the player's first approach as another game. In a short later incident, smoke rises from a storage shed and the player helps clear the way while the Squirtle put out the fire. Officer Jenny sees that their energy needs a purpose. The leader volunteers to travel with the player; its friends remain to help at the harbor.

> **Jenny:** You got them working together. That was the part my whistle couldn't manage.

The offer remains available after a decline or a full-party interruption. It never blocks the S.S. Anne, Cut, Lt. Surge or travel onward.

All three recruitment stories are optional and can be completed later. They are not prerequisites for the League, Mewtwo or Johto. The player may box, evolve and choose among their Pokémon normally; no forced party slot or Pikachu evolution restriction is part of this request. Later dialogue recognizes only events the player actually completed.

## Chapter 1 — A shape in the clouds

*First journey onto Route 1, after the starter and opening rival sequence.*

A brief shower has passed over the route. Near the path, a young Pidgey keeps trying to fly into a gust and tumbling back. The player crouches beside it, shielding it until the wind eases. No battle begins. No item is required.

The Pidgey settles. Then it looks up.

A broad shadow moves across the grass. Above the treetops, a bird glows gold and red, its tail trailing color across the thinning clouds. It gives a single distant cry and flies toward the western horizon.

The Pidgey takes off after it for a few wingbeats, then circles back to its tree.

One short text box appears:

> For a moment, even the wind was still.

There is no nameplate, prophecy, battle or collectible feather. The player continues toward Viridian.

When the player later returns with Oak's parcel, Oak hears the story after his original business is finished.

> **Oak:** A bird with feathers like a rainbow? I can't identify it from a description alone.
>
> **Oak:** I'll write down what you saw. Keep looking up, {PLAYER}. There is still plenty we don't know.

## Chapter 2 — The bell that will not ring

*An optional conversation outside Pewter Museum.*

Nao is comparing a weathered illustration of a long-tailed bird with notes from travelers. The player's description interrupts a string of disappointing interviews.

> **Nao:** Gold wings? A long tail? And it was flying west?
>
> **Nao:** I've crossed half of Kanto asking that question. You saw it on your first day?

She introduces herself and shows the player her practice bell. It produces a dull clink.

> **Nao:** My grandfather can hear a crack before he can see it. I thought I could, too.
>
> **Nao:** Back home, people keep bells for a Pokémon that almost nobody has seen. I want to know what they're waiting for.

She has been collecting ordinary bell sounds and accounts of unusual Pokémon behavior. She thinks an old welcoming melody may be incomplete. The player can ask about the bird or her home; both answers are available without a permanent choice.

She calls the bird **Ho-Oh** as a possibility, not a confirmed identification. Her next stop is Lavender, where people remember Pokémon in a different way.

## Chapter 3 — What can be brought back

*Mr. Fuji's house, after his original rescue from Pokémon Tower.*

Nao is helping Fuji settle the Pokémon in his care. She has heard a Johto legend about lives restored by Ho-Oh and asks the question she has been avoiding: if such a Pokémon exists, why does anyone have to lose anything?

Fuji does not promise a miracle. The original Pokémon Tower story remains resolved as written.

> **Fuji:** I don't know why some stories are given miracles.
>
> **Fuji:** I do know that these Pokémon needed a home this morning. They will need one tomorrow, too.

A restless Pokémon settles beside him. Nao puts her notebook away to help.

> **Nao:** I came here to ask about a legend. You haven't asked me about it once.
>
> **Fuji:** You looked as though you could use something useful to do.

This is the first crack in her theory: perhaps caring for what is here matters more than recovering what is gone. The scene does not revive Marowak, rewrite Fuji's history, or make Ho-Oh responsible for every loss.

## Chapter 4 — Rocket's echo

*Celadon, after the original Rocket Hideout is cleared; a small later callback after Silph Co.*

Nao has been tricked by a buyer who claimed to represent a historical collection. Her notebook of bell recordings and sightings ended up with Team Rocket. After the player clears the hideout, she recovers it among the abandoned papers. Nothing is added to the player's Bag.

There are new annotations in a different hand. Someone has compared her observations with equipment orders: microphones, amplifiers, and a request to test whether Pokémon approach a sound even when they cannot see its source.

> **Nao:** Those are my notes. That isn't my handwriting.
>
> **Nao:** I wrote, "Wait quietly and see what comes." They crossed out "wait."

She takes the notebook homeward. After Silph's original liberation, a brief optional conversation with an existing scientist confirms that Rocket also sought equipment capable of reproducing unusual calls. This remains a side lead. Giovanni still loses for the original reasons, and every original reward remains where it belongs.

For the rest of Kanto, the mystery recedes. The player earns badges, faces their rival and reaches the League. Ho-Oh does not appear after every victory.

## Kanto parallel arc — The Quiet Stranger

These scenes weave between the chapters above and the original Kanto campaign. Most are optional conversations lasting a few text boxes. Mew's background appearances are brief visual rewards for attentive players; there is no checklist or requirement to spot them.

### K1 — Someone at the edge of town

*Viridian, early in the journey, after the player has visited Oak with the parcel.*

A traveler in a plain gray coat stands beyond the busiest part of town. He has no visible Pokémon and seems uninterested in the road ahead. If approached, he asks about the Pidgey on Route 1.

> **Stranger:** You stopped for that bird. You did not catch it.
>
> **Stranger:** What did you gain?

The player can answer, "It needed help" or "I didn't think about it."

> **Stranger:** I see.

He does not sound convinced. When the player leaves, the camera holds for a heartbeat. A pink tail curls out from behind a distant hedge, then disappears. The stranger turns toward the movement a fraction too late.

If the opening was not witnessed, his question is simply: “Why do you want to travel with Pokémon?” The game never invents a memory for the player.

### K2 — What remains in the stone

*A quiet, optional conversation on the Route 4 side of Mt. Moon.*

The traveler is examining the cliffs. Following the original fossil sequence, he asks whether something brought into the world by human hands would owe its life to those hands.

> **Stranger:** If people restore a Pokémon from a fossil, who decides what it becomes?
>
> **Stranger:** The people? Or the Pokémon?

The player can answer, "The Pokémon" or "They have to learn together." He does not grade either response.

> **Stranger:** Together. Humans use that word often.

A small rock beside him rises for an instant before settling. There is no visible Pokémon using a move. Farther up the cliff, something pink ducks out of sight.

The scene raises a question that Cinnabar will later answer. It does not change the fossil reward or require its revival.

### K3 — A house with an open door

*Lavender, outside Fuji's house after the original rescue and reward.*

The traveler watches a rescued Pokémon move freely through the doorway.

> **Stranger:** There is nothing keeping them here.
>
> **Fuji:** No. Some leave when they're ready.
>
> **Stranger:** And you allow that?
>
> **Fuji:** It's their home. It isn't a cage.

For the first time, the traveler has no reply. This is a separate short interaction from Nao's visit, not a second automatic speech after the Tower.

Across the lane, a puddle ripples beneath an invisible weight. Mew has been watching the stranger rather than Fuji.

### K4 — The language of ownership

*Celadon, after the original Rocket Hideout is cleared.*

The traveler has noticed the player emerging from Rocket's operation. His attention is on the people the player confronted, not the stolen notebook in Nao's story.

> **Stranger:** They called Pokémon property. You opposed them.
>
> **Stranger:** Yet you carry Poké Balls, too.

The player can answer, "I try to earn their trust" or "You can judge how I use them."

> **Stranger:** Then perhaps I will.

He leaves on foot. He is not a new Rocket boss, an informant handing out keys, or the hidden cause of Giovanni's plans. His uncertainty gives the player's existing actions an additional witness.

### K5 — The moment the disguise slips

*Silph Co., after Giovanni is defeated and the original rescue/rewards are complete.*

The traveler is near an open window in a safe hallway. The player's attention is drawn to a faint sound behind him. For a single beat, the veil around his outline wavers: a different head shape, a long tail, then the ordinary coat again.

> **Stranger:** They offered power to anyone willing to take it.
>
> **Stranger:** You kept stopping to help people.

He looks toward the window. A small pink shape is reflected in the glass, well above the street. Mew disappears when he turns.

> **Stranger:** ...We are not alone.

He departs without a fight. Mewtwo is beginning to suspect that he is also being observed. The scene does not add a rescue by Mewtwo, change the Master Ball grant, or assume the player accepted Lapras.

### K6 — The name in the journals

*Cinnabar, after the player's original Pokémon Mansion exploration.*

The existing journals retain their account of Mew and Mewtwo. Outside the Mansion, the traveler waits away from the entrance. When the player speaks to him, he looks back at the building.

> **Stranger:** Those pages tell you what they hoped to create.
>
> **Stranger:** They cannot tell you who I will become.

The veil falls. The figure who has appeared throughout Kanto is Mewtwo.

There is no battle transition. The player has a moment to recognize the silhouette from Silph, the floating stone, and the questions that never sounded quite like a trainer's.

> **Mewtwo:** I watched you because I expected the same answer every time.
>
> **Mewtwo:** A stronger Pokémon. Another possession. Another reason to command.
>
> **Mewtwo:** You have made that answer difficult.

The player can answer, "Come with me" or "You can choose your own path."

For “Come with me”:

> **Mewtwo:** An invitation. I am not ready to accept it.

For “You can choose your own path”:

> **Mewtwo:** Yes. That is what I intend to do.

Both lead to:

> **Mewtwo:** You do not speak for every human. I no longer believe every human speaks for you.

Mewtwo leaves to find somewhere quiet. In the distance, Mew becomes briefly visible above the ruined roof. It looks from the player to the place Mewtwo disappeared, then follows. There is no announcement, reward, Pokédex entry or chase objective.

Mew's connection to Mewtwo is now something the player can infer from the original journals and this image. Neither Pokémon becomes obtainable through this scene.

### K7 — Before the summit

*Optional Route 22 conversation before the first Kanto Championship, if the Cinnabar reveal has happened.*

The familiar traveler is back, but the player now knows who he is. He is still using the disguise around other people.

> **Mewtwo:** They will call you Champion if you win.
>
> **Mewtwo:** I wonder what you will do when nobody is asking you to prove anything.

The line bridges naturally into Johto: the player can keep helping after becoming powerful. Mewtwo does not give an item, change the rival battle or accompany the player through Victory Road.

This scene can be missed without losing the ending. After the Kanto League, use a brief retrospective version if the traveler is met before his native encounter is resolved.

### K8 — A meeting without a disguise

*Optional postgame conclusion at the existing Mewtwo encounter in Cerulean Cave, whenever its original prerequisites have been met.*

The player reaches Mewtwo's original location. This time there is no disguise, no distant window and no question asked through a stranger's face.

> **Mewtwo:** You knew where I was. Still, you came yourself.
>
> **Mewtwo:** I would understand the bond that brought you this far.

The new prompt offers **“Face Mewtwo”** or **“Leave for now.”** Leaving returns control without consuming the original encounter. Facing it continues into the existing native battle, with its original level, catch rules and outcomes.

If caught, the additional line is brief:

> An unanswered question has become a journey together.

If defeated or the encounter ends without a catch, use the native outcome and a neutral reflection:

> You have met without a disguise. The rest remains unwritten.

Do not show Mewtwo fleeing in a cutscene after a successful catch, manufacture a second copy, or promise a rematch the original game does not provide. The story does not equate capture with proving moral worth.

After the native encounter is closed by a catch or defeat, a safe later exit can show a final distant glimpse of Mew. It watches the player leave, then fades. It has been watching Mewtwo learn to make his own decisions, not conducting an exam the player could fail. The later reflection stays neutral because the original durable fought state does not distinguish capture from defeat. Fleeing retains the original retry and does not count as this ending.

Cerulean Cave's existing Sevii-related unlock remains intact. The player may enter Johto before this conclusion. Optional Johto callbacks can acknowledge an unresolved observer, but the core Kanto arc does not require following Mewtwo between regions.

### How the two stories fit together

| Campaign point | Ho-Oh / Nao thread | Mewtwo / Mew thread |
|---|---|---|
| Early Kanto | A generous act, then a mysterious flyby | A stranger questions the act; a second observer is hidden nearby |
| Pewter / Mt. Moon | Nao wants a legend to return | Mewtwo asks who gets to decide a Pokémon's future |
| Lavender | Nao learns that care cannot depend on miracles | Mewtwo sees Pokémon staying where they are free to leave |
| Celadon / Silph | Rocket misuses research about welcoming sounds | Mewtwo compares the player's choices with Rocket's ownership mentality |
| Cinnabar / League | The sky mystery waits while Kanto reaches its climax | The stranger's identity is revealed; power becomes a question of responsibility |
| Johto | The Ho-Oh thread becomes the regional emotional arc | Kanto's observer thread can rest while the player continues helping |
| Optional Kanto postgame | Earlier places remember the journey | Cerulean Cave resolves the existing encounter without a new access gate |

Do not add a new cutscene for both threads at every stop. Lavender, Celadon and Silph use optional interactions, with original game business first. Mew's glimpses are sparse and silent; missing one never spoils the story.

## Chapter 5 — The road west

*Oak's existing post-Kanto League referral, followed by the western Indigo pass.*

Oak congratulates the player as usual, then connects their early observation to his existing referral.

> **Oak:** Professor Elm has heard reports of a remarkable bird in Johto. Your description reminded me of them.
>
> **Oak:** I'd like you to meet him in New Bark Town. Your experience could be a great help to his research.
>
> **Oak:** When you're ready, return to Indigo Plateau and take the western pass. It leads to New Bark.

The original credits and return to Pallet still occur. Sevii remains available under its own conditions. Johto does not require finishing Sevii or completing a new Ho-Oh checklist.

The pass is quiet. There is no second sighting here. The landscape itself pays off the direction Ho-Oh flew: for the first time, the player is walking into that horizon.

Elm welcomes an experienced Kanto trainer. His existing research introduction, Mr. Pokémon errand and subsequent Silver sequence continue.

> **Elm:** Oak told me about the bird. I'd love to hear everything you remember.
>
> **Elm:** First, there's a research matter I could use your help with. Mr. Pokémon has made another discovery.

The story introduces no new starter selection or party reset; the merged campaign's established rules remain authoritative.

## Chapter 6 — A city listening

*Ecruteak, after the original Burned Tower event has finished.*

Nao is home. Her notebook now contains reports from two regions, but the tower still offers no answer.

Morty identifies the bird in the player's description with far greater confidence. He recounts the local tradition of the burned tower, three Pokémon lost there, and Ho-Oh's restoration of their lives. The existing game supplies the precise history and the legendary beasts' original release scene.

> **Morty:** People remember the fire. They remember the miracle.
>
> **Morty:** I wonder how often they remember that the Pokémon had nowhere safe to return to.

Nao wants to play a reconstructed welcoming melody from the tower. Morty permits repairs to the ordinary bells on the grounds but cautions against treating a ceremony as a command.

> **Nao:** If the sound is wrong, I can fix it.
>
> **Morty:** Perhaps. But what will you do if the sound is right and Ho-Oh still doesn't come?

She has no answer.

An optional Eusine line, placed beside one of his existing encounters, offers a contrasting response:

> **Eusine:** One sighting would never be enough for me. I'd have to understand why it appeared.

His pursuit of Suicune remains his own story. The player does not need to capture or register the beasts for this new arc.

## Chapter 7 — The Pokémon already here

*Short optional callback after the existing Amphy medicine event in Olivine.*

Nao has come to hear the harbor bells. Instead, she finds a town worried about its lighthouse Pokémon. After the player completes Jasmine's original request, Nao stays to help tidy the lighthouse approach.

> **Nao:** Nobody asked whether Amphy was rare. They just wanted him to get better.
>
> **Nao:** I think I understand Mr. Fuji a little more now.

The player can answer, "He's their friend" or "They need his light." Nao agrees with either; the choice changes a line, not a hidden score.

The original Lake of Rage and Mahogany events then give the theme a sharper edge. Team Rocket has already shown what happens when people force Pokémon to respond to a signal. An optional post-event remark from Lance connects the idea without changing that operation's existing cause or mechanics:

> **Lance:** They knew how to make Pokémon react. They never cared what the Pokémon were feeling.

## Chapter 8 — A voice that does not belong

*Goldenrod, immediately after the original Radio Tower Rocket story and rewards finish.*

The restored station has found a secondary recording loop attached to the equipment used by Rocket. The takeover's original purpose remains calling for Giovanni. This additional experiment spliced Nao's copied bell recordings into an attempted lure.

Nao recognizes the sequence. The director explains that the experiment frightened nearby Pokémon; there is no evidence it could summon Ho-Oh at all.

> **Nao:** I thought if I found the right sound, it would have to listen.
>
> **Nao:** That's what they thought, too.
>
> **Director:** Wanting to be heard isn't the same as making someone answer. What happens next is your choice.

The player helps disconnect the playback unit. The chimes stop. A moment of ordinary station noise follows: footsteps, a door, conversation. The absence of the false song is the scene's release.

Nao keeps her research. She does not destroy knowledge because Rocket misused it. She crosses out the heading "How to bring Ho-Oh back" and writes "A welcome, if it returns."

> **Nao:** Will you come to Ecruteak? I want to try this properly. Even if nothing happens.

The existing Radio Tower rewards, including whichever Wing the original branch awards, are untouched.

## Chapter 9 — An answer on the wind

*An optional return to Ecruteak after the Radio Tower is free.*

The player meets Nao on the tower grounds. She has repaired the ordinary bells and arranged a small welcome with Morty's help. No collection quest, donation or capture requirement stands between the player and this scene.

Nao shows her grandfather's practice bell. Its crack is still visible.

> **Nao:** I could replace it. Then it would sound perfect.
>
> **Nao:** But I think I'd miss this one.

She rings it once. The note is uneven. The player and Nao wait. Nothing happens.

Nearby, a small bird hops toward the path. Nao notices a loose cord near its feet and moves it aside. She laughs at herself for expecting a legend while overlooking something small.

> **Nao:** Well. Someone came.

As the little bird settles, the light changes. Color passes over the tower. A familiar cry carries across the city.

Ho-Oh flies above Ecruteak.

There is no proclamation that Nao's bell caused it. Morty looks up. Nao reaches for her notebook, then lets her hand fall. For once, she watches without trying to turn the moment into proof.

> **Nao:** I thought I would know what to say.
>
> **Morty:** You can tell us afterward.

The bird continues beyond the tower. Nao watches until it is gone.

> **Nao:** It came back.
>
> **Nao:** And tomorrow, we'll still have work to do.

This closes Nao's story in both the Ho-Oh and Lugia branches. It does not start a battle or unlock the roof. The original Route 39 shadow sighting and Baoba's Gold/Silver choice still happen independently; the first-day Ho-Oh sighting does not answer that later question for the player. Ho-Oh's original Wing, tower, Kimono and encounter rules remain. Whirl Islands Lugia additionally requires the three replica encounters in Black Tide. If the player has already resolved the native Ho-Oh encounter, use the alternate rainbow-and-memory staging in the handoff rather than displaying a second wild Ho-Oh.

## Chapter 10 — Home, with a larger sky

*After the existing Johto League victory, on an optional visit to Pallet.*

Oak has received a letter from Nao. She has begun recording local stories again, including accounts of ordinary Pokémon that guide travelers, keep lights burning and find their way home.

> **Oak:** She asked whether your next discovery could be something that stays still long enough to draw.

At the Route 1 edge, a Pidgey is sheltering another small bird from a gust. The player pauses. The camera briefly holds on the open sky; Ho-Oh does not make another appearance.

If the player saw the opening, a final line recalls it:

> You remember the first day. The sky seems larger now.

For a player who joined this story later:

> There is still so much beyond the horizon.

Control returns. Kanto, Sevii and Johto remain places to explore, not chapters that close behind the player.

## Recurring characters — Rocket, research and trust

**Owner direction, October 15:** include Jessie, James and Meowth; develop Silver's gradual trust; give Blue a positive scientific path after losing, following Oak. The earlier suggestion that Blue struggles with losing his title is discarded. Do not write resentment, wounded pride, a crisis of purpose or research as a consolation prize into his added post-League scenes. His possible Eevee starter remains a separate, undecided recommendation.

The following are **proposed event drafts**, with conceptual IDs only. For every row: **game source file/script label and exact build are unassigned; implemented dialogue is unavailable; gameplay is NOT RUN; actual in-game images are pending.** Quoted lines are the complete dialogue proposed for these small beats, not extracted game text. Event-specific script references, exact implemented textbox order, choices/outcomes and local gameplay captures must replace this draft review metadata when engineering implements them. No mockups or unrelated-build captures stand in for those missing images.

### Jessie, James and Meowth — Big plans, small disasters

Use a few memorable appearances across the adventure rather than interrupting every town. They pursue Pikachu when the player's history supports it; otherwise their scheme targets research equipment or a rumored valuable Pokémon. They never take a party member or item away as a scripted penalty. Locations below are proposed staging areas requiring actual map/actor checks.

| Event | Proposed location and trigger | Draft dialogue in order | Choice and outcome |
|---|---|---|---|
| JT01 — The wrong end of the net | Mt. Moon exit area, after original fossil business and safe field control; early Kanto only | Jessie: "One rare Pokémon, and headquarters will finally remember our names." James: "They remember mine. I signed for the net." Meowth: "Then help me out of it!" | No choice. Their tangled equipment ends the attempt; they retreat. No battle, theft or extra fossil reward. |
| JT02 — Completely official researchers | Celadon, optional street interaction after the Hideout is cleared | James: "We're conducting a completely official Pokémon survey." Jessie: "Question one: would your Pokémon like to stand in this convenient cage?" Meowth: "You were supposed to say observation booth!" | "No thanks" ends safely; "Who sent you?" reveals the uniforms and gets Jessie: "This survey is closed!" Both end in retreat, with no reward or progression gate. |
| JT03 — A fresh start, allegedly | Goldenrod, optional encounter before the Radio Tower takeover; suppress during and after that crisis | Jessie: "New region. New disguises. New reputation." James: "Same unpaid balloon bill." Meowth: "And the same kid!" If no prior trio meeting occurred, use Meowth: "And an audience!" | No choice. A failed disguise reveals the trio and they leave. Any later battle version is a separately specified encounter, not assumed by this draft. |
| JT04 — Even we know better | Whirl Islands rescue aftermath, optional conversation only after Shadow Lugia actually resolves | James: "They had a whole room of frightened Pokémon. I couldn't leave the cages shut." Jessie: "We were inspecting company property." Meowth: "Sure. With all the doors open." | No choice. The trio has helped ordinary captive Pokémon escape. The player still broke all three links and resolved Lugia; the trio takes no credit for those actions. They leave together without a permanent redemption or forced alliance. |

The trio remains distinct from the seven-friend comedy, now developed in its own treatment. Keep their jokes away from the middle of Pokémon Tower's grief, Mewtwo's reveal and Lugia's battle/restoration. Their humane moment can coexist with future foolish schemes. The existing Giovanni and Johto executive plots remain authoritative.

### Blue — Following in Oak's footsteps

Keep the original competitive Kanto journey through the first Champion battle. Begin this added direction afterward, once the original Hall of Fame, credits and return have completed. Blue is interested, confident and pleased with the work. He remains a capable trainer; native rematches can be friendly competition and a source of observations.

| Event | Proposed location and trigger | Draft dialogue in order | Choice and outcome |
|---|---|---|---|
| BL01 — Back at the lab | Optional Oak's lab conversation after first Kanto League clear, outside Oak's original reward/referral transactions | Blue: "Great battle, {PLAYER}. Grandpa's taking me on his next field survey." Blue: "I've already filled half a notebook. Apparently I'm supposed to leave room for the results." | No choice. Establishes his chosen direction; no new Oak grant, travel prerequisite or rematch change. |
| BL02 — A question worth following | Optional Route 1 fieldwork scene after BL01 | Blue: "These Pidgey all use the same tree when the wind changes. I'm trying to find out why." | "What have you learned?" → Blue: "The youngest ones follow an older bird. Tomorrow I'm watching who chooses first." "I'll let you work" → Blue: "Tell me if you see them farther down the route." Both return control; no timed errand or research counter. |
| BL03 — Notes from Johto | Optional Oak's lab follow-up after the player's first completed Johto introduction and BL01 | Blue: "Grandpa and I are comparing observations from both regions." Blue: "Next time we battle, I'm bringing a notebook. Try to give me something interesting to write down." | No choice. Friendly anticipation of an existing later battle, without launching, promising an unlocked rematch or changing the League team. No claim about optional sights the player missed. |

Blue does not become Viridian Gym Leader in this addition; this campaign keeps FireRed's Giovanni story. His research never depends on meeting Silver or finishing a legendary quest. If native post-Champion dialogue contradicts this settled outlook, identify and adapt that dialogue narrowly while preserving the associated battle, reward and progression logic.

### Silver — Learning to stay

The exact native progress bindings remain to be audited. These are three chronological stages in character growth, not three new rival battles. Suppress obsolete early scenes once the corresponding later development has happened.

| Event | Proposed location and trigger | Draft dialogue in order | Choice and outcome |
|---|---|---|---|
| SV01 — A pause on the road | Safe Ecruteak outskirts after the local native rival event, while Silver is still early in his trust arc | Silver: "We're stopping here. Catch your breath." Silver, noticing the player: "What? You can't train properly when you're exhausted." | No choice. He waits beside his tired partner, then departs with it. A small caring act, not a declaration that his native arc is already resolved. |
| SV02 — Waiting for his partner | Proposed Goldenrod Pokémon Center follow-up only after the native story has challenged his treatment of Pokémon; exact prerequisite pending | Silver: "They said it'll be fine." Silver: "I'm waiting anyway." | "I'll wait with you" → Silver: "...Do what you want." "See you later" → Silver: "Yeah." Both are cosmetic, with no morality score, healing delay or change to the player's party. |
| SV03 — Ask again | Optional conversation at a verified late rival training location after his original late trust milestone | Silver, to his partner: "Another round?" His Pokémon responds willingly. Silver, to the player: "We'll be ready next time." | No choice. The moment shows partnership through his behavior; no immediate extra battle, reward or override of native evolution/team progression. |

Silver keeps his saved regional rival name, original stolen partner, encounter order and independent Johto state. Blue's contentment and Silver's gradual change are parallel developments; neither character needs to lecture the other or replace the native lessons already in Silver's story.

## Optional later additions

These are hooks for separate writing passes, outside the core event package:

- **Sevii — Stories Carried by Sea:** Travelers disagree about a rainbow seen offshore. A local child has a sketch that resembles a familiar wing. Flavor only; Sevii is never a mandatory Ho-Oh errand.
- **Kanto return conversations:** Fuji asks how Nao is doing. A Pewter visitor recognizes her revised drawing. These let earlier places respond to the journey without creating new quest gates.

The earlier **Whirl Islands — A Safe Passage** idea has been replaced by the active [Black Tide chapter](johto-shadow-lugia-story.md). Additional **Gen 3+ legendary storylines** remain deferred, with the expressly requested Giratina role in the friends' story now active. Existing expansion encounters are not removed by that writing decision.

## Companion comedy — Friends from the Other Side

**Active writing direction, October 15:** the owner supplied personalities and requested a profane, deliberately out-of-place isekai comedy across the entire Kanto-to-Johto journey. The [full friends story](friends-from-the-other-side-story.md) now contains FG01–FG22, their draft dialogue and choices, gradually acquired Pokémon teams, seven introductory player battles, individual final matches and a return-home/reunion ending. These are proposed scenes, with no implementation or current-build images claimed.

Giratina brings **Tim, Xavier (X), LB, Brian, Jon, Nick and Ham** from the owner's world. They are fictionalized adults. Brian is a homebody and 2K fan; Xavier has hippie language and practical judgment; Tim loves Thailand travel and makes adult-nightlife jokes; LB constantly invokes Drake; Nick is a grounded, relaxed 2K fan; Jon is loud and profane; Ham has strange, sparse interjections and unexpected courage. The owner permits "nigga" **only from LB directly to Xavier or from Xavier directly to LB**. Neither uses it toward anyone else or the group collectively. Do not infer racial identities or extend that dialogue permission. Sprites remain undecided.

Their independent progress and friendships carry the story between major campaign events. Preserve Pokémon Tower's grief, Mewtwo's reveal, original legendary rituals and Nao's welcome. The group never claims the player's victories or gates regional progression. Tim's sexual references stay non-graphic and about human adults. LB uses accurate, context-triggered Drake album titles: for example, "it's all the same" prompts "First of all, NOTHING WAS THE SAME." The revised scenes are full conversations with responses, actions and callbacks, not a series of isolated one-liners. No copied lyrics or fabricated artist quotations are required.

Giratina remains **nonobtainable** and its motive remains mysterious. It permits the eventual return home with the friends' willing Pokémon and a later visit; it never becomes a battle, gift, egg, trade, party reward or reusable player portal. Audit other active acquisition routes before asserting game-wide nonobtainability. This pass develops writing and handoff requirements only; it changes no game source, assets or saves.

## Canon and original invention

The opening takes inspiration from Ho-Oh's appearance at the end of the first television episode, a connection confirmed by the [official Johto quiz](https://www.pokemon.com/us/pokemon-news/test-your-johto-region-knowledge-with-this-quiz). New games now use Pikachu; starter-neutral staging supports older saves without rewriting their history. The player is still their own trainer, not Ash.

The acquisition structure specifically follows **Yellow**: Pikachu first, Bulbasaur in Cerulean, Charmander on Route 24 and Squirtle in Vermilion after the Thunder Badge. See the [Yellow gift encounter reference](https://www.serebii.net/yellow/gift.shtml). The garden rescue, rain sequence, harbor incident and their dialogue above are proposed original adaptations with anime-inspired themes, not a claim that these exact quests occur in Red, Blue or Yellow. Yellow's original Bulbasaur friendship check is deliberately replaced by a visible story task in this proposal.

Ecruteak's bells, Morty, Eusine and concern about the relationship between humans and Pokémon draw on **“For Ho-Oh the Bells Toll!”** The [episode reference](https://bulbapedia.bulbagarden.net/wiki/EP227) documents the stolen Crystal Bells and Suicune's intervention. Our story does not repeat that incident or replace the game's sacred bells with Nao's ordinary practice bell. Game history takes precedence where the television account differs; new dialogue avoids conflicting dates and tower names.

The dropped Rainbow Wing leading into a Ho-Oh quest is part of the [2017 *I Choose You!* film synopsis](https://www.pokemon.com/us/animation/movies/pokemon-the-movie-i-choose-you). This treatment does not import the film's Rainbow Hero prophecy, Mount Tensei or Marshadow trial. The actual game item remains under its original progression rules.

Nao, her family, the recordings, Rocket's secondary experiment, all new dialogue and the welcome scene are **original fan-story additions**, not claims about established Pokémon canon. Existing characters and lore retain their original attribution; see the project's [sources and rights notes](sources-and-rights.md). No episode dialogue or game assets are reproduced by this writing handoff.

The [official Mewtwo Pokédex](https://sg.portal-pokemon.com/pokedex/0150/) supports its artificial origin and Psychic typing. The [official first-movie synopsis](https://sg.portal-pokemon.com/tv-film/movie/1-1/) supplies inspiration for its distrust of humans and changing view of Pokémon friendship. The traveler disguise, questions and encounters above are original adaptations; the disguise uses a narrative psychic veil, **not Transform**, and is not presented as an established canonical ability.

The [official Mew Pokédex](https://sg.portal-pokemon.com/pokedex/0151/) describes Mew becoming invisible and approaching people unnoticed. Mew secretly following this trainer and Mewtwo is our invented use of that lore. The Mansion journals and the native games' encounter rules remain the continuity authority; no film clone tournament, memory erasure or alternate protagonist history is imported.
