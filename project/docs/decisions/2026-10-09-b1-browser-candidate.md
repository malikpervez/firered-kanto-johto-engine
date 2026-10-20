# B1 isolated browser test authorization

**Owner:** Malik  
**Date:** October 9, 2026, America/New_York  
**Scope:** Finish B1 browser tests using the recommended third-party mGBA WASM candidate in an isolated local B harness.

The owner states:

> Use the browser candidate you recommend and finish the B1 browser tests. Keep Workstream A untouched and stop at the B1 review gate.

This resolves the runtime-choice dependency for B's isolated compatibility evaluation. It does not select Workstream A's production dependency or authorize any A repository, configuration, dependency, service, credential or plan change.

The candidate is `@thenick775/mgba-wasm` 2.5.1. The earlier assessed source commit was `d5e226c63725f79bc96c7f75e2c8cbf07af9f2cd`; the actual registry package records `gitHead=e974b288bd7e5cfc7c7b96f8b4d32b673ddfb68c`. Preserve both identities and inspect differences. Pin actual downloaded files and reported runtime version; do not claim the published binary was built from the later assessed commit.

Use exact 010 ROM hashes and disposable copies of B-owned native fixtures. Keep B0 originals and C's frozen handoff unchanged. A local file-selection harness and its server stay under ignored `_local/`; bind only to `127.0.0.1` with an OS-assigned unused port. No ROM/saves are bundled or served as page assets, and no remote endpoint is used for their contents.

Execute input, audio-output, speed, focus, RTC, native save import/export, refresh/restart persistence and native/browser/native checks. Native saves, not emulator states, establish persistence. Attribute any human listening separately and leave unexecuted checks pending. No ROM memory edits, gameplay bypass, engine changes, new save format, roamer repair, asset integration or region merge are authorized.

No system/global installation, NAS/network configuration, hosted automation, GitHub Actions, commit, remote write or deployment. Stop at B1 review; later implementation still requires explicit approval.
