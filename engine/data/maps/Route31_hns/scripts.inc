@ Johto (data/maps/Route31_hns/scripts.inc), as built into the FireRed game.

Route31_hns_MapScripts::
	map_script 3, Route31_OnTransition
	map_script 5, J_SetTimeEncounters
	.byte 0

Route31_OnTransition:
	callnative SetTimeBasedEncounters
	end

Route31_EventScript_Bugcatcher_Wade::
	trainerbattle_single 1192, Route31_Text_BugCatcherWade1_Seen, Route31_Text_BugCatcherWade1_Beaten, Route31_EventScript_RegisterWade
	goto_if_set 8938, Route31_EventScript_WadeGiveItem
	specialvar 32781, ShouldTryRematchBattle
	goto_if_eq 32781, TRUE, Route31_EventScript_RematchWade
	msgbox Route31_Text_BugCatcherWade1_After, MSGBOX_AUTOCLOSE
	end

Route31_EventScript_RegisterWade::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route31_Text_WadeRegister, MSGBOX_DEFAULT
	register_matchcall 1192
	release
	end

Route31_EventScript_RematchWade::
	trainerbattle_rematch 1192, Route31_Text_WadeRematchIntro, Route31_Text_WadeRematchDefeat
	msgbox Route31_Text_WadePostRematch, MSGBOX_AUTOCLOSE
	end

Route31_EventScript_WadeGiveItem::
	msgbox Route31_Text_WadeHasItem, MSGBOX_DEFAULT
	giveitem 20615
	goto_if_eq 32781, FALSE, Route31_EventScript_WadeNoRoom
	clearflag 8938
	msgbox Route31_Text_WadeGaveItem, MSGBOX_AUTOCLOSE
	end

Route31_EventScript_WadeNoRoom::
	msgbox Route31_Text_WadeNoRoom, MSGBOX_AUTOCLOSE
	end

Route31_EventScript_Youngster::
	lock
	faceplayer
	msgbox Route31_Text_CooltrainerM, MSGBOX_DEFAULT
	closemessage
	release
	end

Route31_EventScript_SleepyMan::
	lock
	faceplayer
	goto_if_eq 20574, 1, Route31_EventScript_SleepyMan_AskForKenya
	msgbox Route31_Text_SleepyMan, MSGBOX_DEFAULT
	closemessage
	release
	end

Route31_EventScript_SleepyMan_AskForKenya::
	msgbox Route31_Text_SleepyManGotMail, MSGBOX_YESNO
	goto_if_eq 32781, TRUE, Route31_EventScript_SleepyMan_GiveKenya
	msgbox Route31_Text_SleepyManFail, MSGBOX_DEFAULT
	closemessage
	release
	end

Route31_EventScript_SleepyMan_GiveKenya::
	removenamedmon 1
	goto_if_eq 32781, 2, Route31_EventScript_SleepyMan_Fail
	msgbox Route31_Text_HandOverMailMon, MSGBOX_DEFAULT
	delay 55
	callnative UpdateFollowingPokemon
	msgbox Route31_Text_ReadingMail, MSGBOX_DEFAULT
	giveitem 625
	msgbox Route31_Text_DescribeRest, MSGBOX_DEFAULT
	closemessage
	setvar 20574, 2
	release
	end

Route31_EventScript_SleepyMan_Fail::
	msgbox Route31_Text_SleepyManFail, MSGBOX_DEFAULT
	release
	end

Route31_EventScript_Boy::
	lock
	faceplayer
	msgbox Route31_Text_Youngster, MSGBOX_DEFAULT
	closemessage
	release
	end

Route31_EventScript_DarkCaveSign::
	lock
	msgbox Route31_Text_DarkCaveSign, MSGBOX_SIGN
	closemessage
	release
	end

Route31_EventScript_Sign::
	lock
	msgbox Route31_Text_Sign, MSGBOX_SIGN
	closemessage
	release
	end

Route31_EventScript_ItemPokeBall::
	finditem ITEM_POKE_BALL
	end

Route31_EventScript_ItemAntidote::
	finditem ITEM_ANTIDOTE
	end

Route31_Text_CooltrainerM:
	.string "DAR{SE_M_SNORE}CAVE…\p"
	.string "I{SE_M_ACID_ARMOR}POKéMO{SE_M_PSYBEAM2}coul{SE_M_WATERFALL}ligh{SE_M_SPIT_UP}i{SE_M_SPIT_UP}up,\n"
	.string "I'{SE_M_WATERFALL}explor{SE_M_REVERSAL}it.$"

Route31_Text_BugCatcherWade1_Seen:
	.string "{SE_M_HEAL_BELL}caugh{SE_M_SPIT_UP}{SE_M_CHARGE}bunc{SE_M_TRI_ATTACK}o{SE_M_ACID_ARMOR}POKéMON.\n"
	.string "Le{SE_M_SPIT_UP}m{SE_M_REVERSAL}battl{SE_M_REVERSAL}wit{SE_M_TRI_ATTACK}you!$"

Route31_Text_BugCatcherWade1_Beaten:
	.string "Awwwww…$"

Route31_Text_BugCatcherWade1_After:
	.string "Yo{SE_M_DIVE}ca{SE_M_ATTRACT}catc{SE_M_TRI_ATTACK}POKéMO{SE_M_PSYBEAM2}eve{SE_M_ATTRACT}if\n"
	.string "yo{SE_M_DIVE}hav{SE_M_REVERSAL}si{SE_M_SWEET_SCENT}wit{SE_M_TRI_ATTACK}you.\p"
	.string "I{SE_M_ACID_ARMOR}yo{SE_M_DIVE}catc{SE_M_TRI_ATTACK}one{SE_M_SUPERSONIC}it'l{SE_M_BATON_PASS}g{SE_M_ATTRACT2}to\n"
	.string "you{SE_M_SAND_TOMB}BO{SE_M_LOCK_ON}automatically.$"

Route31_Text_SleepyMan:
	.string "{SE_M_DIZZY_PUNCH}Hnuurg{SE_M_DIZZY_PUNCH}Huh?\p"
	.string "{SE_M_HEAL_BELL}walke{SE_M_WATERFALL}to{SE_M_ATTRACT2}fa{SE_M_SAND_TOMB}toda{SE_M_YAWN}looking\n"
	.string "fo{SE_M_SAND_TOMB}POKéMON.\p"
	.string "M{SE_M_YAWN}fee{SE_M_SPIT_UP}hur{SE_M_SPIT_UP}an{SE_M_WATERFALL}I'{SE_M_MILK_DRINK}sleepy…\p"
	.string "I{SE_M_ACID_ARMOR}{SE_M_HEAL_BELL}wer{SE_M_REVERSAL}{SE_M_CHARGE}wil{SE_M_WATERFALL}POKéMON{SE_M_SUPERSONIC}I'd\n"
	.string "b{SE_M_REVERSAL}eas{SE_M_YAWN}t{SE_M_ATTRACT2}catch…\p"
	.string "…Zzzz…$"

Route31_Text_SleepyManGotMail:
	.string "…Zzzz{SE_M_DIZZY_PUNCH}Huh?\p"
	.string "What'{SE_M_GRASSWHISTLE}that{SE_M_SING}Yo{SE_M_DIVE}hav{SE_M_REVERSAL}MAIL\n"
	.string "fo{SE_M_SAND_TOMB}me?$"

Route31_Text_SleepyManFail:
	.string "…Zzzz…$"

Route31_Text_HandOverMailMon:
	.string "{PLAYER} hande{SE_M_WATERFALL}ove{SE_M_SAND_TOMB}the\n"
	.string "POKéMO{SE_M_PSYBEAM2}holdin{SE_M_SANDSTORM}th{SE_M_REVERSAL}MAIL.$"

Route31_Text_ReadingMail:
	.string "Let'{SE_M_GRASSWHISTLE}see…\p"
	.string "Thank{SE_M_GRASSWHISTLE}fo{SE_M_SAND_TOMB}bringin{SE_M_SANDSTORM}thi{SE_M_GRASSWHISTLE}to\n"
	.string "me.\p"
	.string "M{SE_M_YAWN}friend'{SE_M_GRASSWHISTLE}{SE_M_CHARGE}goo{SE_M_WATERFALL}guy{SE_M_SUPERSONIC}and\n"
	.string "you'r{SE_M_REVERSAL}swel{SE_M_BATON_PASS}too!\p"
	.string "I'{SE_M_WATERFALL}lik{SE_M_REVERSAL}t{SE_M_ATTRACT2}d{SE_M_ATTRACT2}somethin{SE_M_SANDSTORM}good\n"
	.string "i{SE_M_ATTRACT}retur{SE_M_ATTRACT}too!\p"
	.string "{SE_M_HEAL_BELL}know{SE_M_DRAGON_RAGE}{SE_M_HEAL_BELL}wan{SE_M_SPIT_UP}yo{SE_M_DIVE}t{SE_M_ATTRACT2}have\n"
	.string "this!$"

Route31_Text_DescribeRest:
	.string "...Zzz...\p"
	.string "...Umm..{SE_M_PERISH_SONG}Rest!\p"
	.string "Th{SE_M_REVERSAL}phras{SE_M_REVERSAL}'recove{SE_M_SAND_TOMB}fast{SE_M_ABSORB}became\n"
	.string "shortene{SE_M_WATERFALL}t{SE_M_ATTRACT2}'Rest,{SE_M_ABSORB}yo{SE_M_DIVE}see?\p"
	.string "Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}mov{SE_M_REVERSAL}t{SE_M_ATTRACT2}slee{SE_M_MORNING_SUN}an{SE_M_WATERFALL}recover\n"
	.string "som{SE_M_REVERSAL}HP.$"

Route31_Text_WrongMail:
	.string "Thi{SE_M_GRASSWHISTLE}MAI{SE_M_BRICK_BREAK}isn'{SE_M_SPIT_UP}fo{SE_M_SAND_TOMB}me.$"

Route31_Text_MissingMail:
	.string "Wh{SE_M_YAWN}i{SE_M_GRASSWHISTLE}thi{SE_M_GRASSWHISTLE}POKéMO{SE_M_PSYBEAM2}s{SE_M_ATTRACT2}special?\p"
	.string "I{SE_M_SPIT_UP}doesn'{SE_M_SPIT_UP}hav{SE_M_REVERSAL}an{SE_M_YAWN}MAIL.$"

Route31_Text_DeclinedToHandOverMail:
	.string "What{SE_M_SING}Yo{SE_M_DIVE}don'{SE_M_SPIT_UP}want\n"
	.string "anything?$"

Route31_Text_CantTakeLastMon:
	.string "I{SE_M_ACID_ARMOR}{SE_M_HEAL_BELL}tak{SE_M_REVERSAL}tha{SE_M_SPIT_UP}POKéMO{SE_M_PSYBEAM2}from\n"
	.string "you,\p"
	.string "wha{SE_M_SPIT_UP}ar{SE_M_REVERSAL}yo{SE_M_DIVE}goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}us{SE_M_REVERSAL}in\n"
	.string "battle?$"

Route31_Text_Youngster:
	.string "{SE_M_HEAL_BELL}foun{SE_M_WATERFALL}{SE_M_CHARGE}goo{SE_M_WATERFALL}POKéMO{SE_M_PSYBEAM2}i{SE_M_ATTRACT}DARK\n"
	.string "CAVE.\p"
	.string "I'{SE_M_MILK_DRINK}goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}rais{SE_M_REVERSAL}i{SE_M_SPIT_UP}t{SE_M_ATTRACT2}take\n"
	.string "o{SE_M_ATTRACT}FALKNER.\p"
	.string "He'{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}leade{SE_M_SAND_TOMB}o{SE_M_ACID_ARMOR}VIOLET\n"
	.string "CITY'{SE_M_GRASSWHISTLE}GYM.$"

Route31_Text_Sign:
	.string "ROUT{SE_M_SWORDS_DANCE}31\p"
	.string "VIOLE{SE_M_SWIFT}CIT{SE_M_MOONLIGHT}{SE_M_PAY_DAY}CHERRYGROV{SE_M_SWORDS_DANCE}CITY$"

Route31_Text_WadeRegister:
	.string "You'r{SE_M_REVERSAL}awesome{SE_M_DRAGON_RAGE}{SE_M_HEAL_BELL}lik{SE_M_REVERSAL}you!\p"
	.string "{SE_M_HEAL_BELL}loo{SE_M_ENCORE2}fo{SE_M_SAND_TOMB}POKéMO{SE_M_PSYBEAM2}her{SE_M_REVERSAL}every\n"
	.string "day.\p"
	.string "Whe{SE_M_ATTRACT}I'{SE_M_MILK_DRINK}i{SE_M_ATTRACT}th{SE_M_REVERSAL}grass{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}find\n"
	.string "al{SE_M_BATON_PASS}kind{SE_M_GRASSWHISTLE}o{SE_M_ACID_ARMOR}BERRIES.\p"
	.string "I{SE_M_ACID_ARMOR}you'{SE_M_WATERFALL}like{SE_M_SUPERSONIC}I'l{SE_M_BATON_PASS}share\n"
	.string "some.$"

Route31_Text_WadeRematchIntro:
	.string "{SE_M_HEAL_BELL}wa{SE_M_GRASSWHISTLE}waitin{SE_M_SANDSTORM}fo{SE_M_SAND_TOMB}you.\n"
	.string "Let'{SE_M_GRASSWHISTLE}battle!$"

Route31_Text_WadeRematchDefeat:
	.string "Awwwww…$"

Route31_Text_WadePostRematch:
	.string "You'l{SE_M_BATON_PASS}hea{SE_M_SAND_TOMB}fro{SE_M_MILK_DRINK}m{SE_M_REVERSAL}a{SE_M_GRASSWHISTLE}soon\n"
	.string "a{SE_M_GRASSWHISTLE}{SE_M_HEAL_BELL}fin{SE_M_WATERFALL}anythin{SE_M_SANDSTORM}tha{SE_M_SPIT_UP}you\l"
	.string "migh{SE_M_SPIT_UP}like.$"

Route31_Text_WadeHasItem:
	.string "Hey{SE_M_DRAGON_RAGE}I'v{SE_M_REVERSAL}bee{SE_M_ATTRACT}lookin{SE_M_SANDSTORM}for\n"
	.string "you!\p"
	.string "{SE_M_HEAL_BELL}foun{SE_M_WATERFALL}somethin{SE_M_SANDSTORM}whil{SE_M_REVERSAL}I\n"
	.string "wa{SE_M_GRASSWHISTLE}i{SE_M_ATTRACT}th{SE_M_REVERSAL}grass.\p"
	.string "Here{SE_M_SUPERSONIC}yo{SE_M_DIVE}ca{SE_M_ATTRACT}hav{SE_M_REVERSAL}it!$"

Route31_Text_WadeGaveItem:
	.string "I'l{SE_M_BATON_PASS}le{SE_M_SPIT_UP}yo{SE_M_DIVE}kno{SE_M_TWISTER}i{SE_M_ACID_ARMOR}{SE_M_HEAL_BELL}find\n"
	.string "anythin{SE_M_SANDSTORM}else!$"

Route31_Text_WadeNoRoom:
	.string "Hmm{SE_M_SUPERSONIC}look{SE_M_GRASSWHISTLE}lik{SE_M_REVERSAL}you{SE_M_SAND_TOMB}BAG\n"
	.string "i{SE_M_GRASSWHISTLE}full.\p"
	.string "Com{SE_M_REVERSAL}bac{SE_M_ENCORE2}whe{SE_M_ATTRACT}yo{SE_M_DIVE}have\n"
	.string "room!$"

Route31_Text_DarkCaveSign:
	.string "DAR{SE_M_SNORE}CAVE$"

