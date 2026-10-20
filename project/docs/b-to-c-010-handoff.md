# Frozen 010 handoff for Workstream C

**Ready for initial asset inventory.** Local package verification executed successfully: **36,955 checks, no failures, real verifier exit 0**. This verifies frozen bytes, source connectivity, the complete patch apply-check and read-only permissions. It is not a new build, gameplay test, save-compatibility result or permission to publish assets.

The owner authorized this handoff and the B1 audit on October 9, 2026. B/C ownership and future impact notices are defined in [the coordination contract](b-to-c-coordination.md). No C workspace or Workstream A files were inspected or changed.

## Exact package identity

Package: `[LOCAL_WORKSPACE]/_local/handoffs/b-to-c/010-2026-10-09/`.

| Record | Exact identity |
|---|---|
| [Canonical manifest](../_local/handoffs/b-to-c/010-2026-10-09/manifest.json) | SHA-256 `7114ef93633999129770b056a2dacccb26bd351e3f4abb4d13e82f0a24eac9e8` |
| Verified payload | 36,945 files; 664,224,847 bytes, excluding manifest/verification/seal records bound separately |
| [Executed verification](../_local/handoffs/b-to-c/010-2026-10-09/verification.json) | PASS, 36,955 checks, real exit 0; SHA-256 `c4f3e399941f62b14c75af839f540b8b2a829350a5ae55d0fadb27d1d0ea13cd` |
| [Final seal receipt](../_local/handoffs/b-to-c/010-2026-10-09/seal.json) | SHA-256 `6534e3cc3f38b0332b95dbae79f72a99aa539ff543e416b4c7316c5805ccae0b`; 36,948 files / 5,534 directories with no write bits, originals unchanged |
| Source commit | `167aa6d537b109bb229c231ddce4616974c4da71`, tag `Release-v2.0.6` |
| Source Git tree | `894cb396da56fbf8054a95ebf864dc74b7b6b4c6` |
| Snapshot bundle | `source/pinned-snapshot.bundle`, 66,618,997 bytes; SHA-256 `b528cad85e4d27a667000f7e1d35ad560dc54c07183f3b10178df0de26339e3d` |
| Required shallow boundary | `source/shallow-boundary.txt`; SHA-256 `3ad4658162ae1d0332552c4ce2d95ba239b59a76928b2253e0909608bafe8b00` |
| Complete patch | `patches/0010-firered-fresh-monotype-default.patch`, 21,515 bytes; SHA-256 `3e9b6b003557cbfacff59706ad04e4f7f2fdd58bc6162be995f91dc09742d5f3` |
| Patch/configuration fingerprint | `32faeccdf41db77505858cd2981a070c7f835f0eee3180fe1563cb4c0e343f00` |
| Canonical pristine input inventory | SHA-256 `14355135c27148a0b2ee06dce388f5d21dba443880e22e022f2fa49e56d82e2a` |
| Canonical patched input inventory | SHA-256 `be227d880e6a3a4791f0a2a04b6571b6a00d7e43de3c52d1a352ba25d998caea` |
| Canonical asset input inventory | SHA-256 `099f1b132b9c7dc0d353b1132293ccff30bc2228df81cb19f6f6b21b50b9947a`; 34,105 asset-path files within 36,739 tracked source files |

The source snapshot is **depth-1**, with complete pinned source content but no full upstream ancestry. Full-history enumeration was interrupted after about seven minutes and remains explicitly incomplete. A fresh local bundle receive executed; connectivity initially failed on the excluded parent, then passed after installing the supplied shallow marker. Both outcomes are preserved. Git's generic bundle message about complete history is not an ancestry qualification. Original B upstream history and checkouts remain untouched.

Source inventories retain raw filesystem hashes and Git-clean blob identities; pinned attributes require CRLF for some palette/PowerShell inputs. Authoritative `*-input-inventory-v3.json` files account for this. Earlier inventory/checkpoint failures and corrections are retained under `preparation/` and clearly superseded; they do not change the candidate.

## Included inputs and outputs

The manifest enumerates every frozen payload and separately maps original manifest paths to frozen files. It retains original paths inside all copied build manifests rather than rewriting history.

- `source/`: pristine source snapshot, bundle/boundary, complete tracked/input inventories and target input fingerprints.
- `patches/`: complete 010 patch, applied alone to the pristine pin. Do not stack earlier patches.
- `control/` and `tools/`: original lock files, manual build wrapper, setup notes and activation script; verified external tool/archive hashes. Tool binaries and the macOS SDK remain external prerequisites.
- `builds/`: all four final 010 clean/repeat manifests with full logs, actual effective configurations, commands/exits and applied/generated diffs; original HnS 009 manifest/evidence association.
- `configuration/` and `generated/`: effective target definitions, configuration inventories and actual map/layout selections. FireRed selects 417 FRLG maps and zero HnS; HnS selects 560 HnS maps.
- `artifacts/`: one canonical ROM/ELF/map set for each target. Repeat manifests refer to the same verified bytes through the package mapping.
- `comparisons/` and `qualification/`: repeat identity, HnS 009→010 byte identity, original native report snapshots/session bindings, actual ARM layout evidence, rights notes and separate owner audio attribution.

No native save, save state, personal evidence image/audio/video, BIOS or credential was copied. Public upstream graphics remain inside the ignored source snapshot for the authorized local inventory; they are not approved for publication. Inherited workflow files remain inert inside private source material.

| Frozen output | SHA-256 |
|---|---|
| `artifacts/firered/pokefirered.gba` | `3e504731d9dd3c02ec273dc257c86f557caaf8c9b933d2f0ff73558c2e121a39` |
| `artifacts/firered/pokefirered.elf` | `f0409c5e872ad265d26f1a38660c8ecee6763e85ef2728a5ec7bd2951d483853` |
| `artifacts/firered/pokefirered.map` | `5d4bbe4d505caf89015c2577144852e139898130f85ba96fb0e74877f573bc4c` |
| `artifacts/hns/pokehns.gba` | `4bb58fe3c06bc0b60146aa946cbc34f087efa607f525f68e0a1e99c0db9cde75` |
| `artifacts/hns/pokehns.elf` | `874096c8eee38c4f0f1d242e8e840c324ca34a5ac7623a04848568b11fcf4a0b` |
| `artifacts/hns/pokehns.map` | `5a7fcf822ec78dfd8dd8fe4fffe29a5464c732902ba4c859a56216255198cf79` |

Both ROMs are 33,554,432 bytes. Original available manifests are `repair-10-firered`, `repair-10-hns`, `repair-10-repeat-firered`, `repair-10-repeat-hns` and `repair-09-hns`, all with make/wrapper exit 0. The first four are the reproducible final 010 builds. HnS native evidence stays bound to its 009 session and is associated with 010 by executed exact ROM/ELF/map identity, without claiming an additional GUI run.

## Verification and reproduction

Read the frozen [README](../_local/handoffs/b-to-c/010-2026-10-09/README.md) and [known limits](../_local/handoffs/b-to-c/010-2026-10-09/KNOWN_LIMITS.md). Manual verification is:

```sh
python3 [LOCAL_WORKSPACE]/_local/handoffs/b-to-c/010-2026-10-09/verify_package.py
```

Compare the returned manifest hash to the value above. The verifier reads locally, disables lazy remote fetching and permits file transport only; it does not modify the package or execute game/build code. Hashes are the identity; read-only permissions prevent routine edits and are not cryptographic signing.

The README supplies exact commands to restore into a new isolated B-owned receiver, install the shallow marker, verify commit/tree/connectivity, set the source URL on that new copy only for the manual wrapper's identity check, and build each target with unique run IDs and two jobs. The complete patch is applied by the wrapper to fresh per-target trees. No original checkout or receiver with existing data is reused.

**These restored-source rebuild commands were prepared, not executed during B1.** Existing original clean/repeat builds are the build evidence. Local tools are pinned and hash-checked but not bundled; same-host tool paths are recorded. Relocation or another host requires documented prerequisite setup/requalification, not an assumed hermetic build. C's first inventory needs verified source/configuration and does not require another playthrough merely to copy unchanged bytes.

## Limits and C use

The four-byte FireRed save margin and roamer fidelity defect remain open. Full campaigns, natural Sevii progression, old/cross-target saves, broad RTC behavior, browser interoperability and runtime peaks are unqualified. B1 additionally identifies unprotected SaveBlock3 chunks/partial-save coherence, persistent regional-ID conflicts, HnS Kanto reset behavior, disabled original interfaces and a 16-active-object limit. See [the B1 review gate](b1-gate.md) and attached known limits; this handoff does not fix or waive them.

C records the canonical handoff hash, asset/input hashes, actual target selection, logical IDs, format/conversion/palette/animation dependencies and rights/credits. Keep replacements isolated and report budget/runtime requirements to B. B retains saves, campaigns, time/palette code, engine budgets and integration. Later B notices identify affected dependency closures and tests; unchanged C work is retained.

No engine selection, save implementation, region merge, art integration, remote write, commit, deployment, hosted automation or Workstream A/NAS/network change is authorized by this package. Stop at the B1 review gate.
