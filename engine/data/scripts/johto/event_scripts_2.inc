@ Johto (data/event_scripts.s), as built into the FireRed game.

J_Common_EventScript_ShowPokemartSign::
	msgbox J_gText_PokemartSign, MSGBOX_SIGN
	end

J_Common_EventScript_ShowPokemonCenterSign::
	msgbox J_gText_PokemonCenterSign, MSGBOX_SIGN
	end

J_Common_ShowEasyChatScreen::
	fadescreen FADE_TO_BLACK
	special ShowEasyChatScreen
	fadescreen FADE_FROM_BLACK
	return

J_Common_EventScript_ReadyPetalburgGymForBattle::
	clearflag FLAG_HIDE_PETALBURG_GYM_GREETER
	setflag FLAG_PETALBURG_MART_EXPANDED_ITEMS
	return

J_Common_EventScript_BufferTrendyPhrase::
	dotimebasedevents
	setvar VAR_0x8004, 0
	special BufferTrendyPhraseString
	return

J_EventScript_BackupMrBrineyLocation::
	copyvar VAR_0x8008, JOHTO_VAR_BRINEY_LOCATION
	setvar JOHTO_VAR_BRINEY_LOCATION, 0
	return

