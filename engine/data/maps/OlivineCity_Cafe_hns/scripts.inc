@ Johto (data/maps/OlivineCity_Cafe_hns/scripts.inc), as built into the FireRed game.

OlivineCity_Cafe_hns_MapScripts::
	.byte 0

OlivineCity_Cafe_EventScript_Jasmine::
	lock
	faceplayer
	msgbox OlivineCity_Cafe_Text_Jasmine, MSGBOX_DEFAULT
	closemessage
	fadescreenswapbuffers 1
	setflag 8329
	removeobject 4
	fadescreenswapbuffers 0
	clearflag 8395
	release
	end

OlivineCity_Cafe_Text_Jasmine:
	.string "Oh..{SE_M_PERISH_SONG}Hello{SE_M_SUPERSONIC}{PLAYER}.\p"
	.string "Thes{SE_M_REVERSAL}dishe{SE_M_GRASSWHISTLE}i{SE_M_ATTRACT}fron{SE_M_SPIT_UP}o{SE_M_ACID_ARMOR}m{SE_M_REVERSAL}are\n"
	.string "no{SE_M_SPIT_UP}al{SE_M_BATON_PASS}mine...\p"
	.string "Uh...\p"
	.string "Actually{SE_M_SUPERSONIC}th{SE_M_REVERSAL}perso{SE_M_ATTRACT}wh{SE_M_ATTRACT2}sa{SE_M_SPIT_UP}here\n"
	.string "befor{SE_M_REVERSAL}m{SE_M_REVERSAL}at{SE_M_REVERSAL}{SE_M_CHARGE}lot...\p"
	.string "I{SE_M_ACID_ARMOR}you'{SE_M_WATERFALL}lik{SE_M_REVERSAL}t{SE_M_ATTRACT2}battl{SE_M_REVERSAL}again,\n"
	.string "pleas{SE_M_REVERSAL}visi{SE_M_SPIT_UP}m{SE_M_REVERSAL}a{SE_M_SPIT_UP}th{SE_M_REVERSAL}FIGHTING\l"
	.string "DOJ{SE_M_SOLAR_BEAM}i{SE_M_ATTRACT}SAFFRO{SE_M_PSYBEAM2}CITY.$"

OlivineCity_EventScript_SailorA::
	lock
	faceplayer
	goto_if_set 8696, OlivineCity_EventScript_SailorA2
	msgbox OlivineCity_Text_CafeSailorStrength, MSGBOX_DEFAULT
	giveitem 685
	setflag 8696

OlivineCity_EventScript_SailorA2::
	msgbox OlivineCity_Text_CafeSailorGotStrength, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_EventScript_Cook::
	lock
	faceplayer
	msgbox OlivineCity_Text_CafeFishingGuru, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_EventScript_SailorB::
	lock
	faceplayer
	msgbox OlivineCity_Text_CafeSailor, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_Text_CafeSailorStrength:
	.string "Hah{SE_M_DRAGON_RAGE}You{SE_M_SAND_TOMB}POKéMO{SE_M_PSYBEAM2}sur{SE_M_REVERSAL}loo{SE_M_ENCORE2}like\n"
	.string "lightweights!\p"
	.string "The{SE_M_YAWN}don'{SE_M_SPIT_UP}hav{SE_M_REVERSAL}th{SE_M_REVERSAL}powe{SE_M_SAND_TOMB}to\n"
	.string "mov{SE_M_REVERSAL}boulder{SE_M_GRASSWHISTLE}aside.\p"
	.string "Here{SE_M_SUPERSONIC}us{SE_M_REVERSAL}thi{SE_M_GRASSWHISTLE}an{SE_M_WATERFALL}teac{SE_M_TRI_ATTACK}them\n"
	.string "STRENGTH!$"

OlivineCity_Text_CafeSailorGotStrength:
	.string "O{SE_M_ATTRACT}th{SE_M_REVERSAL}sea{SE_M_SUPERSONIC}th{SE_M_REVERSAL}onl{SE_M_YAWN}thin{SE_M_SANDSTORM}you\n"
	.string "ca{SE_M_ATTRACT}coun{SE_M_SPIT_UP}o{SE_M_ATTRACT}i{SE_M_GRASSWHISTLE}you{SE_M_SAND_TOMB}ow{SE_M_ATTRACT}self!\p"
	.string "I'{SE_M_MILK_DRINK}s{SE_M_ATTRACT2}prou{SE_M_WATERFALL}o{SE_M_ACID_ARMOR}m{SE_M_YAWN}buf{SE_M_ACID_ARMOR}bod!\n"
	.string "Yo{SE_M_DIVE}shoul{SE_M_WATERFALL}trai{SE_M_ATTRACT}lik{SE_M_REVERSAL}me!$"

OlivineCity_Text_CafeFishingGuru:
	.string "OLIVIN{SE_M_SWORDS_DANCE}CAFE'{SE_M_GRASSWHISTLE}men{SE_M_DIVE}i{SE_M_GRASSWHISTLE}packed\n"
	.string "wit{SE_M_TRI_ATTACK}heart{SE_M_YAWN}far{SE_M_REVERSAL}fo{SE_M_SAND_TOMB}beefy\l"
	.string "SAILOR{SE_M_SKETCH}lik{SE_M_REVERSAL}me!$"

OlivineCity_Text_CafeSailor:
	.string "Wheneve{SE_M_SAND_TOMB}{SE_M_HEAL_BELL}rol{SE_M_BATON_PASS}int{SE_M_ATTRACT2}thi{SE_M_GRASSWHISTLE}town,\n"
	.string "{SE_M_HEAL_BELL}alway{SE_M_GRASSWHISTLE}visi{SE_M_SPIT_UP}th{SE_M_REVERSAL}OLIVIN{SE_M_SWORDS_DANCE}CAFE.\p"
	.string "Everythin{SE_M_SANDSTORM}o{SE_M_ATTRACT}th{SE_M_REVERSAL}men{SE_M_DIVE}make{SE_M_GRASSWHISTLE}me\n"
	.string "fee{SE_M_BATON_PASS}stronger{SE_M_PERISH_SONG}{SE_M_HEAL_BELL}can'{SE_M_SPIT_UP}sto{SE_M_MORNING_SUN}eating!$"

