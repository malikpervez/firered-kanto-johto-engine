@ Johto (data/maps/Route26_hns/scripts.inc), as built into the FireRed game.

Route26_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route26_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, J_SetTimeEncounters
	.byte 0

Route26_OnTransition:
	callnative SetTimeBasedEncounters
	end

Route26_EventScript_Jake::
	trainerbattle_single TRAINER_JOHTO_JAKE_HNS, Route26_Text_CooltrainermJakeSeen, Route26_Text_CooltrainermJakeBeaten
	msgbox Route26_Text_CooltrainermJakeAfter, MSGBOX_AUTOCLOSE
	end

Route26_EventScript_Gaven::
	trainerbattle_single TRAINER_JOHTO_GAVEN_HNS, Route26_Text_CooltrainermGavenSeen, Route26_Text_CooltrainermGavenBeaten, Route26_EventScript_RegisterGaven
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route26_EventScript_RematchGaven
	msgbox Route26_Text_CooltrainermGavenAfter, MSGBOX_AUTOCLOSE
	end

Route26_EventScript_RegisterGaven::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route26_Text_GavenRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_JOHTO_GAVEN_HNS
	release
	end

Route26_EventScript_RematchGaven::
	trainerbattle_rematch TRAINER_JOHTO_GAVEN_HNS, Route26_Text_GavenRematchIntro, Route26_Text_GavenRematchDefeat
	msgbox Route26_Text_GavenPostRematch, MSGBOX_AUTOCLOSE
	end

Route26_EventScript_Joyce::
	trainerbattle_single TRAINER_JOHTO_JOYCE_HNS, Route26_Text_CooltrainerfJoyceSeen, Route26_Text_CooltrainerfJoyceBeaten
	msgbox Route26_Text_CooltrainerfJoyceAfter, MSGBOX_AUTOCLOSE
	end

Route26_EventScript_Beth::
	trainerbattle_single TRAINER_JOHTO_BETH_HNS, Route26_Text_CooltrainerfBethSeen, Route26_Text_CooltrainerfBethBeaten, Route26_EventScript_RegisterBeth
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route26_EventScript_RematchBeth
	msgbox Route26_Text_CooltrainerfBethAfter, MSGBOX_AUTOCLOSE
	end

Route26_EventScript_RegisterBeth::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route26_Text_BethRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_JOHTO_BETH_HNS
	release
	end

Route26_EventScript_RematchBeth::
	trainerbattle_rematch TRAINER_JOHTO_BETH_HNS, Route26_Text_BethRematchIntro, Route26_Text_BethRematchDefeat
	msgbox Route26_Text_BethPostRematch, MSGBOX_AUTOCLOSE
	end

Route26_EventScript_Richard::
	trainerbattle_single TRAINER_JOHTO_RICHARD_HNS, Route26_Text_PsychicRichardSeen, Route26_Text_PsychicRichardBeaten
	msgbox Route26_Text_PsychicRichardAfter, MSGBOX_AUTOCLOSE
	end

Route26_Text_CooltrainermJakeSeen:
	.string "I'{SE_M_MILK_DRINK}makin{SE_M_SANDSTORM}m{SE_M_YAWN}fina{SE_M_BATON_PASS}preparations\n"
	.string "fo{SE_M_SAND_TOMB}th{SE_M_REVERSAL}POKéMO{SE_M_PSYBEAM2}LEAGUE.$"

Route26_Text_CooltrainermJakeBeaten:
	.string "{SE_M_HEAL_BELL}ble{SE_M_TWISTER}it!$"

Route26_Text_CooltrainermJakeAfter:
	.string "It'{SE_M_GRASSWHISTLE}goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}b{SE_M_REVERSAL}toug{SE_M_TRI_ATTACK}t{SE_M_ATTRACT2}wi{SE_M_ATTRACT}at\n"
	.string "th{SE_M_REVERSAL}LEAGUE.\p"
	.string "{SE_M_HEAL_BELL}nee{SE_M_WATERFALL}t{SE_M_ATTRACT2}d{SE_M_ATTRACT2}som{SE_M_REVERSAL}mor{SE_M_REVERSAL}training.\p"
	.string "{SE_M_HEAL_BELL}hea{SE_M_SAND_TOMB}tha{SE_M_SPIT_UP}th{SE_M_REVERSAL}LEAGUE'{SE_M_GRASSWHISTLE}ELITE\n"
	.string "FOU{SE_M_MINIMIZE}ar{SE_M_REVERSAL}toughe{SE_M_SAND_TOMB}tha{SE_M_ATTRACT}GY{SE_M_GIGA_DRAIN}LEADERS.$"

Route26_Text_CooltrainermGavenSeen:
	.string "B{SE_M_YAWN}experiencin{SE_M_SANDSTORM}toug{SE_M_TRI_ATTACK}battles{SE_M_SUPERSONIC}you\n"
	.string "gai{SE_M_ATTRACT}power.$"

Route26_Text_CooltrainermGavenBeaten:
	.string "Gaah{SE_M_DRAGON_RAGE}Lif{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}eve{SE_M_ATTRACT}tougher!$"

Route26_Text_CooltrainermGavenAfter:
	.string "T{SE_M_ATTRACT2}ge{SE_M_SPIT_UP}t{SE_M_ATTRACT2}POKéMO{SE_M_PSYBEAM2}LEAGUE{SE_M_SUPERSONIC}yo{SE_M_DIVE}have\n"
	.string "t{SE_M_ATTRACT2}ge{SE_M_SPIT_UP}throug{SE_M_TRI_ATTACK}VICTOR{SE_M_MOONLIGHT}ROAD.\p"
	.string "Bu{SE_M_SPIT_UP}VICTOR{SE_M_MOONLIGHT}ROA{SE_M_FAINT_ATTACK}i{SE_M_GRASSWHISTLE}tough.\p"
	.string "Practicall{SE_M_YAWN}nobod{SE_M_YAWN}goe{SE_M_GRASSWHISTLE}there!$"

Route26_Text_GavenRegister:
	.string "T{SE_M_ATTRACT2}ge{SE_M_SPIT_UP}t{SE_M_ATTRACT2}POKéMO{SE_M_PSYBEAM2}LEAGUE{SE_M_SUPERSONIC}yo{SE_M_DIVE}have\n"
	.string "t{SE_M_ATTRACT2}ge{SE_M_SPIT_UP}throug{SE_M_TRI_ATTACK}VICTOR{SE_M_MOONLIGHT}ROAD.\p"
	.string "Bu{SE_M_SPIT_UP}VICTOR{SE_M_MOONLIGHT}ROA{SE_M_FAINT_ATTACK}i{SE_M_GRASSWHISTLE}tough.\p"
	.string "Practicall{SE_M_YAWN}nobod{SE_M_YAWN}goe{SE_M_GRASSWHISTLE}there!$"

Route26_Text_GavenRematchIntro:
	.string "B{SE_M_YAWN}experiencin{SE_M_SANDSTORM}toug{SE_M_TRI_ATTACK}battles{SE_M_SUPERSONIC}you\n"
	.string "gai{SE_M_ATTRACT}power.$"

Route26_Text_GavenRematchDefeat:
	.string "Gaah{SE_M_DRAGON_RAGE}Lif{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}eve{SE_M_ATTRACT}tougher!$"

Route26_Text_GavenPostRematch:
	.string "T{SE_M_ATTRACT2}ge{SE_M_SPIT_UP}t{SE_M_ATTRACT2}POKéMO{SE_M_PSYBEAM2}LEAGUE{SE_M_SUPERSONIC}yo{SE_M_DIVE}have\n"
	.string "t{SE_M_ATTRACT2}ge{SE_M_SPIT_UP}throug{SE_M_TRI_ATTACK}VICTOR{SE_M_MOONLIGHT}ROAD.\p"
	.string "Bu{SE_M_SPIT_UP}VICTOR{SE_M_MOONLIGHT}ROA{SE_M_FAINT_ATTACK}i{SE_M_GRASSWHISTLE}tough.\p"
	.string "Practicall{SE_M_YAWN}nobod{SE_M_YAWN}goe{SE_M_GRASSWHISTLE}there!$"

Route26_Text_CooltrainerfJoyceSeen:
	.string "Sinc{SE_M_REVERSAL}you'v{SE_M_REVERSAL}com{SE_M_REVERSAL}thi{SE_M_GRASSWHISTLE}far,\n"
	.string "yo{SE_M_DIVE}mus{SE_M_SPIT_UP}b{SE_M_REVERSAL}good.\p"
	.string "I'{SE_M_MILK_DRINK}goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}giv{SE_M_REVERSAL}thi{SE_M_GRASSWHISTLE}battle\n"
	.string "everythin{SE_M_SANDSTORM}I'v{SE_M_REVERSAL}got!$"

Route26_Text_CooltrainerfJoyceBeaten:
	.string "No{SE_M_DRAGON_RAGE}{SE_M_HEAL_BELL}don'{SE_M_SPIT_UP}believ{SE_M_REVERSAL}this!$"

Route26_Text_CooltrainerfJoyceAfter:
	.string "I'v{SE_M_REVERSAL}defeate{SE_M_WATERFALL}eigh{SE_M_SPIT_UP}GY{SE_M_GIGA_DRAIN}LEADERS,\n"
	.string "s{SE_M_ATTRACT2}{SE_M_HEAL_BELL}wa{SE_M_GRASSWHISTLE}feelin{SE_M_SANDSTORM}confident.\p"
	.string "I'l{SE_M_BATON_PASS}hav{SE_M_REVERSAL}t{SE_M_ATTRACT2}tr{SE_M_YAWN}harde{SE_M_SAND_TOMB}nex{SE_M_SPIT_UP}time.$"

Route26_Text_CooltrainerfBethSeen:
	.string "{SE_M_HEAL_BELL}los{SE_M_SPIT_UP}t{SE_M_ATTRACT2}{SE_M_CHARGE}traine{SE_M_SAND_TOMB}name{SE_M_WATERFALL}{RIVAL}.\p"
	.string "H{SE_M_REVERSAL}wa{SE_M_GRASSWHISTLE}reall{SE_M_YAWN}strong{SE_M_SUPERSONIC}but…\p"
	.string "I{SE_M_SPIT_UP}wa{SE_M_GRASSWHISTLE}a{SE_M_GRASSWHISTLE}i{SE_M_ACID_ARMOR}h{SE_M_REVERSAL}absolutel{SE_M_YAWN}ha{SE_M_WATERFALL}to\n"
	.string "wi{SE_M_ATTRACT}a{SE_M_SPIT_UP}an{SE_M_YAWN}cost.\p"
	.string "{SE_M_HEAL_BELL}fel{SE_M_SPIT_UP}sorr{SE_M_YAWN}fo{SE_M_SAND_TOMB}hi{SE_M_GRASSWHISTLE}POKéMON.$"

Route26_Text_CooltrainerfBethBeaten:
	.string "POKéMO{SE_M_PSYBEAM2}aren'{SE_M_SPIT_UP}tool{SE_M_GRASSWHISTLE}o{SE_M_ACID_ARMOR}war.$"

Route26_Text_CooltrainerfBethAfter:
	.string "POKéMO{SE_M_PSYBEAM2}ar{SE_M_REVERSAL}in-valuable{SE_M_SUPERSONIC}lifelong\n"
	.string "partners.$"

Route26_Text_BethRegister:
	.string "POKéMO{SE_M_PSYBEAM2}ar{SE_M_REVERSAL}invaluable{SE_M_SUPERSONIC}lifelong\n"
	.string "partners.$"

Route26_Text_BethRematchIntro:
	.string "{SE_M_HEAL_BELL}los{SE_M_SPIT_UP}t{SE_M_ATTRACT2}{SE_M_CHARGE}traine{SE_M_SAND_TOMB}name{SE_M_WATERFALL}{RIVAL}.\p"
	.string "Bu{SE_M_SPIT_UP}{SE_M_HEAL_BELL}won'{SE_M_SPIT_UP}los{SE_M_REVERSAL}t{SE_M_ATTRACT2}you!$"

Route26_Text_BethRematchDefeat:
	.string "POKéMO{SE_M_PSYBEAM2}aren'{SE_M_SPIT_UP}tool{SE_M_GRASSWHISTLE}o{SE_M_ACID_ARMOR}war.$"

Route26_Text_BethPostRematch:
	.string "POKéMO{SE_M_PSYBEAM2}ar{SE_M_REVERSAL}invaluable{SE_M_SUPERSONIC}lifelong\n"
	.string "partners.$"

Route26_Text_PsychicRichardSeen:
	.string "Wow{SE_M_SUPERSONIC}loo{SE_M_ENCORE2}a{SE_M_SPIT_UP}al{SE_M_BATON_PASS}thos{SE_M_REVERSAL}BADGES!\n"
	.string "I'{SE_M_MILK_DRINK}impressed.\p"
	.string "Bu{SE_M_SPIT_UP}you'r{SE_M_REVERSAL}no{SE_M_SPIT_UP}satisfie{SE_M_WATERFALL}b{SE_M_YAWN}just\n"
	.string "collectin{SE_M_SANDSTORM}them{SE_M_SUPERSONIC}right?$"

Route26_Text_PsychicRichardBeaten:
	.string "Goo{SE_M_WATERFALL}battle!$"

Route26_Text_PsychicRichardAfter:
	.string "Peopl{SE_M_REVERSAL}an{SE_M_WATERFALL}POKéMO{SE_M_PSYBEAM2}gro{SE_M_TWISTER}fro{SE_M_MILK_DRINK}their\n"
	.string "experiences.\p"
	.string "Don'{SE_M_SPIT_UP}ge{SE_M_SPIT_UP}laz{SE_M_YAWN}an{SE_M_WATERFALL}complacent.$"

Route26_Text_Sign:
	.string "ROUT{SE_M_SWORDS_DANCE}26\p"
	.string "POKéMO{SE_M_PSYBEAM2}LEAGUE\n"
	.string "RECEPTIO{SE_M_PSYBEAM2}GATE$"

