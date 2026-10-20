@ Johto (data/maps/DarkCave_NorthSide_hns/scripts.inc), as built into the FireRed game.

DarkCave_NorthSide_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, DarkCave_NorthSide_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, J_SetTimeEncounters
	.byte 0

DarkCave_NorthSide_OnTransition:
	callnative SetTimeBasedEncounters
	end

DarkCave2_EventScript_Item_BlackFlute::
	finditem ITEM_BLACK_FLUTE
	end

DarkCave2_EventScript_Item_StarPiece::
	finditem ITEM_STAR_PIECE
	end

DarkCave2_EventScript_BlackGlasses::
	lock
	faceplayer
	goto_if_set JOHTO_FLAG_GOT_BLACK_GLASSES, DarkCave2_EventScript_BlackGlassesGot
	msgbox DarkCave2_Text_Nerd, MSGBOX_DEFAULT
	giveitem ITEM_BLACK_GLASSES
	setflag JOHTO_FLAG_GOT_BLACK_GLASSES
	closemessage
	release
	end

DarkCave2_EventScript_BlackGlassesGot::
	msgbox DarkCave2_Text_Nerd2, MSGBOX_DEFAULT
	closemessage
	release
	end

DarkCave2_Text_Nerd:
	.string "Whoa{SE_M_DRAGON_RAGE}Yo{SE_M_DIVE}startle{SE_M_WATERFALL}m{SE_M_REVERSAL}there!\p"
	.string "{SE_M_HEAL_BELL}ha{SE_M_WATERFALL}m{SE_M_YAWN}BLACK-GLASSE{SE_M_SKETCH}on{SE_M_SUPERSONIC}s{SE_M_ATTRACT2}I\n"
	.string "didn'{SE_M_SPIT_UP}notic{SE_M_REVERSAL}yo{SE_M_DIVE}a{SE_M_SPIT_UP}all.\p"
	.string "Wha{SE_M_SPIT_UP}a{SE_M_MILK_DRINK}{SE_M_HEAL_BELL}doin{SE_M_SANDSTORM}here?\p"
	.string "Hey{SE_M_SUPERSONIC}don'{SE_M_SPIT_UP}yo{SE_M_DIVE}worr{SE_M_YAWN}abou{SE_M_SPIT_UP}it.\p"
	.string "I'l{SE_M_BATON_PASS}giv{SE_M_REVERSAL}yo{SE_M_DIVE}{SE_M_CHARGE}pai{SE_M_SAND_TOMB}o{SE_M_ACID_ARMOR}BLACK-\n"
	.string "GLASSES{SE_M_SUPERSONIC}s{SE_M_ATTRACT2}forge{SE_M_SPIT_UP}yo{SE_M_DIVE}sa{SE_M_TWISTER}me,\n"
	.string "OK?$"

DarkCave2_Text_Nerd2:
	.string "BLACK-GLASSE{SE_M_SKETCH}up{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}powe{SE_M_SAND_TOMB}of\n"
	.string "DARK-typ{SE_M_REVERSAL}moves.$"

