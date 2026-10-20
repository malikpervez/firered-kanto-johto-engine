# FireRed Kanto → Johto engine — private 37C test snapshot

One trainer and collection through FireRed’s Kanto/Sevii, then HnS Johto with independent regional progression. This repository is the owner-authorized **private cloud review/testing handoff**, not a game release.

## Start here

- Read [AGENTS.md](AGENTS.md), [CLOUD_TESTING.md](CLOUD_TESTING.md), and the [current Claude assignment](CLAUDE.md).
- [Start-to-finish story guide](project/docs/campaign-story-and-progression-guide.md): 19 chapters; original dialogue remains in the actual scripts under `engine/data/`.
- [Exact source/build reference](provenance/local-build-reference.json) and [raw input manifest](provenance/engine-inputs.json).
- [Cumulative source patch against pinned upstream](provenance/complete-upstream-to-37c.patch) and [940 changed/added file records](provenance/changed-files.json).
- [Attribution](ATTRIBUTION.md) and [export exclusions](provenance/export-policy.json).

`engine/` contains the current **37C** game source and integrated runtime graphics, byte-checked against the frozen local candidate. Its upstream base is PokemonHnS-Development/pokehns-expansion commit **167aa6d537b109bb229c231ddce4616974c4da71**. It does not use the historical 35A review prompt as its baseline.

The complete patch is preserved as raw Git patch bytes, including inherited legacy text encodings and binary asset hunks. Do not recode it as UTF-8 to inspect or apply it.

The original 37C local ROM SHA-256 is `14ffbb4739e873eb259ce584e879c081a78ee65cdef59103f4a3e3a110265023`. That artifact is **not uploaded**. The local linker measured **781,436 ROM bytes free**, EWRAM used 255,044 and IWRAM used 25,920. Native SaveBlock1 is 15,868 / 15,872 bytes; the protected 256-byte reserve and FireRed roamer fidelity issue remain unchanged/open. Reproduce and report your own cloud results; a source hash or compilation does not certify gameplay.

## Source and evidence boundaries

Included: current source, integrated build-input sprites/palettes and encoded title/player data, complete cumulative patch, pinned input/configuration records, existing battle-test sources, 397-fact ARM probes, project scripts and current/historical story/engineering documentation.

Excluded: full ROM/BIOS outputs, the three upstream embedded multiboot `.gba` inputs, emulator executables, personal/test saves, save states, private screenshots/recordings, raw reference photographs, unused/rejected asset packages, credentials, old source checkouts, generated local HTML/evidence, installed tools and every GitHub workflow. The three original embedded inputs are restored explicitly with the setup script; they stay ignored and are never committed. The full source-input manifest records the exclusions.

The polished HTML review, its 512 private images and browser-local feedback remain on the owner’s computer. `project/scripts/review_hub/shell.html` is a **template**, not a working generated review. Cloud reviewers should use the Markdown and real engine scripts. `[LOCAL_WORKSPACE]` references in historical records identify intentionally excluded local evidence; missing screenshots are not new failed gameplay tests.

## Current story status

Implemented source includes Nao/Ho-Oh; Mewtwo/Mew; Black Tide’s separate Rocket-created bird replicas and Shadow Lugia; Pikachu opening and optional Kanto starters; Blue/Silver’s independent arcs; Jessie/James/Meowth and the optional Celadon double battle; FG01–FG22 and 14 friend opponents; Pikachu’s permanent presentation companion, 15 reaction selectors and 37C bicycle riding; Trail/title preview assets. Current scripts and actual source gates are authoritative.

The October 19 Friends dialogue/art expansion and **FG-A–FG-G are proposed, not implemented in 37C**. Friends still use 22 scene receipts and required-zero bits 0x956–0x95F. No third region or additional legendary chapter is implied. Final visual acceptance and the reports’ unexecuted branches remain separate.

GitHub Actions/CI/deployment are deliberately absent and disabled. Builds/tests are manual, with logs and generated binaries under ignored `_local/`. Workstreams A/C, the separate native port, services and networking are outside this repository’s scope.
