@ Johto (data/maps/LakeOfRage_hns/scripts.inc), as built into the FireRed game.

LakeOfRage_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LakeOfRage_OnTransition
	.byte 0

LakeOfRage_OnTransition::
	setflag JOHTO_FLAG_VISITED_LAKE_OF_RAGE
	call_if_lt JOHTO_VAR_MAHOGANY_TOWN_STATE, 2, LakeOfRage_EventScript_HideLois
	goto_if_lt JOHTO_VAR_MAHOGANY_TOWN_STATE, 14, LakeOfRage_EventScript_SetHighTide
	special UpdateShoalTideFlag
	goto_if_set JOHTO_FLAG_SYS_LAKE_OF_RAGE_TIDE, LakeOfRage_EventScript_SetHighTide
	goto LakeOfRage_EventScript_SetLowTide

LakeOfRage_EventScript_SetLowTide::
	setweather WEATHER_NONE
	setmaplayoutindex LAYOUT_LAKE_OF_RAGE_LOW_TIDE_HNS
	end

LakeOfRage_EventScript_SetHighTide::
	setmaplayoutindex LAYOUT_LAKE_OF_RAGE_HNS
	goto_if_lt JOHTO_VAR_MAHOGANY_TOWN_STATE, 14, LakeOfRage_EventScript_ThunderStorm
	random 2
	goto_if_eq VAR_RESULT, 1, LakeOfRage_EventScript_ThunderStorm
	end

LakeOfRage_EventScript_HideLois::
	setflag FLAG_TEMP_1
	return

LakeOfRage_EventScript_ThunderStorm::
	setweather WEATHER_RAIN_THUNDERSTORM
	end

LakeOfRage_EventScript_Pryce::
	lock
	faceplayer
	msgbox LakeOfRage_Text_Pryce, MSGBOX_DEFAULT
	closemessage
	fadescreenswapbuffers FADE_TO_BLACK
	setflag JOHTO_FLAG_HIDE_LAKE_PRYCE
	removeobject LOCALID_LAKE_PRYCE
	fadescreenswapbuffers FADE_FROM_BLACK
	clearflag JOHTO_FLAG_HIDE_DOJO_PRYCE
	release
	end

LakeOfRage_Text_Pryce:
	.string "{PLAYER}.\p"
	.string "Eve{SE_M_ATTRACT}here{SE_M_SUPERSONIC}th{SE_M_REVERSAL}col{SE_M_WATERFALL}keep{SE_M_GRASSWHISTLE}m{SE_M_REVERSAL}sharp.\p"
	.string "I{SE_M_ACID_ARMOR}yo{SE_M_DIVE}wis{SE_M_TRI_ATTACK}t{SE_M_ATTRACT2}battl{SE_M_REVERSAL}again{SE_M_SUPERSONIC}come\n"
	.string "t{SE_M_ATTRACT2}th{SE_M_REVERSAL}FIGHTIN{SE_M_SWAGGER}DOJO.$"

LakeOfRage_EventScript_Gramps::
	goto_if_ge JOHTO_VAR_MAHOGANY_TOWN_STATE, 14, LakeOfRage_EventScript_Gramps2
	msgbox LakeOfRage_Text_Gramps, MSGBOX_NPC
	end

LakeOfRage_EventScript_Gramps2::
	msgbox LakeOfRage_Text_GrampsCleared, MSGBOX_NPC
	end

LakeOfRage_EventScript_Lass::
	msgbox LakeOfRage_Text_CooltrainerF, MSGBOX_NPC
	end

LakeOfRage_EventScript_Nerd::
	msgbox LakeOfRage_Text_SuperNerd, MSGBOX_NPC
	end

LakeOfRage_EventScript_Andre::
	trainerbattle_single TRAINER_JOHTO_ANDRE_HNS, LakeOfRage_Text_FisherAndreSeen, LakeOfRage_Text_FisherAndreBeaten
	msgbox LakeOfRage_Text_FisherAndreAfter, MSGBOX_AUTOCLOSE
	end

LakeOfRage_EventScript_Raymond::
	trainerbattle_single TRAINER_JOHTO_RAYMOND_HNS, LakeOfRage_Text_FisherRaymondSeen, LakeOfRage_Text_FisherRaymondBeaten
	msgbox LakeOfRage_Text_FisherRaymondAfter, MSGBOX_AUTOCLOSE
	end

LakeOfRage_EventScript_Aaron::
	trainerbattle_single TRAINER_JOHTO_AARON_HNS, LakeOfRage_Text_CooltrainermAaronSeen, LakeOfRage_Text_CooltrainermAaronBeaten
	msgbox LakeOfRage_Text_CooltrainermAaronAfter, MSGBOX_AUTOCLOSE
	end

LakeOfRage_EventScript_Lois::
	trainerbattle_single TRAINER_JOHTO_LOIS_HNS, LakeOfRage_Text_CooltrainerfLoisSeen, LakeOfRage_Text_CooltrainerfLoisBeaten
	msgbox LakeOfRage_Text_CooltrainerfLoisAfter, MSGBOX_AUTOCLOSE
	end

LakeOfRage_EventScript_Gyarados::
	lock
	faceplayer
	msgbox LakeOfRage_Text_GyaradosCry, MSGBOX_DEFAULT
	waitse
	playmoncry SPECIES_GYARADOS, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setwildbattleshiny SPECIES_GYARADOS, 30
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, LakeOfRage_EventScript_Defeated_Gyarados
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, LakeOfRage_EventScript_Ran_Gyarados
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, LakeOfRage_EventScript_Ran_Gyarados

LakeOfRage_EventScript_Defeated_Gyarados::
	setflag JOHTO_FLAG_HIDE_LAKE_OF_RAGE_GYARADOS
	clearflag FLAG_TEMP_1
	removeobject LOCALID_LAKEOFRAGE_GYARADOS
	clearflag JOHTO_FLAG_HIDE_LAKE_OF_RAGE_LANCE
	addobject LOCALID_LAKEOFRAGE_LANCE
	giveitem ITEM_RED_SCALE
	setobjectxyperm LOCALID_LAKEOFRAGE_OLDMAN, 32, 38
	setvar JOHTO_VAR_MAHOGANY_TOWN_STATE, 2
	release
	end

LakeOfRage_EventScript_Ran_Gyarados::
	release
	end

LakeOfRage_EventScript_Item_Full_Restore::
	finditem ITEM_FULL_RESTORE
	end

LakeOfRage_EventScript_Item_Secret_Power::
	finditem ITEM_TM_SECRET_POWER
	end

LakeOfRage_EventScript_Item_Red_Flute::
	finditem ITEM_RED_FLUTE
	end

LakeOfRage_EventScript_Dragonite::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_DRAGONITE, CRY_MODE_NORMAL
	msgbox LakeOfRage_Text_Dragonite, MSGBOX_DEFAULT
	waitmoncry
	turnobject LOCALID_LAKEOFRAGE_DRAGONITE, DIR_WEST
	release
	end

LakeOfRage_EventScript_Lance::
	lock
	goto_if_eq JOHTO_VAR_MAHOGANY_TOWN_STATE, 3, LakeOfRage_EventScript_Lance_Return
	msgbox LakeOfRage_Text_LanceForcedToEvolve, MSGBOX_DEFAULT
	closemessage
	delay 20
	faceplayer
	turnobject LOCALID_LAKEOFRAGE_OLDMAN, DIR_WEST
	msgbox LakeOfRage_Text_LanceIntro2, MSGBOX_DEFAULT
	setvar JOHTO_VAR_MAHOGANY_TOWN_STATE, 3
	msgbox LakeOfRage_Text_LanceIntro3, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, LakeOfRage_EventScript_LancDeclined

LakeOfRage_EventScript_LanceAccept::
	lock
	msgbox LakeOfRage_Text_LanceRadioSignal, MSGBOX_DEFAULT
	closemessage
	goto_if_eq VAR_FACING, DIR_NORTH, LakeOfRage_EventScript_LanceDragoniteLeaveNorth
	applymovement LOCALID_LAKEOFRAGE_LANCE, LakeOfRage_Movement_LanceLeave
	applymovement LOCALID_LAKEOFRAGE_DRAGONITE, LakeOfRage_Movement_DragoniteLeave
	waitmovement LOCALID_LAKEOFRAGE_LANCE
	waitmovement LOCALID_LAKEOFRAGE_DRAGONITE

LakeOfRage_EventScript_EndScene::
	setflag JOHTO_FLAG_HIDE_LAKE_OF_RAGE_LANCE
	removeobject LOCALID_LAKEOFRAGE_LANCE
	removeobject LOCALID_LAKEOFRAGE_DRAGONITE
	setvar JOHTO_VAR_MAHOGANY_TOWN_STATE, 4
	clearflag JOHTO_FLAG_HIDE_MAHOGANY_TOWN_SHOP_NPCS
	release
	end

LakeOfRage_EventScript_Lance_Return::
	lock
	faceplayer
	msgbox LakeOfRage_Text_LanceAskHelp, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, LakeOfRage_EventScript_LanceAccept
	goto_if_eq VAR_RESULT, FALSE, LakeOfRage_EventScript_LancDeclined

LakeOfRage_EventScript_LancDeclined::
	msgbox LakeOfRage_Text_LanceRefused, MSGBOX_DEFAULT
	closemessage
	release
	end

LakeOfRage_EventScript_LanceDragoniteLeaveNorth::
	applymovement LOCALID_LAKEOFRAGE_LANCE, LakeOfRage_Movement_LanceLeaveNorth
	applymovement LOCALID_LAKEOFRAGE_DRAGONITE, LakeOfRage_Movement_DragoniteLeaveNorth
	waitmovement LOCALID_LAKEOFRAGE_LANCE
	waitmovement LOCALID_LAKEOFRAGE_DRAGONITE
	goto LakeOfRage_EventScript_EndScene

LakeOfRage_Movement_LanceLeaveNorth:
	walk_left
	walk_down
	delay_8
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

LakeOfRage_Movement_DragoniteLeaveNorth:
	delay_16
	delay_16
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

LakeOfRage_Movement_LanceLeave:
	walk_down
	delay_8
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

LakeOfRage_Movement_DragoniteLeave:
	delay_16
	delay_16
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

LakeOfRage_Text_Dragonite:
	.string "DRAGONITE{SE_M_HEAT_WAVE}Gyafooha!$"

LakeOfRage_Text_LanceForcedToEvolve:
	.string "Thi{SE_M_GRASSWHISTLE}lak{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}ful{SE_M_BATON_PASS}o{SE_M_ACID_ARMOR}GYARADOS\n"
	.string "bu{SE_M_SPIT_UP}nothin{SE_M_SANDSTORM}else…\p"
	.string "S{SE_M_ATTRACT2}th{SE_M_REVERSAL}MAGIKAR{SE_M_PETAL_DANCE}ar{SE_M_REVERSAL}bein{SE_M_SANDSTORM}forced\n"
	.string "t{SE_M_ATTRACT2}evolve…$"

LakeOfRage_Text_LanceIntro1:
	.string "Di{SE_M_WATERFALL}yo{SE_M_DIVE}com{SE_M_REVERSAL}her{SE_M_REVERSAL}becaus{SE_M_REVERSAL}of\n"
	.string "th{SE_M_REVERSAL}rumors?\p"
	.string "You'r{SE_M_REVERSAL}{PLAYER}{SE_M_SING}I'{SE_M_MILK_DRINK}LANCE{SE_M_SUPERSONIC}a\n"
	.string "traine{SE_M_SAND_TOMB}lik{SE_M_REVERSAL}you.$"

LakeOfRage_Text_LanceIntro2:
	.string "Thi{SE_M_GRASSWHISTLE}ma{SE_M_ATTRACT}her{SE_M_REVERSAL}informe{SE_M_WATERFALL}m{SE_M_REVERSAL}of\n"
	.string "som{SE_M_REVERSAL}rumors.\p"
	.string "S{SE_M_ATTRACT2}w{SE_M_REVERSAL}cam{SE_M_REVERSAL}t{SE_M_ATTRACT2}investigate…$"

LakeOfRage_Text_LanceIntro3:
	.string "{SE_M_HEAL_BELL}sa{SE_M_TWISTER}th{SE_M_REVERSAL}wa{SE_M_YAWN}yo{SE_M_DIVE}battled\n"
	.string "earlier{SE_M_SUPERSONIC}{PLAYER}.\p"
	.string "{SE_M_HEAL_BELL}ca{SE_M_ATTRACT}tel{SE_M_BATON_PASS}tha{SE_M_SPIT_UP}you'r{SE_M_REVERSAL}{SE_M_CHARGE}trainer\n"
	.string "wit{SE_M_TRI_ATTACK}considerabl{SE_M_REVERSAL}skill.\p"
	.string "I{SE_M_ACID_ARMOR}yo{SE_M_DIVE}don'{SE_M_SPIT_UP}mind{SE_M_SUPERSONIC}coul{SE_M_WATERFALL}yo{SE_M_DIVE}help\n"
	.string "u{SE_M_GRASSWHISTLE}investigate?$"

LakeOfRage_Text_LanceRadioSignal:
	.string "LANCE{SE_M_HEAT_WAVE}Excellent!\p"
	.string "I{SE_M_SPIT_UP}seem{SE_M_GRASSWHISTLE}tha{SE_M_SPIT_UP}th{SE_M_REVERSAL}LAKE'{SE_M_GRASSWHISTLE}MAGIKARP\n"
	.string "ar{SE_M_REVERSAL}bein{SE_M_SANDSTORM}force{SE_M_WATERFALL}t{SE_M_ATTRACT2}evolve.\p"
	.string "{SE_M_BONEMERANG}mysteriou{SE_M_GRASSWHISTLE}radi{SE_M_ATTRACT2}broadcast\n"
	.string "comin{SE_M_SANDSTORM}fro{SE_M_MILK_DRINK}MAHOGAN{SE_M_MOONLIGHT}i{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}cause.\p"
	.string "We'l{SE_M_BATON_PASS}b{SE_M_REVERSAL}waitin{SE_M_SANDSTORM}fo{SE_M_SAND_TOMB}you,\n"
	.string "{PLAYER}.$"

LakeOfRage_Text_LanceRefused:
	.string "Oh{SE_M_DIZZY_PUNCH}Well{SE_M_SUPERSONIC}i{SE_M_ACID_ARMOR}yo{SE_M_DIVE}chang{SE_M_REVERSAL}you{SE_M_SAND_TOMB}mind,\n"
	.string "pleas{SE_M_REVERSAL}hel{SE_M_MORNING_SUN}us.$"

LakeOfRage_Text_LanceAskHelp:
	.string "LANCE{SE_M_HEAT_WAVE}Hm{SE_M_SING}Ar{SE_M_REVERSAL}yo{SE_M_DIVE}goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}help\n"
	.string "us?$"

LakeOfRage_Text_GyaradosCry:
	.string "GYARADOS{SE_M_HEAT_WAVE}Gyashaa!$"

LakeOfRage_Text_Gramps:
	.string "Th{SE_M_REVERSAL}GYARADO{SE_M_SKETCH}ar{SE_M_REVERSAL}angry!\p"
	.string "It'{SE_M_GRASSWHISTLE}{SE_M_CHARGE}ba{SE_M_WATERFALL}omen!$"

LakeOfRage_Text_GrampsCleared:
	.string "Hahah{SE_M_DRAGON_RAGE}Th{SE_M_REVERSAL}MAGIKAR{SE_M_PETAL_DANCE}ar{SE_M_REVERSAL}biting!$"

LakeOfRage_Text_SuperNerd:
	.string "{SE_M_HEAL_BELL}hear{SE_M_WATERFALL}thi{SE_M_GRASSWHISTLE}lak{SE_M_REVERSAL}wa{SE_M_GRASSWHISTLE}mad{SE_M_REVERSAL}by\n"
	.string "rampagin{SE_M_SANDSTORM}GYARADOS.\p"
	.string "{SE_M_HEAL_BELL}wonde{SE_M_SAND_TOMB}i{SE_M_ACID_ARMOR}ther{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}any\n"
	.string "connectio{SE_M_ATTRACT}t{SE_M_ATTRACT2}thei{SE_M_SAND_TOMB}mas{SE_M_GRASSWHISTLE}outbreak\l"
	.string "now?$"

LakeOfRage_Text_CooltrainerF:
	.string "Di{SE_M_WATERFALL}m{SE_M_YAWN}eye{SE_M_GRASSWHISTLE}deceiv{SE_M_REVERSAL}me{SE_M_SING}{SE_M_HEAL_BELL}sa{SE_M_TWISTER}a\n"
	.string "re{SE_M_WATERFALL}GYARADO{SE_M_SKETCH}i{SE_M_ATTRACT}th{SE_M_REVERSAL}LAKE…\p"
	.string "Bu{SE_M_SPIT_UP}{SE_M_HEAL_BELL}though{SE_M_SPIT_UP}GYARADO{SE_M_SKETCH}were\n"
	.string "usuall{SE_M_YAWN}blue?$"

LakeOfRage_Text_FisherAndreSeen:
	.string "Le{SE_M_SPIT_UP}m{SE_M_REVERSAL}battl{SE_M_REVERSAL}wit{SE_M_TRI_ATTACK}th{SE_M_REVERSAL}POKéMO{SE_M_PSYBEAM2}I\n"
	.string "jus{SE_M_SPIT_UP}caught!$"

LakeOfRage_Text_FisherAndreBeaten:
	.string "{SE_M_HEAL_BELL}migh{SE_M_SPIT_UP}b{SE_M_REVERSAL}a{SE_M_ATTRACT}exper{SE_M_SPIT_UP}angler{SE_M_SUPERSONIC}but\n"
	.string "{SE_M_HEAL_BELL}stin{SE_M_ENCORE2}a{SE_M_GRASSWHISTLE}{SE_M_CHARGE}POKéMO{SE_M_PSYBEAM2}trainer…$"

LakeOfRage_Text_FisherAndreAfter:
	.string "{SE_M_HEAL_BELL}won'{SE_M_SPIT_UP}los{SE_M_REVERSAL}a{SE_M_GRASSWHISTLE}a{SE_M_ATTRACT}angler{SE_M_DRAGON_RAGE}{SE_M_HEAL_BELL}catch\n"
	.string "POKéMO{SE_M_PSYBEAM2}al{SE_M_BATON_PASS}day.$"

LakeOfRage_Text_FisherRaymondSeen:
	.string "N{SE_M_ATTRACT2}matte{SE_M_SAND_TOMB}wha{SE_M_SPIT_UP}{SE_M_HEAL_BELL}do{SE_M_SUPERSONIC}al{SE_M_BATON_PASS}{SE_M_HEAL_BELL}catch\n"
	.string "ar{SE_M_REVERSAL}th{SE_M_REVERSAL}sam{SE_M_REVERSAL}POKéMON…$"

LakeOfRage_Text_FisherRaymondBeaten:
	.string "M{SE_M_YAWN}line'{SE_M_GRASSWHISTLE}al{SE_M_BATON_PASS}tangle{SE_M_WATERFALL}up…$"

LakeOfRage_Text_FisherRaymondAfter:
	.string "Wh{SE_M_YAWN}can'{SE_M_SPIT_UP}{SE_M_HEAL_BELL}catc{SE_M_TRI_ATTACK}an{SE_M_YAWN}good\n"
	.string "POKéMON?$"

LakeOfRage_Text_CooltrainermAaronSeen:
	.string "I{SE_M_ACID_ARMOR}{SE_M_CHARGE}traine{SE_M_SAND_TOMB}spot{SE_M_GRASSWHISTLE}anothe{SE_M_SAND_TOMB}trainer,\n"
	.string "h{SE_M_REVERSAL}ha{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}mak{SE_M_REVERSAL}{SE_M_CHARGE}challenge.\p"
	.string "Tha{SE_M_SPIT_UP}i{SE_M_GRASSWHISTLE}ou{SE_M_SAND_TOMB}destiny.$"

LakeOfRage_Text_CooltrainermAaronBeaten:
	.string "Whew{SE_M_DIZZY_PUNCH}Goo{SE_M_WATERFALL}battle.$"

LakeOfRage_Text_CooltrainermAaronAfter:
	.string "POKéMO{SE_M_PSYBEAM2}an{SE_M_WATERFALL}thei{SE_M_SAND_TOMB}traine{SE_M_SAND_TOMB}become\n"
	.string "powerfu{SE_M_BATON_PASS}throug{SE_M_TRI_ATTACK}constan{SE_M_SPIT_UP}battling.$"

LakeOfRage_Text_CooltrainerfLoisSeen:
	.string "Wha{SE_M_SPIT_UP}happene{SE_M_WATERFALL}t{SE_M_ATTRACT2}th{SE_M_REVERSAL}red\n"
	.string "GYARADOS?\p"
	.string "It'{SE_M_GRASSWHISTLE}gone?\p"
	.string "Oh{SE_M_SUPERSONIC}darn{SE_M_PERISH_SONG}{SE_M_HEAL_BELL}cam{SE_M_REVERSAL}her{SE_M_REVERSAL}for\n"
	.string "nothing?\p"
	.string "{SE_M_HEAL_BELL}know--let'{SE_M_GRASSWHISTLE}battle!$"

LakeOfRage_Text_CooltrainerfLoisBeaten:
	.string "Goo{SE_M_WATERFALL}going!$"

LakeOfRage_Text_CooltrainerfLoisAfter:
	.string "Com{SE_M_REVERSAL}t{SE_M_ATTRACT2}thin{SE_M_ENCORE2}o{SE_M_ACID_ARMOR}it{SE_M_SUPERSONIC}I'v{SE_M_REVERSAL}see{SE_M_ATTRACT}a\n"
	.string "pin{SE_M_ENCORE2}BUTTERFREE.$"

LakeOfRage_EventScript_Wesley::
	lock
	faceplayer
	goto_if_set JOHTO_FLAG_GOT_BLACK_BELT, LakeOfRage_EventScript_WesleyCompleted
	msgbox LakeOfRage_Text_MeetWesley, MSGBOX_DEFAULT
	closemessage
	multichoice 20, 0, MULTI_DAYS_OF_WEEK, FALSE
	switch VAR_RESULT
	case 0, LakeOfRage_EventScript_WesleyNope
	case 1, LakeOfRage_EventScript_WesleyNope
	case 2, LakeOfRage_EventScript_WesleyNope
	case 3, LakeOfRage_EventScript_WesleyYes
	case 4, LakeOfRage_EventScript_WesleyNope
	case 5, LakeOfRage_EventScript_WesleyNope
	case 6, LakeOfRage_EventScript_WesleyNope
	case 7 LakeOfRage_EventScript_WesleyCancel
	case MULTI_B_PRESSED, LakeOfRage_EventScript_WesleyCancel
	closemessage
	release
	end

LakeOfRage_EventScript_WesleyYes::
	msgbox LakeOfRage_Text_WesleyGivesGift, MSGBOX_DEFAULT
	giveitem ITEM_BLACK_BELT
	goto_if_eq VAR_RESULT, FALSE, J_Common_EventScript_ShowBagIsFull
	setflag JOHTO_FLAG_GOT_BLACK_BELT
	msgbox LakeOfRage_Text_WesleyGaveGift, MSGBOX_DEFAULT
	closemessage
	release
	end

LakeOfRage_EventScript_WesleyNope::
	msgbox LakeOfRage_Text_WesleyNotWednesday, MSGBOX_DEFAULT
	closemessage
	release
	end

LakeOfRage_EventScript_WesleyCancel::
	closemessage
	release
	end

LakeOfRage_EventScript_WesleyCompleted::
	msgbox LakeOfRage_Text_WesleyWednesday, MSGBOX_DEFAULT
	closemessage
	release
	end

LakeOfRage_Text_MeetWesley:
	.string "WESLEY{SE_M_HEAT_WAVE}Well{SE_M_SUPERSONIC}ho{SE_M_TWISTER}d{SE_M_ATTRACT2}yo{SE_M_DIVE}do?\p"
	.string "I'{SE_M_MILK_DRINK}{SE_M_CHARGE}membe{SE_M_SAND_TOMB}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}WEEKDA{SE_M_MOONLIGHT}family!\n"
	.string "Ca{SE_M_ATTRACT}yo{SE_M_DIVE}gues{SE_M_GRASSWHISTLE}m{SE_M_YAWN}favorit{SE_M_REVERSAL}day?$"

LakeOfRage_Text_WesleyGivesGift:
	.string "Please{SE_M_WATERFALL}t{SE_M_ATTRACT2}mee{SE_M_SPIT_UP}you{SE_M_PERISH_SONG}Pleas{SE_M_REVERSAL}tak{SE_M_REVERSAL}a\n"
	.string "souvenir.$"

LakeOfRage_Text_WesleyGaveGift:
	.string "WESLEY{SE_M_HEAT_WAVE}BLAC{SE_M_SNORE}BEL{SE_M_SWIFT}beef{SE_M_GRASSWHISTLE}u{SE_M_MORNING_SUN}the\n"
	.string "powe{SE_M_SAND_TOMB}o{SE_M_ACID_ARMOR}fightin{SE_M_SANDSTORM}moves.$"

LakeOfRage_Text_WesleyWednesday:
	.string "WESLEY{SE_M_HEAT_WAVE}Sinc{SE_M_REVERSAL}yo{SE_M_DIVE}foun{SE_M_WATERFALL}me{SE_M_SUPERSONIC}you\n"
	.string "mus{SE_M_SPIT_UP}hav{SE_M_REVERSAL}me{SE_M_SPIT_UP}m{SE_M_YAWN}brother{SE_M_GRASSWHISTLE}and\l"
	.string "sisters.\p"
	.string "O{SE_M_SAND_TOMB}di{SE_M_WATERFALL}yo{SE_M_DIVE}jus{SE_M_SPIT_UP}ge{SE_M_SPIT_UP}lucky?$"

LakeOfRage_Text_WesleyNotWednesday:
	.string "WESLEY{SE_M_HEAT_WAVE}No{SE_M_SPIT_UP}exactly...$"

LakeOfRage_EventScript_Sign1::
	msgbox LakeOfRage_Text_Sign, MSGBOX_SIGN
	end

LakeOfRage_EventScript_Sign2::
	msgbox LakeOfRage_Text_FishingGuruSign, MSGBOX_SIGN
	end

LakeOfRage_Text_Sign:
	.string "LAK{SE_M_SWORDS_DANCE}O{SE_M_LEER}RAGE,\n"
	.string "als{SE_M_ATTRACT2}know{SE_M_ATTRACT}a{SE_M_GRASSWHISTLE}GYARADO{SE_M_SKETCH}LAKE.$"

LakeOfRage_Text_FishingGuruSign:
	.string "FISHIN{SE_M_SWAGGER}GURU'{SE_M_SKETCH}HOUSE$"

