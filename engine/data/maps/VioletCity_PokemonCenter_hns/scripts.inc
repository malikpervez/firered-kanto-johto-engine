@ Johto (data/maps/VioletCity_PokemonCenter_hns/scripts.inc), as built into the FireRed game.

VioletCity_PokemonCenter_hns_MapScripts::
	map_script 3, VioletCity_Pokecenter_OnTransition
	.byte 0

VioletCity_Pokecenter_OnTransition::
	setrespawn 130
	end

VioletCity_PokemonCenter_EventScript_Aide::
	lock
	faceplayer
	goto_if_set 8703, VioletCity_PokemonCenter_EventScript_Aide_Received
	specialvar 32772, GetMaxPartySize
	goto_if_eq 32772, 1, VioletCity_PokemonCenter_EventScript_Aide_Offer
	getpartysize
	goto_if_eq 32781, 32772, VioletCity_PokemonCenter_EventScript_AideNoRoom

VioletCity_PokemonCenter_EventScript_Aide_Offer::
	msgbox VioletCity_PokeCenter_Text_ElmsAideFavor, MSGBOX_YESNO
	goto_if_eq 32781, NO, VioletCity_PokemonCenter_EventScript_Aide_Refuse
	goto_if_eq 32781, YES, VioletCity_PokemonCenter_EventScript_Aide_Accepted
	release
	end

VioletCity_PokemonCenter_EventScript_Aide_FullParty::
	msgbox VioletCity_PokeCenter_Text_ElmsAideFullParty, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_PokemonCenter_EventScript_AideNoRoom::
	msgbox VioletCity_PokeCenter_Text_ElmsAideNoRoom, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_PokemonCenter_EventScript_Aide_Refuse::
	msgbox VioletCity_PokeCenter_Text_ElmsAideRefuse, MSGBOX_YESNO
	goto_if_eq 32781, NO, VioletCity_PokemonCenter_EventScript_Aide_Refuse
	goto_if_eq 32781, YES, VioletCity_PokemonCenter_EventScript_Aide_Accepted
	release
	end

VioletCity_PokemonCenter_EventScript_Aide_Accepted::
	specialvar 32772, GetMaxPartySize
	goto_if_eq 32772, 1, VioletCity_PokemonCenter_EventScript_Aide_GiveEgg
	getpartysize
	goto_if_eq 32781, 32772, VioletCity_PokemonCenter_EventScript_Aide_FullParty

VioletCity_PokemonCenter_EventScript_Aide_GiveEgg::
	playfanfare 370
	message J_LavaridgeTown_Text_ReceivedTheEgg
	waitfanfare
	msgbox VioletCity_PokeCenter_Text_ElmsAideGiveEgg, MSGBOX_DEFAULT
	closemessage
	giveegg 175
	goto_if_eq 32781, 2, J_Common_EventScript_NoMoreRoomForPokemon
	call_if_eq 32781, 1, VioletCity_PokemonCenter_EventScript_Aide_EggSentToPC
	setflag 8703
	msgbox VioletCity_PokeCenter_Text_ElmsAideGiveItem, MSGBOX_DEFAULT
	giveitem ITEM_EXP_SHARE_SMALL
	setflag 8276
	setvar 20608, 1
	clearflag 8278
	clearflag 8267
	release
	end

VioletCity_PokemonCenter_EventScript_Aide_EggSentToPC::
	msgbox VioletCity_PokeCenter_Text_ElmsAideEggToPC, MSGBOX_DEFAULT
	closemessage
	return

VioletCity_PokemonCenter_EventScript_Aide_Received::
	msgbox VioletCity_PokeCenter_Text_ElmsAideGiveEgg, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_PokemonCenter_EventScript_Gentleman::
	lock
	faceplayer
	msgbox VioletCity_PokeCenter_Text_Gentleman, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_PokemonCenter_EVentScript_Kid::
	lock
	faceplayer
	msgbox VioletCity_PokeCenter_Text_GameboyKid, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_PokemonCenter_EventScript_Man::
	lock
	faceplayer
	msgbox VioletCity_PokeCenter_Text_Youngster, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_PokemonCenter_Text_BookshelfWoman::
	lock
	faceplayer
	msgbox VioletCity_PokeCenter_Text_BooksAreGreat, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_PokeCenter_Text_ElmsAideFavor:
	.string "{PLAYER}{SE_M_SUPERSONIC}lon{SE_M_SANDSTORM}time{SE_M_SUPERSONIC}n{SE_M_ATTRACT2}see.\p"
	.string "PROF.EL{SE_M_GIGA_DRAIN}aske{SE_M_WATERFALL}m{SE_M_REVERSAL}t{SE_M_ATTRACT2}fin{SE_M_WATERFALL}you.\p"
	.string "H{SE_M_REVERSAL}ha{SE_M_GRASSWHISTLE}anothe{SE_M_SAND_TOMB}favo{SE_M_SAND_TOMB}t{SE_M_ATTRACT2}ask.\p"
	.string "Woul{SE_M_WATERFALL}yo{SE_M_DIVE}tak{SE_M_REVERSAL}th{SE_M_REVERSAL}POKéMO{SE_M_PSYBEAM2}EGG?$"

VioletCity_PokeCenter_Text_ElmsAideNoRoom:
	.string "{PLAYER}{SE_M_SUPERSONIC}lon{SE_M_SANDSTORM}time{SE_M_SUPERSONIC}n{SE_M_ATTRACT2}see.\p"
	.string "PROF.EL{SE_M_GIGA_DRAIN}aske{SE_M_WATERFALL}m{SE_M_REVERSAL}t{SE_M_ATTRACT2}fin{SE_M_WATERFALL}you.\p"
	.string "H{SE_M_REVERSAL}ha{SE_M_GRASSWHISTLE}anothe{SE_M_SAND_TOMB}favo{SE_M_SAND_TOMB}t{SE_M_ATTRACT2}ask.\p"
	.string "Woul{SE_M_WATERFALL}yo{SE_M_DIVE}tak{SE_M_REVERSAL}th{SE_M_REVERSAL}POKéMO{SE_M_PSYBEAM2}EGG?\p"
	.string "Oh{SE_M_SUPERSONIC}wait..{SE_M_PERISH_SONG}Yo{SE_M_DIVE}nee{SE_M_WATERFALL}t{SE_M_ATTRACT2}mak{SE_M_REVERSAL}room\n"
	.string "i{SE_M_ATTRACT}you{SE_M_SAND_TOMB}part{SE_M_YAWN}first.$"

VioletCity_PokeCenter_Text_ElmsAideGiveEgg:
	.string "W{SE_M_REVERSAL}discovere{SE_M_WATERFALL}tha{SE_M_SPIT_UP}{SE_M_CHARGE}POKéMO{SE_M_PSYBEAM2}won't\n"
	.string "hatc{SE_M_TRI_ATTACK}unti{SE_M_BATON_PASS}i{SE_M_SPIT_UP}grow{SE_M_GRASSWHISTLE}i{SE_M_ATTRACT}th{SE_M_REVERSAL}EGG.\p"
	.string "I{SE_M_SPIT_UP}als{SE_M_ATTRACT2}ha{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}b{SE_M_REVERSAL}wit{SE_M_TRI_ATTACK}other\n"
	.string "activ{SE_M_REVERSAL}POKéMO{SE_M_PSYBEAM2}t{SE_M_ATTRACT2}hatch.\p"
	.string "{PLAYER}{SE_M_SUPERSONIC}you'r{SE_M_REVERSAL}th{SE_M_REVERSAL}onl{SE_M_YAWN}person\n"
	.string "w{SE_M_REVERSAL}ca{SE_M_ATTRACT}rel{SE_M_YAWN}on.$"

VioletCity_PokeCenter_Text_ElmsAideGiveItem:
	.string "Oh{SE_M_SUPERSONIC}an{SE_M_WATERFALL}thi{SE_M_GRASSWHISTLE}migh{SE_M_SPIT_UP}hel{SE_M_MORNING_SUN}whe{SE_M_ATTRACT}i{SE_M_SPIT_UP}hatches.$"

VioletCity_PokeCenter_Text_ElmsAideFullParty:
	.string "Oh{SE_M_SUPERSONIC}no{SE_M_PERISH_SONG}Yo{SE_M_DIVE}can'{SE_M_SPIT_UP}carr{SE_M_YAWN}an{SE_M_YAWN}more\n"
	.string "POKéMO{SE_M_PSYBEAM2}wit{SE_M_TRI_ATTACK}you.\p"
	.string "I'l{SE_M_BATON_PASS}wai{SE_M_SPIT_UP}her{SE_M_REVERSAL}whil{SE_M_REVERSAL}yo{SE_M_DIVE}make\n"
	.string "roo{SE_M_MILK_DRINK}fo{SE_M_SAND_TOMB}th{SE_M_REVERSAL}EGG.$"

VioletCity_PokeCenter_Text_ElmsAideEggToPC:
	.string "Oh{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}yo{SE_M_DIVE}can'{SE_M_SPIT_UP}carr{SE_M_YAWN}an{SE_M_YAWN}more\n"
	.string "POKéMO{SE_M_PSYBEAM2}wit{SE_M_TRI_ATTACK}you.\p"
	.string "Don'{SE_M_SPIT_UP}worry--{SE_M_HEAL_BELL}sen{SE_M_SPIT_UP}th{SE_M_REVERSAL}EG{SE_M_SWAGGER}to\n"
	.string "BILL'{SE_M_SKETCH}P{SE_M_PSYBEAM}fo{SE_M_SAND_TOMB}you.$"

VioletCity_PokeCenter_Text_ElmsAideRefuse:
	.string "B-but{SE_M_DIZZY_PUNCH}PROF.EL{SE_M_GIGA_DRAIN}aske{SE_M_WATERFALL}fo{SE_M_SAND_TOMB}you…$"

VioletCity_PokeCenter_Text_BooksAreGreat:
	.string "Whil{SE_M_REVERSAL}m{SE_M_YAWN}POKéMO{SE_M_PSYBEAM2}ar{SE_M_REVERSAL}recovering\n"
	.string "{SE_M_HEAL_BELL}lov{SE_M_REVERSAL}t{SE_M_ATTRACT2}rea{SE_M_WATERFALL}{SE_M_CHARGE}goo{SE_M_WATERFALL}book.$"

VioletCity_PokeCenter_Text_MobileAdapter:
	.string "{SE_M_HEAL_BELL}jus{SE_M_SPIT_UP}battle{SE_M_WATERFALL}{SE_M_CHARGE}frien{SE_M_WATERFALL}in\n"
	.string "CIANWOO{SE_M_FAINT_ATTACK}ove{SE_M_SAND_TOMB}{SE_M_CHARGE}link.\p"
	.string "I{SE_M_ACID_ARMOR}yo{SE_M_DIVE}connec{SE_M_SPIT_UP}{SE_M_CHARGE}MOBIL{SE_M_SWORDS_DANCE}ADAPTER,\n"
	.string "yo{SE_M_DIVE}ca{SE_M_ATTRACT}lin{SE_M_ENCORE2}wit{SE_M_TRI_ATTACK}{SE_M_CHARGE}frien{SE_M_WATERFALL}far\l"
	.string "away.$"

VioletCity_PokeCenter_Text_GameboyKid:
	.string "{SE_M_BONEMERANG}gu{SE_M_YAWN}name{SE_M_WATERFALL}BIL{SE_M_BRICK_BREAK}mad{SE_M_REVERSAL}the\n"
	.string "POKéMO{SE_M_PSYBEAM2}P{SE_M_PSYBEAM}storag{SE_M_REVERSAL}system.$"

VioletCity_PokeCenter_Text_Gentleman:
	.string "I{SE_M_SPIT_UP}wa{SE_M_GRASSWHISTLE}aroun{SE_M_WATERFALL}thre{SE_M_REVERSAL}year{SE_M_GRASSWHISTLE}ago.\p"
	.string "TEA{SE_M_GIGA_DRAIN}ROCKE{SE_M_SWIFT}wa{SE_M_GRASSWHISTLE}u{SE_M_MORNING_SUN}t{SE_M_ATTRACT2}n{SE_M_ATTRACT2}good\n"
	.string "wit{SE_M_TRI_ATTACK}POKéMON.\p"
	.string "Bu{SE_M_SPIT_UP}justic{SE_M_REVERSAL}prevailed--{SE_M_CHARGE}young\n"
	.string "ki{SE_M_WATERFALL}brok{SE_M_REVERSAL}'e{SE_M_MILK_DRINK}up.$"

VioletCity_PokeCenter_Text_Youngster:
	.string "POKéMO{SE_M_PSYBEAM2}ar{SE_M_REVERSAL}smart{SE_M_PERISH_SONG}The{SE_M_YAWN}won't\n"
	.string "obe{SE_M_YAWN}{SE_M_CHARGE}traine{SE_M_SAND_TOMB}the{SE_M_YAWN}don'{SE_M_SPIT_UP}respect.\p"
	.string "Withou{SE_M_SPIT_UP}th{SE_M_REVERSAL}righ{SE_M_SPIT_UP}GY{SE_M_GIGA_DRAIN}BADGES,\n"
	.string "the{SE_M_YAWN}wil{SE_M_BATON_PASS}jus{SE_M_SPIT_UP}d{SE_M_ATTRACT2}a{SE_M_GRASSWHISTLE}the{SE_M_YAWN}please.$"

