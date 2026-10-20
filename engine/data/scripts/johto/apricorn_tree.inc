@ Johto (data/scripts/apricorn_tree.inc), as built into the FireRed game.

J_ApricornTreeScript::
	lock
	faceplayer
	message J_ApricornTree_Text_Intro
	waitmessage
	waitbuttonpress
	special ObjectEventInteractionGetApricornTreeData
	goto_if_gt 32773, 0, J_ApricornTree_EventScript_WantToPick
	message J_ApricornTree_Text_Empty
	waitmessage
	waitbuttonpress
	release
	end

J_ApricornTree_EventScript_WantToPick::
	buffernumberstring STR_VAR_2, 32773
	msgbox J_ApricornTree_Text_WantToPick, MSGBOX_YESNO
	goto_if_eq 32781, YES, J_ApricornTree_EventScript_PickApricorn
	goto_if_eq 32781, NO, J_ApricornTree_EventScript_CancelPickingApricorn

	.set APRICORN_NORMAL_BAG_FULL, 0
	.set APRICORN_NORMAL_SPACE_IN_BAG, 1

J_ApricornTree_EventScript_PickApricorn::
	special ObjectEventInteractionPickApricornTree
	call J_EventScript_BufferPocketNameAndTryFanfare
	goto_if_eq 32774, APRICORN_NORMAL_BAG_FULL, J_ApricornTree_EventScript_PocketFull
	message J_ApricornTree_Text_PickedTheApricorn
	.if 0 != 0
	copyvar 32774 32772
	.endif
	delay 10
	.if 0 != 0
	showberrydescription
	.endif
	playfanfare 387
	waitmessage
	waitfanfare
	waitbuttonpress
	message J_ApricornTree_Text_PutAwayApricorn
	waitmessage
	waitbuttonpress
	.if 0 != 0
	hideitemdescription
	.endif
	release
	end

J_ApricornTree_EventScript_PocketFull::
	message J_ApricornTree_Text_PocketFull
	waitmessage
	waitbuttonpress
	release
	end

J_ApricornTree_EventScript_CancelPickingApricorn::
	message J_ApricornTree_Text_ApricornLeftUnpicked
	waitmessage
	waitbuttonpress
	release
	end

J_ApricornTree_Text_Intro:
	.string "It'{SE_M_GRASSWHISTLE}a{SE_M_ATTRACT}Apricor{SE_M_ATTRACT}Tree!$"

J_ApricornTree_Text_Empty:
	.string "Ther{SE_M_REVERSAL}ar{SE_M_REVERSAL}n{SE_M_ATTRACT2}Apricorns…$"

J_ApricornTree_Text_WantToPick:
	.string "…It'{SE_M_GRASSWHISTLE}{STR_VAR_2} {STR_VAR_1}!\n"
	.string "D{SE_M_ATTRACT2}yo{SE_M_DIVE}wan{SE_M_SPIT_UP}t{SE_M_ATTRACT2}pic{SE_M_ENCORE2}the\l"
	.string "{STR_VAR_1}?$"

J_ApricornTree_Text_PickedTheApricorn:
	.string "{PLAYER} obtained\n"
	.string "{STR_VAR_2} {STR_VAR_1}.$"

J_ApricornTree_Text_PutAwayApricorn:
	.string "{PLAYER} pu{SE_M_SPIT_UP}awa{SE_M_YAWN}the\n"
	.string "{STR_VAR_1} in\l"
	.string "th{SE_M_REVERSAL}BAG'{SE_M_GRASSWHISTLE}{STR_VAR_3} POCKET.$"

J_ApricornTree_Text_PocketFull:
	.string "Th{SE_M_REVERSAL}BAG'{SE_M_GRASSWHISTLE}{STR_VAR_3} POCKE{SE_M_SWIFT}i{SE_M_GRASSWHISTLE}full.\p"
	.string "{PLAYER} gav{SE_M_REVERSAL}u{SE_M_MORNING_SUN}o{SE_M_ATTRACT}the\n"
	.string "{STR_VAR_1}…$"

J_ApricornTree_Text_ApricornLeftUnpicked:
	.string "{PLAYER} gav{SE_M_REVERSAL}u{SE_M_MORNING_SUN}o{SE_M_ATTRACT}the\n"
	.string "{STR_VAR_1}…$"

