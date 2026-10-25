# Friends story: when each scene plays

Where and when every scene of the Friends story (FG01–FG22) and every Friends battle can happen in the game as it
is built now. It is read from the code, not from the drafts: `FriendsStory_GetGate` and `FriendsStory_GetMapScene`
in `engine/src/friends_story.c`, the camps in `engine/src/data/friends_scene_locations.h`, who stands at each camp in
`sForeground` (`engine/src/friends_scene.c`), and the scenes themselves in `engine/data/scripts/friends_story.inc`.
Update this page in the same pull request as any change to those. The story itself is described in
[the campaign guide](campaign-story-and-progression-guide.md) and
[friends-from-the-other-side-story.md](friends-from-the-other-side-story.md).

Last checked: 2026-10-25, `v2-main` at `45d5bbe1`.

## How the story moves on

* **One scene at a time.** The group has a current stage (1–22). Each scene belongs to one map. When the player
  enters a map whose scene is later than the current stage and that scene's condition is met, the stage jumps to
  it. The stage never goes back.
* **Scenes can be skipped.** Because the stage jumps, a scene whose map the player never visits while it is current
  is passed over for good. For example, a player who reaches Fuchsia City (scene 9) by Cycling Road before the Rocket
  Hideout and the Poké Flute never sees scenes 7 (Celadon) and 8 (Lavender).
* **Where the group stands.** The friends appear only on the current stage's map, at its camp. Only the friends
  listed below are there; the rest are "nearby in the story".
* **How a scene starts.** Scene 1 plays by itself on entering Viridian. Every other scene starts when the player
  talks to one of the friends at the camp (`Friends_Interact`, which picks the scene by the stage). A scene seen
  once replays only its choice menu.
* **Cut-offs.** Scenes 1–11 stop after the Kanto Hall of Fame (`FLAG_SYS_GAME_CLEAR`); a player who becomes
  Champion first joins at scene 12. Scenes 13–19 stop after the Johto Hall of Fame.
* **Ready.** Nothing happens unless the story has been adopted for this save (`FriendsStory_IsReady`): new games
  are; old saves are adopted only from a blank state.

## The scenes

Camps are map blocks. "Rebuilt" means the map has been redrawn since the 37C snapshot, so its camp should be looked
at again when the scene is next played there.

| # | Scene | Map and camp | Opens when | Starts | At the camp | Battle | Notes to keep track of |
|---|---|---|---|---|---|---|---|
| 1 | Seven people and one HDMI cable | Viridian City, south road (26,46) | Pokédex received | By itself on entering, mandatory | all seven | | Rebuilt map. Since PR #34: Giratina drops them on the road, the camera frames them, the player walks up to (25,48). Played in replay tests. |
| 2 | Brian invents camping badly | Route 2 (5,62) | Pokédex received | Talk | Brian, Jon, Nick | Brian (B01), optional | Rebuilt map. Not played since the rebuild. |
| 3 | The acoustics are incredible | Route 4 (83,14) | The Mt. Moon fossil received (`FLAG_GOT_FOSSIL_FROM_MT_MOON`) | Talk | Jon, Nick, LB | Jon (B02), optional | |
| 4 | Everybody has a partner now | Cerulean City (26,23) | Pokédex received | Talk | Ham, X, Tim | | Entering Cerulean before Route 4 with the fossil skips scene 3. |
| 5 | Tim discovers the ferry schedule | Vermilion City (30,19) | Pokédex received | Talk | Jon, Nick, Tim | | |
| 6 | Two very different coaching styles | Route 11 (25,7) | Pokédex received | Talk | Brian, Nick, LB | Nick (B03) or LB (B04), optional | |
| 7 | Manifesting a room | Celadon City (27,31) | Rocket Hideout cleared (`FLAG_HIDE_CELADON_ROCKETS`) | Talk | Brian, X, LB | X (B05), optional | Skipped if the player reaches a later scene's map first (see above). |
| 8 | Quiet outside Lavender | Lavender Town (13,13), then Mr. Fuji's house (3,6) | Poké Flute received | Talk | Ham, Jon, Nick | | The conversation moves into Fuji's house and back out. |
| 9 | The group gets actual responsibilities | Fuchsia City (19,21) | Pokédex received | Talk | Brian, Nick, Tim | Tim (B06), optional | Reachable early by Cycling Road, which skips 7 and 8. |
| 10 | A very bad job interview | Saffron City (33,15) | Silph Co. cleared (`FLAG_HIDE_SAFFRON_ROCKETS` and the Master Ball) | Talk | Brian, X, Tim | | |
| 11 | The television in the water | Cinnabar Island (46,20) | The Mansion's Secret Key found (`FLAG_HIDE_POKEMON_MANSION_B1F_SECRET_KEY`) | Talk | Brian, Nick, X | | Shows Brian's living room in the water. |
| 12 | Seven terrible spectators | Pallet Town (12,22) | Kanto Hall of Fame, and Oak's Pallet scene done (`VAR_MAP_SCENE_PALLET_TOWN_OAK` ≥ 3) | Talk | Brian, Nick, Tim | | Rebuilt map. Not played since the rebuild. |
| 13 | No second character creation | New Bark Town (21,14) | Met Elm | Talk | Brian, Ham, Nick | | |
| 14 | Xavier reads the room | Ruins of Alph, outside (29,29) | Met Elm | Talk | Nick, X, LB | | |
| 15 | Jon learns one useful volume | Azalea Town (55,24) | Slowpoke Well cleared (Azalea state ≥ 3, its Rockets gone) | Talk | Brian, Jon, Nick | | |
| 16 | The move has a name | Goldenrod City (24,14) | Goldenrod state 1–5, or 11 and later | Talk | Ham, Nick, LB | Ham (B07), optional | Goldenrod holds scene 19 too: 19 wins once its condition is met. |
| 17 | A reflection that waits | Ecruteak City (51,41) | The legendary beasts released | Talk | Brian, Nick, X | | Shows Brian's living room again. |
| 18 | Tim books the right trip | Olivine port, outside (16,6) | Ampharos healed | Talk | Nick, Tim | | |
| 19 | Nobody yells at the frightened Pokémon | Goldenrod City (24,14) | Goldenrod state 11 and later | Talk | Ham, Jon, Nick | | |
| 20 | We actually know what we are doing | Blackthorn City (21,49) | Johto badge 8 and Blackthorn state ≥ 4 (after Clair's Dragon's Den) | Talk | Brian, Nick, Tim | | The last battles before the departure. |
| 21 | Everybody goes home | New Bark Town (21,14) | Johto Hall of Fame, farewell not yet seen | Talk | all seven | | New Bark holds scenes 13, 21 and 22. Giratina comes back; the group leaves with their partners. |
| 22 | Visitors with too much luggage | New Bark Town (21,14) | After 21, once the player has been to another map and comes back (`FLAG_FRIENDS_REUNION_ARMED`) | Talk | all seven | Rematches with each friend (FG_Battle08–14) | A Continue on New Bark itself doesn't arm it. |

## Battles

| Battle | Offered in | Script |
|---|---|---|
| B01 Brian | Scene 2's first choice | `FG_Battle01` |
| B02 Jon | Scene 3's first choice | `FG_Battle02` |
| B03 Nick / B04 LB | Scene 6's two choices | `FG_Battle03`, `FG_Battle04` |
| B05 X | Scene 7's first choice | `FG_Battle05` |
| B06 Tim | Scene 9's first choice | `FG_Battle06` |
| B07 Ham | Scene 16's menu | `FG_Battle07` |
| Rematches, all seven | Scene 22's goodbye menu | `FG_Battle08`–`FG_Battle14` |

All battles are optional. A loss is remembered: the next conversation with the group starts with its follow-up (`FG_Loss01`–`FG_Loss14`).

## Adjustments to track

* Scenes 2 and 12 have camps on rebuilt maps (Route 2, Pallet Town) and haven't been played since the rebuild.
* Sequence breaks skip scenes for good (scene 3 by entering Cerulean first, 7 and 8 by Cycling Road to Fuchsia).
  If that isn't wanted, the stage could wait for the skipped scene instead of jumping.
* Only scene 1 plays by itself; every other scene can be missed by not talking to the group.
* The camps' first local ids all match their maps' Friends objects (checked 2026-10-25). A map edit that adds or
  removes an object before the Friends shifts their ids: check `friends_scene_locations.h` after it.
