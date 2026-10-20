# B1 audit approval and Workstream C handoff

**Owner:** Malik  
**Date:** October 9, 2026, America/New_York  
**Authorized:** B1 compatibility and fidelity audit, plus a frozen local handoff of tested candidate 010 for Workstream C's initial asset inventory

The owner approves proceeding from the B0 review gate into the B1 audit described in `NEXT_STEPS_REQUIREMENTS.md`. The recorded B0 limitations are accepted for further evaluation, not for a player release. This supersedes the earlier B0 stop condition only for the approved audit and handoff.

Save implementation, roamer gameplay repair, engine replacement and a Johto merge remain unauthorized. The source pin, tested complete patch and baseline ROMs remain unchanged. Browser compatibility evaluation remains subject to the existing runtime coordination requirement; the owner reports that Workstream A's selected runtime is unknown.

## Ownership

B retains saves, campaign behavior, runtime time/palette systems, engine budgets and final integration. C owns its isolated art inventory, packages, replacements and validation. B supplies a reproducible frozen candidate, dependency information and change notices; C does not modify B's authoritative baseline. See [B to C coordination](../b-to-c-coordination.md).

For later B baselines, identify changes affecting C's asset dependencies or test assumptions. Do not require unrelated art work or unchanged tests to restart. Preserve evidence for the old baseline and qualify only affected work against the new one.

## Owner authorization

> I approve proceeding from the B0 review gate into the B1 compatibility and fidelity audit described in NEXT_STEPS_REQUIREMENTS.md.
>
> This accepts the recorded B0 limitations for further evaluation, not for a player release. It does not authorize save implementation, roamer gameplay repair, engine replacement, or a Johto merge.
>
> Add a B-to-C coordination section. Provide a frozen, reproducible handoff of the tested 010 candidate for Workstream C's initial asset inventory, including the complete patch, configuration, source fingerprints, available build manifests, and known limits. Keep artifacts and private evidence local and ignored.
>
> B retains ownership of saves, campaign behavior, runtime time/palette systems, engine budgets, and final integration. C owns its isolated art inventory, packages, replacements, and validation.
>
> For subsequent B baselines, identify changes affecting C's asset dependencies or test assumptions. Do not require unrelated art work or unchanged tests to restart.
>
> Preserve the existing workstream, GitHub, and approval boundaries.

## Boundaries

No Workstream A repository, configuration, dependencies, services, credentials or plan changes. No writes to a C workspace are implied by preparing the handoff. No messages to other project chats are authorized by this decision alone.

Artifacts, upstream trees, asset material and private evidence remain local under ignored `_local/`. No GitHub Actions, hosted automation, deployments, NAS/network changes, commits or remote writes are authorized. Existing publication, rights/credits and approval requirements remain in force.

The B1 result must distinguish verified source findings, existing native evidence, new executed tests and pending checks. End at the B1 review gate; later implementation needs its own explicit approval.
