@ Johto (data/maps/Route28_House_hns/scripts.inc), as built into the FireRed game.

Route28_House_hns_MapScripts::
	.byte 0

Route28House_EventScript_Celebrity::
	lock
	faceplayer
	goto_if_set JOHTO_FLAG_GOT_TM_STEEL_WING, Route28House_EventScript_CelebrityAfter
	msgbox Route28House_Text_Celebrity1, MSGBOX_NPC
	giveitem ITEM_TM_STEEL_WING
	setflag JOHTO_FLAG_GOT_TM_STEEL_WING

Route28House_EventScript_CelebrityAfter::
	msgbox Route28House_Text_Celebrity2, MSGBOX_NPC
	release
	end

Route28House_Text_Celebrity1:
	.string "Oh{SE_M_SUPERSONIC}dear{SE_M_PERISH_SONG}You'v{SE_M_REVERSAL}foun{SE_M_WATERFALL}me.\p"
	.string "Pleas{SE_M_REVERSAL}don'{SE_M_SPIT_UP}tel{SE_M_BATON_PASS}anyon{SE_M_REVERSAL}abou{SE_M_SPIT_UP}me.\p"
	.string "I'l{SE_M_BATON_PASS}giv{SE_M_REVERSAL}yo{SE_M_DIVE}thi{SE_M_GRASSWHISTLE}fo{SE_M_SAND_TOMB}keepin{SE_M_SANDSTORM}my\n"
	.string "secret{SE_M_PERISH_SONG}Please?$"

Route28House_Text_Celebrity2:
	.string "It'{SE_M_GRASSWHISTLE}toug{SE_M_TRI_ATTACK}bein{SE_M_SANDSTORM}{SE_M_CHARGE}to{SE_M_MORNING_SUN}celebrity.\p"
	.string "Everywher{SE_M_REVERSAL}{SE_M_HEAL_BELL}go{SE_M_SUPERSONIC}peopl{SE_M_REVERSAL}chas{SE_M_REVERSAL}me.\p"
	.string "{SE_M_HEAL_BELL}jus{SE_M_SPIT_UP}wan{SE_M_SPIT_UP}t{SE_M_ATTRACT2}b{SE_M_REVERSAL}lef{SE_M_SPIT_UP}alone…$"

Route28House_Text_Fearow:
	.string "FEAROW{SE_M_HEAT_WAVE}Feero!$"

