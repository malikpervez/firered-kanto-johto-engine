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
	.string "D{SE_M_ATTRACT2}yo{SE_M_DIVE}wan{SE_M_SPIT_UP}t{SE_M_ATTRACT2}se{SE_M_REVERSAL}th{SE_M_REVERSAL}lis{SE_M_SPIT_UP}of\n"
	.string "POKéMO{SE_M_PSYBEAM2}specie{SE_M_GRASSWHISTLE}yo{SE_M_DIVE}can'{SE_M_SPIT_UP}bring?$"

