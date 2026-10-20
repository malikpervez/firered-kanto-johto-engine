@ Johto (data/scripts/dexnav.inc), as built into the FireRed game.

J_EventScript_StartDexNavBattle::
	lock
	playse SE_PIN
	applymovement 255 J_Common_Movement_ExclamationMark
	waitmovement 0
	waitse
	dowildbattle
	release
	end

J_EventScript_NotFoundNearby::
	msgbox J_sText_NotFoundNearby, MSGBOX_SIGN
	end

J_EventScript_MovedTooFast::
	msgbox J_sText_TryMovingSlower, MSGBOX_SIGN
	end

J_EventScript_PokemonGotAway::
	msgbox J_sText_PokemonGotAway, MSGBOX_SIGN
	end

J_EventScript_LostSignal::
	msgbox J_sText_LostSignal, MSGBOX_SIGN
	end

J_EventScript_TooDark::
	msgbox J_sText_TooDark, MSGBOX_SIGN
	end

J_sText_NotFoundNearby:
	.string "It couldn't be found nearby.\n"
	.string "Try looking in a different area!$"

J_sText_TryMovingSlower:
	.string "The Pokémon got away!\n"
	.string "Try moving more slowly.$"

J_sText_PokemonGotAway:
	.string "The Pokémon got away!$"

J_sText_LostSignal:
	.string "There is no reaction.\n"
	.string "The signal was lost!$"

J_sText_TooDark:
	.string "It's too dark to search\nfor a Pokémon!$"

