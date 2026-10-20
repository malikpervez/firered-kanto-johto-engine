@ Johto (data/scripts/pc.inc), as built into the FireRed game.

J_EventScript_PC::
	lockall

	setvar VAR_0x8004, PC_LOCATION_HNS



	special DoPCTurnOnEffect
	playse SE_PC_ON
	msgbox J_Text_BootUpPC, MSGBOX_DEFAULT
	goto J_EventScript_PCMainMenu
	end

J_EventScript_FakePC::
	lockall

	setvar VAR_0x8004, PC_LOCATION_HNS



	playse SE_PC_ON
	msgbox J_Text_BootUpPC, MSGBOX_DEFAULT
	goto J_EventScript_FakePCMainMenu
	end

J_EventScript_PCMainMenu::
	message J_gText_WhichPCShouldBeAccessed
	waitmessage
	special ScriptMenu_CreatePCMultichoice
	waitstate
	goto_if_unset JOHTO_FLAG_SYS_GAME_CLEAR, J_EventScript_AccessPC_BeforeLeague
	goto J_EventScript_AccessPC_AfterLeague
	end

J_EventScript_FakePCMainMenu::
	message J_gText_WhichPCShouldBeAccessed
	waitmessage
	special ScriptMenu_CreatePCMultichoice
	waitstate
	goto_if_unset JOHTO_FLAG_SYS_GAME_CLEAR, J_EventScript_AccessFakePC_BeforeLeague
	goto J_EventScript_AccessFakePC_AfterLeague
	end

J_EventScript_AccessPC_BeforeLeague::
	switch VAR_RESULT
	case 0, J_EventScript_AccessPokemonStorage
	case 1, J_EventScript_AccessPlayersPC
	case 2, J_EventScript_ChallengeViewer
	case 3, J_EventScript_TurnOffPC
	case MULTI_B_PRESSED, J_EventScript_TurnOffPC
	end

J_EventScript_AccessFakePC_BeforeLeague::
	switch VAR_RESULT
	case 0, J_EventScript_AccessFakePokemonStorage
	case 1, J_EventScript_AccessPlayersFakePC
	case 2, J_EventScript_FakeChallengeViewer
	case 3, J_EventScript_TurnOffFakePC
	case MULTI_B_PRESSED, J_EventScript_TurnOffFakePC
	end

J_EventScript_AccessPC_AfterLeague::
	switch VAR_RESULT
	case 0, J_EventScript_AccessPokemonStorage
	case 1, J_EventScript_AccessPlayersPC
	case 2, J_EventScript_AccessHallOfFame
	case 3, J_EventScript_ChallengeViewer
	case 4, J_EventScript_TurnOffPC
	case MULTI_B_PRESSED, J_EventScript_TurnOffPC
	end

J_EventScript_AccessFakePC_AfterLeague::
	switch VAR_RESULT
	case 0, J_EventScript_AccessFakePokemonStorage
	case 1, J_EventScript_AccessPlayersFakePC
	case 2, J_EventScript_AccessFakeHallOfFame
	case 3, J_EventScript_FakeChallengeViewer
	case 4, J_EventScript_TurnOffFakePC
	case MULTI_B_PRESSED, J_EventScript_TurnOffFakePC
	end

J_EventScript_ChallengeViewer::
	playse SE_PC_LOGIN
	callnative Script_OpenChallengeMenu
	waitstate
	goto J_EventScript_PCMainMenu
	end

J_EventScript_FakeChallengeViewer::
	playse SE_PC_LOGIN
	callnative Script_OpenChallengeMenu
	delay 30
	goto J_EventScript_FakePCMainMenu
	end

J_EventScript_AccessPlayersPC::
	playse SE_PC_LOGIN
	msgbox J_gText_AccessedPlayersPC, MSGBOX_DEFAULT
	special PlayerPC
	waitstate
	goto J_EventScript_PCMainMenu
	end

J_EventScript_AccessPlayersFakePC::
	playse SE_PC_LOGIN
	msgbox J_gText_AccessedPlayersPC, MSGBOX_DEFAULT
	special PlayerPC
	waitstate
	goto J_EventScript_FakePCMainMenu
	end

J_EventScript_AccessPokemonStorage::
	playse SE_PC_LOGIN
	call_if_unset JOHTO_FLAG_SYS_PC_LANETTE, J_EventScript_AccessSomeonesPC
	call_if_set JOHTO_FLAG_SYS_PC_LANETTE, J_EventScript_AccessLanettesPC
	msgbox J_gText_StorageSystemOpened, MSGBOX_DEFAULT
	special ShowPokemonStorageSystemPC
	waitstate
	goto J_EventScript_PCMainMenu
	end

J_EventScript_AccessFakePokemonStorage::
	playse SE_PC_LOGIN
	call_if_unset JOHTO_FLAG_SYS_PC_LANETTE, J_EventScript_AccessSomeonesPC
	call_if_set JOHTO_FLAG_SYS_PC_LANETTE, J_EventScript_AccessLanettesPC
	msgbox J_gText_StorageSystemOpened, MSGBOX_DEFAULT
	special ShowPokemonStorageSystemPC
	waitstate
	goto J_EventScript_FakePCMainMenu
	end

J_EventScript_AccessSomeonesPC::
	msgbox J_gText_AccessedSomeonesPC, MSGBOX_DEFAULT
	return

J_EventScript_AccessLanettesPC::

	msgbox J_gText_AccessedBillsPC, MSGBOX_DEFAULT



	return

J_EventScript_TurnOffPC::

	setvar VAR_0x8004, PC_LOCATION_HNS



	playse SE_PC_OFF
	special DoPCTurnOffEffect
	releaseall
	end

J_EventScript_TurnOffFakePC::
	playse SE_PC_OFF
	releaseall
	end

J_EventScript_AccessHallOfFame::
	goto_if_unset JOHTO_FLAG_SYS_GAME_CLEAR, J_EventScript_TurnOffPC
	playse SE_PC_LOGIN
	special AccessHallOfFamePC
	waitstate
	goto J_EventScript_AccessPC_AfterLeague
	end

J_EventScript_AccessFakeHallOfFame::
	playse SE_PC_LOGIN
	special AccessHallOfFamePC
	waitstate
	goto J_EventScript_AccessFakePC_AfterLeague
	end

J_EventScript_AccessPokemonBoxLink::
	playse SE_PC_LOGIN
	msgbox J_gText_StorageSystemOpened, MSGBOX_DEFAULT
	special ShowPokemonStorageSystemPC
	waitstate
	goto J_EventScript_TurnOffPC
	end

