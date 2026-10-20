@ Johto (data/maps/SproutTower_3F_hns/scripts.inc), as built into the FireRed game.

SproutTower_3F_hns_MapScripts::
	map_script 3, SproutTower_3F_OnTransition
	map_script 5, J_SetTimeEncounters
	.byte 0

SproutTower_3F_OnTransition:
	callnative SetTimeBasedEncounters
	end

SproutTower_3F_EventScript_SageJin::
	trainerbattle_single 1376, SproutTower_Text_SageJin_Seen, SproutTower_Text_SageJin_Beaten
	msgbox SproutTower_Text_SageJin_AfterBattle, MSGBOX_AUTOCLOSE
	end

SproutTower_3F_EventScript_SageNeal::
	trainerbattle_single 1381, SproutTower_Text_SageNeal_Seen, SproutTower_Text_SageNeal_Beaten
	msgbox SproutTower_Text_SageNeal_AfterBattle, MSGBOX_AUTOCLOSE
	end

SproutTower_3F_EventScript_SageTroy::
	trainerbattle_single 1377, SproutTower_Text_SageTroy_Seen, SproutTower_Text_SageTroy_Beaten
	msgbox SproutTower_Text_SageTroy_AfterBattle, MSGBOX_AUTOCLOSE
	end

SproutTower_3F_EventScript_Painting::
	lock
	msgbox SproutTower_Text_3F_Painting, MSGBOX_AUTOCLOSE
	release
	end

SproutTower_3F_EventScript_Potion::
	finditem ITEM_POTION
	end

SproutTower_3F_EventScript_EscapeRope::
	finditem ITEM_ESCAPE_ROPE
	end

SproutTower_3F_EventScript_TriggerSceneLeft::
	lock
	playbgm ((558 + 1) + 0x3B), FALSE
	applymovement 5, SproutTower_3F_Movement_Silver1
	waitmovement 0
	msgbox SproutTower_Text_ElderLecturesRival, MSGBOX_DEFAULT
	closemessage
	playse 21
	applymovement 5, J_Common_Movement_ExclamationMark
	delay 55
	waitmovement 5
	applymovement 5, SproutTower_3F_Movement_SilverLeft
	waitmovement 0
	msgbox SproutTower_Text_RivalOnlyCaresStrong, MSGBOX_DEFAULT
	delay 30
	msgbox SproutTower_Text_RivalUsedEscapeRope, MSGBOX_DEFAULT
	applymovement 5 SproutTower_3F_Movement_EscapeRope
	waitmovement 0
	closemessage
	fadescreen 1
	playse 9
	setflag 8280
	removeobject 5
	delay 55
	fadescreen 0
	special DrawWholeMapView
	fadedefaultbgm
	setvar 20656, 1
	release
	end

SproutTower_3F_EventScript_TriggerSceneRight::
	lock
	playbgm ((558 + 1) + 0x3B), FALSE
	applymovement 5, SproutTower_3F_Movement_Silver1
	waitmovement 0
	msgbox SproutTower_Text_ElderLecturesRival, MSGBOX_DEFAULT
	closemessage
	playse 21
	applymovement 5, J_Common_Movement_ExclamationMark
	delay 55
	waitmovement 5
	applymovement 5, SproutTower_3F_Movement_SilverRight
	waitmovement 0
	waitmovement 0
	msgbox SproutTower_Text_RivalOnlyCaresStrong, MSGBOX_DEFAULT
	msgbox SproutTower_Text_RivalUsedEscapeRope, MSGBOX_DEFAULT
	applymovement 5 SproutTower_3F_Movement_EscapeRope
	waitmovement 0
	closemessage
	fadescreen 1
	playse 9
	setflag 8280
	removeobject 5
	delay 55
	fadescreen 0
	special DrawWholeMapView
	fadedefaultbgm
	setvar 20656, 1
	release
	end

SproutTower_3F_EventScript_SageLi::
	lock
	faceplayer
	goto_if_set 8694, SproutTower_3F_EventScript_SageLi_Beaten
	msgbox SproutTower_Text_SageLi_Seen, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro 1382, SproutTower_Text_SageLi_Beaten
	msgbox SproutTower_Text_SageLi_TakeFlash, MSGBOX_DEFAULT
	giveitem 686
	setflag 8694
	msgbox SproutTower_Text_SageLi_FlashExplain, MSGBOX_DEFAULT
	closemessage
	release
	end

SproutTower_3F_EventScript_SageLi_Beaten::
	msgbox SproutTower_Text_SageLi_AfterBattle, MSGBOX_DEFAULT
	closemessage
	release
	end

SproutTower_3F_Movement_Silver1:
	walk_fast_up
	walk_fast_up
	step_end

SproutTower_3F_Movement_SilverLeft:
	face_down
	delay_16
	walk_right
	walk_right
	walk_down
	walk_down
	step_end

SproutTower_3F_Movement_SilverRight:
	face_down
	delay_16
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	step_end

SproutTower_3F_Movement_EscapeRope:
	face_right
	face_up
	face_left
	face_down
	face_right
	face_up
	face_left
	face_down
	face_right
	face_up
	face_left
	face_down
	step_end

SproutTower_Text_ElderLecturesRival:
	.string "ELDER{SE_M_HEAT_WAVE}Yo{SE_M_DIVE}ar{SE_M_REVERSAL}indee{SE_M_WATERFALL}skilled\n"
	.string "a{SE_M_GRASSWHISTLE}{SE_M_CHARGE}trainer.\p"
	.string "A{SE_M_GRASSWHISTLE}promised{SE_M_SUPERSONIC}her{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}you{SE_M_SAND_TOMB}HM.\p"
	.string "Bu{SE_M_SPIT_UP}le{SE_M_SPIT_UP}m{SE_M_REVERSAL}sa{SE_M_YAWN}this{SE_M_HEAT_WAVE}Yo{SE_M_DIVE}should\n"
	.string "trea{SE_M_SPIT_UP}you{SE_M_SAND_TOMB}POKéMO{SE_M_PSYBEAM2}better.\p"
	.string "Th{SE_M_REVERSAL}wa{SE_M_YAWN}yo{SE_M_DIVE}battl{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}fa{SE_M_SAND_TOMB}too\n"
	.string "harsh.\p"
	.string "POKéMO{SE_M_PSYBEAM2}ar{SE_M_REVERSAL}no{SE_M_SPIT_UP}tool{SE_M_GRASSWHISTLE}o{SE_M_ACID_ARMOR}war…$"

SproutTower_Text_RivalOnlyCaresStrong:
	.string "…\n"
	.string "…Humph!\p"
	.string "H{SE_M_REVERSAL}claim{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}b{SE_M_REVERSAL}th{SE_M_REVERSAL}ELDE{SE_M_MINIMIZE}but\n"
	.string "he'{SE_M_GRASSWHISTLE}weak.\p"
	.string "I{SE_M_SPIT_UP}stand{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}reason.\p"
	.string "I'{SE_M_WATERFALL}neve{SE_M_SAND_TOMB}los{SE_M_REVERSAL}t{SE_M_ATTRACT2}fool{SE_M_GRASSWHISTLE}wh{SE_M_ATTRACT2}babble\n"
	.string "abou{SE_M_SPIT_UP}bein{SE_M_SANDSTORM}nic{SE_M_REVERSAL}t{SE_M_ATTRACT2}POKéMON.\p"
	.string "{SE_M_HEAL_BELL}onl{SE_M_YAWN}car{SE_M_REVERSAL}abou{SE_M_SPIT_UP}strong\n"
	.string "POKéMO{SE_M_PSYBEAM2}tha{SE_M_SPIT_UP}ca{SE_M_ATTRACT}win.\p"
	.string "{SE_M_HEAL_BELL}reall{SE_M_YAWN}couldn'{SE_M_SPIT_UP}car{SE_M_REVERSAL}less\n"
	.string "abou{SE_M_SPIT_UP}wea{SE_M_ENCORE2}POKéMON.$"

SproutTower_Text_RivalUsedEscapeRope:
	.string "{RIVAL} use{SE_M_WATERFALL}a{SE_M_ATTRACT}ESCAP{SE_M_SWORDS_DANCE}ROPE!$"

SproutTower_Text_SageLi_Seen:
	.string "S{SE_M_ATTRACT2}goo{SE_M_WATERFALL}o{SE_M_ACID_ARMOR}yo{SE_M_DIVE}t{SE_M_ATTRACT2}com{SE_M_REVERSAL}here!\p"
	.string "SPROU{SE_M_SWIFT}TOWE{SE_M_MINIMIZE}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}plac{SE_M_REVERSAL}of\n"
	.string "training.\p"
	.string "Peopl{SE_M_REVERSAL}an{SE_M_WATERFALL}POKéMO{SE_M_PSYBEAM2}tes{SE_M_SPIT_UP}their\n"
	.string "bond{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}buil{SE_M_WATERFALL}{SE_M_CHARGE}brigh{SE_M_SPIT_UP}future\l"
	.string "together.\p"
	.string "{SE_M_HEAL_BELL}a{SE_M_MILK_DRINK}th{SE_M_REVERSAL}fina{SE_M_BATON_PASS}test.\p"
	.string "Allo{SE_M_TWISTER}m{SE_M_REVERSAL}t{SE_M_ATTRACT2}chec{SE_M_ENCORE2}th{SE_M_REVERSAL}ties\n"
	.string "betwee{SE_M_ATTRACT}you{SE_M_SAND_TOMB}POKéMO{SE_M_PSYBEAM2}an{SE_M_WATERFALL}you!$"

SproutTower_Text_SageLi_Beaten:
	.string "Ah{SE_M_SUPERSONIC}excellent!$"

SproutTower_Text_SageLi_TakeFlash:
	.string "Yo{SE_M_DIVE}an{SE_M_WATERFALL}you{SE_M_SAND_TOMB}POKéMO{SE_M_PSYBEAM2}should\n"
	.string "hav{SE_M_REVERSAL}n{SE_M_ATTRACT2}proble{SE_M_MILK_DRINK}usin{SE_M_SANDSTORM}thi{SE_M_GRASSWHISTLE}move.\p"
	.string "Tak{SE_M_REVERSAL}thi{SE_M_GRASSWHISTLE}FLAS{SE_M_SWAGGER2}HM.$"

SproutTower_Text_SageLi_FlashExplain:
	.string "FLAS{SE_M_SWAGGER2}illuminate{SE_M_GRASSWHISTLE}eve{SE_M_ATTRACT}the\n"
	.string "darkes{SE_M_SPIT_UP}o{SE_M_ACID_ARMOR}al{SE_M_BATON_PASS}places.\p"
	.string "Bu{SE_M_SPIT_UP}t{SE_M_ATTRACT2}us{SE_M_REVERSAL}i{SE_M_SPIT_UP}ou{SE_M_SPIT_UP}o{SE_M_ACID_ARMOR}battle{SE_M_SUPERSONIC}you\n"
	.string "nee{SE_M_WATERFALL}th{SE_M_REVERSAL}BADG{SE_M_SWORDS_DANCE}fro{SE_M_MILK_DRINK}VIOLET'{SE_M_GRASSWHISTLE}GYM.$"

SproutTower_Text_SageLi_AfterBattle:
	.string "{SE_M_HEAL_BELL}hop{SE_M_REVERSAL}yo{SE_M_DIVE}lear{SE_M_ATTRACT}an{SE_M_WATERFALL}gro{SE_M_TWISTER}from\n"
	.string "you{SE_M_SAND_TOMB}journey.$"

SproutTower_Text_SageJin_Seen:
	.string "{SE_M_HEAL_BELL}trai{SE_M_ATTRACT}t{SE_M_ATTRACT2}fin{SE_M_WATERFALL}enlightenment\n"
	.string "i{SE_M_ATTRACT}POKéMON!$"

SproutTower_Text_SageJin_Beaten:
	.string "M{SE_M_YAWN}trainin{SE_M_SANDSTORM}i{SE_M_GRASSWHISTLE}incomplete…$"

SproutTower_Text_SageJin_AfterBattle:
	.string "A{SE_M_GRASSWHISTLE}POKéMO{SE_M_PSYBEAM2}gro{SE_M_TWISTER}stronger,\n"
	.string "s{SE_M_ATTRACT2}doe{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}trainer.\p"
	.string "No{SE_M_SUPERSONIC}wait{SE_M_PERISH_SONG}A{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}trainer\n"
	.string "grow{SE_M_GRASSWHISTLE}stronger{SE_M_SUPERSONIC}s{SE_M_ATTRACT2}d{SE_M_ATTRACT2}the\l"
	.string "POKéMON.$"

SproutTower_Text_SageTroy_Seen:
	.string "Le{SE_M_SPIT_UP}m{SE_M_REVERSAL}se{SE_M_REVERSAL}ho{SE_M_TWISTER}muc{SE_M_TRI_ATTACK}yo{SE_M_DIVE}trust\n"
	.string "you{SE_M_SAND_TOMB}POKéMON.$"

SproutTower_Text_SageTroy_Beaten:
	.string "Yes{SE_M_SUPERSONIC}you{SE_M_SAND_TOMB}trus{SE_M_SPIT_UP}i{SE_M_GRASSWHISTLE}real!$"

SproutTower_Text_SageTroy_AfterBattle:
	.string "I{SE_M_SPIT_UP}i{SE_M_GRASSWHISTLE}no{SE_M_SPIT_UP}fa{SE_M_SAND_TOMB}t{SE_M_ATTRACT2}th{SE_M_REVERSAL}ELDER.$"

SproutTower_Text_SageNeal_Seen:
	.string "Th{SE_M_REVERSAL}ELDER'{SE_M_GRASSWHISTLE}H{SE_M_GIGA_DRAIN}light{SE_M_GRASSWHISTLE}even\n"
	.string "pitch-blac{SE_M_ENCORE2}darkness.$"

SproutTower_Text_SageNeal_Beaten:
	.string "I{SE_M_SPIT_UP}i{SE_M_GRASSWHISTLE}m{SE_M_YAWN}hea{SE_M_WATERFALL}tha{SE_M_SPIT_UP}i{SE_M_GRASSWHISTLE}bright!$"

SproutTower_Text_SageNeal_AfterBattle:
	.string "Le{SE_M_SPIT_UP}ther{SE_M_REVERSAL}b{SE_M_REVERSAL}ligh{SE_M_SPIT_UP}o{SE_M_ATTRACT}your\n"
	.string "journey.$"

SproutTower_Text_3F_Painting:
	.string "It'{SE_M_GRASSWHISTLE}{SE_M_CHARGE}powerfu{SE_M_BATON_PASS}paintin{SE_M_SANDSTORM}o{SE_M_ACID_ARMOR}a\n"
	.string "BELLSPROUT.$"

