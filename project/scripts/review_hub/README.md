# Local owner review room

Open [_local/owner-review/index.html]([LOCAL_WORKSPACE]/_local/owner-review/index.html) in a browser. The generated file needs no server, account, internet connection or hosted dependencies. Keep it in this folder so its relative image links continue to resolve.

The review room presents the original Markdown records with chapter navigation, full-text search, a screenshot gallery, enlarged images and a feedback notebook. It retains exact dialogue, source links, evidence labels and historical build context. It does not change game code, test outcomes, saves or existing review evidence.

Open `index.html#pikachu` for the focused Pikachu mood review. It places each exact implemented textbox beside its current-build native captures, with filters for bond reactions, situations and missing captures. Source labels, trigger/location details and image-specific feedback remain available. The page derives its 15 outcomes from the current capture index and verifies their dialogue against the local script during generation. Outcomes without accepted gameplay images remain explicitly `NOT RUN`.

Open `index.html#journey` for the start-to-finish campaign guide: Kanto and Sevii, the outdoor western road and Surf crossing, Johto, both legendary branches, farewell/reunion and the open postgame. Region and story-thread filters lead to source-checked event entries and their original exact dialogue/capture records. Proposed Friends events are presented separately. The Markdown source is `docs/campaign-story-and-progression-guide.md`; ignored `_local/review-hub-inputs/campaign-journey.json` supplies the structured chapter navigation. The generator rejects missing references, changed script entry labels and mismatched build identity. Current preview identity is separate from the original 36P mood feature record; historical captures are never relabeled as current-preview gameplay.

## Regenerate after updating reviews

From the workspace root, run:

```sh
[LOCAL_MACHINE_PATH] scripts/review_hub/build.mjs
```

The generator uses the bundled `marked` module (17.0.5 for the initial build). If that runtime moves, select a local Node executable and set `REVIEW_HUB_MODULES` to the installed module directory. It never downloads dependencies. It writes `index.html`, `manifest.json` and `README.txt` under ignored `_local/owner-review/`.

It discovers root Markdown, `docs/**/*.md` and owner evidence Markdown under `_local/evidence/`. Reconstructed upstream `scratch/recon/` documentation and symlinked duplicates are excluded. Matching Markdown reviews supersede their alternate HTML rendering in the library; the HTML-only Rainbow review is preserved through an audited safe fragment.

The initial curated inputs live in ignored `_local/review-hub-inputs/`:

- `document-groups.json`: build scopes and featured review metadata.
- `friends-structure.json`: exact capture provenance, original builds, staged labels and source references.
- `rainbow-structure.json`: historical HTML-only review and its sanitized fragment.

Keep these inputs with the local evidence. Use optional `_local/review-hub-inputs/current-review.json` for the current feature build/ROM/headroom, latest review path, hero image and capture index. This keeps historical story cards and their images on the original builds. The current capture index supplies exact build/staged/script metadata for newly added media. Update featured story paths in `build.mjs` only when their own review is superseded. Rebuild rather than editing generated HTML. The output manifest records source hashes, missing image references, renderer version and the final HTML hash.

## Feedback and privacy

Notes are browser-local and are not written back to Markdown or applied to the game. Export a JSON copy regularly; local-file storage behavior depends on the browser. Imports accept the review room's feedback schema, validate entries and deduplicate normalized IDs. No automatic network requests, synchronization, telemetry or uploads are included.

## Validation scope

The initial package has offline content, anchor, provenance and application-logic checks under `_local/owner-review/qa-*.json`. These are presentation checks, not new gameplay tests. Browser visual review was not executed: the browser automation policy rejected local-file navigation. Open the file directly for owner visual review. Do not bypass that policy with a server or another browser surface.

Original source reviews and evidence remain authoritative. A current document can reuse historical captures only with their original build and scope shown; a gallery image is never proof of an unexecuted branch.
