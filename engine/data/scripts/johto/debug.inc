@ Johto (data/scripts/debug.inc), as built into the FireRed game.

J_Debug_MessageEnd:
	waitmessage
	waitbuttonpress
	releaseall
	end

J_Debug_ShowFieldMessageStringVar4::
	special ShowFieldMessageStringVar4
	goto J_Debug_MessageEnd

J_Debug_CheatStart::
	setflag FLAG_SYS_POKEMON_GET
	setflag FLAG_RESCUED_BIRCH
	setflag FLAG_HIDE_ROUTE_101_BIRCH_ZIGZAGOON_BATTLE
	setflag JOHTO_FLAG_ADVENTURE_STARTED
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_BIRCH
	setflag FLAG_HIDE_ROUTE_101_BIRCH_STARTERS_BAG
	setvar JOHTO_VAR_BIRCH_LAB_STATE, 2
	setvar JOHTO_VAR_ROUTE101_STATE, 3
	givemon SPECIES_TREECKO, 20, ITEM_NONE
	givemon SPECIES_TORCHIC, 20, ITEM_NONE
	givemon SPECIES_MUDKIP, 20, ITEM_NONE
	setflag FLAG_SYS_POKEDEX_GET
	special SetUnlockedPokedexFlags
	setflag JOHTO_FLAG_RECEIVED_POKEDEX_FROM_BIRCH
	setvar JOHTO_VAR_CABLE_CLUB_TUTORIAL_STATE, 2
	setflag FLAG_SYS_NATIONAL_DEX
	special EnableNationalPokedex
	setflag JOHTO_FLAG_RECEIVED_RUNNING_SHOES
	setflag FLAG_SYS_B_DASH
	setvar JOHTO_VAR_LITTLEROOT_TOWN_STATE, 4
	setvar JOHTO_VAR_LITTLEROOT_INTRO_STATE, 7
	setvar JOHTO_VAR_LITTLEROOT_HOUSES_STATE_BRENDAN, 2
	setvar JOHTO_VAR_LITTLEROOT_HOUSES_STATE_MAY, 2
	setvar JOHTO_VAR_LITTLEROOT_RIVAL_STATE, 4
	setflag JOHTO_FLAG_RECEIVED_BIKE
	additem ITEM_ACRO_BIKE
	setvar JOHTO_VAR_BRINEY_HOUSE_STATE, 1
	setvar JOHTO_VAR_ROUTE116_STATE, 2
	setflag FLAG_HIDE_ROUTE_116_MR_BRINEY
	setflag JOHTO_FLAG_BADGE01_GET
	setflag JOHTO_FLAG_BADGE02_GET
	setflag JOHTO_FLAG_BADGE03_GET
	setflag JOHTO_FLAG_BADGE04_GET
	setflag JOHTO_FLAG_BADGE05_GET
	setflag JOHTO_FLAG_BADGE06_GET
	setflag JOHTO_FLAG_BADGE07_GET
	setflag JOHTO_FLAG_BADGE08_GET
	setflag FLAG_VISITED_LITTLEROOT_TOWN
	setflag FLAG_VISITED_OLDALE_TOWN
	setflag FLAG_VISITED_DEWFORD_TOWN
	setflag FLAG_VISITED_LAVARIDGE_TOWN
	setflag FLAG_VISITED_FALLARBOR_TOWN
	setflag FLAG_VISITED_VERDANTURF_TOWN
	setflag FLAG_VISITED_PACIFIDLOG_TOWN
	setflag FLAG_VISITED_PETALBURG_CITY
	setflag FLAG_VISITED_SLATEPORT_CITY
	setflag FLAG_VISITED_MAUVILLE_CITY
	setflag FLAG_VISITED_RUSTBORO_CITY
	setflag FLAG_VISITED_FORTREE_CITY
	setflag FLAG_VISITED_LILYCOVE_CITY
	setflag FLAG_VISITED_MOSSDEEP_CITY
	setflag FLAG_VISITED_SOOTOPOLIS_CITY
	setflag FLAG_VISITED_EVER_GRANDE_CITY
	setflag FLAG_LANDMARK_POKEMON_LEAGUE
	setflag JOHTO_FLAG_LANDMARK_BATTLE_FRONTIER
	clearflag FLAG_HIDE_BRINEYS_HOUSE_MR_BRINEY
	clearflag FLAG_HIDE_BRINEYS_HOUSE_PEEKO
	release
	end

J_Debug_CheatStartFrlg::
	setflag FLAG_SYS_POKEMON_GET
	setflag JOHTO_FLAG_PALLET_LADY_NOT_BLOCKING_SIGN
	setflag JOHTO_FLAG_OPENED_START_MENU
	setflag JOHTO_FLAG_VISITED_OAKS_LAB
	setflag JOHTO_FLAG_BEAT_RIVAL_IN_OAKS_LAB
	givemon SPECIES_BULBASAUR, 20, ITEM_NONE
	givemon SPECIES_CHARMANDER, 20, ITEM_NONE
	givemon SPECIES_SQUIRTLE, 20, ITEM_NONE
	clearflag JOHTO_FLAG_HIDE_OAK_IN_HIS_LAB
	setflag JOHTO_FLAG_HIDE_RIVAL_IN_LAB
	setvar JOHTO_VAR_MAP_SCENE_PALLET_TOWN_OAK, 1
	setflag FLAG_SYS_POKEDEX_GET
	special SetUnlockedPokedexFlags
	setvar JOHTO_VAR_MAP_SCENE_PALLET_TOWN_PROFESSOR_OAKS_LAB, 6
	setvar JOHTO_VAR_MAP_SCENE_VIRIDIAN_CITY_MART, 2
	setvar JOHTO_VAR_MAP_SCENE_VIRIDIAN_CITY_OLD_MAN, 1
	setvar JOHTO_VAR_MAP_SCENE_PALLET_TOWN_RIVALS_HOUSE, 1
	setvar JOHTO_VAR_MAP_SCENE_ROUTE22, 1
	setvar JOHTO_VAR_MAP_SCENE_POKEMON_CENTER_TEALA, 1
	setflag FLAG_SYS_NATIONAL_DEX
	special EnableNationalPokedex
	setflag FLAG_SYS_B_DASH
	setflag JOHTO_FLAG_BADGE01_GET
	setflag JOHTO_FLAG_BADGE02_GET
	setflag JOHTO_FLAG_BADGE03_GET
	setflag JOHTO_FLAG_BADGE04_GET
	setflag JOHTO_FLAG_BADGE05_GET
	setflag JOHTO_FLAG_BADGE06_GET
	setflag JOHTO_FLAG_BADGE07_GET
	setflag JOHTO_FLAG_BADGE08_GET
	setflag JOHTO_FLAG_GOT_BIKE_VOUCHER
	setflag JOHTO_FLAG_GOT_BICYCLE
	additem ITEM_BICYCLE
	setflag JOHTO_FLAG_WORLD_MAP_PALLET_TOWN
	setflag JOHTO_FLAG_WORLD_MAP_VIRIDIAN_CITY
	setflag JOHTO_FLAG_WORLD_MAP_PEWTER_CITY
	setflag JOHTO_FLAG_WORLD_MAP_ROUTE4_POKEMON_CENTER_1F
	setflag JOHTO_FLAG_WORLD_MAP_CERULEAN_CITY
	setflag JOHTO_FLAG_WORLD_MAP_VERMILION_CITY
	setflag JOHTO_FLAG_WORLD_MAP_ROUTE10_POKEMON_CENTER_1F
	setflag JOHTO_FLAG_WORLD_MAP_LAVENDER_TOWN
	setflag JOHTO_FLAG_WORLD_MAP_CELADON_CITY
	setflag JOHTO_FLAG_WORLD_MAP_FUCHSIA_CITY
	setflag JOHTO_FLAG_WORLD_MAP_SAFFRON_CITY
	setflag JOHTO_FLAG_WORLD_MAP_CINNABAR_ISLAND
	setflag JOHTO_FLAG_WORLD_MAP_INDIGO_PLATEAU_EXTERIOR
	setflag JOHTO_FLAG_WORLD_MAP_ONE_ISLAND
	setflag JOHTO_FLAG_WORLD_MAP_TWO_ISLAND
	setflag JOHTO_FLAG_WORLD_MAP_THREE_ISLAND
	setflag JOHTO_FLAG_WORLD_MAP_FOUR_ISLAND
	setflag JOHTO_FLAG_WORLD_MAP_FIVE_ISLAND
	setflag JOHTO_FLAG_WORLD_MAP_SIX_ISLAND
	setflag JOHTO_FLAG_WORLD_MAP_SEVEN_ISLAND
	release
	end

J_Debug_FlagsNotSetOverworldConfigMessage::
	message J_Debug_FlagsNotSetOverworldConfigMessage_Text
	goto J_Debug_MessageEnd

J_Debug_FlagsNotSetOverworldConfigMessage_Text:
	.string "Featur{SE_M_REVERSAL}unavailable!\n"
	.string "Pleas{SE_M_REVERSAL}defin{SE_M_REVERSAL}{SE_M_CHARGE}usabl{SE_M_REVERSAL}fla{SE_M_SANDSTORM}in:\l"
	.string "'include/config/overworld.h'!$"

J_Debug_FlagsNotSetBattleConfigMessage::
	message J_Debug_FlagsNotSetBattleConfigMessage_Text
	goto J_Debug_MessageEnd

J_Debug_FlagsNotSetBattleConfigMessage_Text:
	.string "Featur{SE_M_REVERSAL}unavailable!\n"
	.string "Pleas{SE_M_REVERSAL}defin{SE_M_REVERSAL}{SE_M_CHARGE}usabl{SE_M_REVERSAL}fla{SE_M_SANDSTORM}in:\l"
	.string "'include/config/battle.h'!$"

J_Debug_VarsNotSetBattleConfigMessage::
	message J_Debug_VarsNotSetBattleConfigMessage_Text
	goto J_Debug_MessageEnd

J_Debug_VarsNotSetBattleConfigMessage_Text:
	.string "Featur{SE_M_REVERSAL}unavailable!\n"
	.string "Pleas{SE_M_REVERSAL}defin{SE_M_REVERSAL}{SE_M_CHARGE}usabl{SE_M_REVERSAL}va{SE_M_SAND_TOMB}in:\l"
	.string "'include/config/battle.h'!$"

J_Debug_BoxFilledMessage::
	message J_Debug_BoxFilledMessage_Text
	goto J_Debug_MessageEnd

J_Debug_BoxFilledMessage_Text:
	.string "Storag{SE_M_REVERSAL}boxe{SE_M_GRASSWHISTLE}filled!$"

J_Debug_EventScript_CheckEVs::
	lockall
	getpartysize
	goto_if_eq VAR_RESULT, 0, J_Debug_NoPokemon
	special ChoosePartyMon
	waitstate
	goto_if_ge VAR_0x8004, PARTY_SIZE, J_Debug_EventScript_CheckEVs_End
	callnative Script_GetChosenMonOffensiveEVs
	msgbox J_Debug_EventScript_Text_OffensiveEVs, MSGBOX_DEFAULT
	callnative Script_GetChosenMonDefensiveEVs
	msgbox J_Debug_EventScript_Text_DefensiveEVs, MSGBOX_DEFAULT

J_Debug_EventScript_CheckEVs_End::
	releaseall
	end

J_Debug_EventScript_Text_OffensiveEVs:
	.string "AT{SE_M_SNORE}EVs{SE_M_HEAT_WAVE}{STR_VAR_1}{SE_M_SUPERSONIC}SPAT{SE_M_SNORE}EVs{SE_M_HEAT_WAVE}{STR_VAR_2}{SE_M_SUPERSONIC}SPEE{SE_M_FAINT_ATTACK}EVs{SE_M_HEAT_WAVE}{STR_VAR_3}$"

J_Debug_EventScript_Text_DefensiveEVs:
	.string "H{SE_M_PETAL_DANCE}EVs{SE_M_HEAT_WAVE}{STR_VAR_1}{SE_M_SUPERSONIC}DE{SE_M_LEER}EVs{SE_M_HEAT_WAVE}{STR_VAR_2}{SE_M_SUPERSONIC}SPDE{SE_M_LEER}EVs{SE_M_HEAT_WAVE}{STR_VAR_3}$"

J_Debug_EventScript_CheckIVs::
	lockall
	getpartysize
	goto_if_eq VAR_RESULT, 0, J_Debug_NoPokemon
	special ChoosePartyMon
	waitstate
	goto_if_ge VAR_0x8004, PARTY_SIZE, J_Debug_EventScript_CheckIVs_End
	callnative Script_GetChosenMonOffensiveIVs
	msgbox J_Debug_EventScript_Text_OffensiveIVs, MSGBOX_DEFAULT
	callnative Script_GetChosenMonDefensiveIVs
	msgbox J_Debug_EventScript_Text_DefensiveIVs, MSGBOX_DEFAULT

J_Debug_EventScript_CheckIVs_End::
	releaseall
	end

J_Debug_EventScript_Text_OffensiveIVs:
	.string "AT{SE_M_SNORE}IVs{SE_M_HEAT_WAVE}{STR_VAR_1}{SE_M_SUPERSONIC}SPAT{SE_M_SNORE}IVs{SE_M_HEAT_WAVE}{STR_VAR_2}{SE_M_SUPERSONIC}SPEE{SE_M_FAINT_ATTACK}IVs{SE_M_HEAT_WAVE}{STR_VAR_3}$"

J_Debug_EventScript_Text_DefensiveIVs:
	.string "H{SE_M_PETAL_DANCE}IVs{SE_M_HEAT_WAVE}{STR_VAR_1}{SE_M_SUPERSONIC}DE{SE_M_LEER}IVs{SE_M_HEAT_WAVE}{STR_VAR_2}{SE_M_SUPERSONIC}SPDE{SE_M_LEER}IVs{SE_M_HEAT_WAVE}{STR_VAR_3}$"

J_Debug_EventScript_Script_1::
	goto UnionCave_B2F_EventScript_Lapras
	release
	end

J_Debug_Text_1:
	.string "{STR_VAR_1}$"

J_Debug_EventScript_Script_2::
	finditem ITEM_POTION
	giveitem ITEM_SUPER_POTION
	release
	end

J_Debug_EventScript_Script_3::
	goto SinjohRuins_EventScript_StevenBattle
	release
	end

J_Debug_EventScript_Script_4::
	msgbox SinjohRuins_Lab_Text_StevenCall3Plates, MSGBOX_DEFAULT
	pokenavcall SinjohRuins_Lab_Text_StevenCall6Plates
	release
	end

J_Debug_EventScript_Script_5::
	special InitKantoRoamers
	release
	end

J_Debug_EventScript_Script_6::
	lockall
	setvar JOHTO_VAR_FRONTIER_FACILITY, FRONTIER_FACILITY_TOWER
	setvar JOHTO_VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES
	frontier_settrainers
	setvar VAR_TRAINER_BATTLE_OPPONENT_A, FRONTIER_TRAINER_LEADER_BROCK_HNS
	special HealPlayerParty
	dofacilitytrainerbattle FACILITY_BATTLE_TOWER
	waitstate
	special HealPlayerParty
	releaseall
	end

J_Debug_EventScript_Script_7::
	release
	end

J_Debug_EventScript_Script_8::
	release
	end

J_Debug_EventScript_Lance_Multi::
	special SavePlayerParty
	fadescreen FADE_TO_BLACK
	special ChooseHalfPartyForBattle
	waitstate
	goto_if_ne VAR_RESULT, 0, J_Debug_EventScript_DoLanceMultiBattle
	special LoadPlayerParty
	release
	end

J_Debug_EventScript_DoLanceMultiBattle::
	multi_2_vs_2 TRAINER_JOHTO_ARIANA_1_HNS, J_Debug_Text_ArianaDefeat, TRAINER_JOHTO_GRUNT_23_HNS, J_Debug_Text_Grunt23Defeat, PARTNER_LANCE_HNS
	switch VAR_RESULT
	case 1, J_Debug_EventScript_LanceMultiWin
	fadescreen FADE_TO_BLACK
	special SetCB2WhiteOut
	waitstate

J_Debug_EventScript_LanceMultiWin::
	msgbox J_Debug_Text_LanceMultiVictory, MSGBOX_DEFAULT
	release
	end

J_Debug_Text_ArianaDefeat:
	.string "Yo{SE_M_DIVE}haven'{SE_M_SPIT_UP}see{SE_M_ATTRACT}th{SE_M_REVERSAL}las{SE_M_SPIT_UP}o{SE_M_ACID_ARMOR}me!$"

J_Debug_Text_Grunt23Defeat:
	.string "{SE_M_HEAL_BELL}won'{SE_M_SPIT_UP}accep{SE_M_SPIT_UP}this!$"

J_Debug_Text_LanceMultiVictory:
	.string "Lanc{SE_M_REVERSAL}mult{SE_M_TRI_ATTACK2}battl{SE_M_REVERSAL}complete!$"

J_Debug_EventScript_Silver_Multi::
	special SavePlayerParty
	fadescreen FADE_TO_BLACK
	special ChooseHalfPartyForBattle
	waitstate
	goto_if_ne VAR_RESULT, 0, J_Debug_EventScript_PickSilverPartner
	special LoadPlayerParty
	release
	end

J_Debug_EventScript_PickSilverPartner::
	switch JOHTO_VAR_STARTER_MON
	case 0, J_Debug_EventScript_DoSilverMulti_Typhlosion
	case 1, J_Debug_EventScript_DoSilverMulti_Feraligatr
	case 2, J_Debug_EventScript_DoSilverMulti_Meganium
	goto J_Debug_EventScript_DoSilverMulti_Typhlosion

J_Debug_EventScript_DoSilverMulti_Typhlosion::
	multi_2_vs_2 TRAINER_JOHTO_LANCE_3_HNS, J_Debug_Text_Lance3Defeat, TRAINER_JOHTO_CLAIR_3_HNS, J_Debug_Text_Clair3Defeat, PARTNER_SILVER_TYPHLOSION_HNS
	goto J_Debug_EventScript_SilverMultiResult

J_Debug_EventScript_DoSilverMulti_Feraligatr::
	multi_2_vs_2 TRAINER_JOHTO_LANCE_3_HNS, J_Debug_Text_Lance3Defeat, TRAINER_JOHTO_CLAIR_3_HNS, J_Debug_Text_Clair3Defeat, PARTNER_SILVER_FERALIGATR_HNS
	goto J_Debug_EventScript_SilverMultiResult

J_Debug_EventScript_DoSilverMulti_Meganium::
	multi_2_vs_2 TRAINER_JOHTO_LANCE_3_HNS, J_Debug_Text_Lance3Defeat, TRAINER_JOHTO_CLAIR_3_HNS, J_Debug_Text_Clair3Defeat, PARTNER_SILVER_MEGANIUM_HNS
	goto J_Debug_EventScript_SilverMultiResult

J_Debug_EventScript_SilverMultiResult::
	switch VAR_RESULT
	case 1, J_Debug_EventScript_SilverMultiWin
	fadescreen FADE_TO_BLACK
	special SetCB2WhiteOut
	waitstate

J_Debug_EventScript_SilverMultiWin::
	msgbox J_Debug_Text_SilverMultiVictory, MSGBOX_DEFAULT
	release
	end

J_Debug_Text_SilverMultiVictory:
	.string "Silve{SE_M_SAND_TOMB}mult{SE_M_TRI_ATTACK2}battl{SE_M_REVERSAL}complete!$"

J_Debug_Text_Lance3Defeat:
	.string "Yo{SE_M_DIVE}haven'{SE_M_SPIT_UP}see{SE_M_ATTRACT}th{SE_M_REVERSAL}las{SE_M_SPIT_UP}o{SE_M_ACID_ARMOR}me!$"

J_Debug_Text_Clair3Defeat:
	.string "{SE_M_HEAL_BELL}won'{SE_M_SPIT_UP}accep{SE_M_SPIT_UP}this!$"

J_Debug_CheckSaveBlock::
	callnative CheckSaveBlock1Size
	msgbox J_Debug_SaveBlock1Size, MSGBOX_DEFAULT
	callnative CheckSaveBlock2Size
	msgbox J_Debug_SaveBlock2Size, MSGBOX_DEFAULT
	callnative CheckSaveBlock3Size
	msgbox J_Debug_SaveBlock3Size, MSGBOX_DEFAULT
	callnative CheckPokemonStorageSize
	msgbox J_Debug_PokemonStorageSize, MSGBOX_DEFAULT
	release
	end

J_Debug_SaveBlock1Size::
	.string "SaveBlock{SE_M_HEADBUTT}size{SE_M_HEAT_WAVE}{STR_VAR_1}b/{STR_VAR_2}b.\n"
	.string "Fre{SE_M_REVERSAL}space{SE_M_HEAT_WAVE}{STR_VAR_3}b.$"

J_Debug_SaveBlock2Size::
	.string "SaveBlock{SE_M_SURF}size{SE_M_HEAT_WAVE}{STR_VAR_1}b/{STR_VAR_2}b.\n"
	.string "Fre{SE_M_REVERSAL}space{SE_M_HEAT_WAVE}{STR_VAR_3}b.$"

J_Debug_SaveBlock3Size::
	.string "SaveBlock{SE_M_HYDRO_PUMP}size{SE_M_HEAT_WAVE}{STR_VAR_1}b/{STR_VAR_2}b.\n"
	.string "Fre{SE_M_REVERSAL}space{SE_M_HEAT_WAVE}{STR_VAR_3}b.$"

J_Debug_PokemonStorageSize::
	.string "{PKMN}Storag{SE_M_REVERSAL}size{SE_M_HEAT_WAVE}{STR_VAR_1}b/{STR_VAR_2}b.\n"
	.string "Fre{SE_M_REVERSAL}space{SE_M_HEAT_WAVE}{STR_VAR_3}b.$"

J_Debug_CheckROMSpace::
	callnative CheckROMSize
	msgbox J_Debug_ROMSize, MSGBOX_DEFAULT
	release
	end

J_Debug_ROMSize::
	.string "RO{SE_M_GIGA_DRAIN}size{SE_M_HEAT_WAVE}{STR_VAR_1}MB/32MB.\n"
	.string "Fre{SE_M_REVERSAL}space{SE_M_HEAT_WAVE}{STR_VAR_2}MB.$"

J_Debug_HatchAnEgg::
	lockall
	getpartysize
	goto_if_eq VAR_RESULT, 0, J_Debug_NoPokemon
	special ChoosePartyMon
	waitstate
	goto_if_ge VAR_0x8004, PARTY_SIZE, J_Debug_HatchAnEgg_End
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	goto_if_ne VAR_RESULT, (1572 + 1), J_DebugScript_HatchAnEgg_CantForceHatch
	special EggHatch
	waitstate

J_Debug_HatchAnEgg_End::
	releaseall
	end

J_Debug_NoPokemon::
	msgbox J_DebugScript_Text_EmptyParty, MSGBOX_DEFAULT
	releaseall
	end

J_DebugScript_HatchAnEgg_CantForceHatch::
	msgbox J_DebugScript_HatchAnEgg_Text_NotAnEgg, MSGBOX_DEFAULT
	releaseall
	end

J_DebugScript_Text_EmptyParty::
	.string "Yo{SE_M_DIVE}hav{SE_M_REVERSAL}n{SE_M_ATTRACT2}Pokémo{SE_M_ATTRACT}no{SE_M_SAND_TOMB}Eggs.$"

J_DebugScript_HatchAnEgg_Text_NotAnEgg::
	.string "That'{SE_M_GRASSWHISTLE}no{SE_M_SPIT_UP}{SE_M_CHARGE}Pokémo{SE_M_ATTRACT}Egg.$"

J_DebugScript_ZeroDaycareMons::
	msgbox J_DebugText_DaycareNoPokemon, MSGBOX_DEFAULT
	releaseall
	end

J_DebugScript_OneDaycareMons::
	msgbox J_DebugText_DaycareOnePokemon, MSGBOX_DEFAULT
	releaseall
	end

J_DebugScript_DaycareMonsNotCompatible::
	msgbox J_DebugText_DaycarePokemonNotCompatible, MSGBOX_DEFAULT
	releaseall
	end

J_DebugText_DaycareNoPokemon:
	.string "Yo{SE_M_DIVE}hav{SE_M_REVERSAL}n{SE_M_ATTRACT2}Pokémo{SE_M_ATTRACT}a{SE_M_SPIT_UP}Daycare.$"

J_DebugText_DaycareOnePokemon:
	.string "Yo{SE_M_DIVE}hav{SE_M_REVERSAL}onl{SE_M_YAWN}on{SE_M_REVERSAL}Pokémo{SE_M_ATTRACT}a{SE_M_SPIT_UP}Daycare.$"

J_DebugText_DaycarePokemonNotCompatible:
	.string "You{SE_M_SAND_TOMB}Pokémo{SE_M_ATTRACT}a{SE_M_SPIT_UP}Daycar{SE_M_REVERSAL}can't\nhav{SE_M_REVERSAL}babie{SE_M_GRASSWHISTLE}together!$"

J_Debug_ShowExpansionVersion::
	callnative BufferExpansionVersion
	msgbox J_Debug_ExpansionVersion, MSGBOX_DEFAULT
	release
	end

J_Debug_ExpansionVersion:
	.string "pokeemerald-expansio{SE_M_ATTRACT}{STR_VAR_1}$"

J_Debug_Follower_NPC_Not_Enabled::
	msgbox J_Debug_Enable_To_Use_Follower_NPCs, MSGBOX_DEFAULT
	release
	end

J_Debug_Enable_To_Use_Follower_NPCs:
	.string "Featur{SE_M_REVERSAL}unavailable.\nSe{SE_M_SPIT_UP}FNPC-ENABLE-NPC-FOLLOWER{SE_M_SKETCH}to\lTRU{SE_M_SWORDS_DANCE}i{SE_M_ATTRACT}'include/config/follower-npc.h'.$"

J_Debug_Follower_NPC_Event_Script::
	lock
	facefollowernpc
	msgbox J_Debug_Follower_NPC_Test_Message, MSGBOX_DEFAULT
	releaseall
	end

J_Debug_Follower_NPC_Test_Message:
	.string "Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}Followe{SE_M_SAND_TOMB}NP{SE_M_PSYBEAM}test.$"

J_Debug_EventScript_Steven_Multi::
	call MossdeepCity_SpaceCenter_2F_EventScript_ChoosePartyForMultiBattle
	release
	end

J_Debug_EventScript_WallyTutorial::
	special SavePlayerParty
	special LoadWallyZigzagoon
	special StartWallyTutorialBattle
	waitstate
	special LoadPlayerParty
	release
	end

J_Debug_BerryPestsDisabled::
	msgbox J_DebugText_BerryPestsDisabled, MSGBOX_DEFAULT
	release
	end

J_DebugText_BerryPestsDisabled:
	.string "OW-BERRY-PEST{SE_M_SKETCH}i{SE_M_GRASSWHISTLE}disabled.\n"
	.string "Unabl{SE_M_REVERSAL}t{SE_M_ATTRACT2}forc{SE_M_REVERSAL}pest{SE_M_GRASSWHISTLE}ont{SE_M_ATTRACT2}berr{SE_M_YAWN}trees.$"

J_Debug_BerryWeedsDisabled::
	msgbox J_DebugText_BerryWeedsDisabled, MSGBOX_DEFAULT
	release
	end

J_DebugText_BerryWeedsDisabled:
	.string "OW-BERRY-WEED{SE_M_SKETCH}i{SE_M_GRASSWHISTLE}disabled.\n"
	.string "Unabl{SE_M_REVERSAL}t{SE_M_ATTRACT2}forc{SE_M_REVERSAL}weed{SE_M_GRASSWHISTLE}ont{SE_M_ATTRACT2}berr{SE_M_YAWN}trees.$"

J_Debug_EventScript_InflictStatus1::
	lockall
	getpartysize
	goto_if_eq VAR_RESULT, 0, J_Debug_NoPokemon
	dynmultipush J_Debug_EventScript_InflictStatus1_Text_Single, 0
	dynmultipush J_Debug_EventScript_InflictStatus1_Text_PartyWide, 1
	dynmultipush J_Debug_EventScript_InflictStatus1_Text_Close, 2
	dynmultistack 0, 0, FALSE, 3 FALSE, 0, NULL
	switch VAR_RESULT
	case 0, J_Debug_EventScript_InflictStatus1_Single
	case 1, J_Debug_EventScript_InflictStatus1_Party
	case 2, J_Debug_EventScript_InflictStatus1_Close

J_Debug_EventScript_InflictStatus1_Close:
	releaseall
	end

J_Debug_EventScript_InflictStatus1_Single:
	special ChoosePartyMon
	waitstate
	goto_if_ge VAR_0x8004, PARTY_SIZE, J_Debug_EventScript_InflictStatus1_Close
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	goto_if_eq VAR_RESULT, (1572 + 1), J_Debug_EventScript_InflictStatus1_Close
	dynmultipush J_Debug_EventScript_InflictStatus1_Text_Poison, 0
	dynmultipush J_Debug_EventScript_InflictStatus1_Text_Paralysis, 1
	dynmultipush J_Debug_EventScript_InflictStatus1_Text_Sleep, 2
	dynmultipush J_Debug_EventScript_InflictStatus1_Text_Burn, 3
	dynmultipush J_Debug_EventScript_InflictStatus1_Text_Freeze, 4
	dynmultipush J_Debug_EventScript_InflictStatus1_Text_Frostbite, 5
	dynmultipush J_Debug_EventScript_InflictStatus1_Text_Close, 6
	dynmultistack 0, 0, FALSE, 7, FALSE, 0, NULL
	switch VAR_RESULT
	case 0, J_Debug_EventScript_InflictStatus1_Single_Poison
	case 1, J_Debug_EventScript_InflictStatus1_Single_Paralysis
	case 2, J_Debug_EventScript_InflictStatus1_Single_Sleep
	case 3, J_Debug_EventScript_InflictStatus1_Single_Burn
	case 4, J_Debug_EventScript_InflictStatus1_Single_Freeze
	case 5, J_Debug_EventScript_InflictStatus1_Single_Frostbite
	case 6, J_Debug_EventScript_InflictStatus1_Close
	case MULTI_B_PRESSED, J_Debug_EventScript_InflictStatus1_Close
	releaseall
	end

J_Debug_EventScript_KoPokemon::
	special ChoosePartyMon
	waitstate
	goto_if_ge VAR_0x8004, PARTY_SIZE, J_Debug_EventScript_InflictStatus1_Close
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	goto_if_eq VAR_RESULT, (1572 + 1), J_Debug_EventScript_InflictStatus1_Close
	setko VAR_0x8004
	releaseall
	end

J_Debug_EventScript_SetHiddenNature::
	special ChoosePartyMon
	waitstate
	goto_if_ge VAR_0x8004, PARTY_SIZE, J_Debug_EventScript_InflictStatus1_Close
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	goto_if_eq VAR_RESULT, (1572 + 1), J_Debug_EventScript_InflictStatus1_Close
	dynmultipush J_Debug_EventScript_ChangeNature_Text_Hardy, 0
	dynmultipush J_Debug_EventScript_ChangeNature_Text_Lonely, 1
	dynmultipush J_Debug_EventScript_ChangeNature_Text_Brave, 2
	dynmultipush J_Debug_EventScript_ChangeNature_Text_Adamant, 3
	dynmultipush J_Debug_EventScript_ChangeNature_Text_Naughty, 4
	dynmultipush J_Debug_EventScript_ChangeNature_Text_Bold, 5
	dynmultipush J_Debug_EventScript_ChangeNature_Text_Docile, 6
	dynmultipush J_Debug_EventScript_ChangeNature_Text_Relaxed, 7
	dynmultipush J_Debug_EventScript_ChangeNature_Text_Impish, 8
	dynmultipush J_Debug_EventScript_ChangeNature_Text_Lax, 9
	dynmultipush J_Debug_EventScript_ChangeNature_Text_Timid, 10
	dynmultipush J_Debug_EventScript_ChangeNature_Text_Hasty, 11
	dynmultipush J_Debug_EventScript_ChangeNature_Text_Serious, 12
	dynmultipush J_Debug_EventScript_ChangeNature_Text_Jolly, 13
	dynmultipush J_Debug_EventScript_ChangeNature_Text_Naive, 14
	dynmultipush J_Debug_EventScript_ChangeNature_Text_Modest, 15
	dynmultipush J_Debug_EventScript_ChangeNature_Text_Mild, 16
	dynmultipush J_Debug_EventScript_ChangeNature_Text_Quiet, 17
	dynmultipush J_Debug_EventScript_ChangeNature_Text_Bashful, 18
	dynmultipush J_Debug_EventScript_ChangeNature_Text_Rash, 19
	dynmultipush J_Debug_EventScript_ChangeNature_Text_Calm, 20
	dynmultipush J_Debug_EventScript_ChangeNature_Text_Gentle, 21
	dynmultipush J_Debug_EventScript_ChangeNature_Text_Sassy, 22
	dynmultipush J_Debug_EventScript_ChangeNature_Text_Careful, 23
	dynmultipush J_Debug_EventScript_ChangeNature_Text_Quirky, 24
	dynmultistack 0, 0, TRUE, 7, FALSE, 0, NULL
	switch VAR_RESULT
	case MULTI_B_PRESSED, J_Debug_EventScript_InflictStatus1_Close
	special SetHiddenNature
	releaseall
	end

J_Debug_EventScript_SetAbility::
	special ChoosePartyMon
	waitstate
	callnative DebugNative_GetAbilityNames
	dynmultipush gStringVar1, 0
	dynmultipush gStringVar2, 1
	dynmultipush gStringVar3, 2
	dynmultistack 0, 0, FALSE, 3 FALSE, 0, NULL
	switch VAR_RESULT
	case MULTI_B_PRESSED, J_Debug_EventScript_SetAbilityClose
	special SetAbility

J_Debug_EventScript_SetAbilityClose:
	releaseall
	end

J_Debug_EventScript_SetFriendship::
	special ChoosePartyMon
	waitstate
	callnative DebugNative_Party_SetFriendship
	releaseall
	end

J_Debug_EventScript_GivePokerus::
	special ChoosePartyMon
	waitstate
	callnative DebugNative_Party_SetPokerus
	releaseall
	end

J_Debug_EventScript_InflictStatus1_Single_Poison:
	setstatus1 (1 << 3), VAR_0x8004
	releaseall
	end

J_Debug_EventScript_InflictStatus1_Single_Paralysis:
	setstatus1 (1 << 6), VAR_0x8004
	releaseall
	end

J_Debug_EventScript_InflictStatus1_Single_Sleep:
	setstatus1 (1 << 0 | 1 << 1 | 1 << 2), VAR_0x8004
	releaseall
	end

J_Debug_EventScript_InflictStatus1_Single_Burn:
	setstatus1 (1 << 4), VAR_0x8004
	releaseall
	end

J_Debug_EventScript_InflictStatus1_Single_Freeze:
	setstatus1 (1 << 5), VAR_0x8004
	releaseall
	end

J_Debug_EventScript_InflictStatus1_Single_Frostbite:
	setstatus1 (1 << 12), VAR_0x8004
	releaseall
	end

J_Debug_EventScript_InflictStatus1_Party:
	dynmultipush J_Debug_EventScript_InflictStatus1_Text_Poison, 0
	dynmultipush J_Debug_EventScript_InflictStatus1_Text_Paralysis, 1
	dynmultipush J_Debug_EventScript_InflictStatus1_Text_Sleep, 2
	dynmultipush J_Debug_EventScript_InflictStatus1_Text_Burn, 3
	dynmultipush J_Debug_EventScript_InflictStatus1_Text_Freeze, 4
	dynmultipush J_Debug_EventScript_InflictStatus1_Text_Frostbite, 5
	dynmultipush J_Debug_EventScript_InflictStatus1_Text_Close, 6
	dynmultistack 0, 0, FALSE, 7, FALSE, 0, NULL
	switch VAR_RESULT
	case 0, J_Debug_EventScript_InflictStatus1_Party_Poison
	case 1, J_Debug_EventScript_InflictStatus1_Party_Paralysis
	case 2, J_Debug_EventScript_InflictStatus1_Party_Sleep
	case 3, J_Debug_EventScript_InflictStatus1_Party_Burn
	case 4, J_Debug_EventScript_InflictStatus1_Party_Freeze
	case 5, J_Debug_EventScript_InflictStatus1_Party_Frostbite
	case 6, J_Debug_EventScript_InflictStatus1_Close
	case MULTI_B_PRESSED, J_Debug_EventScript_InflictStatus1_Close
	releaseall
	end

J_Debug_EventScript_InflictStatus1_Party_Poison:
	setstatus1 (1 << 3), PARTY_SIZE
	releaseall
	end

J_Debug_EventScript_InflictStatus1_Party_Paralysis:
	setstatus1 (1 << 6), PARTY_SIZE
	releaseall
	end

J_Debug_EventScript_InflictStatus1_Party_Sleep:
	setstatus1 (1 << 0 | 1 << 1 | 1 << 2), PARTY_SIZE
	releaseall
	end

J_Debug_EventScript_InflictStatus1_Party_Burn:
	setstatus1 (1 << 4), PARTY_SIZE
	releaseall
	end

J_Debug_EventScript_InflictStatus1_Party_Freeze:
	setstatus1 (1 << 5), PARTY_SIZE
	releaseall
	end

J_Debug_EventScript_InflictStatus1_Party_Frostbite:
	setstatus1 (1 << 12), PARTY_SIZE
	releaseall
	end

J_Debug_EventScript_InflictStatus1_Text_Single:
	.string "Single$"

J_Debug_EventScript_InflictStatus1_Text_PartyWide:
	.string "Party-wide$"

J_Debug_EventScript_InflictStatus1_Text_Close:
	.string "Close$"

J_Debug_EventScript_InflictStatus1_Text_Poison:
	.string "Poison$"

J_Debug_EventScript_InflictStatus1_Text_Paralysis:
	.string "Paralysis$"

J_Debug_EventScript_InflictStatus1_Text_Sleep:
	.string "Sleep$"

J_Debug_EventScript_InflictStatus1_Text_Burn:
	.string "Burn$"

J_Debug_EventScript_InflictStatus1_Text_Freeze:
	.string "Freeze$"

J_Debug_EventScript_InflictStatus1_Text_Frostbite:
	.string "Frostbite$"

J_Debug_EventScript_InflictStatus1_Text_KO:
	.string "KO$"

J_Debug_EventScript_ChangeNature_Text_Hardy:
	.string "Hardy$"

J_Debug_EventScript_ChangeNature_Text_Lonely:
	.string "Lonely$"

J_Debug_EventScript_ChangeNature_Text_Brave:
	.string "Brave$"

J_Debug_EventScript_ChangeNature_Text_Adamant:
	.string "Adamant$"

J_Debug_EventScript_ChangeNature_Text_Naughty:
	.string "Naughty$"

J_Debug_EventScript_ChangeNature_Text_Bold:
	.string "Bold$"

J_Debug_EventScript_ChangeNature_Text_Docile:
	.string "Docile$"

J_Debug_EventScript_ChangeNature_Text_Relaxed:
	.string "Relaxed$"

J_Debug_EventScript_ChangeNature_Text_Impish:
	.string "Impish$"

J_Debug_EventScript_ChangeNature_Text_Lax:
	.string "Lax$"

J_Debug_EventScript_ChangeNature_Text_Timid:
	.string "Timid$"

J_Debug_EventScript_ChangeNature_Text_Hasty:
	.string "Hasty$"

J_Debug_EventScript_ChangeNature_Text_Serious:
	.string "Serious$"

J_Debug_EventScript_ChangeNature_Text_Jolly:
	.string "Jolly$"

J_Debug_EventScript_ChangeNature_Text_Naive:
	.string "Naive$"

J_Debug_EventScript_ChangeNature_Text_Modest:
	.string "Modest$"

J_Debug_EventScript_ChangeNature_Text_Mild:
	.string "Mild$"

J_Debug_EventScript_ChangeNature_Text_Quiet:
	.string "Quiet$"

J_Debug_EventScript_ChangeNature_Text_Bashful:
	.string "Bashful$"

J_Debug_EventScript_ChangeNature_Text_Rash:
	.string "Rash$"

J_Debug_EventScript_ChangeNature_Text_Calm:
	.string "Calm$"

J_Debug_EventScript_ChangeNature_Text_Gentle:
	.string "Gentle$"

J_Debug_EventScript_ChangeNature_Text_Sassy:
	.string "Sassy$"

J_Debug_EventScript_ChangeNature_Text_Careful:
	.string "Careful$"

J_Debug_EventScript_ChangeNature_Text_Quirky:
	.string "Quirky$"

J_Debug_EventScript_EWRAMCounters::
	callnative CheckEWRAMCounters
	msgbox J_Debug_EventScript_EWRAMCounters_Text, MSGBOX_DEFAULT
	release
	end

J_Debug_EventScript_EWRAMCounters_Text::
	.string "Followe{SE_M_SAND_TOMB}Steps{SE_M_HEAT_WAVE}{STR_VAR_1}.\n"
	.string "Fishin{SE_M_SANDSTORM}Chain{SE_M_HEAT_WAVE}{STR_VAR_2}.$"

J_Debug_EventScript_FontTest_Text_1::
	.string "{FONT_SMALL_NARROWER}"
	.string "Ange{SE_M_BATON_PASS}Adep{SE_M_SPIT_UP}Blin{SE_M_WATERFALL}Bodic{SE_M_REVERSAL}Clique\n"
	.string "Coas{SE_M_SPIT_UP}Dunc{SE_M_REVERSAL}Docil{SE_M_REVERSAL}Enac{SE_M_SPIT_UP}Eosin\l"
	.string "Furlon{SE_M_SANDSTORM}Foca{SE_M_BATON_PASS}Gnom{SE_M_REVERSAL}Gondol{SE_M_CHARGE}Human\l"
	.string "Hois{SE_M_SPIT_UP}Inle{SE_M_SPIT_UP}Iodin{SE_M_REVERSAL}Justi{SE_M_ATTRACT}Jocose\l"
	.string "Knol{SE_M_BATON_PASS}Koal{SE_M_CHARGE}Linde{SE_M_ATTRACT}Load{SE_M_GRASSWHISTLE}Milliner\l"
	.string "Moda{SE_M_BATON_PASS}Numbe{SE_M_SAND_TOMB}Nodul{SE_M_REVERSAL}Onse{SE_M_SPIT_UP}Oddball\l"
	.string "Pneum{SE_M_ATTRACT2}Ponch{SE_M_ATTRACT2}Quant{SE_M_CHARGE}Qoph{SE_M_GRASSWHISTLE}Rhone\l"
	.string "Roma{SE_M_ATTRACT}Snou{SE_M_SPIT_UP}Sodiu{SE_M_MILK_DRINK}Tundr{SE_M_CHARGE}Tocsin\l"
	.string "Uncl{SE_M_REVERSAL}Udde{SE_M_SAND_TOMB}Vulca{SE_M_ATTRACT}Voca{SE_M_BATON_PASS}Whale\l"
	.string "Woma{SE_M_ATTRACT}Xma{SE_M_GRASSWHISTLE}Xeno{SE_M_ATTRACT}Yunna{SE_M_ATTRACT}Young\l"
	.string "Zlot{SE_M_YAWN}Zodiac.$"

J_Debug_EventScript_FontTest_Text_2::
	.string "{FONT_SMALL_NARROWER}"
	.string "Ange{SE_M_BATON_PASS}ange{SE_M_BATON_PASS}adep{SE_M_SPIT_UP}fo{SE_M_SAND_TOMB}th{SE_M_REVERSAL}nuanc{SE_M_REVERSAL}loads\n"
	.string "o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}aren{SE_M_CHARGE}coco{SE_M_CHARGE}an{SE_M_WATERFALL}quaalude{SE_M_PERISH_SONG}Blind\l"
	.string "blin{SE_M_WATERFALL}bodic{SE_M_REVERSAL}fo{SE_M_SAND_TOMB}th{SE_M_REVERSAL}submi{SE_M_SPIT_UP}obo{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}the\l"
	.string "clu{SE_M_STRENGTH}sno{SE_M_STRENGTH}an{SE_M_WATERFALL}abbot{SE_M_PERISH_SONG}Cliqu{SE_M_REVERSAL}clique\l"
	.string "coas{SE_M_SPIT_UP}fo{SE_M_SAND_TOMB}th{SE_M_REVERSAL}pouc{SE_M_TRI_ATTACK}loc{SE_M_ATTRACT2}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}franc\l"
	.string "asso{SE_M_HYPER_BEAM}an{SE_M_WATERFALL}accede{SE_M_PERISH_SONG}Dunc{SE_M_REVERSAL}dunc{SE_M_REVERSAL}docile\l"
	.string "fo{SE_M_SAND_TOMB}th{SE_M_REVERSAL}loudnes{SE_M_GRASSWHISTLE}mastodo{SE_M_ATTRACT}o{SE_M_ACID_ARMOR}the\l"
	.string "lou{SE_M_WATERFALL}statehoo{SE_M_WATERFALL}an{SE_M_WATERFALL}huddle.$"

J_Debug_EventScript_FontTest_Text_3::
	.string "{FONT_SMALL_NARROWER}"
	.string "Enac{SE_M_SPIT_UP}enac{SE_M_SPIT_UP}eosi{SE_M_ATTRACT}fo{SE_M_SAND_TOMB}th{SE_M_REVERSAL}quenc{SE_M_TRI_ATTACK}coed\n"
	.string "o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}piqu{SE_M_REVERSAL}cano{SE_M_REVERSAL}an{SE_M_WATERFALL}bleep{SE_M_PERISH_SONG}Furlong\l"
	.string "furlon{SE_M_SANDSTORM}foca{SE_M_BATON_PASS}fo{SE_M_SAND_TOMB}th{SE_M_REVERSAL}genuflect\l"
	.string "profoun{SE_M_WATERFALL}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}moti{SE_M_ACID_ARMOR}aloo{SE_M_ACID_ARMOR}an{SE_M_WATERFALL}offers.\l"
	.string "Gnom{SE_M_REVERSAL}gnom{SE_M_REVERSAL}gondol{SE_M_CHARGE}fo{SE_M_SAND_TOMB}th{SE_M_REVERSAL}impugn\l"
	.string "logo{SE_M_GRASSWHISTLE}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}unplu{SE_M_SANDSTORM}analo{SE_M_SANDSTORM}an{SE_M_WATERFALL}smuggle.\l"
	.string "Huma{SE_M_ATTRACT}huma{SE_M_ATTRACT}hois{SE_M_SPIT_UP}fo{SE_M_SAND_TOMB}th{SE_M_REVERSAL}buddhist\l"
	.string "alcoho{SE_M_BATON_PASS}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}riyad{SE_M_TRI_ATTACK}calip{SE_M_TRI_ATTACK}and\l"
	.string "bathhouse.$"

J_Debug_EventScript_FontTest_Text_4::
	.string "{FONT_SMALL_NARROWER}"
	.string "Inle{SE_M_SPIT_UP}inle{SE_M_SPIT_UP}iodin{SE_M_REVERSAL}fo{SE_M_SAND_TOMB}th{SE_M_REVERSAL}quince\n"
	.string "champio{SE_M_ATTRACT}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}ennu{SE_M_TRI_ATTACK2}scamp{SE_M_TRI_ATTACK2}an{SE_M_WATERFALL}shiite.\l"
	.string "Justi{SE_M_ATTRACT}justi{SE_M_ATTRACT}jocos{SE_M_REVERSAL}fo{SE_M_SAND_TOMB}th{SE_M_REVERSAL}djibouti\l"
	.string "sojour{SE_M_ATTRACT}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}oran{SE_M_ENCORE}ra{SE_M_ENCORE}an{SE_M_WATERFALL}hajjis.\l"
	.string "Knol{SE_M_BATON_PASS}knol{SE_M_BATON_PASS}koal{SE_M_CHARGE}fo{SE_M_SAND_TOMB}th{SE_M_REVERSAL}banknote\l"
	.string "lookou{SE_M_SPIT_UP}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}dybbu{SE_M_ENCORE2}outloo{SE_M_ENCORE2}and\l"
	.string "trekked{SE_M_PERISH_SONG}Linde{SE_M_ATTRACT}linde{SE_M_ATTRACT}load{SE_M_GRASSWHISTLE}fo{SE_M_SAND_TOMB}the\l"
	.string "uln{SE_M_CHARGE}monolo{SE_M_SANDSTORM}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}consu{SE_M_BATON_PASS}mentho{SE_M_BATON_PASS}and\l"
	.string "shallot.$"

J_Debug_EventScript_FontTest_Text_5::
	.string "{FONT_SMALL_NARROWER}"
	.string "Milline{SE_M_SAND_TOMB}milline{SE_M_SAND_TOMB}moda{SE_M_BATON_PASS}fo{SE_M_SAND_TOMB}th{SE_M_REVERSAL}alumna\n"
	.string "solomo{SE_M_ATTRACT}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}albu{SE_M_MILK_DRINK}custo{SE_M_MILK_DRINK}an{SE_M_WATERFALL}summon.\l"
	.string "Numbe{SE_M_SAND_TOMB}numbe{SE_M_SAND_TOMB}nodul{SE_M_REVERSAL}fo{SE_M_SAND_TOMB}th{SE_M_REVERSAL}unmade\l"
	.string "economi{SE_M_HYPER_BEAM}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}shotgu{SE_M_ATTRACT}biso{SE_M_ATTRACT}and\l"
	.string "tunnel{SE_M_PERISH_SONG}Onse{SE_M_SPIT_UP}onse{SE_M_SPIT_UP}oddbal{SE_M_BATON_PASS}fo{SE_M_SAND_TOMB}the\l"
	.string "abando{SE_M_ATTRACT}podiu{SE_M_MILK_DRINK}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}antiqu{SE_M_ATTRACT2}tempo\l"
	.string "an{SE_M_WATERFALL}moonlit{SE_M_PERISH_SONG}Pneum{SE_M_ATTRACT2}pneum{SE_M_ATTRACT2}ponch{SE_M_ATTRACT2}for\l"
	.string "th{SE_M_REVERSAL}dauphi{SE_M_ATTRACT}opossu{SE_M_MILK_DRINK}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}holdup\l"
	.string "bisho{SE_M_MORNING_SUN}an{SE_M_WATERFALL}supplies.$"

J_Debug_EventScript_FontTest_Text_6::
	.string "{FONT_SMALL_NARROWER}"
	.string "Quant{SE_M_CHARGE}quant{SE_M_CHARGE}qoph{SE_M_GRASSWHISTLE}fo{SE_M_SAND_TOMB}th{SE_M_REVERSAL}inquest\n"
	.string "sheqe{SE_M_BATON_PASS}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}cin{SE_M_FLATTER}co{SE_M_FLATTER}an{SE_M_WATERFALL}suqqu{SE_M_PERISH_SONG}Rhone\l"
	.string "rhon{SE_M_REVERSAL}roma{SE_M_ATTRACT}fo{SE_M_SAND_TOMB}th{SE_M_REVERSAL}burn{SE_M_SPIT_UP}porou{SE_M_GRASSWHISTLE}o{SE_M_ACID_ARMOR}the\l"
	.string "lemu{SE_M_SAND_TOMB}clamo{SE_M_SAND_TOMB}an{SE_M_WATERFALL}carrot{SE_M_PERISH_SONG}Snou{SE_M_SPIT_UP}snout\l"
	.string "sodiu{SE_M_MILK_DRINK}fo{SE_M_SAND_TOMB}th{SE_M_REVERSAL}ensnar{SE_M_REVERSAL}boso{SE_M_MILK_DRINK}o{SE_M_ACID_ARMOR}the\l"
	.string "genu{SE_M_GRASSWHISTLE}patho{SE_M_GRASSWHISTLE}an{SE_M_WATERFALL}missing{SE_M_PERISH_SONG}Tundra\l"
	.string "tundr{SE_M_CHARGE}tocsi{SE_M_ATTRACT}fo{SE_M_SAND_TOMB}th{SE_M_REVERSAL}nutme{SE_M_SANDSTORM}isotope\l"
	.string "o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}peasan{SE_M_SPIT_UP}ingo{SE_M_SPIT_UP}an{SE_M_WATERFALL}ottoman.$"

J_Debug_EventScript_FontTest_Text_7::
	.string "{FONT_SMALL_NARROWER}"
	.string "Uncl{SE_M_REVERSAL}uncl{SE_M_REVERSAL}udde{SE_M_SAND_TOMB}fo{SE_M_SAND_TOMB}th{SE_M_REVERSAL}dune{SE_M_GRASSWHISTLE}cloud\n"
	.string "o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}hind{SE_M_DIVE}tho{SE_M_DIVE}an{SE_M_WATERFALL}continuum{SE_M_PERISH_SONG}Vulcan\l"
	.string "vulca{SE_M_ATTRACT}voca{SE_M_BATON_PASS}fo{SE_M_SAND_TOMB}th{SE_M_REVERSAL}alluvia{SE_M_BATON_PASS}ovoi{SE_M_WATERFALL}of\l"
	.string "th{SE_M_REVERSAL}yugosla{SE_M_EARTHQUAKE}chekho{SE_M_EARTHQUAKE}an{SE_M_WATERFALL}revved{SE_M_PERISH_SONG}Whale\l"
	.string "whal{SE_M_REVERSAL}woma{SE_M_ATTRACT}fo{SE_M_SAND_TOMB}th{SE_M_REVERSAL}meanwhil{SE_M_REVERSAL}blowout\l"
	.string "o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}forepa{SE_M_TWISTER}meado{SE_M_TWISTER}an{SE_M_WATERFALL}glowworm.\l"
	.string "Xma{SE_M_GRASSWHISTLE}xma{SE_M_GRASSWHISTLE}xeno{SE_M_ATTRACT}fo{SE_M_SAND_TOMB}th{SE_M_REVERSAL}bauxite\l"
	.string "doxolog{SE_M_YAWN}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}tableau{SE_M_SWEET_SCENT}equino{SE_M_SWEET_SCENT}and\l"
	.string "exxon.$"

J_Debug_EventScript_FontTest_Text_8::
	.string "{FONT_SMALL_NARROWER}"
	.string "Yunna{SE_M_ATTRACT}yunna{SE_M_ATTRACT}youn{SE_M_SANDSTORM}fo{SE_M_SAND_TOMB}th{SE_M_REVERSAL}dynamo\n"
	.string "coyot{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}obloqu{SE_M_YAWN}emplo{SE_M_YAWN}and\l"
	.string "sayyid{SE_M_PERISH_SONG}Zlot{SE_M_YAWN}zlot{SE_M_YAWN}zodia{SE_M_HYPER_BEAM}fo{SE_M_SAND_TOMB}th{SE_M_REVERSAL}gizmo\l"
	.string "ozon{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}fran{SE_M_SKY_UPPERCUT}laisse{SE_M_SKY_UPPERCUT}an{SE_M_WATERFALL}buzzing.$"

J_Debug_EventScript_FontTest_Text_9::
	.string "{FONT_SMALL_NARROWER}"
	.string "4{SE_M_SURF}{SE_M_BELLY_DRUM}13{SE_M_POISON_POWDER}{SE_BERRY_BLENDER}5796.\n"
	.string "M{SE_M_SAND_TOMB}Jock{SE_M_SUPERSONIC}T{SE_M_BARRIER}qui{SE_M_SKY_UPPERCUT}PhD{SE_M_HEAT_WAVE}bag{SE_M_GRASSWHISTLE}20{SE_EXP_MAX}fewer\l"
	.string "lyn{SE_M_SWEET_SCENT}a{SE_M_SPIT_UP}{SE_M_CHARGE}café{SE_CARD}voilà{SE_M_SUPERSONIC}they'r{SE_M_REVERSAL}“worth”\l"
	.string "♂1/♀{SE_M_HEADBUTT}{SE_BERRY_BLENDER}¥1{SE_M_PERISH_SONG}That'{SE_M_GRASSWHISTLE}1{SE_M_BITE}{SE_WARP_OUT}{SE_M_BIND}{SE_M_PAY_DAY}{SE_M_POISON_POWDER}{SE_BERRY_BLENDER}11\l"
	.string "Nintend{SE_M_ATTRACT2}GB{SE_M_BONEMERANG}ca{SE_M_ATTRACT}connec{SE_M_SPIT_UP}t{SE_M_ATTRACT2}{SE_M_CHARGE}Nintendo\l"
	.string "GameCub{SE_M_REVERSAL}console{SE_M_DRAGON_RAGE}H{SE_M_REVERSAL}claimed-thoug{SE_M_TRI_ATTACK}{SE_M_HEAL_BELL}don't\l"
	.string "believ{SE_M_REVERSAL}him-t{SE_M_ATTRACT2}hav{SE_M_REVERSAL}don{SE_M_REVERSAL}s{SE_M_ATTRACT2}i{SE_M_ATTRACT}a{SE_M_ATTRACT}eyes-shut\l"
	.string "state…?$"

J_Debug_PrintFontTest::
	msgbox J_Debug_EventScript_FontTest_Text_1, MSGBOX_DEFAULT
	msgbox J_Debug_EventScript_FontTest_Text_2, MSGBOX_DEFAULT
	msgbox J_Debug_EventScript_FontTest_Text_3, MSGBOX_DEFAULT
	msgbox J_Debug_EventScript_FontTest_Text_4, MSGBOX_DEFAULT
	msgbox J_Debug_EventScript_FontTest_Text_5, MSGBOX_DEFAULT
	msgbox J_Debug_EventScript_FontTest_Text_6, MSGBOX_DEFAULT
	msgbox J_Debug_EventScript_FontTest_Text_7, MSGBOX_DEFAULT
	msgbox J_Debug_EventScript_FontTest_Text_8, MSGBOX_DEFAULT
	msgbox J_Debug_EventScript_FontTest_Text_9, MSGBOX_DEFAULT
	releaseall
	end

J_Debug_EventScript_FontTest::
	lockall
	goto J_Debug_PrintFontTest

J_Debug_EventScript_TellTheTime::
	callnative DebugMenu_CalculateTime
	msgbox J_Debug_EventScript_TellTheTime_Text_0, MSGBOX_DEFAULT
	waitmessage
	closemessage
	end

J_Debug_EventScript_PrintTimeOfDay::
	callnative DebugMenu_CalculateTimeOfDay
	msgbox J_DebugEventScript_PrintWeekday_Text_0, MSGBOX_DEFAULT
	waitmessage
	closemessage
	end

J_Debug_EventScript_FakeRTCNotEnabled::
	msgbox J_Debug_EventScript_FakeRTCNotEnabled_Text_0, MSGBOX_DEFAULT
	waitmessage
	closemessage
	return

J_Debug_EventScript_FakeRTCNotEnabled_Text_0:
	.string "Yo{SE_M_DIVE}currentl{SE_M_YAWN}d{SE_M_ATTRACT2}no{SE_M_SPIT_UP}hav{SE_M_REVERSAL}Fak{SE_M_REVERSAL}RTC\nenabled{SE_M_PERISH_SONG}Pleas{SE_M_REVERSAL}enabl{SE_M_REVERSAL}i{SE_M_SPIT_UP}i{SE_M_ATTRACT}include/\lconfig/overworld.h$"

J_Debug_EventScript_TellTheTime_Text_0:
	.string "Tim{SE_M_REVERSAL}an{SE_M_WATERFALL}date:\n"
	.string "{STR_VAR_1}{SE_M_SUPERSONIC}{STR_VAR_2}:{STR_VAR_3}$"

J_DebugEventScript_PrintWeekday_Text_0:
	.string "Tim{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}day{SE_M_HEAT_WAVE}{STR_VAR_1}$"

