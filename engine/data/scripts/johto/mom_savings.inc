@ Johto (data/scripts/mom_savings.inc), as built into the FireRed game.

J_EventScript_MomGiftCall_Item::
	lockall
	pokenavcall J_Mom_Text_GiftCall_Item
	waitmessage
	delay 30
	clearflag JOHTO_FLAG_MOM_HAS_GIFT
	releaseall
	end

J_EventScript_MomGiftCall_Berry::
	lockall
	pokenavcall J_Mom_Text_GiftCall_Berry
	waitmessage
	delay 30
	clearflag JOHTO_FLAG_MOM_HAS_GIFT
	releaseall
	end

J_EventScript_MomGiftCall_Decoration::
	lockall
	pokenavcall J_Mom_Text_GiftCall_Decoration
	waitmessage
	delay 30
	clearflag JOHTO_FLAG_MOM_HAS_GIFT
	releaseall
	end

J_Mom_Text_GiftCall_Item:
	.string "HOST: Hello, {PLAYER}!\p"
	.string "I bought something nice\n"
	.string "for you with your savings!\p"
	.string "I sent it to your PC.\n"
	.string "Take care!$"

J_Mom_Text_GiftCall_Berry:
	.string "HOST: Hello, {PLAYER}!\p"
	.string "I found some nice BERRIES\n"
	.string "at the store for you!\p"
	.string "I sent them to your PC.\n"
	.string "Take care!$"

J_Mom_Text_GiftCall_Decoration:
	.string "HOST: Hello, {PLAYER}!\p"
	.string "I bought a cute POKé DOLL\n"
	.string "for your room!\p"
	.string "Check your DECORATIONS when you\n"
	.string "visit the guest house. Take care!$"

