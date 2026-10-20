# B0 acceptance checklist — two independent baseline games

**Initial status: every test below is NOT RUN.** This file defines work to perform; it is not a report of completed builds or tests.

Use a copy for each tested commit/configuration. Record the tester as Codex, Malik, or another named tester and distinguish human evidence from tool-driven execution.

## Run identity

```text
Run ID:
Date/time/timezone:
Tester:
Host OS/architecture:
Toolchain:
Upstream URL + full commit SHA:
Local patch/config fingerprint:
mGBA version and settings:
FireRed ROM path + SHA-256:
HnS ROM path + SHA-256:
Save paths (separate per target):
Evidence directory (private, ignored):
```

Allowed results: `PASS — EXECUTED`, `FAIL — EXECUTED`, `NOT RUN`, `NEEDS OWNER TEST`, `BLOCKED`.

## A. Environment and build evidence

| ID | Check | Expected result | Initial result |
|---|---|---|---|
| ENV-01 | Inspect resolved workspace path and Git status | New B-owned workspace; no writes to A | NOT RUN |
| ENV-02 | Record dependencies and host | Actual versions; missing prerequisites identified | NOT RUN |
| SRC-01 | Read instructions and pin full source SHA | Real ref/commit and source notes recorded | NOT RUN |
| SRC-02 | Review notices and publication boundaries | Credits preserved; unknown reuse rights recorded | NOT RUN |
| BUILD-FR | Clean FireRed build | Intended target succeeds with real log/exit code | NOT RUN |
| BUILD-HNS | Clean HnS build | Separate intended target succeeds with real log/exit code | NOT RUN |
| BUILD-REPEAT | Repeat clean builds of both targets | Hash comparison; any difference explained | NOT RUN |
| BUILD-MANIFEST | Inventory outputs and configuration | ROM hashes, sizes, toolchain, target and patch status recorded | NOT RUN |
| CAPACITY-01 | Record available linker/size information | Real measurements; unknown capacity not guessed | NOT RUN |
| GIT-01 | Inspect tracked/staged files | No workflows, binary ROMs, private saves, assets or secrets | NOT RUN |

A repaired build must reference the preserved unmodified failure and exact repair. Do not label a patched build as pristine.

## B. FireRed native emulator smoke test

Use a fresh save and default campaign settings unless the selected build requires a documented choice.

| ID | Procedure | Expected result | Initial result |
|---|---|---|---|
| FR-01 | Boot; create trainer; enter the world | Actual intended FireRed/Pallet opening, not just a renamed title | NOT RUN |
| FR-02 | Trigger Oak introduction and choose starter naturally | Dialogue, movements and player control complete without lockup | NOT RUN |
| FR-03 | Complete initial rival sequence | Battle enters/exits correctly; story resumes | NOT RUN |
| FR-04 | Traverse early routes and buildings; talk to NPCs | Valid warps, collision, rendering and control | NOT RUN |
| FR-05 | Complete opening delivery/progression sequence | Intended early story state advances naturally | NOT RUN |
| FR-06 | Wild battle, capture when available, heal, inspect party | Battles and state changes work; no debug grants used as proof | NOT RUN |
| FR-07 | Open relevant bag, party and available Pokédex menus | No crash; changed/missing interfaces documented | NOT RUN |
| FR-08 | Save normally, fully exit, cold-reload | Trainer, party, items/money, location and event progress retained | NOT RUN |
| FR-09 | Continue, save again and cold-reload again | Second cycle works; no repeated starter/rewards or reset story | NOT RUN |
| FR-10 | Observe at least ten minutes active play | Record speed, input, visuals/audio and any hangs | NOT RUN |

Record deviations from vanilla FireRed separately, even when the game remains playable. Early success does not certify gyms, Sevii or the whole campaign.

## C. Heart & Soul native emulator smoke test

Confirm the pinned build's opening sequence in source. Do not force an assumed route order when its intended progression differs.

| ID | Procedure | Expected result | Initial result |
|---|---|---|---|
| HNS-01 | Boot; create trainer; enter the world | Intended New Bark Town/Johto opening | NOT RUN |
| HNS-02 | Complete Elm/starter sequence naturally | Starter and initial task obtained without broken scripts | NOT RUN |
| HNS-03 | Complete opening errand and reachable first rival sequence | Scripted transitions and battle complete in intended order | NOT RUN |
| HNS-04 | Traverse early routes/interiors and talk to NPCs | Valid warps, collision, rendering and control | NOT RUN |
| HNS-05 | Wild battle, capture when available, heal, inspect party | State updates and returns to field work | NOT RUN |
| HNS-06 | Check relevant menus and observable time settings | No crash; RTC setup and any limitations recorded | NOT RUN |
| HNS-07 | Save normally, fully exit, cold-reload | Identity, party, inventory, location and event progress retained | NOT RUN |
| HNS-08 | Continue, save again and cold-reload again | Second cycle works; no duplicate opening rewards | NOT RUN |
| HNS-09 | Observe at least ten minutes active play | Record speed, input, visuals/audio and any hangs | NOT RUN |

Time-dependent behavior observed briefly is not proof that all day/night events work. Mark the broader RTC regression as future scope.

## D. Save evidence rules

Before each cold-reload test, record visible trainer identity, party species/levels/moves, important items/money, map/location and completed opening event. Where safe tooling exposes additional native fields, record them without modifying them.

Fully close the game/emulator. Do not resume an auto-loaded state. Reopen the same ROM and load through the game's own continuation path. Keep native save copies in the target's private test folder. Do not import a FireRed save into HnS or claim cross-build compatibility from this test.

For every failure, record the test ID, ROM hash, last successful step, exact symptoms, reproducibility, relevant settings and local evidence references. Screenshots/logs must reflect actual execution.

## E. Owner test handoff when Codex lacks GUI access

Provide the exact local ROM paths, required mGBA version/settings, clean save-directory setup and the outstanding test IDs. Ask the owner to run those steps and report results. Mark the gate **HOLD — NEEDS OWNER TEST** until evidence arrives; do not mark tests passed because instructions were written.

## F. Gate summary template

```text
B0 decision: GO / HOLD / NO-GO ON CANDIDATE

FireRed build:
FireRed native gameplay:
FireRed normal save/reload:
HnS build:
HnS native gameplay:
HnS normal save/reload:
Clean rebuild comparison:
Source/patch/config identities:
Material fidelity gaps:
Untested checks:
Changed files:
Local artifact/evidence paths:
Reason for gate decision:
Requested owner approval or action:
```

**Stop after this report.** B1, browser testing, region merging and all remote changes require their own approval.
