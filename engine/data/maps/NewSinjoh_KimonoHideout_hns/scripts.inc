@ Johto (data/maps/NewSinjoh_KimonoHideout_hns/scripts.inc), as built into the FireRed game.

NewSinjoh_KimonoHideout_hns_MapScripts::
	map_script 2, NewSinjoh_KimonoHideout_OnFrame
	.byte 0

NewSinjoh_KimonoHideout_OnFrame:
	map_script_2 20639, 4, NewSinjoh_KimonoHideout_EventScript_PlayerMeetsKimonos
	.2byte 0

NewSinjoh_KimonoHideout_EventScript_PlayerMeetsKimonos::
	lock
	msgbox NewSinjoh_KimonoHideout_Text_PlayerMeetsKimonos, MSGBOX_AUTOCLOSE
	applymovement 255, NewSinjoh_KimonoHideout_Movement_PlayerWalksIntoRoom
	waitmovement 0

	playse 202
	applymovement 3, NewSinjoh_KimonoHideout_Movement_KimonoWalksDown
	waitmovement 0
	msgbox NewSinjoh_KimonoHideout_Text_PlayerMeetsMiharu, MSGBOX_AUTOCLOSE
	playse 202
	applymovement 3, NewSinjoh_KimonoHideout_Movement_KimonoWalksUp
	waitmovement 0

	playse 202
	applymovement 1, NewSinjoh_KimonoHideout_Movement_KimonoWalksDown
	waitmovement 0
	msgbox NewSinjoh_KimonoHideout_Text_PlayerMeetsShizuko, MSGBOX_AUTOCLOSE
	playse 202
	applymovement 1, NewSinjoh_KimonoHideout_Movement_KimonoWalksUp
	waitmovement 0

	playse 202
	applymovement 2, NewSinjoh_KimonoHideout_Movement_KimonoWalksDown
	waitmovement 0
	msgbox NewSinjoh_KimonoHideout_Text_PlayerMeetsYouko, MSGBOX_AUTOCLOSE
	playse 202
	applymovement 2, NewSinjoh_KimonoHideout_Movement_KimonoWalksUp
	waitmovement 0

	setvar 20639, 5
	release
	end

NewSinjoh_KimonoHideout_Movement_PlayerWalksIntoRoom:
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

NewSinjoh_KimonoHideout_Movement_KimonoWalksDown:
	face_right
	delay_8
	face_up
	delay_8
	face_left
	delay_8
	face_down
	delay_8
	face_right
	delay_8
	face_up
	delay_8
	face_left
	delay_8
	face_down
	walk_down
	step_end

NewSinjoh_KimonoHideout_Movement_KimonoWalksUp:
	face_right
	delay_8
	face_up
	delay_8
	face_left
	delay_8
	face_down
	delay_8
	face_right
	delay_8
	face_up
	delay_8
	face_left
	delay_8
	face_down
	walk_up
	face_down
	step_end

NewSinjoh_KimonoHideout_Text_PlayerMeetsKimonos:
	.string "{PLAYER}.\p"
	.string "Please{SE_M_SUPERSONIC}approach.$"

NewSinjoh_KimonoHideout_Text_PlayerMeetsMiharu:
	.string "MIHARU{SE_M_HEAT_WAVE}Welcom{SE_M_REVERSAL}t{SE_M_ATTRACT2}NE{SE_M_DETECT}SINJOH{SE_M_SUPERSONIC}\n"
	.string "{PLAYER}.\p"
	.string "Fo{SE_M_SAND_TOMB}generations{SE_M_SUPERSONIC}thi{SE_M_GRASSWHISTLE}villag{SE_M_REVERSAL}has\n"
	.string "peacefull{SE_M_YAWN}coexiste{SE_M_WATERFALL}wit{SE_M_TRI_ATTACK}immensely\l"
	.string "powerfu{SE_M_BATON_PASS}POKéMON{SE_M_SUPERSONIC}i{SE_M_ATTRACT}isolatio{SE_M_ATTRACT}from\l"
	.string "th{SE_M_REVERSAL}pryin{SE_M_SANDSTORM}eye{SE_M_GRASSWHISTLE}o{SE_M_ACID_ARMOR}outsiders.\p"
	.string "Recen{SE_M_SPIT_UP}event{SE_M_GRASSWHISTLE}a{SE_M_SPIT_UP}ou{SE_M_SAND_TOMB}sacre{SE_M_WATERFALL}temple\n"
	.string "an{SE_M_WATERFALL}{SE_M_CHARGE}subsequen{SE_M_SPIT_UP}influ{SE_M_SWEET_SCENT}o{SE_M_ACID_ARMOR}uninvited\l"
	.string "guest{SE_M_GRASSWHISTLE}no{SE_M_TWISTER}threate{SE_M_ATTRACT}t{SE_M_ATTRACT2}disrup{SE_M_SPIT_UP}the\l"
	.string "carefu{SE_M_BATON_PASS}balanc{SE_M_REVERSAL}w{SE_M_REVERSAL}hav{SE_M_REVERSAL}long\l"
	.string "protected.$"

NewSinjoh_KimonoHideout_Text_PlayerMeetsShizuko:
	.string "SHIZUKO{SE_M_HEAT_WAVE}Ou{SE_M_SAND_TOMB}cousin{SE_M_GRASSWHISTLE}i{SE_M_ATTRACT}ECRUTEAK\n"
	.string "CIT{SE_M_MOONLIGHT}mad{SE_M_REVERSAL}u{SE_M_GRASSWHISTLE}awar{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}your\l"
	.string "connectio{SE_M_ATTRACT}t{SE_M_ATTRACT2}th{SE_M_REVERSAL}LEGENDAR{SE_M_MOONLIGHT}POKéMON\l"
	.string "o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}JOHT{SE_M_SOLAR_BEAM}REGION{SE_M_SUPERSONIC}an{SE_M_WATERFALL}your\l"
	.string "prowes{SE_M_GRASSWHISTLE}a{SE_M_GRASSWHISTLE}{SE_M_CHARGE}trainer.\p"
	.string "W{SE_M_REVERSAL}believ{SE_M_REVERSAL}yo{SE_M_DIVE}ca{SE_M_ATTRACT}hel{SE_M_MORNING_SUN}u{SE_M_GRASSWHISTLE}i{SE_M_ATTRACT}these\n"
	.string "tryin{SE_M_SANDSTORM}times.$"

NewSinjoh_KimonoHideout_Text_PlayerMeetsYouko:
	.string "YOUKO{SE_M_HEAT_WAVE}G{SE_M_ATTRACT2}t{SE_M_ATTRACT2}th{SE_M_REVERSAL}SINJO{SE_M_SWAGGER2}RUINS{SE_M_SUPERSONIC}to\n"
	.string "th{SE_M_REVERSAL}nort{SE_M_TRI_ATTACK}o{SE_M_ACID_ARMOR}ROUT{SE_M_SWORDS_DANCE}50.\p"
	.string "Mee{SE_M_SPIT_UP}wit{SE_M_TRI_ATTACK}th{SE_M_REVERSAL}scientist{SE_M_GRASSWHISTLE}there{SE_M_SUPERSONIC}and\n"
	.string "investigat{SE_M_REVERSAL}th{SE_M_REVERSAL}event{SE_M_GRASSWHISTLE}tha{SE_M_SPIT_UP}invoked\l"
	.string "thei{SE_M_SAND_TOMB}presence.\p"
	.string "I{SE_M_SPIT_UP}i{SE_M_GRASSWHISTLE}imperativ{SE_M_REVERSAL}tha{SE_M_SPIT_UP}th{SE_M_REVERSAL}LEGENDARY\n"
	.string "POKéMO{SE_M_PSYBEAM2}ther{SE_M_REVERSAL}ar{SE_M_REVERSAL}no{SE_M_SPIT_UP}disturbed\l"
	.string "b{SE_M_YAWN}th{SE_M_REVERSAL}unworthy.$"

NewSinjoh_KimonoHideout_EventScript_Miharu::
	lock
	faceplayer
	goto_if_ge 20639, 13, NewSinjoh_KimonoHideout_EventScript_MiharuFinal
	goto_if_defeated 1633, NewSinjoh_KimonoHideout_EventScript_MiharuAfter
	msgbox NewSinjoh_KimonoHideout_Text_PlayerMeetsMiharu, MSGBOX_AUTOCLOSE
	goto_if_not_defeated 1633, NewSinjoh_KimonoHideout_EventScript_TryMiharuBattle
	release
	end

NewSinjoh_KimonoHideout_EventScript_TryMiharuBattle::
	goto_if_eq 20639, 6, NewSinjoh_KimonoHideout_EventScript_MiharuBattle
	release
	end

NewSinjoh_KimonoHideout_EventScript_MiharuBattle::
	msgbox NewSinjoh_KimonoHideout_Text_MiharuBeforeBattle, MSGBOX_DEFAULT
	closemessage
	settotemboost B_POSITION_OPPONENT_LEFT, 2, 2, 0, 0, 2, 0
	trainerbattle_no_intro 1633, EcruteakCity_Theater_Text_KimonoGirlBeaten
	giveitem ITEM_MEADOW_PLATE
	addvar 20640, 1
	msgbox NewSinjoh_KimonoHideout_Text_MiharuAfter, MSGBOX_DEFAULT
	closemessage
	call_if_eq 20640, 3, SinjohRuins_Lab_EventScript_3Plates
	call_if_eq 20640, 6, SinjohRuins_Lab_EventScript_6Plates
	call_if_eq 20640, 9, SinjohRuins_Lab_EventScript_9Plates
	call_if_eq 20640, 12, SinjohRuins_Lab_EventScript_12Plates
	call_if_eq 20640, 15, SinjohRuins_Lab_EventScript_15Plates
	call_if_eq 20640, 16, SinjohRuins_Lab_EventScript_16Plates
	release
	end

NewSinjoh_KimonoHideout_EventScript_MiharuAfter::
	msgbox NewSinjoh_KimonoHideout_Text_MiharuAfter, MSGBOX_AUTOCLOSE
	release
	end

NewSinjoh_KimonoHideout_Text_MiharuBeforeBattle:
	.string "MIHARU{SE_M_HEAT_WAVE}Jus{SE_M_SPIT_UP}a{SE_M_GRASSWHISTLE}w{SE_M_REVERSAL}predicted.\p"
	.string "Th{SE_M_REVERSAL}champio{SE_M_ATTRACT}o{SE_M_ACID_ARMOR}ston{SE_M_REVERSAL}sen{SE_M_SPIT_UP}you\n"
	.string "t{SE_M_ATTRACT2}collec{SE_M_SPIT_UP}th{SE_M_REVERSAL}PLATES.\p"
	.string "Ou{SE_M_SAND_TOMB}orde{SE_M_SAND_TOMB}ha{SE_M_GRASSWHISTLE}guarde{SE_M_WATERFALL}these\n"
	.string "PLATE{SE_M_SKETCH}fo{SE_M_SAND_TOMB}centuries.\p"
	.string "W{SE_M_REVERSAL}wil{SE_M_BATON_PASS}no{SE_M_SPIT_UP}par{SE_M_SPIT_UP}wit{SE_M_TRI_ATTACK}them\n"
	.string "readily.$"

NewSinjoh_KimonoHideout_Text_MiharuAfter:
	.string "MIHARU{SE_M_HEAT_WAVE}Yo{SE_M_DIVE}ar{SE_M_REVERSAL}worthy.$"

NewSinjoh_KimonoHideout_EventScript_MiharuFinal::
	msgbox NewSinjoh_KimonoHideout_Text_MiharuFinal, MSGBOX_AUTOCLOSE
	end

NewSinjoh_KimonoHideout_Text_MiharuFinal:
	.string "MIHARU{SE_M_HEAT_WAVE}Yo{SE_M_DIVE}hav{SE_M_REVERSAL}don{SE_M_REVERSAL}ou{SE_M_SAND_TOMB}village\n"
	.string "{SE_M_CHARGE}grea{SE_M_SPIT_UP}service{SE_M_SUPERSONIC}{PLAYER}.\p"
	.string "W{SE_M_REVERSAL}wil{SE_M_BATON_PASS}no{SE_M_SPIT_UP}forge{SE_M_SPIT_UP}this.$"

NewSinjoh_KimonoHideout_EventScript_Youko::
	lock
	faceplayer
	goto_if_ge 20639, 13, NewSinjoh_KimonoHideout_EventScript_YoukoFinal
	goto_if_defeated 1634, NewSinjoh_KimonoHideout_EventScript_YoukoAfter
	msgbox NewSinjoh_KimonoHideout_Text_PlayerMeetsYouko, MSGBOX_AUTOCLOSE
	goto_if_not_defeated 1634, NewSinjoh_KimonoHideout_EventScript_TryYoukoBattle
	release
	end

NewSinjoh_KimonoHideout_EventScript_TryYoukoBattle::
	goto_if_eq 20639, 6, NewSinjoh_KimonoHideout_EventScript_YoukoBattle
	release
	end

NewSinjoh_KimonoHideout_EventScript_YoukoBattle::
	msgbox NewSinjoh_KimonoHideout_Text_YoukoBeforeBattle, MSGBOX_DEFAULT
	closemessage
	settotemboost B_POSITION_OPPONENT_LEFT, 0, 2, 1, 2, 2, 2
	trainerbattle_no_intro 1634, EcruteakCity_Theater_Text_KimonoGirlBeaten
	giveitem ITEM_ICICLE_PLATE
	addvar 20640, 1
	msgbox NewSinjoh_KimonoHideout_Text_YoukoAfter, MSGBOX_DEFAULT
	closemessage
	call_if_eq 20640, 3, SinjohRuins_Lab_EventScript_3Plates
	call_if_eq 20640, 6, SinjohRuins_Lab_EventScript_6Plates
	call_if_eq 20640, 9, SinjohRuins_Lab_EventScript_9Plates
	call_if_eq 20640, 12, SinjohRuins_Lab_EventScript_12Plates
	call_if_eq 20640, 15, SinjohRuins_Lab_EventScript_15Plates
	call_if_eq 20640, 16, SinjohRuins_Lab_EventScript_16Plates
	release
	end

NewSinjoh_KimonoHideout_EventScript_YoukoAfter::
	msgbox NewSinjoh_KimonoHideout_Text_YoukoAfter, MSGBOX_AUTOCLOSE
	release
	end

NewSinjoh_KimonoHideout_Text_YoukoBeforeBattle:
	.string "YOUKO{SE_M_HEAT_WAVE}Ou{SE_M_SAND_TOMB}cousin{SE_M_GRASSWHISTLE}spea{SE_M_ENCORE2}so\n"
	.string "highl{SE_M_YAWN}o{SE_M_ACID_ARMOR}you.\p"
	.string "I{SE_M_GRASSWHISTLE}i{SE_M_SPIT_UP}true?\p"
	.string "{SE_M_HEAL_BELL}wil{SE_M_BATON_PASS}fin{SE_M_WATERFALL}out.$"

NewSinjoh_KimonoHideout_Text_YoukoAfter:
	.string "YOUKO{SE_M_HEAT_WAVE}Ou{SE_M_SAND_TOMB}cousin{SE_M_GRASSWHISTLE}wer{SE_M_REVERSAL}right\n"
	.string "abou{SE_M_SPIT_UP}you.$"

NewSinjoh_KimonoHideout_EventScript_YoukoFinal::
	msgbox NewSinjoh_KimonoHideout_Text_YoukoFinal, MSGBOX_AUTOCLOSE
	end

NewSinjoh_KimonoHideout_Text_YoukoFinal:
	.string "YOUKO{SE_M_HEAT_WAVE}{SE_M_HEAL_BELL}ha{SE_M_WATERFALL}m{SE_M_YAWN}doubts{SE_M_SUPERSONIC}a{SE_M_SPIT_UP}first.\p"
	.string "Bu{SE_M_SPIT_UP}afte{SE_M_SAND_TOMB}wha{SE_M_SPIT_UP}you'v{SE_M_REVERSAL}done{SE_M_SUPERSONIC}it\n"
	.string "canno{SE_M_SPIT_UP}b{SE_M_REVERSAL}denied.$"

NewSinjoh_KimonoHideout_EventScript_Shizuko::
	lock
	faceplayer
	goto_if_ge 20639, 13, NewSinjoh_KimonoHideout_EventScript_ShizukoFinal
	goto_if_defeated 1635, NewSinjoh_KimonoHideout_EventScript_ShizukoAfter
	msgbox NewSinjoh_KimonoHideout_Text_PlayerMeetsShizuko, MSGBOX_AUTOCLOSE
	goto_if_not_defeated 1635, NewSinjoh_KimonoHideout_EventScript_TryShizukoBattle
	release
	end

NewSinjoh_KimonoHideout_EventScript_TryShizukoBattle::
	goto_if_eq 20639, 6, NewSinjoh_KimonoHideout_EventScript_ShizukoBattle
	release
	end

NewSinjoh_KimonoHideout_EventScript_ShizukoBattle::
	msgbox NewSinjoh_KimonoHideout_Text_ShizukoBeforeBattle, MSGBOX_DEFAULT
	closemessage
	settotemboost B_POSITION_OPPONENT_LEFT, 2, 1, 0, 0, 1, 0
	trainerbattle_no_intro 1635, EcruteakCity_Theater_Text_KimonoGirlBeaten
	giveitem ITEM_PIXIE_PLATE
	addvar 20640, 1
	msgbox NewSinjoh_KimonoHideout_Text_ShizukoAfter, MSGBOX_DEFAULT
	closemessage
	call_if_eq 20640, 3, SinjohRuins_Lab_EventScript_3Plates
	call_if_eq 20640, 6, SinjohRuins_Lab_EventScript_6Plates
	call_if_eq 20640, 9, SinjohRuins_Lab_EventScript_9Plates
	call_if_eq 20640, 12, SinjohRuins_Lab_EventScript_12Plates
	call_if_eq 20640, 15, SinjohRuins_Lab_EventScript_15Plates
	call_if_eq 20640, 16, SinjohRuins_Lab_EventScript_16Plates
	release
	end

NewSinjoh_KimonoHideout_EventScript_ShizukoAfter::
	msgbox NewSinjoh_KimonoHideout_Text_ShizukoAfter, MSGBOX_AUTOCLOSE
	release
	end

NewSinjoh_KimonoHideout_Text_ShizukoBeforeBattle:
	.string "SHIZUKO{SE_M_HEAT_WAVE}W{SE_M_REVERSAL}ar{SE_M_REVERSAL}traine{SE_M_WATERFALL}in\n"
	.string "battl{SE_M_REVERSAL}a{SE_M_GRASSWHISTLE}wel{SE_M_BATON_PASS}a{SE_M_GRASSWHISTLE}dance.\p"
	.string "Obtainin{SE_M_SANDSTORM}th{SE_M_REVERSAL}PLATE{SE_M_GRASSWHISTLE}will\n"
	.string "requir{SE_M_REVERSAL}strengt{SE_M_TRI_ATTACK}an{SE_M_WATERFALL}determination.$"

NewSinjoh_KimonoHideout_Text_ShizukoAfter:
	.string "SHIZUKO{SE_M_HEAT_WAVE}Th{SE_M_REVERSAL}bon{SE_M_WATERFALL}yo{SE_M_DIVE}share\n"
	.string "wit{SE_M_TRI_ATTACK}you{SE_M_SAND_TOMB}POKéMO{SE_M_PSYBEAM2}i{SE_M_GRASSWHISTLE}quit{SE_M_REVERSAL}strong.\p"
	.string "Yo{SE_M_DIVE}hav{SE_M_REVERSAL}earne{SE_M_WATERFALL}thi{SE_M_GRASSWHISTLE}PLATE.$"

NewSinjoh_KimonoHideout_EventScript_ShizukoFinal::
	msgbox NewSinjoh_KimonoHideout_Text_ShizukoFinal, MSGBOX_AUTOCLOSE
	end

NewSinjoh_KimonoHideout_Text_ShizukoFinal:
	.string "SHIZUKO{SE_M_HEAT_WAVE}Fe{SE_M_TWISTER}trainer{SE_M_GRASSWHISTLE}i{SE_M_ATTRACT}all\n"
	.string "o{SE_M_ACID_ARMOR}SINJOH'{SE_M_GRASSWHISTLE}storie{SE_M_WATERFALL}histor{SE_M_YAWN}have\l"
	.string "manage{SE_M_WATERFALL}wha{SE_M_SPIT_UP}you'v{SE_M_REVERSAL}jus{SE_M_SPIT_UP}done.\p"
	.string "Quit{SE_M_REVERSAL}impressive{SE_M_SUPERSONIC}{PLAYER}.$"

NewSinjoh_KimonoHideout_EventScript_OldMan::
	msgbox NewSinjoh_KimonoHideout_Text_OldMan, MSGBOX_NPC
	end

NewSinjoh_KimonoHideout_Text_OldMan:
	.string "Th{SE_M_REVERSAL}KIMON{SE_M_SOLAR_BEAM}GIRL{SE_M_SKETCH}hav{SE_M_REVERSAL}watched\n"
	.string "ove{SE_M_SAND_TOMB}ou{SE_M_SAND_TOMB}villag{SE_M_REVERSAL}sinc{SE_M_REVERSAL}it{SE_M_GRASSWHISTLE}founding.\p"
	.string "The{SE_M_YAWN}hav{SE_M_REVERSAL}sacrifice{SE_M_WATERFALL}much.\p"
	.string "Blesse{SE_M_WATERFALL}b{SE_M_YAWN}th{SE_M_REVERSAL}God{SE_M_GRASSWHISTLE}themselves,\n"
	.string "the{SE_M_YAWN}hav{SE_M_REVERSAL}power{SE_M_GRASSWHISTLE}beyon{SE_M_WATERFALL}that\l"
	.string "o{SE_M_ACID_ARMOR}an{SE_M_YAWN}norma{SE_M_BATON_PASS}trainer!\p"
	.string "Tha{SE_M_SPIT_UP}i{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}say{SE_M_SUPERSONIC}b{SE_M_REVERSAL}prepared\n"
	.string "i{SE_M_ACID_ARMOR}yo{SE_M_DIVE}eve{SE_M_SAND_TOMB}figh{SE_M_SPIT_UP}them{SE_M_SUPERSONIC}youn{SE_M_SANDSTORM}one.$"

NewSinjoh_KimonoHideout_Text_OldManAfter:
	.string "Yo{SE_M_DIVE}hav{SE_M_REVERSAL}beste{SE_M_WATERFALL}th{SE_M_REVERSAL}champion{SE_M_GRASSWHISTLE}of\n"
	.string "ou{SE_M_SAND_TOMB}village.\p"
	.string "Wha{SE_M_SPIT_UP}doe{SE_M_GRASSWHISTLE}tha{SE_M_SPIT_UP}mak{SE_M_REVERSAL}you{SE_M_SUPERSONIC}youn{SE_M_SANDSTORM}one?$"

