@ Johto (data/scripts/dexnav.inc), as built into the FireRed game.

J_EventScript_StartDexNavBattle::
	lock
	playse 21
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
	.string "I{SE_M_SPIT_UP}couldn'{SE_M_SPIT_UP}b{SE_M_REVERSAL}foun{SE_M_WATERFALL}nearby.\n"
	.string "Tr{SE_M_YAWN}lookin{SE_M_SANDSTORM}i{SE_M_ATTRACT}{SE_M_CHARGE}differen{SE_M_SPIT_UP}area!$"

J_sText_TryMovingSlower:
	.string "Th{SE_M_REVERSAL}Pokémo{SE_M_ATTRACT}go{SE_M_SPIT_UP}away!\n"
	.string "Tr{SE_M_YAWN}movin{SE_M_SANDSTORM}mor{SE_M_REVERSAL}slowly.$"

J_sText_PokemonGotAway:
	.string "Th{SE_M_REVERSAL}Pokémo{SE_M_ATTRACT}go{SE_M_SPIT_UP}away!$"

J_sText_LostSignal:
	.string "Ther{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}n{SE_M_ATTRACT2}reaction.\n"
	.string "Th{SE_M_REVERSAL}signa{SE_M_BATON_PASS}wa{SE_M_GRASSWHISTLE}lost!$"

J_sText_TooDark:
	.string "It'{SE_M_GRASSWHISTLE}to{SE_M_ATTRACT2}dar{SE_M_ENCORE2}t{SE_M_ATTRACT2}search\nfo{SE_M_SAND_TOMB}{SE_M_CHARGE}Pokémon!$"

