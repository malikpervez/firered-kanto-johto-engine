@ Johto (data/maps/BurnedTower_1F_hns/scripts.inc), as built into the FireRed game.

BurnedTower_1F_hns_MapScripts::
	map_script 1, BurnedTower_1F_OnLoad
	map_script 2, BurnedTower_1F_OnFrame
	map_script 3, BurnedTower_1F_OnTransition
	map_script 5, J_SetTimeEncounters
	.byte 0

BurnedTower_1F_OnTransition:
	callnative SetTimeBasedEncounters
	end

BurnedTower_1F_OnLoad::
	goto_if_ge 20561, 4, BurnedTower_1F_MapScript_CreateHole
	end

BurnedTower_1F_MapScript_CreateHole::
	setmetatile 16, 12, 0x37E, FALSE
	end

BurnedTower_1F_OnFrame::
	map_script_2 20561, 1, BurnedTower_1F_EventScript_MeetEusine
	.2byte 0

BurnedTower_1F_EventScript_MeetEusine::
	lock
	playse 21
	applymovement 1, J_Common_Movement_ExclamationMark
	delay 55
	waitmovement 1
	applymovement 1, BurnedTower_Movement_Eusine1
	waitmovement 0
	msgbox BurnedTower_1FEusineIntroText, MSGBOX_DEFAULT
	closemessage
	applymovement 1, BurnedTower_Movement_Eusine2
	waitmovement 0
	setvar 20561, 2
	release
	end

BurnedTower_Movement_Eusine1:
	walk_down
	walk_down
	step_end

BurnedTower_Movement_Eusine2:
	walk_up
	walk_up
	step_end

BurnedTower_1FEusineIntroText:
	.string "EUSINE{SE_M_HEAT_WAVE}M{SE_M_YAWN}name'{SE_M_GRASSWHISTLE}EUSINE.\p"
	.string "I'{SE_M_MILK_DRINK}o{SE_M_ATTRACT}th{SE_M_REVERSAL}trai{SE_M_BATON_PASS}o{SE_M_ACID_ARMOR}{SE_M_CHARGE}POKéMON\n"
	.string "calle{SE_M_WATERFALL}SUICUNE.\p"
	.string "An{SE_M_WATERFALL}yo{SE_M_DIVE}are...?\p"
	.string "{PLAYER}{SE_M_SING}Gla{SE_M_WATERFALL}t{SE_M_ATTRACT2}mee{SE_M_SPIT_UP}you!\p"
	.string "{SE_M_HEAL_BELL}hear{SE_M_WATERFALL}SUICUN{SE_M_SWORDS_DANCE}migh{SE_M_SPIT_UP}b{SE_M_REVERSAL}in\n"
	.string "thi{SE_M_GRASSWHISTLE}BURNE{SE_M_FAINT_ATTACK}TOWER{SE_M_SUPERSONIC}s{SE_M_ATTRACT2}{SE_M_HEAL_BELL}came\l"
	.string "t{SE_M_ATTRACT2}chec{SE_M_ENCORE2}i{SE_M_SPIT_UP}out.\p"
	.string "Bu{SE_M_SPIT_UP}wher{SE_M_REVERSAL}exactl{SE_M_YAWN}coul{SE_M_WATERFALL}i{SE_M_SPIT_UP}be?$"

BurnedTower_1F_EventScript_Item_HpUp::
	finditem ITEM_HP_UP
	end

BurnedTower_1F_EventScript_Item_Ether::
	finditem ITEM_ETHER
	end

BurnedTower_1F_EventScript_Eusine::
	lock
	faceplayer
	msgbox BurnedTower_1FEusineText, MSGBOX_DEFAULT
	closemessage
	release
	end

BurnedTower_1F_EventScript_Morty::
	lock
	faceplayer
	msgbox BurnedTower_1FMortyText, MSGBOX_DEFAULT
	closemessage
	release
	end

BurnedTower_1FEusineText:
	.string "EUSINE{SE_M_HEAT_WAVE}{SE_M_HEAL_BELL}hear{SE_M_WATERFALL}SUICUN{SE_M_SWORDS_DANCE}might\n"
	.string "b{SE_M_REVERSAL}i{SE_M_ATTRACT}thi{SE_M_GRASSWHISTLE}BURNE{SE_M_FAINT_ATTACK}TOWER{SE_M_SUPERSONIC}s{SE_M_ATTRACT2}I\l"
	.string "cam{SE_M_REVERSAL}t{SE_M_ATTRACT2}chec{SE_M_ENCORE2}i{SE_M_SPIT_UP}out.\p"
	.string "Bu{SE_M_SPIT_UP}wher{SE_M_REVERSAL}exactl{SE_M_YAWN}coul{SE_M_WATERFALL}i{SE_M_SPIT_UP}be?$"

BurnedTower_1FMortyText:
	.string "MORTY{SE_M_HEAT_WAVE}ECRUTEAK'{SE_M_GRASSWHISTLE}GY{SE_M_GIGA_DRAIN}LEADER\n"
	.string "ha{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}stud{SE_M_YAWN}wha{SE_M_SPIT_UP}ar{SE_M_REVERSAL}sai{SE_M_WATERFALL}to\l"
	.string "b{SE_M_REVERSAL}th{SE_M_REVERSAL}legendar{SE_M_YAWN}POKéMON--\l"
	.string "SUICUNE{SE_M_SUPERSONIC}ENTE{SE_M_HEAL_BELL}an{SE_M_WATERFALL}RAIKOU.\p"
	.string "EUSIN{SE_M_SWORDS_DANCE}i{SE_M_GRASSWHISTLE}here{SE_M_SUPERSONIC}s{SE_M_ATTRACT2}I've\n"
	.string "decide{SE_M_WATERFALL}t{SE_M_ATTRACT2}investigat{SE_M_REVERSAL}the\l"
	.string "TOWE{SE_M_MINIMIZE}wit{SE_M_TRI_ATTACK}him.$"

BurnedTower_1F_EventScript_Silver::
	lock
	playse 21
	applymovement 3, J_Common_Movement_ExclamationMark
	delay 55
	waitmovement 3
	applymovement 255, J_Common_Movement_WalkRight1
	applymovement 3, J_Common_Movement_WalkLeft1
	waitmovement 0
	waitmovement 0
	msgbox BurnedTowerSilver_BeforeText, MSGBOX_DEFAULT
	call_if_eq 20499, 0, BurnedTower_1F_Silver_Battle_Cyndaquil
	call_if_eq 20499, 1, BurnedTower_1F_Silver_Battle_Totodile
	call_if_eq 20499, 2, BurnedTower_1F_Silver_Battle_Chikorita
	playbgm ((558 + 1) + 0x3C), FALSE
	msgbox BurnedTowerSilver_AfterText1, MSGBOX_DEFAULT
	closemessage
	setvar 32772, 1
	setvar 32773, 1
	setvar 32774, 20
	setvar 32775, 6
	special ShakeCamera
	waitstate
	playse 36
	setmetatile 16, 12, 0x37E, FALSE
	special DrawWholeMapView
	waitse
	delay 60
	special SpawnCameraObject
	removeobject 255
	playse 43
	delay 60
	msgbox BurnedTowerSilver_AfterText2, MSGBOX_AUTOCLOSE
	waitmessage
	warphole MAP_BURNED_TOWER_B1F_HNS
	setvar 20561, 3
	waitstate
	release
	end

BurnedTower_1F_Silver_Battle_Cyndaquil::
	trainerbattle_no_intro 1476, BurnedTowerSilver_WinText
	return

BurnedTower_1F_Silver_Battle_Totodile::
	trainerbattle_no_intro 1483, BurnedTowerSilver_WinText
	return

BurnedTower_1F_Silver_Battle_Chikorita::
	trainerbattle_no_intro 1469, BurnedTowerSilver_WinText
	return

BurnedTowerSilver_BeforeText:
	.string "..............................\p"
	.string "...Oh{SE_M_SUPERSONIC}it'{SE_M_GRASSWHISTLE}you.\p"
	.string "{SE_M_HEAL_BELL}cam{SE_M_REVERSAL}lookin{SE_M_SANDSTORM}fo{SE_M_SAND_TOMB}some\n"
	.string "legendar{SE_M_YAWN}POKéMO{SE_M_PSYBEAM2}the{SE_M_YAWN}say\l"
	.string "roos{SE_M_SPIT_UP}here.\p"
	.string "Bu{SE_M_SPIT_UP}there'{SE_M_GRASSWHISTLE}nothin{SE_M_SANDSTORM}here!\p"
	.string "Nothing{SE_M_SUPERSONIC}afte{SE_M_SAND_TOMB}al{SE_M_BATON_PASS}th{SE_M_REVERSAL}effort\n"
	.string "o{SE_M_ACID_ARMOR}comin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}thi{SE_M_GRASSWHISTLE}dump?\l"
	.string "N{SE_M_ATTRACT2}way!\p"
	.string "It'{SE_M_GRASSWHISTLE}al{SE_M_BATON_PASS}you{SE_M_SAND_TOMB}fault!$"

BurnedTowerSilver_WinText:
	.string "...Humph!\p"
	.string "{SE_M_HEAL_BELL}onl{SE_M_YAWN}los{SE_M_SPIT_UP}becaus{SE_M_REVERSAL}my\n"
	.string "POKéMO{SE_M_PSYBEAM2}ar{SE_M_REVERSAL}incredibl{SE_M_YAWN}weak.\p"
	.string "Ho{SE_M_TWISTER}pathetic.$"

BurnedTowerSilver_AfterText1:
	.string "...Aw{SE_M_SUPERSONIC}whatever.\p"
	.string "You'{SE_M_WATERFALL}neve{SE_M_SAND_TOMB}b{SE_M_REVERSAL}abl{SE_M_REVERSAL}t{SE_M_ATTRACT2}catch\n"
	.string "{SE_M_CHARGE}legendar{SE_M_YAWN}POKéMO{SE_M_PSYBEAM2}anyway.$"

BurnedTowerSilver_LossText:
	.string "...Humph!\p"
	.string "Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}wh{SE_M_YAWN}{SE_M_HEAL_BELL}hat{SE_M_REVERSAL}battling\n"
	.string "wimps{SE_M_PERISH_SONG}It'{SE_M_GRASSWHISTLE}{SE_M_CHARGE}wast{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}time.$"

BurnedTowerSilver_AfterText2:
	.string "Humph!\p"
	.string "Wha{SE_M_SPIT_UP}ar{SE_M_REVERSAL}yo{SE_M_DIVE}doin{SE_M_SANDSTORM}falling\n"
	.string "int{SE_M_ATTRACT2}{SE_M_CHARGE}hole{SE_M_SING}Som{SE_M_REVERSAL}genius!\p"
	.string "Serve{SE_M_GRASSWHISTLE}yo{SE_M_DIVE}right!$"

BurnedTower_1F_EventScript_Nard::
	trainerbattle_single 1310, BurnedTower_Text_NardSeen, BurnedTower_Text_NardBeaten
	msgbox BurnedTower_Text_NardAfter, MSGBOX_AUTOCLOSE
	end

BurnedTower_1F_EventScript_Richardo::
	trainerbattle_single 1309, BurnedTower_Text_RichardoSeen, BurnedTower_Text_RichardoBeaten
	msgbox BurnedTower_Text_RichardoAfter, MSGBOX_AUTOCLOSE
	end

BurnedTower_Text_NardSeen:
	.string "Don'{SE_M_SPIT_UP}worry!\p"
	.string "W{SE_M_REVERSAL}fire-breather{SE_M_GRASSWHISTLE}kno{SE_M_TWISTER}th{SE_M_REVERSAL}true\n"
	.string "powe{SE_M_SAND_TOMB}o{SE_M_ACID_ARMOR}fir{SE_M_REVERSAL}bette{SE_M_SAND_TOMB}tha{SE_M_ATTRACT}anyone!$"

BurnedTower_Text_NardBeaten:
	.string "Thank{SE_M_GRASSWHISTLE}fo{SE_M_SAND_TOMB}suc{SE_M_TRI_ATTACK}{SE_M_CHARGE}heate{SE_M_WATERFALL}battle!$"

BurnedTower_Text_NardAfter:
	.string "Th{SE_M_REVERSAL}reaso{SE_M_ATTRACT}thi{SE_M_GRASSWHISTLE}tower'{SE_M_GRASSWHISTLE}burne{SE_M_WATERFALL}is\n"
	.string "tha{SE_M_SPIT_UP}i{SE_M_SPIT_UP}wa{SE_M_GRASSWHISTLE}hi{SE_M_SPIT_UP}b{SE_M_YAWN}lightning.\p"
	.string "Th{SE_M_REVERSAL}fir{SE_M_REVERSAL}I'{SE_M_MILK_DRINK}breathin{SE_M_SANDSTORM}i{SE_M_GRASSWHISTLE}tiny\n"
	.string "i{SE_M_ATTRACT}comparison...$"

BurnedTower_Text_RichardoSeen:
	.string "I'{SE_M_MILK_DRINK}practicin{SE_M_SANDSTORM}m{SE_M_YAWN}stealin{SE_M_SANDSTORM}i{SE_M_ATTRACT}the\n"
	.string "BURNE{SE_M_FAINT_ATTACK}TOWER{SE_M_DRAGON_RAGE}Don'{SE_M_SPIT_UP}try\l"
	.string "thi{SE_M_GRASSWHISTLE}a{SE_M_SPIT_UP}home!$"

BurnedTower_Text_RichardoBeaten:
	.string "Pfffffffffffffff.$"

BurnedTower_Text_RichardoAfter:
	.string "Mayb{SE_M_REVERSAL}{SE_M_CHARGE}lif{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}crim{SE_M_REVERSAL}isn'{SE_M_SPIT_UP}for\n"
	.string "me...$"

