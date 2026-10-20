# Pikachu bond and situation reactions — 36P

October 18, 2026. Local additive Workstream B implementation from frozen 36O. [Owner direction and bond policy](decisions/2026-10-18-pikachu-reactions.md). All earlier source, ROM, saves and evidence remain preserved.

## Implemented behavior

PC02 replaces the companion's three equally random reactions with 15 situation/bond outcomes. Pikachu remains a permanent presentation companion, independent of actual party/PC Pokémon, ownership, HP, status and friendship. No Pokémon, items, battle bonuses or campaign progress are granted or removed.

Closeness follows the existing normally saved trainer walking count: warming up below 4,000 steps, friendly from 4,000 to 15,999, devoted at 16,000 and above. Neutral surroundings offer two outcomes per tier: shy/curious, happy/playful, affectionate/trusting. Talking alone does not increase the tier. Supported older saves adopt their current total travel tier; there is no claim that Pikachu witnessed earlier events. This adds no separate happiness meter or persistent counter.

Context takes priority over generic affection:

1. Pokémon Tower and the actual FireRed imported Burned Tower: nervous, or reassured by your company at friendly/devoted bond.
2. Outdoor thunderstorm: startled, or startled then brave at devoted bond.
3. Other underground caves: alert to echoes.
4. Native Center music: relaxed in a quiet room. This also covers peaceful shops/League lobbies that use the same theme; it does not claim a recent heal.
5. Native Gym music: eager and cheering; it does not claim a victory.
6. Outdoor rain/downpour: shaking rain from its ears.
7. Outdoor night: yawning and trying to stay awake.
8. Otherwise: one of the two current bond-tier reactions.

The selector reads current map section/type, active weather, map music, native time of day and the existing travel count. It never reads raw unseeded Johto story variables or invents past campaign participation. Context music can affect room reactions. Authored scene hiding, NPC escort precedence and existing Surf/bike/geometry safety remain. New animations use existing stationary turns, in-place hops and emotes; no actors, palettes, art, collision changes or campaign scenes are added.

## Exact identity and source

| Item | Binding |
| --- | --- |
| Candidate | `johto-full-36p` |
| ROM SHA-256 | `1ce4bcabb3225433b2421044dc00bb09ef33e89543e6664167dd99319b640901` |
| CRC32 | `08b8300a` |
| Source fingerprint | `be7b2722169d820dbab5987e49e7f72d0dba3721c1e507dd7b7690003f500e8d` |
| Upstream | `167aa6d537b109bb229c231ddce4616974c4da71` |
| [ROM](../_local/artifacts/johto-full-36p-firered/pokefirered.gba) | 33,554,432 bytes |
| [Build manifest](../_local/artifacts/johto-full-36p-firered/manifest.json) | Actual make and wrapper exited 0 |
| [Complete source freeze](../_local/evidence/pikachu-reactions-01/source-freeze-36p-01/manifest.json) | SHA `76530257aa72079b93d41447f31b3380fed43cd8ff053c994386509c08be0144` |
| [Complete patch](../_local/evidence/pikachu-reactions-01/source-freeze-36p-01/complete-source.patch) | SHA `f5cbb11dcd8433bdf3c7d9c424c427760fe8d85c059a0308af89c05cf0349238`; pristine apply-check 0 |

Four files change from 36O: `src/event_object_movement.c` (read-only selector and transient `VAR_RESULT` bridge), `include/event_object_movement.h` (declarations), `include/constants/event_object_movement.h` (transient selector IDs/thresholds), and `data/scripts/follower.inc` (PC02 dispatch, stationary animation and exact dialogue). There are no new persistent event IDs. `PIKACHU_REACTION_*` values 0–14 are dialogue selectors, not save allocations.

The private build wrapper [build-36p.py](../_local/evidence/pikachu-reactions-01/build-36p.py) records the exact FireRed `-j2`, pinned 14.2.rel1 toolchain, `O_LEVEL=s`, `RELEASE=0`, `LTO=0` build. This is an incremental isolated APFS clone of frozen 36O, not a separately executed clean repeat. Logs, actual exits and configuration fingerprints remain local. Reconstruct a separate target tree from the pinned source, complete patch, provenance-pinned private assets and recorded configuration; do not apply the cumulative patch on top of an already patched tree.

## Resources and persistence

| Resource | 36O | 36P |
| --- | ---: | ---: |
| ROM headroom | 856,876 | 855,436 |
| EWRAM headroom | 7,100 | 7,100 |
| IWRAM headroom | 6,848 | 6,848 |

The package uses **1,440 ROM bytes**, no additional static RAM, no new save fields or reserve. All 397 actual ARM/save-layout facts and 40 existing artwork pins match. All 36,861 source inputs were catalogued; the exact four-file delta is frozen. Native6/FRJS1/content3/layout1, encrypted game statistics, sector/checksum coordination, existing collection and protected 256-byte reserve are preserved. The four-byte main-save margin and roamer fidelity limitation remain open.

## Executed checks and limits

Actual extracted-C ASan/UBSan checks pass 378 cases and 2,647 assertions: all 15 selectors, threshold boundaries, scenario precedence, native outdoor classification, RNG ownership and nonmutation. Six complete ARM C compilations also preserve the original LeafGreen/HnS/Emerald machine-code sections; only explicitly accounted assertion line-number strings differ in full objects. Their follower scripts preprocess byte-identically. No whole other-target ROM build or playthrough is claimed. Script route/dependency checks are separate from native gameplay. [Policy evidence](../_local/evidence/pikachu-reactions-01/host-tests/report.json).

Native mGBA movement, stationary animation, exact dialogue and return-to-field checks executed on isolated B-owned checkpoints. Observed outcomes are Shy, Curious, Happy, Affectionate, Trusting, Scared, Reassured, Cautious, Relaxed and Eager. The same Pokémon Tower location changes from frightened at 1,001 steps to reassured at 20,001; quiet-house captures distinguish bond tiers. A current native image shows the actual heart emote. These prerequisites were staged, not reached by a natural campaign playthrough. Original party, boxed Pikachu, storage, inventory, Dex, names, options, flags/variables, regional state and reserve remain intact across the sampled interactions. Talking without walking leaves the saved step count unchanged.

Playful, Startled, Brave, Rain and Sleepy are implemented and pass actual-C selection checks, but their native gameplay/captures remain **NOT RUN**. Burned Tower itself, actual transport/NPC escort/battle return, fresh opening, cross-region traversal, crowded-scene peaks, Delta/iPhone, audio listening and full natural campaigns were not replayed for this pass. Unchanged previous evidence retains its original build label.

**Same-ROM normal Save → full quit → fresh Continue PASSED — executed.** Save17 committed generation 5→6, the entire mGBA process exited, and a fresh process loaded the exact private save. [Strict comparison](../_local/evidence/pikachu-reactions-01/native-execution-36p-01/offline-save17-cold18-preservation-01.json) passes all three boundaries × 28 preservation domains without semantic exceptions. All 64 decoded native statistics match after the settled save and cold Continue; the only pre-Save statistic change is the native saved-game counter 5→6. Travel stays at 20,001 steps, preserving the devoted tier. After Continue, one separately disclosed ordinary step increased travel to 20,002; facing Pikachu and interacting then displayed the Affectionate response. No second save was made. Control returned normally and mGBA is fully closed.

All party/PC Pokémon, inventory, money/coins, Pokédex, trainer/rival names, native options, campaign flags/variables, regional state and protected reserve persist. Native encrypted-data rekeying, map-view cache initialization and play-clock changes are distinguished from semantic state; the exact raw-difference appendix is retained. The save SHA is `ec4d5abd1cf6b4b18f4940b24a6e1d58b6c9e00fd36bce4c32f0e6b566987fe6`. This qualifies the disclosed fixture and build, not arbitrary-save compatibility or a natural campaign.

The native diagnostic runner initially used an overly strict field-message-mode predicate: script-owned text was visibly displayed with that native mode equal to zero. The original diagnostic stop is preserved, its actual Happy screenshot remains valid, and V2 uses verified script/control state plus separate visual/text audit. Low host disk space also interrupted two UI calls; preserved logs, a bounded disposable-object cleanup and byte-identical APFS copy-on-write deduplication record the recovery. No source, final artifact, historical evidence or save was discarded.

## Owner review

[Open the offline HTML review room](../_local/owner-review/index.html). Markdown remains the source record. Current and historical captures retain their original build labels. Private screenshots, source, ROMs, fixtures and native saves remain local and ignored. No personal save, other workstream, service, networking, commit, remote write or publication is included.
