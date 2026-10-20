# Claude: verify and review the current Kanto–Johto game engine

Read root AGENTS.md, README.md, CLOUD_TESTING.md and provenance/local-build-reference.json. This is the owner-authorized **37C private cloud test/review snapshot**, upstream `167aa6d537b109bb229c231ddce4616974c4da71`. The exact original raw-source fingerprint is recorded in that manifest and the complete input inventory.

Begin with the included integrity check. Restore the three pinned upstream inputs only if a build needs them. Execute a fresh isolated FireRed build, then the actual ARM 397-fact regression against that build copy’s real generated headers, when the cloud environment has the required toolchain/dependencies. Preserve logs, real failures and artifact hashes under ignored `_local/`. Record unavailable tooling and every unexecuted test explicitly. Do not claim gameplay from compilation or static checks.

Then review the complete cumulative change, not only Pikachu’s bike patch. Use the complete patch and 940 changed/additional file records to identify introduced changes while reading the full actual source for interfaces. Read project/docs/campaign-story-and-progression-guide.md, the state/save registries and current requirements/decisions. Historical 35A/31E/30F review prompts and earlier “current” headings are evidence for those versions, not permission to replace this baseline. Current source is `engine/`.

Priority areas:

1. Native6 save coordinator, regional container dispatch, sectors/checksums/atomicity, four-byte capacity margin, protected reserve, names and collection preservation. No save change, conversion or fixture edit is authorized.
2. Kanto/Sevii campaign identity, map/layout namespaces, native attributes/puzzles, seam/graphics decoder read spans, shared aliases and generator contracts. Earlier broken Oak-lab/exit/tree cases and their narrow repairs must be distinguished from current defects.
3. Pikachu grant/naming/rival recovery/Parcel/Pokédex; successful-delivery-only gift receipts, retries, full party/PC; saved Blue Eevee→Umbreon cohort selection and independent Silver history. Audit player-side state rather than inferring from species ownership.
4. Nao/Ho-Oh, Stranger/Mewtwo/Mew, separate Black Tide replicas and final restoration. Original Kanto birds and Navel Rock stay independent. Loss/flee/interruption must not create replica credit, and actual captures must be preserved.
5. Jessie/James optional double-battle eligibility, native blackout/retry and exact genuine assets; Jenny has no battle. Friends FG01–FG22, optional early/final opponents, late adoption, placement retirement, farewell choices, map-exit reunion and unobtainable scripted Giratina. FG-A–FG-G and the October 19 rework are drafts; do not implement or mark them complete.
6. Permanent Pikachu presentation companion, 15 mood selectors, absent/boxed/evolved actual owned Pokémon, escorts/scene suppression, native walking versus bicycle/Surf transitions, stale saved sprite IDs and palette/affine/visibility ownership.
7. Trail’s five rear frames, battler graphics allocation and dynamic heap; static RAM equality is not a runtime peak guarantee. Audit compressed sprite/palette formats, native draw ordering and the current title preview without adding Pikachu.
8. ROM deduplication/aliasing, -Os exceptions, C undefined behavior/alignment, host tool reproducibility, target guards and affected non-FireRed behavior. Most intended players use Delta, but no fresh Delta/device test is implied by this export.

Use bounded source/host/ARM checks where useful; do not weaken expectations, invent macros, remove content, expand the cartridge, consume reserve, change source, publish, create automation or touch other workstreams. A source-confirmed defect, runtime hypothesis, inherited limitation, planned feature and missing test are different finding types.

Deliver a concise status plus findings containing severity, exact current file/line/function/script, preconditions, causal chain, practical impact, inherited/introduced status, reproduction/check results and smallest proposed repair. Include commands/tool versions/exits, actual resource measurements, missing prerequisites and a test-coverage table. Testing and review are authorized; fixes and further remote writes wait for owner instruction.
