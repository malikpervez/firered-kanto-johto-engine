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
	.string "Feature unavailable!\n"
	.string "Please define a usable flag in:\l"
	.string "'include/config/overworld.h'!$"

J_Debug_FlagsNotSetBattleConfigMessage::
	message J_Debug_FlagsNotSetBattleConfigMessage_Text
	goto J_Debug_MessageEnd

J_Debug_FlagsNotSetBattleConfigMessage_Text:
	.string "Feature unavailable!\n"
	.string "Please define a usable flag in:\l"
	.string "'include/config/battle.h'!$"

J_Debug_VarsNotSetBattleConfigMessage::
	message J_Debug_VarsNotSetBattleConfigMessage_Text
	goto J_Debug_MessageEnd

J_Debug_VarsNotSetBattleConfigMessage_Text:
	.string "Feature unavailable!\n"
	.string "Please define a usable var in:\l"
	.string "'include/config/battle.h'!$"

J_Debug_BoxFilledMessage::
	message J_Debug_BoxFilledMessage_Text
	goto J_Debug_MessageEnd

J_Debug_BoxFilledMessage_Text:
	.string "Storage boxes filled!$"

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
	.string "ATK EVs: {STR_VAR_1}, SPATK EVs: {STR_VAR_2}, SPEED EVs: {STR_VAR_3}$"

J_Debug_EventScript_Text_DefensiveEVs:
	.string "HP EVs: {STR_VAR_1}, DEF EVs: {STR_VAR_2}, SPDEF EVs: {STR_VAR_3}$"

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
	.string "ATK IVs: {STR_VAR_1}, SPATK IVs: {STR_VAR_2}, SPEED IVs: {STR_VAR_3}$"

J_Debug_EventScript_Text_DefensiveIVs:
	.string "HP IVs: {STR_VAR_1}, DEF IVs: {STR_VAR_2}, SPDEF IVs: {STR_VAR_3}$"

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
	.string "You haven't seen the last of me!$"

J_Debug_Text_Grunt23Defeat:
	.string "I won't accept this!$"

J_Debug_Text_LanceMultiVictory:
	.string "Lance multi battle complete!$"

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
	.string "Silver multi battle complete!$"

J_Debug_Text_Lance3Defeat:
	.string "You haven't seen the last of me!$"

J_Debug_Text_Clair3Defeat:
	.string "I won't accept this!$"

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
	.string "SaveBlock1 size: {STR_VAR_1}b/{STR_VAR_2}b.\n"
	.string "Free space: {STR_VAR_3}b.$"

J_Debug_SaveBlock2Size::
	.string "SaveBlock2 size: {STR_VAR_1}b/{STR_VAR_2}b.\n"
	.string "Free space: {STR_VAR_3}b.$"

J_Debug_SaveBlock3Size::
	.string "SaveBlock3 size: {STR_VAR_1}b/{STR_VAR_2}b.\n"
	.string "Free space: {STR_VAR_3}b.$"

J_Debug_PokemonStorageSize::
	.string "ウエStorage size: {STR_VAR_1}b/{STR_VAR_2}b.\n"
	.string "Free space: {STR_VAR_3}b.$"

J_Debug_CheckROMSpace::
	callnative CheckROMSize
	msgbox J_Debug_ROMSize, MSGBOX_DEFAULT
	release
	end

J_Debug_ROMSize::
	.string "ROM size: {STR_VAR_1}MB/32MB.\n"
	.string "Free space: {STR_VAR_2}MB.$"

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
	.string "You have no Pokémon nor Eggs.$"

J_DebugScript_HatchAnEgg_Text_NotAnEgg::
	.string "That's not a Pokémon Egg.$"

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
	.string "You have no Pokémon at Daycare.$"

J_DebugText_DaycareOnePokemon:
	.string "You have only one Pokémon at Daycare.$"

J_DebugText_DaycarePokemonNotCompatible:
	.string "Your Pokémon at Daycare can't\nhave babies together!$"

J_Debug_ShowExpansionVersion::
	callnative BufferExpansionVersion
	msgbox J_Debug_ExpansionVersion, MSGBOX_DEFAULT
	release
	end

J_Debug_ExpansionVersion:
	.string "pokeemerald-expansion {STR_VAR_1}$"

J_Debug_Follower_NPC_Not_Enabled::
	msgbox J_Debug_Enable_To_Use_Follower_NPCs, MSGBOX_DEFAULT
	release
	end

J_Debug_Enable_To_Use_Follower_NPCs:
	.string "Feature unavailable.\nSet FNPC-ENABLE-NPC-FOLLOWERS to\lTRUE in 'include/config/follower-npc.h'.$"

J_Debug_Follower_NPC_Event_Script::
	lock
	facefollowernpc
	msgbox J_Debug_Follower_NPC_Test_Message, MSGBOX_DEFAULT
	releaseall
	end

J_Debug_Follower_NPC_Test_Message:
	.string "This is a Follower NPC test.$"

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
	.string "OW-BERRY-PESTS is disabled.\n"
	.string "Unable to force pests onto berry trees.$"

J_Debug_BerryWeedsDisabled::
	msgbox J_DebugText_BerryWeedsDisabled, MSGBOX_DEFAULT
	release
	end

J_DebugText_BerryWeedsDisabled:
	.string "OW-BERRY-WEEDS is disabled.\n"
	.string "Unable to force weeds onto berry trees.$"

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
	.string "Follower Steps: {STR_VAR_1}.\n"
	.string "Fishing Chain: {STR_VAR_2}.$"

J_Debug_EventScript_FontTest_Text_1::
	.string "{FONT_SMALL_NARROWER}"
	.string "Angel Adept Blind Bodice Clique\n"
	.string "Coast Dunce Docile Enact Eosin\l"
	.string "Furlong Focal Gnome Gondola Human\l"
	.string "Hoist Inlet Iodine Justin Jocose\l"
	.string "Knoll Koala Linden Loads Milliner\l"
	.string "Modal Number Nodule Onset Oddball\l"
	.string "Pneumo Poncho Quanta Qophs Rhone\l"
	.string "Roman Snout Sodium Tundra Tocsin\l"
	.string "Uncle Udder Vulcan Vocal Whale\l"
	.string "Woman Xmas Xenon Yunnan Young\l"
	.string "Zloty Zodiac.$"

J_Debug_EventScript_FontTest_Text_2::
	.string "{FONT_SMALL_NARROWER}"
	.string "Angel angel adept for the nuance loads\n"
	.string "of the arena cocoa and quaalude. Blind\l"
	.string "blind bodice for the submit oboe of the\l"
	.string "club snob and abbot. Clique clique\l"
	.string "coast for the pouch loco of the franc\l"
	.string "assoc and accede. Dunce dunce docile\l"
	.string "for the loudness mastodon of the\l"
	.string "loud statehood and huddle.$"

J_Debug_EventScript_FontTest_Text_3::
	.string "{FONT_SMALL_NARROWER}"
	.string "Enact enact eosin for the quench coed\n"
	.string "of the pique canoe and bleep. Furlong\l"
	.string "furlong focal for the genuflect\l"
	.string "profound of the motif aloof and offers.\l"
	.string "Gnome gnome gondola for the impugn\l"
	.string "logos of the unplug analog and smuggle.\l"
	.string "Human human hoist for the buddhist\l"
	.string "alcohol of the riyadh caliph and\l"
	.string "bathhouse.$"

J_Debug_EventScript_FontTest_Text_4::
	.string "{FONT_SMALL_NARROWER}"
	.string "Inlet inlet iodine for the quince\n"
	.string "champion of the ennui scampi and shiite.\l"
	.string "Justin justin jocose for the djibouti\l"
	.string "sojourn of the oranj raj and hajjis.\l"
	.string "Knoll knoll koala for the banknote\l"
	.string "lookout of the dybbuk outlook and\l"
	.string "trekked. Linden linden loads for the\l"
	.string "ulna monolog of the consul menthol and\l"
	.string "shallot.$"

J_Debug_EventScript_FontTest_Text_5::
	.string "{FONT_SMALL_NARROWER}"
	.string "Milliner milliner modal for the alumna\n"
	.string "solomon of the album custom and summon.\l"
	.string "Number number nodule for the unmade\l"
	.string "economic of the shotgun bison and\l"
	.string "tunnel. Onset onset oddball for the\l"
	.string "abandon podium of the antiquo tempo\l"
	.string "and moonlit. Pneumo pneumo poncho for\l"
	.string "the dauphin opossum of the holdup\l"
	.string "bishop and supplies.$"

J_Debug_EventScript_FontTest_Text_6::
	.string "{FONT_SMALL_NARROWER}"
	.string "Quanta quanta qophs for the inquest\n"
	.string "sheqel of the cinq coq and suqqu. Rhone\l"
	.string "rhone roman for the burnt porous of the\l"
	.string "lemur clamor and carrot. Snout snout\l"
	.string "sodium for the ensnare bosom of the\l"
	.string "genus pathos and missing. Tundra\l"
	.string "tundra tocsin for the nutmeg isotope\l"
	.string "of the peasant ingot and ottoman.$"

J_Debug_EventScript_FontTest_Text_7::
	.string "{FONT_SMALL_NARROWER}"
	.string "Uncle uncle udder for the dunes cloud\n"
	.string "of the hindu thou and continuum. Vulcan\l"
	.string "vulcan vocal for the alluvial ovoid of\l"
	.string "the yugoslav chekhov and revved. Whale\l"
	.string "whale woman for the meanwhile blowout\l"
	.string "of the forepaw meadow and glowworm.\l"
	.string "Xmas xmas xenon for the bauxite\l"
	.string "doxology of the tableaux equinox and\l"
	.string "exxon.$"

J_Debug_EventScript_FontTest_Text_8::
	.string "{FONT_SMALL_NARROWER}"
	.string "Yunnan yunnan young for the dynamo\n"
	.string "coyote of the obloquy employ and\l"
	.string "sayyid. Zloty zloty zodiac for the gizmo\l"
	.string "ozone of the franz laissez and buzzing.$"

J_Debug_EventScript_FontTest_Text_9::
	.string "{FONT_SMALL_NARROWER}"
	.string "42 × 138 = 5796.\n"
	.string "Mr Jock, TV quiz PhD: bags 20% fewer\l"
	.string "lynx at a café; voilà, they're “worth”\l"
	.string "♂1/♀1 = ¥1. That's 10 + 9 - 8 = 11\l"
	.string "Nintendo GBA can connect to a Nintendo\l"
	.string "GameCube console! He claimed-though I don't\l"
	.string "believe him-to have done so in an eyes-shut\l"
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
	.string "You currently do not have Fake RTC\nenabled. Please enable it in include/\lconfig/overworld.h$"

J_Debug_EventScript_TellTheTime_Text_0:
	.string "Time and date:\n"
	.string "{STR_VAR_1}, {STR_VAR_2}:{STR_VAR_3}$"

J_DebugEventScript_PrintWeekday_Text_0:
	.string "Time of day: {STR_VAR_1}$"

