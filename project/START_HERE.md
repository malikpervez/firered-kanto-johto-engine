> Historical local-workspace record. Root `AGENTS.md`, `CLAUDE.md` and `CLOUD_TESTING.md` govern this current 37C cloud handoff. Local evidence links are not included.

# Start here — Project FireRed Online / Workstream B

**Owner review room:** [Open the local HTML review]([LOCAL_WORKSPACE]/_local/owner-review/index.html) for searchable stories, exact dialogue, screenshots, earlier feedback, decisions and reports. Original Markdown and evidence remain available. Feedback notes stay in the browser; use **Export notes** to keep a backup. [Regeneration instructions](scripts/review_hub/README.md).

**Current local feature — Pikachu bond and situation reactions, 36P, October 18, 2026.** Fifteen authored reactions respond to existing saved travel and surroundings. Native captures cover ten outcomes, including frightened/reassured Tower reactions, quiet-room/cave/Gym moods and affectionate heart animation. **855,436 ROM bytes remain**; this addition uses 1,440 bytes and adds no save fields or static RAM. [Exact build, results and pending branches](docs/pikachu-reactions-implementation-results.md); [dialogue, scripts and native images](_local/evidence/pikachu-reactions-01/owner-review-36p/REVIEW.md). All previous sources, builds and saves remain preserved.

**Preserved permanent Pikachu companion — 36O, October 18, 2026.** Pikachu follows and reacts after the first-Pokémon milestone, including when boxed or absent from the party. Actual owned Pokémon, native saves and protected reserve are unchanged. Focused native movement, interactions, Options, Center transition and normal Save/full quit/fresh Continue passed on isolated saves. **856,876 ROM bytes remain**; the feature costs 368 bytes relative to preserved 36M. [Exact build, tests and remaining limits](docs/pikachu-companion-implementation-results.md); [native images and exact dialogue](_local/evidence/pikachu-companion-01/owner-review-36o/REVIEW.md). No full-campaign or Delta qualification is claimed; all earlier evidence retains its original build label.

**Preserved local Friends review — 36M, October 18, 2026.** Lugia overlap is repaired and the seven friends use varied formations, speaker turns, reactions and authored movement. All 22 primary Friends events, 51 owned menu selections and 28 native battle win/loss branches have executed, with staged prerequisites disclosed. Farewell/reunion battle returns, cross-region retention, older-save adoption and ordinary Save/full quit/fresh Continue checks are recorded. [Exact build, scope, results and limits]([LOCAL_WORKSPACE]/docs/friends-story-presentation-and-native-results.md); [scripts, dialogue and native images]([LOCAL_WORKSPACE]/_local/evidence/friends-story-01/owner-review-36m/REVIEW.md).

ROM SHA-256 `8cda75eb36d9fb578b4771f678557fe838fa7ca132cf3c56800fd98f6db5650d`; **857,244 ROM bytes free**. Save layouts and the protected reserve are unchanged. This is ready for local owner review; portrait/presentation acceptance, Delta, full natural campaigns, the four-byte SaveBlock1 margin and roamer fidelity remain open. All earlier builds/saves/evidence are preserved; mGBA is fully closed. No workstream, service or publication boundary changed.

---

The following earlier status entries are historical and keep their original candidate-specific test scopes.

**Current story review — candidate30f, October 15, 2026.** Rainbow/Ho-Oh, Quiet Stranger/Mewtwo and Black Tide are implemented locally on preserved candidate29. Original birds, starter choices, regional campaign gates and native save layouts remain. [Exact implementation and test report]([LOCAL_WORKSPACE]/docs/rainbow-story-implementation-results.md).

Open [Play Story Review](<[LOCAL_WORKSPACE]/_local/saves/firered/rainbow30f-owner-fresh-01/Play Story Review.command>) and choose **New Game** for a separate fresh story review. The launcher is **PREPARED — NOT LAUNCHED**, with no copied save; existing owner saves and launchers are untouched. ROM SHA-256 `7cb09228e5b089c06ea33d6dbac116c501d3c17cf08e6da60536fe45bb3fc3d0`. mGBA is closed.

**Local review candidate, not a player release.** Executed results are artifact-bound and include disclosed staged checkpoints. Optional variants and natural Gold postgame/full-campaign qualification remain open. The report lists exact paths, state IDs, visuals, budgets and remaining tests. No other workstream, service, networking, commit or publication change is included.

## Preserved candidate29 campaign baseline

**Candidate29, natural Indigo-to-Johto travel with repaired trees.** Native mGBA tree views **PASSED**. The Champion’s construction barrier disappears, and the outdoor road, coastal stairs, Surf crossing, New Bark landing, Elm introduction without a second starter, aide’s Potion, normal Save 7, full quit and cold Continue **PASSED** in candidate29. Identity, party, Pokédex, Potion ×1, HM03, native Kanto clear/eight badges and regional state were preserved exactly across that save/reload. **Return travel PASSED to Indigo11,8 after the cold reload, without repeating the introduction or Potion gift. The emulator is fully closed.** [Journey results and exact scope]([LOCAL_WORKSPACE]/docs/natural-johto-journey-results.md).

Candidate28’s Hall-of-Fame event, Oak referral and normal Save 6 **PASSED** from a staged eight-badge/Champion-room fixture; this does not establish a naturally completed League.

Both owner29 launchers are **PREPARED — NOT LAUNCHED**: [Play Kanto and Johto](<[LOCAL_WORKSPACE]/_local/saves/firered/johto-full-29-owner-fresh-01/Play Kanto and Johto.command>) for **New Game**, or [Test Johto Journey](<[LOCAL_WORKSPACE]/_local/saves/firered/johto-full-29-owner-postchampion-01/Test Johto Journey.command>) for **Continue**. The latter is an explicitly **STAGED** Indigo11,8 checkpoint: RED/GARY, eight native Kanto badges and game-clear set, level 6 Bulbasaur, level 25 Lapras and HM03; it is not a natural League playthrough.

Candidate29 make and wrapper both exited 0; 22,204 ROM bytes remain. ROM SHA-256 `153db055de453e9a06cc0d5620108cb88dddfaed3fc299e44092d3198e329274`. Its 629 changed ROM bytes relative to candidate28 are confined to the three repaired map grids. [Build manifest]([LOCAL_WORKSPACE]/_local/artifacts/johto-full-29-firered/manifest.json).

Save layout and Workstream A remain unchanged. The four-byte main-save margin, roamer fidelity defect, Hall-of-Fame/special-sector atomicity and inherited graphics read spans remain open. Full campaigns, general save compatibility and player release remain unqualified. Earlier candidate23 completion/GO remains withdrawn.

## Historical candidate26

The following candidate26 record is preserved for its original scope; candidate29 above is current.

**Historical candidate26, Indigo’s western route to Johto.** Bounded desktop mGBA checks executed: the staged pre-Champion gate stays closed and returns the trainer; a staged Kanto Champion walks from Indigo through the pass into New Bark, meets Elm and receives the aide’s Potion, then saves normally, fully quits and cold-Continues. Repeat passage returns to Indigo without repeating the introduction. Independent preservation and repeat-entry reviews passed; the emulator is fully closed. [Travel results and exact scope]([LOCAL_WORKSPACE]/docs/indigo-west-pass-results.md). No full-campaign or player-release qualification is claimed.

To try the journey, open [Test Johto Journey](<[LOCAL_WORKSPACE]/_local/saves/firered/johto-full-26-owner-postchampion-01/Test Johto Journey.command>) and choose **Continue**. This is an explicitly **STAGED** checkpoint at Indigo11,8: eight native Kanto badges and game-clear set, trainer RED/rival GARY, level6 Bulbasaur; the party is not battle-ready. It does not represent a naturally completed League. For a separate fresh game, use [Play Kanto and Johto](<[LOCAL_WORKSPACE]/_local/saves/firered/johto-full-26-owner-fresh-01/Play Kanto and Johto.command>) and choose **New Game**; that fresh launcher is **PREPARED — NOT LAUNCHED**.

Candidate26 ROM SHA-256 `c705c297ca34e86ec45d061ae9291073dcbfc3e545a3290b6d85a7816068ff13`;23,196 ROM bytes remain. Actual make exited0, the original wrapper exited2, and separate qualification exited0 after proving its sole changed C object differs by the one generated debug map-count byte2→3. This is an incremental build from verified25b, with no clean26 repeat. [Qualified build manifest]([LOCAL_WORKSPACE]/_local/artifacts/johto-full-26-firered/manifest.qualified.json).

Candidate25b’s Lab repairs and their executed fresh opening/starter/rival victory/exit and normal-save/cold checks remain preserved in the [Preserved25b repair audit]([LOCAL_WORKSPACE]/docs/candidate23-repair-and-tooling-audit.md). Earlier candidate23 completion/GO remains withdrawn. Save format/layout and Workstream A remain unchanged; the four-byte main-save margin and roamer fidelity defect stay open.

## Original kickoff package — historical instructions

The following package started a **separate Codex game-engine session**. It does not replace the existing multiplayer handoff or change the current Workstream A repository. Its B0-only setup and initial checklist wording are historical; the dated current scope above governs this existing workspace.

## Use the package

Extract these files into a new folder for the game-engine project, separate from the active multiplayer folder. A suggested name is `firered-online-engine`.

Open that folder in the new Codex session. Read or paste the contents of `CODEX_KICKOFF_PROMPT.md` as the first message. The prompt instructs Codex to read the requirements and checklist and then perform **B0 only**.

Leave the current multiplayer session working under its own existing instructions. No prompt needs to be sent to that session merely to start B0.

## Included files

| File | Purpose |
|---|---|
| `CODEX_KICKOFF_PROMPT.md` | The paste-ready assignment for the new session |
| `WORKSTREAM_B_REQUIREMENTS.md` | Scope, safeguards, source policy, acceptance criteria and future gates |
| `AGENTS.md` | Concise repository instructions for Codex |
| `B0_ACCEPTANCE_CHECKLIST.md` | Build, native gameplay and ordinary save/reload checks |
| `START_HERE.md` | Setup and package explanation |

Codex supports project instructions through `AGENTS.md`; the kickoff also explicitly tells it to read the longer requirements. Official reference:

```text
https://developers.openai.com/codex/guides/agents-md
```

## First outcome to expect

Two independent baseline build results, ideally two games you can open in desktop mGBA: FireRed and Heart & Soul. You should receive exact local artifact paths, hashes, commands, tests and known issues. A combined Kanto–Johto ROM is **not** the first deliverable.

If Codex can compile but cannot operate a desktop emulator, it must give you the manual test steps and leave gameplay acceptance pending. A title screen or compiled ROM is not evidence of a complete adventure.

## GitHub and local files

No GitHub repository has been created, forked or modified by preparing this package. The default design is a small control repository with local upstream clones and outputs ignored. That makes it easier to keep inherited workflows and unreviewed game materials out of future pushes.

No GitHub Actions or CI/CD. No remote write without your approval. No NAS or Discord changes. No game ROMs, BIOS, personal saves, credentials or private evidence committed to Git.

## Gate sequence

**B0:** Separate native builds and emulator tests.  
**B1:** Approved compatibility/fidelity audit and early local browser test.  
**B2:** Approved one-ROM Pallet Town–Johto-slice round trip.  
**B3:** First Johto quest built and focused native gameplay/save/return checks passed; at its prototype review gate. The save foundation is completed separately.  
**B4:** Incremental campaign qualification and joint integration readiness.

Each milestone ends with a review. The latest dated owner steering determines the current bounded work; there is no automatic advance beyond its review gate or changes to Workstream A.

Prepared October 8, 2026. Source documentation was inspected for this package; no game compilation or playtest was performed in preparing it. All checklist results start as **NOT RUN**.
