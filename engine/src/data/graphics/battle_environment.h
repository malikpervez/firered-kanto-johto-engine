const u32 gBattleEnvironmentTiles_TallGrass[] = INCBIN_U32("graphics/battle_environment/tall_grass/tiles.4bpp.smol");
const u16 gBattleEnvironmentPalette_TallGrass[] = INCBIN_U16("graphics/battle_environment/tall_grass/palette.gbapal");
const u32 gBattleEnvironmentTilemap_TallGrass[] = INCBIN_U32("graphics/battle_environment/tall_grass/map.bin.smolTM");

const u32 gBattleEnvironmentTiles_LongGrass[] = INCBIN_U32("graphics/battle_environment/long_grass/tiles.4bpp.smol");
const u16 gBattleEnvironmentPalette_LongGrass[] = INCBIN_U16("graphics/battle_environment/long_grass/palette.gbapal");
extern const u32 gBattleEnvironmentTilemap_LongGrass[29] __attribute__((alias("gBattleEnvironmentTilemap_TallGrass")));

const u32 gBattleEnvironmentTiles_Sand[] = INCBIN_U32("graphics/battle_environment/sand/tiles.4bpp.smol");
const u16 gBattleEnvironmentPalette_Sand[] = INCBIN_U16("graphics/battle_environment/sand/palette.gbapal");
const u32 gBattleEnvironmentTilemap_Sand[] = INCBIN_U32("graphics/battle_environment/sand/map.bin.smolTM");

const u32 gBattleEnvironmentTiles_Underwater[] = INCBIN_U32("graphics/battle_environment/underwater/tiles.4bpp.smol");
const u16 gBattleEnvironmentPalette_Underwater[] = INCBIN_U16("graphics/battle_environment/underwater/palette.gbapal");
extern const u32 gBattleEnvironmentTilemap_Underwater[29] __attribute__((alias("gBattleEnvironmentTilemap_TallGrass")));

const u32 gBattleEnvironmentTiles_Water[] = INCBIN_U32("graphics/battle_environment/water/tiles.4bpp.smol");
const u16 gBattleEnvironmentPalette_Water[] = INCBIN_U16("graphics/battle_environment/water/palette.gbapal");
extern const u32 gBattleEnvironmentTilemap_Water[29] __attribute__((alias("gBattleEnvironmentTilemap_TallGrass")));

const u32 gBattleEnvironmentTiles_PondWater[] = INCBIN_U32("graphics/battle_environment/pond_water/tiles.4bpp.smol");
const u16 gBattleEnvironmentPalette_PondWater[] = INCBIN_U16("graphics/battle_environment/pond_water/palette.gbapal");
extern const u32 gBattleEnvironmentTilemap_PondWater[29] __attribute__((alias("gBattleEnvironmentTilemap_TallGrass")));

const u32 gBattleEnvironmentTiles_Rock[] = INCBIN_U32("graphics/battle_environment/rock/tiles.4bpp.smol");
const u16 gBattleEnvironmentPalette_Rock[] = INCBIN_U16("graphics/battle_environment/rock/palette.gbapal");
extern const u32 gBattleEnvironmentTilemap_Rock[29] __attribute__((alias("gBattleEnvironmentTilemap_TallGrass")));

const u32 gBattleEnvironmentTiles_Cave[] = INCBIN_U32("graphics/battle_environment/cave/tiles.4bpp.smol");
const u16 gBattleEnvironmentPalette_Cave[] = INCBIN_U16("graphics/battle_environment/cave/palette.gbapal");
extern const u32 gBattleEnvironmentTilemap_Cave[29] __attribute__((alias("gBattleEnvironmentTilemap_TallGrass")));

const u32 gBattleEnvironmentTiles_Building[] = INCBIN_U32("graphics/battle_environment/building/tiles.4bpp.smol");
const u16 gBattleEnvironmentPalette_Building[] = INCBIN_U16("graphics/battle_environment/building/palette.gbapal");
extern const u32 gBattleEnvironmentTilemap_Building[29] __attribute__((alias("gBattleEnvironmentTilemap_Sand")));

const u16 gBattleEnvironmentPalette_BuildingGym[] = INCBIN_U16("graphics/battle_environment/building/gym.gbapal");
const u16 gBattleEnvironmentPalette_BuildingLeader[] = INCBIN_U16("graphics/battle_environment/building/leader.gbapal");
const u16 gBattleEnvironmentPalette_Plain[] = INCBIN_U16("graphics/battle_environment/plain/palette.gbapal");

const u32 gBattleEnvironmentTiles_Stadium[] = INCBIN_U32("graphics/battle_environment/stadium/tiles.4bpp.smol");
extern const u32 gBattleEnvironmentTilemap_Stadium[29] __attribute__((alias("gBattleEnvironmentTilemap_Sand")));

const u16 gBattleEnvironmentPalette_Frontier[] = INCBIN_U16("graphics/battle_environment/stadium/battle_frontier.gbapal"); // this is also used for link battles
const u16 gBattleEnvironmentPalette_StadiumAqua[] = INCBIN_U16("graphics/battle_environment/stadium/aqua.gbapal");
const u16 gBattleEnvironmentPalette_StadiumMagma[] = INCBIN_U16("graphics/battle_environment/stadium/magma.gbapal");
const u16 gBattleEnvironmentPalette_StadiumSidney[] = INCBIN_U16("graphics/battle_environment/stadium/sidney.gbapal");
const u16 gBattleEnvironmentPalette_StadiumPhoebe[] = INCBIN_U16("graphics/battle_environment/stadium/phoebe.gbapal");
const u16 gBattleEnvironmentPalette_StadiumGlacia[] = INCBIN_U16("graphics/battle_environment/stadium/glacia.gbapal");
const u16 gBattleEnvironmentPalette_StadiumDrake[] = INCBIN_U16("graphics/battle_environment/stadium/drake.gbapal");
const u16 gBattleEnvironmentPalette_StadiumWallace[] = INCBIN_U16("graphics/battle_environment/stadium/wallace.gbapal");

const u16 gBattleEnvironmentPalette_Kyogre[] = INCBIN_U16("graphics/battle_environment/water/kyogre.gbapal");
const u16 gBattleEnvironmentPalette_Groudon[] = INCBIN_U16("graphics/battle_environment/cave/groudon.gbapal");

const u32 gBattleEnvironmentTiles_Rayquaza[] = INCBIN_U32("graphics/battle_environment/sky/tiles.4bpp.smol");
const u16 gBattleEnvironmentPalette_Rayquaza[] = INCBIN_U16("graphics/battle_environment/sky/palette.gbapal");
extern const u32 gBattleEnvironmentTilemap_Rayquaza[29] __attribute__((alias("gBattleEnvironmentTilemap_Sand")));

const u32 gBattleEnvironmentAnimTiles_TallGrass[] = INCBIN_U32("graphics/battle_environment/tall_grass/anim_tiles.4bpp.smol");
const u32 gBattleEnvironmentAnimTilemap_TallGrass[] = INCBIN_U32("graphics/battle_environment/tall_grass/anim_map.bin.smolTM");

const u32 gBattleEnvironmentAnimTiles_LongGrass[] = INCBIN_U32("graphics/battle_environment/long_grass/anim_tiles.4bpp.smol");
const u32 gBattleEnvironmentAnimTilemap_LongGrass[] = INCBIN_U32("graphics/battle_environment/long_grass/anim_map.bin.smolTM");

const u32 gBattleEnvironmentAnimTiles_Sand[] = INCBIN_U32("graphics/battle_environment/sand/anim_tiles.4bpp.smol");
const u32 gBattleEnvironmentAnimTilemap_Sand[] = INCBIN_U32("graphics/battle_environment/sand/anim_map.bin.smolTM");

const u32 gBattleEnvironmentAnimTiles_Underwater[] = INCBIN_U32("graphics/battle_environment/underwater/anim_tiles.4bpp.smol");
const u32 gBattleEnvironmentAnimTilemap_Underwater[] = INCBIN_U32("graphics/battle_environment/underwater/anim_map.bin.smolTM");

const u32 gBattleEnvironmentAnimTiles_Water[] = INCBIN_U32("graphics/battle_environment/water/anim_tiles.4bpp.smol");
const u32 gBattleEnvironmentAnimTilemap_Water[] = INCBIN_U32("graphics/battle_environment/water/anim_map.bin.smolTM");

const u32 gBattleEnvironmentAnimTiles_PondWater[] = INCBIN_U32("graphics/battle_environment/pond_water/anim_tiles.4bpp.smol");
const u32 gBattleEnvironmentAnimTilemap_PondWater[] = INCBIN_U32("graphics/battle_environment/pond_water/anim_map.bin.smolTM");

const u32 gBattleEnvironmentAnimTiles_Rock[] = INCBIN_U32("graphics/battle_environment/rock/anim_tiles.4bpp.smol");
const u32 gBattleEnvironmentAnimTilemap_Rock[] = INCBIN_U32("graphics/battle_environment/rock/anim_map.bin.smolTM");

extern const u32 gBattleEnvironmentTiles_RockSnow[185] __attribute__((alias("gBattleEnvironmentTiles_Rock")));
extern const u16 gBattleEnvironmentPalette_RockSnow[48] __attribute__((alias("gBattleEnvironmentPalette_Rock")));
extern const u32 gBattleEnvironmentTilemap_RockSnow[29] __attribute__((alias("gBattleEnvironmentTilemap_TallGrass")));
extern const u32 gBattleEnvironmentAnimTiles_RockSnow[138] __attribute__((alias("gBattleEnvironmentAnimTiles_Rock")));
extern const u32 gBattleEnvironmentAnimTilemap_RockSnow[38] __attribute__((alias("gBattleEnvironmentAnimTilemap_Rock")));

extern const u32 gBattleEnvironmentTiles_MountainSnow[185] __attribute__((alias("gBattleEnvironmentTiles_Rock")));
extern const u16 gBattleEnvironmentPalette_MountainSnow[48] __attribute__((alias("gBattleEnvironmentPalette_Rock")));
extern const u32 gBattleEnvironmentTilemap_MountainSnow[29] __attribute__((alias("gBattleEnvironmentTilemap_TallGrass")));
extern const u32 gBattleEnvironmentAnimTiles_MountainSnow[138] __attribute__((alias("gBattleEnvironmentAnimTiles_Rock")));
extern const u32 gBattleEnvironmentAnimTilemap_MountainSnow[38] __attribute__((alias("gBattleEnvironmentAnimTilemap_Rock")));

extern const u32 gBattleEnvironmentTiles_Volcano[210] __attribute__((alias("gBattleEnvironmentTiles_Cave")));
extern const u16 gBattleEnvironmentPalette_Volcano[48] __attribute__((alias("gBattleEnvironmentPalette_Cave")));
extern const u32 gBattleEnvironmentTilemap_Volcano[29] __attribute__((alias("gBattleEnvironmentTilemap_TallGrass")));
const u32 gBattleEnvironmentAnimTiles_Volcano[] = INCBIN_U32("graphics/battle_environment/volcano/anim_tiles.4bpp.smol");
const u32 gBattleEnvironmentAnimTilemap_Volcano[] = INCBIN_U32("graphics/battle_environment/volcano/anim_map.bin.smolTM");

extern const u32 gBattleEnvironmentTiles_SnowCave[210] __attribute__((alias("gBattleEnvironmentTiles_Cave")));
extern const u16 gBattleEnvironmentPalette_SnowCave[48] __attribute__((alias("gBattleEnvironmentPalette_Cave")));
extern const u32 gBattleEnvironmentTilemap_SnowCave[29] __attribute__((alias("gBattleEnvironmentTilemap_TallGrass")));
extern const u32 gBattleEnvironmentAnimTiles_SnowCave[337] __attribute__((alias("gBattleEnvironmentAnimTiles_Volcano")));
extern const u32 gBattleEnvironmentAnimTilemap_SnowCave[41] __attribute__((alias("gBattleEnvironmentAnimTilemap_Volcano")));

extern const u32 gBattleEnvironmentAnimTiles_Cave[337] __attribute__((alias("gBattleEnvironmentAnimTiles_Volcano")));
extern const u32 gBattleEnvironmentAnimTilemap_Cave[41] __attribute__((alias("gBattleEnvironmentAnimTilemap_Volcano")));

const u32 gBattleEnvironmentAnimTiles_Building[] = INCBIN_U32("graphics/battle_environment/building/anim_tiles.4bpp.smol");
const u32 gBattleEnvironmentAnimTilemap_Building[] = INCBIN_U32("graphics/battle_environment/building/anim_map.bin.smolTM");

const u32 gBattleEnvironmentAnimTiles_Rayquaza[] = INCBIN_U32("graphics/battle_environment/sky/anim_tiles.4bpp.smol");
const u32 gBattleEnvironmentAnimTilemap_Rayquaza[] = INCBIN_U32("graphics/battle_environment/sky/anim_map.bin.smolTM");

// Blue building environment
extern const u32 gBattleEnvironmentTiles_BlueBuilding[192] __attribute__((alias("gBattleEnvironmentTiles_Building")));
extern const u16 gBattleEnvironmentPalette_BlueBuilding[48] __attribute__((alias("gBattleEnvironmentPalette_Building")));
extern const u32 gBattleEnvironmentTilemap_BlueBuilding[29] __attribute__((alias("gBattleEnvironmentTilemap_Sand")));
extern const u32 gBattleEnvironmentAnimTiles_BlueBuilding[24] __attribute__((alias("gBattleEnvironmentAnimTiles_Building")));
extern const u32 gBattleEnvironmentAnimTilemap_BlueBuilding[38] __attribute__((alias("gBattleEnvironmentAnimTilemap_Building")));

// Modern battle environment graphics
const u32 gBattleEnvironmentTiles_TallGrassModern[] = INCBIN_U32("graphics/battle_environment/tall_grass_modern/tiles.4bpp.smol");
const u16 gBattleEnvironmentPalette_TallGrassModern[] = INCBIN_U16("graphics/battle_environment/tall_grass_modern/palette.gbapal");
const u32 gBattleEnvironmentTilemap_TallGrassModern[] = INCBIN_U32("graphics/battle_environment/tall_grass_modern/map.bin.smolTM");

const u32 gBattleEnvironmentTiles_LongGrassModern[] = INCBIN_U32("graphics/battle_environment/long_grass_modern/tiles.4bpp.smol");
extern const u16 gBattleEnvironmentPalette_LongGrassModern[48] __attribute__((alias("gBattleEnvironmentPalette_TallGrassModern")));
const u32 gBattleEnvironmentTilemap_LongGrassModern[] = INCBIN_U32("graphics/battle_environment/long_grass_modern/map.bin.smolTM");

const u32 gBattleEnvironmentTiles_SandModern[] = INCBIN_U32("graphics/battle_environment/sand_modern/tiles.4bpp.smol");
const u16 gBattleEnvironmentPalette_SandModern[] = INCBIN_U16("graphics/battle_environment/sand_modern/palette.gbapal");
const u32 gBattleEnvironmentTilemap_SandModern[] = INCBIN_U32("graphics/battle_environment/sand_modern/map.bin.smolTM");

const u32 gBattleEnvironmentTiles_UnderwaterModern[] = INCBIN_U32("graphics/battle_environment/underwater_modern/tiles.4bpp.smol");
extern const u16 gBattleEnvironmentPalette_UnderwaterModern[48] __attribute__((alias("gBattleEnvironmentPalette_Underwater")));
extern const u32 gBattleEnvironmentTilemap_UnderwaterModern[29] __attribute__((alias("gBattleEnvironmentTilemap_TallGrass")));

const u32 gBattleEnvironmentTiles_WaterModern[] = INCBIN_U32("graphics/battle_environment/water_modern/tiles.4bpp.smol");
const u16 gBattleEnvironmentPalette_WaterModern[] = INCBIN_U16("graphics/battle_environment/water_modern/palette.gbapal");
const u32 gBattleEnvironmentTilemap_WaterModern[] = INCBIN_U32("graphics/battle_environment/water_modern/map.bin.smolTM");

const u32 gBattleEnvironmentTiles_PondWaterModern[] = INCBIN_U32("graphics/battle_environment/pond_water_modern/tiles.4bpp.smol");
const u16 gBattleEnvironmentPalette_PondWaterModern[] = INCBIN_U16("graphics/battle_environment/pond_water_modern/palette.gbapal");
const u32 gBattleEnvironmentTilemap_PondWaterModern[] = INCBIN_U32("graphics/battle_environment/pond_water_modern/map.bin.smolTM");

const u32 gBattleEnvironmentTiles_RockModern[] = INCBIN_U32("graphics/battle_environment/rock_modern/tiles.4bpp.smol");
const u16 gBattleEnvironmentPalette_RockModern[] = INCBIN_U16("graphics/battle_environment/rock_modern/palette.gbapal");
const u32 gBattleEnvironmentTilemap_RockModern[] = INCBIN_U32("graphics/battle_environment/rock_modern/map.bin.smolTM");

const u32 gBattleEnvironmentTiles_CaveModern[] = INCBIN_U32("graphics/battle_environment/cave_modern/tiles.4bpp.smol");
const u16 gBattleEnvironmentPalette_CaveModern[] = INCBIN_U16("graphics/battle_environment/cave_modern/palette.gbapal");
const u32 gBattleEnvironmentTilemap_CaveModern[] = INCBIN_U32("graphics/battle_environment/cave_modern/map.bin.smolTM");

const u32 gBattleEnvironmentTiles_BuildingModern[] = INCBIN_U32("graphics/battle_environment/building_modern/tiles.4bpp.smol");
const u16 gBattleEnvironmentPalette_BuildingModern[] = INCBIN_U16("graphics/battle_environment/building_modern/palette.gbapal");
const u32 gBattleEnvironmentTilemap_BuildingModern[] = INCBIN_U32("graphics/battle_environment/building_modern/map.bin.smolTM");

const u32 gBattleEnvironmentTiles_PlainModern[] = INCBIN_U32("graphics/battle_environment/plain_modern/tiles.4bpp.smol");
const u16 gBattleEnvironmentPalette_PlainModern[] = INCBIN_U16("graphics/battle_environment/plain_modern/palette.gbapal");
const u32 gBattleEnvironmentTilemap_PlainModern[] = INCBIN_U32("graphics/battle_environment/plain_modern/map.bin.smolTM");

const u32 gBattleEnvironmentTiles_StadiumModern[] = INCBIN_U32("graphics/battle_environment/stadium_modern/tiles.4bpp.smol");
const u32 gBattleEnvironmentTilemap_StadiumModern[] = INCBIN_U32("graphics/battle_environment/stadium_modern/map.bin.smolTM");

const u32 gBattleEnvironmentTiles_SkyModern[] = INCBIN_U32("graphics/battle_environment/sky_modern/tiles.4bpp.smol");
const u16 gBattleEnvironmentPalette_SkyModern[] = INCBIN_U16("graphics/battle_environment/sky_modern/palette.gbapal");
const u32 gBattleEnvironmentTilemap_SkyModern[] = INCBIN_U32("graphics/battle_environment/sky_modern/map.bin.smolTM");

extern const u32 gBattleEnvironmentTiles_BlueBuildingModern[88] __attribute__((alias("gBattleEnvironmentTiles_BuildingModern")));
const u16 gBattleEnvironmentPalette_BlueBuildingModern[] = INCBIN_U16("graphics/battle_environment/blue_building_modern/palette.gbapal");
extern const u32 gBattleEnvironmentTilemap_BlueBuildingModern[43] __attribute__((alias("gBattleEnvironmentTilemap_BuildingModern")));
extern const u32 gBattleEnvironmentAnimTiles_BlueBuildingModern[24] __attribute__((alias("gBattleEnvironmentAnimTiles_Building")));
extern const u32 gBattleEnvironmentAnimTilemap_BlueBuildingModern[38] __attribute__((alias("gBattleEnvironmentAnimTilemap_Building")));

const u16 gBattleEnvironmentPalette_GrayCaveModern[] = INCBIN_U16("graphics/battle_environment/cave_modern/gray_cave.gbapal");

const u32 gBattleEnvironmentTiles_CaveWaterModern[] = INCBIN_U32("graphics/battle_environment/cave_water_modern/tiles.4bpp.smol");
const u16 gBattleEnvironmentPalette_CaveWaterModern[] = INCBIN_U16("graphics/battle_environment/cave_water_modern/palette.gbapal");
const u32 gBattleEnvironmentTilemap_CaveWaterModern[] = INCBIN_U32("graphics/battle_environment/cave_water_modern/map.bin.smolTM");
const u32 gBattleEnvironmentAnimTiles_CaveWaterModern[] = INCBIN_U32("graphics/battle_environment/cave_water_modern/anim_tiles.4bpp.smol");
extern const u32 gBattleEnvironmentAnimTilemap_CaveWaterModern[41] __attribute__((alias("gBattleEnvironmentAnimTilemap_Volcano")));
const u16 gBattleEnvironmentPalette_GrayCaveWaterModern[] = INCBIN_U16("graphics/battle_environment/cave_water_modern/gray_cave.gbapal");

const u16 gBattleEnvironmentPalette_GroudonModern[] = INCBIN_U16("graphics/battle_environment/cave_modern/groudon.gbapal");
const u16 gBattleEnvironmentPalette_KyogreModern[] = INCBIN_U16("graphics/battle_environment/water_modern/kyogre.gbapal");
const u16 gBattleEnvironmentPalette_FrontierModern[] = INCBIN_U16("graphics/battle_environment/building_modern/battle_frontier.gbapal");

const u16 gBattleEnvironmentPalette_StadiumWill[] = INCBIN_U16("graphics/battle_environment/stadium_modern/will.gbapal");
const u16 gBattleEnvironmentPalette_StadiumKoga[] = INCBIN_U16("graphics/battle_environment/stadium_modern/koga.gbapal");
const u16 gBattleEnvironmentPalette_StadiumBruno[] = INCBIN_U16("graphics/battle_environment/stadium_modern/bruno.gbapal");
const u16 gBattleEnvironmentPalette_StadiumKaren[] = INCBIN_U16("graphics/battle_environment/stadium_modern/karen.gbapal");
const u16 gBattleEnvironmentPalette_StadiumLance[] = INCBIN_U16("graphics/battle_environment/stadium_modern/lance.gbapal");
const u16 gBattleEnvironmentPalette_StadiumLeaderModern[] = INCBIN_U16("graphics/battle_environment/stadium_modern/leader.gbapal");

// Modern time-of-day palettes
const u16 gBattleEnvironmentPalette_TallGrassModernMorning[] = INCBIN_U16("graphics/battle_environment/tall_grass_modern/palette_morning.gbapal");
const u16 gBattleEnvironmentPalette_TallGrassModernNight[] = INCBIN_U16("graphics/battle_environment/tall_grass_modern/palette_night.gbapal");
extern const u16 gBattleEnvironmentPalette_LongGrassModernNight[48] __attribute__((alias("gBattleEnvironmentPalette_TallGrassModernNight")));
const u16 gBattleEnvironmentPalette_SandModernMorning[] = INCBIN_U16("graphics/battle_environment/sand_modern/palette_morning.gbapal");
const u16 gBattleEnvironmentPalette_SandModernNight[] = INCBIN_U16("graphics/battle_environment/sand_modern/palette_night.gbapal");
const u16 gBattleEnvironmentPalette_WaterModernMorning[] = INCBIN_U16("graphics/battle_environment/water_modern/palette_morning.gbapal");
const u16 gBattleEnvironmentPalette_WaterModernNight[] = INCBIN_U16("graphics/battle_environment/water_modern/palette_night.gbapal");
const u16 gBattleEnvironmentPalette_PondWaterModernMorning[] = INCBIN_U16("graphics/battle_environment/pond_water_modern/palette_morning.gbapal");
const u16 gBattleEnvironmentPalette_PondWaterModernNight[] = INCBIN_U16("graphics/battle_environment/pond_water_modern/palette_night.gbapal");
const u16 gBattleEnvironmentPalette_RockModernMorning[] = INCBIN_U16("graphics/battle_environment/rock_modern/palette_morning.gbapal");
const u16 gBattleEnvironmentPalette_RockModernNight[] = INCBIN_U16("graphics/battle_environment/rock_modern/palette_night.gbapal");
const u16 gBattleEnvironmentPalette_RockSnowModernMorning[] = INCBIN_U16("graphics/battle_environment/rock_snow_modern/palette_morning.gbapal");
const u16 gBattleEnvironmentPalette_RockSnowModernNight[] = INCBIN_U16("graphics/battle_environment/rock_snow_modern/palette_night.gbapal");
extern const u16 gBattleEnvironmentPalette_MountainSnowModernMorning[48] __attribute__((alias("gBattleEnvironmentPalette_RockSnowModernMorning")));
extern const u16 gBattleEnvironmentPalette_MountainSnowModernNight[48] __attribute__((alias("gBattleEnvironmentPalette_RockSnowModernNight")));
const u16 gBattleEnvironmentPalette_PlainModernNight[] = INCBIN_U16("graphics/battle_environment/plain_modern/palette_night.gbapal");
const u16 gBattleEnvironmentPalette_SkyModernNight[] = INCBIN_U16("graphics/battle_environment/sky_modern/palette_night.gbapal");

extern const u32 gBattleEnvironmentAnimTiles_TallGrassModern[178] __attribute__((alias("gBattleEnvironmentAnimTiles_TallGrass")));
extern const u32 gBattleEnvironmentAnimTilemap_TallGrassModern[18] __attribute__((alias("gBattleEnvironmentAnimTilemap_TallGrass")));

extern const u32 gBattleEnvironmentAnimTiles_LongGrassModern[306] __attribute__((alias("gBattleEnvironmentAnimTiles_LongGrass")));
extern const u32 gBattleEnvironmentAnimTilemap_LongGrassModern[11] __attribute__((alias("gBattleEnvironmentAnimTilemap_LongGrass")));

extern const u32 gBattleEnvironmentAnimTiles_SandModern[129] __attribute__((alias("gBattleEnvironmentAnimTiles_Sand")));
extern const u32 gBattleEnvironmentAnimTilemap_SandModern[52] __attribute__((alias("gBattleEnvironmentAnimTilemap_Sand")));

const u32 gBattleEnvironmentAnimTiles_UnderwaterModern[] = INCBIN_U32("graphics/battle_environment/underwater_modern/anim_tiles.4bpp.smol");
extern const u32 gBattleEnvironmentAnimTilemap_UnderwaterModern[83] __attribute__((alias("gBattleEnvironmentAnimTilemap_Underwater")));

const u32 gBattleEnvironmentAnimTiles_WaterModern[] = INCBIN_U32("graphics/battle_environment/water_modern/anim_tiles.4bpp.smol");
extern const u32 gBattleEnvironmentAnimTilemap_WaterModern[19] __attribute__((alias("gBattleEnvironmentAnimTilemap_Water")));

extern const u32 gBattleEnvironmentAnimTiles_PondWaterModern[92] __attribute__((alias("gBattleEnvironmentAnimTiles_PondWater")));
extern const u32 gBattleEnvironmentAnimTilemap_PondWaterModern[15] __attribute__((alias("gBattleEnvironmentAnimTilemap_PondWater")));

extern const u32 gBattleEnvironmentAnimTiles_RockModern[138] __attribute__((alias("gBattleEnvironmentAnimTiles_Rock")));
extern const u32 gBattleEnvironmentAnimTilemap_RockModern[38] __attribute__((alias("gBattleEnvironmentAnimTilemap_Rock")));

const u32 gBattleEnvironmentTiles_RockSnowModern[] = INCBIN_U32("graphics/battle_environment/rock_snow_modern/tiles.4bpp.smol");
const u16 gBattleEnvironmentPalette_RockSnowModern[] = INCBIN_U16("graphics/battle_environment/rock_snow_modern/palette.gbapal");
const u32 gBattleEnvironmentTilemap_RockSnowModern[] = INCBIN_U32("graphics/battle_environment/rock_snow_modern/map.bin.smolTM");
extern const u32 gBattleEnvironmentAnimTiles_RockSnowModern[138] __attribute__((alias("gBattleEnvironmentAnimTiles_Rock")));
extern const u32 gBattleEnvironmentAnimTilemap_RockSnowModern[38] __attribute__((alias("gBattleEnvironmentAnimTilemap_Rock")));

const u32 gBattleEnvironmentTiles_MountainSnowModern[] = INCBIN_U32("graphics/battle_environment/mountain_snow_modern/tiles.4bpp.smol");
extern const u16 gBattleEnvironmentPalette_MountainSnowModern[48] __attribute__((alias("gBattleEnvironmentPalette_RockSnowModern")));
const u32 gBattleEnvironmentTilemap_MountainSnowModern[] = INCBIN_U32("graphics/battle_environment/mountain_snow_modern/map.bin.smolTM");
extern const u32 gBattleEnvironmentAnimTiles_MountainSnowModern[138] __attribute__((alias("gBattleEnvironmentAnimTiles_Rock")));
extern const u32 gBattleEnvironmentAnimTilemap_MountainSnowModern[38] __attribute__((alias("gBattleEnvironmentAnimTilemap_Rock")));

const u32 gBattleEnvironmentTiles_VolcanoModern[] = INCBIN_U32("graphics/battle_environment/volcano_modern/tiles.4bpp.smol");
const u16 gBattleEnvironmentPalette_VolcanoModern[] = INCBIN_U16("graphics/battle_environment/volcano_modern/palette.gbapal");
const u32 gBattleEnvironmentTilemap_VolcanoModern[] = INCBIN_U32("graphics/battle_environment/volcano_modern/map.bin.smolTM");
extern const u32 gBattleEnvironmentAnimTiles_VolcanoModern[303] __attribute__((alias("gBattleEnvironmentAnimTiles_CaveWaterModern")));
extern const u32 gBattleEnvironmentAnimTilemap_VolcanoModern[41] __attribute__((alias("gBattleEnvironmentAnimTilemap_Volcano")));

const u32 gBattleEnvironmentTiles_SnowCaveModern[] = INCBIN_U32("graphics/battle_environment/snow_cave_modern/tiles.4bpp.smol");
const u16 gBattleEnvironmentPalette_SnowCaveModern[] = INCBIN_U16("graphics/battle_environment/snow_cave_modern/palette.gbapal");
const u32 gBattleEnvironmentTilemap_SnowCaveModern[] = INCBIN_U32("graphics/battle_environment/snow_cave_modern/map.bin.smolTM");
extern const u32 gBattleEnvironmentAnimTiles_SnowCaveModern[303] __attribute__((alias("gBattleEnvironmentAnimTiles_CaveWaterModern")));
extern const u32 gBattleEnvironmentAnimTilemap_SnowCaveModern[41] __attribute__((alias("gBattleEnvironmentAnimTilemap_Volcano")));

extern const u32 gBattleEnvironmentAnimTiles_CaveModern[303] __attribute__((alias("gBattleEnvironmentAnimTiles_CaveWaterModern")));
extern const u32 gBattleEnvironmentAnimTilemap_CaveModern[41] __attribute__((alias("gBattleEnvironmentAnimTilemap_Volcano")));

extern const u32 gBattleEnvironmentAnimTiles_BuildingModern[24] __attribute__((alias("gBattleEnvironmentAnimTiles_Building")));
extern const u32 gBattleEnvironmentAnimTilemap_BuildingModern[38] __attribute__((alias("gBattleEnvironmentAnimTilemap_Building")));

const u32 gBattleEnvironmentAnimTiles_SkyModern[] = INCBIN_U32("graphics/battle_environment/sky_modern/anim_tiles.4bpp.smol");
extern const u32 gBattleEnvironmentAnimTilemap_SkyModern[14] __attribute__((alias("gBattleEnvironmentAnimTilemap_Rayquaza")));
