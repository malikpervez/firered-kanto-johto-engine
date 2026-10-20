@ Johto (data/maps/LakeOfRage_House1_hns/scripts.inc), as built into the FireRed game.

LakeOfRage_House1_hns_MapScripts::
	.byte 0

LakeOfRage_House1_EventScript_HiddenPowerGuy::
	lock
	faceplayer
	goto_if_set 8711, LakeOfRage_House1_EventScript_HiddenPowerGuyAfter
	msgbox HiddenPowerGuy_Text_Intro, MSGBOX_DEFAULT
	giveitem 591
	msgbox HiddenPowerGuy_Text_Explanation, MSGBOX_DEFAULT
	setflag 8711
	closemessage
	release
	end

LakeOfRage_House1_EventScript_HiddenPowerGuyAfter::
	msgbox HiddenPowerGuy_Text_Meditating, MSGBOX_DEFAULT
	closemessage
	release
	end

HiddenPowerGuy_Text_Intro:
	.string "…Yo{SE_M_DIVE}hav{SE_M_REVERSAL}straye{SE_M_WATERFALL}far…\p"
	.string "Her{SE_M_REVERSAL}{SE_M_HEAL_BELL}hav{SE_M_REVERSAL}meditated{SE_M_PERISH_SONG}Insid{SE_M_REVERSAL}me,\n"
	.string "{SE_M_CHARGE}ne{SE_M_TWISTER}powe{SE_M_SAND_TOMB}ha{SE_M_GRASSWHISTLE}bee{SE_M_ATTRACT}awakened.\p"
	.string "Le{SE_M_SPIT_UP}m{SE_M_REVERSAL}shar{SE_M_REVERSAL}m{SE_M_YAWN}powe{SE_M_SAND_TOMB}wit{SE_M_TRI_ATTACK}your\n"
	.string "POKéMON{SE_M_PERISH_SONG}Tak{SE_M_REVERSAL}this{SE_M_SUPERSONIC}child.$"

HiddenPowerGuy_Text_Explanation:
	.string "D{SE_M_ATTRACT2}yo{SE_M_DIVE}se{SE_M_REVERSAL}it{SE_M_SING}I{SE_M_SPIT_UP}i{SE_M_GRASSWHISTLE}HIDDE{SE_M_PSYBEAM2}POWER!\p"
	.string "I{SE_M_SPIT_UP}draw{SE_M_GRASSWHISTLE}ou{SE_M_SPIT_UP}th{SE_M_REVERSAL}powe{SE_M_SAND_TOMB}o{SE_M_ACID_ARMOR}POKéMON\n"
	.string "fo{SE_M_SAND_TOMB}attacking.\p"
	.string "Remembe{SE_M_SAND_TOMB}this{SE_M_HEAT_WAVE}it{SE_M_GRASSWHISTLE}typ{SE_M_REVERSAL}an{SE_M_WATERFALL}power\n"
	.string "depen{SE_M_WATERFALL}o{SE_M_ATTRACT}th{SE_M_REVERSAL}POKéMO{SE_M_PSYBEAM2}usin{SE_M_SANDSTORM}it.$"

HiddenPowerGuy_Text_Meditating:
	.string "{SE_M_HEAL_BELL}a{SE_M_MILK_DRINK}meditating…$"

