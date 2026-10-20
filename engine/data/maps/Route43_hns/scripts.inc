@ Johto (data/maps/Route43_hns/scripts.inc), as built into the FireRed game.

Route43_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route43_MapScript_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, J_SetTimeEncounters
	.byte 0

Route43_MapScript_OnTransition::
	call_if_set JOHTO_FLAG_HIDE_ROUTE42_SUICUNE, Route42_MapScript_HideTrigger
	callnative SetTimeBasedEncounters
	end

Route43_EventScript_Ben::
	trainerbattle_single TRAINER_JOHTO_BEN_HNS, Route43_Text_PokemaniacBenSeen, Route43_Text_PokemaniacBenBeaten
	msgbox Route43_Text_PokemaniacBenAfter, MSGBOX_AUTOCLOSE
	end

Route43_EventScript_Brent::
	trainerbattle_single TRAINER_JOHTO_BRENT_HNS, Route43_Text_PokemaniacBrentSeen, Route43_Text_PokemaniacBrentBeaten, Route43_EventScript_RegisterBrent
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route43_EventScript_RematchBrent
	msgbox Route43_Text_PokemaniacBrentAfter, MSGBOX_AUTOCLOSE
	end

Route43_EventScript_RegisterBrent::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route43_Text_BrentRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_JOHTO_BRENT_HNS
	release
	end

Route43_EventScript_RematchBrent::
	trainerbattle_rematch TRAINER_JOHTO_BRENT_HNS, Route43_Text_BrentRematchIntro, Route43_Text_BrentRematchDefeat
	msgbox Route43_Text_BrentPostRematch, MSGBOX_AUTOCLOSE
	end

Route43_EventScript_Ron::
	trainerbattle_single TRAINER_JOHTO_RON_HNS, Route43_Text_PokemaniacRonSeen, Route43_Text_PokemaniacRonBeaten
	msgbox Route43_Text_PokemaniacRonAfter, MSGBOX_AUTOCLOSE
	end

Route43_EventScript_Marvin::
	trainerbattle_single TRAINER_JOHTO_MARVIN_HNS, Route43_Text_FisherMarvinSeen, Route43_Text_FisherMarvinBeaten
	msgbox Route43_Text_FisherMarvinAfter, MSGBOX_AUTOCLOSE
	end

Route43_EventScript_Spencer::
	trainerbattle_single TRAINER_JOHTO_SPENCER_HNS, Route43_Text_CamperSpencerSeen, Route43_Text_CamperSpencerBeaten
	msgbox Route43_Text_CamperSpencerAfter, MSGBOX_AUTOCLOSE
	end

Route43_EventScript_Tiffany::
	trainerbattle_single TRAINER_JOHTO_TIFFANY_HNS, Route43_Text_PicnickerTiffanySeen, Route43_Text_PicnickerTiffanyBeaten, Route43_EventScript_RegisterTiffany
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route43_EventScript_RematchTiffany
	msgbox Route43_Text_PicnickerTiffanyWantsPicnic, MSGBOX_AUTOCLOSE
	end

Route43_EventScript_RegisterTiffany::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route43_Text_TiffanyRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_JOHTO_TIFFANY_HNS
	release
	end

Route43_EventScript_RematchTiffany::
	trainerbattle_rematch TRAINER_JOHTO_TIFFANY_HNS, Route43_Text_TiffanyRematchIntro, Route43_Text_TiffanyRematchDefeat
	msgbox Route43_Text_TiffanyPostRematch, MSGBOX_AUTOCLOSE
	end

Route43_EventScript_Sign1::
	msgbox Route43_Sign2, MSGBOX_SIGN
	end

Route43_EventScript_Sign2::
	msgbox Route43_TrainerTips, MSGBOX_SIGN
	end

Route43_EventScript_Item_Max_Ether::
	finditem ITEM_MAX_ETHER
	end

Route43_Text_PokemaniacBenSeen:
	.string "{SE_M_HEAL_BELL}lov{SE_M_REVERSAL}POKéMON!\p"
	.string "That'{SE_M_GRASSWHISTLE}wh{SE_M_YAWN}{SE_M_HEAL_BELL}started--an{SE_M_WATERFALL}wh{SE_M_YAWN}I'll\n"
	.string "kee{SE_M_MORNING_SUN}o{SE_M_ATTRACT}collectin{SE_M_SANDSTORM}POKéMON!$"

Route43_Text_PokemaniacBenBeaten:
	.string "Ho{SE_M_TWISTER}coul{SE_M_WATERFALL}yo{SE_M_DIVE}d{SE_M_ATTRACT2}thi{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}me?$"

Route43_Text_PokemaniacBenAfter:
	.string "Wha{SE_M_SPIT_UP}els{SE_M_REVERSAL}d{SE_M_ATTRACT2}{SE_M_HEAL_BELL}lik{SE_M_REVERSAL}besides\n"
	.string "POKéMON?\p"
	.string "MAR{SE_M_MOONLIGHT}o{SE_M_ATTRACT}th{SE_M_REVERSAL}radio{SE_M_PERISH_SONG}{SE_M_HEAL_BELL}be{SE_M_SPIT_UP}she's\n"
	.string "cute!$"

Route43_Text_PokemaniacBrentSeen:
	.string "Hey{SE_M_DRAGON_RAGE}D{SE_M_ATTRACT2}yo{SE_M_DIVE}hav{SE_M_REVERSAL}an{SE_M_YAWN}rare\n"
	.string "POKéMON?$"

Route43_Text_PokemaniacBrentBeaten:
	.string "Oh{SE_M_SUPERSONIC}m{SE_M_YAWN}poo{SE_M_SAND_TOMB}POKéMON{SE_M_DRAGON_RAGE}Darlings!$"

Route43_Text_PokemaniacBrentAfter:
	.string "I'{SE_M_WATERFALL}b{SE_M_REVERSAL}happ{SE_M_YAWN}jus{SE_M_SPIT_UP}t{SE_M_ATTRACT2}ow{SE_M_ATTRACT}{SE_M_CHARGE}single\n"
	.string "rar{SE_M_REVERSAL}POKéMON.$"

Route43_Text_BrentRegister:
	.string "I'{SE_M_WATERFALL}b{SE_M_REVERSAL}happ{SE_M_YAWN}jus{SE_M_SPIT_UP}t{SE_M_ATTRACT2}ow{SE_M_ATTRACT}{SE_M_CHARGE}single\n"
	.string "rar{SE_M_REVERSAL}POKéMON.$"

Route43_Text_BrentRematchIntro:
	.string "Hey{SE_M_DRAGON_RAGE}D{SE_M_ATTRACT2}yo{SE_M_DIVE}hav{SE_M_REVERSAL}an{SE_M_YAWN}rare\n"
	.string "POKéMON?$"

Route43_Text_BrentRematchDefeat:
	.string "Oh{SE_M_SUPERSONIC}m{SE_M_YAWN}poo{SE_M_SAND_TOMB}POKéMON{SE_M_DRAGON_RAGE}Darlings!$"

Route43_Text_BrentPostRematch:
	.string "I'{SE_M_WATERFALL}b{SE_M_REVERSAL}happ{SE_M_YAWN}jus{SE_M_SPIT_UP}t{SE_M_ATTRACT2}ow{SE_M_ATTRACT}{SE_M_CHARGE}single\n"
	.string "rar{SE_M_REVERSAL}POKéMON.$"

Route43_Text_PokemaniacRonSeen:
	.string "Woul{SE_M_WATERFALL}yo{SE_M_DIVE}ge{SE_M_SPIT_UP}this?\p"
	.string "Som{SE_M_REVERSAL}{RIVAL} gu{SE_M_YAWN}mad{SE_M_REVERSAL}fu{SE_M_ATTRACT}o{SE_M_ACID_ARMOR}my\n"
	.string "POKéMON!\p"
	.string "Dar{SE_M_ATTRACT}it{SE_M_DRAGON_RAGE}M{SE_M_YAWN}POKéMON'{SE_M_GRASSWHISTLE}great!$"

Route43_Text_PokemaniacRonBeaten:
	.string "M{SE_M_YAWN}NIDOKIN{SE_M_SWAGGER}di{SE_M_WATERFALL}prett{SE_M_YAWN}righ{SE_M_SPIT_UP}on!$"

Route43_Text_PokemaniacRonAfter:
	.string "It'{SE_M_GRASSWHISTLE}oka{SE_M_YAWN}fo{SE_M_SAND_TOMB}peopl{SE_M_REVERSAL}t{SE_M_ATTRACT2}like\n"
	.string "differen{SE_M_SPIT_UP}type{SE_M_GRASSWHISTLE}o{SE_M_ACID_ARMOR}POKéMON.\p"
	.string "POKéMO{SE_M_PSYBEAM2}isn'{SE_M_SPIT_UP}jus{SE_M_SPIT_UP}abou{SE_M_SPIT_UP}havin{SE_M_SANDSTORM}the\n"
	.string "mos{SE_M_SPIT_UP}powerfu{SE_M_BATON_PASS}one.$"

Route43_Text_FisherMarvinSeen:
	.string "I'{SE_M_MILK_DRINK}i{SE_M_ATTRACT}{SE_M_CHARGE}slump.\p"
	.string "Mayb{SE_M_REVERSAL}it'{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}gea{SE_M_SAND_TOMB}I'{SE_M_MILK_DRINK}using.\p"
	.string "Let'{SE_M_GRASSWHISTLE}battl{SE_M_REVERSAL}fo{SE_M_SAND_TOMB}{SE_M_CHARGE}chang{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}pace!$"

Route43_Text_FisherMarvinBeaten:
	.string "{SE_M_HEAL_BELL}lost{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}{SE_M_HEAL_BELL}fee{SE_M_BATON_PASS}bette{SE_M_SAND_TOMB}anyway.$"

Route43_Text_FisherMarvinAfter:
	.string "KURT'{SE_M_GRASSWHISTLE}LUR{SE_M_SWORDS_DANCE}BAL{SE_M_BRICK_BREAK}i{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}bes{SE_M_SPIT_UP}for\n"
	.string "catchin{SE_M_SANDSTORM}hooke{SE_M_WATERFALL}POKéMON.\p"
	.string "It'{SE_M_GRASSWHISTLE}muc{SE_M_TRI_ATTACK}mor{SE_M_REVERSAL}effectiv{SE_M_REVERSAL}tha{SE_M_ATTRACT}a\n"
	.string "ULTR{SE_M_BONEMERANG}BALL.$"

Route43_Text_CamperSpencerSeen:
	.string "{SE_M_HEAL_BELL}ca{SE_M_ATTRACT}d{SE_M_ATTRACT2}s{SE_M_ATTRACT2}muc{SE_M_TRI_ATTACK}wit{SE_M_TRI_ATTACK}my\n"
	.string "POKéMON--it'{SE_M_GRASSWHISTLE}super-fun!$"

Route43_Text_CamperSpencerBeaten:
	.string "Losin{SE_M_SANDSTORM}isn'{SE_M_SPIT_UP}fu{SE_M_ATTRACT}a{SE_M_SPIT_UP}all…$"

Route43_Text_CamperSpencerAfter:
	.string "Wha{SE_M_SPIT_UP}i{SE_M_GRASSWHISTLE}goin{SE_M_SANDSTORM}o{SE_M_ATTRACT}a{SE_M_SPIT_UP}LAK{SE_M_SWORDS_DANCE}O{SE_M_LEER}RAGE?\p"
	.string "W{SE_M_REVERSAL}wer{SE_M_REVERSAL}plannin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}cam{SE_M_MORNING_SUN}there.$"

Route43_Text_PicnickerTiffanySeen:
	.string "Ar{SE_M_REVERSAL}yo{SE_M_DIVE}goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}LAK{SE_M_SWORDS_DANCE}O{SE_M_LEER}RAG{SE_M_SWORDS_DANCE}too?\p"
	.string "Let'{SE_M_GRASSWHISTLE}pla{SE_M_YAWN}fo{SE_M_SAND_TOMB}{SE_M_CHARGE}littl{SE_M_REVERSAL}while!$"

Route43_Text_PicnickerTiffanyBeaten:
	.string "{SE_M_HEAL_BELL}playe{SE_M_WATERFALL}to{SE_M_ATTRACT2}much!$"

Route43_Text_PicnickerTiffanyWantsPicnic:
	.string "I'{SE_M_MILK_DRINK}havin{SE_M_SANDSTORM}{SE_M_CHARGE}picni{SE_M_HYPER_BEAM}wit{SE_M_TRI_ATTACK}POKéMON.\p"
	.string "Won'{SE_M_SPIT_UP}yo{SE_M_DIVE}joi{SE_M_ATTRACT}us?$"

Route43_Text_TiffanyRegister:
	.string "I'{SE_M_MILK_DRINK}havin{SE_M_SANDSTORM}{SE_M_CHARGE}picni{SE_M_HYPER_BEAM}wit{SE_M_TRI_ATTACK}POKéMON.\p"
	.string "Won'{SE_M_SPIT_UP}yo{SE_M_DIVE}joi{SE_M_ATTRACT}us?$"

Route43_Text_TiffanyRematchIntro:
	.string "Ar{SE_M_REVERSAL}yo{SE_M_DIVE}goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}LAK{SE_M_SWORDS_DANCE}O{SE_M_LEER}RAG{SE_M_SWORDS_DANCE}too?\p"
	.string "Let'{SE_M_GRASSWHISTLE}pla{SE_M_YAWN}fo{SE_M_SAND_TOMB}{SE_M_CHARGE}littl{SE_M_REVERSAL}while!$"

Route43_Text_TiffanyRematchDefeat:
	.string "{SE_M_HEAL_BELL}playe{SE_M_WATERFALL}to{SE_M_ATTRACT2}much!$"

Route43_Text_TiffanyPostRematch:
	.string "I'{SE_M_MILK_DRINK}havin{SE_M_SANDSTORM}{SE_M_CHARGE}picni{SE_M_HYPER_BEAM}wit{SE_M_TRI_ATTACK}POKéMON.\p"
	.string "Won'{SE_M_SPIT_UP}yo{SE_M_DIVE}joi{SE_M_ATTRACT}us?$"

Route43_Sign1:
	.string "ROUT{SE_M_SWORDS_DANCE}43\p"
	.string "LAK{SE_M_SWORDS_DANCE}O{SE_M_LEER}RAG{SE_M_SWORDS_DANCE}{SE_M_PAY_DAY}MAHOGAN{SE_M_MOONLIGHT}TOWN$"

Route43_Sign2:
	.string "ROUT{SE_M_SWORDS_DANCE}43\p"
	.string "LAK{SE_M_SWORDS_DANCE}O{SE_M_LEER}RAG{SE_M_SWORDS_DANCE}{SE_M_PAY_DAY}MAHOGAN{SE_M_MOONLIGHT}TOWN$"

Route43_TrainerTips:
	.string "TRAINE{SE_M_MINIMIZE}TIPS\p"
	.string "Al{SE_M_BATON_PASS}POKéMO{SE_M_PSYBEAM2}hav{SE_M_REVERSAL}pro{SE_M_GRASSWHISTLE}an{SE_M_WATERFALL}cons\n"
	.string "dependin{SE_M_SANDSTORM}o{SE_M_ATTRACT}thei{SE_M_SAND_TOMB}types.\p"
	.string "I{SE_M_ACID_ARMOR}thei{SE_M_SAND_TOMB}type{SE_M_GRASSWHISTLE}differ{SE_M_SUPERSONIC}{SE_M_CHARGE}higher-\n"
	.string "leve{SE_M_BATON_PASS}POKéMO{SE_M_PSYBEAM2}ma{SE_M_YAWN}los{SE_M_REVERSAL}i{SE_M_ATTRACT}battle.\p"
	.string "Lear{SE_M_ATTRACT}whic{SE_M_TRI_ATTACK}type{SE_M_GRASSWHISTLE}ar{SE_M_REVERSAL}stron{SE_M_SANDSTORM}and\n"
	.string "wea{SE_M_ENCORE2}agains{SE_M_SPIT_UP}you{SE_M_SAND_TOMB}POKéMON'{SE_M_GRASSWHISTLE}type.$"

