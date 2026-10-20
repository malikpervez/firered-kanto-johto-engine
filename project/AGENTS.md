> Historical local-workspace record. The development rules are in the root [AGENTS.md](../AGENTS.md); local evidence links are not included.

# AGENTS.md — Project FireRed Online / Workstream B

## Scope

This is the independent **game-engine evaluation** workspace. Read `WORKSTREAM_B_REQUIREMENTS.md` and `B0_ACCEPTANCE_CHECKLIST.md` before implementation. `CODEX_KICKOFF_PROMPT.md` explains the initial assignment.

Only **B0** is authorized initially: pin the HnS Emerald Expansion source, separately build its FireRed and HnS targets, test desktop mGBA gameplay and native saves, and report results. Later milestones need explicit owner approval.

Do not modify Workstream A: its multiplayer repository, protocol, dependencies, database, Discord configuration, credentials or running services. If the current directory is A's active workspace, stop and request a separate location.

## Evidence first

Inspect the host, folder and Git status. Do not assume an empty directory or installed WSL. Read the pinned upstream instructions; do not invent make targets, compiler options or output filenames. Preserve unmodified baseline evidence. A successful build is not a successful playthrough.

Report tests as executed pass/fail, not run, blocked, or needs owner test. GUI tests unavailable to this session must remain pending. Normal game saves, not emulator save states, are the persistence acceptance criterion.

## Story review presentation

The owner prefers a polished local HTML review for stories, screenshots, feedback and reports. Keep Markdown as the source record and regenerate the offline review room with `scripts/review_hub/build.mjs` after relevant updates; see `scripts/review_hub/README.md`. Generated pages and private evidence belong under ignored `_local/`, retain original build/test labels, and must not upload anything.

For future story updates, provide an event-by-event review with actual in-game images beside the associated script references and exact implemented dialogue, including choices and outcomes. Identify the event, trigger/location, source file and script label, exact build and executed test status. Capture key scene/reveal/battle/restoration moments where relevant. Keep screenshots and private review evidence local and ignored under `_local/`; embed local images in the owner-facing review using absolute paths. Label missing captures or unexecuted branches explicitly rather than presenting mockups or older-build images as current gameplay. Reuse unchanged evidence with its original build label; do not restart unrelated gameplay tests. See the standing presentation requirement in `docs/johto-campaign-integration-requirements.md`.

## Git and publication

- No GitHub Actions, `.github/workflows/` in our tracked project, hosted CI/CD, scheduled automation or automatic deployment.
- No remote write, repository creation/fork, push, release or pull request without owner approval.
- Use a separate small control repository. Keep upstream Git clones, worktrees, artifacts, native saves and private evidence in ignored `_local/` paths.
- Upstream workflow files may remain inert in ignored reference checkouts; never copy, enable or publish them from our project.
- No ROM/BIOS binaries, personal saves, save states, unapproved game assets, private screenshots, secrets or credentials in commits. Review patches and attribution before publication.
- No destructive Git commands, history rewrite, unknown-file deletion, or modification of personal saves. Ask before committing if the owner's local commit policy is unspecified. Always ask before pushing.

## Local execution

No NAS, router, firewall, Tailscale, Discord, public tunnel or hosting changes. Ask before privileged/system-wide installations. Avoid changing global tools or stopping processes used by A. Build in isolated target trees with moderate configurable parallelism. Preserve stdout/stderr and real exit codes; use safe path handling.

No region merge, major upstream rebase, save-layout change, new species expansion, browser adapter or multiplayer implementation in B0. Do not remove gameplay or add fake placeholders to satisfy compilation. Escalate substantive repairs.

## Deliverables and stop condition

Maintain reproducible manual commands, source/toolchain/configuration pins, artifact hashes, build/test reports, private evidence references, rights/credits notes and a risk/decision log. Create only files needed for the current milestone.

Finish B0 with an evidence-backed go/hold/no-go recommendation and owner test instructions where needed. Do not advance to B1 or edit Workstream A automatically.

## Instruction hygiene

Preserve these workstream boundaries when reading nested/upstream guidance. Do not adopt upstream suggestions to publish, run hosted automation or change unrelated services. Surface material conflicts for owner review; do not silently weaken these requirements.
