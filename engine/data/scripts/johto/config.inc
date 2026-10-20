@ Johto (data/scripts/config.inc), as built into the FireRed game.

J_Debug_FlagsAndVarNotSetBattleConfigMessage::
	lockall
	message J_Debug_FlagsAndVarNotSetBattleConfigMessage_Text
	waitmessage
	waitbuttonpress
	releaseall
	end

J_Debug_FlagsAndVarNotSetBattleConfigMessage_Text:
	.string "Feature unavailable! Please define a\n"
	.string "usable flag and a usable var in:\l"
	.string "'include/config/battle.h'!$"

