@ Johto (data/maps/NationalPark_Normal_hns/scripts.inc), as built into the FireRed game.

NationalPark_Normal_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, NationalPark_Normal_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, J_SetTimeEncounters
	.byte 0

NationalPark_Normal_OnTransition:
	callnative SetTimeBasedEncounters
	end

NationalPark_Normal_EventScript_Lass::
	lock
	faceplayer
	msgbox NationalPark_Normal_Text_Lass, MSGBOX_DEFAULT
	closemessage
	release
	end

NationalPark_Normal_EventScript_Youngster1::
	lock
	faceplayer
	msgbox NationalPark_Normal_Text_Youngster1, MSGBOX_DEFAULT
	closemessage
	release
	end

NationalPark_Normal_EventScript_Youngster2::
	lock
	faceplayer
	msgbox NationalPark_Normal_Text_Youngster2, MSGBOX_DEFAULT
	closemessage
	release
	end

NationalPark_Normal_EventScript_Teacher2::
	lock
	faceplayer
	msgbox NationalPark_Normal_Text_Teacher2, MSGBOX_DEFAULT
	closemessage
	call J_Common_EventScript_OutOfCenterPartyHeal
	release
	end

NationalPark_Normal_EventScript_TeacherQuickclaw::
	lock
	faceplayer
	goto_if_set JOHTO_FLAG_GOT_QUICK_CLAW, NationalPark_Normal_EventScript_TeacherQuickclaw2
	msgbox NationalPark_Normal_Text_Teacher1, MSGBOX_DEFAULT
	giveitem ITEM_QUICK_CLAW
	goto_if_eq VAR_RESULT, FALSE, J_Common_EventScript_BagIsFull
	setflag JOHTO_FLAG_GOT_QUICK_CLAW

NationalPark_Normal_EventScript_TeacherQuickclaw2::
	msgbox NationalPark_Normal_Text_Teacher1_QuickClaw, MSGBOX_DEFAULT
	closemessage
	release
	end

NationalPark_Normal_EventScript_Persian::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_PERSIAN, CRY_MODE_NORMAL
	msgbox NationalPark_Normal_Text_Persian, MSGBOX_DEFAULT
	waitmoncry
	release
	end

NationalPark_Normal_Text_Lass:
	.string "Look{SE_M_DRAGON_RAGE}Chec{SE_M_ENCORE2}ou{SE_M_SPIT_UP}m{SE_M_YAWN}bag!\p"
	.string "{SE_M_HEAL_BELL}printe{SE_M_WATERFALL}ou{SE_M_SPIT_UP}m{SE_M_YAWN}favorite{SE_M_GRASSWHISTLE}fro{SE_M_MILK_DRINK}my\n"
	.string "POKéDE{SE_M_LOCK_ON}an{SE_M_WATERFALL}stuc{SE_M_ENCORE2}the{SE_M_MILK_DRINK}o{SE_M_ATTRACT}m{SE_M_YAWN}bag.$"

NationalPark_Normal_Text_PokefanF:
	.string "Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}MAI{SE_M_BRICK_BREAK}{SE_M_HEAL_BELL}go{SE_M_SPIT_UP}fro{SE_M_MILK_DRINK}m{SE_M_YAWN}daughter.\n"
	.string "I{SE_M_SPIT_UP}cheer{SE_M_GRASSWHISTLE}m{SE_M_REVERSAL}up.$"

NationalPark_Normal_Text_Teacher1:
	.string "Pa{SE_M_YAWN}attention{SE_M_SUPERSONIC}please!\p"
	.string "…Oops{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}hav{SE_M_REVERSAL}t{SE_M_ATTRACT2}qui{SE_M_SPIT_UP}thinkin{SE_M_SANDSTORM}like\n"
	.string "{SE_M_CHARGE}teache{SE_M_SAND_TOMB}al{SE_M_BATON_PASS}th{SE_M_REVERSAL}time.\p"
	.string "Yo{SE_M_DIVE}mus{SE_M_SPIT_UP}b{SE_M_REVERSAL}{SE_M_CHARGE}POKéMO{SE_M_PSYBEAM2}trainer.\p"
	.string "Sinc{SE_M_REVERSAL}you'r{SE_M_REVERSAL}workin{SE_M_SANDSTORM}s{SE_M_ATTRACT2}hard{SE_M_SUPERSONIC}I\n"
	.string "wan{SE_M_SPIT_UP}yo{SE_M_DIVE}t{SE_M_ATTRACT2}hav{SE_M_REVERSAL}this.$"

NationalPark_Normal_Text_Teacher1_QuickClaw:
	.string "Le{SE_M_SPIT_UP}{SE_M_CHARGE}POKéMO{SE_M_PSYBEAM2}hol{SE_M_WATERFALL}tha{SE_M_SPIT_UP}QUIC{SE_M_SNORE}CLAW.\p"
	.string "Sometime{SE_M_GRASSWHISTLE}i{SE_M_SPIT_UP}wil{SE_M_BATON_PASS}strik{SE_M_REVERSAL}first\n"
	.string "durin{SE_M_SANDSTORM}battle.$"

NationalPark_Normal_Text_Youngster1:
	.string "I'{SE_M_MILK_DRINK}playin{SE_M_SANDSTORM}wit{SE_M_TRI_ATTACK}sticker{SE_M_GRASSWHISTLE}{SE_M_HEAL_BELL}printed\n"
	.string "fro{SE_M_MILK_DRINK}m{SE_M_YAWN}POKéDEX.$"

NationalPark_Normal_Text_Youngster2:
	.string "{SE_M_HEAL_BELL}ge{SE_M_SPIT_UP}th{SE_M_REVERSAL}othe{SE_M_SAND_TOMB}guy'{SE_M_GRASSWHISTLE}POKéDE{SE_M_LOCK_ON}sticker\n"
	.string "i{SE_M_ACID_ARMOR}{SE_M_HEAL_BELL}win.$"

NationalPark_Normal_Text_Teacher2:
	.string "{SE_M_HEAL_BELL}tak{SE_M_REVERSAL}walk{SE_M_GRASSWHISTLE}i{SE_M_ATTRACT}th{SE_M_REVERSAL}PARK{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}I\n"
	.string "neve{SE_M_SAND_TOMB}g{SE_M_ATTRACT2}int{SE_M_ATTRACT2}th{SE_M_REVERSAL}grass.\p"
	.string "Trainer{SE_M_GRASSWHISTLE}alway{SE_M_GRASSWHISTLE}wan{SE_M_SPIT_UP}t{SE_M_ATTRACT2}battle…\p"
	.string "Yo{SE_M_DIVE}mus{SE_M_SPIT_UP}hav{SE_M_REVERSAL}bee{SE_M_ATTRACT}i{SE_M_ATTRACT}man{SE_M_YAWN}battles.\n"
	.string "Le{SE_M_SPIT_UP}m{SE_M_REVERSAL}hea{SE_M_BATON_PASS}you{SE_M_SAND_TOMB}POKéMO{SE_M_PSYBEAM2}fo{SE_M_SAND_TOMB}you.$"

NationalPark_Normal_Text_Persian:
	.string "PERSIAN{SE_M_HEAT_WAVE}Fufushaa!$"

NationalPark_Normal_EventScript_Jack::
	trainerbattle_single TRAINER_JOHTO_JACK_HNS, NationalPark_Normal_Text_SchoolboyJack1_Seen, NationalPark_Normal_Text_SchoolboyJack1_Beaten, NationalPark_Normal_EventScript_RegisterJack
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, NationalPark_Normal_EventScript_RematchJack
	msgbox NationalPark_Normal_Text_SchoolboyJack_After, MSGBOX_AUTOCLOSE
	end

NationalPark_Normal_EventScript_RegisterJack::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox NationalPark_Normal_Text_JackRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_JOHTO_JACK_HNS
	release
	end

NationalPark_Normal_EventScript_RematchJack::
	trainerbattle_rematch TRAINER_JOHTO_JACK_HNS, NationalPark_Normal_Text_JackRematchIntro, NationalPark_Normal_Text_JackRematchDefeat
	msgbox NationalPark_Normal_Text_JackPostRematch, MSGBOX_AUTOCLOSE
	end

NationalPark_Normal_EventScript_Beverly::
	trainerbattle_single TRAINER_JOHTO_BEVERLY_HNS, NationalPark_Normal_Text_PokefanFBeverly1_Seen, NationalPark_Normal_Text_PokefanFBeverly1_Beaten, NationalPark_Normal_EventScript_RegisterBeverly
	goto_if_set JOHTO_FLAG_BEVERLY_HAS_ITEM_HNS, NationalPark_Normal_EventScript_BeverlyGiveItem
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, NationalPark_Normal_EventScript_RematchBeverly
	msgbox NationalPark_Normal_Text_PokefanFBeverly_After, MSGBOX_AUTOCLOSE
	end

NationalPark_Normal_EventScript_RematchBeverly::
	trainerbattle_rematch TRAINER_JOHTO_BEVERLY_HNS, NationalPark_Normal_Text_PokefanFBeverly1_Seen, NationalPark_Normal_Text_PokefanFBeverly1_Beaten
	msgbox NationalPark_Normal_Text_PokefanFBeverly_After, MSGBOX_AUTOCLOSE
	end

NationalPark_Normal_EventScript_RegisterBeverly::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox NationalPark_Normal_Text_BeverlyRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_JOHTO_BEVERLY_HNS
	release
	end

NationalPark_Normal_EventScript_BeverlyGiveItem::
	msgbox NationalPark_Normal_Text_BeverlyHasItem, MSGBOX_DEFAULT
	giveitem JOHTO_VAR_BEVERLY_ITEM_HNS
	goto_if_eq VAR_RESULT, FALSE, NationalPark_Normal_EventScript_BeverlyNoRoom
	clearflag JOHTO_FLAG_BEVERLY_HAS_ITEM_HNS
	msgbox NationalPark_Normal_Text_BeverlyGaveItem, MSGBOX_AUTOCLOSE
	end

NationalPark_Normal_EventScript_BeverlyNoRoom::
	msgbox NationalPark_Normal_Text_BeverlyNoRoom, MSGBOX_AUTOCLOSE
	end

NationalPark_Normal_EventScript_William::
	trainerbattle_single TRAINER_JOHTO_WILLIAM_HNS, NationalPark_Normal_Text_PokefanmWilliam_Seen, NationalPark_Normal_Text_PokefanmWilliam_Beaten
	msgbox NationalPark_Normal_Text_PokefanmWilliam_After, MSGBOX_AUTOCLOSE
	end

NationalPark_Normal_EventScript_Krise::
	trainerbattle_single TRAINER_JOHTO_KRISE_HNS, NationalPark_Normal_Text_LassKrise_Seen, NationalPark_Normal_Text_LassKrise_Beaten
	msgbox NationalPark_Normal_Text_LassKrise_After, MSGBOX_AUTOCLOSE
	end

NationalPark_Normal_EventScript_TM_Dig::
	finditem ITEM_TM_DIG
	end

NationalPark_Normal_EventScript_Item_Soothe_Bell::
	finditem ITEM_SOOTHE_BELL
	end

NationalPark_Normal_Text_SchoolboyJack1_Seen:
	.string "Th{SE_M_REVERSAL}worl{SE_M_WATERFALL}o{SE_M_ACID_ARMOR}POKéMO{SE_M_PSYBEAM2}i{SE_M_GRASSWHISTLE}deep.\p"
	.string "Ther{SE_M_REVERSAL}ar{SE_M_REVERSAL}stil{SE_M_BATON_PASS}lot{SE_M_GRASSWHISTLE}o{SE_M_ACID_ARMOR}thing{SE_M_GRASSWHISTLE}we\n"
	.string "don'{SE_M_SPIT_UP}know.\p"
	.string "Bu{SE_M_SPIT_UP}{SE_M_HEAL_BELL}kno{SE_M_TWISTER}mor{SE_M_REVERSAL}tha{SE_M_ATTRACT}yo{SE_M_DIVE}do!$"

NationalPark_Normal_Text_SchoolboyJack1_Beaten:
	.string "Wha-wha-what?$"

NationalPark_Normal_Text_SchoolboyJack_After:
	.string "Ther{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}lo{SE_M_SPIT_UP}t{SE_M_ATTRACT2}learn.\p"
	.string "Fo{SE_M_SAND_TOMB}example…\p"
	.string "Ther{SE_M_REVERSAL}ar{SE_M_REVERSAL}9{SE_M_SURF}kind{SE_M_GRASSWHISTLE}o{SE_M_ACID_ARMOR}TMs.\p"
	.string "Trade{SE_M_WATERFALL}POKéMO{SE_M_PSYBEAM2}leve{SE_M_BATON_PASS}u{SE_M_MORNING_SUN}faster.$"

NationalPark_Normal_Text_JackRegister:
	.string "Ther{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}lo{SE_M_SPIT_UP}t{SE_M_ATTRACT2}learn.\p"
	.string "Fo{SE_M_SAND_TOMB}example…\p"
	.string "Ther{SE_M_REVERSAL}ar{SE_M_REVERSAL}9{SE_M_SURF}kind{SE_M_GRASSWHISTLE}o{SE_M_ACID_ARMOR}TMs.\p"
	.string "Trade{SE_M_WATERFALL}POKéMO{SE_M_PSYBEAM2}leve{SE_M_BATON_PASS}u{SE_M_MORNING_SUN}faster.$"

NationalPark_Normal_Text_JackRematchIntro:
	.string "I'v{SE_M_REVERSAL}learne{SE_M_WATERFALL}{SE_M_CHARGE}lo{SE_M_SPIT_UP}sinc{SE_M_REVERSAL}we\n"
	.string "las{SE_M_SPIT_UP}battled{SE_M_DRAGON_RAGE}Let'{SE_M_GRASSWHISTLE}go!$"

NationalPark_Normal_Text_JackRematchDefeat:
	.string "Wha-wha-what?$"

NationalPark_Normal_Text_JackPostRematch:
	.string "Ther{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}lo{SE_M_SPIT_UP}t{SE_M_ATTRACT2}learn.\p"
	.string "Fo{SE_M_SAND_TOMB}example…\p"
	.string "Ther{SE_M_REVERSAL}ar{SE_M_REVERSAL}9{SE_M_SURF}kind{SE_M_GRASSWHISTLE}o{SE_M_ACID_ARMOR}TMs.\p"
	.string "Trade{SE_M_WATERFALL}POKéMO{SE_M_PSYBEAM2}leve{SE_M_BATON_PASS}u{SE_M_MORNING_SUN}faster.$"

NationalPark_Normal_Text_PokefanFBeverly1_Seen:
	.string "M{SE_M_YAWN}POKéMO{SE_M_PSYBEAM2}ar{SE_M_REVERSAL}simpl{SE_M_YAWN}darling.\p"
	.string "Le{SE_M_SPIT_UP}m{SE_M_REVERSAL}tel{SE_M_BATON_PASS}yo{SE_M_DIVE}ho{SE_M_TWISTER}prou{SE_M_WATERFALL}my\n"
	.string "darling{SE_M_GRASSWHISTLE}mak{SE_M_REVERSAL}me.$"

NationalPark_Normal_Text_PokefanFBeverly1_Beaten:
	.string "{SE_M_HEAL_BELL}ca{SE_M_ATTRACT}bea{SE_M_SPIT_UP}yo{SE_M_DIVE}i{SE_M_ATTRACT}pride{SE_M_SUPERSONIC}but…$"

NationalPark_Normal_Text_PokefanFBeverly_After:
	.string "{SE_M_HEAL_BELL}mus{SE_M_SPIT_UP}say{SE_M_SUPERSONIC}you{SE_M_SAND_TOMB}POKéMO{SE_M_PSYBEAM2}ar{SE_M_REVERSAL}quite\n"
	.string "cute{SE_M_SUPERSONIC}too.$"

NationalPark_Normal_Text_PokefanmWilliam_Seen:
	.string "W{SE_M_REVERSAL}ador{SE_M_REVERSAL}ou{SE_M_SAND_TOMB}POKéMON{SE_M_SUPERSONIC}eve{SE_M_ATTRACT}i{SE_M_ACID_ARMOR}they\n"
	.string "dislik{SE_M_REVERSAL}us.\p"
	.string "That'{SE_M_GRASSWHISTLE}wha{SE_M_SPIT_UP}bein{SE_M_SANDSTORM}{SE_M_CHARGE}FA{SE_M_PSYBEAM2}i{SE_M_GRASSWHISTLE}about.$"

NationalPark_Normal_Text_PokefanmWilliam_Beaten:
	.string "M-m{SE_M_YAWN}POKéMON!$"

NationalPark_Normal_Text_PokefanmWilliam_After:
	.string "{SE_M_HEAL_BELL}los{SE_M_SPIT_UP}th{SE_M_REVERSAL}battle{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}m{SE_M_YAWN}POKéMO{SE_M_PSYBEAM2}win\n"
	.string "th{SE_M_REVERSAL}priz{SE_M_REVERSAL}fo{SE_M_SAND_TOMB}bein{SE_M_SANDSTORM}mos{SE_M_SPIT_UP}lovely.$"

NationalPark_Normal_Text_LassKrise_Seen:
	.string "Hello{SE_M_SING}Wh{SE_M_YAWN}ar{SE_M_REVERSAL}yo{SE_M_DIVE}starin{SE_M_SANDSTORM}a{SE_M_SPIT_UP}me?\p"
	.string "Oh{SE_M_SUPERSONIC}{SE_M_CHARGE}battle?$"

NationalPark_Normal_Text_LassKrise_Beaten:
	.string "…Hmmm…$"

NationalPark_Normal_Text_LassKrise_After:
	.string "{SE_M_HEAL_BELL}though{SE_M_SPIT_UP}yo{SE_M_DIVE}wer{SE_M_REVERSAL}starin{SE_M_SANDSTORM}a{SE_M_SPIT_UP}me\n"
	.string "becaus{SE_M_REVERSAL}I'{SE_M_MILK_DRINK}cute!$"

NationalPark_Normal_Text_Sign_RelaxationSquare:
	.string "RELAXATIO{SE_M_PSYBEAM2}SQUARE\n"
	.string "NATIONA{SE_M_BRICK_BREAK}PARK$"

NationalPark_Normal_Text_Sign_BattleNotice:
	.string "Wha{SE_M_SPIT_UP}i{SE_M_GRASSWHISTLE}thi{SE_M_GRASSWHISTLE}notice?\p"
	.string "Pleas{SE_M_REVERSAL}battl{SE_M_REVERSAL}onl{SE_M_YAWN}i{SE_M_ATTRACT}th{SE_M_REVERSAL}grass.\p"
	.string "NATIONA{SE_M_BRICK_BREAK}PAR{SE_M_SNORE}WARDEN'{SE_M_SKETCH}OFFICE$"

NationalPark_Normal_Text_TrainerTips:
	.string "TRAINE{SE_M_MINIMIZE}TIPS\p"
	.string "Prin{SE_M_SPIT_UP}ou{SE_M_SPIT_UP}MAI{SE_M_BRICK_BREAK}b{SE_M_YAWN}openin{SE_M_SANDSTORM}i{SE_M_SPIT_UP}then\n"
	.string "pressin{SE_M_SANDSTORM}START.$"

NationalPark_Normal_Text_BeverlyRegister:
	.string "{SE_M_HEAL_BELL}mus{SE_M_SPIT_UP}say{SE_M_SUPERSONIC}you{SE_M_SAND_TOMB}POKéMO{SE_M_PSYBEAM2}ar{SE_M_REVERSAL}quite\n"
	.string "cute{SE_M_SUPERSONIC}too.$"

NationalPark_Normal_Text_BeverlyHasItem:
	.string "Oh{SE_M_SUPERSONIC}hello{SE_M_DRAGON_RAGE}{SE_M_HEAL_BELL}hav{SE_M_REVERSAL}something\n"
	.string "fo{SE_M_SAND_TOMB}you.\p"
	.string "Pleas{SE_M_REVERSAL}tak{SE_M_REVERSAL}i{SE_M_SPIT_UP}a{SE_M_GRASSWHISTLE}{SE_M_CHARGE}toke{SE_M_ATTRACT}of\n"
	.string "m{SE_M_YAWN}appreciation!$"

NationalPark_Normal_Text_BeverlyGaveItem:
	.string "M{SE_M_YAWN}darlin{SE_M_SANDSTORM}POKéMO{SE_M_PSYBEAM2}an{SE_M_WATERFALL}{SE_M_HEAL_BELL}will\n"
	.string "b{SE_M_REVERSAL}cheerin{SE_M_SANDSTORM}fo{SE_M_SAND_TOMB}you!$"

NationalPark_Normal_Text_BeverlyNoRoom:
	.string "Hmm{SE_M_SUPERSONIC}you{SE_M_SAND_TOMB}BA{SE_M_SWAGGER}i{SE_M_GRASSWHISTLE}full.\p"
	.string "Com{SE_M_REVERSAL}bac{SE_M_ENCORE2}whe{SE_M_ATTRACT}yo{SE_M_DIVE}hav{SE_M_REVERSAL}room.$"

