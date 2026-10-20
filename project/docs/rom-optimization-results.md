# ROM capacity recovery — local preview35a

An additional lossless storage pass is implemented in isolated35a. It shares exact copies of battle environment graphics, item icons/palettes, door images and one complete sound sample. Original content, gameplay tables and saved structures remain unchanged.

| Build | Linked ROM used | Free ROM | Additional recovery |
|---|---:|---:|---:|
| Qualified34b |32,577,748 B|976,684 B|—|
|35a |32,536,260 B|**1,018,172 B**|**41,488 B**|

Total recovery versus33b's204-byte margin is1,017,968bytes. The configured cartridge and padded file remain32MiB. Four-byteSaveBlock1headroom remains a separate unchanged limit.

35a ROM SHA256 `281906d23f03f4f5eb590b967e33b5badeff3d1c27502337a067988008bf4a49`, CRC32 `e5f56ba5`. [Exactbuildmanifest]([LOCAL_WORKSPACE]/_local/artifacts/johto-full-35a-firered/manifest.json), [ownerreport/nativeimages]([LOCAL_WORKSPACE]/_local/evidence/rom-optimization-02/delivery-35a-01/REPORT.md), [deliverymanifest]([LOCAL_WORKSPACE]/_local/evidence/rom-optimization-02/delivery-35a-01/manifest.json), [complete838-recordsourcefreeze]([LOCAL_WORKSPACE]/_local/evidence/rom-optimization-02/source-freeze-35a/manifest.json).

Executed staticchecks:219originalgraphics/palette arrays exact;155aliases share64groups;628,592bytes of consumer/gameplaytable meanings preserved;1,563soundblobs and3,312samplefiles exact; soundmetadata/6,265relocations preserved;397actualARMsave/layoutfacts andall32configfiles unchanged. EWRAM254,972B/IWRAM25,920B, allRAMsymbols andheap unchanged. Other-targetgraphics preprocessorand soundobject comparisons pass; other-target fullbuild/nativechecksNOTRUN.

Executed35a desktopmGBA: normalContinue of unmodifiedB-owned34bSave10, party/Bag/HM03icon, Celadon/Restaurantroundtrip, one normalSave10to11/fullquit/freshContinue. Initial22/22, strict81/81 andfullprogress23/23 pass. This is stagedcheckpoint evaluation, not a naturalcampaignreplay. Fullcampaigns, new35abattles/audio-listening/allbackgrounds-icons-doors individually/browser/stress wereNOTRUN. Frozen34b andits evidence remain preserved below.

B-to-C: sourceart/IDs/palettes/frames unchanged; unchanged artwork/tests need no restart. Exactduplicate rawdata may now share addresses andROMaddresses relocate; bind tools to35aELF/hash. Save/RAMaddresses unchanged. No otherworkstream/task/service/network/NAS/commit/push/publication/CI/automation change. GO boundedlocalpreview; playerreleaseHOLD, roamerfidelity/artacceptance/Goldenrodroofissues remain open.

## Preserved34b qualification and prior recovery

The owner authorized identical surfing-image deduplication followed by a compiler size trial, preserving gameplay and native saves. Both steps are implemented locally. The selected bounded preview is **johto-full-34b**; frozen33b remains preserved. This does not grant player-release approval or new feature scope.

| Build | Linked ROM used | Free ROM | Recovery versus preceding build |
|---|---:|---:|---:|
|33b baseline|33,554,228 B|204 B|—|
|34a: surfing image aliases, O2|33,124,148 B|430,284 B|430,080 B|
|34b: same source, Os|32,577,748 B|976,684 B|546,400 B|

Total recovery: **976,480 bytes**. The configured cartridge and padded ROM file remain32MiB.

Exact34b ROM SHA256: `911908a97e982dd8f286a95e703beee5df90b517552a19412bc8a1139e9bf781`, CRC32 `0ecf9fc9`.

- [Local ROM]([LOCAL_WORKSPACE]/_local/artifacts/johto-full-34b-firered/pokefirered.gba).
- [Build/configuration manifest]([LOCAL_WORKSPACE]/_local/artifacts/johto-full-34b-firered/manifest.json).
- [Owner report and native images]([LOCAL_WORKSPACE]/_local/evidence/rom-optimization-01/delivery-34b-01/REPORT.md).
- [Delivery manifest]([LOCAL_WORKSPACE]/_local/evidence/rom-optimization-01/delivery-34b-01/manifest.json).
- [835-record complete source freeze]([LOCAL_WORKSPACE]/_local/evidence/rom-optimization-01/source-freeze-34b/manifest.json).
- [Root native execution ledger]([LOCAL_WORKSPACE]/_local/evidence/rom-optimization-01/native-execution-01/ledger-final-01.json).

The only authored source delta versus33b is `src/data/object_events/surfable/surfable_pokemon_graphics.h`:61FIRERED-only immutable aliases retain both normal/shiny symbols and separate palettes. The78different pairs remain separate. No artwork, species, maps, scripts, gameplay tables, saves or content were removed or replaced. The complete34a/34b patches are identical;34b uses `O_LEVEL=s RELEASE=0 LTO=0` on the build command, preserving native per-objectO2 exceptions. Future34b builds must retain those explicit flags; changing compiler flags requires rebuilding target objects.

Independent checks confirm397actualARM save/registry/layout facts unchanged, exact assembly-owned map/script/sound payloads and relocations, and preserved trainer/species/move/item/surf table meanings. EWRAM254,972 B andIWRAM25,920 B use72fewer bytes overall; the change is fully reconciled to alignment and compiler emission, with no removed or resized prior RAM symbol.

Native34b checks executed on isolated B-owned copies: normal/shiny Surf entry, all six body/overlay animation frames, palette distinction, right mirroring, normal dismount, existing-save load, party/Bag menus, Celadon/restaurant map roundtrip, and one ordinary Save/full quit/fresh Continue cycle. Strict comparisons passed80/80; full flag/variable/party/location comparisons passed23/23; initial unmodified33bSave9 load passed29/29. Surf saves are explicitly rendering diagnostics with inheritedLapras stats/nickname; the save/cold case uses a separate unmodified real33bSave9 copy. These are bounded checkpoint checks, not a natural campaign playthrough.

Failed auxiliary configuration/generation attempts and harness limitations are retained in the owner report. Correct target regeneration restored all4,511 map outputs/aggregates/stamps exactly to33b before the final build. No authored map repair or error suppression was used.

## B-to-C coordination

Art source bytes, species identities, palettes, frame ordering and picture IDs remain unchanged. C's unchanged artwork and inventory checks need no restart. Identical surfing tile arrays now share ROM storage; C should not assume distinct addresses for normal/shiny tile data. Compiler optimization relocates ROM code/data and some RAM globals, so any address-bound harness must derive symbols from34b's ELF and use its exact ROM hash. Save structure offsets remain unchanged. Historical images retain their original build labels; current34b images are available in the private owner report. No other task was messaged.

B retains save/campaign/runtime palette/time/budget/integration ownership. C retains isolated art packages and visual validation. The four-byteSaveBlock1 margin, FireRed roamer fidelity defect, prior art acceptance/Goldenrod roof occlusion and player-release HOLD remain open. Full campaigns, all61species individually native, new34bcombat outcomes, browser compatibility and extended audio/performance stress were not rerun.

All ROMs, patches containing game assets, source checkouts, test saves and private images remain local/ignored. No other workstream, personal save, service/network/NAS, commit, push, publication, PR, CI or automation change was made.
