# Candidate23 — owner-reported Oak Lab defects

**Current — repaired candidate25b.** Oak’s Lab’s missing tiles and blocked exit are fixed. Fresh opening/starter/rival victory/exit and two normal-save/full-quit/cold checks executed; the final25b lab save also reloads and exits correctly. GO for bounded fresh-game local evaluation; HOLD for release/full-campaign completion. [Audit, exact tests and remaining limits]([LOCAL_WORKSPACE]/docs/candidate23-repair-and-tooling-audit.md). Previous candidate23 completion/GO remains withdrawn.

Owner-authorized review and repair are complete within the reported scope. Candidate23 symptoms were independently reproduced; the corrected build passed the focused opening/rival/exit/save/cold checks. [Full repair report]([LOCAL_WORKSPACE]/docs/candidate23-repair-and-tooling-audit.md).

## Original report and review request — historical

Current disposition: **HOLD — owner-reported blocking defects; independent reproduction pending.** The previous completion/GO recommendation is withdrawn pending diagnosis and repair. This supersedes the completion language in the historical source/build closeout; it does not erase the checks that actually executed.

The owner reports: “Oaks lab has missing blocks, you cant even leave after beating gary.” The context is the candidate23 play instructions. Verify the actual owner ROM/process identity before attributing a reproduced failure to an exact artifact. Do not overwrite the owner's save or take over an active game without coordinating control.

Two reported symptoms require independent investigation:

1. Missing map blocks/tiles in Oak's Lab.
2. Inability to leave the lab after winning the first rival battle.

These are owner observations, not agent-executed reproductions. Their exact visual extent, movement failure, script state and root causes remain unconfirmed. Do not assume the two symptoms share a cause or that the lab is the only affected map.

The previous candidate23 native check continued an isolated candidate21 Pallet save, entered the lab through Oak's opening, selected Bulbasaur, completed the rival's starter-selection scene, and saved/cold-reloaded at lab position7,4. **It did not execute the rival battle or the lab exit, and did not start a fresh candidate23 New Game.** Its PASS supports only those executed actions. The prior screenshot/visual review did not establish complete, correct lab rendering. Compilation, emitted-byte equality, source coverage and save persistence cannot establish correct map rendering or traversability.

Preserve candidate23 and its logs, source freeze, complete patch, verifier failures/corrections, native snapshots/screenshots and prior recommendation as historical evidence. Review the hybrid-map, tile/attribute decoding, dynamic script-write, layout/default binding and alias mechanisms before declaring the issue local to the lab. No implementation changes are authorized by this report itself; the current requested deliverable is an independent Astra review prompt.

Boundaries remain unchanged: no Workstream A/C repository/service/configuration changes, no save-format or capacity changes, no remote writes/CI/deployment/NAS/network changes, and no personal-save modification. Upstream sources, ROMs, saves and private evidence stay ignored under `_local/`.
