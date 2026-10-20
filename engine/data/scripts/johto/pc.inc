@ Johto (data/scripts/pc.inc), as built into the FireRed game.

J_EventScript_PC::
	lockall

	setvar 32772, PC_LOCATION_HNS



	special DoPCTurnOnEffect
	playse 4
	msgbox J_Text_BootUpPC, MSGBOX_DEFAULT
	goto J_EventScript_PCMainMenu
	end

J_EventScript_FakePC::
	lockall

	setvar 32772, PC_LOCATION_HNS



	playse 4
	msgbox J_Text_BootUpPC, MSGBOX_DEFAULT
	goto J_EventScript_FakePCMainMenu
	end

J_EventScript_PCMainMenu::
	message J_gText_WhichPCShouldBeAccessed
	waitmessage
	special ScriptMenu_CreatePCMultichoice
	waitstate
	goto_if_unset 10387, J_EventScript_AccessPC_BeforeLeague
	goto J_EventScript_AccessPC_AfterLeague
	end

J_EventScript_FakePCMainMenu::
	message J_gText_WhichPCShouldBeAccessed
	waitmessage
	special ScriptMenu_CreatePCMultichoice
	waitstate
	goto_if_unset 10387, J_EventScript_AccessFakePC_BeforeLeague
	goto J_EventScript_AccessFakePC_AfterLeague
	end

J_EventScript_AccessPC_BeforeLeague::
	switch 32781
	case 0, J_EventScript_AccessPokemonStorage
	case 1, J_EventScript_AccessPlayersPC
	case 2, J_EventScript_ChallengeViewer
	case 3, J_EventScript_TurnOffPC
	case 127, J_EventScript_TurnOffPC
	end

J_EventScript_AccessFakePC_BeforeLeague::
	switch 32781
	case 0, J_EventScript_AccessFakePokemonStorage
	case 1, J_EventScript_AccessPlayersFakePC
	case 2, J_EventScript_FakeChallengeViewer
	case 3, J_EventScript_TurnOffFakePC
	case 127, J_EventScript_TurnOffFakePC
	end

J_EventScript_AccessPC_AfterLeague::
	switch 32781
	case 0, J_EventScript_AccessPokemonStorage
	case 1, J_EventScript_AccessPlayersPC
	case 2, J_EventScript_AccessHallOfFame
	case 3, J_EventScript_ChallengeViewer
	case 4, J_EventScript_TurnOffPC
	case 127, J_EventScript_TurnOffPC
	end

J_EventScript_AccessFakePC_AfterLeague::
	switch 32781
	case 0, J_EventScript_AccessFakePokemonStorage
	case 1, J_EventScript_AccessPlayersFakePC
	case 2, J_EventScript_AccessFakeHallOfFame
	case 3, J_EventScript_FakeChallengeViewer
	case 4, J_EventScript_TurnOffFakePC
	case 127, J_EventScript_TurnOffFakePC
	end

J_EventScript_ChallengeViewer::
	playse 2
	callnative Script_OpenChallengeMenu
	waitstate
	goto J_EventScript_PCMainMenu
	end

J_EventScript_FakeChallengeViewer::
	playse 2
	callnative Script_OpenChallengeMenu
	delay 30
	goto J_EventScript_FakePCMainMenu
	end

J_EventScript_AccessPlayersPC::
	playse 2
	msgbox J_gText_AccessedPlayersPC, MSGBOX_DEFAULT
	special PlayerPC
	waitstate
	goto J_EventScript_PCMainMenu
	end

J_EventScript_AccessPlayersFakePC::
	playse 2
	msgbox J_gText_AccessedPlayersPC, MSGBOX_DEFAULT
	special PlayerPC
	waitstate
	goto J_EventScript_FakePCMainMenu
	end

J_EventScript_AccessPokemonStorage::
	playse 2
	call_if_unset 10391, J_EventScript_AccessSomeonesPC
	call_if_set 10391, J_EventScript_AccessLanettesPC
	msgbox J_gText_StorageSystemOpened, MSGBOX_DEFAULT
	special ShowPokemonStorageSystemPC
	waitstate
	goto J_EventScript_PCMainMenu
	end

J_EventScript_AccessFakePokemonStorage::
	playse 2
	call_if_unset 10391, J_EventScript_AccessSomeonesPC
	call_if_set 10391, J_EventScript_AccessLanettesPC
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

	setvar 32772, PC_LOCATION_HNS



	playse 3
	special DoPCTurnOffEffect
	releaseall
	end

J_EventScript_TurnOffFakePC::
	playse 3
	releaseall
	end

J_EventScript_AccessHallOfFame::
	goto_if_unset 10387, J_EventScript_TurnOffPC
	playse 2
	special AccessHallOfFamePC
	waitstate
	goto J_EventScript_AccessPC_AfterLeague
	end

J_EventScript_AccessFakeHallOfFame::
	playse 2
	special AccessHallOfFamePC
	waitstate
	goto J_EventScript_AccessFakePC_AfterLeague
	end

J_EventScript_AccessPokemonBoxLink::
	playse 2
	msgbox J_gText_StorageSystemOpened, MSGBOX_DEFAULT
	special ShowPokemonStorageSystemPC
	waitstate
	goto J_EventScript_TurnOffPC
	end

