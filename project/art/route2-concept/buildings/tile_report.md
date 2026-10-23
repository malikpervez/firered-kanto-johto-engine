# Route 2 v0.3 tile report

Counts use actual 8×8 palette-index tiles. H, V and combined H/V mirrors merge; rotations do not. Animation frame storage is excluded. Used transparent blanks are included.

| Building / group | v0.2 | v0.3 | Cap |
| --- | ---: | ---: | --- |
| Forest gate south | 149 | 116 | Shared pair cap |
| Forest gate north | 147 | 96 | Shared pair cap |
| Forest pair union | 177 | 120 | 140 |
| Full cave assembly | 87 | 59 | 60 |
| East gatehouse | 41 | 41 | 41 |

The south/north counts overlap. Use the **120-tile union**, not their sum. The union includes one transparent blank: nonblank totals are 176 before and 119 after.

**Permanent building pool: 305 → 220 tiles**, a reduction of 85. The final pool occupies 7,040 bytes.

**Budget: 220 buildings + 160 other route tiles = 380/384**, leaving 4 tiles using the supplied estimate. All individual targets pass.

Three unchanged 16-entry palettes occupy 96 bytes. Their order and RGB values are unchanged. The trade house is an external dependency and is omitted.

The 62 stored animation tiles (1,984 bytes) are in a separate frame-replacement pool. The 14-tile optional cave-mouth overlay (448 bytes) is for alternate cave composition; the full cave already contains it. Do not add either excluded pool permanently to Route 2. Neither is hidden in the 220-tile resident binary.

Validation independently decodes the resident binary and applies all flip flags to reconstruct each base image exactly. Complete door strips and 4× copies, palettes, route plan and east gate remain byte-identical to v0.2. See validation.json and the 4× before/after preview.
