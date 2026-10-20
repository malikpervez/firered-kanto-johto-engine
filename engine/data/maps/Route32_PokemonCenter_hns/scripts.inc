@ Johto (data/maps/Route32_PokemonCenter_hns/scripts.inc), as built into the FireRed game.

Route32_PokemonCenter_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route32_PokemonCenter_OnTransition
	.byte 0

Route32_PokemonCenter_OnTransition::
	setrespawn JOHTO_HEAL_LOCATION_ROUTE_32_HNS
	end

Route32_PokemonCenter_EventScript_Lass::
	lock
	faceplayer
	msgbox Route32_Pokecenter_Text_CooltrainerF, MSGBOX_DEFAULT
	closemessage
	release
	end

Route32_PokemonCenter_EventScript_FishingGuru::
	lock
	faceplayer
	checkitem ITEM_OLD_ROD
	goto_if_eq VAR_RESULT, TRUE, Route32_PokemonCenter_EventScript_FishingGuru3
	msgbox Route32_Pokecenter_Text_FishingGuruQuestion, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, Route32_PokemonCenter_EventScript_FishingGuru2
	msgbox Route32_Pokecenter_Text_FishingGuruNo, MSGBOX_DEFAULT
	closemessage
	release
	end

Route32_PokemonCenter_EventScript_FishingGuru2::
	msgbox Route32_Pokecenter_Text_FishingGuruYes, MSGBOX_DEFAULT
	giveitem ITEM_OLD_ROD
	goto_if_eq VAR_RESULT, FALSE, J_Common_EventScript_ShowBagIsFull
	msgbox Route32_Pokecenter_Text_FishingGuruGiveRod, MSGBOX_DEFAULT
	closemessage
	release
	end

Route32_PokemonCenter_EventScript_FishingGuru3::
	msgbox Route32_Pokecenter_Text_FishingGuruAfter, MSGBOX_DEFAULT
	release
	end

Route32_Pokecenter_Text_FishingGuruQuestion:
	.string "Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}grea{SE_M_SPIT_UP}fishin{SE_M_SANDSTORM}spot.\p"
	.string "Yo{SE_M_DIVE}sa{SE_M_TWISTER}peopl{SE_M_REVERSAL}fishing?\n"
	.string "Ho{SE_M_TWISTER}abou{SE_M_SPIT_UP}you?\p"
	.string "Woul{SE_M_WATERFALL}yo{SE_M_DIVE}lik{SE_M_REVERSAL}on{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}m{SE_M_YAWN}RODS?$"

Route32_Pokecenter_Text_FishingGuruYes:
	.string "Heh{SE_M_SUPERSONIC}that'{SE_M_GRASSWHISTLE}goo{SE_M_WATERFALL}t{SE_M_ATTRACT2}hear.\p"
	.string "No{SE_M_TWISTER}you'r{SE_M_REVERSAL}a{SE_M_ATTRACT}angle{SE_M_SAND_TOMB}too!$"

Route32_Pokecenter_Text_FishingGuruGiveRod:
	.string "Fishin{SE_M_SANDSTORM}i{SE_M_GRASSWHISTLE}great!\p"
	.string "I{SE_M_ACID_ARMOR}there'{SE_M_GRASSWHISTLE}water{SE_M_SUPERSONIC}b{SE_M_REVERSAL}i{SE_M_SPIT_UP}th{SE_M_REVERSAL}se{SE_M_CHARGE}or\n"
	.string "{SE_M_CHARGE}stream{SE_M_SUPERSONIC}tr{SE_M_YAWN}ou{SE_M_SPIT_UP}you{SE_M_SAND_TOMB}ROD.$"

Route32_Pokecenter_Text_FishingGuruNo:
	.string "Oh{SE_M_PERISH_SONG}That'{SE_M_GRASSWHISTLE}rathe{SE_M_SAND_TOMB}disappointing…$"

Route32_Pokecenter_Text_FishingGuruAfter:
	.string "Yo{SE_M_SUPERSONIC}kid{SE_M_PERISH_SONG}Ho{SE_M_TWISTER}ar{SE_M_REVERSAL}the{SE_M_YAWN}biting?$"

Route32_Pokecenter_Text_CooltrainerF:
	.string "Wha{SE_M_SPIT_UP}shoul{SE_M_WATERFALL}{SE_M_HEAL_BELL}mak{SE_M_REVERSAL}m{SE_M_YAWN}POKéMO{SE_M_PSYBEAM2}hold?\p"
	.string "Mayb{SE_M_REVERSAL}a{SE_M_ATTRACT}ite{SE_M_MILK_DRINK}tha{SE_M_SPIT_UP}increases\n"
	.string "ATTAC{SE_M_SNORE}power…$"

