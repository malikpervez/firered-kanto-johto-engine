@ Johto (data/scripts/apricorn_tree.inc), as built into the FireRed game.

J_ApricornTreeScript::
	lock
	faceplayer
	message J_ApricornTree_Text_Intro
	waitmessage
	waitbuttonpress
	special ObjectEventInteractionGetApricornTreeData
	goto_if_gt VAR_0x8005, 0, J_ApricornTree_EventScript_WantToPick
	message J_ApricornTree_Text_Empty
	waitmessage
	waitbuttonpress
	release
	end

J_ApricornTree_EventScript_WantToPick::
	buffernumberstring STR_VAR_2, VAR_0x8005
	msgbox J_ApricornTree_Text_WantToPick, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, J_ApricornTree_EventScript_PickApricorn
	goto_if_eq VAR_RESULT, NO, J_ApricornTree_EventScript_CancelPickingApricorn

	.set APRICORN_NORMAL_BAG_FULL, 0
	.set APRICORN_NORMAL_SPACE_IN_BAG, 1

J_ApricornTree_EventScript_PickApricorn::
	special ObjectEventInteractionPickApricornTree
	call J_EventScript_BufferPocketNameAndTryFanfare
	goto_if_eq VAR_0x8006, APRICORN_NORMAL_BAG_FULL, J_ApricornTree_EventScript_PocketFull
	message J_ApricornTree_Text_PickedTheApricorn
	.if 0 != 0
	copyvar 32774 32772
	.endif
	delay 10
	.if 0 != 0
	showberrydescription
	.endif
	playfanfare MUS_OBTAIN_BERRY
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
	.string "It's an Apricorn Tree!$"

J_ApricornTree_Text_Empty:
	.string "There are no Apricorns…$"

J_ApricornTree_Text_WantToPick:
	.string "…It's {STR_VAR_2} {STR_VAR_1}!\n"
	.string "Do you want to pick the\l"
	.string "{STR_VAR_1}?$"

J_ApricornTree_Text_PickedTheApricorn:
	.string "{PLAYER} obtained\n"
	.string "{STR_VAR_2} {STR_VAR_1}.$"

J_ApricornTree_Text_PutAwayApricorn:
	.string "{PLAYER} put away the\n"
	.string "{STR_VAR_1} in\l"
	.string "the BAG's {STR_VAR_3} POCKET.$"

J_ApricornTree_Text_PocketFull:
	.string "The BAG's {STR_VAR_3} POCKET is full.\p"
	.string "{PLAYER} gave up on the\n"
	.string "{STR_VAR_1}…$"

J_ApricornTree_Text_ApricornLeftUnpicked:
	.string "{PLAYER} gave up on the\n"
	.string "{STR_VAR_1}…$"

