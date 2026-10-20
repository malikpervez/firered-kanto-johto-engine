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
	.string "HOST{SE_M_HEAT_WAVE}Hello{SE_M_SUPERSONIC}{PLAYER}!\p"
	.string "{SE_M_HEAL_BELL}bough{SE_M_SPIT_UP}somethin{SE_M_SANDSTORM}nice\n"
	.string "fo{SE_M_SAND_TOMB}yo{SE_M_DIVE}wit{SE_M_TRI_ATTACK}you{SE_M_SAND_TOMB}savings!\p"
	.string "{SE_M_HEAL_BELL}sen{SE_M_SPIT_UP}i{SE_M_SPIT_UP}t{SE_M_ATTRACT2}you{SE_M_SAND_TOMB}PC.\n"
	.string "Tak{SE_M_REVERSAL}care!$"

J_Mom_Text_GiftCall_Berry:
	.string "HOST{SE_M_HEAT_WAVE}Hello{SE_M_SUPERSONIC}{PLAYER}!\p"
	.string "{SE_M_HEAL_BELL}foun{SE_M_WATERFALL}som{SE_M_REVERSAL}nic{SE_M_REVERSAL}BERRIES\n"
	.string "a{SE_M_SPIT_UP}th{SE_M_REVERSAL}stor{SE_M_REVERSAL}fo{SE_M_SAND_TOMB}you!\p"
	.string "{SE_M_HEAL_BELL}sen{SE_M_SPIT_UP}the{SE_M_MILK_DRINK}t{SE_M_ATTRACT2}you{SE_M_SAND_TOMB}PC.\n"
	.string "Tak{SE_M_REVERSAL}care!$"

J_Mom_Text_GiftCall_Decoration:
	.string "HOST{SE_M_HEAT_WAVE}Hello{SE_M_SUPERSONIC}{PLAYER}!\p"
	.string "{SE_M_HEAL_BELL}bough{SE_M_SPIT_UP}{SE_M_CHARGE}cut{SE_M_REVERSAL}POK{SE_U}DOLL\n"
	.string "fo{SE_M_SAND_TOMB}you{SE_M_SAND_TOMB}room!\p"
	.string "Chec{SE_M_ENCORE2}you{SE_M_SAND_TOMB}DECORATION{SE_M_SKETCH}whe{SE_M_ATTRACT}you\n"
	.string "visi{SE_M_SPIT_UP}th{SE_M_REVERSAL}gues{SE_M_SPIT_UP}house{SE_M_PERISH_SONG}Tak{SE_M_REVERSAL}care!$"

