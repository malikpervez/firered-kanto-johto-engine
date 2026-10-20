@ Johto (data/maps/Gate_GoldenrodCity_Route35_hns/scripts.inc), as built into the FireRed game.

Gate_GoldenrodCity_Route35_hns_MapScripts::
	.byte 0

Gate_GoldenrodCity_Route35_EventScript_Randy::
	lock
	faceplayer
	goto_if_eq JOHTO_VAR_KENYA, 3, Gate_GoldenrodCity_Route35_EventScript_RandyPostKenya
	goto_if_eq JOHTO_VAR_KENYA, 2, Gate_GoldenrodCity_Route35_EventScript_RandyDeliveredKenya
	goto_if_eq JOHTO_VAR_KENYA, 1, Gate_GoldenrodCity_Route35_EventScript_RandyHaveKenya
	msgbox Route35GoldenrodGate_Text_RandyAskFavor, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, Gate_GoldenrodCity_Route35_EventScript_RandyCancel
	closemessage

	msgbox Route35GoldenrodGate_Text_RandyThanks, MSGBOX_DEFAULT


	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_SPEAROW
	bufferspeciesname STR_VAR_1, SPECIES_SPEAROW
	givenamedmon 1
	call J_Common_EventScript_GiftMonNamed

	setvar JOHTO_VAR_KENYA, 1
	release
	end

Gate_GoldenrodCity_Route35_EventScript_RandyCancel::
	msgbox Route35GoldenrodGate_Text_RandyNeverMind, MSGBOX_DEFAULT
	closemessage
	release
	end

Gate_GoldenrodCity_Route35_EventScript_RandyHaveKenya::
	msgbox Route35GoldenrodGate_Text_RandyWeirdTree, MSGBOX_DEFAULT
	closemessage
	release
	end

Gate_GoldenrodCity_Route35_EventScript_RandyDeliveredKenya::
	msgbox Route35GoldenrodGate_Text_ThanksForDelivery, MSGBOX_DEFAULT
	closemessage
	giveitem ITEM_HP_UP
	goto_if_eq VAR_RESULT, FALSE, J_Common_EventScript_BagIsFull
	msgbox Route35GoldenrodGate_Text_RandyMyPalSnoozing, MSGBOX_DEFAULT
	closemessage
	setvar JOHTO_VAR_KENYA, 3
	release
	end

Gate_GoldenrodCity_Route35_EventScript_RandyPostKenya::
	msgbox Route35GoldenrodGate_Text_RandyMyPalSnoozing, MSGBOX_DEFAULT
	closemessage
	release
	end

Gate_GoldenrodCity_Route35_EventScript_Lady::
	lock
	faceplayer
	goto_if_set JOHTO_FLAG_HIDE_SUDOWOODO, Gate_GoldenrodCity_Route35_EventScript_Lady2
	msgbox Route35GoldenrodGate_Text_PokefanF_TreeBlocking, MSGBOX_DEFAULT
	closemessage
	release
	end

Gate_GoldenrodCity_Route35_EventScript_Lady2::
	msgbox Route35GoldenrodGate_Text_PokefanF_Lullaby, MSGBOX_DEFAULT
	closemessage
	release
	end

Gate_GoldenrodCity_Route35_EventScript_Fisher::
	lock
	faceplayer
	msgbox Route35GoldenrodGate_Text_Fisher, MSGBOX_DEFAULT
	closemessage
	release
	end

Route35GoldenrodGate_Text_RandyAskFavor:
	.string "Excus{SE_M_REVERSAL}me{SE_M_SUPERSONIC}kid{SE_M_DRAGON_RAGE}Ca{SE_M_ATTRACT}yo{SE_M_DIVE}d{SE_M_ATTRACT2}{SE_M_CHARGE}guy\n"
	.string "{SE_M_CHARGE}favor?\p"
	.string "Ca{SE_M_ATTRACT}yo{SE_M_DIVE}tak{SE_M_REVERSAL}thi{SE_M_GRASSWHISTLE}POKéMO{SE_M_PSYBEAM2}wit{SE_M_TRI_ATTACK}MAIL\n"
	.string "t{SE_M_ATTRACT2}m{SE_M_YAWN}friend?\p"
	.string "He'{SE_M_GRASSWHISTLE}o{SE_M_ATTRACT}ROUT{SE_M_SWORDS_DANCE}31.$"

Route35GoldenrodGate_Text_RandyThanks:
	.string "Yo{SE_M_DIVE}will{SE_M_SING}Perfect{SE_M_DRAGON_RAGE}Thanks{SE_M_SUPERSONIC}kid!\p"
	.string "M{SE_M_YAWN}pal'{SE_M_GRASSWHISTLE}{SE_M_CHARGE}chubb{SE_M_YAWN}gu{SE_M_YAWN}wh{SE_M_ATTRACT2}snoozes\n"
	.string "al{SE_M_BATON_PASS}th{SE_M_REVERSAL}time.\p"
	.string "You'l{SE_M_BATON_PASS}recogniz{SE_M_REVERSAL}hi{SE_M_MILK_DRINK}righ{SE_M_SPIT_UP}away!$"

Route35GoldenrodGate_Text_ReceivedMonWithMail:
	.string "{PLAYER} receive{SE_M_WATERFALL}{SE_M_CHARGE}POKéMO{SE_M_PSYBEAM2}wit{SE_M_TRI_ATTACK}MAIL.$"

Route35GoldenrodGate_Text_RandyWeirdTree:
	.string "Mak{SE_M_REVERSAL}sur{SE_M_REVERSAL}t{SE_M_ATTRACT2}pu{SE_M_SPIT_UP}i{SE_M_SPIT_UP}a{SE_M_SPIT_UP}th{SE_M_REVERSAL}fron{SE_M_SPIT_UP}of\n"
	.string "you{SE_M_SAND_TOMB}tea{SE_M_MILK_DRINK}whe{SE_M_ATTRACT}yo{SE_M_DIVE}fin{SE_M_WATERFALL}m{SE_M_YAWN}friend!\p"
	.string "ROUT{SE_M_SWORDS_DANCE}31!\p"
	.string "Oh{SE_M_SUPERSONIC}yeah{SE_M_PERISH_SONG}Ther{SE_M_REVERSAL}wa{SE_M_GRASSWHISTLE}{SE_M_CHARGE}weir{SE_M_WATERFALL}tree\n"
	.string "blockin{SE_M_SANDSTORM}th{SE_M_REVERSAL}road.\p"
	.string "{SE_M_HEAL_BELL}wonde{SE_M_SAND_TOMB}i{SE_M_ACID_ARMOR}it'{SE_M_GRASSWHISTLE}bee{SE_M_ATTRACT}cleared?$"

Route35GoldenrodGate_Text_CantCarryMoreMon:
	.string "Yo{SE_M_DIVE}can'{SE_M_SPIT_UP}carr{SE_M_YAWN}anothe{SE_M_SAND_TOMB}POKéMON…$"

Route35GoldenrodGate_Text_RandyNeverMind:
	.string "Oh{SE_M_DIZZY_PUNCH}Neve{SE_M_SAND_TOMB}mind{SE_M_SUPERSONIC}then…$"

Route35GoldenrodGate_Text_ThanksForDelivery:
	.string "Thanks{SE_M_SUPERSONIC}kid{SE_M_DRAGON_RAGE}Yo{SE_M_DIVE}mad{SE_M_REVERSAL}th{SE_M_REVERSAL}delivery\n"
	.string "fo{SE_M_SAND_TOMB}me!\p"
	.string "Here'{SE_M_GRASSWHISTLE}somethin{SE_M_SANDSTORM}fo{SE_M_SAND_TOMB}you{SE_M_SAND_TOMB}trouble!$"

Route35GoldenrodGate_Text_RandyMyPalSnoozing:
	.string "M{SE_M_YAWN}pa{SE_M_BATON_PASS}wa{SE_M_GRASSWHISTLE}snoozing{SE_M_SUPERSONIC}right{SE_M_SING}Heh,\n"
	.string "what'{SE_M_WATERFALL}{SE_M_HEAL_BELL}say?$"

Route35GoldenrodGate_Text_PokefanF_TreeBlocking:
	.string "{SE_M_BONEMERANG}strang{SE_M_REVERSAL}tre{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}blockin{SE_M_SANDSTORM}th{SE_M_REVERSAL}road.\p"
	.string "I{SE_M_SPIT_UP}wriggle{SE_M_GRASSWHISTLE}aroun{SE_M_WATERFALL}i{SE_M_ACID_ARMOR}yo{SE_M_DIVE}tal{SE_M_ENCORE2}t{SE_M_ATTRACT2}it.\p"
	.string "{SE_M_HEAL_BELL}hear{SE_M_WATERFALL}i{SE_M_SPIT_UP}becam{SE_M_REVERSAL}wil{SE_M_WATERFALL}whe{SE_M_ATTRACT}someone\n"
	.string "watere{SE_M_WATERFALL}i{SE_M_SPIT_UP}wit{SE_M_TRI_ATTACK}{SE_M_CHARGE}SQUIRTBOTTLE.$"

Route35GoldenrodGate_Text_PokefanF_Lullaby:
	.string "{SE_M_HEAL_BELL}lik{SE_M_REVERSAL}th{SE_M_REVERSAL}POKéMO{SE_M_PSYBEAM2}Lullab{SE_M_YAWN}the{SE_M_YAWN}play\n"
	.string "o{SE_M_ATTRACT}th{SE_M_REVERSAL}radio.$"

Route35GoldenrodGate_Text_Fisher:
	.string "{SE_M_HEAL_BELL}wonde{SE_M_SAND_TOMB}ho{SE_M_TWISTER}man{SE_M_YAWN}kind{SE_M_GRASSWHISTLE}o{SE_M_ACID_ARMOR}POKéMON\n"
	.string "ther{SE_M_REVERSAL}ar{SE_M_REVERSAL}i{SE_M_ATTRACT}th{SE_M_REVERSAL}world.\p"
	.string "Thre{SE_M_REVERSAL}year{SE_M_GRASSWHISTLE}ago{SE_M_SUPERSONIC}PROF.OA{SE_M_SNORE}sai{SE_M_WATERFALL}that\n"
	.string "ther{SE_M_REVERSAL}wer{SE_M_REVERSAL}15{SE_M_BITE}differen{SE_M_SPIT_UP}kinds.\p"
	.string "Bu{SE_M_SPIT_UP}recentl{SE_M_YAWN}{SE_M_HEAL_BELL}hear{SE_M_WATERFALL}there's\n"
	.string "ove{SE_M_SAND_TOMB}400!$"

