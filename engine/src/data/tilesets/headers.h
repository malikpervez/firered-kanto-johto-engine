#include "fieldmap.h"

// Whether a palette has a night version, located at ((x + 9) % 16).pal
#define SWAP_PAL(x) ((x) < NUM_PALS_IN_PRIMARY ? 1 << (x) : 1 << ((x) - NUM_PALS_IN_PRIMARY))

const struct Tileset gTileset_SecretBase = {0};

const struct Tileset gTileset_SecretBaseRedCave = {0};

const struct Tileset *const gTilesetPointer_SecretBase = &gTileset_SecretBase;
const struct Tileset *const gTilesetPointer_SecretBaseRedCave = &gTileset_SecretBaseRedCave;

const struct Tileset gTileset_General = {0};

const struct Tileset gTileset_Building =
{
    .isCompressed = TRUE,
    .isSecondary = FALSE,
    .tiles = gTilesetTiles_InsideBuilding,
    .palettes = gTilesetPalettes_InsideBuilding,
    .metatiles = gMetatiles_InsideBuilding,
    .metatileAttributes = gMetatileAttributes_InsideBuilding,
    .callback = InitTilesetAnim_Building,
};

const struct Tileset gTileset_TrainerHill = {0};

const struct Tileset gTileset_BattleTent = {0};

const struct Tileset gTileset_Rustboro =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Rustboro,
    .palettes = gTilesetPalettes_Rustboro,
    .metatiles = gMetatiles_Rustboro,
    .metatileAttributes = gMetatileAttributes_Rustboro,
    .callback = InitTilesetAnim_Rustboro,
};

const struct Tileset gTileset_Dewford =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Dewford,
    .palettes = gTilesetPalettes_Dewford,
    .metatiles = gMetatiles_Dewford,
    .metatileAttributes = gMetatileAttributes_Dewford,
    .callback = InitTilesetAnim_Dewford,
};

const struct Tileset gTileset_Fortree =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Fortree,
    .palettes = gTilesetPalettes_Fortree,
    .metatiles = gMetatiles_Fortree,
    .metatileAttributes = gMetatileAttributes_Fortree,
    .callback = InitTilesetAnim_Fortree,
};

const struct Tileset gTileset_IslandHarbor =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_IslandHarbor,
    .palettes = gTilesetPalettes_IslandHarbor,
    .metatiles = gMetatiles_IslandHarbor,
    .metatileAttributes = gMetatileAttributes_IslandHarbor,
    .callback = NULL,
};

const struct Tileset gTileset_BattleFrontierOutsideWest = {0};

const struct Tileset gTileset_BattleFrontierOutsideEast = {0};

const struct Tileset gTileset_PokemonCenter = {0};

const struct Tileset gTileset_Shop = {0};

const struct Tileset gTileset_BattleFrontier = {0};

const struct Tileset gTileset_BattlePalace = {0};

const struct Tileset gTileset_BattleDome = {0};

const struct Tileset gTileset_BattleFactory = {0};

const struct Tileset gTileset_BattlePike = {0};

const struct Tileset gTileset_BattleArena = {0};

const struct Tileset gTileset_BattlePyramid = {0};

const struct Tileset gTileset_BattleFrontierRankingHall = {0};


const struct Tileset gTileset_CableClub =
{
    .isCompressed = FALSE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_CableClub,
    .palettes = gTilesetPalettes_CableClub,
    .metatiles = gMetatiles_CableClub,
    .metatileAttributes = gMetatileAttributes_CableClub,
    .callback = NULL,
};

const struct Tileset gTileset_Lab_Frlg =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Lab_Frlg,
    .palettes = gTilesetPalettes_Lab_Frlg,
    .metatiles = gMetatiles_Lab_Frlg,
    .metatileAttributes = gMetatileAttributes_Lab_Frlg,
    .callback = NULL,
};


// FRLG tilesets
const struct Tileset gTileset_BuildingFrlg =
{
    .isCompressed = TRUE,
    .isSecondary = FALSE,
    .tiles = gTilesetTiles_Building_Frlg,
    .palettes = gTilesetPalettes_Building_Frlg,
    .metatiles = gMetatiles_Building_Frlg,
    .metatileAttributes = gMetatileAttributes_Building_Frlg,
    .callback = NULL,
};

const struct Tileset gTileset_General_Frlg =
{
    .isCompressed = TRUE,
    .isSecondary = FALSE,
    .tiles = gTilesetTiles_General_Frlg,
    .palettes = gTilesetPalettes_General_Frlg,
    .metatiles = gMetatiles_General_Frlg,
    .metatileAttributes = gMetatileAttributes_General_Frlg,
    .callback = InitTilesetAnim_General_Frlg,
};

const struct Tileset gTileset_PalletTown =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_PalletTown,
    .palettes = gTilesetPalettes_PalletTown,
    .metatiles = gMetatiles_PalletTown,
    .metatileAttributes = gMetatileAttributes_PalletTown,
    .callback = NULL,
};

const struct Tileset gTileset_ViridianCity =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_ViridianCity,
    .palettes = gTilesetPalettes_ViridianCity,
    .metatiles = gMetatiles_ViridianCity,
    .metatileAttributes = gMetatileAttributes_ViridianCity,
    .callback = NULL,
};

const struct Tileset gTileset_PewterCity =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_PewterCity,
    .palettes = gTilesetPalettes_PewterCity,
    .metatiles = gMetatiles_PewterCity,
    .metatileAttributes = gMetatileAttributes_PewterCity,
    .callback = NULL,
};

const struct Tileset gTileset_CeruleanCity =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_CeruleanCity,
    .palettes = gTilesetPalettes_CeruleanCity,
    .metatiles = gMetatiles_CeruleanCity,
    .metatileAttributes = gMetatileAttributes_CeruleanCity,
    .callback = NULL,
};

const struct Tileset gTileset_LavenderTown =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_LavenderTown,
    .palettes = gTilesetPalettes_LavenderTown,
    .metatiles = gMetatiles_LavenderTown,
    .metatileAttributes = gMetatileAttributes_LavenderTown,
    .callback = NULL,
};

const struct Tileset gTileset_VermilionCity =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_VermilionCity,
    .palettes = gTilesetPalettes_VermilionCity,
    .metatiles = gMetatiles_VermilionCity,
    .metatileAttributes = gMetatileAttributes_VermilionCity,
    .callback = NULL,
};

const struct Tileset gTileset_CeladonCity =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_CeladonCity,
    .palettes = gTilesetPalettes_CeladonCity,
    .metatiles = gMetatiles_CeladonCity,
    .metatileAttributes = gMetatileAttributes_CeladonCity,
    .callback = InitTilesetAnim_CeladonCity,
};

const struct Tileset gTileset_FuchsiaCity =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_FuchsiaCity,
    .palettes = gTilesetPalettes_FuchsiaCity,
    .metatiles = gMetatiles_FuchsiaCity,
    .metatileAttributes = gMetatileAttributes_FuchsiaCity,
    .callback = NULL,
};

const struct Tileset gTileset_CinnabarIsland =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_CinnabarIsland,
    .palettes = gTilesetPalettes_CinnabarIsland,
    .metatiles = gMetatiles_CinnabarIsland,
    .metatileAttributes = gMetatileAttributes_CinnabarIsland,
    .callback = NULL,
};

const struct Tileset gTileset_IndigoPlateau =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_IndigoPlateau,
    .palettes = gTilesetPalettes_IndigoPlateau,
    .metatiles = gMetatiles_IndigoPlateau,
    .metatileAttributes = gMetatileAttributes_IndigoPlateau,
    .callback = NULL,
};

const struct Tileset gTileset_SaffronCity =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_SaffronCity,
    .palettes = gTilesetPalettes_SaffronCity,
    .metatiles = gMetatiles_SaffronCity,
    .metatileAttributes = gMetatileAttributes_SaffronCity,
    .callback = NULL,
};

const struct Tileset gTileset_Mart =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Mart,
    .palettes = gTilesetPalettes_Mart,
    .metatiles = gMetatiles_Mart,
    .metatileAttributes = gMetatileAttributes_Mart,
    .callback = NULL,
};

const struct Tileset gTileset_PokemonCenterFrlg =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_PokemonCenter_Frlg,
    .palettes = gTilesetPalettes_PokemonCenter_Frlg,
    .metatiles = gMetatiles_PokemonCenter_Frlg,
    .metatileAttributes = gMetatileAttributes_PokemonCenter_Frlg,
    .callback = NULL,
};

const struct Tileset gTileset_Cave_Frlg =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Cave_Frlg,
    .palettes = gTilesetPalettes_Cave_Frlg,
    .metatiles = gMetatiles_Cave_Frlg,
    .metatileAttributes = gMetatileAttributes_Cave_Frlg,
    .callback = NULL,
};

const struct Tileset gTileset_Museum =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Museum,
    .palettes = gTilesetPalettes_Museum,
    .metatiles = gMetatiles_Museum,
    .metatileAttributes = gMetatileAttributes_Museum,
    .callback = NULL,
};

const struct Tileset gTileset_CableClub_Frlg =
{
    .isCompressed = FALSE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_CableClub_Frlg,
    .palettes = gTilesetPalettes_CableClub_Frlg,
    .metatiles = gMetatiles_CableClub_Frlg,
    .metatileAttributes = gMetatileAttributes_CableClub_Frlg,
    .callback = NULL,
};

const struct Tileset gTileset_BikeShop_Frlg = {0};

const struct Tileset gTileset_GenericBuilding1 =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_GenericBuilding1,
    .palettes = gTilesetPalettes_GenericBuilding1,
    .metatiles = gMetatiles_GenericBuilding1,
    .metatileAttributes = gMetatileAttributes_GenericBuilding1,
    .callback = NULL,
};

const struct Tileset gTileset_FuchsiaGym = {0};

const struct Tileset gTileset_ViridianGym =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_ViridianGym,
    .palettes = gTilesetPalettes_ViridianGym,
    .metatiles = gMetatiles_ViridianGym,
    .metatileAttributes = gMetatileAttributes_ViridianGym,
    .callback = NULL,
};

const struct Tileset gTileset_HoennBuilding =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_HoennBuilding,
    .palettes = gTilesetPalettes_HoennBuilding,
    .metatiles = gMetatiles_HoennBuilding,
    .metatileAttributes = gMetatileAttributes_HoennBuilding,
    .callback = NULL,
};

const struct Tileset gTileset_GameCorner =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_GameCorner,
    .palettes = gTilesetPalettes_GameCorner,
    .metatiles = gMetatiles_GameCorner,
    .metatileAttributes = gMetatileAttributes_GameCorner,
    .callback = NULL,
};

const struct Tileset gTileset_PewterGym = {0};

const struct Tileset gTileset_CeruleanGym = {0};

const struct Tileset gTileset_VermilionGym =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_VermilionGym,
    .palettes = gTilesetPalettes_VermilionGym,
    .metatiles = gMetatiles_VermilionGym,
    .metatileAttributes = gMetatileAttributes_VermilionGym,
    .callback = InitTilesetAnim_VermilionGym,
};

const struct Tileset gTileset_CeladonGym = {0};

const struct Tileset gTileset_SaffronGym = {0};

const struct Tileset gTileset_CinnabarGym =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_CinnabarGym,
    .palettes = gTilesetPalettes_CinnabarGym,
    .metatiles = gMetatiles_CinnabarGym,
    .metatileAttributes = gMetatileAttributes_CinnabarGym,
    .callback = NULL,
};

const struct Tileset gTileset_SSAnne =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_SSAnne,
    .palettes = gTilesetPalettes_SSAnne,
    .metatiles = gMetatiles_SSAnne,
    .metatileAttributes = gMetatileAttributes_SSAnne,
    .callback = NULL,
};

const struct Tileset gTileset_ViridianForest =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_ViridianForest,
    .palettes = gTilesetPalettes_ViridianForest,
    .metatiles = gMetatiles_ViridianForest,
    .metatileAttributes = gMetatileAttributes_ViridianForest,
    .callback = NULL,
};


const struct Tileset gTileset_RockTunnel =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_RockTunnel,
    .palettes = gTilesetPalettes_RockTunnel,
    .metatiles = gMetatiles_RockTunnel,
    .metatileAttributes = gMetatileAttributes_RockTunnel,
    .callback = NULL,
};

const struct Tileset gTileset_DiglettsCave =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_DiglettsCave,
    .palettes = gTilesetPalettes_DiglettsCave,
    .metatiles = gMetatiles_DiglettsCave,
    .metatileAttributes = gMetatileAttributes_DiglettsCave,
    .callback = NULL,
};

const struct Tileset gTileset_SeafoamIslands =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_SeafoamIslands,
    .palettes = gTilesetPalettes_SeafoamIslands,
    .metatiles = gMetatiles_SeafoamIslands,
    .metatileAttributes = gMetatileAttributes_SeafoamIslands,
    .callback = NULL,
};


const struct Tileset gTileset_CeruleanCave = {0};

const struct Tileset gTileset_DepartmentStore = {0};

const struct Tileset gTileset_GenericBuilding2 =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_GenericBuilding2,
    .palettes = gTilesetPalettes_GenericBuilding2,
    .metatiles = gMetatiles_GenericBuilding2,
    .metatileAttributes = gMetatileAttributes_GenericBuilding2,
    .callback = NULL,
};

const struct Tileset gTileset_PowerPlant =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_PowerPlant,
    .palettes = gTilesetPalettes_PowerPlant,
    .metatiles = gMetatiles_PowerPlant,
    .metatileAttributes = gMetatileAttributes_PowerPlant,
    .callback = NULL,
};

const struct Tileset gTileset_SeaCottage =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_SeaCottage,
    .palettes = gTilesetPalettes_SeaCottage,
    .metatiles = gMetatiles_SeaCottage,
    .metatileAttributes = gMetatileAttributes_SeaCottage,
    .callback = NULL,
};

const struct Tileset gTileset_SilphCo =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Condominiums,
    .palettes = gTilesetPalettes_Condominiums,
    .metatiles = gMetatiles_SilphCo,
    .metatileAttributes = gMetatileAttributes_SilphCo,
    .callback = InitTilesetAnim_SilphCo,
};

const struct Tileset gTileset_UndergroundPath = {0};

const struct Tileset gTileset_PokemonTower =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_PokemonTower,
    .palettes = gTilesetPalettes_PokemonTower,
    .metatiles = gMetatiles_PokemonTower,
    .metatileAttributes = gMetatileAttributes_PokemonTower,
    .callback = NULL,
};

const struct Tileset gTileset_SafariZoneBuilding =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_SafariZoneBuilding,
    .palettes = gTilesetPalettes_SafariZoneBuilding,
    .metatiles = gMetatiles_SafariZoneBuilding,
    .metatileAttributes = gMetatileAttributes_SafariZoneBuilding,
    .callback = NULL,
};

const struct Tileset gTileset_PokemonMansion =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_PokemonMansion,
    .palettes = gTilesetPalettes_PokemonMansion,
    .metatiles = gMetatiles_PokemonMansion,
    .metatileAttributes = gMetatileAttributes_PokemonMansion,
    .callback = NULL,
};

const struct Tileset gTileset_RestaurantHotel =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_RestaurantHotel,
    .palettes = gTilesetPalettes_RestaurantHotel,
    .metatiles = gMetatiles_RestaurantHotel,
    .metatileAttributes = gMetatileAttributes_RestaurantHotel,
    .callback = NULL,
};

const struct Tileset gTileset_School =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_School,
    .palettes = gTilesetPalettes_School,
    .metatiles = gMetatiles_School,
    .metatileAttributes = gMetatileAttributes_School,
    .callback = NULL,
};

const struct Tileset gTileset_FanClubDaycare =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_FanClubDaycare,
    .palettes = gTilesetPalettes_FanClubDaycare,
    .metatiles = gMetatiles_FanClubDaycare,
    .metatileAttributes = gMetatileAttributes_FanClubDaycare,
    .callback = NULL,
};

const struct Tileset gTileset_Condominiums =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Condominiums,
    .palettes = gTilesetPalettes_Condominiums,
    .metatiles = gMetatiles_Condominiums,
    .metatileAttributes = gMetatileAttributes_Condominiums,
    .callback = NULL,
};

const struct Tileset gTileset_BurgledHouse =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_BurgledHouse,
    .palettes = gTilesetPalettes_BurgledHouse,
    .metatiles = gMetatiles_BurgledHouse,
    .metatileAttributes = gMetatileAttributes_BurgledHouse,
    .callback = NULL,
};

const struct Tileset gTileset_MtEmber =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_MtEmber,
    .palettes = gTilesetPalettes_MtEmber,
    .metatiles = gMetatiles_MtEmber,
    .metatileAttributes = gMetatileAttributes_MtEmber,
    .callback = InitTilesetAnim_MtEmber,
};

const struct Tileset gTileset_BerryForest =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_BerryForest,
    .palettes = gTilesetPalettes_BerryForest,
    .metatiles = gMetatiles_BerryForest,
    .metatileAttributes = gMetatileAttributes_BerryForest,
    .callback = NULL,
};

const struct Tileset gTileset_NavelRock_Frlg =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_NavelRock_Frlg,
    .palettes = gTilesetPalettes_NavelRock_Frlg,
    .metatiles = gMetatiles_NavelRock_Frlg,
    .metatileAttributes = gMetatileAttributes_NavelRock_Frlg,
    .callback = NULL,
};

const struct Tileset gTileset_TanobyRuins =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_TanobyRuins,
    .palettes = gTilesetPalettes_TanobyRuins,
    .metatiles = gMetatiles_TanobyRuins,
    .metatileAttributes = gMetatileAttributes_TanobyRuins,
    .callback = NULL,
};

const struct Tileset gTileset_SeviiIslands123 =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_SeviiIslands123,
    .palettes = gTilesetPalettes_SeviiIslands123,
    .metatiles = gMetatiles_SeviiIslands123,
    .metatileAttributes = gMetatileAttributes_SeviiIslands123,
    .callback = NULL,
};

const struct Tileset gTileset_SeviiIslands45 =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_SeviiIslands45,
    .palettes = gTilesetPalettes_SeviiIslands45,
    .metatiles = gMetatiles_SeviiIslands45,
    .metatileAttributes = gMetatileAttributes_SeviiIslands45,
    .callback = NULL,
};

const struct Tileset gTileset_SeviiIslands67 =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_SeviiIslands67,
    .palettes = gTilesetPalettes_SeviiIslands67,
    .metatiles = gMetatiles_SeviiIslands67,
    .metatileAttributes = gMetatileAttributes_SeviiIslands67,
    .callback = NULL,
};

const struct Tileset gTileset_TrainerTower =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_TrainerTower,
    .palettes = gTilesetPalettes_TrainerTower,
    .metatiles = gMetatiles_TrainerTower,
    .metatileAttributes = gMetatileAttributes_TrainerTower,
    .callback = NULL,
};

const struct Tileset gTileset_IslandHarbor_Frlg =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_IslandHarbor_Frlg,
    .palettes = gTilesetPalettes_IslandHarbor_Frlg,
    .metatiles = gMetatiles_IslandHarbor_Frlg,
    .metatileAttributes = gMetatileAttributes_IslandHarbor_Frlg,
    .callback = NULL,
};

const struct Tileset gTileset_PokemonLeague =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_PokemonLeague,
    .palettes = gTilesetPalettes_PokemonLeague,
    .metatiles = gMetatiles_PokemonLeague,
    .metatileAttributes = gMetatileAttributes_PokemonLeague,
    .callback = NULL,
};

const struct Tileset gTileset_HallOfFame =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_HallOfFame,
    .palettes = gTilesetPalettes_HallOfFame,
    .metatiles = gMetatiles_HallOfFame,
    .metatileAttributes = gMetatileAttributes_HallOfFame,
    .callback = NULL,
};


// Campaign: exact upstream tileset dependencies of selected Johto maps.

const struct Tileset gTileset_ArceusRoom_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_ArceusRoom_Hns,
    .palettes = gTilesetPalettes_ArceusRoom_Hns,
    .metatiles = gMetatiles_ArceusRoom_Hns,
    .metatileAttributes = gMetatileAttributes_ArceusRoom_Hns,
    .callback = NULL,
};

const struct Tileset gTileset_AzaleaTown_Gym_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_AzaleaTown_Gym_Hns,
    .palettes = gTilesetPalettes_AzaleaTown_Gym_Hns,
    .metatiles = gMetatiles_AzaleaTown_Gym_Hns,
    .metatileAttributes = gMetatileAttributes_AzaleaTown_Gym_Hns,
    .callback = InitTilesetAnim_AzaleaTownGym,
};

const struct Tileset gTileset_AzaleaTown_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_AzaleaTown_Hns,
    .palettes = gTilesetPalettes_AzaleaTown_Hns,
    .metatiles = gMetatiles_AzaleaTown_Hns,
    .metatileAttributes = gMetatileAttributes_AzaleaTown_Hns,
    .callback = NULL,
};

const struct Tileset gTileset_Barn_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Barn_Hns,
    .palettes = gTilesetPalettes_Barn_Hns,
    .metatiles = gMetatiles_Barn_Hns,
    .metatileAttributes = gMetatileAttributes_Barn_Hns,
    .callback = NULL,
};

const struct Tileset gTileset_BellchimeTrail_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_BellchimeTrail_Hns,
    .palettes = gTilesetPalettes_BellchimeTrail_Hns,
    .metatiles = gMetatiles_BellchimeTrail_Hns,
    .metatileAttributes = gMetatileAttributes_BellchimeTrail_Hns,
    .callback = NULL,
};

const struct Tileset gTileset_BikeShop_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_BikeShop_Hns,
    .palettes = gTilesetPalettes_BikeShop_Hns,
    .metatiles = gMetatiles_BikeShop_Hns,
    .metatileAttributes = gMetatileAttributes_BikeShop_Hns,
    .callback = NULL,
};

const struct Tileset gTileset_BlackthornGym_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_BlackthornGym_Hns,
    .palettes = gTilesetPalettes_BlackthornGym_Hns,
    .metatiles = gMetatiles_BlackthornGym_Hns,
    .metatileAttributes = gMetatileAttributes_BlackthornGym_Hns,
    .callback = InitTilesetAnim_BlackthornGym,
};

const struct Tileset gTileset_Blackthorn_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Blackthorn_Hns,
    .palettes = gTilesetPalettes_Blackthorn_Hns,
    .metatiles = gMetatiles_Blackthorn_Hns,
    .metatileAttributes = gMetatileAttributes_Blackthorn_Hns,
    .callback = NULL,
};

const struct Tileset gTileset_BurnedTower_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_BurnedTower_Hns,
    .palettes = gTilesetPalettes_BurnedTower_Hns,
    .metatiles = gMetatiles_BurnedTower_Hns,
    .metatileAttributes = gMetatileAttributes_BurnedTower_Hns,
    .callback = NULL,
};

const struct Tileset gTileset_Cafe_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Cafe_Hns,
    .palettes = gTilesetPalettes_Cafe_Hns,
    .metatiles = gMetatiles_Cafe_Hns,
    .metatileAttributes = gMetatileAttributes_Cafe_Hns,
    .callback = NULL,
};

const struct Tileset gTileset_Cave_Default_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Cave_Default_Hns,
    .palettes = gTilesetPalettes_Cave_Default_Hns,
    .metatiles = gMetatiles_Cave_Default_Hns,
    .metatileAttributes = gMetatileAttributes_Cave_Default_Hns,
    .callback = NULL,
};

const struct Tileset gTileset_Cave_DragonsDen_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Cave_DragonsDen_Hns,
    .palettes = gTilesetPalettes_Cave_DragonsDen_Hns,
    .metatiles = gMetatiles_Cave_DragonsDen_Hns,
    .metatileAttributes = gMetatileAttributes_Cave_DragonsDen_Hns,
    .callback = NULL,
};

const struct Tileset gTileset_Cave_Gray_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Cave_Gray_Hns,
    .palettes = gTilesetPalettes_Cave_Gray_Hns,
    .metatiles = gMetatiles_Cave_Gray_Hns,
    .metatileAttributes = gMetatileAttributes_Cave_Gray_Hns,
    .callback = NULL,
};

const struct Tileset gTileset_Cave_Ice_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Cave_Ice_Hns,
    .palettes = gTilesetPalettes_Cave_Ice_Hns,
    .metatiles = gMetatiles_Cave_Ice_Hns,
    .metatileAttributes = gMetatileAttributes_Cave_Ice_Hns,
    .callback = NULL,
};

const struct Tileset gTileset_CherrygroveCity_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_CherrygroveCity_Hns,
    .palettes = gTilesetPalettes_CherrygroveCity_Hns,
    .metatiles = gMetatiles_CherrygroveCity_Hns,
    .metatileAttributes = gMetatileAttributes_CherrygroveCity_Hns,
    .callback = NULL,
};

const struct Tileset gTileset_CianwoodCity_Gym_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_CianwoodCity_Gym_Hns,
    .palettes = gTilesetPalettes_CianwoodCity_Gym_Hns,
    .metatiles = gMetatiles_CianwoodCity_Gym_Hns,
    .metatileAttributes = gMetatileAttributes_CianwoodCity_Gym_Hns,
    .callback = NULL,
};

const struct Tileset gTileset_CianwoodCity_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_CianwoodCity_Hns,
    .palettes = gTilesetPalettes_CianwoodCity_Hns,
    .metatiles = gMetatiles_CianwoodCity_Hns,
    .metatileAttributes = gMetatileAttributes_CianwoodCity_Hns,
    .callback = NULL,
};

const struct Tileset gTileset_DepartmentStore_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_DepartmentStore_Hns,
    .palettes = gTilesetPalettes_DepartmentStore_Hns,
    .metatiles = gMetatiles_DepartmentStore_Hns,
    .metatileAttributes = gMetatileAttributes_DepartmentStore_Hns,
    .callback = NULL,
};

const struct Tileset gTileset_DragonsDen_Shrine_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_DragonsDen_Shrine_Hns,
    .palettes = gTilesetPalettes_DragonsDen_Shrine_Hns,
    .metatiles = gMetatiles_DragonsDen_Shrine_Hns,
    .metatileAttributes = gMetatileAttributes_DragonsDen_Shrine_Hns,
    .callback = NULL,
};

const struct Tileset gTileset_EcruteakCity_Gym_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_EcruteakCity_Gym_Hns,
    .palettes = gTilesetPalettes_EcruteakCity_Gym_Hns,
    .metatiles = gMetatiles_EcruteakCity_Gym_Hns,
    .metatileAttributes = gMetatileAttributes_EcruteakCity_Gym_Hns,
    .callback = NULL,
};

const struct Tileset gTileset_EcruteakTheater_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_EcruteakTheater_Hns,
    .palettes = gTilesetPalettes_EcruteakTheater_Hns,
    .metatiles = gMetatiles_EcruteakTheater_Hns,
    .metatileAttributes = gMetatileAttributes_EcruteakTheater_Hns,
    .callback = InitTilesetAnim_EcruteakTheater,
};

const struct Tileset gTileset_Ecruteak_City_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Ecruteak_City_Hns,
    .palettes = gTilesetPalettes_Ecruteak_City_Hns,
    .metatiles = gMetatiles_Ecruteak_City_Hns,
    .metatileAttributes = gMetatileAttributes_Ecruteak_City_Hns,
    .callback = NULL,
};

const struct Tileset gTileset_GameCorner_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_GameCorner_Hns,
    .palettes = gTilesetPalettes_GameCorner_Hns,
    .metatiles = gMetatiles_GameCorner_Hns,
    .metatileAttributes = gMetatileAttributes_GameCorner_Hns,
    .callback = NULL,
};

const struct Tileset gTileset_Gate_Standard_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Gate_Standard_Hns,
    .palettes = gTilesetPalettes_Gate_Standard_Hns,
    .metatiles = gMetatiles_Gate_Standard_Hns,
    .metatileAttributes = gMetatileAttributes_Gate_Standard_Hns,
    .callback = NULL,
};

const struct Tileset gTileset_GoldenrodCity_TrainStation_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_GoldenrodCity_TrainStation_Hns,
    .palettes = gTilesetPalettes_GoldenrodCity_TrainStation_Hns,
    .metatiles = gMetatiles_GoldenrodCity_TrainStation_Hns,
    .metatileAttributes = gMetatileAttributes_GoldenrodCity_TrainStation_Hns,
    .callback = NULL,
};

const struct Tileset gTileset_GoldenrodUndergroundRocket_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_GoldenrodUndergroundRocket_Hns,
    .palettes = gTilesetPalettes_GoldenrodUndergroundRocket_Hns,
    .metatiles = gMetatiles_GoldenrodUndergroundRocket_Hns,
    .metatileAttributes = gMetatileAttributes_GoldenrodUndergroundRocket_Hns,
    .callback = NULL,
};

const struct Tileset gTileset_GoldenrodUndergroundTunnel_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_GoldenrodUndergroundTunnel_Hns,
    .palettes = gTilesetPalettes_GoldenrodUndergroundTunnel_Hns,
    .metatiles = gMetatiles_GoldenrodUndergroundTunnel_Hns,
    .metatileAttributes = gMetatileAttributes_GoldenrodUndergroundTunnel_Hns,
    .callback = NULL,
};

const struct Tileset gTileset_Goldenrod_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Goldenrod_Hns,
    .palettes = gTilesetPalettes_Goldenrod_Hns,
    .metatiles = gMetatiles_Goldenrod_Hns,
    .metatileAttributes = gMetatileAttributes_Goldenrod_Hns,
    .callback = NULL,
};

const struct Tileset gTileset_Goldenrod_Underground_Storage_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Goldenrod_Underground_Storage_Hns,
    .palettes = gTilesetPalettes_Goldenrod_Underground_Storage_Hns,
    .metatiles = gMetatiles_Goldenrod_Underground_Storage_Hns,
    .metatileAttributes = gMetatileAttributes_Goldenrod_Underground_Storage_Hns,
    .callback = NULL,
};

const struct Tileset gTileset_HallOfFame_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_HallOfFame_Hns,
    .palettes = gTilesetPalettes_HallOfFame_Hns,
    .metatiles = gMetatiles_HallOfFame_Hns,
    .metatileAttributes = gMetatileAttributes_HallOfFame_Hns,
    .callback = NULL,
};

const struct Tileset gTileset_House_2_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_House_2_Hns,
    .palettes = gTilesetPalettes_House_2_Hns,
    .metatiles = gMetatiles_House_2_Hns,
    .metatileAttributes = gMetatileAttributes_House_2_Hns,
    .callback = NULL,
};

const struct Tileset gTileset_House_Lab_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_House_Lab_Hns,
    .palettes = gTilesetPalettes_House_Lab_Hns,
    .metatiles = gMetatiles_House_Lab_Hns,
    .metatileAttributes = gMetatileAttributes_House_Lab_Hns,
    .callback = NULL,
};

const struct Tileset gTileset_IlexForest_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_IlexForest_Hns,
    .palettes = gTilesetPalettes_IlexForest_Hns,
    .metatiles = gMetatiles_IlexForest_Hns,
    .metatileAttributes = gMetatileAttributes_IlexForest_Hns,
    .callback = NULL,
};

const struct Tileset gTileset_IndigoPlateau_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_IndigoPlateau_Hns,
    .palettes = gTilesetPalettes_IndigoPlateau_Hns,
    .metatiles = gMetatiles_IndigoPlateau_Hns,
    .metatileAttributes = gMetatileAttributes_IndigoPlateau_Hns,
    .callback = NULL,
};

const struct Tileset gTileset_JohtoBikeShop_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_JohtoBikeShop_Hns,
    .palettes = gTilesetPalettes_JohtoBikeShop_Hns,
    .metatiles = gMetatiles_JohtoBikeShop_Hns,
    .metatileAttributes = gMetatileAttributes_JohtoBikeShop_Hns,
    .callback = NULL,
};

const struct Tileset gTileset_JohtoMart_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_JohtoMart_Hns,
    .palettes = gTilesetPalettes_JohtoMart_Hns,
    .metatiles = gMetatiles_JohtoMart_Hns,
    .metatileAttributes = gMetatileAttributes_JohtoMart_Hns,
    .callback = NULL,
};

const struct Tileset gTileset_Johto_Building_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = FALSE,
    .tiles = gTilesetTiles_Johto_Building_Hns,
    .palettes = gTilesetPalettes_Johto_Building_Hns,
    .metatiles = gMetatiles_Johto_Building_Hns,
    .metatileAttributes = gMetatileAttributes_Johto_Building_Hns,
    .callback = NULL,
};

const struct Tileset gTileset_Johto_General_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = FALSE,
    .tiles = gTilesetTiles_Johto_General_Hns,
    .palettes = gTilesetPalettes_Johto_General_Hns,
    .metatiles = gMetatiles_Johto_General_Hns,
    .metatileAttributes = gMetatileAttributes_Johto_General_Hns,
    .callback = InitTilesetAnim_JohtoGeneral,
};

const struct Tileset gTileset_Johto_NorthEast_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = FALSE,
    .tiles = gTilesetTiles_Johto_NorthEast_Hns,
    .palettes = gTilesetPalettes_Johto_NorthEast_Hns,
    .metatiles = gMetatiles_Johto_NorthEast_Hns,
    .metatileAttributes = gMetatileAttributes_Johto_NorthEast_Hns,
    .callback = InitTilesetAnim_JohtoGeneral,
};

const struct Tileset gTileset_Johto_NorthWest_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = FALSE,
    .tiles = gTilesetTiles_Johto_NorthWest_Hns,
    .palettes = gTilesetPalettes_Johto_NorthWest_Hns,
    .metatiles = gMetatiles_Johto_NorthWest_Hns,
    .metatileAttributes = gMetatileAttributes_Johto_NorthWest_Hns,
    .callback = InitTilesetAnim_JohtoGeneral,
};

const struct Tileset gTileset_Johto_South_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = FALSE,
    .tiles = gTilesetTiles_Johto_South_Hns,
    .palettes = gTilesetPalettes_Johto_South_Hns,
    .metatiles = gMetatiles_Johto_South_Hns,
    .metatileAttributes = gMetatileAttributes_Johto_South_Hns,
    .callback = InitTilesetAnim_JohtoGeneral,
};

const struct Tileset gTileset_Kanto_General_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = FALSE,
    .tiles = gTilesetTiles_Kanto_General_Hns,
    .palettes = gTilesetPalettes_Kanto_General_Hns,
    .metatiles = gMetatiles_Kanto_General_Hns,
    .metatileAttributes = gMetatileAttributes_Kanto_General_Hns,
    .callback = InitTilesetAnim_JohtoGeneral,
};

const struct Tileset gTileset_Kanto_PokemonCenter_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Kanto_PokemonCenter_Hns,
    .palettes = gTilesetPalettes_Kanto_PokemonCenter_Hns,
    .metatiles = gMetatiles_Kanto_PokemonCenter_Hns,
    .metatileAttributes = gMetatileAttributes_Kanto_PokemonCenter_Hns,
    .callback = NULL,
};

const struct Tileset gTileset_KurtsHouse_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_KurtsHouse_Hns,
    .palettes = gTilesetPalettes_KurtsHouse_Hns,
    .metatiles = gMetatiles_KurtsHouse_Hns,
    .metatileAttributes = gMetatileAttributes_KurtsHouse_Hns,
    .callback = NULL,
};

const struct Tileset gTileset_Lighthouse_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Lighthouse_Hns,
    .palettes = gTilesetPalettes_Lighthouse_Hns,
    .metatiles = gMetatiles_Lighthouse_Hns,
    .metatileAttributes = gMetatileAttributes_Lighthouse_Hns,
    .callback = NULL,
};

const struct Tileset gTileset_MahoganyTown_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_MahoganyTown_Hns,
    .palettes = gTilesetPalettes_MahoganyTown_Hns,
    .metatiles = gMetatiles_MahoganyTown_Hns,
    .metatileAttributes = gMetatileAttributes_MahoganyTown_Hns,
    .callback = NULL,
};

const struct Tileset gTileset_MtEmber_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_MtEmber_Hns,
    .palettes = gTilesetPalettes_MtEmber_Hns,
    .metatiles = gMetatiles_MtEmber_Hns,
    .metatileAttributes = gMetatileAttributes_MtEmber_Hns,
    .callback = InitTilesetAnim_MtEmber_Hns,
};

const struct Tileset gTileset_MtSilverSnow_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_MtSilverSnow_Hns,
    .palettes = gTilesetPalettes_MtSilverSnow_Hns,
    .metatiles = gMetatiles_MtSilverSnow_Hns,
    .metatileAttributes = gMetatileAttributes_MtSilverSnow_Hns,
    .callback = NULL,
};

const struct Tileset gTileset_MtSilver_Ancient_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_MtSilver_Ancient_Hns,
    .palettes = gTilesetPalettes_MtSilver_Ancient_Hns,
    .metatiles = gMetatiles_MtSilver_Ancient_Hns,
    .metatileAttributes = gMetatileAttributes_MtSilver_Ancient_Hns,
    .callback = NULL,
};

const struct Tileset gTileset_MtSilver_Exp_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = FALSE,
    .tiles = gTilesetTiles_MtSilver_Exp_Hns,
    .palettes = gTilesetPalettes_MtSilver_Exp_Hns,
    .metatiles = gMetatiles_MtSilver_Exp_Hns,
    .metatileAttributes = gMetatileAttributes_MtSilver_Exp_Hns,
    .callback = InitTilesetAnim_MtSilverExp,
};

const struct Tileset gTileset_MtSilver_NewSinjoh_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_MtSilver_NewSinjoh_Hns,
    .palettes = gTilesetPalettes_MtSilver_NewSinjoh_Hns,
    .metatiles = gMetatiles_MtSilver_NewSinjoh_Hns,
    .metatileAttributes = gMetatileAttributes_MtSilver_NewSinjoh_Hns,
    .callback = NULL,
};

const struct Tileset gTileset_NationalPark_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_NationalPark_Hns,
    .palettes = gTilesetPalettes_NationalPark_Hns,
    .metatiles = gMetatiles_NationalPark_Hns,
    .metatileAttributes = gMetatileAttributes_NationalPark_Hns,
    .callback = InitTilesetAnim_NationalPark,
};

const struct Tileset gTileset_NewBarkTown_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_NewBarkTown_Hns,
    .palettes = gTilesetPalettes_NewBarkTown_Hns,
    .metatiles = gMetatiles_NewBarkTown_Hns,
    .metatileAttributes = gMetatileAttributes_NewBarkTown_Hns,
    .callback = NULL,
};

const struct Tileset gTileset_OlivineCity_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_OlivineCity_Hns,
    .palettes = gTilesetPalettes_OlivineCity_Hns,
    .metatiles = gMetatiles_OlivineCity_Hns,
    .metatileAttributes = gMetatileAttributes_OlivineCity_Hns,
    .callback = NULL,
};

const struct Tileset gTileset_PlayersHouse_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_PlayersHouse_Hns,
    .palettes = gTilesetPalettes_PlayersHouse_Hns,
    .metatiles = gMetatiles_PlayersHouse_Hns,
    .metatileAttributes = gMetatileAttributes_PlayersHouse_Hns,
    .callback = NULL,
};

const struct Tileset gTileset_PokemonCenter_White_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_PokemonCenter_White_Hns,
    .palettes = gTilesetPalettes_PokemonCenter_White_Hns,
    .metatiles = gMetatiles_PokemonCenter_White_Hns,
    .metatileAttributes = gMetatileAttributes_PokemonCenter_White_Hns,
    .callback = NULL,
};

const struct Tileset gTileset_PokemonDayCare_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_PokemonDayCare_Hns,
    .palettes = gTilesetPalettes_PokemonDayCare_Hns,
    .metatiles = gMetatiles_PokemonDayCare_Hns,
    .metatileAttributes = gMetatileAttributes_PokemonDayCare_Hns,
    .callback = NULL,
};

const struct Tileset gTileset_PokemonLeague_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_PokemonLeague_Hns,
    .palettes = gTilesetPalettes_PokemonLeague_Hns,
    .metatiles = gMetatiles_PokemonLeague_Hns,
    .metatileAttributes = gMetatileAttributes_PokemonLeague_Hns,
    .callback = NULL,
};

const struct Tileset gTileset_PortIndoor_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_PortIndoor_Hns,
    .palettes = gTilesetPalettes_PortIndoor_Hns,
    .metatiles = gMetatiles_PortIndoor_Hns,
    .metatileAttributes = gMetatileAttributes_PortIndoor_Hns,
    .callback = NULL,
};

const struct Tileset gTileset_PowerPlant_GeneratorRoom_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_PowerPlant_GeneratorRoom_Hns,
    .palettes = gTilesetPalettes_PowerPlant_GeneratorRoom_Hns,
    .metatiles = gMetatiles_PowerPlant_GeneratorRoom_Hns,
    .metatileAttributes = gMetatileAttributes_PowerPlant_GeneratorRoom_Hns,
    .callback = NULL,
};

const struct Tileset gTileset_Route32_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Route32_Hns,
    .palettes = gTilesetPalettes_Route32_Hns,
    .metatiles = gMetatiles_Route32_Hns,
    .metatileAttributes = gMetatileAttributes_Route32_Hns,
    .callback = NULL,
};

const struct Tileset gTileset_Route38_Farmland_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Route38_Farmland_Hns,
    .palettes = gTilesetPalettes_Route38_Farmland_Hns,
    .metatiles = gMetatiles_Route38_Farmland_Hns,
    .metatileAttributes = gMetatileAttributes_Route38_Farmland_Hns,
    .callback = NULL,
};

const struct Tileset gTileset_Route40_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Route40_Hns,
    .palettes = gTilesetPalettes_Route40_Hns,
    .metatiles = gMetatiles_Route40_Hns,
    .metatileAttributes = gMetatileAttributes_Route40_Hns,
    .callback = NULL,
};

const struct Tileset gTileset_RuinsOfAlphWriting_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_RuinsOfAlphWriting_Hns,
    .palettes = gTilesetPalettes_RuinsOfAlphWriting_Hns,
    .metatiles = gMetatiles_RuinsOfAlphWriting_Hns,
    .metatileAttributes = gMetatileAttributes_RuinsOfAlphWriting_Hns,
    .callback = NULL,
};

const struct Tileset gTileset_RuinsOfAlph_B1F_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_RuinsOfAlph_B1F_Hns,
    .palettes = gTilesetPalettes_RuinsOfAlph_B1F_Hns,
    .metatiles = gMetatiles_RuinsOfAlph_B1F_Hns,
    .metatileAttributes = gMetatileAttributes_RuinsOfAlph_B1F_Hns,
    .callback = NULL,
};

const struct Tileset gTileset_RuinsOfAlph_Outside_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_RuinsOfAlph_Outside_Hns,
    .palettes = gTilesetPalettes_RuinsOfAlph_Outside_Hns,
    .metatiles = gMetatiles_RuinsOfAlph_Outside_Hns,
    .metatileAttributes = gMetatileAttributes_RuinsOfAlph_Outside_Hns,
    .callback = NULL,
};

const struct Tileset gTileset_SafariZoneJohto_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_SafariZoneJohto_Hns,
    .palettes = gTilesetPalettes_SafariZoneJohto_Hns,
    .metatiles = gMetatiles_SafariZoneJohto_Hns,
    .metatileAttributes = gMetatileAttributes_SafariZoneJohto_Hns,
    .callback = NULL,
};

const struct Tileset gTileset_SafariZone_Entrance_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_SafariZone_Entrance_Hns,
    .palettes = gTilesetPalettes_SafariZone_Entrance_Hns,
    .metatiles = gMetatiles_SafariZone_Entrance_Hns,
    .metatileAttributes = gMetatileAttributes_SafariZone_Entrance_Hns,
    .callback = NULL,
};

const struct Tileset gTileset_SaffronCity_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_SaffronCity_Hns,
    .palettes = gTilesetPalettes_SaffronCity_Hns,
    .metatiles = gMetatiles_SaffronCity_Hns,
    .metatileAttributes = gMetatileAttributes_SaffronCity_Hns,
    .callback = NULL,
};

const struct Tileset gTileset_ShopRooftop_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_ShopRooftop_Hns,
    .palettes = gTilesetPalettes_ShopRooftop_Hns,
    .metatiles = gMetatiles_ShopRooftop_Hns,
    .metatileAttributes = gMetatileAttributes_ShopRooftop_Hns,
    .callback = NULL,
};

const struct Tileset gTileset_SootopolisGym_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_SootopolisGym_Hns,
    .palettes = gTilesetPalettes_SootopolisGym_Hns,
    .metatiles = gMetatiles_SootopolisGym_Hns,
    .metatileAttributes = gMetatileAttributes_SootopolisGym_Hns,
    .callback = NULL,
};

const struct Tileset gTileset_SoulHouse_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_SoulHouse_Hns,
    .palettes = gTilesetPalettes_SoulHouse_Hns,
    .metatiles = gMetatiles_SoulHouse_Hns,
    .metatileAttributes = gMetatileAttributes_SoulHouse_Hns,
    .callback = NULL,
};

const struct Tileset gTileset_TrainerHill_Courtyard_Hns = {0};

const struct Tileset gTileset_TrainerSchool_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_TrainerSchool_Hns,
    .palettes = gTilesetPalettes_TrainerSchool_Hns,
    .metatiles = gMetatiles_TrainerSchool_Hns,
    .metatileAttributes = gMetatileAttributes_TrainerSchool_Hns,
    .callback = NULL,
};

const struct Tileset gTileset_VioletCity_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_VioletCity_Hns,
    .palettes = gTilesetPalettes_VioletCity_Hns,
    .metatiles = gMetatiles_VioletCity_Hns,
    .metatileAttributes = gMetatileAttributes_VioletCity_Hns,
    .callback = NULL,
};

const struct Tileset gTileset_ViridianCity_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_ViridianCity_Hns,
    .palettes = gTilesetPalettes_ViridianCity_Hns,
    .metatiles = gMetatiles_ViridianCity_Hns,
    .metatileAttributes = gMetatileAttributes_ViridianCity_Hns,
    .callback = NULL,
};

const struct Tileset gTileset_WhirlIslands_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_WhirlIslands_Hns,
    .palettes = gTilesetPalettes_WhirlIslands_Hns,
    .metatiles = gMetatiles_WhirlIslands_Hns,
    .metatileAttributes = gMetatileAttributes_WhirlIslands_Hns,
    .callback = NULL,
};

const struct Tileset gTileset_ssaqua_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_ssaqua_Hns,
    .palettes = gTilesetPalettes_ssaqua_Hns,
    .metatiles = gMetatiles_ssaqua_Hns,
    .metatileAttributes = gMetatileAttributes_ssaqua_Hns,
    .callback = NULL,
};

// Exact upstream dependencies of the campaign Artisan Cave and shared link room.
const struct Tileset gTileset_Cave = {0};

const struct Tileset gTileset_UnionRoom =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_UnionRoom,
    .palettes = gTilesetPalettes_UnionRoom,
    .metatiles = gMetatiles_UnionRoom,
    .metatileAttributes = gMetatileAttributes_UnionRoom,
    .callback = NULL,
};

// Exact pinned providers for the selected native Kanto interior visuals.
const struct Tileset gTileset_Kanto_Building_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = FALSE,
    .tiles = gTilesetTiles_Kanto_Building_Hns,
    .palettes = gTilesetPalettes_Kanto_Building_Hns,
    .metatiles = gMetatiles_Kanto_Building_Hns,
    .metatileAttributes = gMetatileAttributes_Kanto_Building_Hns,
    .callback = NULL,
};

const struct Tileset gTileset_KantoMart_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_KantoMart_Hns,
    .palettes = gTilesetPalettes_KantoMart_Hns,
    .metatiles = gMetatiles_KantoMart_Hns,
    .metatileAttributes = gMetatileAttributes_KantoMart_Hns,
    .callback = NULL,
};

// Redesigned native Kanto: exact pinned Pallet/Pewter provider definitions.
const struct Tileset gTileset_PalletTown_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_PalletTown_Hns,
    .palettes = gTilesetPalettes_PalletTown_Hns,
    .metatiles = gMetatiles_PalletTown_Hns,
    .metatileAttributes = gMetatileAttributes_PalletTown_Hns,
    .callback = NULL,
};

const struct Tileset gTileset_PewterCity_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_PewterCity_Hns,
    .palettes = gTilesetPalettes_PewterCity_Hns,
    .metatiles = gMetatiles_PewterCity_Hns,
    .metatileAttributes = gMetatileAttributes_PewterCity_Hns,
    .callback = NULL,
};

// Exact pinned providers for redesigned native Kanto rooms; original peer branches retained.
const struct Tileset gTileset_CeladonApartments_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_CeladonApartments_Hns,
    .palettes = gTilesetPalettes_CeladonApartments_Hns,
    .metatiles = gMetatiles_CeladonApartments_Hns,
    .metatileAttributes = gMetatileAttributes_CeladonApartments_Hns,
    .callback = NULL,
};

const struct Tileset gTileset_CeruleanCity_Gym_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_CeruleanCity_Gym_Hns,
    .palettes = gTilesetPalettes_CeruleanCity_Gym_Hns,
    .metatiles = gMetatiles_CeruleanCity_Gym_Hns,
    .metatileAttributes = gMetatileAttributes_CeruleanCity_Gym_Hns,
    .callback = NULL,
};

const struct Tileset gTileset_FuchsiaCity_Gym_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_FuchsiaCity_Gym_Hns,
    .palettes = gTilesetPalettes_FuchsiaCity_Gym_Hns,
    .metatiles = gMetatiles_FuchsiaCity_Gym_Hns,
    .metatileAttributes = gMetatileAttributes_FuchsiaCity_Gym_Hns,
    .callback = NULL,
};

const struct Tileset gTileset_SaffronCity_Gym_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_SaffronCity_Gym_Hns,
    .palettes = gTilesetPalettes_SaffronCity_Gym_Hns,
    .metatiles = gMetatiles_SaffronCity_Gym_Hns,
    .metatileAttributes = gMetatileAttributes_SaffronCity_Gym_Hns,
    .callback = NULL,
};

const struct Tileset gTileset_ViridianForest_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_ViridianForest_Hns,
    .palettes = gTilesetPalettes_ViridianForest_Hns,
    .metatiles = gMetatiles_ViridianForest_Hns,
    .metatileAttributes = gMetatileAttributes_ViridianForest_Hns,
    .callback = NULL,
};

const struct Tileset gTileset_Cave_MtMoon_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Cave_MtMoon_Hns,
    .palettes = gTilesetPalettes_Cave_MtMoon_Hns,
    .metatiles = gMetatiles_Cave_MtMoon_Hns,
    .metatileAttributes = gMetatileAttributes_Cave_MtMoon_Hns,
    .callback = NULL,
};

// FireRed Mt. Moon front floors: original native attribute formats/IDs with pinned HnS art.
const struct Tileset gTileset_MtMoonNativeGeneral_FireRed =
{
    .isCompressed = TRUE,
    .isSecondary = FALSE,
    .tiles = gTilesetTiles_Johto_General_Hns,
    .palettes = gTilesetPalettes_Johto_General_Hns,
    .metatiles = gMetatiles_Johto_General_Hns,
    .metatileAttributes = gMetatileAttributes_General_Frlg,
    .callback = InitTilesetAnim_JohtoGeneral,
};

const struct Tileset gTileset_MtMoonNativeCave_FireRed =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Cave_MtMoon_Hns,
    .palettes = gTilesetPalettes_Cave_MtMoon_Hns,
    .metatiles = gMetatiles_MtMoonNativeArt_FireRed,
    .metatileAttributes = gMetatileAttributes_Cave_Frlg,
    .callback = NULL,
};


const struct Tileset gTileset_Cave_Sandy_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Cave_Sandy_Hns,
    .palettes = gTilesetPalettes_Cave_Sandy_Hns,
    .metatiles = gMetatiles_Cave_Sandy_Hns,
    .metatileAttributes = gMetatileAttributes_Cave_Sandy_Hns,
    .callback = NULL,
};


const struct Tileset gTileset_Cave_Green_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Cave_Green_Hns,
    .palettes = gTilesetPalettes_Cave_Green_Hns,
    .metatiles = gMetatiles_Cave_Green_Hns,
    .metatileAttributes = gMetatileAttributes_Cave_Green_Hns,
    .callback = NULL,
};


// Native Seafoam puzzle topology/attributes with pinned HnS ice artwork.
const struct Tileset gTileset_SeafoamNativeGeneral_FireRed =
{
    .isCompressed = TRUE,
    .isSecondary = FALSE,
    .tiles = gTilesetTiles_Johto_General_Hns,
    .palettes = gTilesetPalettes_Johto_General_Hns,
    .metatiles = gMetatiles_SeafoamNativeGeneralArt_FireRed,
    .metatileAttributes = gMetatileAttributes_General_Frlg,
    .callback = InitTilesetAnim_JohtoGeneral,
};

const struct Tileset gTileset_SeafoamNativeIce_FireRed =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Cave_Ice_Hns,
    .palettes = gTilesetPalettes_Cave_Ice_Hns,
    .metatiles = gMetatiles_SeafoamNativeIceArt_FireRed,
    .metatileAttributes = gMetatileAttributes_SeafoamIslands,
    .callback = NULL,
};


const struct Tileset gTileset_VictoryRoadNativeCave_FireRed =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Cave_Default_Hns,
    .palettes = gTilesetPalettes_Cave_Default_Hns,
    .metatiles = gMetatiles_VictoryRoadNativeArt_FireRed,
    .metatileAttributes = gMetatileAttributes_Cave_Frlg,
    .callback = NULL,
};


// Reuse pinned HnS art; native gate services need their original attributes.
const struct Tileset gTileset_Gate_Standard_FireRedCampaign =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Gate_Standard_Hns,
    .palettes = gTilesetPalettes_Gate_Standard_Hns,
    .metatiles = gMetatiles_Gate_Standard_Hns,
    .metatileAttributes = gMetatileAttributes_Gate_Standard_FireRedCampaign,
    .callback = NULL,
};

// Original HnS Kanto building art; native FRLG attributes retain full native semantics.
const struct Tileset gTileset_Kanto_Building_FireRedNative =
{
    .isCompressed = TRUE,
    .isSecondary = FALSE,
    .tiles = gTilesetTiles_Kanto_Building_Hns,
    .palettes = gTilesetPalettes_Kanto_Building_Hns,
    .metatiles = gMetatiles_Kanto_Building_Hns,
    .metatileAttributes = gMetatileAttributes_Building_Frlg,
    .callback = NULL,
};

// Original art/frame pointers, full exact historical FRLG attributes. Shared original untouched.
const struct Tileset gTileset_Lab_FireRedNative =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Lab_Frlg,
    .palettes = gTilesetPalettes_Lab_Frlg,
    .metatiles = gMetatiles_Lab_Frlg,
    .metatileAttributes = (const u16 *)gMetatileAttributes_Lab_FireRedNative,
    .callback = NULL,
};

// Native topology/attributes keep FireRed services; use original HnS Kanto artwork.
const struct Tileset gTileset_Johto_Building_FireRedNative =
{
    .isCompressed = TRUE,
    .isSecondary = FALSE,
    .tiles = gTilesetTiles_Johto_Building_Hns,
    .palettes = gTilesetPalettes_Johto_Building_Hns,
    .metatiles = gMetatiles_Johto_Building_Hns,
    .metatileAttributes = gMetatileAttributes_Building_Frlg,
    .callback = NULL,
};
const struct Tileset gTileset_Kanto_PokemonCenter_FireRedNative =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Kanto_PokemonCenter_Hns,
    .palettes = gTilesetPalettes_Kanto_PokemonCenter_Hns,
    .metatiles = gMetatiles_Kanto_PokemonCenter_Hns,
    .metatileAttributes = gMetatileAttributes_PokemonCenter_Frlg,
    .callback = NULL,
};
const struct Tileset gTileset_Museum_FireRedNative =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Museum_Hns,
    .palettes = gTilesetPalettes_Museum_Hns,
    .metatiles = gMetatiles_Museum_Hns,
    .metatileAttributes = gMetatileAttributes_Museum,
    .callback = NULL,
};

// Original HnS Vermilion provider required by the FireRed Route6 redesign.
// Preserve the original HnS branch and every peer target.
const struct Tileset gTileset_Vermilion_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Vermilion_Hns,
    .palettes = gTilesetPalettes_Vermilion_Hns,
    .metatiles = gMetatiles_Vermilion_Hns,
    .metatileAttributes = gMetatileAttributes_Vermilion_Hns,
    .callback = NULL,
};

// Exact original eastern Kanto Lavender providers. Other targets retain their
// original declarations; no source assets or provider semantics are changed.
const struct Tileset gTileset_LavenderTown_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_LavenderTown_Hns,
    .palettes = gTilesetPalettes_LavenderTown_Hns,
    .metatiles = gMetatiles_LavenderTown_Hns,
    .metatileAttributes = gMetatileAttributes_LavenderTown_Hns,
    .callback = NULL,
};

// Exact original western/southern Kanto providers. Other targets retain their
// original declarations; no source assets or provider semantics are changed.
const struct Tileset gTileset_CeladonCity_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_CeladonCity_Hns,
    .palettes = gTilesetPalettes_CeladonCity_Hns,
    .metatiles = gMetatiles_CeladonCity_Hns,
    .metatileAttributes = gMetatileAttributes_CeladonCity_Hns,
    .callback = InitTilesetAnim_CeladonCity_Hns,
};

const struct Tileset gTileset_CyclingRoad_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_CyclingRoad_Hns,
    .palettes = gTilesetPalettes_CyclingRoad_Hns,
    .metatiles = gMetatiles_CyclingRoad_Hns,
    .metatileAttributes = gMetatileAttributes_CyclingRoad_Hns,
    .callback = NULL,
};

const struct Tileset gTileset_Fuchsia_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Fuchsia_Hns,
    .palettes = gTilesetPalettes_Fuchsia_Hns,
    .metatiles = gMetatiles_Fuchsia_Hns,
    .metatileAttributes = gMetatileAttributes_Fuchsia_Hns,
    .callback = NULL,
};

const struct Tileset gTileset_Lavaridge_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Lavaridge_Hns,
    .palettes = gTilesetPalettes_Lavaridge_Hns,
    .metatiles = gMetatiles_Lavaridge_Hns,
    .metatileAttributes = gMetatileAttributes_Lavaridge_Hns,
    .callback = NULL,
};

// Exact original Cerulean/Route5 Kanto provider. Other targets retain their
// original declarations; no source assets or provider semantics are changed.
const struct Tileset gTileset_CeruleanCity_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_CeruleanCity_Hns,
    .palettes = gTilesetPalettes_CeruleanCity_Hns,
    .metatiles = gMetatiles_CeruleanCity_Hns,
    .metatileAttributes = gMetatileAttributes_CeruleanCity_Hns,
    .callback = InitTilesetAnim_CeruleanCity_Hns,
};

// HnS's restyled General tileset for the event islands (Birth, Faraway and Southern Island) instead of Emerald's.
const struct Tileset gTileset_General_Hns =
{
    .isCompressed = TRUE,
    .isSecondary = FALSE,
    .tiles = gTilesetTiles_General_Hns,
    .palettes = gTilesetPalettes_General_Hns,
    .metatiles = gMetatiles_General_Hns,
    .metatileAttributes = gMetatileAttributes_General_Hns,
    .callback = NULL,
};

const struct Tileset gTileset_PalletConcept_General =
{
    .isCompressed = TRUE,
    .isSecondary = FALSE,
    .tiles = gTilesetTiles_PalletConcept_General,
    .palettes = gTilesetPalettes_PalletConcept_General,
    .metatiles = gMetatiles_PalletConcept_General,
    .metatileAttributes = gMetatileAttributes_PalletConcept_General,
    .callback = InitTilesetAnim_PalletConcept_General,
};

const struct Tileset gTileset_PalletConcept =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_PalletConcept,
    .palettes = gTilesetPalettes_PalletConcept,
    .metatiles = gMetatiles_PalletConcept,
    .metatileAttributes = gMetatileAttributes_PalletConcept,
    .callback = NULL,
};

const struct Tileset gTileset_Route1Concept =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Route1Concept,
    .palettes = gTilesetPalettes_Route1Concept,
    .metatiles = gMetatiles_Route1Concept,
    .metatileAttributes = gMetatileAttributes_Route1Concept,
    .callback = NULL,
};

const struct Tileset gTileset_ViridianConcept =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_ViridianConcept,
    .palettes = gTilesetPalettes_ViridianConcept,
    .metatiles = gMetatiles_ViridianConcept,
    .metatileAttributes = gMetatileAttributes_ViridianConcept,
    .callback = NULL,
};

const struct Tileset gTileset_Route22Concept =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Route22Concept,
    .palettes = gTilesetPalettes_Route22Concept,
    .metatiles = gMetatiles_Route22Concept,
    .metatileAttributes = gMetatileAttributes_Route22Concept,
    .callback = NULL,
};

const struct Tileset gTileset_Route2Concept =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Route2Concept,
    .palettes = gTilesetPalettes_Route2Concept,
    .metatiles = gMetatiles_Route2Concept,
    .metatileAttributes = gMetatileAttributes_Route2Concept,
    .callback = NULL,
};

const struct Tileset gTileset_ViridianForestConcept =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_ViridianForestConcept,
    .palettes = gTilesetPalettes_ViridianForestConcept,
    .metatiles = gMetatiles_ViridianForestConcept,
    .metatileAttributes = gMetatileAttributes_ViridianForestConcept,
    .callback = NULL,
};

const struct Tileset gTileset_PewterConcept =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_PewterConcept,
    .palettes = gTilesetPalettes_PewterConcept,
    .metatiles = gMetatiles_PewterConcept,
    .metatileAttributes = gMetatileAttributes_PewterConcept,
    .callback = NULL,
};

const struct Tileset gTileset_Route3Concept =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Route3Concept,
    .palettes = gTilesetPalettes_Route3Concept,
    .metatiles = gMetatiles_Route3Concept,
    .metatileAttributes = gMetatileAttributes_Route3Concept,
    .callback = NULL,
};

const struct Tileset gTileset_Route4Concept =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Route4Concept,
    .palettes = gTilesetPalettes_Route4Concept,
    .metatiles = gMetatiles_Route4Concept,
    .metatileAttributes = gMetatileAttributes_Route4Concept,
    .callback = NULL,
};

const struct Tileset gTileset_CeruleanConcept =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_CeruleanConcept,
    .palettes = gTilesetPalettes_CeruleanConcept,
    .metatiles = gMetatiles_CeruleanConcept,
    .metatileAttributes = gMetatileAttributes_CeruleanConcept,
    .callback = NULL,
};
