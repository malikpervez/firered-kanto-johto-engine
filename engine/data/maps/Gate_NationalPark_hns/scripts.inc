@ Johto (data/maps/Gate_NationalPark_hns/scripts.inc), as built into the FireRed game.

Gate_NationalPark_hns_MapScripts::
	.byte 0

Gate_NationalPark_EventScript_Attendant::
	lockall
	faceplayer
	goto_if_set JOHTO_FLAG_DAILY_BUG_CONTEST_COMPLETED, Gate_NationalPark_EventScript_AttendantAlreadyPlayed
	msgbox Route35NationalParkGate_Text_OfficerAskToParticipate, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, Gate_NationalPark_EventScript_AttendantStart
	msgbox Route35NationalParkGate_Text_TakePartInFuture, MSGBOX_DEFAULT
	releaseall
	end

Gate_NationalPark_EventScript_AttendantStart::
	playbgm ((558 + 1) + 0x3D), FALSE
	msgbox Route35NationalParkGate_Text_OfficerAskToUseFirstMon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, Gate_NationalPark_EventScript_AttendantCancel
	getpartysize
	call_if_eq VAR_RESULT, 1, Gate_NationalPark_EventScript_OnlyOneMon
	msgbox Route35NationalParkGate_Text_OfficerHoldYourMon, MSGBOX_DEFAULT
	closemessage
	special SavePlayerParty
	remove5mons
	goto_if_eq VAR_RESULT, MON_CANT_GIVE, Gate_NationalPark_EventScript_AttendantFaint
	playfanfare MUS_OBTAIN_ITEM
	message Route35NationalParkGate_Text_MonLeftWithHelper
	waitfanfare
	closemessage
	msgbox Route35NationalParkGate_Text_OfficerGiveSportBalls, MSGBOX_DEFAULT
	closemessage
	giveitem ITEM_SPORT_BALL, 30
	closemessage
	msgbox Route35NationalParkGate_Text_OfficerExplainRules, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_FACING, DIR_WEST, Gate_NationalPark_EventScript_AttendantEnterTop
	call_if_eq VAR_FACING, DIR_NORTH, Gate_NationalPark_EventScript_AttendantEnterBot
	playse SE_EXIT
	clearflag JOHTO_FLAG_HIDE_BUG_CONTEST_ATTENDANT_SIDE
	special EnterBugContestMode
	setflag JOHTO_FLAG_DISABLE_EXP_GAIN
	setvar JOHTO_VAR_BUG_CONTEST_STATE, 1
	warp MAP_NATIONAL_PARK_BUG_CONTEST_HNS, 1
	waitstate
	end

Gate_NationalPark_EventScript_OnlyOneMon::
	special SavePlayerParty
	msgbox Route35NationalParkGate_Text_OfficerGiveSportBalls, MSGBOX_DEFAULT
	closemessage
	giveitem ITEM_SPORT_BALL, 30
	closemessage
	msgbox Route35NationalParkGate_Text_OfficerExplainRules, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_FACING, DIR_WEST, Gate_NationalPark_EventScript_AttendantEnterTop
	call_if_eq VAR_FACING, DIR_NORTH, Gate_NationalPark_EventScript_AttendantEnterBot
	playse SE_EXIT
	clearflag JOHTO_FLAG_HIDE_BUG_CONTEST_ATTENDANT_SIDE
	special EnterBugContestMode
	setflag JOHTO_FLAG_DISABLE_EXP_GAIN
	setvar JOHTO_VAR_BUG_CONTEST_STATE, 1
	warp MAP_NATIONAL_PARK_BUG_CONTEST_HNS, 1
	waitstate
	end

Gate_NationalPark_EventScript_AttendantEnterTop::
	applymovement OBJ_EVENT_ID_PLAYER, Gate_NationalPark_Movement_Player_EnterParkTop
	waitmovement 0
	return

Gate_NationalPark_EventScript_AttendantEnterBot::
	applymovement OBJ_EVENT_ID_PLAYER, Gate_NationalPark_Movement_Player_EnterParkBot
	waitmovement 0
	return

Gate_NationalPark_EventScript_AttendantFaint::
	msgbox Route35NationalParkGate_Text_FirstMonCantBattle, MSGBOX_DEFAULT
	closemessage
	fadedefaultbgm
	release
	end

Gate_NationalPark_EventScript_AttendantCancel::
	msgbox Route35NationalParkGate_Text_TakePartInFuture, MSGBOX_DEFAULT
	closemessage
	fadedefaultbgm
	release
	end

Gate_NationalPark_EventScript_AttendantAlreadyPlayed::
	msgbox Route35NationalParkGate_Text_ContestIsOver, MSGBOX_DEFAULT
	closemessage
	release
	end

Gate_NationalPark_Movement_Player_EnterParkTop:
	walk_down
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	step_end

Gate_NationalPark_Movement_Player_EnterParkBot:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	step_end

Gate_NationalPark_EventScript_BAttendant::
	lockall
	faceplayer
	goto_if_set JOHTO_FLAG_DAILY_BUG_CONTEST_COMPLETED, Gate_NationalPark_EventScript_AttendantAlreadyPlayed
	msgbox Route35NationalParkGate_Text_OfficerAskToParticipate, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, Gate_NationalPark_EventScript_BAttendantStart
	msgbox Route35NationalParkGate_Text_TakePartInFuture, MSGBOX_DEFAULT
	releaseall
	end

Gate_NationalPark_EventScript_BAttendantStart::
	playbgm ((558 + 1) + 0x3D), FALSE
	msgbox Route35NationalParkGate_Text_OfficerAskToUseFirstMon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, Gate_NationalPark_EventScript_AttendantCancel
	getpartysize
	call_if_eq VAR_RESULT, 1, Gate_NationalPark_EventScript_OnlyOneMonB
	msgbox Route35NationalParkGate_Text_OfficerHoldYourMon, MSGBOX_DEFAULT
	closemessage
	special SavePlayerParty
	remove5mons
	goto_if_eq VAR_RESULT, MON_CANT_GIVE, Gate_NationalPark_EventScript_AttendantFaint
	playfanfare MUS_OBTAIN_ITEM
	message Route35NationalParkGate_Text_MonLeftWithHelper
	waitfanfare
	closemessage
	msgbox Route35NationalParkGate_Text_OfficerGiveSportBalls, MSGBOX_DEFAULT
	closemessage
	giveitem ITEM_SPORT_BALL, 30
	closemessage
	msgbox Route35NationalParkGate_Text_OfficerExplainRules, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_FACING, DIR_EAST, Gate_NationalPark_EventScript_AttendantBEnterTop
	call_if_eq VAR_FACING, DIR_NORTH, Gate_NationalPark_EventScript_AttendantBEnterBot
	playse SE_EXIT
	special EnterBugContestMode
	setflag JOHTO_FLAG_DISABLE_EXP_GAIN
	setflag JOHTO_FLAG_HIDE_BUG_CONTEST_ATTENDANT_SIDE
	setvar JOHTO_VAR_BUG_CONTEST_STATE, 5
	warp MAP_NATIONAL_PARK_BUG_CONTEST_HNS, 40, 19
	waitstate
	end

Gate_NationalPark_EventScript_OnlyOneMonB::
	special SavePlayerParty
	msgbox Route35NationalParkGate_Text_OfficerGiveSportBalls, MSGBOX_DEFAULT
	closemessage
	giveitem ITEM_SPORT_BALL, 30
	closemessage
	msgbox Route35NationalParkGate_Text_OfficerExplainRules, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_FACING, DIR_EAST, Gate_NationalPark_EventScript_AttendantBEnterTop
	call_if_eq VAR_FACING, DIR_NORTH, Gate_NationalPark_EventScript_AttendantBEnterBot
	playse SE_EXIT
	special EnterBugContestMode
	setflag JOHTO_FLAG_DISABLE_EXP_GAIN
	setflag JOHTO_FLAG_HIDE_BUG_CONTEST_ATTENDANT_SIDE
	setvar JOHTO_VAR_BUG_CONTEST_STATE, 5
	warp MAP_NATIONAL_PARK_BUG_CONTEST_HNS, 40, 19
	waitstate
	end

Gate_NationalPark_EventScript_AttendantBEnterTop::
	applymovement OBJ_EVENT_ID_PLAYER, Gate_NationalPark_Movement_Player_EnterParkTopB
	waitmovement 0
	return

Gate_NationalPark_EventScript_AttendantBEnterBot::
	applymovement OBJ_EVENT_ID_PLAYER, Gate_NationalPark_Movement_Player_EnterParkBotB
	waitmovement 0
	return

Gate_NationalPark_Movement_Player_EnterParkTopB:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_in_place_left
	step_end

Gate_NationalPark_Movement_Player_EnterParkBotB:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_in_place_left
	step_end

Route35NationalParkGate_Text_OfficerAskToParticipate:
	.string "Hell{SE_M_ATTRACT2}Trainer{SE_M_DRAGON_RAGE}Th{SE_M_REVERSAL}Bug-Catching\n"
	.string "Contes{SE_M_SPIT_UP}i{SE_M_GRASSWHISTLE}o{SE_M_ATTRACT}today.\p"
	.string "Th{SE_M_REVERSAL}rule{SE_M_GRASSWHISTLE}ar{SE_M_REVERSAL}simple.\p"
	.string "Usin{SE_M_SANDSTORM}on{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}you{SE_M_SAND_TOMB}POKéMON{SE_M_SUPERSONIC}catc{SE_M_TRI_ATTACK}a\n"
	.string "bu{SE_M_SANDSTORM}POKéMO{SE_M_PSYBEAM2}t{SE_M_ATTRACT2}b{SE_M_REVERSAL}judged.\p"
	.string "Woul{SE_M_WATERFALL}yo{SE_M_DIVE}lik{SE_M_REVERSAL}t{SE_M_ATTRACT2}giv{SE_M_REVERSAL}i{SE_M_SPIT_UP}{SE_M_CHARGE}try?$"

Route35NationalParkGate_Text_OfficerGiveSportBalls:
	.string "An{SE_M_YAWN}EX{SE_M_PETAL_DANCE}you{SE_M_SAND_TOMB}POKéMO{SE_M_PSYBEAM2}gain{SE_M_GRASSWHISTLE}during\n"
	.string "th{SE_M_REVERSAL}contes{SE_M_SPIT_UP}wil{SE_M_BATON_PASS}b{SE_M_REVERSAL}reverte{SE_M_WATERFALL}when\l"
	.string "yo{SE_M_DIVE}leave.\p"
	.string "Her{SE_M_REVERSAL}ar{SE_M_REVERSAL}th{SE_M_REVERSAL}SPOR{SE_M_SWIFT}BALL{SE_M_SKETCH}fo{SE_M_SAND_TOMB}the\n"
	.string "Contest.$"

Route35NationalParkGate_Text_ReceivedSportBalls:
	.string "{PLAYER} receive{SE_M_WATERFALL}SPOR{SE_M_SWIFT}BALLS.$"

Route35NationalParkGate_Text_OfficerExplainRules:
	.string "Th{SE_M_REVERSAL}perso{SE_M_ATTRACT}wh{SE_M_ATTRACT2}get{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}strongest\n"
	.string "bu{SE_M_SANDSTORM}POKéMO{SE_M_PSYBEAM2}i{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}winner.\p"
	.string "I{SE_M_ACID_ARMOR}yo{SE_M_DIVE}ru{SE_M_ATTRACT}ou{SE_M_SPIT_UP}o{SE_M_ACID_ARMOR}SPOR{SE_M_SWIFT}BALLS,\n"
	.string "you'r{SE_M_REVERSAL}done.\p"
	.string "Yo{SE_M_DIVE}ca{SE_M_ATTRACT}catc{SE_M_TRI_ATTACK}u{SE_M_MORNING_SUN}t{SE_M_ATTRACT2}{SE_M_HORN_ATTACK}POKéMON{SE_M_PERISH_SONG}The\n"
	.string "las{SE_M_SPIT_UP}on{SE_M_REVERSAL}caugh{SE_M_SPIT_UP}wil{SE_M_BATON_PASS}b{SE_M_REVERSAL}th{SE_M_REVERSAL}only\l"
	.string "on{SE_M_REVERSAL}kep{SE_M_SPIT_UP}an{SE_M_WATERFALL}place{SE_M_WATERFALL}i{SE_M_ATTRACT}th{SE_M_REVERSAL}contest.\p"
	.string "G{SE_M_ATTRACT2}ou{SE_M_SPIT_UP}an{SE_M_WATERFALL}catc{SE_M_TRI_ATTACK}th{SE_M_REVERSAL}stronges{SE_M_SPIT_UP}bug\n"
	.string "POKéMO{SE_M_PSYBEAM2}yo{SE_M_DIVE}ca{SE_M_ATTRACT}find!$"

Route35NationalParkGate_Text_OfficerAskToUseFirstMon:
	.string "I{SE_M_ACID_ARMOR}yo{SE_M_DIVE}hav{SE_M_REVERSAL}mor{SE_M_REVERSAL}tha{SE_M_ATTRACT}on{SE_M_REVERSAL}POKéMON,\n"
	.string "you'l{SE_M_BATON_PASS}hav{SE_M_REVERSAL}t{SE_M_ATTRACT2}us{SE_M_REVERSAL}the\l"
	.string "firs{SE_M_SPIT_UP}POKéMO{SE_M_PSYBEAM2}i{SE_M_ATTRACT}you{SE_M_SAND_TOMB}party.\p"
	.string "I{SE_M_GRASSWHISTLE}tha{SE_M_SPIT_UP}O{SE_M_SNORE}wit{SE_M_TRI_ATTACK}you?$"

Route35NationalParkGate_Text_OfficerHoldYourMon:
	.string "Fine{SE_M_SUPERSONIC}we'l{SE_M_BATON_PASS}hol{SE_M_WATERFALL}you{SE_M_SAND_TOMB}othe{SE_M_SAND_TOMB}POKéMON\n"
	.string "whil{SE_M_REVERSAL}yo{SE_M_DIVE}compete.$"

Route35NationalParkGate_Text_MonLeftWithHelper:
	.string "{PLAYER}'{SE_M_GRASSWHISTLE}POKéMO{SE_M_PSYBEAM2}wer{SE_M_REVERSAL}lef{SE_M_SPIT_UP}wit{SE_M_TRI_ATTACK}the\n"
	.string "CONTES{SE_M_SWIFT}HELPER.$"

Route35NationalParkGate_Text_ChooseMonAndComeBack:
	.string "Pleas{SE_M_REVERSAL}choos{SE_M_REVERSAL}th{SE_M_REVERSAL}POKéMO{SE_M_PSYBEAM2}t{SE_M_ATTRACT2}b{SE_M_REVERSAL}used\n"
	.string "i{SE_M_ATTRACT}th{SE_M_REVERSAL}Contest{SE_M_SUPERSONIC}the{SE_M_ATTRACT}com{SE_M_REVERSAL}se{SE_M_REVERSAL}me.$"

Route35NationalParkGate_Text_TakePartInFuture:
	.string "OK{SE_M_PERISH_SONG}W{SE_M_REVERSAL}hop{SE_M_REVERSAL}you'l{SE_M_BATON_PASS}tak{SE_M_REVERSAL}par{SE_M_SPIT_UP}i{SE_M_ATTRACT}the\n"
	.string "future.$"

Route35NationalParkGate_Text_FirstMonCantBattle:
	.string "Uh-oh{SE_M_DIZZY_PUNCH}Th{SE_M_REVERSAL}firs{SE_M_SPIT_UP}POKéMO{SE_M_PSYBEAM2}i{SE_M_ATTRACT}your\n"
	.string "part{SE_M_YAWN}can'{SE_M_SPIT_UP}battle.\p"
	.string "Pleas{SE_M_REVERSAL}switc{SE_M_TRI_ATTACK}i{SE_M_SPIT_UP}wit{SE_M_TRI_ATTACK}th{SE_M_REVERSAL}POKéMON\n"
	.string "yo{SE_M_DIVE}wan{SE_M_SPIT_UP}t{SE_M_ATTRACT2}use{SE_M_SUPERSONIC}the{SE_M_ATTRACT}com{SE_M_REVERSAL}se{SE_M_REVERSAL}me.$"

Route35NationalParkGate_Text_MakeRoom:
	.string "Uh-oh{SE_M_DIZZY_PUNCH}Bot{SE_M_TRI_ATTACK}you{SE_M_SAND_TOMB}part{SE_M_YAWN}an{SE_M_WATERFALL}your\n"
	.string "P{SE_M_PSYBEAM}BO{SE_M_LOCK_ON}ar{SE_M_REVERSAL}full.\p"
	.string "Yo{SE_M_DIVE}hav{SE_M_REVERSAL}n{SE_M_ATTRACT2}roo{SE_M_MILK_DRINK}t{SE_M_ATTRACT2}pu{SE_M_SPIT_UP}th{SE_M_REVERSAL}bug\n"
	.string "POKéMO{SE_M_PSYBEAM2}yo{SE_M_DIVE}catch.\p"
	.string "Pleas{SE_M_REVERSAL}mak{SE_M_REVERSAL}roo{SE_M_MILK_DRINK}i{SE_M_ATTRACT}you{SE_M_SAND_TOMB}part{SE_M_YAWN}or\n"
	.string "you{SE_M_SAND_TOMB}P{SE_M_PSYBEAM}BOX{SE_M_SUPERSONIC}the{SE_M_ATTRACT}com{SE_M_REVERSAL}se{SE_M_REVERSAL}me.$"

Route35NationalParkGate_Text_EggAsFirstMon:
	.string "Uh-oh{SE_M_DIZZY_PUNCH}Yo{SE_M_DIVE}hav{SE_M_REVERSAL}a{SE_M_ATTRACT}EG{SE_M_SWAGGER}a{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}first\n"
	.string "POKéMO{SE_M_PSYBEAM2}i{SE_M_ATTRACT}you{SE_M_SAND_TOMB}party.\p"
	.string "Pleas{SE_M_REVERSAL}switc{SE_M_TRI_ATTACK}i{SE_M_SPIT_UP}wit{SE_M_TRI_ATTACK}th{SE_M_REVERSAL}POKéMON\n"
	.string "yo{SE_M_DIVE}wan{SE_M_SPIT_UP}t{SE_M_ATTRACT2}use{SE_M_SUPERSONIC}the{SE_M_ATTRACT}com{SE_M_REVERSAL}se{SE_M_REVERSAL}me.$"

Route35NationalParkGate_Text_ContestIsOver:
	.string "Today'{SE_M_GRASSWHISTLE}Contes{SE_M_SPIT_UP}i{SE_M_GRASSWHISTLE}over{SE_M_PERISH_SONG}W{SE_M_REVERSAL}hop{SE_M_REVERSAL}you\n"
	.string "wil{SE_M_BATON_PASS}participat{SE_M_REVERSAL}i{SE_M_ATTRACT}th{SE_M_REVERSAL}future.$"

Route35NationalParkGate_EventScript_Policeman::
	lock
	faceplayer
	msgbox Route35NationalParkGate_Text_WeHoldContests, MSGBOX_DEFAULT
	closemessage
	release
	end

Route35NationalParkGate_EventScript_BC1::
	lock
	faceplayer
	msgbox Route35NationalParkGate_Text_YoungsterWonders, MSGBOX_DEFAULT
	closemessage
	release
	end

Route35NationalParkGate_EventScript_BC2::
	lock
	faceplayer
	msgbox Route35NationalParkGate_Text_BC2, MSGBOX_DEFAULT
	closemessage
	release
	end

Route35NationalParkGate_EventScript_Rocker::
	lock
	faceplayer
	msgbox Route35NationalParkGate_Text_Rocker, MSGBOX_DEFAULT
	closemessage
	release
	end

Route35NationalParkGate_EventScript_Beauty::
	lock
	faceplayer
	msgbox Route35NationalParkGate_Text_Beauty, MSGBOX_DEFAULT
	closemessage
	release
	end

Route35NationalParkGate_Text_Rocker:
	.string "{SE_M_HEAL_BELL}lov{SE_M_REVERSAL}bir{SE_M_WATERFALL}POKéMON{SE_M_DRAGON_RAGE}{SE_M_HEAL_BELL}foun{SE_M_WATERFALL}a\n"
	.string "DARK-typ{SE_M_REVERSAL}bir{SE_M_WATERFALL}i{SE_M_ATTRACT}th{SE_M_REVERSAL}park\l"
	.string "las{SE_M_SPIT_UP}night!$"

Route35NationalParkGate_Text_BC2:
	.string "{SE_M_HEAL_BELL}caugh{SE_M_SPIT_UP}{SE_M_CHARGE}whoppin{SE_M_SANDSTORM}SCYTHER!$"

Route35NationalParkGate_Text_Beauty:
	.string "H{SE_M_REVERSAL}alway{SE_M_GRASSWHISTLE}win{SE_M_GRASSWHISTLE}thes{SE_M_REVERSAL}contests!$"

Route35NationalParkGate_Text_WeHoldContests:
	.string "W{SE_M_REVERSAL}hol{SE_M_WATERFALL}Contest{SE_M_GRASSWHISTLE}regularl{SE_M_YAWN}i{SE_M_ATTRACT}the\n"
	.string "PARK{SE_M_PERISH_SONG}Yo{SE_M_DIVE}shoul{SE_M_WATERFALL}giv{SE_M_REVERSAL}i{SE_M_SPIT_UP}{SE_M_CHARGE}shot.$"

Route35NationalParkGate_Text_YoungsterWonders:
	.string "Whe{SE_M_ATTRACT}i{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}nex{SE_M_SPIT_UP}Bug-Catchin{SE_M_SANDSTORM}Contest\n"
	.string "goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}be?$"

Route35NationalParkGate_Text_ContestExplanation:
	.string "Th{SE_M_REVERSAL}Bug-Catchin{SE_M_SANDSTORM}Contes{SE_M_SPIT_UP}i{SE_M_GRASSWHISTLE}hel{SE_M_WATERFALL}on\n"
	.string "Tuesday{SE_M_SUPERSONIC}Thursda{SE_M_YAWN}an{SE_M_WATERFALL}Saturday.\p"
	.string "No{SE_M_SPIT_UP}onl{SE_M_YAWN}d{SE_M_ATTRACT2}yo{SE_M_DIVE}ear{SE_M_ATTRACT}{SE_M_CHARGE}priz{SE_M_REVERSAL}just\n"
	.string "fo{SE_M_SAND_TOMB}participating,\p"
	.string "yo{SE_M_DIVE}als{SE_M_ATTRACT2}ge{SE_M_SPIT_UP}t{SE_M_ATTRACT2}kee{SE_M_MORNING_SUN}th{SE_M_REVERSAL}bu{SE_M_SANDSTORM}POKéMON\n"
	.string "yo{SE_M_DIVE}ma{SE_M_YAWN}hav{SE_M_REVERSAL}a{SE_M_SPIT_UP}th{SE_M_REVERSAL}en{SE_M_WATERFALL}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}contest.$"

