#ifndef GUARD_REGIONS_H
#define GUARD_REGIONS_H

#include "global.h"
#include "constants/regions.h"
#include "constants/region_map_sections.h"
#include "constants/maps.h"
#include "constants/johto_map_sections.h"

enum KantoSubRegion GetKantoSubregion(u32 mapSecId);

// MapHeader has no region member. Use the exact selected map identities so
// shared Indigo/Route22/etc. sections keep their native Kanto interpretation.
static inline bool32 IsJohtoCampaignMapId(u32 mapId)
{
    u32 mapNum = MAP_NUM(mapId);

    switch (MAP_GROUP(mapId))
    {
    case MAP_GROUP(MAP_NEW_BARK_TOWN_HNS):
        return (mapNum >= MAP_NUM(MAP_NEW_BARK_TOWN_HNS) && mapNum <= MAP_NUM(MAP_ROUTE48_HNS))
            || (mapNum >= MAP_NUM(MAP_ROUTE22_HNS) && mapNum <= MAP_NUM(MAP_INDIGO_PLATEAU_HNS))
            || (mapNum >= MAP_NUM(MAP_ROUTE26_HNS) && mapNum <= MAP_NUM(MAP_ROUTE28_HNS));
    case MAP_GROUP(MAP_NEW_BARK_TOWN_LAB_HNS):
        return (mapNum >= MAP_NUM(MAP_NEW_BARK_TOWN_LAB_HNS) && mapNum <= MAP_NUM(MAP_NEW_BARK_TOWN_PLAYERS_HOUSE_2F_HNS));
    case MAP_GROUP(MAP_CHERRYGROVE_CITY_POKEMON_CENTER_HNS):
        return (mapNum >= MAP_NUM(MAP_CHERRYGROVE_CITY_POKEMON_CENTER_HNS) && mapNum <= MAP_NUM(MAP_CHERRYGROVE_CITY_HOUSE3_HNS));
    case MAP_GROUP(MAP_VIOLET_CITY_POKEMON_CENTER_HNS):
        return (mapNum >= MAP_NUM(MAP_VIOLET_CITY_POKEMON_CENTER_HNS) && mapNum <= MAP_NUM(MAP_VIOLET_CITY_GYM_HNS));
    case MAP_GROUP(MAP_AZALEA_TOWN_POKEMON_CENTER_HNS):
        return (mapNum >= MAP_NUM(MAP_AZALEA_TOWN_POKEMON_CENTER_HNS) && mapNum <= MAP_NUM(MAP_AZALEA_TOWN_GYM_HNS));
    case MAP_GROUP(MAP_GOLDENROD_CITY_POKEMON_CENTER_HNS):
        return (mapNum >= MAP_NUM(MAP_GOLDENROD_CITY_POKEMON_CENTER_HNS) && mapNum <= MAP_NUM(MAP_GOLDENROD_CITY_DEPARTMENT_STORE_ELEVATOR_HNS));
    case MAP_GROUP(MAP_ECRUTEAK_CITY_POKEMON_CENTER_HNS):
        return (mapNum >= MAP_NUM(MAP_ECRUTEAK_CITY_POKEMON_CENTER_HNS) && mapNum <= MAP_NUM(MAP_ECRUTEAK_CITY_GYM_HNS));
    case MAP_GROUP(MAP_OLIVINE_CITY_POKEMON_CENTER_HNS):
        return (mapNum >= MAP_NUM(MAP_OLIVINE_CITY_POKEMON_CENTER_HNS) && mapNum <= MAP_NUM(MAP_OLIVINE_CITY_LIGHTHOUSE_HNS));
    case MAP_GROUP(MAP_CIANWOOD_POKECENTER_HNS):
        return (mapNum >= MAP_NUM(MAP_CIANWOOD_POKECENTER_HNS) && mapNum <= MAP_NUM(MAP_CIANWOOD_GYM_HNS));
    case MAP_GROUP(MAP_MAHOGANY_TOWN_POKEMON_CENTER_HNS):
        return (mapNum >= MAP_NUM(MAP_MAHOGANY_TOWN_POKEMON_CENTER_HNS) && mapNum <= MAP_NUM(MAP_LAKE_OF_RAGE_HOUSE2_HNS));
    case MAP_GROUP(MAP_BLACKTHORN_CITY_POKEMON_CENTER_HNS):
        return (mapNum >= MAP_NUM(MAP_BLACKTHORN_CITY_POKEMON_CENTER_HNS) && mapNum <= MAP_NUM(MAP_BLACKTHORN_CITY_HOUSE3_HNS));
    case MAP_GROUP(MAP_INDIGO_PLATEAU_POKEMON_CENTER_HNS):
        return (mapNum >= MAP_NUM(MAP_INDIGO_PLATEAU_POKEMON_CENTER_HNS) && mapNum <= MAP_NUM(MAP_POKEMON_LEAGUE_HALL_OF_FAME_HNS));
    case MAP_GROUP(MAP_GATE_ROUTE29_ROUTE46_HNS):
        return (mapNum >= MAP_NUM(MAP_GATE_ROUTE29_ROUTE46_HNS) && mapNum <= MAP_NUM(MAP_MT_SILVER_POKEMON_CENTER_HNS));
    case MAP_GROUP(MAP_ROUTE26_HOUSE1_HNS):
        return (mapNum >= MAP_NUM(MAP_ROUTE26_HOUSE1_HNS) && mapNum <= MAP_NUM(MAP_ROUTE26_HOUSE2_HNS));
    case MAP_GROUP(MAP_DARK_CAVE_SOUTH_SIDE_HNS):
        return (mapNum >= MAP_NUM(MAP_DARK_CAVE_SOUTH_SIDE_HNS) && mapNum <= MAP_NUM(MAP_VICTORY_ROAD_KANTO_1F_HNS))
            || (mapNum >= MAP_NUM(MAP_MT_SILVER_OUTSIDE_HNS) && mapNum <= MAP_NUM(MAP_RUINS_OF_ALPH_WORDS_ROOM4_HNS));
    case MAP_GROUP(MAP_SNOWSWEPT_CAVERN_HNS):
        return (mapNum >= MAP_NUM(MAP_SNOWSWEPT_CAVERN_HNS) && mapNum <= MAP_NUM(MAP_SINJOH_RUINS_HNS));
    case MAP_GROUP(MAP_NEW_SINJOH_POKEMON_CENTER_HNS):
        return (mapNum >= MAP_NUM(MAP_NEW_SINJOH_POKEMON_CENTER_HNS) && mapNum <= MAP_NUM(MAP_SINJOH_RUINS_HOUSE1_HNS));
    case MAP_GROUP(MAP_TRAINER_HILL_COURTYARD_HNS):
        return (mapNum >= MAP_NUM(MAP_TRAINER_HILL_COURTYARD_HNS) && mapNum <= MAP_NUM(MAP_SAFARI_ZONE_TOP_RIGHT_HNS))
            || (mapNum >= MAP_NUM(MAP_TEST_MAP1_HNS) && mapNum <= MAP_NUM(MAP_BATTLE_FRONTIER_MART_HNS))
            || (mapNum >= MAP_NUM(MAP_TRADE_CENTER_HNS) && mapNum <= MAP_NUM(MAP_BATTLE_COLOSSEUM_2P_HNS));
    case MAP_GROUP(MAP_ARTISAN_CAVE_B1F):
        return (mapNum >= MAP_NUM(MAP_ARTISAN_CAVE_B1F) && mapNum <= MAP_NUM(MAP_ARTISAN_CAVE_1F));
    case MAP_GROUP(MAP_TRADE_CENTER):
        return mapNum == MAP_NUM(MAP_TRADE_CENTER)
            || mapNum == MAP_NUM(MAP_UNION_ROOM)
            || (mapNum >= MAP_NUM(MAP_BATTLE_PYRAMID_SQUARE01_HNS) && mapNum <= MAP_NUM(MAP_BATTLE_PYRAMID_SQUARE16_HNS));
    default:
        return FALSE;
    }
}

static inline bool32 IsJohtoCampaignMap(void)
{
    return IsJohtoCampaignMapId(((u8)gSaveBlock1Ptr->location.mapGroup << 8)
                               | (u8)gSaveBlock1Ptr->location.mapNum);
}

// Optional HnS side areas retain their original Hoenn geography. Campaign
// persistence/quest ownership still uses the complete identity registry above.
static inline bool32 IsJohtoMainlandMap(void)
{
    if (!IsJohtoCampaignMap())
        return FALSE;
    switch (gMapHeader.regionMapSectionId)
    {
    case MAPSEC_BATTLE_FRONTIER:
    case MAPSEC_SOUTHERN_ISLAND:
    case MAPSEC_BIRTH_ISLAND:
    case MAPSEC_FARAWAY_ISLAND:
    case MAPSEC_ARTISAN_CAVE:
        return FALSE;
    default:
        return TRUE;
    }
}



static inline enum Region GetRegionForSectionId(u32 sectionId)
{
    // Only distinct Johto IDs classify without a current map context.
    if (JOHTO_MAPSEC_IS_DISTINCT(sectionId))
        return REGION_JOHTO;
    if (sectionId >= KANTO_MAPSEC_START && sectionId < MAPSEC_SPECIAL_AREA)
        return REGION_KANTO;
    return REGION_HOENN;
}

static inline enum Region GetCurrentRegion(void)
{
    if (IsJohtoCampaignMap())
        return REGION_JOHTO;
    return GetRegionForSectionId(gMapHeader.regionMapSectionId);
}

#endif // GUARD_REGIONS_H
