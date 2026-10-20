@ Johto (data/scripts/kecleon.inc), as built into the FireRed game.

J_Route120_EventScript_Kecleon1::
	lock
	faceplayer
	setvar 32777, 1
	goto J_EventScript_Kecleon
	end

J_Route120_EventScript_Kecleon2::
	lock
	faceplayer
	setvar 32777, 2
	goto J_EventScript_Kecleon
	end

J_Route120_EventScript_Kecleon3::
	lock
	faceplayer
	setvar 32777, 3
	goto J_EventScript_Kecleon
	end

J_Route120_EventScript_Kecleon4::
	lock
	faceplayer
	setvar 32777, 4
	goto J_EventScript_Kecleon
	end

J_Route120_EventScript_Kecleon5::
	lock
	faceplayer
	setvar 32777, 5
	goto J_EventScript_Kecleon
	end

J_Route119_EventScript_Kecleon1::
	lock
	faceplayer
	setvar 32777, 6
	goto J_EventScript_Kecleon
	end

J_Route119_EventScript_Kecleon2::
	lock
	faceplayer
	setvar 32777, 7
	goto J_EventScript_Kecleon
	end

J_EventScript_Kecleon::
	checkitem ITEM_DEVON_SCOPE
	goto_if_eq 32781, TRUE, J_EventScript_AskUseDevonScope
	msgbox J_Kecleon_Text_SomethingUnseeable, MSGBOX_DEFAULT
	release
	end

J_EventScript_AskUseDevonScope::
	msgbox J_Kecleon_Text_WantToUseDevonScope, MSGBOX_YESNO
	goto_if_eq 32781, YES, J_EventScript_BattleKecleon
	release
	end

J_EventScript_BattleKecleon::
	msgbox J_Kecleon_Text_UseDevonScopeMonAttacked, MSGBOX_DEFAULT
	closemessage
	applymovement 32783, J_Common_Movement_FacePlayer
	waitmovement 0
	applymovement 32783, J_Movement_KecleonAppears
	waitmovement 0
	waitse
	playmoncry 352, 2
	delay 40
	waitmoncry
	setwildbattle 352, 30
	setflag 10342
	dowildbattle
	clearflag 10342
	specialvar 32781, GetBattleOutcome
	goto_if_eq 32781, 1, J_EventScript_RemoveKecleon
	goto_if_eq 32781, 4, J_EventScript_RemoveKecleon
	goto_if_eq 32781, 5, J_EventScript_RemoveKecleon
	release
	end

J_EventScript_RemoveKecleon::
	goto J_Common_EventScript_RemoveStaticPokemon
	end

J_Movement_KecleonAppears:
	set_visible
	delay_4
	set_invisible
	delay_4
	set_visible
	delay_4
	set_invisible
	delay_4
	set_visible
	delay_8
	set_invisible
	delay_8
	set_visible
	delay_8
	set_invisible
	delay_8
	set_visible
	delay_16
	set_invisible
	delay_16
	set_visible
	step_end

