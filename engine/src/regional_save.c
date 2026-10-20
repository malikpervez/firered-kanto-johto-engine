#include "global.h"
#include "regional_save.h"

static const u8 sMagic[4] = {'F', 'R', 'J', 'S'};
static const u8 sMainDomain[8] = {'F', 'R', 'J', 'S', 'M', 'A', 'I', 'N'};
static const u16 sMainSectorSizes[14] =
{
    3892, 3968, 3968, 3968, 3964,
    3968, 3968, 3968, 3968, 3968, 3968, 3968, 3968, 2400,
};

static const u32 sSha256RoundConstants[64] =
{
    0x428A2F98, 0x71374491, 0xB5C0FBCF, 0xE9B5DBA5,
    0x3956C25B, 0x59F111F1, 0x923F82A4, 0xAB1C5ED5,
    0xD807AA98, 0x12835B01, 0x243185BE, 0x550C7DC3,
    0x72BE5D74, 0x80DEB1FE, 0x9BDC06A7, 0xC19BF174,
    0xE49B69C1, 0xEFBE4786, 0x0FC19DC6, 0x240CA1CC,
    0x2DE92C6F, 0x4A7484AA, 0x5CB0A9DC, 0x76F988DA,
    0x983E5152, 0xA831C66D, 0xB00327C8, 0xBF597FC7,
    0xC6E00BF3, 0xD5A79147, 0x06CA6351, 0x14292967,
    0x27B70A85, 0x2E1B2138, 0x4D2C6DFC, 0x53380D13,
    0x650A7354, 0x766A0ABB, 0x81C2C92E, 0x92722C85,
    0xA2BFE8A1, 0xA81A664B, 0xC24B8B70, 0xC76C51A3,
    0xD192E819, 0xD6990624, 0xF40E3585, 0x106AA070,
    0x19A4C116, 0x1E376C08, 0x2748774C, 0x34B0BCB5,
    0x391C0CB3, 0x4ED8AA4A, 0x5B9CCA4F, 0x682E6FF3,
    0x748F82EE, 0x78A5636F, 0x84C87814, 0x8CC70208,
    0x90BEFFFA, 0xA4506CEB, 0xBEF9A3F7, 0xC67178F2,
};

u16 RegionalSave_Read16(const u8 *bytes)
{
    return (u16)bytes[0] | ((u16)bytes[1] << 8);
}

u32 RegionalSave_Read32(const u8 *bytes)
{
    return (u32)bytes[0] | ((u32)bytes[1] << 8) | ((u32)bytes[2] << 16) | ((u32)bytes[3] << 24);
}

void RegionalSave_Write16(u8 *bytes, u16 value)
{
    bytes[0] = value;
    bytes[1] = value >> 8;
}

void RegionalSave_Write32(u8 *bytes, u32 value)
{
    bytes[0] = value;
    bytes[1] = value >> 8;
    bytes[2] = value >> 16;
    bytes[3] = value >> 24;
}

void RegionalSave_InitExtension(u8 *image)
{
    memset(image + REGIONAL_SAVE_PREFIX_SIZE, 0, REGIONAL_SAVE_SIZE - REGIONAL_SAVE_PREFIX_SIZE);
    memcpy(image + REGIONAL_SAVE_HEADER_OFFSET, sMagic, sizeof(sMagic));
    RegionalSave_Write16(image + REGIONAL_SAVE_SCHEMA_OFFSET, REGIONAL_SAVE_SCHEMA);
    RegionalSave_Write16(image + REGIONAL_SAVE_HEADER_LENGTH_OFFSET, REGIONAL_SAVE_HEADER_SIZE);
    RegionalSave_Write16(image + REGIONAL_SAVE_LENGTH_OFFSET, REGIONAL_SAVE_SIZE);
    RegionalSave_Write32(image + REGIONAL_SAVE_CONTENT_OFFSET, REGIONAL_SAVE_CONTENT_ID);
    RegionalSave_Write32(image + REGIONAL_SAVE_LAYOUT_OFFSET, REGIONAL_SAVE_LAYOUT_ID);
    RegionalSave_Write16(image + REGIONAL_SAVE_RECORD_COUNT_OFFSET, 2);
    RegionalSave_Write16(image + REGIONAL_SAVE_KANTO_OFFSET, REGIONAL_SAVE_KANTO);
    RegionalSave_Write16(image + REGIONAL_SAVE_KANTO_OFFSET + 2, 1);
    RegionalSave_Write16(image + REGIONAL_SAVE_JOHTO_OFFSET, REGIONAL_SAVE_JOHTO);
    RegionalSave_Write16(image + REGIONAL_SAVE_JOHTO_OFFSET + 2, 1);
}

static bool8 BytesAreZero(const u8 *bytes, u32 length)
{
    while (length--)
        if (*bytes++ != 0)
            return FALSE;
    return TRUE;
}

static bool8 PrototypeMilestonesValid(const u8 *image, bool8 allowBlank)
{
    u16 quest = RegionalSave_Read16(image + REGIONAL_SAVE_VARS_OFFSET);
    if (quest > 3 || (!allowBlank && quest == 0))
        return FALSE;
    return (image[REGIONAL_SAVE_EVENTS_OFFSET] & 7) == ((1 << quest) - 1);
}

static bool8 CampaignTypedStateValid(const u8 *image)
{
    u32 i;
    const u8 *mom = image + REGIONAL_SAVE_MOM_SAVINGS_OFFSET;
    // These are the original HnS savings bounds and ten sequential gift bits.
    if (RegionalSave_Read32(mom) > 999999
     || (RegionalSave_Read16(mom + 4) & ~0x3FF) != 0
     || mom[6] > TRUE || mom[7] != TRUE)
        return FALSE;
    for (i = 0; i < REGIONAL_SAVE_DOG_ROAMER_COUNT; i++)
    {
        const u8 *dog = image + REGIONAL_SAVE_DOG_ROAMERS_OFFSET + i * REGIONAL_SAVE_DOG_ROAMER_SIZE;
        u16 species = RegionalSave_Read16(dog + 8);
        if (species == SPECIES_NONE)
        {
            if (!BytesAreZero(dog, REGIONAL_SAVE_DOG_ROAMER_SIZE))
                return FALSE;
        }
        else if ((species != SPECIES_RAIKOU && species != SPECIES_ENTEI)
         || dog[12] == 0 || dog[12] > MAX_LEVEL
         || dog[19] > TRUE || dog[21] > TRUE || dog[22] != 0
         || !BytesAreZero(dog + 23, 5))
        {
            return FALSE;
        }
    }
    for (i = 0; i < REGIONAL_SAVE_REMATCH_COUNT; i++)
    {
        u32 start = REGIONAL_SAVE_REMATCH_BIT_OFFSET + i * 3;
        u32 bit;
        u8 readiness = 0;
        for (bit = 0; bit < 3; bit++)
            readiness |= ((image[REGIONAL_SAVE_TRAINERS_OFFSET + ((start + bit) >> 3)] >> ((start + bit) & 7)) & 1) << bit;
        if (readiness > 5)
            return FALSE;
    }
    return TRUE;
}

bool8 RegionalSave_FoundationValid(const u8 *image)
{
    u32 content;
    u32 initialized;
    u16 headerFlags;
    u32 revision;
    u32 i;
    u8 badges = 0;
    bool8 badge;

    if (image == NULL
     || memcmp(image + REGIONAL_SAVE_HEADER_OFFSET, sMagic, sizeof(sMagic)) != 0
     || RegionalSave_Read16(image + REGIONAL_SAVE_SCHEMA_OFFSET) != REGIONAL_SAVE_SCHEMA
     || RegionalSave_Read16(image + REGIONAL_SAVE_HEADER_LENGTH_OFFSET) != REGIONAL_SAVE_HEADER_SIZE
     || RegionalSave_Read16(image + REGIONAL_SAVE_LENGTH_OFFSET) != REGIONAL_SAVE_SIZE
     || RegionalSave_Read32(image + REGIONAL_SAVE_LAYOUT_OFFSET) != REGIONAL_SAVE_LAYOUT_ID
     || RegionalSave_Read16(image + REGIONAL_SAVE_RECORD_COUNT_OFFSET) != 2
     || RegionalSave_Read16(image + REGIONAL_SAVE_RESERVED_OFFSET) != 0
     || RegionalSave_Read16(image + REGIONAL_SAVE_KANTO_OFFSET) != REGIONAL_SAVE_KANTO
     || RegionalSave_Read16(image + REGIONAL_SAVE_KANTO_OFFSET + 2) != 1
     || RegionalSave_Read16(image + REGIONAL_SAVE_JOHTO_OFFSET) != REGIONAL_SAVE_JOHTO
     || RegionalSave_Read16(image + REGIONAL_SAVE_JOHTO_OFFSET + 2) != 1
     || !BytesAreZero(image + REGIONAL_SAVE_KANTO_OFFSET + 4, 28))
        return FALSE;

    content = RegionalSave_Read32(image + REGIONAL_SAVE_CONTENT_OFFSET);
    headerFlags = RegionalSave_Read16(image + REGIONAL_SAVE_FLAGS_OFFSET);
    if (content != REGIONAL_SAVE_FOUNDATION_CONTENT_ID
     && content != REGIONAL_SAVE_PROTOTYPE_CONTENT_ID
     && content != REGIONAL_SAVE_CONTENT_ID)
        return FALSE;
    if ((content != REGIONAL_SAVE_CONTENT_ID && headerFlags != 0)
     || (content == REGIONAL_SAVE_CONTENT_ID
      && headerFlags != 0 && headerFlags != REGIONAL_SAVE_HEADER_CAMPAIGN_SEEDED))
        return FALSE;

    initialized = RegionalSave_Read32(image + REGIONAL_SAVE_JOHTO_FLAGS_OFFSET);
    if (content == REGIONAL_SAVE_FOUNDATION_CONTENT_ID || initialized == 0)
        return headerFlags == 0
            && BytesAreZero(image + REGIONAL_SAVE_JOHTO_OFFSET + 4, REGIONAL_SAVE_SIZE - REGIONAL_SAVE_JOHTO_OFFSET - 4);
    revision = content == REGIONAL_SAVE_CONTENT_ID ? REGIONAL_SAVE_CAMPAIGN_MAPPING_REVISION : 1;
    if (initialized != REGIONAL_SAVE_JOHTO_INITIALIZED
     || RegionalSave_Read32(image + REGIONAL_SAVE_JOHTO_EVENT_REVISION_OFFSET) != revision
     || RegionalSave_Read32(image + REGIONAL_SAVE_JOHTO_TRAINER_REVISION_OFFSET) != revision
     || RegionalSave_Read32(image + REGIONAL_SAVE_JOHTO_VAR_REVISION_OFFSET) != revision)
        return FALSE;

    if (headerFlags == 0)
    {
        // Preserved prototype state is the only occupied unseeded state.
        return BytesAreZero(image + REGIONAL_SAVE_JOHTO_OFFSET + 8, 12)
            && PrototypeMilestonesValid(image, FALSE)
            && (image[REGIONAL_SAVE_EVENTS_OFFSET] & ~7) == 0
            && BytesAreZero(image + REGIONAL_SAVE_EVENTS_OFFSET + 1, REGIONAL_SAVE_VARS_OFFSET - REGIONAL_SAVE_EVENTS_OFFSET - 1)
            && BytesAreZero(image + REGIONAL_SAVE_VARS_OFFSET + 2, REGIONAL_SAVE_SIZE - REGIONAL_SAVE_VARS_OFFSET - 2);
    }

    // Content3: the original prototype indices remain permanently reserved.
    // Registered nontrainer flags use event3..1538; trainers use0..863.
    if (!PrototypeMilestonesValid(image, TRUE)
     || (image[REGIONAL_SAVE_EVENTS_OFFSET + 192] & 0xF8) != 0
     || !BytesAreZero(image + REGIONAL_SAVE_EVENTS_OFFSET + 193, 3)
     || !BytesAreZero(image + REGIONAL_SAVE_DOG_ROAMERS_OFFSET + 56, 4)
     || !BytesAreZero(image + REGIONAL_SAVE_TRAINERS_OFFSET + 124, 4)
     || !BytesAreZero(image + REGIONAL_SAVE_DOG_HISTORY_OFFSET + 12, 8)
     || !BytesAreZero(image + REGIONAL_SAVE_RESERVE_OFFSET, REGIONAL_SAVE_RESERVE_SIZE)
     || !CampaignTypedStateValid(image)
     || image[REGIONAL_SAVE_JOHTO_STARTER_STATE_OFFSET] > 2)
        return FALSE;
    // The fixed eight-Johto-badge mask must match the registered flag bits.
    for (i = 0; i < 8; i++)
    {
        RegionalSave_GetEvent(image, REGIONAL_SAVE_JOHTO, 1283 + i, &badge);
        if (badge)
            badges |= 1 << i;
    }
    if (image[REGIONAL_SAVE_JOHTO_BADGES_OFFSET] != badges)
        return FALSE;
    return TRUE;
}

bool8 RegionalSave_UpgradeToCampaign(u8 *image)
{
    if (!RegionalSave_FoundationValid(image))
        return FALSE;
    if (RegionalSave_Read32(image + REGIONAL_SAVE_CONTENT_OFFSET) == REGIONAL_SAVE_CONTENT_ID)
        return TRUE;
    // Only known, validated content1/2 is upgraded. The prototype data stays.
    RegionalSave_Write32(image + REGIONAL_SAVE_CONTENT_OFFSET, REGIONAL_SAVE_CONTENT_ID);
    if (RegionalSave_Read32(image + REGIONAL_SAVE_JOHTO_FLAGS_OFFSET) == REGIONAL_SAVE_JOHTO_INITIALIZED)
    {
        RegionalSave_Write32(image + REGIONAL_SAVE_JOHTO_EVENT_REVISION_OFFSET, REGIONAL_SAVE_CAMPAIGN_MAPPING_REVISION);
        RegionalSave_Write32(image + REGIONAL_SAVE_JOHTO_TRAINER_REVISION_OFFSET, REGIONAL_SAVE_CAMPAIGN_MAPPING_REVISION);
        RegionalSave_Write32(image + REGIONAL_SAVE_JOHTO_VAR_REVISION_OFFSET, REGIONAL_SAVE_CAMPAIGN_MAPPING_REVISION);
    }
    return TRUE;
}

void RegionalSave_SetGeneration(u8 *image, u32 generation)
{
    if (RegionalSave_UpgradeToCampaign(image))
        RegionalSave_Write32(image + REGIONAL_SAVE_GENERATION_OFFSET, generation);
}

bool8 RegionalSave_InitializeJohto(u8 *image)
{
    if (!RegionalSave_UpgradeToCampaign(image))
        return FALSE;
    if (RegionalSave_Read16(image + REGIONAL_SAVE_VARS_OFFSET) != 0)
        return TRUE;
    RegionalSave_Write32(image + REGIONAL_SAVE_JOHTO_FLAGS_OFFSET, REGIONAL_SAVE_JOHTO_INITIALIZED);
    RegionalSave_Write32(image + REGIONAL_SAVE_JOHTO_EVENT_REVISION_OFFSET, REGIONAL_SAVE_CAMPAIGN_MAPPING_REVISION);
    RegionalSave_Write32(image + REGIONAL_SAVE_JOHTO_TRAINER_REVISION_OFFSET, REGIONAL_SAVE_CAMPAIGN_MAPPING_REVISION);
    RegionalSave_Write32(image + REGIONAL_SAVE_JOHTO_VAR_REVISION_OFFSET, REGIONAL_SAVE_CAMPAIGN_MAPPING_REVISION);
    image[REGIONAL_SAVE_EVENTS_OFFSET] |= 1;
    RegionalSave_Write16(image + REGIONAL_SAVE_VARS_OFFSET, 1);
    return TRUE;
}

u8 RegionalSave_CheckHeader(const u8 *image, u32 generation)
{
    if (image == NULL || memcmp(image + REGIONAL_SAVE_HEADER_OFFSET, sMagic, sizeof(sMagic)) != 0)
        return REGIONAL_SAVE_HEADER_INVALID;
    if (RegionalSave_Read16(image + REGIONAL_SAVE_SCHEMA_OFFSET) != REGIONAL_SAVE_SCHEMA
     || (RegionalSave_Read32(image + REGIONAL_SAVE_CONTENT_OFFSET) != REGIONAL_SAVE_FOUNDATION_CONTENT_ID
      && RegionalSave_Read32(image + REGIONAL_SAVE_CONTENT_OFFSET) != REGIONAL_SAVE_PROTOTYPE_CONTENT_ID
      && RegionalSave_Read32(image + REGIONAL_SAVE_CONTENT_OFFSET) != REGIONAL_SAVE_CONTENT_ID)
     || (RegionalSave_Read16(image + REGIONAL_SAVE_FLAGS_OFFSET) != 0
      && (RegionalSave_Read32(image + REGIONAL_SAVE_CONTENT_OFFSET) != REGIONAL_SAVE_CONTENT_ID
       || RegionalSave_Read16(image + REGIONAL_SAVE_FLAGS_OFFSET) != REGIONAL_SAVE_HEADER_CAMPAIGN_SEEDED))
     || RegionalSave_Read32(image + REGIONAL_SAVE_LAYOUT_OFFSET) != REGIONAL_SAVE_LAYOUT_ID)
        return REGIONAL_SAVE_HEADER_UNSUPPORTED;
    if (RegionalSave_Read16(image + REGIONAL_SAVE_HEADER_LENGTH_OFFSET) != REGIONAL_SAVE_HEADER_SIZE
     || RegionalSave_Read16(image + REGIONAL_SAVE_LENGTH_OFFSET) != REGIONAL_SAVE_SIZE
     || RegionalSave_Read32(image + REGIONAL_SAVE_GENERATION_OFFSET) != generation
     || RegionalSave_Read16(image + REGIONAL_SAVE_RECORD_COUNT_OFFSET) != 2
     || RegionalSave_Read16(image + REGIONAL_SAVE_RESERVED_OFFSET) != 0
     || !RegionalSave_FoundationValid(image))
        return REGIONAL_SAVE_HEADER_INVALID;
    return REGIONAL_SAVE_HEADER_VALID;
}

static u32 CrcByte(u32 crc, u8 byte)
{
    u32 bit;
    crc ^= byte;
    for (bit = 0; bit < 8; bit++)
        crc = (crc >> 1) ^ ((crc & 1) ? 0xEDB88320 : 0);
    return crc;
}

u32 RegionalSave_Crc32(const u8 *bytes, u32 length)
{
    u32 crc = 0xFFFFFFFF;
    while (length--)
        crc = CrcByte(crc, *bytes++);
    return crc ^ 0xFFFFFFFF;
}

u32 RegionalSave_ComputeCrc(const u8 *image)
{
    u32 crc = 0xFFFFFFFF;
    u32 i;
    for (i = 0; i < REGIONAL_SAVE_SIZE; i++)
        crc = CrcByte(crc, i >= REGIONAL_SAVE_CRC_OFFSET && i < REGIONAL_SAVE_CRC_OFFSET + 4 ? 0 : image[i]);
    return crc ^ 0xFFFFFFFF;
}

bool8 RegionalSave_CheckCrc(const u8 *image)
{
    return RegionalSave_Read32(image + REGIONAL_SAVE_CRC_OFFSET) == RegionalSave_ComputeCrc(image);
}

void RegionalSave_Finalize(u8 *image, const u8 digest[32])
{
    memcpy(image + REGIONAL_SAVE_DIGEST_OFFSET, digest, 32);
    RegionalSave_Write32(image + REGIONAL_SAVE_CRC_OFFSET, RegionalSave_ComputeCrc(image));
}

static u32 RotateRight(u32 value, u32 count)
{
    return (value >> count) | (value << (32 - count));
}

static u32 ReadBig32(const u8 *bytes)
{
    return ((u32)bytes[0] << 24) | ((u32)bytes[1] << 16) | ((u32)bytes[2] << 8) | bytes[3];
}

static void WriteBig32(u8 *bytes, u32 value)
{
    bytes[0] = value >> 24;
    bytes[1] = value >> 16;
    bytes[2] = value >> 8;
    bytes[3] = value;
}

static void ShaTransform(struct RegionalSaveSha256Context *context, struct RegionalSaveSha256Schedule *schedule)
{
    u32 a = context->state[0];
    u32 b = context->state[1];
    u32 c = context->state[2];
    u32 d = context->state[3];
    u32 e = context->state[4];
    u32 f = context->state[5];
    u32 g = context->state[6];
    u32 h = context->state[7];
    u32 i;
    for (i = 0; i < 16; i++)
        schedule->words[i] = ReadBig32(context->block + i * 4);
    for (i = 0; i < 64; i++)
    {
        u32 t1;
        u32 t2;
        if (i >= 16)
        {
            u32 x = schedule->words[(i - 15) & 15];
            u32 y = schedule->words[(i - 2) & 15];
            u32 s0 = RotateRight(x, 7) ^ RotateRight(x, 18) ^ (x >> 3);
            u32 s1 = RotateRight(y, 17) ^ RotateRight(y, 19) ^ (y >> 10);
            schedule->words[i & 15] += s0 + schedule->words[(i - 7) & 15] + s1;
        }
        t1 = h + (RotateRight(e, 6) ^ RotateRight(e, 11) ^ RotateRight(e, 25))
           + ((e & f) ^ (~e & g)) + sSha256RoundConstants[i] + schedule->words[i & 15];
        t2 = (RotateRight(a, 2) ^ RotateRight(a, 13) ^ RotateRight(a, 22))
           + ((a & b) ^ (a & c) ^ (b & c));
        h = g;
        g = f;
        f = e;
        e = d + t1;
        d = c;
        c = b;
        b = a;
        a = t1 + t2;
    }
    context->state[0] += a;
    context->state[1] += b;
    context->state[2] += c;
    context->state[3] += d;
    context->state[4] += e;
    context->state[5] += f;
    context->state[6] += g;
    context->state[7] += h;
}

void RegionalSave_Sha256Init(struct RegionalSaveSha256Context *context)
{
    static const u32 initial[8] =
    {
        0x6A09E667, 0xBB67AE85, 0x3C6EF372, 0xA54FF53A,
        0x510E527F, 0x9B05688C, 0x1F83D9AB, 0x5BE0CD19,
    };
    memcpy(context->state, initial, sizeof(initial));
    context->bitCountLow = 0;
    context->bitCountHigh = 0;
    context->blockLength = 0;
}

void RegionalSave_Sha256Update(struct RegionalSaveSha256Context *context, struct RegionalSaveSha256Schedule *schedule, const u8 *bytes, u32 length)
{
    u32 oldLow = context->bitCountLow;
    context->bitCountLow += length << 3;
    context->bitCountHigh += (length >> 29) + (context->bitCountLow < oldLow);
    while (length)
    {
        u32 copy = min(64 - context->blockLength, length);
        memcpy(context->block + context->blockLength, bytes, copy);
        context->blockLength += copy;
        bytes += copy;
        length -= copy;
        if (context->blockLength == 64)
        {
            ShaTransform(context, schedule);
            context->blockLength = 0;
        }
    }
}

void RegionalSave_Sha256Final(struct RegionalSaveSha256Context *context, struct RegionalSaveSha256Schedule *schedule, u8 digest[32])
{
    u32 low = context->bitCountLow;
    u32 high = context->bitCountHigh;
    u32 i;
    context->block[context->blockLength++] = 0x80;
    if (context->blockLength > 56)
    {
        memset(context->block + context->blockLength, 0, 64 - context->blockLength);
        ShaTransform(context, schedule);
        context->blockLength = 0;
    }
    memset(context->block + context->blockLength, 0, 56 - context->blockLength);
    WriteBig32(context->block + 56, high);
    WriteBig32(context->block + 60, low);
    ShaTransform(context, schedule);
    for (i = 0; i < 8; i++)
        WriteBig32(digest + 4 * i, context->state[i]);
    context->blockLength = 0;
}

void RegionalSave_HashMainInit(struct RegionalSaveSha256Context *context, struct RegionalSaveSha256Schedule *schedule, const u8 *image)
{
    RegionalSave_Sha256Init(context);
    RegionalSave_Sha256Update(context, schedule, sMainDomain, sizeof(sMainDomain));
    RegionalSave_Sha256Update(context, schedule, image + REGIONAL_SAVE_HEADER_OFFSET, 28);
}

u16 RegionalSave_MainSectorSize(u16 id)
{
    if (id >= ARRAY_COUNT(sMainSectorSizes))
        return 0;
    return sMainSectorSizes[id];
}

bool8 RegionalSave_HashMainSector(struct RegionalSaveSha256Context *context, struct RegionalSaveSha256Schedule *schedule, u16 id, const u8 *payload, u16 size)
{
    u8 frame[4];
    if (id >= ARRAY_COUNT(sMainSectorSizes) || size != sMainSectorSizes[id] || payload == NULL)
        return FALSE;
    RegionalSave_Write16(frame, id);
    RegionalSave_Write16(frame + 2, size);
    RegionalSave_Sha256Update(context, schedule, frame, sizeof(frame));
    RegionalSave_Sha256Update(context, schedule, payload, size);
    return TRUE;
}

static bool8 GetBit(const u8 *image, u16 region, u16 index, u16 count, u16 offset, bool8 *value)
{
    if (image == NULL || value == NULL || region != REGIONAL_SAVE_JOHTO || index >= count)
        return FALSE;
    *value = (image[offset + (index >> 3)] >> (index & 7)) & 1;
    return TRUE;
}

static bool8 SetBit(u8 *image, u16 region, u16 index, u16 count, u16 offset, bool8 value)
{
    u8 mask;
    if (image == NULL || region != REGIONAL_SAVE_JOHTO || index >= count || value > 1)
        return FALSE;
    mask = 1 << (index & 7);
    if (value)
        image[offset + (index >> 3)] |= mask;
    else
        image[offset + (index >> 3)] &= ~mask;
    return TRUE;
}

bool8 RegionalSave_GetEvent(const u8 *image, u16 region, u16 index, bool8 *value)
{
    if (image != NULL && RegionalSave_Read32(image + REGIONAL_SAVE_CONTENT_OFFSET) == REGIONAL_SAVE_CONTENT_ID
     && index >= REGIONAL_SAVE_CAMPAIGN_EVENT_COUNT)
        return FALSE;
    return GetBit(image, region, index, REGIONAL_SAVE_EVENT_COUNT, REGIONAL_SAVE_EVENTS_OFFSET, value);
}

bool8 RegionalSave_SetEvent(u8 *image, u16 region, u16 index, bool8 value)
{
    if (image != NULL && RegionalSave_Read32(image + REGIONAL_SAVE_CONTENT_OFFSET) == REGIONAL_SAVE_CONTENT_ID
     && index >= REGIONAL_SAVE_CAMPAIGN_EVENT_COUNT)
        return FALSE;
    return SetBit(image, region, index, REGIONAL_SAVE_EVENT_COUNT, REGIONAL_SAVE_EVENTS_OFFSET, value);
}

bool8 RegionalSave_GetTrainer(const u8 *image, u16 region, u16 index, bool8 *value)
{
    return GetBit(image, region, index, REGIONAL_SAVE_TRAINER_COUNT, REGIONAL_SAVE_TRAINERS_OFFSET, value);
}

bool8 RegionalSave_SetTrainer(u8 *image, u16 region, u16 index, bool8 value)
{
    return SetBit(image, region, index, REGIONAL_SAVE_TRAINER_COUNT, REGIONAL_SAVE_TRAINERS_OFFSET, value);
}

bool8 RegionalSave_GetVar(const u8 *image, u16 region, u16 index, u16 *value)
{
    if (image == NULL || value == NULL || region != REGIONAL_SAVE_JOHTO || index >= REGIONAL_SAVE_VAR_COUNT)
        return FALSE;
    *value = RegionalSave_Read16(image + REGIONAL_SAVE_VARS_OFFSET + 2 * index);
    return TRUE;
}

bool8 RegionalSave_SetVar(u8 *image, u16 region, u16 index, u16 value)
{
    if (image == NULL || region != REGIONAL_SAVE_JOHTO || index >= REGIONAL_SAVE_VAR_COUNT)
        return FALSE;
    RegionalSave_Write16(image + REGIONAL_SAVE_VARS_OFFSET + 2 * index, value);
    return TRUE;
}
