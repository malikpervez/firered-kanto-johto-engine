# Patched HnS native regression — exact repair09 ROM

Codex executed the fresh desktop mGBA regression on 2026-10-08/09 (UTC chronology below; host America/New_York), completing HNS-01–08. HNS-09 remains **NEEDS OWNER TEST** for audible output: the owner requested muted sound. Its active-play, input and visual subchecks were executed. This is an early-game smoke test, not full Johto, postgame or broader RTC certification.

## Exact run and settings

- Source: `PokemonHnS-Development/pokehns-expansion`, commit `167aa6d537b109bb229c231ddce4616974c4da71`, repaired configuration, not pristine.
- Executed session: `hns/repair-09-native-01`; fresh native save, no previous progress imported. Host macOS 27/Darwin 27, arm64; desktop mGBA 0.10.5.
- [Executed manifest]([LOCAL_WORKSPACE]/_local/artifacts/repair-09-hns/manifest.json), SHA-256 `693ea19f406cbc8a942681df6965e6275c5424b559bbf7aa240ea6d557118e0b`.
- [Session metadata]([LOCAL_WORKSPACE]/_local/saves/hns/repair-09-native-01/session.json).
- [Exact ROM]([LOCAL_WORKSPACE]/_local/saves/hns/repair-09-native-01/hns-repair-09-native-01.gba), 33,554,432 bytes, SHA-256 `4bb58fe3c06bc0b60146aa946cbc34f087efa607f525f68e0a1e99c0db9cde75`.
- Local configuration/patch fingerprint `656b49ab221989a12362bb1bbc9e24303e833274e33c7bde2ec9822056a97b44`; cumulative repair09 patch SHA-256 `bea352da2bf5aa726084e4b418933c82287101abd1621af7b58e49e8d6de6c82`.
- Root/build evidence measured repair10 HnS ROM byte identity to this ROM: zero differing bytes, same SHA-256 (ELF/map also identical). This report keeps its actual repair09 manifest/session binding and does not claim a separate repair10 GUI run. Earlier repair08 partial execution does not transfer to this different ROM.

Inspected mGBA settings: SDL audio 44,100 Hz/buffer 1536/volume 256, normal and fast-forward Mute=1; OpenGL, frameskip 0, native FPS target 59.7275, audio sync on/video sync off. Load last state, load cheats and periodic save-state autosave off; native saves use the ROM directory; no BIOS supplied. Owner mute preference was preserved. Normal X/A, Z/B, Return/Start and arrows were used; no states, cheats, debug grants or warps.

Recommended campaign options were inspected and accepted unchanged: Gen7 movepool, physical/special split, Fairy and reusable TMs enabled; real RTC, shiny denominator 8192; randomizers/Nuzlocke/party and level limits/One Type Only disabled; EXP 1.0, player/trainer items and Centers enabled. The natural bedroom clock PM prompt was accepted without changing its values. Menu clock advanced from 8:37 PM to 10:47 PM during execution; this does not qualify all time-dependent encounters or palette transitions.

## Executed checks

| ID | Result | Actual observation |
|---|---|---|
| HNS-01 | PASS — EXECUTED | Cold New Game; Heart & Soul lighthouse/Oak-Wooper opening, male CODEX named through normal grid; bedroom and New Bark rendered. |
| HNS-02 | PASS — EXECUTED | Natural clock/Mom/PokéGear/shoes/front Elm Lab sequence; accepted errand, middle Cyndaquil gift and preview; actual male Lv5 HP19/19 party member. |
| HNS-03 | PASS — EXECUTED | Route29/Cherrygrove/Route30 eastern branch/Mr Pokémon/Oak sequence; first Silver sequence completed after two legitimate losses and a natural Lv6 rematch win. Police naturally named rival PATCH, Elm egg/adventure sequence completed; exit aide gave5 Balls, Mom departure dialogue and west departure completed. |
| HNS-04 | PASS — EXECUTED | Ordinary home/lab, New Bark↔Route29↔Cherrygrove↔Route30 connections, Cherrygrove Center, Mr Pokémon house and Guide tour/NPC dialogue. Navigation detours were corrected normally; no measured map defect. Cherrygrove Mart interior specifically NOT RUN; other interiors/campaign remain unqualified. |
| HNS-05 | PASS — EXECUTED | Wild Rattata/Hoothoot/Spinarak battles; normal defeat/EXP, poison survival and escape; female RattataLv3 captured with one Ball after weakening; Center and Elm machine healed party. |
| HNS-06 | PASS — EXECUTED | Bag pockets, party Summary/info/skills/moves, trainer card and Johto Dex opened without crash; Cyndaquil/Rattata owned entries and observed clock recorded. |
| HNS-07 | PASS — EXECUTED | Normal SAVE→Yes→saving screen→field; full CmdQ/process absence; cold exact-ROM title/native Continue restored Elm machine checkpoint and all compared fields. |
| HNS-08 | PASS — EXECUTED | Natural Route29 Potion pickup changed inventory and location; second normal save/full quit/cold Continue retained Route29/Potion and compared state. Pickup did not reappear or repeat. |
| HNS-09 | NEEDS OWNER TEST | Audible component muted/unheard. Active-play/input/visual subchecks PASS — EXECUTED: conservative601.2s measured ordinary movement, responsive controls, no observed hang; FPS variation recorded below. |

The first two Silver attempts lost against TotodileLv5, each returning normally to Cherrygrove Center with full HP and a40-money loss. Silver retriggered after each loss; neither loss was treated as completed progression. Natural Route30 training and healing preceded the third attempt: CyndaquilLv6, two Leers/three Tackles, win, level7 and normal rival disappearance. No reset or prepared save forced this result. Selected Gen7 campaign settings actually showed only Tackle/Leer at Lv6/7; the separate source learnset aid was not reported as runtime move acquisition.

## Two native persistence cycles

| Compared field | Cycle1 before/after cold Continue | Cycle2 before/after cold Continue |
|---|---|---|
| Identity | CODEX, male, ID42606; PATCH named normally and stored native supplement | Same CODEX42606/PATCH |
| Location/progression | Elm Lab healing machine; police/egg/adventure/Balls completed; lab exit did not replay police/Balls | Route29 Potion clearing (55,7); acquired ball absent; normal A facing former item gave no duplicate reward |
| Party | Male Cyndaquil7 HP23/23; female Rattata3 HP15/15; both held NONE | Same species/levels/HP/held items |
| Moves/PP | Cynda Tackle35/35, Leer30/30; Rattata Tackle35/35, TailWhip30/30 | Same moves/PP |
| Inventory/money | Ball4; Medicine empty; EXP.SHARE/GB PLAYER, Mystery Egg absent; money3220 | Potion1, Ball4; same key items/Egg absent; money3220 |
| Dex | GUI Johto seen5/owned2, Cynda004/Rattata017 owned markers/full entries | GUI seen5/owned2, both owned markers retained |
| Native Continue summary | CODEX/Dex2/time1:20 | CODEX/Dex2/time2:01 |

Between cycles the Potion was obtained naturally from the Route29 item ball; three intervening wild encounters were escaped through ordinary RUN, with no attack or item cost. Only two normal persistence saves were made. Each cold cycle started from an empty newly launched mGBA, then exact-ROM copyright/intro/title and the game's own Continue. Process checks after CmdQ returned `pgrep -fl mGBA` exit1 with no output.

Preserved backups, each131,088 bytes and mode0444:

- [cycle-01.sav]([LOCAL_WORKSPACE]/_local/saves/hns/repair-09-native-01/cycle-01.sav): `9c340868da9bcfd3c9f10032284e74a4e2497d70b186bfd48e224460a2a373b0`.
- [cycle-02.sav]([LOCAL_WORKSPACE]/_local/saves/hns/repair-09-native-01/cycle-02.sav): `a3a590c19b4215fc4f98cb23e7e808d0995a5b50fc68e16c43285417f2354822`.
- Final active [native save]([LOCAL_WORKSPACE]/_local/saves/hns/repair-09-native-01/hns-repair-09-native-01.sav) after the final full quit was whole-file equal to cycle02, same hash; no third normal save was made.

Independent read-only native inspections accepted both backups under the exact compiled repair09 field map/manifest: all14 payload sector checksums valid; cycle1 bank1/counter1/rotation1, cycle2 bank0/counter2/rotation2; CODEX/42606/PATCH, seen5/caught2 (National19/155), party count2 retained. Native decoding supplements the visible rival/Dex checks; it does not replace GUI party/location/progression evidence or infer unparsed fields.

## Active-play evidence and limits

After all builds were idle, 17 documented ordinary New Bark movement blocks executed334 directional holds of2000ms (668s raw control duration). A conservative1800ms per hold excluded turning/settling, yielding601.2s. Actual west/east traversal endpoints were viewed in the open lane; no sustained stationary wall holds were counted. Setup, menus, API/idle waits and adjustments were excluded; earlier natural story play was additional but not needed for this total. The wall interval 02:00:42.609–02:25:41.322 UTC is not asserted as continuous active time.

Active-block FPS snapshots ranged33.6–60.4, mostly near59–60, with transient lower values preserved. Other menu snapshots reached60.5; cold Continue/title snapshots also fluctuated. Movement remained responsive and no hang was observed; this does not establish constant60FPS or explain a cause. No performance tuning was attempted. CUA occasionally returned transitional/stale images or changed window size; refreshing the owned exact-ROM window restored observation, and those waits were excluded. No actor identity was inferred from external-change guards.

Private evidence: [chronological observations]([LOCAL_WORKSPACE]/_local/evidence/native/repair-09-hns-native-01/observations.md), [completed active-input log]([LOCAL_WORKSPACE]/_local/evidence/native/repair-09-hns-native-01/active-inputs.json), [cycle1 backup record]([LOCAL_WORKSPACE]/_local/evidence/native/repair-09-hns-native-01/cycle-01-backup.json), [cycle2 backup record]([LOCAL_WORKSPACE]/_local/evidence/native/repair-09-hns-native-01/cycle-02-backup.json), [final save comparison]([LOCAL_WORKSPACE]/_local/evidence/native/repair-09-hns-native-01/final-save-comparison.json), and [native inspection directory]([LOCAL_WORKSPACE]/_local/evidence/native/repair-09-backup-inspections). CUA screenshots were viewed in tool results; no disk screenshot files are claimed.

mGBA was fully quit at completion. Owner audio observation remains the outstanding HNS-09 component; all later-game and broader RTC tests remain outside this smoke run.
