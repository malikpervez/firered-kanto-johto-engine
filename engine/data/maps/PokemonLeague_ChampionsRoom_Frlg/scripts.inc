PokemonLeague_ChampionsRoom_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, PokemonLeague_ChampionsRoom_OnWarp
	map_script MAP_SCRIPT_ON_RESUME, PokemonLeague_ChampionsRoom_OnResume
	map_script MAP_SCRIPT_ON_FRAME_TABLE, PokemonLeague_ChampionsRoom_OnFrame
	.byte 0

PokemonLeague_ChampionsRoom_OnResume::
	setvar VAR_0x8004, 4
	call PokemonLeague_EventScript_DoLightingEffect
	call_if_eq VAR_STARTER_MON, 2, PokemonLeague_ChampionsRoom_EventScript_CheckStopTriggerSquirtle
	call_if_eq VAR_STARTER_MON, 1, PokemonLeague_ChampionsRoom_EventScript_CheckStopTriggerBulbasaur
	call_if_eq VAR_STARTER_MON, 0, PokemonLeague_ChampionsRoom_EventScript_CheckStopTriggerCharmander
	end

PokemonLeague_ChampionsRoom_EventScript_CheckStopTriggerSquirtle::
	goto_if_defeated TRAINER_CHAMPION_FIRST_SQUIRTLE, PokemonLeague_ChampionsRoom_EventScript_StopSceneTrigger
	goto_if_defeated TRAINER_CHAMPION_REMATCH_SQUIRTLE, PokemonLeague_ChampionsRoom_EventScript_StopSceneTrigger
	return

PokemonLeague_ChampionsRoom_EventScript_CheckStopTriggerBulbasaur::
	goto_if_defeated TRAINER_CHAMPION_FIRST_BULBASAUR, PokemonLeague_ChampionsRoom_EventScript_StopSceneTrigger
	goto_if_defeated TRAINER_CHAMPION_REMATCH_BULBASAUR, PokemonLeague_ChampionsRoom_EventScript_StopSceneTrigger
	return

PokemonLeague_ChampionsRoom_EventScript_CheckStopTriggerCharmander::
	goto_if_defeated TRAINER_CHAMPION_FIRST_CHARMANDER, PokemonLeague_ChampionsRoom_EventScript_StopSceneTrigger
	goto_if_defeated TRAINER_CHAMPION_REMATCH_CHARMANDER, PokemonLeague_ChampionsRoom_EventScript_StopSceneTrigger
	return

PokemonLeague_ChampionsRoom_EventScript_StopSceneTrigger::
	setvar VAR_TEMP_1, 1
	return

PokemonLeague_ChampionsRoom_OnWarp::
	map_script_2 VAR_TEMP_1, 0, PokemonLeague_ChampionsRoom_EventScript_TurnPlayerNorth
	.2byte 0

PokemonLeague_ChampionsRoom_EventScript_TurnPlayerNorth::
	turnobject LOCALID_PLAYER, DIR_NORTH
	end

PokemonLeague_ChampionsRoom_OnFrame::
	map_script_2 VAR_TEMP_1, 0, PokemonLeague_ChampionsRoom_EventScript_EnterRoom
	.2byte 0

PokemonLeague_ChampionsRoom_EventScript_EnterRoom::
	lockall
	textcolor NPC_TEXT_COLOR_MALE
	setflag FLAG_TEMP_2
	applymovement LOCALID_PLAYER, PokemonLeague_ChampionsRoom_Movement_PlayerEnter
	waitmovement 0
	delay 20
	call_if_unset FLAG_SYS_GAME_CLEAR, PokemonLeague_ChampionsRoom_EventScript_Intro
	call_if_set FLAG_SYS_GAME_CLEAR, PokemonLeague_ChampionsRoom_EventScript_RematchIntro
	setflag FLAG_TEMP_3
	setflag FLAG_TEMP_5
	savebgm MUS_VICTORY_GYM_LEADER
	call_if_unset FLAG_IS_CHAMPION, PokemonLeague_ChampionsRoom_EventScript_Battle
	call_if_set FLAG_IS_CHAMPION, PokemonLeague_ChampionsRoom_EventScript_Rematch
	setflag FLAG_TEMP_4
	clearflag FLAG_TEMP_5
	setflag FLAG_DEFEATED_CHAMP
	setflag FLAG_TEMP_4
#ifdef FIRERED
	call_if_unset FLAG_SYS_GAME_CLEAR, CG_ChampionOriginalPostBattle
	call_if_set FLAG_SYS_GAME_CLEAR, CG_ChampionResearchPostBattle
#else
	msgbox PokemonLeague_ChampionsRoom_Text_PostBattle
#endif
	playbgm MUS_RG_SLOW_PALLET, 0
	addobject LOCALID_CHAMPIONS_ROOM_PROF_OAK
	msgbox PokemonLeague_ChampionsRoom_Text_OakPlayer
	closemessage
	applymovement LOCALID_PLAYER, PokemonLeague_ChampionsRoom_Movement_PlayerWatchOakEnter
	applymovement LOCALID_KANTO_CHAMPIONS_ROOM_RIVAL, PokemonLeague_ChampionsRoom_Movement_RivalWatchOakEnter
	applymovement LOCALID_CHAMPIONS_ROOM_PROF_OAK, PokemonLeague_ChampionsRoom_Movement_OakEnter
	waitmovement 0
	delay 25
#ifdef FIRERED
	callnative Special_CharacterStarterSpecies, requests_effects=1
#else
	specialvar VAR_RESULT, GetStarterPokemon
#endif
	bufferspeciesname STR_VAR_1, VAR_RESULT
	msgbox PokemonLeague_ChampionsRoom_Text_OakCongratulations
	applymovement LOCALID_CHAMPIONS_ROOM_PROF_OAK, Common_Movement_WalkInPlaceFasterRight
	applymovement LOCALID_KANTO_CHAMPIONS_ROOM_RIVAL, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
#ifdef FIRERED
	call_if_unset FLAG_SYS_GAME_CLEAR, CG_ChampionOriginalOakLesson
	call_if_set FLAG_SYS_GAME_CLEAR, CG_ChampionResearchOakLesson
#else
	msgbox PokemonLeague_ChampionsRoom_Text_OakImDisappointedRival
#endif
	closemessage
	applymovement LOCALID_CHAMPIONS_ROOM_PROF_OAK, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	delay 20
	msgbox PokemonLeague_ChampionsRoom_Text_OakPlayerComeWithMe
	closemessage
	delay 13
	applymovement LOCALID_CHAMPIONS_ROOM_PROF_OAK, PokemonLeague_ChampionsRoom_Movement_OakExit
	applymovement LOCALID_PLAYER, PokemonLeague_ChampionsRoom_Movement_PlayerExit
	waitmovement 0
	setvar VAR_TEMP_1, 1
	warp MAP_POKEMON_LEAGUE_HALL_OF_FAME, 5, 12
	waitstate
	releaseall
	end

PokemonLeague_ChampionsRoom_EventScript_QuestLogEnd::
	call PokemonLeague_ChampionsRoom_EventScript_StopSceneTrigger
	releaseall
	end

PokemonLeague_ChampionsRoom_EventScript_Battle::
	call_if_eq VAR_STARTER_MON, 2, PokemonLeague_ChampionsRoom_EventScript_BattleSquirtle
	call_if_eq VAR_STARTER_MON, 1, PokemonLeague_ChampionsRoom_EventScript_BattleBulbasaur
	call_if_eq VAR_STARTER_MON, 0, PokemonLeague_ChampionsRoom_EventScript_BattleCharmander
	return

PokemonLeague_ChampionsRoom_EventScript_Rematch::
	call_if_eq VAR_STARTER_MON, 2, PokemonLeague_ChampionsRoom_EventScript_RematchSquirtle
	call_if_eq VAR_STARTER_MON, 1, PokemonLeague_ChampionsRoom_EventScript_RematchBulbasaur
	call_if_eq VAR_STARTER_MON, 0, PokemonLeague_ChampionsRoom_EventScript_RematchCharmander
	return

PokemonLeague_ChampionsRoom_EventScript_Intro::
	msgbox PokemonLeague_ChampionsRoom_Text_Intro
	return

PokemonLeague_ChampionsRoom_EventScript_RematchIntro::
	msgbox PokemonLeague_ChampionsRoom_Text_RematchIntro
	return

PokemonLeague_ChampionsRoom_EventScript_BattleSquirtle::
	trainerbattle_no_intro TRAINER_CHAMPION_FIRST_SQUIRTLE, PokemonLeague_ChampionsRoom_Text_Defeat
	return

PokemonLeague_ChampionsRoom_EventScript_BattleBulbasaur::
	trainerbattle_no_intro TRAINER_CHAMPION_FIRST_BULBASAUR, PokemonLeague_ChampionsRoom_Text_Defeat
	return

PokemonLeague_ChampionsRoom_EventScript_BattleCharmander::
	trainerbattle_no_intro TRAINER_CHAMPION_FIRST_CHARMANDER, PokemonLeague_ChampionsRoom_Text_Defeat
	return

PokemonLeague_ChampionsRoom_EventScript_RematchSquirtle::
#ifdef FIRERED
	trainerbattle_no_intro TRAINER_CHAMPION_REMATCH_SQUIRTLE, CG_ChampionText_RematchDefeat
#else
	trainerbattle_no_intro TRAINER_CHAMPION_REMATCH_SQUIRTLE, PokemonLeague_ChampionsRoom_Text_Defeat
#endif
	return

PokemonLeague_ChampionsRoom_EventScript_RematchBulbasaur::
#ifdef FIRERED
	trainerbattle_no_intro TRAINER_CHAMPION_REMATCH_BULBASAUR, CG_ChampionText_RematchDefeat
#else
	trainerbattle_no_intro TRAINER_CHAMPION_REMATCH_BULBASAUR, PokemonLeague_ChampionsRoom_Text_Defeat
#endif
	return

PokemonLeague_ChampionsRoom_EventScript_RematchCharmander::
#ifdef FIRERED
	trainerbattle_no_intro TRAINER_CHAMPION_REMATCH_CHARMANDER, CG_ChampionText_RematchDefeat
#else
	trainerbattle_no_intro TRAINER_CHAMPION_REMATCH_CHARMANDER, PokemonLeague_ChampionsRoom_Text_Defeat
#endif
	return

PokemonLeague_ChampionsRoom_Movement_PlayerEnter::
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

PokemonLeague_ChampionsRoom_Movement_PlayerExit::
	delay_16
	walk_left
	walk_up
	walk_up
	walk_up
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	delay_8
	set_invisible
	step_end

PokemonLeague_ChampionsRoom_Movement_PlayerWatchOakEnter::
	delay_8
	walk_in_place_faster_down
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	walk_in_place_faster_left
	step_end

PokemonLeague_ChampionsRoom_Movement_OakEnter::
	delay_16
	delay_16
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	walk_up
	walk_up
	walk_in_place_faster_down
	delay_16
	step_end

PokemonLeague_ChampionsRoom_Movement_OakExit::
	walk_up
	walk_up
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	delay_8
	set_invisible
	step_end

PokemonLeague_ChampionsRoom_Movement_RivalWatchOakEnter::
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	walk_in_place_faster_left
	step_end

PokemonLeague_ChampionsRoom_Text_Intro::
	.string "{RIVAL}: Hey, {PLAYER}!\p"
	.string "I was looking forward to seeing\n"
	.string "you, {PLAYER}.\p"
	.string "My rival should be strong to keep\n"
	.string "me sharp.\p"
	.string "While working on my POKéDEX, I\n"
	.string "looked all over for POKéMON.\p"
	.string "Not only that, I assembled teams\n"
	.string "that would beat any POKéMON type.\p"
	.string "And now…\p"
	.string "I'm the POKéMON LEAGUE CHAMPION!\p"
	.string "{PLAYER}!\n"
	.string "Do you know what that means?\p"
	.string "I'll tell you.\p"
	.string "I am the most powerful TRAINER in\n"
	.string "the world!$"

PokemonLeague_ChampionsRoom_Text_RematchIntro::
#ifdef FIRERED
	.string "{RIVAL}: Hey, {PLAYER}!\p"
	.string "My field notes are full of ideas\n"
	.string "for our next battle.\p"
	.string "A strong rival keeps me sharp.\p"
	.string "Let's see how our teams have grown!$"
#else
	.string "{RIVAL}: Hey, {PLAYER}!\p"
	.string "You came back, {PLAYER}!\n"
	.string "Hahah, that is so great!\p"
	.string "My rival should be strong to keep\n"
	.string "me sharp.\p"
	.string "While working on my POKéDEX, I\n"
	.string "looked all over for POKéMON.\p"
	.string "Not only that, I assembled teams\n"
	.string "that would beat any POKéMON type.\p"
	.string "And now…\p"
	.string "I'm the POKéMON LEAGUE CHAMPION!\p"
	.string "{PLAYER}!\n"
	.string "Do you know what that means?\p"
	.string "I'll tell you.\p"
	.string "I am the most powerful TRAINER in\n"
	.string "the world!$"
#endif

PokemonLeague_ChampionsRoom_Text_Defeat::
#ifdef FIRERED
	.string "{RIVAL}: You beat me at my best!\p"
	.string "Great battle, {PLAYER}!\n"
	.string "I have plenty to write down.$"
#else
	.string "NO!\n"
	.string "That can't be!\l"
	.string "You beat me at my best!\p"
	.string "After all that work to become\n"
	.string "the LEAGUE CHAMP?\p"
	.string "My reign is over already?\n"
	.string "It's not fair!$"
#endif

PokemonLeague_ChampionsRoom_Text_Victory::
	.string "はーはッ！\n"
	.string "かった！　かった！　かった！\p"
	.string "{PLAYER}に　まける　ような\n"
	.string "おれさま　では　なーい！\p"
	.string "ま！　ポケモンの\n"
	.string "てんさい　{RIVAL}さま　あいてに\l"
	.string "ここまで　よく　がんばった！\p"
	.string "ほめて　つかわす！\n"
	.string "はーッ！　はーはッはッ！$"

PokemonLeague_ChampionsRoom_Text_PostBattle::
#ifdef FIRERED
	.string "{RIVAL}: Grandpa will want to hear\n"
	.string "what our teams taught us today!$"
#else
	.string "Why?\n"
	.string "Why did I lose?\p"
	.string "I never made any mistakes raising\n"
	.string "my POKéMON…\p"
	.string "Darn it! You're the new POKéMON\n"
	.string "LEAGUE CHAMPION!\p"
	.string "Although I don't like to admit it…$"
#endif

PokemonLeague_ChampionsRoom_Text_OakPlayer::
	.string "OAK: {PLAYER}!$"

PokemonLeague_ChampionsRoom_Text_OakCongratulations::
	.string "OAK: So, you've won!\n"
	.string "Sincerely, congratulations!\p"
	.string "You're the new POKéMON LEAGUE\n"
	.string "CHAMPION!\p"
	.string "You've grown up so much since you\n"
	.string "first left with {STR_VAR_1} to work\l"
	.string "on the POKéDEX.\p"
	.string "{PLAYER}, you have come of age!$"

PokemonLeague_ChampionsRoom_Text_OakImDisappointedRival::
#ifdef FIRERED
	.string "OAK: You both worked hard\n"
	.string "with your POKéMON.\p"
	.string "{RIVAL}, keep listening to what\n"
	.string "your partners teach you.\p"
	.string "That curiosity belongs in\n"
	.string "research and in battle.$"
#else
	.string "OAK: {RIVAL}…\n"
	.string "I'm disappointed in you.\p"
	.string "I came when I heard you'd beaten\n"
	.string "the ELITE FOUR.\p"
	.string "But, when I got here, you had\n"
	.string "already lost!\p"
	.string "{RIVAL}, do you understand why\n"
	.string "you lost?\p"
	.string "You have forgotten to treat your\n"
	.string "POKéMON with love and trust.\p"
	.string "Without them, you will never\n"
	.string "become a CHAMP again!$"
#endif

PokemonLeague_ChampionsRoom_Text_OakPlayerComeWithMe::
	.string "OAK: {PLAYER}.\p"
	.string "You understand that your victory\n"
	.string "was not just your own doing.\p"
	.string "The bond you share with your\n"
	.string "POKéMON is marvelous.\p"
	.string "{PLAYER}!\n"
	.string "Come with me!$"


#ifdef FIRERED
@ First-victory and later-rematch replies keep the researcher path positive.
CG_ChampionOriginalPostBattle::
	msgbox PokemonLeague_ChampionsRoom_Text_PostBattle
	return
CG_ChampionResearchPostBattle::
	msgbox CG_ChampionText_PostBattle
	return
CG_ChampionOriginalOakLesson::
	msgbox PokemonLeague_ChampionsRoom_Text_OakImDisappointedRival
	return
CG_ChampionResearchOakLesson::
	msgbox CG_ChampionText_OakLesson
	return
CG_ChampionText_RematchDefeat::
	.string "{RIVAL}: Great battle!\pI have a few new observations\nfor my notebook.$"
CG_ChampionText_PostBattle::
	.string "{RIVAL}: That was worth the trip.\pI'll take these notes back to\nGrandpa when we're finished here.$"
CG_ChampionText_OakLesson::
	.string "OAK: {RIVAL}, keep recording\nwhat your POKéMON teach you.\pGood research begins by listening.$"
#endif
