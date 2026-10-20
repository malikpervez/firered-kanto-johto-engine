@ Johto (data/maps/GoldenrodCity_FlowerShop_hns/scripts.inc), as built into the FireRed game.

GoldenrodCity_FlowerShop_hns_MapScripts::
	.byte 0

GoldenrodCity_FlowerShop_EventScript_MintClerk::
	lock
	faceplayer
	goto_if_unset 10370, GoldenrodCity_FlowerShop_EventScript_MintClerkNotReady
	message J_gText_HowMayIServeYou
	waitmessage
	pokemart GoldenrodCity_FlowerShop_Mints
	msgbox J_gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

GoldenrodCity_FlowerShop_EventScript_MintClerkNotReady::
	msgbox GoldenrodCity_FlowerShop_Text_MintClerkNotReady, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_FlowerShop_Text_MintClerkNotReady:
	.byte 0xD1, 0xD9, 0x00, 0xD5, 0xE6, 0xD9, 0x00, 0xD7, 0xE9, 0xE6, 0xE6, 0xD9, 0xE2, 0xE8, 0xE0, 0xED, 0x00, 0xE3, 0xE9, 0xE8, 0x00, 0xE3, 0xDA, 0x00, 0xE7, 0xE8, 0xE3, 0xD7, 0xDF, 0xAD, 0xFB
	.byte 0xCA, 0xE0, 0xD9, 0xD5, 0xE7, 0xD9, 0x00, 0xD7, 0xE3, 0xE1, 0xD9, 0x00, 0xD6, 0xD5, 0xD7, 0xDF, 0x00, 0xE0, 0xD5, 0xE8, 0xD9, 0xE6, 0xAD, 0xFF

	.align 2

GoldenrodCity_FlowerShop_Mints:
	.2byte ITEM_SERIOUS_MINT
	.2byte ITEM_ADAMANT_MINT
	.2byte ITEM_BOLD_MINT
	.2byte ITEM_BRAVE_MINT
	.2byte ITEM_CALM_MINT
	.2byte ITEM_CAREFUL_MINT
	.2byte ITEM_GENTLE_MINT
	.2byte ITEM_HASTY_MINT
	.2byte ITEM_IMPISH_MINT
	.2byte ITEM_JOLLY_MINT
	.2byte ITEM_LAX_MINT
	.2byte ITEM_LONELY_MINT
	.2byte ITEM_MILD_MINT
	.2byte ITEM_MODEST_MINT
	.2byte ITEM_NAIVE_MINT
	.2byte ITEM_NAUGHTY_MINT
	.2byte ITEM_QUIET_MINT
	.2byte ITEM_RASH_MINT
	.2byte ITEM_RELAXED_MINT
	.2byte ITEM_SASSY_MINT
	.2byte ITEM_TIMID_MINT
	pokemartlistend

GoldenrodCity_FlowerShop_EventScript_Owner::
	lock
	faceplayer
	goto_if_set 8246, GoldenrodCity_FlowerShop_EventScript_Normal
	goto_if_set 8702, GoldenrodCity_FlowerShop_EventScript_GotSquirtBottle
	goto_if_set 10370, GoldenrodCity_FlowerShop_EventScript_GiveSquirtBottle
	msgbox GoldenrodCity_FlowerShop_Text_Owner1, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_FlowerShop_EventScript_GiveSquirtBottle::
	lock
	faceplayer
	msgbox GoldenrodCity_FlowerShop_Text_Owner2, MSGBOX_DEFAULT
	giveitem ITEM_SQUIRT_BOTTLE
	setflag 8702
	closemessage
	release
	end

GoldenrodCity_FlowerShop_EventScript_GotSquirtBottle::
	lock
	faceplayer
	msgbox GoldenrodCity_FlowerShop_Text_Owner3, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_FlowerShop_EventScript_Normal::
	lock
	faceplayer
	msgbox GoldenrodCity_FlowerShop_Text_Owner4, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_FlowerShop_EventScript_Floria1::
	lock
	faceplayer
	goto_if_set 8246, GoldenrodCity_FlowerShop_EventScript_Floria3
	goto_if_set 10370, GoldenrodCity_FlowerShop_EventScript_Floria2
	msgbox GoldenrodCity_FlowerShop_Text_Floria, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_FlowerShop_EventScript_Floria2::
	msgbox GoldenrodCity_FlowerShop_Text_FloriaYouBeatWhitney, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_FlowerShop_EventScript_Floria3::
	msgbox GoldenrodCity_FlowerShop_Text_FloriaItWasAMon, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_FlowerShop_Text_Floria:
	.string "Whe{SE_M_ATTRACT}{SE_M_HEAL_BELL}tol{SE_M_WATERFALL}m{SE_M_YAWN}si{SE_M_GRASSWHISTLE}abou{SE_M_SPIT_UP}th{SE_M_REVERSAL}jiggly\n"
	.string "tree{SE_M_SUPERSONIC}sh{SE_M_REVERSAL}sai{SE_M_WATERFALL}it'{SE_M_GRASSWHISTLE}dangerous.\p"
	.string "I{SE_M_ACID_ARMOR}{SE_M_HEAL_BELL}bea{SE_M_SPIT_UP}WHITNEY{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}wonde{SE_M_SAND_TOMB}if\n"
	.string "she'l{SE_M_BATON_PASS}len{SE_M_WATERFALL}m{SE_M_REVERSAL}he{SE_M_SAND_TOMB}wate{SE_M_SAND_TOMB}bottle…$"

GoldenrodCity_FlowerShop_Text_Owner1:
	.string "Apparently{SE_M_SUPERSONIC}ther{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}a{SE_M_ATTRACT}od{SE_M_WATERFALL}tree\n"
	.string "o{SE_M_ATTRACT}ROUT{SE_M_SWORDS_DANCE}36.\p"
	.string "The{SE_M_YAWN}sa{SE_M_YAWN}i{SE_M_SPIT_UP}dance{SE_M_GRASSWHISTLE}whe{SE_M_ATTRACT}yo{SE_M_DIVE}water\n"
	.string "it...\p"
	.string "Oh{SE_M_SUPERSONIC}o{SE_M_ACID_ARMOR}cours{SE_M_REVERSAL}not!\p"
	.string "Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}flowe{SE_M_SAND_TOMB}shop{SE_M_SUPERSONIC}s{SE_M_ATTRACT2}w{SE_M_REVERSAL}do\n"
	.string "hav{SE_M_REVERSAL}waterin{SE_M_SANDSTORM}cans...\p"
	.string "Bu{SE_M_SPIT_UP}{SE_M_HEAL_BELL}canno{SE_M_SPIT_UP}le{SE_M_SPIT_UP}yo{SE_M_DIVE}hav{SE_M_REVERSAL}one!\n"
	.string "It'{SE_M_GRASSWHISTLE}to{SE_M_ATTRACT2}dangerous!\p"
	.string "Well{SE_M_SUPERSONIC}mayb{SE_M_REVERSAL}i{SE_M_ACID_ARMOR}yo{SE_M_DIVE}manag{SE_M_REVERSAL}to\n"
	.string "defea{SE_M_SPIT_UP}gy{SE_M_MILK_DRINK}leade{SE_M_SAND_TOMB}WHITNEY{SE_M_SUPERSONIC}it\l"
	.string "migh{SE_M_SPIT_UP}b{SE_M_REVERSAL}okay.$"

GoldenrodCity_FlowerShop_Text_Owner2:
	.string "Apparently{SE_M_SUPERSONIC}ther{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}a{SE_M_ATTRACT}od{SE_M_WATERFALL}tree\n"
	.string "o{SE_M_ATTRACT}ROUT{SE_M_SWORDS_DANCE}36.\p"
	.string "The{SE_M_YAWN}sa{SE_M_YAWN}i{SE_M_SPIT_UP}dance{SE_M_GRASSWHISTLE}whe{SE_M_ATTRACT}yo{SE_M_DIVE}water\n"
	.string "it...\p"
	.string "Oh{SE_M_SUPERSONIC}that'{SE_M_GRASSWHISTLE}{SE_M_CHARGE}PLAINBADG{SE_M_SWORDS_DANCE}from\n"
	.string "th{SE_M_REVERSAL}GOLDENRO{SE_M_FAINT_ATTACK}GYM!\p"
	.string "Di{SE_M_WATERFALL}yo{SE_M_DIVE}defea{SE_M_SPIT_UP}WHITNEY?!\p"
	.string "Well{SE_M_SUPERSONIC}the{SE_M_ATTRACT}there'{SE_M_GRASSWHISTLE}nothin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}worry\n"
	.string "about{SE_M_SUPERSONIC}i{SE_M_GRASSWHISTLE}there?\p"
	.string "I'l{SE_M_BATON_PASS}le{SE_M_SPIT_UP}yo{SE_M_DIVE}us{SE_M_REVERSAL}thi{SE_M_GRASSWHISTLE}SQUIRTBOTTLE\n"
	.string "fo{SE_M_SAND_TOMB}{SE_M_CHARGE}whil{SE_M_REVERSAL}then.\l"
	.string "...\p"
	.string "Oh{SE_M_SUPERSONIC}neve{SE_M_SAND_TOMB}mind{SE_M_PERISH_SONG}Kee{SE_M_MORNING_SUN}it!$"

GoldenrodCity_FlowerShop_Text_Owner3:
	.string "Th{SE_M_REVERSAL}od{SE_M_WATERFALL}tre{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}o{SE_M_ATTRACT}ROUT{SE_M_SWORDS_DANCE}36.\n"
	.string "Pleas{SE_M_REVERSAL}b{SE_M_REVERSAL}careful!$"

GoldenrodCity_FlowerShop_Text_Owner4:
	.string "Lalal{SE_M_CHARGE}lalalala{SE_M_PERISH_SONG}Hav{SE_M_REVERSAL}plent{SE_M_YAWN}of\n"
	.string "water{SE_M_SUPERSONIC}m{SE_M_YAWN}lovely!$"

GoldenrodCity_FlowerShop_Text_FloriaYouBeatWhitney:
	.string "Wow{SE_M_SUPERSONIC}yo{SE_M_DIVE}bea{SE_M_SPIT_UP}WHITNEY{SE_M_SING}Cool!$"

GoldenrodCity_FlowerShop_Text_FloriaItWasAMon:
	.string "S{SE_M_ATTRACT2}i{SE_M_SPIT_UP}reall{SE_M_YAWN}wa{SE_M_GRASSWHISTLE}{SE_M_CHARGE}POKéMON!$"

GoldenrodCity_FlowerShop_EventScript_RandomBerryGirl::
	lock
	faceplayer
	dotimebasedevents
	goto_if_set 10522, GoldenrodCity_FlowerShop_EventScript_AlreadyReceivedBerry
	msgbox J_Route104_PrettyPetalFlowerShop_Text_ImGrowingFlowers, MSGBOX_DEFAULT
	random 8
	addvar 32781, FIRST_BERRY_INDEX
	giveitem 32781
	goto_if_eq 32781, 0, J_Common_EventScript_ShowBagIsFull
	setflag 10522
	msgbox J_Route104_PrettyPetalFlowerShop_Text_MachineMixesBerries, MSGBOX_DEFAULT
	release
	end

GoldenrodCity_FlowerShop_EventScript_AlreadyReceivedBerry::
	msgbox J_Route104_PrettyPetalFlowerShop_Text_MachineMixesBerries, MSGBOX_DEFAULT
	release
	end

