@ Johto (data/maps/NewSinjoh_House4_hns/scripts.inc), as built into the FireRed game.

NewSinjoh_House4_hns_MapScripts::
	.byte 0

NewSinjoh_Cafe_Script_Sister::
	lock
	faceplayer
	message NewSinjoh_Cafe_Text_ResturantGreeting
	waitmessage
	pokemart NewSinjoh_Cafe_Pokemart_Resturant
	msgbox NewSinjoh_Cafe_Text_ResturantEnd, MSGBOX_DEFAULT
	release
	end

	.align 2

NewSinjoh_Cafe_Pokemart_Resturant:
	.2byte ITEM_YACHE_BERRY
	.2byte ITEM_LANSAT_BERRY
	.2byte ITEM_ROWAP_BERRY
	.2byte ITEM_BERRY_JUICE
	.2byte ITEM_SODA_POP
	.2byte ITEM_LAVA_COOKIE
	.2byte ITEM_HEAL_POWDER
	.2byte ITEM_LEEK
	.2byte ITEM_BIG_ROOT
	.2byte ITEM_NONE
	release
	end

NewSinjoh_Cafe_Text_ResturantGreeting:
	.string "H-hello{SE_M_DRAGON_RAGE}Welcom{SE_M_REVERSAL}t{SE_M_ATTRACT2}ou{SE_M_SAND_TOMB}Cafe!\n"
	.string "Ho{SE_M_TWISTER}ca{SE_M_ATTRACT}{SE_M_HEAL_BELL}hel{SE_M_MORNING_SUN}yo{SE_M_DIVE}today?$"

NewSinjoh_Cafe_Text_ResturantEnd:
	.string "Pleas{SE_M_REVERSAL}com{SE_M_REVERSAL}again!$"

NewSinjoh_Cafe_EventScript_BaldingMan::
	msgbox NewSinjoh_Cafe_Text_BaldingMan, MSGBOX_NPC
	end

NewSinjoh_Cafe_Text_BaldingMan:
	.string "{SE_M_BONEMERANG}loca{SE_M_BATON_PASS}famil{SE_M_YAWN}ha{SE_M_GRASSWHISTLE}ru{SE_M_ATTRACT}this\n"
	.string "caf{SE_M_REVERSAL}fo{SE_M_SAND_TOMB}a{SE_M_GRASSWHISTLE}lon{SE_M_SANDSTORM}a{SE_M_GRASSWHISTLE}anyone\l"
	.string "ca{SE_M_ATTRACT}remember.\p"
	.string "Thei{SE_M_SAND_TOMB}younges{SE_M_SPIT_UP}gir{SE_M_BATON_PASS}ove{SE_M_SAND_TOMB}there\n"
	.string "isn'{SE_M_SPIT_UP}use{SE_M_WATERFALL}t{SE_M_ATTRACT2}servin{SE_M_SANDSTORM}s{SE_M_ATTRACT2}many\l"
	.string "strangers.$"

NewSinjoh_Cafe_EventScript_ScientistF::
	msgbox NewSinjoh_Cafe_Text_ScientistF, MSGBOX_NPC
	end

NewSinjoh_Cafe_Text_ScientistF:
	.string "Thi{SE_M_GRASSWHISTLE}drin{SE_M_ENCORE2}i{SE_M_GRASSWHISTLE}s{SE_M_ATTRACT2}goo--ood!\n"
	.string ".......\p"
	.string ".......\p"
	.string "Hahaha\p"
	.string ".......$"

NewSinjoh_Cafe_EventScript_ScientistM::
	lock
	faceplayer
	msgbox NewSinjoh_Cafe_Text_ScientistM, MSGBOX_DEFAULT
	closemessage
	release
	end

NewSinjoh_Cafe_Text_ScientistM:
	.string "Pleas{SE_M_REVERSAL}forgiv{SE_M_REVERSAL}m{SE_M_YAWN}colleague...\p"
	.string "Th{SE_M_REVERSAL}drink{SE_M_GRASSWHISTLE}her{SE_M_REVERSAL}ar{SE_M_REVERSAL}stronge{SE_M_SAND_TOMB}than\n"
	.string "wha{SE_M_SPIT_UP}we'r{SE_M_REVERSAL}use{SE_M_WATERFALL}t{SE_M_ATTRACT2}i{SE_M_ATTRACT}HOENN.\p"
	.string "{SE_M_HEAL_BELL}trie{SE_M_WATERFALL}t{SE_M_ATTRACT2}war{SE_M_ATTRACT}her{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}sh{SE_M_REVERSAL}said\n"
	.string "sh{SE_M_REVERSAL}neede{SE_M_WATERFALL}t{SE_M_ATTRACT2}unwind.\p"
	.string "Thi{SE_M_GRASSWHISTLE}researc{SE_M_TRI_ATTACK}expeditio{SE_M_ATTRACT}ha{SE_M_GRASSWHISTLE}been\n"
	.string "har{SE_M_WATERFALL}o{SE_M_ATTRACT}u{SE_M_GRASSWHISTLE}all.$"

NewSinjoh_Cafe_EventScript_Gentleman::
	msgbox NewSinjoh_Cafe_Text_Gentleman, MSGBOX_NPC
	end

NewSinjoh_Cafe_Text_Gentleman:
	.string "Wha{SE_M_SPIT_UP}ar{SE_M_REVERSAL}yo{SE_M_DIVE}starin{SE_M_SANDSTORM}at{SE_M_SUPERSONIC}kid?\p"
	.string "Nothin{SE_M_ABSORB}wron{SE_M_SANDSTORM}wit{SE_M_TRI_ATTACK}{SE_M_CHARGE}ma{SE_M_ATTRACT}an{SE_M_WATERFALL}his\n"
	.string "POKéMO{SE_M_PSYBEAM2}eatin{SE_M_SANDSTORM}a{SE_M_SPIT_UP}th{SE_M_REVERSAL}sam{SE_M_REVERSAL}table.$"

NewSinjoh_EventScript_Scyther::
	lock
	faceplayer
	playmoncry 123, 0
	msgbox NewSinjoh_Text_Scyther, MSGBOX_DEFAULT
	waitmoncry
	closemessage
	release
	end

NewSinjoh_Text_Scyther:
	.string "Scyyy!$"

