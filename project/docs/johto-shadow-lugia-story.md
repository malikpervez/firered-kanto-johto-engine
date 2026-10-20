# Black Tide — the Shadow Lugia storyline

**Current owner direction, October 14, 2026. Story/design only; not implemented.** This replaces the earlier small Lugia rescue outline. It also supersedes the briefly considered relocation of the Kanto birds: **Articuno, Zapdos and Moltres keep their original Kanto/Sevii encounters.** The Johto attackers are separate, corrupted replicas created by Team Rocket.

This arc joins [The Road Beneath the Rainbow](kanto-johto-rainbow-story.md). Implementation conditions and outcomes are specified in the [engineering handoff](kanto-johto-rainbow-event-handoff.md#black-tide--required-shadow-lugia-arc).

## The premise

Team Rocket has failed to keep control of powerful Pokémon before. A remaining research operation has taken a different approach: create three obedient weapons and use them to break a fourth Pokémon's resistance.

Its replicas of Articuno, Zapdos and Moltres carry conditioning devices that channel their attacks into a single pattern. The devices are designed to exhaust Lugia and force it into a violent Shadow state. The birds are visibly hostile, with unnatural coloring and synchronized movements that distinguish them from the original legendaries.

The player must **defeat or catch each of the three replicas**. Every resolved encounter severs one part of Rocket's control network. Once all three are stopped, the player can face **Shadow Lugia**. Rocket's transformation has already taken hold; destroying the links makes a rescue possible, but does not instantly restore Lugia.

This gives the story a clear progression: **witness the attack → stop three corrupted birds → confront Shadow Lugia → restore the guardian of the islands**.

The Shadow conditioning, replica project and restoration below are original story proposals. They do not imply that a complete Shadow Pokémon system already exists in this engine.

## 1. Three cries over the water

Olivine and Cianwood sailors report lightning without rain, ice forming on warm seawater, and drifting ash far from any eruption. One sailor insists that he saw three enormous birds circling the Whirl Islands in formation.

> **Sailor:** Birds fight over fishing grounds. I've seen that before.
>
> **Sailor:** These three took turns. Like someone was telling them when to strike.

The warnings can appear after the Radio Tower is liberated, but the playable crisis begins only when the player's existing Johto progression makes the Lugia encounter available. This avoids sending an unprepared player into an inaccessible island sequence.

An optional Nao conversation connects the disturbing rhythm to the theme of her research without making her responsible for Rocket's new project:

> **Nao:** A welcome leaves room for an answer.
>
> **Nao:** Whatever is out there keeps repeating until something obeys.

Her bell notebook is not a required quest item. The coastal story remains understandable without meeting her.

## 2. The guardian falls

At the Whirl Islands, the player witnesses Lugia under attack. Articuno's replica coats a wing with ice. Zapdos's replica strikes the exposed side. Moltres's replica drives Lugia back before it can rise again. Their attacks follow the same cruel sequence.

Lugia could lash out across the islands, but it keeps turning away from the inhabited coast. The player sees it take a hit while shielding a small group of wild Pokémon from falling debris.

A Rocket technician monitors the attack from a concealed relay.

> **Technician:** The first problem was making it angry.
>
> **Technician:** The second was making sure it stayed that way.

The player approaches. The technician escapes without replacing an existing Rocket boss or restarting the defeated Radio Tower takeover. The abandoned controls reveal three active links. The operation can continue without anyone at the console.

The birds make one final synchronized pass. Lugia's coloring darkens. Its next cry is distorted, and its attempt to shelter the nearby Pokémon becomes a violent burst of force. It retreats into the islands.

The three replicas separate to maintain their links from different positions. The player can now tackle them in any order, returning to heal or save between encounters. There is no real-time countdown.

## 3. Articuno — the frozen approach

The Articuno replica occupies a sheltered island approach where ice is spreading across the stone. Its movements are unnaturally precise: it turns toward every cry it hears, even when the sound comes from a frightened Pokémon rather than a threat.

The player first helps the nearby Pokémon move behind cover through a short interaction. No required species or move is introduced.

> The bird's eyes follow the relay's blinking light.
>
> It attacks before the next pulse can finish.

The player fights the corrupted Articuno. **Winning or catching it disables the ice link.** If defeated, it withdraws as the conditioning breaks; if caught, the connection collapses and its corruption fades before it enters normal party/storage use.

The ice nearest the relay begins to melt. Through the cavern, Lugia's cry sounds slightly less distorted. This is progress, not a complete cure.

## 4. Zapdos — the lightning shelf

The Zapdos replica guards a relay on an exposed rocky shelf. Every discharge makes the device answer, which triggers another discharge. Rocket has turned its own power into a repeating command.

The player approaches between scripted bursts. This is a short visual approach, not a reaction-time test, damage timer or new field-move requirement.

> A flash lights the rocks.
>
> For an instant, the bird's outline seems trapped inside its own lightning.

**Winning or catching Zapdos disables the electric link.** The flashes stop. The air becomes quiet enough to hear waves against the rock.

An optional inspection of the now-dark relay supplies the clearest evidence that these are replicas:

> The records describe three manufactured specimens.
>
> Their instructions contain no command to retreat.

Owning the original Zapdos does not resolve this encounter; it is a different individual created for Rocket's operation.

## 5. Moltres — the ash-filled hollow

The Moltres replica keeps circling a relay inside a sheltered, open-roofed hollow. Its flames flare whenever it tries to move away. Of the three, it most visibly struggles against its commands, then turns its aggression toward the approaching player.

> Its wings blaze brighter.
>
> The machine answers. The bird turns back.

**Winning or catching Moltres disables the fire link.** The forced flares end. A defeated replica leaves as its ordinary coloring returns; a caught replica is restored before entering normal party/storage use.

None of the birds is killed. Defeat and capture are equally valid ways to end the attack, with no moral score or reward penalty attached to either choice.

## 6. The silence beneath the storm

When the third link fails, the remaining relay goes dark. There is a moment when everyone expects the storm to end.

Instead, a deep cry shakes the cavern.

Rocket's controls are gone, but Lugia remains in the Shadow state. The process has driven it into a continuing fear response: it attacks anything that approaches, unable to distinguish rescue from another assault.

The Kimono Girls help the player prepare to approach. On the original Lugia route, their existing ceremonial choreography and the player's earned items give this moment its foundation; the new dialogue acknowledges the crisis.

> **Kimono Girl:** We can call to it now. We cannot make it trust us.
>
> **Kimono Girl:** Stand your ground. Give it something to recognize besides the attack.

For a later postgame encounter without the Kimono group present, a local keeper gives the same practical guidance. Do not replay completed Kimono battles or fabricate a new Bell grant.

The player can leave to prepare. All three bird victories remain recorded. Returning does not restart the attack.

## 7. Shadow Lugia

Lugia rises from the water in its corrupted appearance. This is the boss the player has been working toward; the story must actually present Shadow Lugia rather than claim it happened offscreen.

The player chooses **“Face Lugia”** or **“Prepare first.”** Facing it begins the final battle. The three bird encounters must already be resolved.

The first implementation design uses Lugia's existing species identity and native encounter level/catch rules, with scene-specific corrupted visuals. It does not assume a complete new permanent form, Shadow move list or purification subsystem. Those would require a separate design decision.

If the player **catches Lugia**, the last trace of the conditioning breaks, and the Pokémon is restored to ordinary Lugia before normal party/storage access. If the player **defeats Lugia**, the Shadow appearance fades during the aftermath and the restored Pokémon withdraws under the existing encounter rules. Losing or fleeing does not resolve the crisis; the player may return without repeating the bird battles, subject to the existing encounter's retry behavior.

The final image is quiet. No controller light answers Lugia's movement. The nearby Pokémon emerge from shelter, and the water settles.

> **Keeper:** For the first time since this began, it chose where to go.

If Lugia was caught, use an outcome-appropriate line instead:

> **Keeper:** It can hear something besides those commands now. Take care of it.

Only show capture-specific dialogue while the actual battle outcome is available. Later conversations describe the islands' recovery without inventing an ownership history.

The crisis happens once. If the original game later permits another Lugia encounter, it uses the restored ordinary appearance and its native rules; Rocket's replicas and their attack do not return.

## How this fits the combined game

- **The original birds stay in Kanto/Sevii.** Their encounters, captures, puzzles and flags are independent. The three Rocket replicas can also be caught; this intentionally allows a player to own an original and a rescued replica of the same species.
- **Lugia's selected story route gains a required chapter.** The existing Silver/Lugia route resolves its legendary story before the Johto League. Requiring these three battles therefore extends that route's pre-League progression. This is the owner's intended new gate, not an optional conversation-only addition.
- **The Gold/Ho-Oh route remains the Ho-Oh route.** Black Tide occurs when the later Whirl Islands Lugia encounter actually becomes available. No branch switch or early Wing/Bell grant is implied. The merged build's exact natural postgame access still needs verification.
- **Scope is Whirl Islands Lugia.** Existing separate Navel Rock content is not silently moved or disabled. Its presence is not proof that its ticket route is naturally reachable.
- **Earlier catches remain valid.** Neither Kanto bird ownership nor a traded Pokémon satisfies the three new replica battles. A supported save that already resolved Whirl Islands Lugia needs a retrospective/skip policy rather than a duplicate catch or forced reset.
- **Other Gen 3 and later legendary story development is deferred.** Rayquaza, Latias, Latios, Deoxys, later-generation Regis and Arceus receive no new storyline in this pass. The owner subsequently activated the [friends' Giratina comedy](friends-from-the-other-side-story.md) as a separate writing pass; Giratina remains nonobtainable and friends' sprites remain undecided. That story neither resolves Black Tide for the player nor requires the Lugia branch for its ending. Deferral does not remove existing compiled content.

All terrain labels above describe scene functions, not verified map IDs or existing clearings. Engineering must find safe placements or identify the required small map/asset changes while preserving normal navigation and original puzzles. Source review is not a gameplay test.
