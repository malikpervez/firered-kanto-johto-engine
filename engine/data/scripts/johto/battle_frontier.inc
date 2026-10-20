@ Johto (data/scripts/battle_frontier.inc), as built into the FireRed game.

J_BattleFrontier_ShowCaughtBannedSpecies::
	goto_if_eq VAR_0x8005, 0, J_BattleFrontier_ShowCaughtBannedSpeciesEnd
	msgbox J_BattleFrontier_DoYouWantToSeeTheListOfCaughtBannedSpecies, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, J_BattleFrontier_ShowCaughtBannedSpeciesEnd
	callnative ShowBattleFrontierCaughtBannedSpecies
	waitstate

J_BattleFrontier_ShowCaughtBannedSpeciesEnd:
	return

J_BattleFrontier_DoYouWantToSeeTheListOfCaughtBannedSpecies:
	.string "Do you want to see the list of\n"
	.string "POKéMON species you can't bring?$"

