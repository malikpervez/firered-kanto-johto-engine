@ Johto (data/maps/IcePath_B1F_hns/scripts.inc), as built into the FireRed game.

IcePath_B1F_hns_MapScripts::
	map_script 3, IcePath_B1F_OnTransition
	.byte 0

IcePath_B1F_OnTransition:
	callnative SetTimeBasedEncounters
	end

IcePath_B1F_EventScript_PuzzleSkipButton::
	lock
	msgbox IcePath_B1F_Text_PuzzleSkipButton, MSGBOX_YESNO
	goto_if_eq 32781, FALSE, IcePath_B1F_EventScript_PuzzleSkipButtonNo
	warp MAP_ICE_PATH_B1F_HNS, 15, 12
	release
	end

IcePath_B1F_EventScript_PuzzleSkipButtonNo::
	release
	end

IcePath_B1F_Text_PuzzleSkipButton::
	.string "Woul{SE_M_WATERFALL}yo{SE_M_DIVE}lik{SE_M_REVERSAL}t{SE_M_ATTRACT2}ski{SE_M_MORNING_SUN}this\n"
	.string "puzzle?$"

IcePath_B1F_EventScript_Item_Iron::
	finditem ITEM_IRON
	end

IcePath_B1F_EventScript_Item_Revive::
	finditem ITEM_REVIVE
	end

IcePath_B1F_EventScript_Sign::
	msgbox IcePath_B1F_Text_Sign, MSGBOX_SIGN
	end

IcePath_B1F_Text_Sign:
	.string "DANGE{SE_M_MINIMIZE}CRACKE{SE_M_FAINT_ATTACK}ICE\n"
	.string "G{SE_M_SOLAR_BEAM}FAS{SE_M_SWIFT}O{SE_M_PSYBEAM2}BICYCLE\l"
	.string "SWITC{SE_M_SWAGGER2}GEAR{SE_M_SKETCH}BY\l"
	.string "PRESSIN{SE_M_SWAGGER}...\l"
	.string "Th{SE_M_REVERSAL}sig{SE_M_ATTRACT}i{SE_M_GRASSWHISTLE}faded...$"

