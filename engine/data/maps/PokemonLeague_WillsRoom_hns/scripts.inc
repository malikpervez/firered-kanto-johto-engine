@ Johto (data/maps/PokemonLeague_WillsRoom_hns/scripts.inc), as built into the FireRed game.

PokemonLeague_WillsRoom_hns_MapScripts::
	map_script 2, EliteFourRoom_OnFrame
	map_script 5, PokemonLeague_WillsRoom_OnResume
	map_script 1, EliteFourRoom_OnLoad
	.byte 0

EliteFourRoom_OnLoad::
	call_if_eq 16384, 1, EliteFourRoom_CreateDoor
	end

EliteFourRoom_CreateDoor::
	setmetatile 5, 11, 0x29D, TRUE
	setmetatile 6, 11, 0x29E, TRUE
	setmetatile 7, 11, 0x29F, TRUE
	setmetatile 5, 12, 0x2A5, TRUE
	setmetatile 6, 12, 0x2A6, TRUE
	setmetatile 7, 12, 0x2A7, TRUE
	return

PokemonLeague_WillsRoom_OnResume::
	setvar 32772, 0
	special DoPokemonLeagueLightingEffect
	end

EliteFourRoom_OnFrame::
	map_script_2 16384, 0, EliteFourRoom_CloseDoor
	.2byte 0

EliteFourRoom_CloseDoor::
	lock
	setflag 2
	applymovement 255, J_Common_Movement_WalkUp1
	waitmovement 0
	applymovement 255, J_Common_Movement_WalkUp1
	waitmovement 0
	setmetatile 5, 11, 0x29D, TRUE
	setmetatile 6, 11, 0x29E, TRUE
	setmetatile 7, 11, 0x29F, TRUE
	setmetatile 5, 12, 0x2A5, TRUE
	setmetatile 6, 12, 0x2A6, TRUE
	setmetatile 7, 12, 0x2A7, TRUE
	playse 20
	setvar 32772, 1
	setvar 32773, 1
	setvar 32774, 4
	setvar 32775, 4
	special ShakeCamera
	waitstate
	special DrawWholeMapView
	setvar 16384, 1
	release
	end

PokemonLeague_WillsRoom_EventScript_Will::
	lock
	faceplayer
	goto_if_ge 20576, 2, PokemonLeague_WillsRoom_EventScript_WillDefeated
	goto_if_set 10399, PokemonLeague_WillsRoom_EventScript_WillRematch
	msgbox PokemonLeague_WillsRoom_Text_Before, MSGBOX_DEFAULT
	setflag 3
	setflag 5
	trainerbattle_no_intro 1457, PokemonLeague_WillsRoom_Text_Beaten
	goto PokemonLeague_WillsRoom_EventScript_WillOnDefeat

PokemonLeague_WillsRoom_EventScript_WillRematch::
	goto_if_unset 10400, PokemonLeague_WillsRoom_EventScript_WillRematchStandard
	goto_if_ge 20639, 13, PokemonLeague_WillsRoom_EventScript_WillRematchPostOBC

PokemonLeague_WillsRoom_EventScript_WillRematchStandard::
	msgbox PokemonLeague_WillsRoom_Text_RematchBefore, MSGBOX_DEFAULT
	setflag 3
	setflag 5
	trainerbattle_no_intro 1458, PokemonLeague_WillsRoom_Text_Beaten
	goto PokemonLeague_WillsRoom_EventScript_WillOnDefeat

PokemonLeague_WillsRoom_EventScript_WillRematchPostOBC::
	msgbox PokemonLeague_WillsRoom_Text_RematchBefore, MSGBOX_DEFAULT
	setflag 3
	setflag 5
	trainerbattle_no_intro 1669, PokemonLeague_WillsRoom_Text_Beaten
	goto PokemonLeague_WillsRoom_EventScript_WillOnDefeat

PokemonLeague_WillsRoom_EventScript_WillOnDefeat::
	clearflag 5
	msgbox PokemonLeague_WillsRoom_Text_Defeat, MSGBOX_DEFAULT
	closemessage
	setmetatile 6, 1, 0x28E, FALSE
	setmetatile 6, 2, 0x296, FALSE
	playse 20
	setvar 32772, 1
	setvar 32773, 1
	setvar 32774, 4
	setvar 32775, 4
	special ShakeCamera
	waitstate
	special DrawWholeMapView
	setvar 20576, 2
	release
	end

PokemonLeague_WillsRoom_EventScript_WillDefeated::
	msgbox PokemonLeague_WillsRoom_Text_Defeat, MSGBOX_DEFAULT
	closemessage
	release
	end

PokemonLeague_WillsRoom_Text_Before:
	.string "Welcom{SE_M_REVERSAL}t{SE_M_ATTRACT2}POKéMO{SE_M_PSYBEAM2}LEAGUE,\n"
	.string "{PLAYER}.\p"
	.string "Allo{SE_M_TWISTER}m{SE_M_REVERSAL}t{SE_M_ATTRACT2}introduc{SE_M_REVERSAL}myself.\n"
	.string "{SE_M_HEAL_BELL}a{SE_M_MILK_DRINK}WILL.\p"
	.string "{SE_M_HEAL_BELL}hav{SE_M_REVERSAL}traine{SE_M_WATERFALL}al{SE_M_BATON_PASS}aroun{SE_M_WATERFALL}the\n"
	.string "world{SE_M_SUPERSONIC}makin{SE_M_SANDSTORM}m{SE_M_YAWN}psychic\l"
	.string "POKéMO{SE_M_PSYBEAM2}powerful.\p"
	.string "And{SE_M_SUPERSONIC}a{SE_M_SPIT_UP}last{SE_M_SUPERSONIC}I'v{SE_M_REVERSAL}bee{SE_M_ATTRACT}accepted\n"
	.string "int{SE_M_ATTRACT2}th{SE_M_REVERSAL}ELIT{SE_M_SWORDS_DANCE}FOUR.\p"
	.string "{SE_M_HEAL_BELL}ca{SE_M_ATTRACT}onl{SE_M_YAWN}kee{SE_M_MORNING_SUN}gettin{SE_M_SANDSTORM}better!\p"
	.string "Losin{SE_M_SANDSTORM}i{SE_M_GRASSWHISTLE}no{SE_M_SPIT_UP}a{SE_M_ATTRACT}option!$"

PokemonLeague_WillsRoom_Text_Beaten:
	.string "I{SE_M_DIZZY_PUNCH}{SE_M_HEAL_BELL}can't{SE_M_DIZZY_PUNCH}believ{SE_M_REVERSAL}it…$"

PokemonLeague_WillsRoom_Text_Defeat:
	.string "Eve{SE_M_ATTRACT}thoug{SE_M_TRI_ATTACK}{SE_M_HEAL_BELL}wa{SE_M_GRASSWHISTLE}defeated{SE_M_SUPERSONIC}I\n"
	.string "won'{SE_M_SPIT_UP}chang{SE_M_REVERSAL}m{SE_M_YAWN}course.\p"
	.string "{SE_M_HEAL_BELL}wil{SE_M_BATON_PASS}continu{SE_M_REVERSAL}battlin{SE_M_SANDSTORM}unti{SE_M_BATON_PASS}I\n"
	.string "stan{SE_M_WATERFALL}abov{SE_M_REVERSAL}al{SE_M_BATON_PASS}trainers!\p"
	.string "Now{SE_M_SUPERSONIC}{PLAYER}{SE_M_SUPERSONIC}mov{SE_M_REVERSAL}o{SE_M_ATTRACT}and\n"
	.string "experienc{SE_M_REVERSAL}th{SE_M_REVERSAL}tru{SE_M_REVERSAL}ferocit{SE_M_YAWN}of\l"
	.string "th{SE_M_REVERSAL}ELIT{SE_M_SWORDS_DANCE}FOUR.$"

PokemonLeague_WillsRoom_Text_RematchBefore:
	.string "WILL{SE_M_HEAT_WAVE}Ah{SE_M_SUPERSONIC}welcom{SE_M_REVERSAL}back.\p"
	.string "{SE_M_HEAL_BELL}hav{SE_M_REVERSAL}foresee{SE_M_ATTRACT}thi{SE_M_GRASSWHISTLE}encounter.\p"
	.string "M{SE_M_YAWN}psychi{SE_M_HYPER_BEAM}POKéMO{SE_M_PSYBEAM2}and\n"
	.string "{SE_M_HEAL_BELL}hav{SE_M_REVERSAL}evolved{SE_M_SUPERSONIC}developing\l"
	.string "ne{SE_M_TWISTER}tactics.\p"
	.string "Prepar{SE_M_REVERSAL}yoursel{SE_M_ACID_ARMOR}fo{SE_M_SAND_TOMB}{SE_M_CHARGE}battl{SE_M_REVERSAL}of\n"
	.string "enhance{SE_M_WATERFALL}strateg{SE_M_YAWN}an{SE_M_WATERFALL}might.\p"
	.string "Le{SE_M_SPIT_UP}u{SE_M_GRASSWHISTLE}se{SE_M_REVERSAL}i{SE_M_ACID_ARMOR}you{SE_M_SAND_TOMB}foresight\n"
	.string "matche{SE_M_GRASSWHISTLE}mine.$"

