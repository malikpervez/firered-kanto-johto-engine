@ Johto (data/maps/GoldenrodCity_BikeShop_hns/scripts.inc), as built into the FireRed game.

GoldenrodCity_BikeShop_hns_MapScripts::
	.byte 0

GoldenrodCity_BikeShop_EventScript_Clerk::
	lock
	faceplayer
	goto_if_set 8690, GoldenrodCity_BikeShop_EventScript_Clerk_BikeReceived
	msgbox GoldenrodCity_BikeShop_Text_ClerkIntro, MSGBOX_YESNO
	goto_if_eq 32781, TRUE, GoldenrodCity_BikeShop_EventScript_Clerk_BikeAgreed
	msgbox GoldenrodCity_BikeShop_Text_Refused, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_BikeShop_EventScript_Clerk_BikeAgreed::
	msgbox GoldenrodCity_BikeShop_Text_ClerkAgreed, MSGBOX_DEFAULT
	giveitem ITEM_BICYCLE
	setflag 8690
	closemessage
	release
	end

GoldenrodCity_BikeShop_EventScript_Clerk_BikeReceived::
	msgbox GoldenrodCity_BikeShop_Text_Mainshop, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_BikeShop_EventScript_Clerk2::
	lock
	faceplayer
	msgbox GoldenrodCity_BikeShop_Text_Clerk2, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_BikeShop_EventScript_Bike::
	lock
	msgbox GoldenrodCity_BikeShop_Text_Bicycle, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_BikeShop_Text_Clerk2:
	.string "Ridin{SE_M_SANDSTORM}th{SE_M_REVERSAL}BIK{SE_M_SWORDS_DANCE}i{SE_M_GRASSWHISTLE}a{SE_M_GRASSWHISTLE}simpl{SE_M_REVERSAL}as\n"
	.string "pressin{SE_M_SANDSTORM}{SE_M_CHARGE}butto{SE_M_ATTRACT}i{SE_M_ACID_ARMOR}you\l"
	.string "REGISTE{SE_M_MINIMIZE}i{SE_M_SPIT_UP}fro{SE_M_MILK_DRINK}th{SE_M_REVERSAL}BAG.\p"
	.string "I{SE_M_ACID_ARMOR}yo{SE_M_DIVE}nee{SE_M_WATERFALL}t{SE_M_ATTRACT2}g{SE_M_ATTRACT2}faster,\n"
	.string "yo{SE_M_DIVE}firs{SE_M_SPIT_UP}nee{SE_M_WATERFALL}t{SE_M_ATTRACT2}com{SE_M_REVERSAL}t{SE_M_ATTRACT2}{SE_M_CHARGE}stop!\p"
	.string "Tha{SE_M_SPIT_UP}migh{SE_M_SPIT_UP}see{SE_M_MILK_DRINK}lik{SE_M_REVERSAL}strange\n"
	.string "advice{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}yo{SE_M_DIVE}ca{SE_M_ATTRACT}onl{SE_M_YAWN}change\l"
	.string "gear{SE_M_GRASSWHISTLE}o{SE_M_ATTRACT}th{SE_M_REVERSAL}BIK{SE_M_SWORDS_DANCE}whil{SE_M_REVERSAL}stopped.\p"
	.string "Pres{SE_M_GRASSWHISTLE}you{SE_M_SAND_TOMB}{SE_M_MINIMIZE}butto{SE_M_ATTRACT}whe{SE_M_ATTRACT}stopped\n"
	.string "an{SE_M_WATERFALL}th{SE_M_REVERSAL}nex{SE_M_SPIT_UP}tim{SE_M_REVERSAL}yo{SE_M_DIVE}pedal,\l"
	.string "yo{SE_M_DIVE}wil{SE_M_BATON_PASS}reac{SE_M_TRI_ATTACK}greate{SE_M_SAND_TOMB}speeds!$"

GoldenrodCity_BikeShop_Text_ClerkIntro:
	.string "…sigh{SE_M_DIZZY_PUNCH}{SE_M_HEAL_BELL}move{SE_M_WATERFALL}here{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}{SE_M_HEAL_BELL}can't\n"
	.string "sel{SE_M_BATON_PASS}m{SE_M_YAWN}BICYCLES{SE_M_PERISH_SONG}Wh{SE_M_YAWN}i{SE_M_GRASSWHISTLE}that?\p"
	.string "Coul{SE_M_WATERFALL}yo{SE_M_DIVE}rid{SE_M_REVERSAL}{SE_M_CHARGE}BICYCL{SE_M_SWORDS_DANCE}and\n"
	.string "advertis{SE_M_REVERSAL}fo{SE_M_SAND_TOMB}me?$"

GoldenrodCity_BikeShop_Text_ClerkAgreed:
	.string "Really{SE_M_SING}Great!\p"
	.string "Giv{SE_M_REVERSAL}m{SE_M_REVERSAL}you{SE_M_SAND_TOMB}nam{SE_M_REVERSAL}an{SE_M_WATERFALL}phon{SE_M_REVERSAL}number,\n"
	.string "an{SE_M_WATERFALL}I'l{SE_M_BATON_PASS}loa{SE_M_ATTRACT}yo{SE_M_DIVE}{SE_M_CHARGE}BICYCLE.$"

GoldenrodCity_BikeShop_Text_BorrowedBicycle:
	.string "{PLAYER} borrowe{SE_M_WATERFALL}{SE_M_CHARGE}BICYCLE.$"

GoldenrodCity_BikeShop_Text_Mainshop:
	.string "Busines{SE_M_GRASSWHISTLE}ha{SE_M_GRASSWHISTLE}bee{SE_M_ATTRACT}har{SE_M_WATERFALL}t{SE_M_ATTRACT2}come\n"
	.string "b{SE_M_YAWN}sinc{SE_M_REVERSAL}w{SE_M_REVERSAL}move{SE_M_WATERFALL}fro{SE_M_MILK_DRINK}KANTO.\l"
	.string "W{SE_M_REVERSAL}appreciat{SE_M_REVERSAL}you{SE_M_SAND_TOMB}help!\p"
	.string "Ca{SE_M_ATTRACT}yo{SE_M_DIVE}mak{SE_M_REVERSAL}sur{SE_M_REVERSAL}t{SE_M_ATTRACT2}sho{SE_M_TWISTER}off\n"
	.string "ou{SE_M_SAND_TOMB}patente{SE_M_WATERFALL}gear-changin{SE_M_SANDSTORM}tech?\p"
	.string "It'{SE_M_GRASSWHISTLE}a{SE_M_GRASSWHISTLE}simpl{SE_M_REVERSAL}a{SE_M_GRASSWHISTLE}pressin{SE_M_SANDSTORM}{SE_M_MINIMIZE}when\n"
	.string "yo{SE_M_DIVE}ar{SE_M_REVERSAL}stoppe{SE_M_WATERFALL}o{SE_M_ATTRACT}you{SE_M_SAND_TOMB}BIKE.\p"
	.string "Beware{SE_M_DRAGON_RAGE}Yo{SE_M_DIVE}wil{SE_M_BATON_PASS}the{SE_M_ATTRACT}g{SE_M_ATTRACT2}faster!$"

GoldenrodCity_BikeShop_Text_Refused:
	.string "…sigh{SE_M_DIZZY_PUNCH}Oh{SE_M_SUPERSONIC}fo{SE_M_SAND_TOMB}th{SE_M_REVERSAL}kindnes{SE_M_GRASSWHISTLE}of\n"
	.string "people…$"

GoldenrodCity_BikeShop_Text_JustReleasedCompact:
	.string "Jus{SE_M_SPIT_UP}released!\p"
	.string "First-rat{SE_M_REVERSAL}compac{SE_M_SPIT_UP}BICYCLES!$"

GoldenrodCity_BikeShop_Text_Bicycle:
	.string "It'{SE_M_GRASSWHISTLE}{SE_M_CHARGE}shin{SE_M_YAWN}ne{SE_M_TWISTER}BICYCLE!$"

