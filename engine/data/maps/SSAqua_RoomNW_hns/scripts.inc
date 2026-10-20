@ Johto (data/maps/SSAqua_RoomNW_hns/scripts.inc), as built into the FireRed game.

SSAqua_RoomNW_hns_MapScripts::
	map_script 3, SSAqua_RoomNW_OnTransition
	.byte 0

SSAqua_RoomNW_OnTransition::
	goto_if_ge 20603, 3, SSAqua_RoomNW_SetTrainerPos
	end

SSAqua_RoomNW_SetTrainerPos::
	setobjectxyperm 2, 2, 6
	setobjectxyperm 3, 4, 3
	end

SSAqua_RoomNW_EventScript_Stanly::
	lock
	faceplayer
	msgbox SSAqua_RoomNW_Text_SailorStanlySeen, MSGBOX_DEFAULT
	trainerbattle_no_intro 1264, SSAqua_RoomNW_Text_SailorStanlyBeaten
	msgbox SSAqua_RoomNW_Text_SailorStanlyAfterBattle, MSGBOX_DEFAULT
	closemessage
	fadescreenswapbuffers 1
	delay 60
	playse 8
	removeobject 1
	fadescreenswapbuffers 0
	setvar 20603, 3
	end

SSAqua_RoomNW_EventScript_Edward::
	trainerbattle_single 1180, SSAqua_RoomNW_Text_GentlemanEdwardSeen, SSAqua_RoomNW_Text_GentlemanEdwardBeaten
	msgbox SSAqua_RoomNW_Text_GentlemanEdwardAfterBattle, MSGBOX_AUTOCLOSE
	end

SSAqua_RoomNW_EventScript_Corey::
	trainerbattle_single 1311, SSAqua_RoomNW_Text_BurglarCoreySeen, SSAqua_RoomNW_Text_BurglarCoreyBeaten
	msgbox SSAqua_RoomNW_Text_BurglarCoreyAfterBattle, MSGBOX_AUTOCLOSE
	end

SSAqua_RoomNW_Text_SailorStanlySeen:
	.string "Yeah{SE_M_SUPERSONIC}I'{SE_M_MILK_DRINK}{SE_M_CHARGE}sailor{SE_M_SUPERSONIC}al{SE_M_BATON_PASS}right.\p"
	.string "{SE_M_HEAL_BELL}wasn'{SE_M_SPIT_UP}goofin{SE_M_SANDSTORM}off!\p"
	.string "Thi{SE_M_GRASSWHISTLE}cabi{SE_M_ATTRACT}wa{SE_M_GRASSWHISTLE}vacant{SE_M_SUPERSONIC}s{SE_M_ATTRACT2}I\n"
	.string "jus{SE_M_SPIT_UP}too{SE_M_ENCORE2}{SE_M_CHARGE}quic{SE_M_ENCORE2}nap!\p"
	.string "Ah{SE_M_SUPERSONIC}forge{SE_M_SPIT_UP}it{SE_M_DRAGON_RAGE}Let'{SE_M_GRASSWHISTLE}battle!$"

SSAqua_RoomNW_Text_SailorStanlyBeaten:
	.string "Sorry{SE_M_DRAGON_RAGE}It'{SE_M_GRASSWHISTLE}al{SE_M_BATON_PASS}m{SE_M_YAWN}fault!$"

SSAqua_RoomNW_Text_SailorStanlyAfterBattle:
	.string "Bein{SE_M_SANDSTORM}{SE_M_CHARGE}sailor{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}hav{SE_M_REVERSAL}t{SE_M_ATTRACT2}do\n"
	.string "physica{SE_M_BATON_PASS}labor{SE_M_PERISH_SONG}It'{SE_M_GRASSWHISTLE}exhausting!$"

SSAqua_RoomNW_Text_GentlemanEdwardSeen:
	.string "Oh{SE_M_SUPERSONIC}no{SE_M_PERISH_SONG}I'v{SE_M_REVERSAL}los{SE_M_SPIT_UP}something\n"
	.string "that'{SE_M_GRASSWHISTLE}ver{SE_M_YAWN}important.$"

SSAqua_RoomNW_Text_GentlemanEdwardBeaten:
	.string "I{SE_M_DIZZY_PUNCH}{SE_M_HEAL_BELL}can'{SE_M_SPIT_UP}fin{SE_M_WATERFALL}it…$"

SSAqua_RoomNW_Text_GentlemanEdwardAfterBattle:
	.string "{SE_M_HEAL_BELL}giv{SE_M_REVERSAL}up{SE_M_PERISH_SONG}Yo{SE_M_DIVE}don'{SE_M_SPIT_UP}hav{SE_M_REVERSAL}to\n"
	.string "look.\p"
	.string "Jus{SE_M_SPIT_UP}forge{SE_M_SPIT_UP}abou{SE_M_SPIT_UP}it!$"

SSAqua_RoomNW_Text_BurglarCoreySeen:
	.string "Yeehaw{SE_M_DRAGON_RAGE}Lucky!$"

SSAqua_RoomNW_Text_BurglarCoreyBeaten:
	.string "Ho{SE_M_TWISTER}unlucky{SE_M_DRAGON_RAGE}{SE_M_HEAL_BELL}lost!$"

SSAqua_RoomNW_Text_BurglarCoreyAfterBattle:
	.string "{SE_M_HEAL_BELL}foun{SE_M_WATERFALL}{SE_M_CHARGE}prett{SE_M_YAWN}coi{SE_M_ATTRACT}here.\p"
	.string "Someon{SE_M_REVERSAL}mus{SE_M_SPIT_UP}hav{SE_M_REVERSAL}los{SE_M_SPIT_UP}it…$"

