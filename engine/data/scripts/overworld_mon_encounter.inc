@ An overworld Pokémon outside a town that the player can choose to battle (src/overworld_mon_encounter.c): a
@ few levels above the map's own wild Pokémon, with better IVs. Gone once battled, until the player leaves the map.
OverworldMon_EventScript_Encounter::
	lock
	faceplayer
	special Special_OwMonEncounterPrepare
	goto_if_eq VAR_RESULT, FALSE, OverworldMon_EventScript_LeaveIt
	playmoncry VAR_0x8004, CRY_MODE_NORMAL
	msgbox OverworldMon_Text_LooksStrong, MSGBOX_YESNO
	waitmoncry
	goto_if_eq VAR_RESULT, NO, OverworldMon_EventScript_LeaveIt
	closemessage
	special BattleSetup_StartOverworldMonBattle
	waitstate
	special Special_OwMonEncounterRemove
	release
	end

OverworldMon_EventScript_LeaveIt::
	release
	end

OverworldMon_Text_LooksStrong:
	.string "This {STR_VAR_1} looks stronger than\n"
	.string "the others around here. Battle it?$"
