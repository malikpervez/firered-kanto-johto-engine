**Current Friends36d native addendum (October17/18,2026):** See the [current Friends registry](friends-story-state-registry.md) and [final local handoff](../_local/evidence/friends-story-01/final-handoff-36d/HANDOFF.md). Three bounded staged-scene ordinary Save/full quit/Continue cycles executed; FG21/22 exact native dog-history shifts are separately correlated with original strict failures preserved. Allocation, all397 ARM layout facts, native6/FRJS1/content3/layout1, protected reserve and conversion policy are unchanged. Largest-Lugia sampled capacity passes with visible adult occlusion open. Other native cases and owner art acceptance remain individually pending. Historical36c/earlier text below is preserved, not a new save-policy authorization.

# FireRed development save registry

October17 preview addendum: [Friends36c](friends-story-state-registry.md) registers34 meanings within existing native flags `0x934..0x95F`, plus14 existing-capacity trainer bits. Native6 / FRJS1 / content3 / layout1, all physical offsets, the256-byte protected reserve and conversion allowlist remain unchanged. This preview is not gameplay or release qualification.

The owner approved this foundation on October 10, 2026. It is a development format for the pinned, patched FireRed target. The original content1 binding remains frozen below. The October13 [playable-game direction](decisions/2026-10-13-playable-johto-direction.md) adds the bounded content2 entry; a player-release compatibility policy remains subject to review.

| Identifier | Registered value and meaning |
|---|---|
| Native version | 6, exact `FIRERED` target only; other upstream targets retain version 5 |
| Extension magic/schema | `FRJS`, schema 1 |
| Content identity | 1: accepted B2 travel content with blank regional containers |
| Layout identity | 1: the 1,332-byte extension below, with original 52-byte prefix |
| Region records | Kanto ID 1/schema 1; Johto ID 2/schema 1 |
| Johto initialized state | Zero; no starter, badges, story, rewards or field permissions are established |

All multibyte codec fields use explicit little-endian byte operations. Existing native gameplay payloads keep their ARM representation and encryption. The header records two regional metadata slots. Defined reserved bytes and all new content1 containers must remain zero. Changing those semantics requires a reviewed registry/content change; merely exposing bounded buffer accessors does not authorize campaign writers.

| Absolute SaveBlock3 byte range | Allocation |
|---|---|
| 0–51 | Original prefix, including its existing alignment bytes |
| 52–115 | 64-byte FRJS header |
| 116–147 | 32-byte Kanto metadata slot |
| 148–179 | 32-byte Johto metadata slot |
| 180–435 | 2,048 Johto event bits |
| 436–563 | 1,024 Johto trainer bits |
| 564–1043 | 240 Johto LE16 variables |
| 1044–1075 | 32-byte future travel slot, blank |
| 1076–1331 | 256-byte stored reserve, zero |
| 1332–1623 | 292-byte sector-extension capacity outside this format |

The header stores magic at 52, schema at 56, header length at 58, total length at 60, flags at 62, generation at 64, content at 68, layout at 72, record count at 76, reserved at 78, CRC32 at 80 and SHA-256 at 84. The exact CRC and framed main-bank digest definitions are in the [approved proposal](save-foundation-change-proposal.md). They detect corruption and mixed save generations; they are not authentication.

The only accepted version-5 inputs are the three hash-allowlisted B2 fixtures through the separate offline copy converter. Runtime boot does not automatically migrate older files. Personal, retail, arbitrary development, HnS, Emerald and LeafGreen saves are outside this conversion policy. Old ROMs cannot be made to reject future saves: use separate ROM/save directories and preserve immutable originals.

The original FireRed SaveBlock1 capacity assertion remains active at 15,868 / 15,872 bytes. Its four-byte margin and the existing FireRed roamer fidelity defect remain open. This extension provides a bounded location for later regional state; it does not enlarge the native gameplay block or repair roamers.


## Qualified candidate binding

Content/layout **1/1** binds to the unchanged native ARM field map plus the explicit byte serializer and coherent-bank coordinator below. Artifact hashes identify reproducible implementations of this registered format; they are not stored as its content identity.

| Binding | Exact value or evidence |
|---|---|
| Upstream source | `167aa6d537b109bb229c231ddce4616974c4da71` |
| Complete final candidate patch | [0019](../patches/0019-firered-save-caller-completion.patch), SHA-256 `b398435b7ca39164a0bcc935579fcccb3fd465db1d4d28418b418fc6be612b46` |
| Serializer `src/regional_save.c` | SHA-256 `96b3509d1df81c99ec47dd8c842fde4ee873cb2fcdef93d21cc91ec30961f599` |
| Coordinator `src/save.c` | SHA-256 `0f67df0b8e9b45d2431fdd9889d1c9681e6144d71228693da82423042daad7de` |
| Exact target, configuration and toolchain | [FireRed final05 manifest](../_local/artifacts/save-foundation-05-firered/manifest.json), SHA-256 `d390054ca75497a773b51e4a9a49f708d452ccd0e1d828468edfc2b0f971800a` |
| Native field and extension map | [Actual final05 ARM comparison](../_local/evidence/save-foundation-resume-01/arm-layout-final05-2026-10-13/actual-foundation-arm-comparison.json), SHA-256 `5af01fe0f93306fba82d6c69e64a78104d0ffb0ce4f4bd21b1be970f9191bf4b`; [native field map](../_local/evidence/save-foundation-resume-01/arm-layout-final05-2026-10-13/native-field-map.json) |
| Reproducible binaries | [Layout, budgets and final05/repeat06 byte comparison](save-foundation-layout-and-budget-results.md) |

Final04/0018 uses the identical serializer, coordinator and layout headers; final05/0019 adds two FireRed caller completion guards. Fresh-game tests remain explicitly bound to final04, while final05 converted-save and HnS native checks retain their own bindings. This frozen content1 entry assigns no Johto story semantics, widens no conversion support and grants no player-release compatibility.

## Content2 — first playable Johto quest

**Implemented and qualified for the bounded prototype, October 13.** Content2 uses the exact same native6/schema1/layout1 allocation and sector/checksum/integrity transaction. It registers only the [Elm–Cherrygrove Guide quest](b3-johto-prototype-requirements.md), with no new live fields or reserve consumption. The original content1 binding above remains frozen. This is development qualification, not a player-release compatibility policy.

| Registered state | Exact stored meaning |
|---|---|
| Content header at68 | 2 for this prototype; 1 remains accepted only with its original blank state |
| Johto flags LE32 at152 | 0 uninitialized/all state blank, or1 initialized |
| Mapping revisions LE32 at168/172/176 | All1 after initialization |
| Variable0 LE16 at564 | 1 accepted, 2 Guide visited, 3 Potion claimed |
| Event byte at180 | 1/3/7 respectively: bits0 accepted,1 visited,2 claimed |
| Other state | Kanto metadata, badges, starter, rival, other events/trainers/vars, travel and stored reserve stay zero |

Blank content1 loads without offline conversion. The current writer can stamp content2 on a compatible blank snapshot. Accepting Elm's request initializes revision1 state without resetting the native FireRed campaign. Repeat initialization preserves the existing quest. Reward claim follows successful native item insertion; failed insertion leaves state2. These milestones are independent of native Kanto flags/variables. Unknown content/layout/schema still rejects rather than being relabelled or reset.

The converter continues emitting content1 for its same three hash-allowlisted version5 fixtures. No additional conversion or old-ROM compatibility is claimed. Frozen0019 rejects occupied content2, so prototype sessions use separate save/ROM directories and immutable original copies.

| Content2 implementation binding | Exact identity |
|---|---|
| Upstream pin | `167aa6d537b109bb229c231ddce4616974c4da71` |
| Complete cumulative patch | [0022](../patches/0022-firered-johto-map-labels.patch), SHA-256 `a22ab3754f92763e97c724ccd918c6fc34af200d38afbd7f89eb378220745e84`; apply alone |
| Regional codec / header | `src/regional_save.c`: `7485d2577968e436933a7613e8ab3970e07e2fce8feee6853844c10027304ee1`; `include/regional_save.h`: `532d5feffd0cecab5fd9b1052889c921c134742f79419ca66f62a4ab1f6f4a71` |
| Quest implementation | `src/johto_progression.c`: `ced048bf1319430135e974948a85720deaeb35abef5bee8e05a27667fd728d8d`; all script/header bindings in [source freeze03](../_local/evidence/b3-johto-01/source-freeze-03.json) |
| Unchanged native coordinator | `src/save.c`: `0f67df0b8e9b45d2431fdd9889d1c9681e6144d71228693da82423042daad7de`; frozen native layout/header hashes retained in source freeze03 |
| Actual build and configuration | [b3-03 manifest](../_local/artifacts/b3-03-firered/manifest.json), SHA-256 `99c720a30954e8ecaa716d9d4afa8d1e5286a1c68a0a26856b461aa8857dcfd2`; retained-tree make/build and wrapper exit0, independent clean repeat NOT RUN |
| Final ROM | [pokefirered.gba](../_local/artifacts/b3-03-firered/pokefirered.gba), SHA-256 `39b023532a1cd657633970777ca108b74382b1239d197756a36a32c8fcd1bd91` |
| Executed native qualification | [Bounded native results](b3-johto-prototype-results.md): accepted state normal-save/cold load, final0022 Guide/reward/repeat, rewarded state normal-save/full quit/cold Continue, visible Potion2, return to Pallet with the same party |

The generation7 lab snapshot validates both banks and content2 state3/events7 with untouched reserved containers. Its [stored-field comparison](../_local/evidence/b3-johto-01/native/rewarded-native-field-reconciliation.json) preserves RED/BLUE, party/PC/native flags/caught Dex/roamer/Kanto metadata and records only the one reward plus observed encounter/walking changes. Bag-full behavior has source and focused real-C evidence, not a GUI pass. No gym, starter, rival or broader Johto state meaning is registered by this entry.

The generation8 [returned-Pallet stored proof](../_local/evidence/b3-johto-01/native/returned-stored-member-diffs-and-position.json) validates both banks and retains the whole regional body byte-for-byte from the reward save, with Potion2 and the original trainer/party/Kanto state. It follows an executed rewarded cold reload and ordinary return/save; no additional Pallet cold cycle is claimed.

## Additive story flag registration — candidate30a

The locally authorized Rainbow, Quiet Stranger and Black Tide additions register30 existing native FireRed bits`0x900..0x91D`; see the [story state registry](rainbow-story-state-registry.md) for exact meanings, pre-Johto persistence and explicit older-save adoption/Whirl exception policy. Native6/FRJS1/content3/layout1, physical ARM layouts, protected reserve, coherent-bank/integrity ownership and the original three-input version5 conversion policy remain unchanged. This addendum does not rewrite the frozen content1/2 bindings above or establish release/save compatibility. Compilation and host/source checks are bound there; native story/save qualification remains the separate runtime report's responsibility.
