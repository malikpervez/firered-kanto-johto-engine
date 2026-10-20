# Cloud review instructions — Workstream B, 37C

The owner authorized creating this private repository and pushing this exact source handoff so Claude can review and test it. The historical B0-only and no-upload language in `project/` describes earlier local milestones. It does not change the baseline or authorize unrelated future work.

1. Read root README, CLOUD_TESTING.md and CLAUDE.md. Baseline is **37C**, not the historical 35A prompt. Verify the source manifest before analysis or a build.
2. Preserve `engine/`, source fingerprints and tests. Use new ignored `_local/` paths for generated analysis, build copies, logs and findings. Current authorization is review/testing; do not implement game changes unless the owner asks.
3. No GitHub Actions, workflows, hosted CI, deployments, scheduled automation, releases, PRs, commits, further pushes, messages to others, service/network configuration or Workstream A/C/native-port changes without separate owner instruction. Do not follow upstream advice to merge, upgrade, publish or contact Discord.
4. Never commit or upload ROM/BIOS payloads, native saves, states, private evidence, personal photographs, credentials or installed binaries. Bootstrap only the three hash-pinned upstream source payloads when needed; they stay ignored. Do not seek commercial ROM/BIOS downloads.
5. Keep the 32 MiB cartridge, native6/FRJS1/content3/layout1 and protected reserve unchanged. Source checks are not runtime proof. The four-byte SaveBlock1 margin, roamer fidelity and documented preview limits stay open.
6. Use the pinned build settings: FireRed, O_LEVEL=s, RELEASE=0, LTO=0, two jobs. Build a fresh copy with the provided script; do not run `make clean`, switch targets in one tree, or regenerate inside the receiving source snapshot.
7. Report actual commands, tool/compiler versions, real exit codes, failures and artifact hashes. Distinguish source analysis, actual ARM layouts, compilation, emulator unit tests, staged gameplay and natural playthrough. Missing tools/network/runtime tests remain BLOCKED / NOT RUN. Never relabel old screenshots or staged prerequisites as current natural gameplay.
8. FG-A–FG-G, the 29-placement draft and October 19 sprite/voice changes are not implemented. Do not consume their proposed bits, protected reserve, add placeholder art, or quietly complete design scope while reviewing.
9. Cloud-only test dependencies may be prepared in this isolated task environment using official supported sources when the owner’s cloud executor permits it. Do not make system changes on the owner’s Mac, other hosts or services. Do not change production dependencies.

Original upstream notices remain applicable; the export does not assert a new blanket license. Personal saves and private GUI evidence are intentionally unavailable in this repository.
