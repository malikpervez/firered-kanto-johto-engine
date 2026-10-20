@ Johto (data/event_scripts.s), as built into the FireRed game.

J_Common_EventScript_ShowPokemartSign::
	msgbox J_gText_PokemartSign, MSGBOX_SIGN
	end

J_Common_EventScript_ShowPokemonCenterSign::
	msgbox J_gText_PokemonCenterSign, MSGBOX_SIGN
	end

J_Common_ShowEasyChatScreen::
	fadescreen 1
	special ShowEasyChatScreen
	fadescreen 0
	return

J_Common_EventScript_ReadyPetalburgGymForBattle::
	clearflag 0
	setflag 0
	return

J_Common_EventScript_BufferTrendyPhrase::
	dotimebasedevents
	setvar 32772, 0
	special BufferTrendyPhraseString
	return

J_EventScript_BackupMrBrineyLocation::
	copyvar 32776, 20614
	setvar 20614, 0
	return

