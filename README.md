# FireRed Kanto → Johto

One trainer and one collection through FireRed's Kanto and Sevii Islands, then Heart & Soul's Johto, with the
owner's own stories (Pikachu's companion and bike, the friends' arc, Nao and the rainbow, the Rocket trio, Mewtwo
and the Stranger, Black Tide). After the Kanto League, the road west of Indigo Plateau (League West Pass) leads down
to Route 27 and New Bark Town; Kanto and Johto keep separate story progress.

This is a private repository in active development. **Read [AGENTS.md](AGENTS.md) before changing anything.**

## Build and test

```sh
python3 scripts/bootstrap_upstream_inputs.py --fetch   # once: three small upstream inputs (git-ignored)
cd engine && make -j4                                   # pokefirered.gba
```

The game is edited and tested with [pae](https://github.com/malikpervez/pkmn-asset-editor):

```sh
pae doctor -p engine      # can this machine build and play-test?
pae serve -p engine       # the editor: http://localhost:8765
pae test run -p engine    # build, then replay every test in engine/pae_tests/
```

## Where to look

* [Story guide](project/docs/campaign-story-and-progression-guide.md): 19 chapters, start to finish.
* [AGENTS.md](AGENTS.md): how the source is organised, how to make and prove a change, and what not to touch.
* [Attribution](ATTRIBUTION.md). Upstream base: PokemonHnS-Development/pokehns-expansion commit
  `167aa6d537b109bb229c231ddce4616974c4da71` (pret pokeemerald → RHH pokeemerald-expansion → HnS).
* `provenance/`, `CLOUD_TESTING.md` and the `project/` records describe the 37C review snapshot this development
  started from.

## What changed since 37C

* Hoenn, the Battle Frontier, Trainer Hill, the Battle Tents and HnS's own Kanto are gone; the event islands use
  HnS tiles. Cries of Pokémon the game never shows play Ditto's cry (4.4 MB saved). The ROM uses about 27.1 MB.
* Johto's scripts are ordinary source again (one file per map, readable texts and names) instead of one generated
  7.4 MB file, and every map's `map.json` holds the events the game has.
* The repository builds one game: the Emerald, HnS and LeafGreen targets, their code branches, 788 maps and 750
  layout folders that the game did not have are removed. Every cleanup step built a byte-identical ROM
  (removing the other targets' code branches changed only the line numbers that asserts embed).

Original upstream notices remain applicable. Personal saves and private review evidence are not in this repository.
