@ Johto (data/maps/MtSilver_1F_WaterfallRoom_hns/scripts.inc), as built into the FireRed game.

MtSilver_1F_WaterfallRoom_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MtSilver_1F_WaterfallRoom_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, MtSilver_1F_WaterfallRoom_OnWarp
	map_script MAP_SCRIPT_ON_FRAME_TABLE, MtSilver_1F_WaterfallRoom_OnFrame
	map_script MAP_SCRIPT_ON_RESUME, MtSilver_1F_WaterfallRoom_OnResume
	.byte 0

MtSilver_1F_WaterfallRoom_OnResume::
	callnative SetTimeBasedEncounters
	setescapewarp MAP_MT_SILVER_OUTSIDE_HNS, 17, 8
	end

MtSilver_1F_WaterfallRoom_OnWarp::
	map_script_2 JOHTO_VAR_SINJOH_STORYLINE, 1, MtSilver_1F_WaterfallRoom_TurnPlayer
	.2byte 0

MtSilver_1F_WaterfallRoom_TurnPlayer::
	turnobject LOCALID_PLAYER, DIR_WEST
	end

MtSilver_1F_WaterfallRoom_OnFrame::
	map_script_2 JOHTO_VAR_SINJOH_STORYLINE, 1, MtSilver_1F_WaterfallRoom_Scientist_Scene
	.2byte 0

MtSilver_1F_WaterfallRoom_Scientist_Scene::
	msgbox MtSilver_1F_WaterfallRoom_Text_Scientist, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_MT_SILVER_1F_WATERFALL_ROOM_SCIENTIST, MtSilver_1F_Movement_Scientist
	playse SE_LEDGE
	waitmovement 0
	removeobject LOCALID_MT_SILVER_1F_WATERFALL_ROOM_SCIENTIST
	setflag JOHTO_FLAG_MT_SILVER_1F_HIDE_SCIENTIST
	setvar JOHTO_VAR_SINJOH_STORYLINE, 2
	release
	end

MtSilver_1F_WaterfallRoom_Text_Scientist:
	.string "Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}entranc{SE_M_REVERSAL}t{SE_M_ATTRACT2}the\n"
	.string "unexplore{SE_M_WATERFALL}branch..{SE_M_PERISH_SONG}{PAUSE}Ô{PAUSE}Ô{PAUSE}Ô\p"
	.string "Doe{SE_M_GRASSWHISTLE}i{SE_M_SPIT_UP}fee{SE_M_BATON_PASS}col{SE_M_WATERFALL}her{SE_M_REVERSAL}t{SE_M_ATTRACT2}you?\p"
	.string "Okay{SE_M_SUPERSONIC}I'{SE_M_MILK_DRINK}goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}leav{SE_M_REVERSAL}now.\p"
	.string "Goo{SE_M_WATERFALL}luck!$"

MtSilver_1F_Movement_Scientist:
	jump_2_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

MtSilver_1F_WaterfallRoom_OnTransition:
	callnative SetTimeBasedEncounters
	setescapewarp MAP_MT_SILVER_OUTSIDE_HNS, 17, 8
	end

MtSilver_1F_WaterfallRoom_EventScript_MaxPotion::
	finditem ITEM_MAX_POTION
	end

MtSilver_1F_WaterfallRoom_EventScript_DireHit::
	finditem ITEM_DIRE_HIT
	end

MtSilver_1F_WaterfallRoom_EventScript_FullRestore::
	finditem ITEM_FULL_RESTORE
	end

MtSilver_1F_WaterfallRoom_EventScript_UltraBall::
	finditem ITEM_ULTRA_BALL
	end

MtSilver_1F_WaterfallRoom_EventScript_SpellTag::
	finditem ITEM_SPELL_TAG
	end

