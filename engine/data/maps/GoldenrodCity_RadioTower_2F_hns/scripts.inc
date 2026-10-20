@ Johto (data/maps/GoldenrodCity_RadioTower_2F_hns/scripts.inc), as built into the FireRed game.

GoldenrodCity_RadioTower_2F_hns_MapScripts::
	.byte 0

GoldenrodRaidoTower2_EventScript_Grunt3::
	trainerbattle_single TRAINER_JOHTO_GRUNT_3_HNS, GoldenrodCity_RadioTower_2F_Text_GruntM4Seen, GoldenrodCity_RadioTower_2F_Text_GruntM4Beaten
	msgbox GoldenrodCity_RadioTower_2F_Text_GruntM4After, MSGBOX_AUTOCLOSE
	end

GoldenrodRaidoTower2_EventScript_Grunt4::
	trainerbattle_single TRAINER_JOHTO_GRUNT_4_HNS, GoldenrodCity_RadioTower_2F_Text_GruntM5Seen, GoldenrodCity_RadioTower_2F_Text_GruntM5Beaten
	msgbox GoldenrodCity_RadioTower_2F_Text_GruntM5After, MSGBOX_AUTOCLOSE
	end

GoldenrodRaidoTower2_EventScript_Grunt5::
	trainerbattle_single TRAINER_JOHTO_GRUNT_5_HNS, GoldenrodCity_RadioTower_2F_Text_GruntM6Seen, GoldenrodCity_RadioTower_2F_Text_GruntM6Beaten
	msgbox GoldenrodCity_RadioTower_2F_Text_GruntM6After, MSGBOX_AUTOCLOSE
	end

GoldenrodRaidoTower2_EventScript_GruntF2::
	trainerbattle_single TRAINER_JOHTO_GRUNT_26_HNS, GoldenrodCity_RadioTower_2F_Text_GruntF2Seen, GoldenrodCity_RadioTower_2F_Text_GruntF2Beaten
	msgbox GoldenrodCity_RadioTower_2F_Text_GruntF2After, MSGBOX_AUTOCLOSE
	end

GoldenrodCity_RadioTower_2F_EventScript_Sign1::
	lock
	msgbox GoldenrodCity_RadioTower_2F_Text_SalesSign, MSGBOX_SIGN
	closemessage
	release
	end

GoldenrodCity_RadioTower_2F_EventScript_Sign2::
	lock
	msgbox GoldenrodCity_RadioTower_2F_Text_OakTalkSign, MSGBOX_SIGN
	closemessage
	release
	end

GoldenrodCity_RadioTower_2F_EventScript_Boy::
	lock
	faceplayer
	msgbox GoldenrodCity_RadioTower_2F_Text_SuperNerd, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_2F_EventScript_Policeman::
	lock
	faceplayer
	msgbox GoldenrodCity_RadioTower_2F_Text_Policeman, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_2F_EventScript_Buena::
	lock
	faceplayer
	goto_if_eq JOHTO_VAR_GOLDENROD_CITY_STATE, 6, GoldenrodCity_RadioTower_2F_EventScript_BuenaRocket
	goto_if_eq JOHTO_VAR_GOLDENROD_CITY_STATE, 7, GoldenrodCity_RadioTower_2F_EventScript_BuenaRocket
	goto_if_eq JOHTO_VAR_GOLDENROD_CITY_STATE, 8, GoldenrodCity_RadioTower_2F_EventScript_BuenaRocket
	goto_if_eq JOHTO_VAR_GOLDENROD_CITY_STATE, 9, GoldenrodCity_RadioTower_2F_EventScript_BuenaRocket
	goto_if_set JOHTO_FLAG_DAILY_BUENAS_PASSWORD_GUESSED, GoldenrodCity_RadioTower_2F_EventScript_BuenaAlreadyPlayed
	goto_if_unset JOHTO_FLAG_DAILY_BUENAS_PASSWORD, GoldenrodCity_RadioTower_2F_EventScript_BuenaNoShow
	msgbox GoldenrodCity_RadioTower_2F_Text_BuenaAskPassword, MSGBOX_DEFAULT
	special Special_BuenaPasswordShowMultichoice
	waitstate
	compare VAR_RESULT, 127
	goto_if_eq GoldenrodCity_RadioTower_2F_EventScript_BuenaCancelled
	special Special_BuenaCheckAnswer
	compare VAR_RESULT, TRUE
	goto_if_eq GoldenrodCity_RadioTower_2F_EventScript_BuenaCorrect
	setflag JOHTO_FLAG_DAILY_BUENAS_PASSWORD_GUESSED
	msgbox GoldenrodCity_RadioTower_2F_Text_BuenaWrong, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_2F_EventScript_BuenaCorrect::
	special Special_BuenaRollReward
	copyvar VAR_0x8004, VAR_RESULT
	checkitemspace VAR_0x8004, 1
	compare VAR_RESULT, FALSE
	goto_if_eq GoldenrodCity_RadioTower_2F_EventScript_BuenaBagFull
	giveitem VAR_0x8004, 1
	setflag JOHTO_FLAG_DAILY_BUENAS_PASSWORD_GUESSED
	msgbox GoldenrodCity_RadioTower_2F_Text_BuenaCorrect, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_2F_EventScript_BuenaBagFull::
	msgbox GoldenrodCity_RadioTower_2F_Text_BuenaBagFull, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_2F_EventScript_BuenaCancelled::
	msgbox GoldenrodCity_RadioTower_2F_Text_BuenaComeBack, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_2F_EventScript_BuenaAlreadyPlayed::
	msgbox GoldenrodCity_RadioTower_2F_Text_BuenaAlreadyPlayed, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_2F_EventScript_BuenaNoShow::
	msgbox GoldenrodCity_RadioTower_2F_Text_BuenaShowPromo, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_2F_EventScript_BuenaRocket::
	msgbox RadioTower2FBuenaPasswordIsHelpText, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_2F_EventScript_Teacher::
	lock
	faceplayer
	goto_if_eq JOHTO_VAR_GOLDENROD_CITY_STATE, 6, GoldenrodCity_RadioTower_2F_EventScript_Teacher2
	goto_if_eq JOHTO_VAR_GOLDENROD_CITY_STATE, 7, GoldenrodCity_RadioTower_2F_EventScript_Teacher2
	goto_if_eq JOHTO_VAR_GOLDENROD_CITY_STATE, 8, GoldenrodCity_RadioTower_2F_EventScript_Teacher2
	goto_if_eq JOHTO_VAR_GOLDENROD_CITY_STATE, 9, GoldenrodCity_RadioTower_2F_EventScript_Teacher2
	msgbox GoldenrodCity_RadioTower_2F_Text_Teacher, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_2F_EventScript_Teacher2::
	msgbox GoldenrodCity_RadioTower_2F_Text_TeacherRockets, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_2F_EventScript_Jigglypuff::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_JIGGLYPUFF, CRY_MODE_NORMAL
	msgbox GoldenrodCity_RadioTower_2F_Text_Jigglypuff, MSGBOX_DEFAULT
	waitmoncry
	release
	end

RadioTower2FBuenaPasswordIsHelpText:
	.string "BUENA{SE_M_HEAT_WAVE}Huh{SE_M_SING}Today'{SE_M_GRASSWHISTLE}password?\n"
	.string "HELP{SE_M_SUPERSONIC}o{SE_M_ACID_ARMOR}course!$"

GoldenrodCity_RadioTower_2F_Text_SuperNerd:
	.string "Yo{SE_M_DIVE}ca{SE_M_ATTRACT}liste{SE_M_ATTRACT}t{SE_M_ATTRACT2}th{SE_M_REVERSAL}radio\n"
	.string "anywhere{SE_M_PERISH_SONG}Tun{SE_M_REVERSAL}in!$"

GoldenrodCity_RadioTower_2F_Text_Policeman:
	.string "Restricte{SE_M_WATERFALL}acces{SE_M_GRASSWHISTLE}beyon{SE_M_WATERFALL}this\n"
	.string "point.$"

GoldenrodCity_RadioTower_2F_Text_Teacher:
	.string "Lullabie{SE_M_GRASSWHISTLE}o{SE_M_ATTRACT}th{SE_M_REVERSAL}radi{SE_M_ATTRACT2}ma{SE_M_YAWN}make\n"
	.string "POKéMO{SE_M_PSYBEAM2}sleep.$"

GoldenrodCity_RadioTower_2F_Text_TeacherRockets:
	.string "Wh{SE_M_YAWN}woul{SE_M_WATERFALL}the{SE_M_YAWN}wan{SE_M_SPIT_UP}t{SE_M_ATTRACT2}tak{SE_M_REVERSAL}over\n"
	.string "th{SE_M_REVERSAL}RADI{SE_M_SOLAR_BEAM}TOWER?$"

GoldenrodCity_RadioTower_2F_Text_Jigglypuff:
	.string "JIGGLYPUFF{SE_M_HEAT_WAVE}Jiggly…$"

GoldenrodCity_RadioTower_2F_Text_BlackBelt1:
	.string "Sorry{SE_M_PERISH_SONG}Authorize{SE_M_WATERFALL}personne{SE_M_BATON_PASS}only\n"
	.string "beyon{SE_M_WATERFALL}thi{SE_M_GRASSWHISTLE}point.\p"
	.string "I{SE_M_SPIT_UP}wasn'{SE_M_SPIT_UP}tha{SE_M_SPIT_UP}wa{SE_M_YAWN}before.\p"
	.string "There'{SE_M_GRASSWHISTLE}somethin{SE_M_SANDSTORM}wron{SE_M_SANDSTORM}wit{SE_M_TRI_ATTACK}the\n"
	.string "DIRECTOR…$"

GoldenrodCity_RadioTower_2F_Text_BlackBelt2:
	.string "Fee{SE_M_BATON_PASS}fre{SE_M_REVERSAL}t{SE_M_ATTRACT2}loo{SE_M_ENCORE2}aroun{SE_M_WATERFALL}anywhere.\p"
	.string "Th{SE_M_REVERSAL}DIRECTO{SE_M_MINIMIZE}i{SE_M_GRASSWHISTLE}nic{SE_M_REVERSAL}again{SE_M_SUPERSONIC}just\n"
	.string "a{SE_M_GRASSWHISTLE}h{SE_M_REVERSAL}wa{SE_M_GRASSWHISTLE}before.$"

GoldenrodCity_RadioTower_2F_Text_GruntM4Seen:
	.string "Thre{SE_M_REVERSAL}year{SE_M_GRASSWHISTLE}ago{SE_M_SUPERSONIC}TEA{SE_M_GIGA_DRAIN}ROCKE{SE_M_SWIFT}was\n"
	.string "force{SE_M_WATERFALL}t{SE_M_ATTRACT2}disband.\p"
	.string "Bu{SE_M_SPIT_UP}we'r{SE_M_REVERSAL}makin{SE_M_SANDSTORM}{SE_M_CHARGE}comebac{SE_M_ENCORE2}here!$"

GoldenrodCity_RadioTower_2F_Text_GruntM4Beaten:
	.string "Gwah{SE_M_DRAGON_RAGE}Don'{SE_M_SPIT_UP}ge{SE_M_SPIT_UP}cute!$"

GoldenrodCity_RadioTower_2F_Text_GruntM4After:
	.string "W{SE_M_REVERSAL}won'{SE_M_SPIT_UP}le{SE_M_SPIT_UP}yo{SE_M_DIVE}rui{SE_M_ATTRACT}ou{SE_M_SAND_TOMB}plans\n"
	.string "fo{SE_M_SAND_TOMB}ou{SE_M_SAND_TOMB}comeback!$"

GoldenrodCity_RadioTower_2F_Text_GruntM5Seen:
	.string "We'r{SE_M_REVERSAL}TEA{SE_M_GIGA_DRAIN}ROCKET{SE_M_SUPERSONIC}th{SE_M_REVERSAL}exploiters\n"
	.string "o{SE_M_ACID_ARMOR}POKéMON!\p"
	.string "W{SE_M_REVERSAL}lov{SE_M_REVERSAL}bein{SE_M_SANDSTORM}evil{SE_M_DRAGON_RAGE}Scared?$"

GoldenrodCity_RadioTower_2F_Text_GruntM5Beaten:
	.string "Yo{SE_M_DIVE}thin{SE_M_ENCORE2}you'r{SE_M_REVERSAL}{SE_M_CHARGE}hero?$"

GoldenrodCity_RadioTower_2F_Text_GruntM5After:
	.string "We'r{SE_M_REVERSAL}no{SE_M_SPIT_UP}alway{SE_M_GRASSWHISTLE}evil{SE_M_PERISH_SONG}W{SE_M_REVERSAL}jus{SE_M_SPIT_UP}do\n"
	.string "whateve{SE_M_SAND_TOMB}w{SE_M_REVERSAL}like.$"

GoldenrodCity_RadioTower_2F_Text_GruntM6Seen:
	.string "Hey{SE_M_SUPERSONIC}hey{SE_M_DRAGON_RAGE}Kee{SE_M_MORNING_SUN}ou{SE_M_SPIT_UP}o{SE_M_ACID_ARMOR}ou{SE_M_SAND_TOMB}way!$"

GoldenrodCity_RadioTower_2F_Text_GruntM6Beaten:
	.string "Arggh{SE_M_PERISH_SONG}{SE_M_HEAL_BELL}giv{SE_M_REVERSAL}up.$"

GoldenrodCity_RadioTower_2F_Text_GruntM6After:
	.string "Ou{SE_M_SAND_TOMB}EXECUTIVE{SE_M_SKETCH}ar{SE_M_REVERSAL}tryin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}take\n"
	.string "thi{SE_M_GRASSWHISTLE}plac{SE_M_REVERSAL}over.\p"
	.string "The{SE_M_YAWN}hav{SE_M_REVERSAL}som{SE_M_REVERSAL}bi{SE_M_SANDSTORM}plan{SE_M_PERISH_SONG}{SE_M_HEAL_BELL}wonder\n"
	.string "wha{SE_M_SPIT_UP}tha{SE_M_SPIT_UP}is?$"

GoldenrodCity_RadioTower_2F_Text_GruntF2Seen:
	.string "Hahaha!\p"
	.string "Ho{SE_M_TWISTER}boring{SE_M_PERISH_SONG}I{SE_M_SPIT_UP}wa{SE_M_GRASSWHISTLE}fa{SE_M_SAND_TOMB}to{SE_M_ATTRACT2}easy\n"
	.string "t{SE_M_ATTRACT2}tak{SE_M_REVERSAL}ove{SE_M_SAND_TOMB}thi{SE_M_GRASSWHISTLE}place!\p"
	.string "Com{SE_M_REVERSAL}on{SE_M_SUPERSONIC}kee{SE_M_MORNING_SUN}m{SE_M_REVERSAL}amused!$"

GoldenrodCity_RadioTower_2F_Text_GruntF2Beaten:
	.string "Wh-wh{SE_M_ATTRACT2}ar{SE_M_REVERSAL}you?$"

GoldenrodCity_RadioTower_2F_Text_GruntF2After:
	.string "Yo{SE_M_DIVE}bea{SE_M_SPIT_UP}me{SE_M_SUPERSONIC}an{SE_M_WATERFALL}{SE_M_HEAL_BELL}won'{SE_M_SPIT_UP}forget\n"
	.string "it!$"

GoldenrodCity_RadioTower_2F_Text_BuenaShowPromo:
	.string "BUENA{SE_M_HEAT_WAVE}Tun{SE_M_REVERSAL}i{SE_M_ATTRACT}t{SE_M_ATTRACT2}m{SE_M_YAWN}PASSWORD\n"
	.string "SHOW!\p"
	.string "Liste{SE_M_ATTRACT}t{SE_M_ATTRACT2}fin{SE_M_WATERFALL}ou{SE_M_SPIT_UP}today's\n"
	.string "password!$"

GoldenrodCity_RadioTower_2F_Text_BuenaAskPassword:
	.string "BUENA{SE_M_HEAT_WAVE}H{SE_M_TRI_ATTACK2}there!\p"
	.string "So{SE_M_SUPERSONIC}d{SE_M_ATTRACT2}yo{SE_M_DIVE}kno{SE_M_TWISTER}today's\n"
	.string "password?\p"
	.string "OK{SE_M_DRAGON_RAGE}Whic{SE_M_TRI_ATTACK}on{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}it?$"

GoldenrodCity_RadioTower_2F_Text_BuenaCorrect:
	.string "BUENA{SE_M_HEAT_WAVE}Yo{SE_M_DIVE}go{SE_M_SPIT_UP}it!\p"
	.string "Here{SE_M_SUPERSONIC}tak{SE_M_REVERSAL}thi{SE_M_GRASSWHISTLE}{STR_VAR_1}\n"
	.string "a{SE_M_GRASSWHISTLE}you{SE_M_SAND_TOMB}prize!$"

GoldenrodCity_RadioTower_2F_Text_BuenaWrong:
	.string "BUENA{SE_M_HEAT_WAVE}Bzzt{SE_M_DRAGON_RAGE}To{SE_M_ATTRACT2}bad!\p"
	.string "Tr{SE_M_YAWN}agai{SE_M_ATTRACT}tomorrow!$"

GoldenrodCity_RadioTower_2F_Text_BuenaComeBack:
	.string "BUENA{SE_M_HEAT_WAVE}N{SE_M_ATTRACT2}guess?\n"
	.string "Com{SE_M_REVERSAL}bac{SE_M_ENCORE2}whe{SE_M_ATTRACT}you'r{SE_M_REVERSAL}ready!$"

GoldenrodCity_RadioTower_2F_Text_BuenaAlreadyPlayed:
	.string "BUENA{SE_M_HEAT_WAVE}Yo{SE_M_DIVE}alread{SE_M_YAWN}guessed\n"
	.string "today'{SE_M_GRASSWHISTLE}password!\p"
	.string "Tun{SE_M_REVERSAL}i{SE_M_ATTRACT}agai{SE_M_ATTRACT}tomorrow!$"

GoldenrodCity_RadioTower_2F_Text_BuenaBagFull:
	.string "BUENA{SE_M_HEAT_WAVE}Yo{SE_M_DIVE}go{SE_M_SPIT_UP}i{SE_M_SPIT_UP}right{SE_M_SUPERSONIC}but\n"
	.string "you{SE_M_SAND_TOMB}BA{SE_M_SWAGGER}i{SE_M_GRASSWHISTLE}full!\p"
	.string "Mak{SE_M_REVERSAL}som{SE_M_REVERSAL}roo{SE_M_MILK_DRINK}an{SE_M_WATERFALL}come\n"
	.string "tal{SE_M_ENCORE2}t{SE_M_ATTRACT2}m{SE_M_REVERSAL}again!$"

GoldenrodCity_RadioTower_2F_Text_SalesSign:
	.string "2{SE_M_LEER}SALES$"

GoldenrodCity_RadioTower_2F_Text_OakTalkSign:
	.string "PROF.OAK'{SE_M_SKETCH}POKéMO{SE_M_PSYBEAM2}TALK\p"
	.string "Th{SE_M_REVERSAL}Hottes{SE_M_SPIT_UP}Sho{SE_M_TWISTER}o{SE_M_ATTRACT}th{SE_M_REVERSAL}Air!$"

GoldenrodCity_RadioTower_2F_Text_PokemonRadioSign:
	.string "Anywhere{SE_M_SUPERSONIC}Anytim{SE_M_REVERSAL}POKéMO{SE_M_PSYBEAM2}Radio$"

