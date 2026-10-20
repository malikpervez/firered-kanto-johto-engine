@ Johto (data/maps/RuinsOfAlph_PuzzleAndRewardChambers_hns/scripts.inc), as built into the FireRed game.

RuinsOfAlph_PuzzleAndRewardChambers_hns_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, RuinsOfAlph_PuzzleAndRewardChambers_OnLoad
	.byte 0

RuinsOfAlph_PuzzleAndRewardChambers_OnLoad::
	call_if_set JOHTO_FLAG_COMPLETED_KABUTO_PUZZLE, RuinsOfAlph_PuzzleAndRewardChambers_MapScript_KabutoHole
	call_if_set JOHTO_FLAG_COMPLETED_OMANYTE_PUZZLE, RuinsOfAlph_PuzzleAndRewardChambers_MapScript_OmanyteHole
	call_if_set JOHTO_FLAG_COMPLETED_AERODACTYL_PUZZLE, RuinsOfAlph_PuzzleAndRewardChambers_MapScript_AerodactylHole
	call_if_set JOHTO_FLAG_COMPLETED_HOOH_PUZZLE, RuinsOfAlph_PuzzleAndRewardChambers_MapScript_HoohHole

	call_if_set JOHTO_FLAG_KABUTO_BROUGHT, RuinsOfAlph_PuzzleAndRewardChambers_MapScript_KabutoDoor
	call_if_set JOHTO_FLAG_OMANYTE_BROUGHT, RuinsOfAlph_PuzzleAndRewardChambers_MapScript_OmanyteDoor
	call_if_set JOHTO_FLAG_AERODACTYL_BROUGHT, RuinsOfAlph_PuzzleAndRewardChambers_MapScript_AerodactylDoor
	call_if_set JOHTO_FLAG_HOOH_BROUGHT, RuinsOfAlph_PuzzleAndRewardChambers_MapScript_HoohDoor
	end

RuinsOfAlph_PuzzleAndRewardChambers_MapScript_KabutoHole::
	setmetatile 20, 5, 0x302, FALSE
	setmetatile 21, 5, 0x303, FALSE
	return

RuinsOfAlph_PuzzleAndRewardChambers_MapScript_OmanyteHole::
	setmetatile 4, 22, 0x302, FALSE
	setmetatile 5, 22, 0x303, FALSE
	return

RuinsOfAlph_PuzzleAndRewardChambers_MapScript_AerodactylHole::
	setmetatile 20, 22, 0x302, FALSE
	setmetatile 21, 22, 0x303, FALSE
	return

RuinsOfAlph_PuzzleAndRewardChambers_MapScript_HoohHole::
	setmetatile 4, 5, 0x302, FALSE
	setmetatile 5, 5, 0x303, FALSE
	return

RuinsOfAlph_PuzzleAndRewardChambers_MapScript_KabutoDoor::
	setmetatile 21, 1, 0x308, FALSE
	return

RuinsOfAlph_PuzzleAndRewardChambers_MapScript_OmanyteDoor::
	setmetatile 5, 18, 0x308, FALSE
	return

RuinsOfAlph_PuzzleAndRewardChambers_MapScript_AerodactylDoor::
	setmetatile 21, 18, 0x308, FALSE
	return

RuinsOfAlph_PuzzleAndRewardChambers_MapScript_HoohDoor::
	setmetatile 5, 1, 0x308, FALSE
	return

RuinsOfAlph_PuzzleAndRewardChambers_MapScript_KabutoDescripton::
	lock
	msgbox RuinsOfAlph_PuzzleAndRewardChambers_Text_Kabuto, MSGBOX_DEFAULT
	release
	end

RuinsOfAlph_PuzzleAndRewardChambers_MapScript_OmanyteDescription::
	lock
	msgbox RuinsOfAlph_PuzzleAndRewardChambers_Text_Omanyte, MSGBOX_DEFAULT
	release
	end

RuinsOfAlph_PuzzleAndRewardChambers_MapScript_AerodactylDescription::
	lock
	msgbox RuinsOfAlph_PuzzleAndRewardChambers_Text_Aerodactyl, MSGBOX_DEFAULT
	release
	end

RuinsOfAlph_PuzzleAndRewardChambers_MapScript_HoohDescription::
	lock
	msgbox RuinsOfAlph_PuzzleAndRewardChambers_Text_Hooh, MSGBOX_DEFAULT
	release
	end

RuinsOfAlph_PuzzleAndRewardChambers_MapScript_StatueDescription::
	lock
	msgbox RuinsOfAlph_PuzzleAndRewardChambers_Text_Statue, MSGBOX_DEFAULT
	release
	end

RuinsOfAlph_PuzzleAndRewardChambers_MapScript_UnownText::
	lock
	msgbox RuinsOfAlph_PuzzleAndRewardChambers_Text_UnownText, MSGBOX_DEFAULT
	release
	end

RuinsOfAlph_PuzzleAndRewardChambers_EventScript_Receptionist::
	lock
	faceplayer
	goto_if_set JOHTO_FLAG_KABUTO_BROUGHT, RuinsOfAlph_PuzzleAndRewardChambers_EventScript_Receptionist3
	goto_if_set JOHTO_FLAG_COMPLETED_KABUTO_PUZZLE, RuinsOfAlph_PuzzleAndRewardChambers_EventScript_Receptionist2
	msgbox RuinsOfAlph_PuzzleAndRewardChambers_Text_Receptionist1, MSGBOX_DEFAULT
	closemessage
	release
	end

RuinsOfAlph_PuzzleAndRewardChambers_EventScript_Receptionist2::
	msgbox RuinsOfAlph_PuzzleAndRewardChambers_Text_Receptionist2, MSGBOX_DEFAULT
	closemessage
	release
	end

RuinsOfAlph_PuzzleAndRewardChambers_EventScript_Receptionist3::
	msgbox RuinsOfAlph_PuzzleAndRewardChambers_Text_Receptionist3, MSGBOX_DEFAULT
	closemessage
	release
	end

RuinsOfAlph_PuzzleAndRewardChambers_EventScript_KabutoPuzzle::
	fadescreen FADE_TO_BLACK
	setvar VAR_0x8004, SLIDING_PUZZLE_KABUTO
	goto_if_set JOHTO_FLAG_COMPLETED_KABUTO_PUZZLE, RuinsOfAlph_PuzzleAndRewardChambers_EventScript_KabutoPuzzleCompleted
	setvar VAR_0x8005, FALSE
	special DoSlidingPuzzle
	waitstate
	goto_if_eq VAR_RESULT, TRUE, RuinsOfAlph_PuzzleAndRewardChambers_MapScript_KabutoSuccess
	end

RuinsOfAlph_PuzzleAndRewardChambers_EventScript_KabutoPuzzleCompleted::
	setvar VAR_0x8005, TRUE
	special DoSlidingPuzzle
	waitstate
	end

RuinsOfAlph_PuzzleAndRewardChambers_MapScript_KabutoSuccess::
	setflag JOHTO_FLAG_COMPLETED_KABUTO_PUZZLE
	setvar VAR_0x8004, 1
	setvar VAR_0x8005, 1
	setvar VAR_0x8006, 20
	setvar VAR_0x8007, 6
	special ShakeCamera
	waitstate
	setmetatile 20, 5, 0x302, FALSE
	setmetatile 21, 5, 0x303, FALSE
	playse SE_CLICK
	special DrawWholeMapView
	delay 30
	clearflag JOHTO_FLAG_ITEM_DOME_FOSSIL
	setvar JOHTO_VAR_RUINSOFALPH_STATE, 1
	applymovement OBJ_EVENT_ID_PLAYER, RuinsOfAlph_PuzzleAndRewardChambers_Movement_Fall
	delay 30
	special SpawnCameraObject
	removeobject OBJ_EVENT_ID_PLAYER
	playse SE_FALL
	delay 60
	warphole MAP_RUINS_OF_ALPH_B1F_HNS
	waitstate
	release
	end

RuinsOfAlph_PuzzleAndRewardChambers_Movement_Fall:
	walk_in_place_fast_up
	walk_in_place_fast_up
	walk_in_place_fast_up
	step_end

RuinsOfAlph_PuzzleAndRewardChambers_EventScript_OmanytePuzzle::
	fadescreen FADE_TO_BLACK
	setvar VAR_0x8004, SLIDING_PUZZLE_OMANYTE
	goto_if_set JOHTO_FLAG_COMPLETED_OMANYTE_PUZZLE, RuinsOfAlph_PuzzleAndRewardChambers_EventScript_OmanytePuzzleCompleted
	setvar VAR_0x8005, FALSE
	special DoSlidingPuzzle
	waitstate
	goto_if_eq VAR_RESULT, TRUE, RuinsOfAlph_PuzzleAndRewardChambers_MapScript_OmanyteSuccess
	end

RuinsOfAlph_PuzzleAndRewardChambers_EventScript_OmanytePuzzleCompleted::
	setvar VAR_0x8005, TRUE
	special DoSlidingPuzzle
	waitstate
	end

RuinsOfAlph_PuzzleAndRewardChambers_MapScript_OmanyteSuccess::
	setflag JOHTO_FLAG_COMPLETED_OMANYTE_PUZZLE
	setvar VAR_0x8004, 1
	setvar VAR_0x8005, 1
	setvar VAR_0x8006, 20
	setvar VAR_0x8007, 6
	special ShakeCamera
	waitstate
	setmetatile 4, 22, 0x302, FALSE
	setmetatile 5, 22, 0x303, FALSE
	playse SE_CLICK
	special DrawWholeMapView
	delay 30
	clearflag JOHTO_FLAG_ITEM_HELIX_FOSSIL
	applymovement OBJ_EVENT_ID_PLAYER, RuinsOfAlph_PuzzleAndRewardChambers_Movement_Fall
	delay 30
	special SpawnCameraObject
	removeobject OBJ_EVENT_ID_PLAYER
	playse SE_FALL
	delay 60
	warphole MAP_RUINS_OF_ALPH_B1F_HNS
	waitstate
	release
	end

RuinsOfAlph_PuzzleAndRewardChambers_EventScript_AerodactylPuzzle::
	fadescreen FADE_TO_BLACK
	setvar VAR_0x8004, SLIDING_PUZZLE_AERODACTYL
	goto_if_set JOHTO_FLAG_COMPLETED_AERODACTYL_PUZZLE, RuinsOfAlph_PuzzleAndRewardChambers_EventScript_AerodactylPuzzleCompleted
	setvar VAR_0x8005, FALSE
	special DoSlidingPuzzle
	waitstate
	goto_if_eq VAR_RESULT, TRUE, RuinsOfAlph_PuzzleAndRewardChambers_MapScript_AerodactylSuccess
	end

RuinsOfAlph_PuzzleAndRewardChambers_EventScript_AerodactylPuzzleCompleted::
	setvar VAR_0x8005, TRUE
	special DoSlidingPuzzle
	waitstate
	end

RuinsOfAlph_PuzzleAndRewardChambers_MapScript_AerodactylSuccess::
	setflag JOHTO_FLAG_COMPLETED_AERODACTYL_PUZZLE
	setvar VAR_0x8004, 1
	setvar VAR_0x8005, 1
	setvar VAR_0x8006, 20
	setvar VAR_0x8007, 6
	special ShakeCamera
	waitstate
	setmetatile 20, 22, 0x302, FALSE
	setmetatile 21, 22, 0x303, FALSE
	playse SE_CLICK
	special DrawWholeMapView
	delay 30
	clearflag JOHTO_FLAG_ITEM_OLD_AMBER
	applymovement OBJ_EVENT_ID_PLAYER, RuinsOfAlph_PuzzleAndRewardChambers_Movement_Fall
	delay 30
	special SpawnCameraObject
	removeobject OBJ_EVENT_ID_PLAYER
	playse SE_FALL
	delay 60
	warphole MAP_RUINS_OF_ALPH_B1F_HNS
	waitstate
	release
	end

RuinsOfAlph_PuzzleAndRewardChambers_EventScript_HooHPuzzle::
	fadescreen FADE_TO_BLACK
	setvar VAR_0x8004, SLIDING_PUZZLE_HO_OH
	goto_if_set JOHTO_FLAG_COMPLETED_HOOH_PUZZLE, RuinsOfAlph_PuzzleAndRewardChambers_EventScript_HoohPuzzleCompleted
	setvar VAR_0x8005, FALSE
	special DoSlidingPuzzle
	waitstate
	goto_if_eq VAR_RESULT, TRUE, RuinsOfAlph_PuzzleAndRewardChambers_MapScript_HoohSuccess
	end

RuinsOfAlph_PuzzleAndRewardChambers_EventScript_HoohPuzzleCompleted::
	setvar VAR_0x8005, TRUE
	special DoSlidingPuzzle
	waitstate
	end

RuinsOfAlph_PuzzleAndRewardChambers_MapScript_HoohSuccess::
	setflag JOHTO_FLAG_COMPLETED_HOOH_PUZZLE
	setvar VAR_0x8004, 1
	setvar VAR_0x8005, 1
	setvar VAR_0x8006, 20
	setvar VAR_0x8007, 6
	special ShakeCamera
	waitstate
	setmetatile 4, 5, 0x302, FALSE
	setmetatile 5, 5, 0x303, FALSE
	playse SE_CLICK
	special DrawWholeMapView
	delay 30
	clearflag JOHTO_FLAG_ITEM_GS_BALL
	applymovement OBJ_EVENT_ID_PLAYER, RuinsOfAlph_PuzzleAndRewardChambers_Movement_Fall
	delay 30
	special SpawnCameraObject
	removeobject OBJ_EVENT_ID_PLAYER
	playse SE_FALL
	delay 60
	warphole MAP_RUINS_OF_ALPH_B1F_HNS
	waitstate
	release
	end

RuinsOfAlph_PuzzleAndRewardChambers_EventScript_CheckHooh::
	lock
	goto_if_set JOHTO_FLAG_HOOH_BROUGHT, RuinsOfAlph_PuzzleAndRewardChambers_EventScript_RewardGotten
	checkspecies SPECIES_HO_OH
	goto_if_eq VAR_RESULT, TRUE, RuinsOfAlph_PuzzleAndRewardChambers_EventScript_RewardHooh
	msgbox RuinsOfAlph_PuzzleAndRewardChambers_Text_Mon, MSGBOX_SIGN
	closemessage
	release
	end

RuinsOfAlph_PuzzleAndRewardChambers_EventScript_RewardHooh::
	setvar VAR_0x8004, 1
	setvar VAR_0x8005, 1
	setvar VAR_0x8006, 20
	setvar VAR_0x8007, 6
	special ShakeCamera
	waitstate
	msgbox RuinsOfAlph_PuzzleAndRewardChambers_Text_Reward, MSGBOX_DEFAULT
	closemessage
	playse SE_CLICK
	setmetatile 5, 1, 0x308, FALSE
	special DrawWholeMapView
	setflag JOHTO_FLAG_HOOH_BROUGHT
	release
	end

RuinsOfAlph_PuzzleAndRewardChambers_EventScript_CheckAerodactyl::
	lock
	goto_if_set JOHTO_FLAG_AERODACTYL_BROUGHT, RuinsOfAlph_PuzzleAndRewardChambers_EventScript_RewardGotten
	checkspecies SPECIES_AERODACTYL
	goto_if_eq VAR_RESULT, TRUE, RuinsOfAlph_PuzzleAndRewardChambers_EventScript_RewardAerodactyl
	msgbox RuinsOfAlph_PuzzleAndRewardChambers_Text_Mon, MSGBOX_SIGN
	closemessage
	release
	end

RuinsOfAlph_PuzzleAndRewardChambers_EventScript_RewardAerodactyl::
	setvar VAR_0x8004, 1
	setvar VAR_0x8005, 1
	setvar VAR_0x8006, 20
	setvar VAR_0x8007, 6
	special ShakeCamera
	waitstate
	msgbox RuinsOfAlph_PuzzleAndRewardChambers_Text_Reward, MSGBOX_DEFAULT
	closemessage
	playse SE_CLICK
	setmetatile 21, 18, 0x308, FALSE
	special DrawWholeMapView
	setflag JOHTO_FLAG_AERODACTYL_BROUGHT
	release
	end

RuinsOfAlph_PuzzleAndRewardChambers_EventScript_CheckKabuto::
	lock
	goto_if_set JOHTO_FLAG_KABUTO_BROUGHT, RuinsOfAlph_PuzzleAndRewardChambers_EventScript_RewardGotten
	checkspecies SPECIES_KABUTO
	goto_if_eq VAR_RESULT, TRUE, RuinsOfAlph_PuzzleAndRewardChambers_EventScript_RewardKabuto
	msgbox RuinsOfAlph_PuzzleAndRewardChambers_Text_Mon, MSGBOX_SIGN
	closemessage
	release
	end

RuinsOfAlph_PuzzleAndRewardChambers_EventScript_RewardKabuto::
	setvar VAR_0x8004, 1
	setvar VAR_0x8005, 1
	setvar VAR_0x8006, 20
	setvar VAR_0x8007, 6
	special ShakeCamera
	waitstate
	msgbox RuinsOfAlph_PuzzleAndRewardChambers_Text_Reward, MSGBOX_DEFAULT
	closemessage
	playse SE_CLICK
	setmetatile 21, 1, 0x308, FALSE
	special DrawWholeMapView
	setflag JOHTO_FLAG_KABUTO_BROUGHT
	release
	end

RuinsOfAlph_PuzzleAndRewardChambers_EventScript_CheckOmanyte::
	lock
	goto_if_set JOHTO_FLAG_OMANYTE_BROUGHT, RuinsOfAlph_PuzzleAndRewardChambers_EventScript_RewardGotten
	checkspecies SPECIES_OMANYTE
	goto_if_eq VAR_RESULT, TRUE, RuinsOfAlph_PuzzleAndRewardChambers_EventScript_RewardOmanyte
	msgbox RuinsOfAlph_PuzzleAndRewardChambers_Text_Mon, MSGBOX_SIGN
	closemessage
	release
	end

RuinsOfAlph_PuzzleAndRewardChambers_EventScript_RewardOmanyte::
	setvar VAR_0x8004, 1
	setvar VAR_0x8005, 1
	setvar VAR_0x8006, 20
	setvar VAR_0x8007, 6
	special ShakeCamera
	waitstate
	msgbox RuinsOfAlph_PuzzleAndRewardChambers_Text_Reward, MSGBOX_DEFAULT
	closemessage
	playse SE_CLICK
	setmetatile 5, 18, 0x308, FALSE
	special DrawWholeMapView
	setflag JOHTO_FLAG_OMANYTE_BROUGHT
	release
	end

RuinsOfAlph_PuzzleAndRewardChambers_EventScript_RewardGotten::
	msgbox RuinsOfAlph_PuzzleAndRewardChambers_Text_Solved, MSGBOX_DEFAULT
	closemessage
	release
	end

RuinsOfAlph_PuzzleAndRewardChambers_Text_Reward:
	.string "Th{SE_M_REVERSAL}chambe{SE_M_SAND_TOMB}reacts!\n"
	.string "Th{SE_M_REVERSAL}wa{SE_M_YAWN}i{SE_M_GRASSWHISTLE}open.$"

RuinsOfAlph_PuzzleAndRewardChambers_Text_Mon:
	.string "Som{SE_M_REVERSAL}kin{SE_M_WATERFALL}o{SE_M_ACID_ARMOR}ancien{SE_M_SPIT_UP}sensor.\n"
	.string "Wha{SE_M_SPIT_UP}i{SE_M_GRASSWHISTLE}i{SE_M_SPIT_UP}lookin{SE_M_SANDSTORM}for?$"

RuinsOfAlph_PuzzleAndRewardChambers_Text_Solved:
	.string "Th{SE_M_REVERSAL}wa{SE_M_YAWN}i{SE_M_GRASSWHISTLE}open.$"

RuinsOfAlph_PuzzleAndRewardChambers_Text_Receptionist1:
	.string "Welcom{SE_M_REVERSAL}t{SE_M_ATTRACT2}thi{SE_M_GRASSWHISTLE}chamber.\p"
	.string "Ther{SE_M_REVERSAL}ar{SE_M_REVERSAL}slidin{SE_M_SANDSTORM}panel{SE_M_GRASSWHISTLE}tha{SE_M_SPIT_UP}depict\n"
	.string "{SE_M_CHARGE}POKéMO{SE_M_PSYBEAM2}draw{SE_M_ATTRACT}b{SE_M_YAWN}th{SE_M_REVERSAL}ancients.\p"
	.string "Slid{SE_M_REVERSAL}th{SE_M_REVERSAL}panel{SE_M_GRASSWHISTLE}aroun{SE_M_WATERFALL}t{SE_M_ATTRACT2}form\n"
	.string "th{SE_M_REVERSAL}picture.\p"
	.string "T{SE_M_ATTRACT2}th{SE_M_REVERSAL}lef{SE_M_SPIT_UP}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}descriptio{SE_M_ATTRACT}of\n"
	.string "th{SE_M_REVERSAL}POKéMON.\p"
	.string "Scientist{SE_M_GRASSWHISTLE}i{SE_M_ATTRACT}th{SE_M_REVERSAL}la{SE_M_STRENGTH}ar{SE_M_REVERSAL}examin-\n"
	.string "-in{SE_M_SANDSTORM}som{SE_M_REVERSAL}newl{SE_M_YAWN}foun{SE_M_WATERFALL}patterns.$"

RuinsOfAlph_PuzzleAndRewardChambers_Text_Receptionist2:
	.string "{SE_M_BONEMERANG}hol{SE_M_REVERSAL}jus{SE_M_SPIT_UP}opene{SE_M_WATERFALL}u{SE_M_MORNING_SUN}i{SE_M_ATTRACT}th{SE_M_REVERSAL}floor!\n"
	.string "I'{SE_M_WATERFALL}bette{SE_M_SAND_TOMB}tel{SE_M_BATON_PASS}th{SE_M_REVERSAL}others.$"

RuinsOfAlph_PuzzleAndRewardChambers_Text_Receptionist3:
	.string "No{SE_M_TWISTER}{SE_M_CHARGE}hol{SE_M_REVERSAL}i{SE_M_ATTRACT}th{SE_M_REVERSAL}wal{SE_M_BATON_PASS}too?!\n"
	.string "Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}gettin{SE_M_SANDSTORM}spooky.$"

RuinsOfAlph_PuzzleAndRewardChambers_Text_Kabuto:
	.string "{SE_M_BONEMERANG}POKéMO{SE_M_PSYBEAM2}tha{SE_M_SPIT_UP}hi{SE_M_WATERFALL}o{SE_M_ATTRACT}th{SE_M_REVERSAL}se{SE_M_CHARGE}floor.\n"
	.string "Eye{SE_M_GRASSWHISTLE}o{SE_M_ATTRACT}it{SE_M_GRASSWHISTLE}bac{SE_M_ENCORE2}scanne{SE_M_WATERFALL}th{SE_M_REVERSAL}area.$"

RuinsOfAlph_PuzzleAndRewardChambers_Text_UnownText:
	.string "It'{SE_M_GRASSWHISTLE}UNOW{SE_M_PSYBEAM2}text!$"

RuinsOfAlph_PuzzleAndRewardChambers_Text_Statue:
	.string "It'{SE_M_GRASSWHISTLE}{SE_M_CHARGE}replic{SE_M_CHARGE}o{SE_M_ACID_ARMOR}a{SE_M_ATTRACT}ancient\n"
	.string "POKéMON.$"

RuinsOfAlph_PuzzleAndRewardChambers_Text_Aerodactyl:
	.string "Thi{SE_M_GRASSWHISTLE}flyin{SE_M_SANDSTORM}POKéMO{SE_M_PSYBEAM2}attacke{SE_M_WATERFALL}its\n"
	.string "pre{SE_M_YAWN}wit{SE_M_TRI_ATTACK}saw-lik{SE_M_REVERSAL}fangs.$"

RuinsOfAlph_PuzzleAndRewardChambers_Text_Omanyte:
	.string "Thi{SE_M_GRASSWHISTLE}POKéMO{SE_M_PSYBEAM2}drifte{SE_M_WATERFALL}i{SE_M_ATTRACT}th{SE_M_REVERSAL}sea\n"
	.string "b{SE_M_YAWN}twistin{SE_M_SANDSTORM}it{SE_M_GRASSWHISTLE}te{SE_M_ATTRACT}tentacles.$"

RuinsOfAlph_PuzzleAndRewardChambers_Text_Hooh:
	.string "{SE_M_BONEMERANG}POKéMO{SE_M_PSYBEAM2}tha{SE_M_SPIT_UP}fle{SE_M_TWISTER}gracefull{SE_M_YAWN}on\n"
	.string "rainbow-colore{SE_M_WATERFALL}wings.$"

RuinsOfAlph_EventScript_Item_LifeOrb::
	finditem ITEM_LIFE_ORB
	end

RuinsOfAlph_EventScript_Item_Charcoal::
	finditem ITEM_CHARCOAL
	end

RuinsOfAlph_EventScript_Item_MaxRevive1::
	finditem ITEM_MAX_REVIVE
	end

RuinsOfAlph_EventScript_Item_SacredAsh::
	finditem ITEM_SACRED_ASH
	end

RuinsOfAlph_EventScript_Item_HealPowder1::
	finditem ITEM_HEAL_POWDER
	end

RuinsOfAlph_EventScript_Item_EnergyRoot::
	finditem ITEM_ENERGY_ROOT
	end

RuinsOfAlph_EventScript_Item_SitrusBerry2::
	finditem ITEM_SITRUS_BERRY
	end

RuinsOfAlph_EventScript_Item_MoonStone::
	finditem ITEM_MOON_STONE
	end

RuinsOfAlph_EventScript_Item_HealPowder2::
	finditem ITEM_HEAL_POWDER
	end

RuinsOfAlph_EventScript_Item_EnergyPowder::
	finditem ITEM_ENERGY_POWDER
	end

RuinsOfAlph_EventScript_Item_OranBerry::
	finditem ITEM_ORAN_BERRY
	end

RuinsOfAlph_EventScript_Item_PechaBerry::
	finditem ITEM_PECHA_BERRY
	end

RuinsOfAlph_EventScript_Item_Stardust::
	finditem ITEM_STARDUST
	end

RuinsOfAlph_EventScript_Item_StarPiece::
	finditem ITEM_STAR_PIECE
	end

RuinsOfAlph_EventScript_Item_LumBerry2::
	finditem ITEM_LUM_BERRY
	end

RuinsOfAlph_EventScript_Item_WaterStone::
	finditem ITEM_WATER_STONE
	end

