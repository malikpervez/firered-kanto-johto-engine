@ Johto (data/scripts/test_signpost.inc), as built into the FireRed game.

J_Text_ThisIsATestSignpostMsg::
	.string "Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}tes{SE_M_SPIT_UP}message.\n"
	.string "Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}signpost.$"

J_EventScript_TestSignpostMsg::
	msgbox J_Text_ThisIsATestSignpostMsg, MSGBOX_SIGN
	end

