@ Johto (data/maps/CianwoodHouse2_hns/scripts.inc), as built into the FireRed game.

CianwoodHouse2_hns_MapScripts::
	.byte 0

CianwoodHouse2_EventScript_Teacher::
	lock
	faceplayer
	msgbox CianwoodCity_Text_LugiaHouseTeacher, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodHouse2_EventScript_Lass::
	lock
	faceplayer
	msgbox CianwoodCity_Text_LugiaHouseLass, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodHouse2_EventScript_Twin::
	lock
	faceplayer
	msgbox CianwoodCity_Text_LugiaHouseTwin, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodCity_Text_LugiaHouseTeacher:
	.string "Yo{SE_M_DIVE}cam{SE_M_REVERSAL}fro{SE_M_MILK_DRINK}OLIVINE?\p"
	.string "D{SE_M_ATTRACT2}yo{SE_M_DIVE}remembe{SE_M_SAND_TOMB}th{SE_M_REVERSAL}fou{SE_M_SAND_TOMB}islands\n"
	.string "alon{SE_M_SANDSTORM}th{SE_M_REVERSAL}way?\p"
	.string "{SE_M_HEAL_BELL}hear{SE_M_WATERFALL}tha{SE_M_SPIT_UP}{SE_M_CHARGE}mythica{SE_M_BATON_PASS}se{SE_M_CHARGE}crea-\n"
	.string "tur{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}hidin{SE_M_SANDSTORM}i{SE_M_ATTRACT}them.$"

CianwoodCity_Text_LugiaHouseLass:
	.string "{SE_M_HEAL_BELL}hear{SE_M_WATERFALL}tha{SE_M_SPIT_UP}yo{SE_M_DIVE}ca{SE_M_ATTRACT}onl{SE_M_YAWN}se{SE_M_REVERSAL}it\n"
	.string "i{SE_M_ACID_ARMOR}yo{SE_M_DIVE}hav{SE_M_REVERSAL}{SE_M_CHARGE}SILVE{SE_M_MINIMIZE}WING.\p"
	.string "I{SE_M_SPIT_UP}mus{SE_M_SPIT_UP}hav{SE_M_REVERSAL}th{SE_M_REVERSAL}sam{SE_M_REVERSAL}scen{SE_M_SPIT_UP}as\n"
	.string "th{SE_M_REVERSAL}creature.$"

CianwoodCity_Text_LugiaHouseTwin:
	.string "I'v{SE_M_REVERSAL}hear{SE_M_WATERFALL}tha{SE_M_SPIT_UP}th{SE_M_REVERSAL}whirlpools\n"
	.string "aroun{SE_M_WATERFALL}th{SE_M_REVERSAL}island{SE_M_GRASSWHISTLE}ar{SE_M_REVERSAL}cause{SE_M_WATERFALL}by\l"
	.string "th{SE_M_REVERSAL}se{SE_M_CHARGE}creature.\p"
	.string "Yo{SE_M_DIVE}migh{SE_M_SPIT_UP}nee{SE_M_WATERFALL}{SE_M_CHARGE}specia{SE_M_BATON_PASS}move\n"
	.string "t{SE_M_ATTRACT2}ge{SE_M_SPIT_UP}pas{SE_M_SPIT_UP}them.$"

