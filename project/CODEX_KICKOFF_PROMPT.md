> Historical local-workspace record. Root `AGENTS.md`, `CLAUDE.md` and `CLOUD_TESTING.md` govern this current 37C cloud handoff. Local evidence links are not included.

# Codex kickoff: Project FireRed Online — Workstream B

Read `AGENTS.md`, `WORKSTREAM_B_REQUIREMENTS.md`, and `B0_ACCEPTANCE_CHECKLIST.md` completely before working. Treat them as the requirements for this session, subject to higher-priority instructions and explicit owner decisions.

You are responsible for a **new, independent game-engine workstream**. My existing multiplayer/Discord workstream is near the end of Phase 1 and must continue unchanged. Do not edit its repository, stop its services, change its dependencies, or rewrite its plan.

## Objective

Evaluate this source candidate:

```text
https://github.com/PokemonHnS-Development/pokehns-expansion
```

The long-term goal is one game containing FireRed's Kanto and Sevii Islands followed by Heart & Soul's Johto, with one trainer and separate regional progression. The later online platform targets 25 simultaneous players, but multiplayer is not this session's assignment.

**Execute B0 only:** establish reproducible local builds, attempt the existing FireRed and Heart & Soul targets separately, and verify them in desktop mGBA before we consider combining regions or integrating with Discord.

## Start here

1. Inspect the current folder, Git state, host OS, shell, available tools and disk space. This must be a separate Workstream B workspace. Stop if it is the active multiplayer repository. Windows is the intended baseline, but do not assume WSL or even Windows is present; record the actual environment.
2. Read the candidate's own build/install instructions, Makefile, relevant configuration, credits and reuse notices. Confirm the actual target names and record a full immutable commit SHA. A Makefile entry is not proof that a target builds or plays correctly.
3. Set up a small control repository for our docs, manual build scripts, provenance and reviewed patches. Keep the upstream clone, build outputs, native saves and private evidence under ignored `_local/` paths. Preserve upstream Git history; do not copy the entire source tree into the tracked control project.
4. Build FireRed and HnS from separate clean target trees. Record real commands, logs, exit codes, compiler versions, configuration and SHA-256 artifact hashes. Preserve unmodified baseline results before any proposed narrow repair.
5. Run the B0 acceptance checklist in mGBA. Verify the intended opening, starter acquisition, early battles/transitions, ordinary in-game saves, full exit and cold reload. Keep targets and saves isolated. Do not use save states or debug skips as proof of progression.
6. Produce the required reports, reproducible owner instructions and a go/hold/no-go recommendation. If graphical testing is unavailable, clearly mark it `NEEDS OWNER TEST` and give me the exact steps and output paths. Compilation alone does not pass the gameplay gate.

## Non-negotiable boundaries

- No GitHub Actions, workflows, hosted CI/CD, automatic deployments or background repository automation. Do not copy inherited upstream workflows into our tracked project.
- No GitHub repository creation, fork, push, pull request, release or other remote write without my explicit approval. Do not modify my existing repository.
- No ROMs, BIOS, personal saves, save states, protected game assets, private screenshots or credentials committed to Git. Keep attribution and review source/asset reuse restrictions.
- No NAS, Docker hosting, router, firewall, Tailscale, public tunnel or Discord changes. Ask before privileged/system-wide installations.
- No region merge, major engine upgrade, new Pokémon expansion, multiplayer bridge, save-format redesign or placeholder gameplay to make tests pass during B0.
- Do not silently delete original FireRed features. Record missing or changed behavior and escalate substantive repairs.
- Never claim an unrun test passed. Distinguish source findings, build success, boot success, gameplay, saving and whole-campaign completion.

Work independently on safe, reversible B0 tasks. Ask only for genuinely missing permissions, required inputs, environment blockers or product decisions. Do not spend the whole session restating a plan; attempt the real baseline builds when prerequisites allow.

End with: source commit; environment; per-target build and test results; local artifact paths/hashes; changes made; untested items; blockers; and the next decision needed. **Stop at the B0 review gate and wait for approval before B1 or any merge work.**
