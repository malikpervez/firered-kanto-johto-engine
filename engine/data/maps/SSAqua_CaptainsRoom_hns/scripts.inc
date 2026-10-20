@ Johto (data/maps/SSAqua_CaptainsRoom_hns/scripts.inc), as built into the FireRed game.

SSAqua_CaptainsRoom_hns_MapScripts::
	.byte 0

SSAqua_CaptainsRoom_EventScript_Captain::
	goto_if_eq 16384, 1, SSAqua_CaptainsRoom_EventScrip_CaptainAfter
	msgbox SSAqua_CaptainsRoom_Text_CaptainExhausting, MSGBOX_NPC
	setvar 16384, 1

SSAqua_CaptainsRoom_EventScrip_CaptainAfter::
	msgbox SSAqua_CaptainsRoom_Text_CaptainHowDoYouLike, MSGBOX_DEFAULT
	closemessage
	end

SSAqua_CaptainsRoom_EventScript_Granddaughter::
	lock
	applymovement 2, SSAqua_CaptainsRoom_Movement_Jump
	waitmovement 0
	msgbox SSAqua_CaptainsRoom_Text_GranddaughterCaptainPlayWithMe, MSGBOX_DEFAULT
	turnobject 1, DIR_WEST
	playse 21
	applymovement 1, J_Common_Movement_QuestionMark
	delay 55
	waitmovement 1
	delay 60
	faceplayer
	msgbox SSAqua_CaptainsRoom_Text_GranddaughterHasToFindGrandpa, MSGBOX_DEFAULT
	closemessage
	fadescreen 1
	setflag 8326
	setvar 20603, 4
	clearflag 8327
	warp MAP_SSAQUA_ROOM_SSE_HNS, 0
	waitstate
	release
	end

SSAqua_CaptainsRoom_Movement_Jump:
	jump_in_place_right
	jump_in_place_right
	jump_in_place_right
	step_end

SSAqua_CaptainsRoom_Text_GranddaughterCaptainPlayWithMe:
	.string "CAPTAIN{SE_M_SUPERSONIC}pla{SE_M_YAWN}wit{SE_M_TRI_ATTACK}me{SE_M_SUPERSONIC}please?\p"
	.string "I'{SE_M_MILK_DRINK}bored{SE_M_DRAGON_RAGE}{SE_M_HEAL_BELL}wan{SE_M_SPIT_UP}t{SE_M_ATTRACT2}pla{SE_M_YAWN}more!$"

SSAqua_CaptainsRoom_Text_GranddaughterHasToFindGrandpa:
	.string "Hi{SE_M_DRAGON_RAGE}Wil{SE_M_BATON_PASS}yo{SE_M_DIVE}pla{SE_M_YAWN}wit{SE_M_TRI_ATTACK}me?\p"
	.string "…Oh!\p"
	.string "Grandpa'{SE_M_GRASSWHISTLE}worrie{SE_M_WATERFALL}abou{SE_M_SPIT_UP}me?\p"
	.string "{SE_M_HEAL_BELL}hav{SE_M_REVERSAL}t{SE_M_ATTRACT2}go!\p"
	.string "{SE_M_HEAL_BELL}hav{SE_M_REVERSAL}t{SE_M_ATTRACT2}g{SE_M_ATTRACT2}fin{SE_M_WATERFALL}Grandpa!$"

SSAqua_CaptainsRoom_Text_CaptainExhausting:
	.string "Whew{SE_M_DRAGON_RAGE}Thank{SE_M_GRASSWHISTLE}fo{SE_M_SAND_TOMB}comin{SE_M_SANDSTORM}along.\p"
	.string "Keepin{SE_M_SANDSTORM}tha{SE_M_SPIT_UP}littl{SE_M_REVERSAL}gir{SE_M_BATON_PASS}amused\n"
	.string "wa{SE_M_GRASSWHISTLE}exhausting.$"

SSAqua_CaptainsRoom_Text_CaptainHowDoYouLike:
	.string "Ho{SE_M_TWISTER}d{SE_M_ATTRACT2}yo{SE_M_DIVE}lik{SE_M_REVERSAL}S.S.AQUA'{SE_M_GRASSWHISTLE}ride?\p"
	.string "Sh{SE_M_REVERSAL}practicall{SE_M_YAWN}skate{SE_M_GRASSWHISTLE}across\n"
	.string "th{SE_M_REVERSAL}waves.$"

