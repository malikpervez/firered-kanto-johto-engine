@ Johto (data/maps/NewSinjoh_HotSprings_hns/scripts.inc), as built into the FireRed game.

NewSinjoh_HotSprings_hns_MapScripts::
	.byte 0

NewSinjoh_HotSprings_EventScript_Item_MaxRevive::
	finditem ITEM_MAX_REVIVE
	end

NewSinjoh_HotSprings_EventScript_Item_LavaCookie::
	finditem ITEM_LAVA_COOKIE
	end

NewSinjoh_HotSprings_EventScript_Mualani::
	goto_if_defeated 1638, NewSinjoh_HotSprings_EventScript_MualaniAfter
	msgbox NewSinjoh_HotSprings_Text_MualaniBefore, MSGBOX_NPC
	goto_if_not_defeated 1638, NewSinjoh_HotSprings_EventScript_TryMualaniBattle
	end

NewSinjoh_HotSprings_EventScript_TryMualaniBattle::
	goto_if_eq 20639, 6, NewSinjoh_HotSprings_EventScript_MualaniBattle
	end

NewSinjoh_HotSprings_EventScript_MualaniBattle::
	lock
	msgbox NewSinjoh_HotSprings_Text_MualaniBeforeBattle, MSGBOX_AUTOCLOSE
	trainerbattle_no_intro 1638, NewSinjoh_HotSprings_Text_MualaniDefeat
	giveitem ITEM_SPLASH_PLATE
	addvar 20640, 1
	msgbox NewSinjoh_HotSprings_Text_MualaniAfter, MSGBOX_AUTOCLOSE
	call_if_eq 20640, 3, SinjohRuins_Lab_EventScript_3Plates
	call_if_eq 20640, 6, SinjohRuins_Lab_EventScript_6Plates
	call_if_eq 20640, 9, SinjohRuins_Lab_EventScript_9Plates
	call_if_eq 20640, 12, SinjohRuins_Lab_EventScript_12Plates
	call_if_eq 20640, 15, SinjohRuins_Lab_EventScript_15Plates
	call_if_eq 20640, 16, SinjohRuins_Lab_EventScript_16Plates
	release
	end

NewSinjoh_HotSprings_EventScript_MualaniAfter::
	msgbox NewSinjoh_HotSprings_Text_MualaniAfter, MSGBOX_NPC
	end

NewSinjoh_HotSprings_Text_MualaniBefore:
	.string "A{SE_M_MILK_DRINK}{SE_M_HEAL_BELL}{SE_M_CHARGE}loca{SE_M_BATON_PASS}o{SE_M_SAND_TOMB}{SE_M_CHARGE}visitor?\n"
	.string "Wha{SE_M_SPIT_UP}{SE_M_CHARGE}rud{SE_M_REVERSAL}question!\p"
	.string "I{SE_M_ACID_ARMOR}yo{SE_M_DIVE}mus{SE_M_SPIT_UP}know{SE_M_SUPERSONIC}I'{SE_M_MILK_DRINK}{SE_M_CHARGE}local.\p"
	.string "M{SE_M_YAWN}famil{SE_M_YAWN}wa{SE_M_GRASSWHISTLE}amon{SE_M_SANDSTORM}th{SE_M_REVERSAL}firs{SE_M_SPIT_UP}to\n"
	.string "enjo{SE_M_YAWN}thes{SE_M_REVERSAL}springs.\p"
	.string "See{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}eve{SE_M_ATTRACT}hav{SE_M_REVERSAL}thi{SE_M_GRASSWHISTLE}SPLAS{SE_M_SWAGGER2}PLATE\n"
	.string "t{SE_M_ATTRACT2}prov{SE_M_REVERSAL}it.$"

NewSinjoh_HotSprings_Text_MualaniBeforeBattle:
	.string "Wait...\p"
	.string "Yo{SE_M_DIVE}nee{SE_M_WATERFALL}th{SE_M_REVERSAL}SPLAS{SE_M_SWAGGER2}PLATE\n"
	.string "t{SE_M_ATTRACT2}tam{SE_M_REVERSAL}th{SE_M_REVERSAL}legendar{SE_M_YAWN}POKéMON?\p"
	.string "I{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}KIMON{SE_M_SOLAR_BEAM}GIRL{SE_M_SKETCH}thin{SE_M_ENCORE2}you\n"
	.string "ar{SE_M_REVERSAL}worthy{SE_M_SUPERSONIC}the{SE_M_ATTRACT}s{SE_M_ATTRACT2}d{SE_M_ATTRACT2}I.\p"
	.string "Bu{SE_M_SPIT_UP}you'l{SE_M_BATON_PASS}stil{SE_M_BATON_PASS}nee{SE_M_WATERFALL}t{SE_M_ATTRACT2}earn\n"
	.string "it.$"

NewSinjoh_HotSprings_Text_MualaniDefeat:
	.string "Wel{SE_M_BATON_PASS}earned.$"

NewSinjoh_HotSprings_Text_MualaniAfter:
	.string "I{SE_M_SPIT_UP}i{SE_M_GRASSWHISTLE}har{SE_M_WATERFALL}fo{SE_M_SAND_TOMB}m{SE_M_REVERSAL}t{SE_M_ATTRACT2}le{SE_M_SPIT_UP}that\n"
	.string "plat{SE_M_REVERSAL}go.\p"
	.string "Bu{SE_M_SPIT_UP}whe{SE_M_ATTRACT}th{SE_M_REVERSAL}situatio{SE_M_ATTRACT}changes,\n"
	.string "i{SE_M_SPIT_UP}i{SE_M_GRASSWHISTLE}importan{SE_M_SPIT_UP}fo{SE_M_SAND_TOMB}u{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}change\l"
	.string "too.\p"
	.string "Th{SE_M_REVERSAL}plat{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}yours.$"

NewSinjoh_HotSprings_EventScript_Sign1::
	msgbox NewSinjoh_HotSprings_Text_Sign1, MSGBOX_SIGN
	end

NewSinjoh_HotSprings_Text_Sign1:
	.string "NE{SE_M_DETECT}SINJOH\n"
	.string "HO{SE_M_SWIFT}SPRINGS$"

NewSinjoh_HotSprings_EventScript_Sign2::
	msgbox NewSinjoh_HotSprings_Text_Sign2, MSGBOX_SIGN
	end

NewSinjoh_HotSprings_Text_Sign2:
	.string "DANGER\n"
	.string "WIL{SE_M_FAINT_ATTACK}HIBERNATIO{SE_M_PSYBEAM2}DEN$"

NewSinjoh_HotSprings_EventScript_SkierF::
	msgbox NewSinjoh_HotSprings_Text_SkierF, MSGBOX_NPC
	end

NewSinjoh_HotSprings_Text_SkierF:
	.string "{SE_M_HEAL_BELL}hat{SE_M_REVERSAL}th{SE_M_REVERSAL}cold!\p"
	.string "I'{SE_M_MILK_DRINK}jus{SE_M_SPIT_UP}her{SE_M_REVERSAL}fo{SE_M_SAND_TOMB}th{SE_M_REVERSAL}ho{SE_M_SPIT_UP}springs!$"

NewSinjoh_HotSprings_EventScript_SkierM::
	msgbox NewSinjoh_HotSprings_Text_SkierM, MSGBOX_NPC
	end

NewSinjoh_HotSprings_Text_SkierM:
	.string "{SE_M_HEAL_BELL}cam{SE_M_REVERSAL}her{SE_M_REVERSAL}t{SE_M_ATTRACT2}snowboard\n"
	.string "bu{SE_M_SPIT_UP}al{SE_M_BATON_PASS}m{SE_M_YAWN}girlfrien{SE_M_WATERFALL}want{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}do\l"
	.string "i{SE_M_GRASSWHISTLE}si{SE_M_SPIT_UP}i{SE_M_ATTRACT}th{SE_M_REVERSAL}spring{SE_M_GRASSWHISTLE}al{SE_M_BATON_PASS}day!$"

NewSinjoh_HotSprings_EventScript_OldLady::
	msgbox NewSinjoh_HotSprings_Text_OldLady, MSGBOX_NPC
	end

NewSinjoh_HotSprings_Text_OldLady:
	.string "Ignor{SE_M_REVERSAL}m{SE_M_YAWN}husband.\p"
	.string "Le{SE_M_SPIT_UP}you{SE_M_SAND_TOMB}worrie{SE_M_GRASSWHISTLE}mel{SE_M_SPIT_UP}away.$"

NewSinjoh_HotSprings_EventScript_CreepyMan::
	msgbox NewSinjoh_HotSprings_Text_CreepyMan, MSGBOX_NPC
	end

NewSinjoh_HotSprings_Text_CreepyMan:
	.string "Ouughh...\p"
	.string "Thi{SE_M_GRASSWHISTLE}wate{SE_M_SAND_TOMB}feel{SE_M_GRASSWHISTLE}magica{SE_M_BATON_PASS}o{SE_M_ATTRACT}m{SE_M_YAWN}back.\p"
	.string "I{SE_M_ACID_ARMOR}yo{SE_M_DIVE}hav{SE_M_REVERSAL}bac{SE_M_ENCORE2}pai{SE_M_ATTRACT}too,\n"
	.string "yo{SE_M_DIVE}shoul{SE_M_WATERFALL}sta{SE_M_YAWN}her{SE_M_REVERSAL}wit{SE_M_TRI_ATTACK}me...$"

NewSinjoh_HotSprings_EventScript_PLATutor::
	lock
	faceplayer
	msgbox NewSinjoh_HotSprings_Text_PLATutorIntro, MSGBOX_YESNO
	goto_if_eq 32781, NO, NewSinjoh_HotSprings_EventScript_PLATutorDecline
	message NewSinjoh_HotSprings_Text_PLATutorChoose
	waitmessage
	dynmultichoice 0, 0, FALSE, 6, 0, 255, NewSinjoh_HotSprings_Text_PLAMove_PowerShift, NewSinjoh_HotSprings_Text_PLAMove_SpringtideStorm, NewSinjoh_HotSprings_Text_PLAMove_MysticalPower, NewSinjoh_HotSprings_Text_PLAMove_WaveCrash, NewSinjoh_HotSprings_Text_PLAMove_MountainGale, NewSinjoh_HotSprings_Text_PLAMove_VictoryDance, NewSinjoh_HotSprings_Text_PLAMove_EsperWing, NewSinjoh_HotSprings_Text_PLAMove_BitterMalice, NewSinjoh_HotSprings_Text_PLAMove_Shelter, NewSinjoh_HotSprings_Text_PLAMove_BleakwindStorm, NewSinjoh_HotSprings_Text_PLAMove_WildboltStorm, NewSinjoh_HotSprings_Text_PLAMove_SandsearStorm, NewSinjoh_HotSprings_Text_PLAMove_LunarBlessing, NewSinjoh_HotSprings_Text_PLAMove_TakeHeart, NewSinjoh_HotSprings_Text_PLAMove_Cancel
	switch 32781
	case 0, NewSinjoh_HotSprings_EventScript_PLATeach_PowerShift
	case 1, NewSinjoh_HotSprings_EventScript_PLATeach_SpringtideStorm
	case 2, NewSinjoh_HotSprings_EventScript_PLATeach_MysticalPower
	case 3, NewSinjoh_HotSprings_EventScript_PLATeach_WaveCrash
	case 4, NewSinjoh_HotSprings_EventScript_PLATeach_MountainGale
	case 5, NewSinjoh_HotSprings_EventScript_PLATeach_VictoryDance
	case 6, NewSinjoh_HotSprings_EventScript_PLATeach_EsperWing
	case 7, NewSinjoh_HotSprings_EventScript_PLATeach_BitterMalice
	case 8, NewSinjoh_HotSprings_EventScript_PLATeach_Shelter
	case 9, NewSinjoh_HotSprings_EventScript_PLATeach_BleakwindStorm
	case 10, NewSinjoh_HotSprings_EventScript_PLATeach_WildboltStorm
	case 11, NewSinjoh_HotSprings_EventScript_PLATeach_SandsearStorm
	case 12, NewSinjoh_HotSprings_EventScript_PLATeach_LunarBlessing
	case 13, NewSinjoh_HotSprings_EventScript_PLATeach_TakeHeart
	case 14, NewSinjoh_HotSprings_EventScript_PLATutorDecline
	case 127, NewSinjoh_HotSprings_EventScript_PLATutorDecline
	end

NewSinjoh_HotSprings_EventScript_PLATeach_PowerShift::
	setvar 32773, MOVE_POWER_SHIFT
	goto NewSinjoh_HotSprings_EventScript_PLATeachMove
	end

NewSinjoh_HotSprings_EventScript_PLATeach_SpringtideStorm::
	setvar 32773, MOVE_SPRINGTIDE_STORM
	goto NewSinjoh_HotSprings_EventScript_PLATeachMove
	end

NewSinjoh_HotSprings_EventScript_PLATeach_MysticalPower::
	setvar 32773, MOVE_MYSTICAL_POWER
	goto NewSinjoh_HotSprings_EventScript_PLATeachMove
	end

NewSinjoh_HotSprings_EventScript_PLATeach_WaveCrash::
	setvar 32773, MOVE_WAVE_CRASH
	goto NewSinjoh_HotSprings_EventScript_PLATeachMove
	end

NewSinjoh_HotSprings_EventScript_PLATeach_MountainGale::
	setvar 32773, MOVE_MOUNTAIN_GALE
	goto NewSinjoh_HotSprings_EventScript_PLATeachMove
	end

NewSinjoh_HotSprings_EventScript_PLATeach_VictoryDance::
	setvar 32773, MOVE_VICTORY_DANCE
	goto NewSinjoh_HotSprings_EventScript_PLATeachMove
	end

NewSinjoh_HotSprings_EventScript_PLATeach_EsperWing::
	setvar 32773, MOVE_ESPER_WING
	goto NewSinjoh_HotSprings_EventScript_PLATeachMove
	end

NewSinjoh_HotSprings_EventScript_PLATeach_BitterMalice::
	setvar 32773, MOVE_BITTER_MALICE
	goto NewSinjoh_HotSprings_EventScript_PLATeachMove
	end

NewSinjoh_HotSprings_EventScript_PLATeach_Shelter::
	setvar 32773, MOVE_SHELTER
	goto NewSinjoh_HotSprings_EventScript_PLATeachMove
	end

NewSinjoh_HotSprings_EventScript_PLATeach_BleakwindStorm::
	setvar 32773, MOVE_BLEAKWIND_STORM
	goto NewSinjoh_HotSprings_EventScript_PLATeachMove
	end

NewSinjoh_HotSprings_EventScript_PLATeach_WildboltStorm::
	setvar 32773, MOVE_WILDBOLT_STORM
	goto NewSinjoh_HotSprings_EventScript_PLATeachMove
	end

NewSinjoh_HotSprings_EventScript_PLATeach_SandsearStorm::
	setvar 32773, MOVE_SANDSEAR_STORM
	goto NewSinjoh_HotSprings_EventScript_PLATeachMove
	end

NewSinjoh_HotSprings_EventScript_PLATeach_LunarBlessing::
	setvar 32773, MOVE_LUNAR_BLESSING
	goto NewSinjoh_HotSprings_EventScript_PLATeachMove
	end

NewSinjoh_HotSprings_EventScript_PLATeach_TakeHeart::
	setvar 32773, MOVE_TAKE_HEART
	goto NewSinjoh_HotSprings_EventScript_PLATeachMove
	end

NewSinjoh_HotSprings_EventScript_PLATeachMove::
	buffermovename STR_VAR_1, 32773
	msgbox NewSinjoh_HotSprings_Text_PLATutorConfirm, MSGBOX_YESNO
	goto_if_eq 32781, NO, NewSinjoh_HotSprings_EventScript_PLATutor
	msgbox NewSinjoh_HotSprings_Text_PLATutorWhichMon, MSGBOX_DEFAULT
	fadescreen 1
	chooseboxmon SELECT_PC_MON_PLA_TUTOR
	waitstate
	goto_if_eq 32781, FALSE, NewSinjoh_HotSprings_EventScript_PLATutorCancelMon
	msgbox NewSinjoh_HotSprings_Text_PLATutorDone, MSGBOX_DEFAULT
	release
	end

NewSinjoh_HotSprings_EventScript_PLATutorCancelMon::
	msgbox NewSinjoh_HotSprings_Text_PLATutorComeBack, MSGBOX_DEFAULT
	release
	end

NewSinjoh_HotSprings_EventScript_PLATutorDecline::
	msgbox NewSinjoh_HotSprings_Text_PLATutorComeBack, MSGBOX_DEFAULT
	release
	end

NewSinjoh_HotSprings_Text_PLATutorIntro:
	.string "Th{SE_M_REVERSAL}ancien{SE_M_SPIT_UP}powe{SE_M_SAND_TOMB}flows\n"
	.string "throug{SE_M_TRI_ATTACK}thes{SE_M_REVERSAL}springs.\p"
	.string "{SE_M_HEAL_BELL}ca{SE_M_ATTRACT}teac{SE_M_TRI_ATTACK}you{SE_M_SAND_TOMB}POKeMO{SE_M_PSYBEAM2}moves\n"
	.string "fro{SE_M_MILK_DRINK}{SE_M_CHARGE}forgotte{SE_M_ATTRACT}age.\p"
	.string "Interested?$"

NewSinjoh_HotSprings_Text_PLATutorChoose:
	.string "Whic{SE_M_TRI_ATTACK}mov{SE_M_REVERSAL}woul{SE_M_WATERFALL}yo{SE_M_DIVE}like?$"

NewSinjoh_HotSprings_Text_PLATutorConfirm:
	.string "You'{SE_M_WATERFALL}lik{SE_M_REVERSAL}t{SE_M_ATTRACT2}lear{SE_M_ATTRACT}{STR_VAR_1}?$"

NewSinjoh_HotSprings_Text_PLATutorWhichMon:
	.string "Whic{SE_M_TRI_ATTACK}POKeMO{SE_M_PSYBEAM2}shoul{SE_M_WATERFALL}lear{SE_M_ATTRACT}it?$"

NewSinjoh_HotSprings_Text_PLATutorDone:
	.string "Done{SE_M_DRAGON_RAGE}You{SE_M_SAND_TOMB}POKeMO{SE_M_PSYBEAM2}ha{SE_M_GRASSWHISTLE}mastered\n"
	.string "th{SE_M_REVERSAL}ancien{SE_M_SPIT_UP}technique.$"

NewSinjoh_HotSprings_Text_PLATutorComeBack:
	.string "Com{SE_M_REVERSAL}bac{SE_M_ENCORE2}anytime.$"

NewSinjoh_HotSprings_Text_PLAMove_VictoryDance:
	.string "VICTOR{SE_M_MOONLIGHT}DANCE$"

NewSinjoh_HotSprings_Text_PLAMove_MountainGale:
	.string "MOUNTAI{SE_M_PSYBEAM2}GALE$"

NewSinjoh_HotSprings_Text_PLAMove_BitterMalice:
	.string "BITTE{SE_M_MINIMIZE}MALICE$"

NewSinjoh_HotSprings_Text_PLAMove_SpringtideStorm:
	.string "SPRINGTID{SE_M_SWORDS_DANCE}STORM$"

NewSinjoh_HotSprings_Text_PLAMove_LunarBlessing:
	.string "LUNA{SE_M_MINIMIZE}BLESSING$"

NewSinjoh_HotSprings_Text_PLAMove_BleakwindStorm:
	.string "BLEAKWIN{SE_M_FAINT_ATTACK}STORM$"

NewSinjoh_HotSprings_Text_PLAMove_WildboltStorm:
	.string "WILDBOL{SE_M_SWIFT}STORM$"

NewSinjoh_HotSprings_Text_PLAMove_SandsearStorm:
	.string "SANDSEA{SE_M_MINIMIZE}STORM$"

NewSinjoh_HotSprings_Text_PLAMove_Shelter:
	.string "SHELTER$"

NewSinjoh_HotSprings_Text_PLAMove_EsperWing:
	.string "ESPE{SE_M_MINIMIZE}WING$"

NewSinjoh_HotSprings_Text_PLAMove_TakeHeart:
	.string "TAK{SE_M_SWORDS_DANCE}HEART$"

NewSinjoh_HotSprings_Text_PLAMove_MysticalPower:
	.string "MYSTICA{SE_M_BRICK_BREAK}POWER$"

NewSinjoh_HotSprings_Text_PLAMove_WaveCrash:
	.string "WAV{SE_M_SWORDS_DANCE}CRASH$"

NewSinjoh_HotSprings_Text_PLAMove_PowerShift:
	.string "POWE{SE_M_MINIMIZE}SHIFT$"

NewSinjoh_HotSprings_Text_PLAMove_Cancel:
	.string "CANCEL$"

NewSinjoh_HotSprings_EventScript_ActivateArcanine::
	lock
	setobjectxyperm 8, 16, 4
	playse 209
	getplayerxy 16385, 16386
	dofieldeffectsparkle 16385, 16386, 0
	waitfieldeffect 54
	playse 21
	applymovement2 255, J_Common_Movement_ExclamationMark
	delay 55
	waitmovement 255
	msgbox SinjohRuins_Lab_Text_PlayFlute, MSGBOX_YESNO
	closemessage
	goto_if_eq 32781, FALSE, SinjohRuins_Lab_EventScript_NoOp
	playbgm ((((558 + 1) + 0xAF) + 1) + 0x00), FALSE
	delay 200
	fadedefaultbgm
	addobject 8
	clearflag 9118
	applymovement2 8, NewSinjoh_HotSprings_Movement_ArcanineEntrance1
	delay 10
	playse 10
	playmoncry 994, 0
	waitmoncry
	waitmovement 0
	applymovement2 8, NewSinjoh_HotSprings_Movement_ArcanineEntrance2
	delay 10
	playmoncry 994, 0
	waitmoncry
	playse 10
	delay 20
	waitmovement 8
	setvar 32772, 1
	setvar 32773, 1
	setvar 32774, 5
	setvar 32775, 2
	special ShakeCamera
	setobjectxyperm 8, 16, 8
	setvar 20647, 2
	release
	end

NewSinjoh_HotSprings_Movement_ArcanineEntrance1:
	slide_down
	slide_down
	slide_down
	slide_down
	step_end

NewSinjoh_HotSprings_Movement_ArcanineEntrance2:
	walk_in_place_slow_down
	walk_in_place_slow_down
	jump_in_place_down
	step_end

NewSinjoh_HotSprings_EventScript_Arcanine::
	lock
	faceplayer
	playmoncry 994, 2
	waitmoncry
	setwildbossbattle species=994, level=80, item=ITEM_LOADED_DICE, move1_1=MOVE_ROCK_BLAST, move1_2=MOVE_WILD_CHARGE, move1_3=MOVE_RAGING_FURY move1_4=MOVE_PROTECT
	settotemboost B_POSITION_OPPONENT_LEFT, 1, 0, 2, 0, 0, 0
	setflag 2411
	setflag 2410
	setflag 2409
	setflag 8804
	dowildbattle
	specialvar 32781, GetBattleOutcome
	goto_if_eq 32781, 4, NewSinjoh_HotSprings_EventScript_ArcanineRan
	bufferspeciesname STR_VAR_1, 994
	msgbox SinjohRuins_Lab_Text_DropedItem, MSGBOX_DEFAULT
	giveitem ITEM_FLAME_PLATE
	addvar 20640, 1
	fadescreenswapbuffers 1
	removeobject 8
	setflag 9118
	fadescreenswapbuffers 0
	call_if_eq 20640, 3, SinjohRuins_Lab_EventScript_3Plates
	call_if_eq 20640, 6, SinjohRuins_Lab_EventScript_6Plates
	call_if_eq 20640, 9, SinjohRuins_Lab_EventScript_9Plates
	call_if_eq 20640, 12, SinjohRuins_Lab_EventScript_12Plates
	call_if_eq 20640, 15, SinjohRuins_Lab_EventScript_15Plates
	call_if_eq 20640, 16, SinjohRuins_Lab_EventScript_16Plates
	clearflag 2411
	clearflag 2410
	clearflag 2409
	clearflag 8804
	release
	end

NewSinjoh_HotSprings_EventScript_ArcanineRan::
	clearflag 2411
	clearflag 2410
	clearflag 2409
	clearflag 8804
	release
	end

NewSinjoh_HotSprings_EventScript_ActivateUrsaluna::
	lock
	setobjectxyperm 9, 52, 26
	playse 209
	getplayerxy 16385, 16386
	dofieldeffectsparkle 16385, 16386, 0
	waitfieldeffect 54
	playse 21
	applymovement2 255, J_Common_Movement_ExclamationMark
	delay 55
	waitmovement 255
	msgbox SinjohRuins_Lab_Text_PlayFlute, MSGBOX_YESNO
	closemessage
	goto_if_eq 32781, FALSE, SinjohRuins_Lab_EventScript_NoOp
	playbgm ((((558 + 1) + 0xAF) + 1) + 0x00), FALSE
	delay 200
	fadedefaultbgm
	addobject 9
	clearflag 9119
	applymovement2 9, NewSinjoh_HotSprings_Movement_UrsalunaEntrance1
	delay 10
	playse 10
	playmoncry 901, 0
	waitmoncry
	waitmovement 0
	applymovement2 9, NewSinjoh_HotSprings_Movement_UrsalunaEntrance2
	delay 10
	playmoncry 901, 0
	waitmoncry
	playse 10
	delay 20
	waitmovement 9
	setvar 32772, 1
	setvar 32773, 1
	setvar 32774, 5
	setvar 32775, 2
	special ShakeCamera
	setobjectxyperm 9, 52, 28
	setvar 20648, 2
	release
	end

NewSinjoh_HotSprings_Movement_UrsalunaEntrance1:
	jump_in_place_down
	walk_in_place_fast_down
	walk_in_place_fast_down
	step_end

NewSinjoh_HotSprings_Movement_UrsalunaEntrance2:
	jump_2_down
	walk_in_place_slow_down
	walk_in_place_slow_down
	jump_in_place_down
	step_end

NewSinjoh_HotSprings_EventScript_Ursaluna::
	lock
	faceplayer
	playmoncry 901, 2
	waitmoncry
	setwildbossbattle species=901, level=80, item=ITEM_EARTH_PLATE, move1_1=MOVE_EARTHQUAKE, move1_2=MOVE_AVALANCHE, move1_3=MOVE_BULK_UP move1_4=MOVE_GIGA_IMPACT
	settotemboost B_POSITION_OPPONENT_LEFT, 1, 0, 2, 0, 0, 0
	setflag 2411
	setflag 2410
	setflag 2409
	setflag 8804
	dowildbattle
	specialvar 32781, GetBattleOutcome
	goto_if_eq 32781, 4, NewSinjoh_HotSprings_EventScript_UrsalunaRan
	bufferspeciesname STR_VAR_1, 901
	msgbox SinjohRuins_Lab_Text_DropedItem, MSGBOX_DEFAULT
	giveitem ITEM_EARTH_PLATE
	addvar 20640, 1
	fadescreenswapbuffers 1
	removeobject 9
	setflag 9119
	fadescreenswapbuffers 0
	call_if_eq 20640, 3, SinjohRuins_Lab_EventScript_3Plates
	call_if_eq 20640, 6, SinjohRuins_Lab_EventScript_6Plates
	call_if_eq 20640, 9, SinjohRuins_Lab_EventScript_9Plates
	call_if_eq 20640, 12, SinjohRuins_Lab_EventScript_12Plates
	call_if_eq 20640, 15, SinjohRuins_Lab_EventScript_15Plates
	call_if_eq 20640, 16, SinjohRuins_Lab_EventScript_16Plates
	clearflag 2411
	clearflag 2410
	clearflag 2409
	clearflag 8804
	release
	end

NewSinjoh_HotSprings_EventScript_UrsalunaRan::
	clearflag 2411
	clearflag 2410
	clearflag 2409
	clearflag 8804
	release
	end

