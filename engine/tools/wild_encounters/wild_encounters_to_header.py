import json
import re

class Config:
    def __init__(self, config_file_name, rtc_constants_file_name, encounters_json_data):
        self.times_of_day = None
        self.mon_types = None
        self.time_encounters = None
        self.disable_time_fallback = None
        self.time_fallback = None

        self.ParseTimeEnum(rtc_constants_file_name)
        if self.times_of_day == None:
            raise Exception(f"Failed to parse 'enum TimeOfDay' in '{rtc_constants_file_name}'")

        self.ParseMonTypes(encounters_json_data)
        if self.mon_types == None:
            raise Exception("No fields defined in 'wild_encounters.json'")

        with open(config_file_name, 'r') as config_file:
            lines = config_file.readlines()
            for line in lines:
                self.ParseTimeConfig(line)
        
        if self.time_encounters == None:
            raise Exception("OW_TIME_OF_DAY_ENCOUNTERS not defined.")
        if self.disable_time_fallback == None:
            raise Exception("OW_TIME_OF_DAY_DISABLE_FALLBACK not defined.")
        if self.time_fallback == None:
            raise Exception("OW_TIME_OF_DAY_FALLBACK not defined.")
    
    def ParseTimeEnum(self, rtc_constants_file_name):
        with open(rtc_constants_file_name, 'r') as rtc_constants_file:
            DEFAULT_TIME_PAT = re.compile(r"enum\s+TimeOfDay\s*\{(?P<rtc_val>[\s*\w+,\=\d*]+)\s*\}\s*\;")
            file = rtc_constants_file.read()

            m = DEFAULT_TIME_PAT.search(file)
            if m:
                txt = m.group('rtc_val')
                values = re.findall(r'TIME_\w+', txt)
                self.times_of_day = {}
                for value in values:
                    self.times_of_day[value] = value.title().replace("Time_", "").replace("_", "")

    def ParseMonTypes(self, encounters_json_data):
        for group in encounters_json_data["wild_encounter_groups"]:
            if "fields" in group:
                for field in group["fields"]:
                    field_type = field["type"]
                    if not self.mon_types:
                        self.mon_types = []
                    self.mon_types.append(field_type)

    def ParseTimeConfig(self, line):
        m = re.search(r'#define OW_TIME_OF_DAY_ENCOUNTERS\s+(\w+)', line)
        if m:
            self.time_encounters = m.group(1) == "TRUE"

        m = re.search(r'#define OW_TIME_OF_DAY_DISABLE_FALLBACK\s+(\w+)', line)
        if m:
            self.disable_time_fallback = m.group(1) == "TRUE"

        m = re.search(r'#define OW_TIME_OF_DAY_FALLBACK\s+(\w+)', line)
        if m:
            self.time_fallback = m.group(1)


class WildEncounterAssembler:
    def __init__(self, output_file, json_data, config):
        self.output_file = output_file
        self.json_data = json_data
        self.config = config
    
    def WriteLine(self, line="", indents = 0):
        self.output_file.write(4 * indents * " " + line + "\n")

    # Exact frozen map identities, including original optional-area dependencies.
    # Labels can contain their own Day/Night suffixes; they are not map identity.
    JOHTO_CAMPAIGN_MAPS = frozenset([
        'MAP_ARTISAN_CAVE_1F',
        'MAP_ARTISAN_CAVE_B1F',
        'MAP_AZALEA_TOWN_GYM_HNS',
        'MAP_AZALEA_TOWN_HNS',
        'MAP_AZALEA_TOWN_HOUSE1_HNS',
        'MAP_AZALEA_TOWN_KURTS_HOUSE_HNS',
        'MAP_AZALEA_TOWN_MART_HNS',
        'MAP_AZALEA_TOWN_POKEMON_CENTER_HNS',
        'MAP_BATTLE_COLOSSEUM_2P_HNS',
        'MAP_BATTLE_FRONTIER_BATTLE_ARENA_BATTLE_ROOM_HNS',
        'MAP_BATTLE_FRONTIER_BATTLE_ARENA_CORRIDOR_HNS',
        'MAP_BATTLE_FRONTIER_BATTLE_ARENA_LOBBY_HNS',
        'MAP_BATTLE_FRONTIER_BATTLE_DOME_BATTLE_ROOM_HNS',
        'MAP_BATTLE_FRONTIER_BATTLE_DOME_CORRIDOR_HNS',
        'MAP_BATTLE_FRONTIER_BATTLE_DOME_LOBBY_HNS',
        'MAP_BATTLE_FRONTIER_BATTLE_DOME_PRE_BATTLE_ROOM_HNS',
        'MAP_BATTLE_FRONTIER_BATTLE_FACTORY_BATTLE_ROOM_HNS',
        'MAP_BATTLE_FRONTIER_BATTLE_FACTORY_LOBBY_HNS',
        'MAP_BATTLE_FRONTIER_BATTLE_FACTORY_PRE_BATTLE_ROOM_HNS',
        'MAP_BATTLE_FRONTIER_BATTLE_PALACE_BATTLE_ROOM_HNS',
        'MAP_BATTLE_FRONTIER_BATTLE_PALACE_CORRIDOR_HNS',
        'MAP_BATTLE_FRONTIER_BATTLE_PALACE_LOBBY_HNS',
        'MAP_BATTLE_FRONTIER_BATTLE_PIKE_CORRIDOR_HNS',
        'MAP_BATTLE_FRONTIER_BATTLE_PIKE_LOBBY_HNS',
        'MAP_BATTLE_FRONTIER_BATTLE_PIKE_ROOM_FINAL_HNS',
        'MAP_BATTLE_FRONTIER_BATTLE_PIKE_ROOM_NORMAL_HNS',
        'MAP_BATTLE_FRONTIER_BATTLE_PIKE_ROOM_WILD_MONS_HNS',
        'MAP_BATTLE_FRONTIER_BATTLE_PIKE_THREE_PATH_ROOM_HNS',
        'MAP_BATTLE_FRONTIER_BATTLE_PYRAMID_FLOOR_HNS',
        'MAP_BATTLE_FRONTIER_BATTLE_PYRAMID_LOBBY_HNS',
        'MAP_BATTLE_FRONTIER_BATTLE_PYRAMID_TOP_HNS',
        'MAP_BATTLE_FRONTIER_BATTLE_TOWER_BATTLE_ROOM_HNS',
        'MAP_BATTLE_FRONTIER_BATTLE_TOWER_CORRIDOR_HNS',
        'MAP_BATTLE_FRONTIER_BATTLE_TOWER_ELEVATOR_HNS',
        'MAP_BATTLE_FRONTIER_BATTLE_TOWER_LOBBY_HNS',
        'MAP_BATTLE_FRONTIER_BATTLE_TOWER_MULTI_BATTLE_ROOM_HNS',
        'MAP_BATTLE_FRONTIER_BATTLE_TOWER_MULTI_CORRIDOR_HNS',
        'MAP_BATTLE_FRONTIER_BATTLE_TOWER_MULTI_PARTNER_ROOM_HNS',
        'MAP_BATTLE_FRONTIER_EXCHANGE_SERVICE_CORNER_HNS',
        'MAP_BATTLE_FRONTIER_LOUNGE1_HNS',
        'MAP_BATTLE_FRONTIER_LOUNGE2_HNS',
        'MAP_BATTLE_FRONTIER_LOUNGE3_HNS',
        'MAP_BATTLE_FRONTIER_LOUNGE4_HNS',
        'MAP_BATTLE_FRONTIER_LOUNGE5_HNS',
        'MAP_BATTLE_FRONTIER_LOUNGE6_HNS',
        'MAP_BATTLE_FRONTIER_LOUNGE7_HNS',
        'MAP_BATTLE_FRONTIER_LOUNGE8_HNS',
        'MAP_BATTLE_FRONTIER_LOUNGE9_HNS',
        'MAP_BATTLE_FRONTIER_MART_HNS',
        'MAP_BATTLE_FRONTIER_OUTSIDE_EAST_HNS',
        'MAP_BATTLE_FRONTIER_OUTSIDE_WEST_HNS',
        'MAP_BATTLE_FRONTIER_POKEMON_CENTER_1F_HNS',
        'MAP_BATTLE_FRONTIER_POKEMON_CENTER_2F_HNS',
        'MAP_BATTLE_FRONTIER_RANKING_HALL_HNS',
        'MAP_BATTLE_FRONTIER_RECEPTION_GATE_HNS',
        'MAP_BATTLE_FRONTIER_SCOTTS_HOUSE_HNS',
        'MAP_BATTLE_PYRAMID_SQUARE01_HNS',
        'MAP_BATTLE_PYRAMID_SQUARE02_HNS',
        'MAP_BATTLE_PYRAMID_SQUARE03_HNS',
        'MAP_BATTLE_PYRAMID_SQUARE04_HNS',
        'MAP_BATTLE_PYRAMID_SQUARE05_HNS',
        'MAP_BATTLE_PYRAMID_SQUARE06_HNS',
        'MAP_BATTLE_PYRAMID_SQUARE07_HNS',
        'MAP_BATTLE_PYRAMID_SQUARE08_HNS',
        'MAP_BATTLE_PYRAMID_SQUARE09_HNS',
        'MAP_BATTLE_PYRAMID_SQUARE10_HNS',
        'MAP_BATTLE_PYRAMID_SQUARE11_HNS',
        'MAP_BATTLE_PYRAMID_SQUARE12_HNS',
        'MAP_BATTLE_PYRAMID_SQUARE13_HNS',
        'MAP_BATTLE_PYRAMID_SQUARE14_HNS',
        'MAP_BATTLE_PYRAMID_SQUARE15_HNS',
        'MAP_BATTLE_PYRAMID_SQUARE16_HNS',
        'MAP_BELLCHIME_TRAIL_HNS',
        'MAP_BIRTH_ISLAND_EXTERIOR_HNS',
        'MAP_BIRTH_ISLAND_HARBOR_HNS',
        'MAP_BLACKTHORN_CITY_GYM_HNS',
        'MAP_BLACKTHORN_CITY_HNS',
        'MAP_BLACKTHORN_CITY_HOUSE1_HNS',
        'MAP_BLACKTHORN_CITY_HOUSE2_HNS',
        'MAP_BLACKTHORN_CITY_HOUSE3_HNS',
        'MAP_BLACKTHORN_CITY_MART_HNS',
        'MAP_BLACKTHORN_CITY_POKEMON_CENTER_HNS',
        'MAP_BURNED_TOWER_1F_HNS',
        'MAP_BURNED_TOWER_B1F_HNS',
        'MAP_CHERRYGROVE_CITY_HNS',
        'MAP_CHERRYGROVE_CITY_HOUSE1_HNS',
        'MAP_CHERRYGROVE_CITY_HOUSE2_HNS',
        'MAP_CHERRYGROVE_CITY_HOUSE3_HNS',
        'MAP_CHERRYGROVE_CITY_MART_HNS',
        'MAP_CHERRYGROVE_CITY_POKEMON_CENTER_HNS',
        'MAP_CIANWOOD_CITY_HNS',
        'MAP_CIANWOOD_GYM_HNS',
        'MAP_CIANWOOD_HOUSE1_HNS',
        'MAP_CIANWOOD_HOUSE2_HNS',
        'MAP_CIANWOOD_HOUSE3_HNS',
        'MAP_CIANWOOD_POKECENTER_HNS',
        'MAP_CIANWOOD_SHOP_HNS',
        'MAP_CLIFF_EDGE_CAVE_HNS',
        'MAP_CLIFF_EDGE_GATE_HNS',
        'MAP_DARK_CAVE_NORTH_SIDE_HNS',
        'MAP_DARK_CAVE_SOUTH_SIDE_HNS',
        'MAP_DRAGONS_DEN_CAVERN_HNS',
        'MAP_DRAGONS_DEN_ENTRANCE_HNS',
        'MAP_DRAGONS_DEN_SHRINE_HNS',
        'MAP_ECRUTEAK_CITY_GYM_HNS',
        'MAP_ECRUTEAK_CITY_HNS',
        'MAP_ECRUTEAK_CITY_HOUSE1_HNS',
        'MAP_ECRUTEAK_CITY_HOUSE2_HNS',
        'MAP_ECRUTEAK_CITY_MART_HNS',
        'MAP_ECRUTEAK_CITY_POKEMON_CENTER_HNS',
        'MAP_ECRUTEAK_CITY_SAGE_OFFICE1_HNS',
        'MAP_ECRUTEAK_CITY_SAGE_OFFICE2_HNS',
        'MAP_ECRUTEAK_CITY_THEATER_HNS',
        'MAP_EMBEDDED_TOWER_HNS',
        'MAP_FALLARBOR_TOWN_BATTLE_TENT_BATTLE_ROOM_HNS',
        'MAP_FALLARBOR_TOWN_BATTLE_TENT_CORRIDOR_HNS',
        'MAP_FALLARBOR_TOWN_BATTLE_TENT_LOBBY_HNS',
        'MAP_FARAWAY_ISLAND_ENTRANCE_HNS',
        'MAP_FARAWAY_ISLAND_INTERIOR_HNS',
        'MAP_GATE_AZALEA_TOWN_ILEX_FOREST_HNS',
        'MAP_GATE_ECRUTEAK_CITY_ROUTE38_HNS',
        'MAP_GATE_ECRUTEAK_CITY_ROUTE42_HNS',
        'MAP_GATE_GOLDENROD_CITY_ROUTE35_HNS',
        'MAP_GATE_ILEX_FOREST_ROUTE34_HNS',
        'MAP_GATE_MAHOGANY_TOWN_ROUTE43_HNS',
        'MAP_GATE_NATIONAL_PARK_HNS',
        'MAP_GATE_ROUTE29_ROUTE46_HNS',
        'MAP_GATE_ROUTE31_VIOLET_CITY_HNS',
        'MAP_GATE_ROUTE40_TRAINER_HILL_COURTYARD_HNS',
        'MAP_GATE_ROUTE43_HNS',
        'MAP_GATE_RUINS_OF_ALPH_ROUTE32_HNS',
        'MAP_GATE_RUINS_OF_ALPH_ROUTE36_HNS',
        'MAP_GOLDENROD_CITY_BIKE_SHOP_HNS',
        'MAP_GOLDENROD_CITY_BILLS_HOUSE_HNS',
        'MAP_GOLDENROD_CITY_DEPARTMENT_STORE_1F_HNS',
        'MAP_GOLDENROD_CITY_DEPARTMENT_STORE_2F_HNS',
        'MAP_GOLDENROD_CITY_DEPARTMENT_STORE_3F_HNS',
        'MAP_GOLDENROD_CITY_DEPARTMENT_STORE_4F_HNS',
        'MAP_GOLDENROD_CITY_DEPARTMENT_STORE_5F_HNS',
        'MAP_GOLDENROD_CITY_DEPARTMENT_STORE_6F_HNS',
        'MAP_GOLDENROD_CITY_DEPARTMENT_STORE_7FNIGHT_HNS',
        'MAP_GOLDENROD_CITY_DEPARTMENT_STORE_7F_HNS',
        'MAP_GOLDENROD_CITY_DEPARTMENT_STORE_BASEMENT_HNS',
        'MAP_GOLDENROD_CITY_DEPARTMENT_STORE_ELEVATOR_HNS',
        'MAP_GOLDENROD_CITY_FLOWER_SHOP_HNS',
        'MAP_GOLDENROD_CITY_GAME_CORNER_HNS',
        'MAP_GOLDENROD_CITY_GYM_HNS',
        'MAP_GOLDENROD_CITY_HNS',
        'MAP_GOLDENROD_CITY_HOUSE1_HNS',
        'MAP_GOLDENROD_CITY_HOUSE2_HNS',
        'MAP_GOLDENROD_CITY_HOUSE3_HNS',
        'MAP_GOLDENROD_CITY_POKEMON_CENTER_HNS',
        'MAP_GOLDENROD_CITY_RADIO_TOWER_1F_HNS',
        'MAP_GOLDENROD_CITY_RADIO_TOWER_2F_HNS',
        'MAP_GOLDENROD_CITY_RADIO_TOWER_3F_HNS',
        'MAP_GOLDENROD_CITY_RADIO_TOWER_4F_HNS',
        'MAP_GOLDENROD_CITY_RADIO_TOWER_5F_HNS',
        'MAP_GOLDENROD_CITY_TRAIN_STATION_HNS',
        'MAP_GOLDENROD_CITY_UNDERGROUND_ENTRANCE_HNS',
        'MAP_GOLDENROD_CITY_UNDERGROUND_STORAGE_HNS',
        'MAP_GOLDENROD_CITY_UNDERGROUND_SWITCHES_HNS',
        'MAP_GOLDENROD_CITY_UNDERGROUND_TUNNEL_HNS',
        'MAP_ICE_PATH_1F_HNS',
        'MAP_ICE_PATH_B1F_HNS',
        'MAP_ICE_PATH_B2F_HNS',
        'MAP_ICE_PATH_B3F_HNS',
        'MAP_ICE_PATH_B4F_HNS',
        'MAP_ILEX_FOREST_HNS',
        'MAP_INDIGO_PLATEAU_HNS',
        'MAP_INDIGO_PLATEAU_POKEMON_CENTER_HNS',
        'MAP_LAKE_OF_RAGE_HNS',
        'MAP_LAKE_OF_RAGE_HOUSE1_HNS',
        'MAP_LAKE_OF_RAGE_HOUSE2_HNS',
        'MAP_LAKE_OF_RAGE_LOW_TIDE_HNS',
        'MAP_MAHOGANYTOWN_HNS',
        'MAP_MAHOGANY_TOWN_GYM_HNS',
        'MAP_MAHOGANY_TOWN_HOUSE1_HNS',
        'MAP_MAHOGANY_TOWN_POKEMON_CENTER_HNS',
        'MAP_MAHOGANY_TOWN_SHOP_HNS',
        'MAP_MT_MORTAR_1F_NORTH_HNS',
        'MAP_MT_MORTAR_1F_SOUTH_HNS',
        'MAP_MT_MORTAR_2F_HNS',
        'MAP_MT_MORTAR_B1F_HNS',
        'MAP_MT_SILVER_1F_ITEM_ROOM_HNS',
        'MAP_MT_SILVER_1F_MOLTRES_ROOM_HNS',
        'MAP_MT_SILVER_1F_WATERFALL_ROOM_HNS',
        'MAP_MT_SILVER_2F_HNS',
        'MAP_MT_SILVER_3F_HNS',
        'MAP_MT_SILVER_MOUNTAIN_SIDE_HNS',
        'MAP_MT_SILVER_OUTSIDE_HNS',
        'MAP_MT_SILVER_POKEMON_CENTER_HNS',
        'MAP_MT_SILVER_SNOW_HNS',
        'MAP_MT_SILVER_SUMMIT_DAY_HNS',
        'MAP_MT_SILVER_SUMMIT_NIGHT_HNS',
        'MAP_NATIONAL_PARK_BUG_CONTEST_HNS',
        'MAP_NATIONAL_PARK_NORMAL_HNS',
        'MAP_NEWSINJOH_HOTSPRINGS_HNS',
        'MAP_NEW_BARK_TOWN_HNS',
        'MAP_NEW_BARK_TOWN_HOUSE1_HNS',
        'MAP_NEW_BARK_TOWN_HOUSE2_HNS',
        'MAP_NEW_BARK_TOWN_LAB_HNS',
        'MAP_NEW_BARK_TOWN_PLAYERS_HOUSE_1F_HNS',
        'MAP_NEW_BARK_TOWN_PLAYERS_HOUSE_2F_HNS',
        'MAP_NEW_SINJOH_HNS',
        'MAP_NEW_SINJOH_HOUSE1_HNS',
        'MAP_NEW_SINJOH_HOUSE2_HNS',
        'MAP_NEW_SINJOH_HOUSE3_HNS',
        'MAP_NEW_SINJOH_HOUSE4_HNS',
        'MAP_NEW_SINJOH_KIMONO_HIDEOUT_HNS',
        'MAP_NEW_SINJOH_POKEMON_CENTER_HNS',
        'MAP_OLIVINE_CITY_CAFE_HNS',
        'MAP_OLIVINE_CITY_GYM_HNS',
        'MAP_OLIVINE_CITY_HNS',
        'MAP_OLIVINE_CITY_HOUSE1_HNS',
        'MAP_OLIVINE_CITY_HOUSE2_HNS',
        'MAP_OLIVINE_CITY_HOUSE3_HNS',
        'MAP_OLIVINE_CITY_LIGHTHOUSE_HNS',
        'MAP_OLIVINE_CITY_MART_HNS',
        'MAP_OLIVINE_CITY_POKEMON_CENTER_HNS',
        'MAP_OLIVINE_CITY_PORT_INSIDE_HNS',
        'MAP_OLIVINE_CITY_PORT_OUTSIDE_HNS',
        'MAP_POKEMON_LEAGUE_BRUNOS_ROOM_HNS',
        'MAP_POKEMON_LEAGUE_CHAMPIONS_ROOM_HNS',
        'MAP_POKEMON_LEAGUE_HALL_OF_FAME_HNS',
        'MAP_POKEMON_LEAGUE_KARENS_ROOM_HNS',
        'MAP_POKEMON_LEAGUE_KOGAS_ROOM_HNS',
        'MAP_POKEMON_LEAGUE_WILLS_ROOM_HNS',
        'MAP_RECEPTION_GATE_HNS',
        'MAP_ROCKET_HIDEOUT_B1F_HNS',
        'MAP_ROCKET_HIDEOUT_B2F_HNS',
        'MAP_ROCKET_HIDEOUT_B3F_HNS',
        'MAP_ROUTE22_HNS',
        'MAP_ROUTE23_HNS',
        'MAP_ROUTE26NORTH_HNS',
        'MAP_ROUTE26_HNS',
        'MAP_ROUTE26_HOUSE1_HNS',
        'MAP_ROUTE26_HOUSE2_HNS',
        'MAP_ROUTE27_HNS',
        'MAP_ROUTE27_HOUSE_HNS',
        'MAP_ROUTE28_HNS',
        'MAP_ROUTE28_HOUSE_HNS',
        'MAP_ROUTE29_HNS',
        'MAP_ROUTE30_HNS',
        'MAP_ROUTE30_HOUSE_HNS',
        'MAP_ROUTE30_MR_POKEMONS_HOUSE_HNS',
        'MAP_ROUTE31_HNS',
        'MAP_ROUTE32_HNS',
        'MAP_ROUTE32_POKEMON_CENTER_HNS',
        'MAP_ROUTE33_HNS',
        'MAP_ROUTE34_DAY_CARE_HNS',
        'MAP_ROUTE34_HNS',
        'MAP_ROUTE35_HNS',
        'MAP_ROUTE36_HNS',
        'MAP_ROUTE37_HNS',
        'MAP_ROUTE38_HNS',
        'MAP_ROUTE39_BARN_HNS',
        'MAP_ROUTE39_FARM_HOUSE_HNS',
        'MAP_ROUTE39_HNS',
        'MAP_ROUTE40_HNS',
        'MAP_ROUTE41_HNS',
        'MAP_ROUTE42_HNS',
        'MAP_ROUTE43_HNS',
        'MAP_ROUTE44_HNS',
        'MAP_ROUTE45_HNS',
        'MAP_ROUTE46_HNS',
        'MAP_ROUTE47_HNS',
        'MAP_ROUTE48_HNS',
        'MAP_ROUTE49_HNS',
        'MAP_ROUTE50_HNS',
        'MAP_RUINS_OF_ALPH_B1F_HNS',
        'MAP_RUINS_OF_ALPH_LAB_HNS',
        'MAP_RUINS_OF_ALPH_OUTSIDE_HNS',
        'MAP_RUINS_OF_ALPH_PUZZLE_AND_REWARD_CHAMBERS_HNS',
        'MAP_RUINS_OF_ALPH_WORDS_ROOM1_HNS',
        'MAP_RUINS_OF_ALPH_WORDS_ROOM2_HNS',
        'MAP_RUINS_OF_ALPH_WORDS_ROOM3_HNS',
        'MAP_RUINS_OF_ALPH_WORDS_ROOM4_HNS',
        'MAP_SAFARI_ZONE1_HNS',
        'MAP_SAFARI_ZONE2_HNS',
        'MAP_SAFARI_ZONE3_HNS',
        'MAP_SAFARI_ZONE_ENTERANCE_HNS',
        'MAP_SAFARI_ZONE_GATE_HNS',
        'MAP_SAFARI_ZONE_GATE_POKEMON_CENTER_HNS',
        'MAP_SAFARI_ZONE_GATE_SAFARI_ZONE_ENTRANCE_HNS',
        'MAP_SAFARI_ZONE_INDOOR_HNS',
        'MAP_SAFARI_ZONE_LOW_LEFT_HNS',
        'MAP_SAFARI_ZONE_LOW_MID_HNS',
        'MAP_SAFARI_ZONE_LOW_RIGHT_HNS',
        'MAP_SAFARI_ZONE_TOP_LEFT_HNS',
        'MAP_SAFARI_ZONE_TOP_MID_HNS',
        'MAP_SAFARI_ZONE_TOP_RIGHT_HNS',
        'MAP_SAFFRON_TEMP_HNS',
        'MAP_SINJOH_RUINS_ARCEUS_ROOM_HNS',
        'MAP_SINJOH_RUINS_HNS',
        'MAP_SINJOH_RUINS_HOUSE1_HNS',
        'MAP_SINJOH_RUINS_REGICE_ROOM_HNS',
        'MAP_SINJOH_RUINS_REGIDRACO_ROOM_HNS',
        'MAP_SINJOH_RUINS_REGIELEKI_ROOM_HNS',
        'MAP_SINJOH_RUINS_REGIGIGAS_ROOM_HNS',
        'MAP_SINJOH_RUINS_REGIROCK_ROOM_HNS',
        'MAP_SINJOH_RUINS_REGISTEEL_ROOM_HNS',
        'MAP_SINJOH_RUINS_TEMPLE_HNS',
        'MAP_SLATEPORT_CITY_BATTLE_TENT_BATTLE_ROOM_HNS',
        'MAP_SLATEPORT_CITY_BATTLE_TENT_CORRIDOR_HNS',
        'MAP_SLATEPORT_CITY_BATTLE_TENT_LOBBY_HNS',
        'MAP_SLOWPOKE_WELL_B1F_HNS',
        'MAP_SLOWPOKE_WELL_B2F_HNS',
        'MAP_SNOWSWEPT_CAVERN_HNS',
        'MAP_SOUTHERN_ISLAND_EXTERIOR_HNS',
        'MAP_SOUTHERN_ISLAND_INTERIOR_HNS',
        'MAP_SPROUT_TOWER_1F_HNS',
        'MAP_SPROUT_TOWER_2F_HNS',
        'MAP_SPROUT_TOWER_3F_HNS',
        'MAP_SSAQUA_1F_HNS',
        'MAP_SSAQUA_B1F_HNS',
        'MAP_SSAQUA_CAPTAINS_ROOM_HNS',
        'MAP_SSAQUA_PLAYERS_ROOM_HNS',
        'MAP_SSAQUA_ROOM_NE_HNS',
        'MAP_SSAQUA_ROOM_NNE_HNS',
        'MAP_SSAQUA_ROOM_NW_HNS',
        'MAP_SSAQUA_ROOM_SE_HNS',
        'MAP_SSAQUA_ROOM_SSE_HNS',
        'MAP_SSAQUA_ROOM_SSW_HNS',
        'MAP_SSAQUA_ROOM_SW_HNS',
        'MAP_TEST_MAP1_HNS',
        'MAP_TEST_MAP2_HNS',
        'MAP_TIN_TOWER_1F_HNS',
        'MAP_TIN_TOWER_2F_HNS',
        'MAP_TIN_TOWER_3F_HNS',
        'MAP_TIN_TOWER_4F_HNS',
        'MAP_TIN_TOWER_5F_HNS',
        'MAP_TIN_TOWER_6F_HNS',
        'MAP_TIN_TOWER_7F_HNS',
        'MAP_TIN_TOWER_8F_HNS',
        'MAP_TIN_TOWER_9F_HNS',
        'MAP_TIN_TOWER_ROOF_DAY_HNS',
        'MAP_TIN_TOWER_ROOF_NIGHT_HNS',
        'MAP_TOHJO_FALLS_CAVERN_HNS',
        'MAP_TOHJO_FALLS_GIOVANNI_ROOM_HNS',
        'MAP_TRADE_CENTER',
        'MAP_TRADE_CENTER_HNS',
        'MAP_TRAINER_HILL_1F_HNS',
        'MAP_TRAINER_HILL_2F_HNS',
        'MAP_TRAINER_HILL_3F_HNS',
        'MAP_TRAINER_HILL_4F_HNS',
        'MAP_TRAINER_HILL_COURTYARD_HNS',
        'MAP_TRAINER_HILL_ELEVATOR_HNS',
        'MAP_TRAINER_HILL_ENTRANCE_HNS',
        'MAP_TRAINER_HILL_ROOF_HNS',
        'MAP_UNION_CAVE_1F_HNS',
        'MAP_UNION_CAVE_B1F_HNS',
        'MAP_UNION_CAVE_B2F_HNS',
        'MAP_UNION_ROOM',
        'MAP_VERDANTURF_TOWN_BATTLE_TENT_BATTLE_ROOM_HNS',
        'MAP_VERDANTURF_TOWN_BATTLE_TENT_CORRIDOR_HNS',
        'MAP_VERDANTURF_TOWN_BATTLE_TENT_LOBBY_HNS',
        'MAP_VICTORY_ROAD_KANTO_1F_HNS',
        'MAP_VICTORY_ROAD_KANTO_B1F_HNS',
        'MAP_VICTORY_ROAD_KANTO_B2F_HNS',
        'MAP_VIOLET_CITY_GYM_HNS',
        'MAP_VIOLET_CITY_HNS',
        'MAP_VIOLET_CITY_HOUSE1_HNS',
        'MAP_VIOLET_CITY_HOUSE2_HNS',
        'MAP_VIOLET_CITY_MART_HNS',
        'MAP_VIOLET_CITY_POKEMON_CENTER_HNS',
        'MAP_VIOLET_CITY_TRAINER_SCHOOL_HNS',
        'MAP_WHIRL_ISLANDS_1F_HNS',
        'MAP_WHIRL_ISLANDS_B1F_HNS',
        'MAP_WHIRL_ISLANDS_B1F_INNER_HNS',
        'MAP_WHIRL_ISLANDS_B2F_HNS',
        'MAP_WHIRL_ISLANDS_B3F_HNS',
        'MAP_WHIRL_ISLANDS_DESCENT_HNS',
        'MAP_WHIRL_ISLANDS_LUGIA_CHAMBER_HNS',
    ])

    def WriteVersionGuard(self, version, shared_label, map_name):
        if map_name in self.JOHTO_CAMPAIGN_MAPS and version in ("POKEMON_HNS", "EMERALD"):
            self.WriteLine(f"#if defined({version}) || defined(FIRERED)")
        else:
            self.WriteLine(f"#ifdef {version}")

    def WriteHeader(self):
        self.WriteLine("//")
        self.WriteLine("// DO NOT MODIFY THIS FILE! It is auto-generated by tools/wild_encounters/wild_encounters_to_header.py")
        self.WriteLine("//")
        self.output_file.write("\n\n")

    def WriteMacro(self, macro, value):
        self.output_file.write("#define " + macro + " " + value + "\n")

    def WriteMacros(self):
        wild_encounter_groups = self.json_data["wild_encounter_groups"]
        for wild_encounter_group in wild_encounter_groups:
            if "fields" in wild_encounter_group:
                fields = wild_encounter_group["fields"]
                for field in fields:
                    field_type = field["type"]
                    macro_base = "ENCOUNTER_CHANCE_" + field_type.upper()
                    previous_group = None
                    previous_macro = None
                    encounter_rates = field["encounter_rates"]

                    group_name_mapping = len(encounter_rates) * [""]
                    if "groups" in field:
                        groups = field["groups"]
                        for group_name, indices in groups.items():
                            for index in indices:
                                group_name_mapping[index] = "_" + group_name.upper()
                    
                    for idx, rate in enumerate(encounter_rates):
                        macro_name = macro_base + group_name_mapping[idx] + "_SLOT_" + str(idx)
                        macro_value = str(rate)
                        if previous_group == group_name_mapping[idx]:
                            macro_value = "(" + previous_macro + " + " + macro_value + ")"
                        elif idx > 0:
                            macro_total_name = macro_base + group_name_mapping[idx - 1] + "_TOTAL"
                            self.WriteMacro(macro_total_name, "(" + previous_macro + ")")
                        self.WriteMacro(macro_name, macro_value)
                        previous_group = group_name_mapping[idx]
                        previous_macro = macro_name
                        if idx == len(encounter_rates) - 1:
                            macro_total_name = macro_base + group_name_mapping[idx] + "_TOTAL"
                            self.WriteMacro(macro_total_name, "(" + previous_macro + ")")
                    macro_total_name = macro_base + group_name_mapping[-1] + "_TOTAL"
                    self.WriteLine()
    
    def WriteMonInfos(self, name, mons, encounter_rate):
        info_name = name + "Info"
        self.WriteLine(f"const struct WildPokemon {name}[] =")
        self.WriteLine("{")
        for mon in mons:
            species = mon["species"]
            min_level = 2 if "min_level" not in mon else mon["min_level"]
            max_level = 100 if "max_level" not in mon else mon["max_level"]
            self.WriteLine(f"{{ {min_level}, {max_level}, {species} }},", 1)

        self.WriteLine("};")
        self.WriteLine()
        self.WriteLine(f"const struct WildPokemonInfo {info_name} = {{ {encounter_rate}, {name} }};")
        self.WriteLine()
    
    def WriteTerminator(self):
        self.WriteLine("{", 1)
        self.WriteLine(".mapGroup = MAP_GROUP(MAP_UNDEFINED),", 2)
        self.WriteLine(".mapNum = MAP_NUM(MAP_UNDEFINED),", 2)
        self.WriteLine(".encounterTypes =", 2)
        self.WriteLine("{", 2)
        for time in self.config.times_of_day:
            if not self.config.time_encounters and time != self.config.time_fallback:
                continue
            self.WriteLine(f"[{time}] =", 3)
            self.WriteLine("{", 3)
            for mon_type in self.config.mon_types:
                member_name = mon_type.title().replace("_", "")
                member_name = member_name[0].lower() + member_name[1:] + "Info"
                self.WriteLine(f".{member_name} = NULL,", 4)
            self.WriteLine("},", 3)
        self.WriteLine("},", 2)
        self.WriteLine("},", 1)

    def WritePokemonHeaders(self, headers):
        label = headers["label"]
        self.WriteLine(f"const struct WildPokemonHeader {label}[] =")
        self.WriteLine("{")
        for shared_label in headers["data"]:
            self.WriteLine()
            map_data = headers["data"][shared_label]
            encounter_data = map_data
            map_group = map_data["mapGroup"]
            map_num = map_data["mapNum"]
            version = "EMERALD"
            if "FireRed" in shared_label:
                version = "FIRERED"
            elif "LeafGreen" in shared_label:
                version = "LEAFGREEN"
            elif "_Hns" in shared_label or "_hns" in shared_label:
                version = "POKEMON_HNS"

            self.WriteVersionGuard(version, shared_label, map_data["map_name"])

            self.WriteLine("{", 1)
            self.WriteLine(f".mapGroup = {map_group},", 2)
            self.WriteLine(f".mapNum = {map_num},", 2)
            self.WriteLine(".encounterTypes =", 2)
            self.WriteLine("{", 2)
            for time in self.config.times_of_day:
                if not self.config.time_encounters and time != self.config.time_fallback:
                    continue
                self.WriteLine(f"[{time}] =", 4)
                self.WriteLine("{", 4)
                for mon_type in self.config.mon_types:
                    member_name = mon_type.title().replace("_", "")
                    member_name = member_name[0].lower() + member_name[1:] + "Info"
                    value = "NULL"
                    if time in encounter_data and mon_type in encounter_data[time]:
                        value = encounter_data[time][mon_type]
                    if value != "NULL":
                        value = "&" + value
                    self.WriteLine(f".{member_name} = {value},", 5)

                self.WriteLine("},", 3)
            
            self.WriteLine("},", 2)
            self.WriteLine("},", 1)
            self.WriteLine(f"#endif")
        self.WriteTerminator()
        self.WriteLine("};")


    def WriteEncounters(self):
        wild_encounter_groups = self.json_data["wild_encounter_groups"]
        for wild_encounter_group in wild_encounter_groups:
            headers = {}
            headers["label"] = wild_encounter_group["label"]
            headers["data"] = {}
            for_maps = False
            map_num_counter = 1
            if "for_maps" in wild_encounter_group:
                for_maps = wild_encounter_group["for_maps"]
            encounters = wild_encounter_group["encounters"]

            for map_encounters in encounters:
                map_group = "0"
                map_num = str(map_num_counter)
                if for_maps:
                    map_name = map_encounters["map"]
                    map_group = f"MAP_GROUP({map_name})"
                    map_num = f"MAP_NUM({map_name})"
                map_num_counter += 1
                base_label = map_encounters["base_label"]
                shared_label = base_label
                time = self.config.time_fallback

                for time_ident in self.config.times_of_day:
                    if self.config.times_of_day[time_ident] in base_label:
                        time = time_ident
                        shared_label = shared_label.replace('_' + self.config.times_of_day[time_ident], '')

                if shared_label not in headers["data"]:
                    headers["data"][shared_label] = {}
                if time not in headers["data"][shared_label]:
                    headers["data"][shared_label][time] = {}
                headers["data"][shared_label]["mapGroup"] = map_group
                headers["data"][shared_label]["mapNum"] = map_num
                headers["data"][shared_label]["map_name"] = map_name if for_maps else None

                version = "EMERALD"
                if "FireRed" in shared_label:
                    version = "FIRERED"
                elif "LeafGreen" in shared_label:
                    version = "LEAFGREEN"
                elif "_Hns" in shared_label or "_hns" in shared_label:
                    version = "POKEMON_HNS"
                self.WriteVersionGuard(version, shared_label, map_name if for_maps else None)
                for mon_type in self.config.mon_types:
                    if mon_type not in map_encounters:
                        headers["data"][shared_label][mon_type] = "NULL"
                        continue
                    
                    mons_entry = map_encounters[mon_type]
                    encounter_rate = mons_entry["encounter_rate"]
                    mons = mons_entry["mons"]

                    mon_array_name = base_label + "_" + mon_type.title().replace("_", "")
                    self.WriteMonInfos(mon_array_name, mons, encounter_rate)
                    headers["data"][shared_label][time][mon_type] = mon_array_name + "Info"
                self.WriteLine(f"#endif")

            self.WritePokemonHeaders(headers)


def ConvertToHeaderFile(json_data):
    with open('src/data/wild_encounters.h', 'w') as output_file:
        config = Config('include/config/overworld.h', 'include/constants/rtc.h', json_data)
        assembler = WildEncounterAssembler(output_file, json_data, config)
        assembler.WriteHeader()
        assembler.WriteMacros()
        assembler.WriteEncounters()

def main():
    with open('src/data/wild_encounters.json', 'r') as json_file:
        json_data = json.load(json_file)
        ConvertToHeaderFile(json_data)
        

if __name__ == '__main__':
    main()
