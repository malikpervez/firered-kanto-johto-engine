@ Johto (data/scripts/bug_contest.inc), as built into the FireRed game.

J_BugContest_EventScript_Start::
	end

J_BugContest_EventScript_WhiteOut::
	lockall
	delay 200
	msgbox J_BugContest_Text_WhiteOut, MSGBOX_DEFAULT
	closemessage
	goto J_BugContest_EventScript_End
	end

J_BugContest_EventScript_TimesUp::
	lockall
	playse SE_DING_DONG
	msgbox J_BugContest_Text_TimesUp, MSGBOX_DEFAULT
	closemessage
	waitse
	getpartysize
	goto_if_eq VAR_RESULT, 1, J_BugContest_EventScript_Didntcatch
	fadescreen FADE_TO_BLACK
	setvar JOHTO_VAR_BUG_CONTEST_STATE, 3

	msgbox J_BugContest_Text_Judging0, MSGBOX_DEFAULT
	closemessage

BugContest_EventScript_TimesUp2::
	special ChoosePartyMon
	waitstate
	copyvar 32778, 32772
	goto_if_eq 32772, 0xFF, J_BugContest_EventScript_WrongChoiceMon
	goto_if_eq 32772, 0, J_BugContest_EventScript_WrongChoiceMon
	fadescreen 1
	warp MAP_NATIONAL_PARK_BUG_CONTEST_HNS, 5
	waitstate
	delay 90
	end

J_BugContest_EventScript_WrongChoiceMon::
	msgbox J_BugContest_Text_WrongChoiceMon, MSGBOX_DEFAULT
	goto BugContest_EventScript_TimesUp2
	end

J_BugContestEventScript_Judging::
	msgbox J_BugContest_Text_Judging1, MSGBOX_DEFAULT
	closemessage
	special JudgeBugContestMon
	call_if_eq VAR_RESULT, 1, J_BugContest_EventScript_First
	call_if_eq VAR_RESULT, 2, J_BugContest_EventScript_Second
	call_if_eq VAR_RESULT, 3, J_BugContest_EventScript_Third
	special TransferBugContestMon
	delay 20
	giveitem VAR_0x8005
	msgbox J_BugContest_Text_TransferAndReturn, MSGBOX_DEFAULT
	playse SE_SUCCESS
	waitse
	msgbox J_BugContest_Text_TakePartInFuture, MSGBOX_DEFAULT
	closemessage
	goto J_BugContest_EventScript_End
	end

J_BugContest_EventScript_Didntcatch::
	msgbox J_BugContest_Text_DidntCatch, MSGBOX_DEFAULT
	playse SE_SUCCESS
	closemessage
	fadescreen FADE_TO_BLACK
	goto J_BugContest_EventScript_End
	end

J_BugContest_EventScript_First::
	msgbox J_BugContest_Text_First1, MSGBOX_DEFAULT
	playfanfare ((558 + 1) + 0xA4)
	waitfanfare
	msgbox J_BugContest_Text_First2, MSGBOX_DEFAULT
	playfanfare ((558 + 1) + 0xA3)
	waitfanfare
	msgbox J_BugContest_Text_First3, MSGBOX_DEFAULT
	playfanfare ((558 + 1) + 0xA2)
	waitfanfare
	closemessage
	return

J_BugContest_EventScript_Second::
	msgbox J_BugContest_Text_Second1, MSGBOX_DEFAULT
	playfanfare ((558 + 1) + 0xA4)
	waitfanfare
	msgbox J_BugContest_Text_Second2, MSGBOX_DEFAULT
	playfanfare ((558 + 1) + 0xA3)
	waitfanfare
	msgbox J_BugContest_Text_Second3, MSGBOX_DEFAULT
	playfanfare ((558 + 1) + 0xA2)
	waitfanfare
	closemessage
	return

J_BugContest_EventScript_Third::
	msgbox J_BugContest_Text_Third1, MSGBOX_DEFAULT
	playfanfare ((558 + 1) + 0xA4)
	waitfanfare
	msgbox J_BugContest_Text_Third2, MSGBOX_DEFAULT
	playfanfare ((558 + 1) + 0xA3)
	waitfanfare
	msgbox J_BugContest_Text_Third3, MSGBOX_DEFAULT
	playfanfare ((558 + 1) + 0xA2)
	waitfanfare
	closemessage
	return

J_BugContest_EventScript_End::
	special HealPlayerParty
	special LoadPlayerParty
	special ExitBugContestMode
	clearflag JOHTO_FLAG_DISABLE_EXP_GAIN
	setvar JOHTO_VAR_BUG_CONTEST_STATE, 0
	special RemoveSportBalls
	goto_if_eq VAR_TEMP_1, 1, J_BugContest_EventScript_SideEnd
	warp MAP_GATE_NATIONAL_PARK_HNS, 7, 2
	waitstate
	releaseall
	end

J_BugContest_EventScript_SideEnd::
	warp MAP_GATE_NATIONAL_PARK_HNS, 35, 7
	waitstate
	releaseall
	end

J_BugContest_Text_Judging0::
	.string "Th{SE_M_REVERSAL}contes{SE_M_SPIT_UP}ha{SE_M_GRASSWHISTLE}no{SE_M_TWISTER}concluded.\n"
	.string "Pleas{SE_M_REVERSAL}pic{SE_M_ENCORE2}th{SE_M_REVERSAL}POKéMO{SE_M_PSYBEAM2}yo{SE_M_DIVE}would\l"
	.string "lik{SE_M_REVERSAL}t{SE_M_ATTRACT2}kee{SE_M_MORNING_SUN}an{SE_M_WATERFALL}hav{SE_M_REVERSAL}judged.$"

J_BugContest_Text_Judging1::
	.string "W{SE_M_REVERSAL}wil{SE_M_BATON_PASS}no{SE_M_TWISTER}judg{SE_M_REVERSAL}th{SE_M_REVERSAL}POKéMON\n"
	.string "you'v{SE_M_REVERSAL}caught.\p"
	.string "...................\n"
	.string "...................\p"
	.string "W{SE_M_REVERSAL}hav{SE_M_REVERSAL}chose{SE_M_ATTRACT}th{SE_M_REVERSAL}winners{SE_M_DRAGON_RAGE}Are\n"
	.string "read{SE_M_YAWN}fo{SE_M_SAND_TOMB}this?$"

J_BugContest_Text_WrongChoiceMon:
	.string "Pleas{SE_M_REVERSAL}pic{SE_M_ENCORE2}th{SE_M_REVERSAL}POKéMO{SE_M_PSYBEAM2}yo{SE_M_DIVE}would\n"
	.string "lik{SE_M_REVERSAL}t{SE_M_ATTRACT2}kee{SE_M_MORNING_SUN}an{SE_M_WATERFALL}hav{SE_M_REVERSAL}judged.$"

J_BugContest_Text_DidntCatch:
	.string "O{SE_M_TRI_ATTACK}no{SE_M_DRAGON_RAGE}Yo{SE_M_DIVE}didn'{SE_M_SPIT_UP}catc{SE_M_TRI_ATTACK}{SE_M_CHARGE}POKéMON.\n"
	.string "You'v{SE_M_REVERSAL}forfeite{SE_M_WATERFALL}th{SE_M_REVERSAL}competition.\p"
	.string "You{SE_M_SAND_TOMB}part{SE_M_YAWN}wil{SE_M_BATON_PASS}no{SE_M_TWISTER}b{SE_M_REVERSAL}returned.$"

J_BugContest_Text_TimesUp:
	.string "Ding-dong{SE_M_DRAGON_RAGE}Time'{SE_M_GRASSWHISTLE}up!$"

J_BugContest_Text_WhiteOut:
	.string "{PLAYER} i{SE_M_GRASSWHISTLE}ou{SE_M_SPIT_UP}o{SE_M_ACID_ARMOR}useabl{SE_M_REVERSAL}POKéMON.\n"
	.string "{PLAYER} forfeite{SE_M_WATERFALL}th{SE_M_REVERSAL}contest.$"

J_BugContest_Text_First1:
	.string "Placin{SE_M_SANDSTORM}thir{SE_M_WATERFALL}i{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}COOLTRAINER\n"
	.string "BELINDA{SE_M_SUPERSONIC}wh{SE_M_ATTRACT2}caugh{SE_M_SPIT_UP}{SE_M_CHARGE}wriggling\l"
	.string "BUTTERFREE!$"

J_BugContest_Text_First2:
	.string "Placin{SE_M_SANDSTORM}secon{SE_M_WATERFALL}i{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}BUGCATCHER\n"
	.string "SHAUN{SE_M_SUPERSONIC}wh{SE_M_ATTRACT2}caugh{SE_M_SPIT_UP}{SE_M_CHARGE}writhing\l"
	.string "PINSIR!$"

J_BugContest_Text_First3:
	.string "Thi{SE_M_GRASSWHISTLE}Bug-Catchin{SE_M_SANDSTORM}Contes{SE_M_SPIT_UP}Winner\n"
	.string "is...\p"
	.string "{PLAYER}{SE_M_SUPERSONIC}wh{SE_M_ATTRACT2}caugh{SE_M_SPIT_UP}{SE_M_CHARGE}whopping\n"
	.string "{STR_VAR_1}!$"

J_BugContest_Text_Second1:
	.string "Placin{SE_M_SANDSTORM}thir{SE_M_WATERFALL}i{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}COOLTRAINER\n"
	.string "BELINDA{SE_M_SUPERSONIC}wh{SE_M_ATTRACT2}caugh{SE_M_SPIT_UP}{SE_M_CHARGE}wriggling\l"
	.string "BUTTERFREE!$"

J_BugContest_Text_Second2:
	.string "Placin{SE_M_SANDSTORM}secon{SE_M_WATERFALL}i{SE_M_GRASSWHISTLE}{PLAYER}{SE_M_SUPERSONIC}who\n"
	.string "caugh{SE_M_SPIT_UP}{SE_M_CHARGE}writhin{SE_M_SANDSTORM}{STR_VAR_1}!$"

J_BugContest_Text_Second3:
	.string "Thi{SE_M_GRASSWHISTLE}Bug-Catchin{SE_M_SANDSTORM}Contes{SE_M_SPIT_UP}Winner\n"
	.string "is...\p"
	.string "BUGCATCHE{SE_M_MINIMIZE}SHAUN{SE_M_SUPERSONIC}wh{SE_M_ATTRACT2}caugh{SE_M_SPIT_UP}a\n"
	.string "whoppin{SE_M_SANDSTORM}PINSIR!$"

J_BugContest_Text_Third1:
	.string "Placin{SE_M_SANDSTORM}thir{SE_M_WATERFALL}i{SE_M_GRASSWHISTLE}{PLAYER}{SE_M_SUPERSONIC}who\n"
	.string "caugh{SE_M_SPIT_UP}{SE_M_CHARGE}wrigglin{SE_M_SANDSTORM}{STR_VAR_1}!$"

J_BugContest_Text_Third2:
	.string "Placin{SE_M_SANDSTORM}secon{SE_M_WATERFALL}i{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}COOLTRAINER\n"
	.string "BELINDA{SE_M_SUPERSONIC}wh{SE_M_ATTRACT2}caugh{SE_M_SPIT_UP}{SE_M_CHARGE}writhing\l"
	.string "BUTTERFREE!$"

J_BugContest_Text_Third3:
	.string "Thi{SE_M_GRASSWHISTLE}Bug-Catchin{SE_M_SANDSTORM}Contes{SE_M_SPIT_UP}Winner\n"
	.string "is...\p"
	.string "BUGCATCHE{SE_M_MINIMIZE}SHAUN{SE_M_SUPERSONIC}wh{SE_M_ATTRACT2}caugh{SE_M_SPIT_UP}a\n"
	.string "whoppin{SE_M_SANDSTORM}PINSIR!$"

J_BugContest_Text_TakePartInFuture:
	.string "Than{SE_M_ENCORE2}yo{SE_M_DIVE}fo{SE_M_SAND_TOMB}participating!\n"
	.string "W{SE_M_REVERSAL}hop{SE_M_REVERSAL}you'l{SE_M_BATON_PASS}tak{SE_M_REVERSAL}par{SE_M_SPIT_UP}i{SE_M_ATTRACT}the\l"
	.string "future.$"

J_BugContest_Text_TransferAndReturn:
	.string "You{SE_M_SAND_TOMB}chose{SE_M_ATTRACT}BU{SE_M_SWAGGER}POKéMO{SE_M_PSYBEAM2}wil{SE_M_BATON_PASS}now\n"
	.string "b{SE_M_REVERSAL}sen{SE_M_SPIT_UP}t{SE_M_ATTRACT2}th{SE_M_REVERSAL}P{SE_M_PSYBEAM}an{SE_M_WATERFALL}you{SE_M_SAND_TOMB}party\l"
	.string "wil{SE_M_BATON_PASS}b{SE_M_REVERSAL}returne{SE_M_WATERFALL}t{SE_M_ATTRACT2}you.$"

