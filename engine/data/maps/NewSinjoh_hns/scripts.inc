@ Johto (data/maps/NewSinjoh_hns/scripts.inc), as built into the FireRed game.

NewSinjoh_hns_MapScripts::
	map_script 3, NewSinjoh_On_Transition
	.byte 0

NewSinjoh_On_Transition:
	setflag 9095
	end

NewSinjoh_EventScript_TriggerNorthGate::
	lock
	msgbox NewSinjoh_Text_TriggerNorthGate, MSGBOX_DEFAULT
	closemessage
	applymovement 255, J_Common_Movement_WalkDown1
	waitmovement 0
	release
	end

NewSinjoh_Text_TriggerNorthGate:
	.string "Bette{SE_M_SAND_TOMB}no{SE_M_SPIT_UP}leav{SE_M_REVERSAL}th{SE_M_REVERSAL}Kimono\n"
	.string "girl{SE_M_GRASSWHISTLE}waiting.$"

NewSinjoh_EventScript_PetStantler::
	lock
	faceplayer
	playmoncry 234, 0
	msgbox NewSinjoh_Text_Stantler_Cry, MSGBOX_DEFAULT
	waitmoncry
	closemessage
	release
	end

NewSinjoh_Text_Stantler_Cry:
	.string "Lerrrrr!$"

NewSinjoh_EventScript_Steven::
	msgbox NewSinjoh_Text_Steven, MSGBOX_AUTOCLOSE
	end

NewSinjoh_Text_Steven:
	.string "STEVEN{SE_M_HEAT_WAVE}Ma'am{SE_M_SUPERSONIC}ma{SE_M_YAWN}{SE_M_HEAL_BELL}hel{SE_M_MORNING_SUN}yo{SE_M_DIVE}to\n"
	.string "th{SE_M_REVERSAL}sprin{SE_M_SANDSTORM}ove{SE_M_SAND_TOMB}there?\p"
	.string "I{SE_M_SPIT_UP}seem{SE_M_GRASSWHISTLE}ther{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}plent{SE_M_YAWN}o{SE_M_ACID_ARMOR}room.$"

NewSinjoh_MilkMan_EventScript_Seller::
	lock
	faceplayer
	checkitem ITEM_MOOMOO_MILK, 99
	goto_if_eq 32781, 1, MilkMan_EventScript_Battle
	showmoneybox 0, 0
	msgbox NewSinjoh_MilkMan_text_BuyMilk, MSGBOX_YESNO
	goto_if_eq 32781, TRUE, NewSinjoh_EventScript_MilkMan_BuyMilk
	msgbox NewSinjoh_MilkMan_NoSale, MSGBOX_DEFAULT
	hidemoneybox
	closemessage
	release
	end

NewSinjoh_EventScript_MilkMan_BuyMilk::
	checkmoney 500, 0
	goto_if_eq 32781, FALSE, NewSinjoh_MilkMan_NotEnough
	additem ITEM_MOOMOO_MILK
	goto_if_eq 32781, FALSE, NewSinjoh_MilkMan_BagFull
	removemoney 500
	updatemoneybox 0
	msgbox NewSinjoh_MilkMan_Text_WouldYouLikeAnother, MSGBOX_YESNO
	goto_if_eq 32781, TRUE, NewSinjoh_EventScript_MilkMan_BuyMilk

	msgbox NewSinjoh_MilkMan_GotMilk, MSGBOX_DEFAULT
	closemessage
	playse 370
	msgbox NewSinjoh_Text_GotMilk, MSGBOX_DEFAULT
	closemessage
	hidemoneybox
	release
	end

NewSinjoh_MilkMan_BagFull::
	msgbox NewSinjoh_MilkMan_NoRoom, MSGBOX_DEFAULT
	hidemoneybox
	closemessage
	release
	end

NewSinjoh_MilkMan_NotEnough::
	msgbox NewSinjoh_MilkMan_NoMoney, MSGBOX_DEFAULT
	closemessage
	hidemoneybox
	release
	end

NewSinjoh_MilkMan_text_BuyMilk:
	.string "{SE_M_HEAL_BELL}a{SE_M_MILK_DRINK}th{SE_M_REVERSAL}Milkman.\p"
	.string "M{SE_M_YAWN}mil{SE_M_ENCORE2}i{SE_M_GRASSWHISTLE}delicious.\p"
	.string "I{SE_M_ACID_ARMOR}yo{SE_M_DIVE}woul{SE_M_WATERFALL}lik{SE_M_REVERSAL}som{SE_M_REVERSAL}today{SE_M_SUPERSONIC}it'l{SE_M_BATON_PASS}be\n"
	.string "¥500.$"

NewSinjoh_MilkMan_GotMilk:
	.string "Her{SE_M_REVERSAL}y{SE_M_CHARGE}go!\n"
	.string "It'{SE_M_GRASSWHISTLE}fortifie{SE_M_WATERFALL}wit{SE_M_TRI_ATTACK}wha{SE_M_SPIT_UP}th{SE_M_REVERSAL}worl{SE_M_WATERFALL}wants.$"

NewSinjoh_MilkMan_NoMoney:
	.string "Sorry.\n"
	.string "Ge{SE_M_SPIT_UP}som{SE_M_REVERSAL}cash{SE_M_SUPERSONIC}the{SE_M_ATTRACT}yo{SE_M_DIVE}wil{SE_M_BATON_PASS}ge{SE_M_SPIT_UP}{SE_M_CHARGE}sale!$"

NewSinjoh_MilkMan_NoRoom:
	.string "Look'{SE_M_GRASSWHISTLE}lik{SE_M_REVERSAL}you{SE_M_SAND_TOMB}PACK'{SE_M_GRASSWHISTLE}full.$"

NewSinjoh_MilkMan_NoSale:
	.string "Don'{SE_M_SPIT_UP}yo{SE_M_DIVE}wan{SE_M_SPIT_UP}it?\n"
	.string "I{SE_M_SPIT_UP}got{SE_M_GRASSWHISTLE}wha{SE_M_SPIT_UP}th{SE_M_REVERSAL}worl{SE_M_WATERFALL}deserves.$"

NewSinjoh_MilkMan_Text_WouldYouLikeAnother:
	.string "Ho{SE_M_TWISTER}bou{SE_M_SPIT_UP}another?$"

NewSinjoh_Text_GotMilk:
	.string "{PLAYER} go{SE_M_SPIT_UP}MOOMO{SE_M_SOLAR_BEAM}MILK.$"

MilkMan_EventScript_Battle::
	msgbox MilkMan_Battle_text
	Trainerbattle_no_intro 1632, NewSinjoh_MilkMan_text_Lose
	release
	end

MilkMan_Battle_text:
	.string "{SE_M_HEAL_BELL}a{SE_M_MILK_DRINK}th{SE_M_REVERSAL}MilkMan,\p"
	.string "M{SE_M_YAWN}mil{SE_M_ENCORE2}i{SE_M_GRASSWHISTLE}delicious.\p"
	.string "Specia{SE_M_BATON_PASS}deliver{SE_M_YAWN}today!$"

NewSinjoh_MilkMan_text_Lose:
	.string "Thi{SE_M_GRASSWHISTLE}worl{SE_M_WATERFALL}i{SE_M_GRASSWHISTLE}perfect.\n"
	.string "isn'{SE_M_SPIT_UP}it?$"

NewSinjoh_Script_TravelMart::
	lock
	faceplayer
	message NewSinjoh_Text_TravelShopGreeting
	waitmessage
	pokemart NewSinjoh_Pokemart_TravelShop
	msgbox NewSinjoh_Text_TravelShopEnd, MSGBOX_DEFAULT
	release
	end

	.align 2

NewSinjoh_Pokemart_TravelShop:
	.2byte ITEM_ENERGY_ROOT
	.2byte ITEM_REVIVAL_HERB
	.2byte ITEM_HEAL_POWDER
	.2byte ITEM_ELIXER
	.2byte ITEM_MAX_REPEL
	.2byte ITEM_MAX_LURE
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_NONE

NewSinjoh_Text_TravelShopGreeting:
	.string "Welcom{SE_M_REVERSAL}t{SE_M_ATTRACT2}M{SE_M_YAWN}littl{SE_M_REVERSAL}Suppl{SE_M_YAWN}Shop.\n"
	.string "Ho{SE_M_TWISTER}ca{SE_M_ATTRACT}{SE_M_HEAL_BELL}hel{SE_M_MORNING_SUN}you?$"

NewSinjoh_Text_TravelShopEnd:
	.string "D{SE_M_ATTRACT2}com{SE_M_REVERSAL}back.$"

Script_NewSinjoh_Traveler_Brother::
	lock
	faceplayer
	msgbox NewSinjoh_Text_TravelBrother_Greeting
	release
	end

NewSinjoh_Text_TravelBrother_Greeting:
	.string "Al{SE_M_BATON_PASS}ou{SE_M_SAND_TOMB}good{SE_M_GRASSWHISTLE}ar{SE_M_REVERSAL}homemade\n"
	.string "an{SE_M_WATERFALL}grow{SE_M_ATTRACT}locally!\p"
	.string "M{SE_M_YAWN}bi{SE_M_SANDSTORM}siste{SE_M_SAND_TOMB}opene{SE_M_WATERFALL}u{SE_M_MORNING_SUN}thi{SE_M_GRASSWHISTLE}shop,\n"
	.string "becaus{SE_M_REVERSAL}th{SE_M_REVERSAL}POKéMAR{SE_M_SWIFT}company\l"
	.string "won'{SE_M_SPIT_UP}ope{SE_M_ATTRACT}{SE_M_CHARGE}location\l"
	.string "thi{SE_M_GRASSWHISTLE}fa{SE_M_SAND_TOMB}ou{SE_M_SPIT_UP}fro{SE_M_MILK_DRINK}{SE_M_CHARGE}majo{SE_M_SAND_TOMB}town.$"

NewSinjoh_EventScript_Josh::
	msgbox NewSinjoh_Text_Josh, MSGBOX_NPC
	end

NewSinjoh_Text_Josh:
	.string "Thi{SE_M_GRASSWHISTLE}plac{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}sick!\p"
	.string "Hidin{SE_M_SANDSTORM}thes{SE_M_REVERSAL}ho{SE_M_SPIT_UP}springs\n"
	.string "fro{SE_M_MILK_DRINK}th{SE_M_REVERSAL}worl{SE_M_WATERFALL}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}travesty.\p"
	.string "I'{SE_M_MILK_DRINK}gonn{SE_M_CHARGE}tel{SE_M_BATON_PASS}al{SE_M_BATON_PASS}m{SE_M_YAWN}friends!$"

NewSinjoh_EventScript_Janice::
	goto_if_ge 20639, 13, NewSinjoh_EventScript_JaniceAfter
	msgbox NewSinjoh_Text_Janice, MSGBOX_NPC
	end

NewSinjoh_EventScript_JaniceAfter::
	msgbox NewSinjoh_Text_JaniceAfter, MSGBOX_NPC
	end

NewSinjoh_Text_Janice:
	.string "Thes{SE_M_REVERSAL}spring{SE_M_GRASSWHISTLE}ar{SE_M_REVERSAL}magical,\n"
	.string "bu{SE_M_SPIT_UP}{SE_M_HEAL_BELL}fee{SE_M_BATON_PASS}lik{SE_M_REVERSAL}th{SE_M_REVERSAL}locals\l"
	.string "ar{SE_M_REVERSAL}givin{SE_M_SANDSTORM}u{SE_M_GRASSWHISTLE}dirt{SE_M_YAWN}looks.$"

NewSinjoh_Text_JaniceAfter:
	.string "Thes{SE_M_REVERSAL}spring{SE_M_GRASSWHISTLE}ar{SE_M_REVERSAL}magical,\n"
	.string "an{SE_M_WATERFALL}th{SE_M_REVERSAL}local{SE_M_GRASSWHISTLE}ar{SE_M_REVERSAL}s{SE_M_ATTRACT2}kind\l"
	.string "whe{SE_M_ATTRACT}yo{SE_M_DIVE}ge{SE_M_SPIT_UP}t{SE_M_ATTRACT2}kno{SE_M_TWISTER}them!$"

NewSinjoh_EventScript_OldLady1::
	msgbox NewSinjoh_Text_OldLady1, MSGBOX_NPC
	end

NewSinjoh_Text_OldLady1:
	.string "There'{SE_M_GRASSWHISTLE}nothin{SE_M_SANDSTORM}lik{SE_M_REVERSAL}{SE_M_CHARGE}nic{SE_M_REVERSAL}vie{SE_M_TWISTER}to\n"
	.string "invigorat{SE_M_REVERSAL}thi{SE_M_GRASSWHISTLE}ol{SE_M_WATERFALL}soul.$"

NewSinjoh_EventScript_OldLady2::
	goto_if_ge 20639, 13, NewSinjoh_EventScript_OldLady2Steven
	msgbox NewSinjoh_Text_OldLady2, MSGBOX_NPC
	end

NewSinjoh_EventScript_OldLady2Steven::
	msgbox NewSinjoh_Text_OldLady2Steven, MSGBOX_NPC
	end

NewSinjoh_Text_OldLady2:
	.string "Great{SE_M_SUPERSONIC}no{SE_M_TWISTER}thes{SE_M_REVERSAL}tourists\n"
	.string "ar{SE_M_REVERSAL}hoggin{SE_M_SANDSTORM}ou{SE_M_SAND_TOMB}ho{SE_M_SPIT_UP}springs!\p"
	.string "It'{SE_M_GRASSWHISTLE}bee{SE_M_ATTRACT}on{SE_M_REVERSAL}ba{SE_M_WATERFALL}thin{SE_M_SANDSTORM}after\n"
	.string "anothe{SE_M_SAND_TOMB}lately!$"

NewSinjoh_Text_OldLady2Steven:
	.string "Wha{SE_M_SPIT_UP}{SE_M_CHARGE}handsom{SE_M_REVERSAL}youn{SE_M_SANDSTORM}man!\p"
	.string "Mayb{SE_M_REVERSAL}thes{SE_M_REVERSAL}tourist{SE_M_GRASSWHISTLE}aren't\n"
	.string "s{SE_M_ATTRACT2}ba{SE_M_WATERFALL}afte{SE_M_SAND_TOMB}all.$"

NewSinjoh_EventScript_OldLady3::
	goto_if_ge 20639, 13, NewSinjoh_EventScript_OldLady3After
	msgbox NewSinjoh_Text_OldLady3, MSGBOX_NPC
	end

NewSinjoh_EventScript_OldLady3After::
	msgbox NewSinjoh_Text_OldLady3After, MSGBOX_NPC
	end

NewSinjoh_Text_OldLady3:
	.string "Ho{SE_M_TWISTER}ca{SE_M_ATTRACT}tha{SE_M_SPIT_UP}woman\n"
	.string "b{SE_M_REVERSAL}s{SE_M_ATTRACT2}rud{SE_M_REVERSAL}t{SE_M_ATTRACT2}ou{SE_M_SAND_TOMB}guests?\p"
	.string "Sh{SE_M_REVERSAL}need{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}tak{SE_M_REVERSAL}{SE_M_CHARGE}dip\n"
	.string "i{SE_M_ATTRACT}th{SE_M_REVERSAL}springs{SE_M_PERISH_SONG}\p"
	.string "Ther{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}plent{SE_M_YAWN}o{SE_M_ACID_ARMOR}space\n"
	.string "fo{SE_M_SAND_TOMB}everyone.$"

NewSinjoh_Text_OldLady3After:
	.string "I{SE_M_SPIT_UP}seem{SE_M_GRASSWHISTLE}everybod{SE_M_YAWN}i{SE_M_GRASSWHISTLE}getting\n"
	.string "use{SE_M_WATERFALL}t{SE_M_ATTRACT2}eac{SE_M_TRI_ATTACK}othe{SE_M_SAND_TOMB}aroun{SE_M_WATERFALL}here.\p"
	.string "Good!$"

NewSinjoh_EventScript_SpringsSage::
	goto_if_ge 20639, 13, NewSinjoh_EventScript_SpringsSageAfter
	msgbox NewSinjoh_Text_SpringsSage, MSGBOX_NPC
	end

NewSinjoh_EventScript_SpringsSageAfter::
	msgbox NewSinjoh_Text_SpringsSageAfter, MSGBOX_NPC
	end

NewSinjoh_Text_SpringsSage:
	.string "Ther{SE_M_REVERSAL}ha{SE_M_GRASSWHISTLE}bee{SE_M_ATTRACT}muc{SE_M_TRI_ATTACK}division\n"
	.string "an{SE_M_WATERFALL}strif{SE_M_REVERSAL}i{SE_M_ATTRACT}ou{SE_M_SAND_TOMB}community\l"
	.string "sinc{SE_M_REVERSAL}th{SE_M_REVERSAL}newcomer{SE_M_GRASSWHISTLE}arrived.\p"
	.string "Regardles{SE_M_GRASSWHISTLE}o{SE_M_ACID_ARMOR}you{SE_M_SAND_TOMB}perspective,\n"
	.string "i{SE_M_SPIT_UP}i{SE_M_GRASSWHISTLE}clea{SE_M_SAND_TOMB}tha{SE_M_SPIT_UP}th{SE_M_REVERSAL}balanc{SE_M_REVERSAL}has\l"
	.string "bee{SE_M_ATTRACT}disturbed.\p"
	.string "Pleas{SE_M_REVERSAL}b{SE_M_REVERSAL}kin{SE_M_WATERFALL}t{SE_M_ATTRACT2}local{SE_M_GRASSWHISTLE}and\n"
	.string "tourist{SE_M_GRASSWHISTLE}alike.$"

NewSinjoh_Text_SpringsSageAfter:
	.string "Thing{SE_M_GRASSWHISTLE}hav{SE_M_REVERSAL}bee{SE_M_ATTRACT}bette{SE_M_SAND_TOMB}since\n"
	.string "th{SE_M_REVERSAL}legendar{SE_M_YAWN}POKéMO{SE_M_PSYBEAM2}wer{SE_M_REVERSAL}quelled.\p"
	.string "Balanc{SE_M_REVERSAL}ha{SE_M_GRASSWHISTLE}returne{SE_M_WATERFALL}t{SE_M_ATTRACT2}SINJOH.$"

NewSinjoh_EventScript_Sage2::
	msgbox NewSinjoh_Text_Sage2, MSGBOX_NPC
	end

NewSinjoh_Text_Sage2:
	.string "Time{SE_M_GRASSWHISTLE}change{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}th{SE_M_REVERSAL}STANTLER\n"
	.string "stil{SE_M_BATON_PASS}gather{SE_M_PERISH_SONG}Fo{SE_M_SAND_TOMB}that{SE_M_SUPERSONIC}w{SE_M_REVERSAL}can\l"
	.string "b{SE_M_REVERSAL}thankful.$"

NewSinjoh_EventScript_Daughter::
	msgbox NewSinjoh_Text_Daughter, MSGBOX_NPC
	end

NewSinjoh_Text_Daughter:
	.string "Wheeeeee!!\p"
	.string "Look{SE_M_SUPERSONIC}Mommy!\n"
	.string "N{SE_M_ATTRACT2}hands!\p"
	.string "Jus{SE_M_SPIT_UP}lik{SE_M_REVERSAL}th{SE_M_REVERSAL}snowboarders!$"

NewSinjoh_EventScript_Mother::
	lock
	faceplayer
	msgbox NewSinjoh_Text_Mother, MSGBOX_DEFAULT
	closemessage
	turnobject 22, DIR_EAST
	release
	end

NewSinjoh_Text_Mother:
	.string "Loo{SE_M_ENCORE2}a{SE_M_SPIT_UP}m{SE_M_YAWN}adorabl{SE_M_REVERSAL}bab{SE_M_YAWN}go!\p"
	.string "Thi{SE_M_GRASSWHISTLE}rin{SE_M_ENCORE2}ha{SE_M_GRASSWHISTLE}bee{SE_M_ATTRACT}here\n"
	.string "fo{SE_M_SAND_TOMB}generations{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}th{SE_M_REVERSAL}children\l"
	.string "neve{SE_M_SAND_TOMB}use{SE_M_WATERFALL}i{SE_M_SPIT_UP}unti{SE_M_BATON_PASS}th{SE_M_REVERSAL}newcomers\l"
	.string "arrived.$"

NewSinjoh_EventScript_Welcome_Sign::
	msgbox NewSinjoh_Text_Welcome_Sign, MSGBOX_SIGN
	end

NewSinjoh_Text_Welcome_Sign:
	.string "NE{SE_M_DETECT}SINJOH$"

NewSinjoh_EventScript_Resturant_Sign::
	msgbox NewSinjoh_Text_Resturant_Sign, MSGBOX_SIGN
	end

NewSinjoh_Text_Resturant_Sign:
	.string "FAMIL{SE_M_MOONLIGHT}CAFE$"

NewSinjoh_EventScript_Cave_Sign::
	msgbox NewSinjoh_Text_Cave_Sign, MSGBOX_SIGN
	end

NewSinjoh_Text_Cave_Sign:
	.string "HO{SE_M_SWIFT}SPRING{SE_M_SKETCH}CAVE$"

NewSinjoh_EventScript_Hiker::
	goto_if_ge 20639, 13, NewSinjoh_EventScript_HikerAfter
	msgbox NewSinjoh_Text_Hiker, MSGBOX_NPC
	end

NewSinjoh_EventScript_HikerAfter::
	msgbox NewSinjoh_Text_HikerAfter, MSGBOX_NPC
	end

NewSinjoh_Text_Hiker:
	.string "Busines{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}booming!\n"
	.string "Bu{SE_M_SPIT_UP}price{SE_M_GRASSWHISTLE}hav{SE_M_REVERSAL}gon{SE_M_REVERSAL}u{SE_M_MORNING_SUN}since\l"
	.string "th{SE_M_REVERSAL}cit{SE_M_YAWN}fol{SE_M_ENCORE2}becam{SE_M_REVERSAL}interested\l"
	.string "i{SE_M_ATTRACT}ou{SE_M_SAND_TOMB}littl{SE_M_REVERSAL}town.$"

NewSinjoh_Text_HikerAfter:
	.string "Busines{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}booming!\p"
	.string "An{SE_M_WATERFALL}wit{SE_M_TRI_ATTACK}ho{SE_M_TWISTER}muc{SE_M_TRI_ATTACK}tha{SE_M_SPIT_UP}silve{SE_M_SAND_TOMB}haried\n"
	.string "gu{SE_M_YAWN}tips{SE_M_SUPERSONIC}price{SE_M_GRASSWHISTLE}hav{SE_M_REVERSAL}com{SE_M_REVERSAL}down!$"

NewSinjoh_EventScript_OldLady4::
	goto_if_ge 20639, 13, NewSinjoh_EventScript_OldLady4After
	msgbox NewSinjoh_Text_OldLady4, MSGBOX_NPC
	end

NewSinjoh_EventScript_OldLady4After::
	msgbox NewSinjoh_Text_OldLady4After, MSGBOX_NPC
	end

NewSinjoh_Text_OldLady4:
	.string "{SE_M_HEAL_BELL}onl{SE_M_YAWN}sel{SE_M_BATON_PASS}t{SE_M_ATTRACT2}locals!$"

NewSinjoh_Text_OldLady4After:
	.string "{SE_M_HEAL_BELL}STIL{SE_M_BRICK_BREAK}onl{SE_M_YAWN}sel{SE_M_BATON_PASS}t{SE_M_ATTRACT2}locals!$"

NewSinjoh_EventScript_Item_DuskBall::
	finditem ITEM_DUSK_BALL
	end

