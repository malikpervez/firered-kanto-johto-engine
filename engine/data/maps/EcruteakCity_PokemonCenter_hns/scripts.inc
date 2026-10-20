@ Johto (data/maps/EcruteakCity_PokemonCenter_hns/scripts.inc), as built into the FireRed game.

EcruteakCity_PokemonCenter_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, EcruteakCity_PokemonCenter_OnTransition
	.byte 0

EcruteakCity_PokemonCenter_OnTransition::
	setrespawn JOHTO_HEAL_LOCATION_ECRUTEAK_CITY_HNS
	end

EcruteakCity_PokemonCenter_EventScript_Bill::
	lock
	delay 30
	playse SE_PC_OFF
	delay 55
	faceplayer
	msgbox EcruteakCity_PokemonCenter1F_Text_Bill1, MSGBOX_DEFAULT
	msgbox EcruteakCity_PokemonCenter1F_Text_Bill2, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_FACING, DIR_NORTH, EcruteakCity_PokemonCenter_EventScript_BillLeaveBot
	call_if_eq VAR_FACING, DIR_WEST, EcruteakCity_PokemonCenter_EventScript_BillLeaveTop
	playse SE_EXIT
	setflag JOHTO_FLAG_HIDE_ECRUTEAK_BILL
	removeobject LOCALID_ECRUTEAK_BILL
	setflag JOHTO_FLAG_SYS_PC_BILL
	clearflag JOHTO_FLAG_HIDE_GOLDENROD_BILL
	release
	end

EcruteakCity_PokemonCenter_EventScript_BillFaceDown::
	turnobject LOCALID_ECRUTEAK_BILL, DIR_SOUTH
	return

EcruteakCity_PokemonCenter_EventScript_BillFaceRight::
	turnobject LOCALID_ECRUTEAK_BILL, DIR_EAST
	return

EcruteakCity_PokemonCenter_EventScript_BillLeaveTop::
	applymovement LOCALID_ECRUTEAK_BILL, EcruteakCity_PokemonCenter_Movement_BillTop
	waitmovement 0
	return

EcruteakCity_PokemonCenter_EventScript_BillLeaveBot::
	applymovement LOCALID_ECRUTEAK_BILL, EcruteakCity_PokemonCenter_Movement_BillBot
	waitmovement 0
	return

EcruteakCity_PokemonCenter_EventScript_Hiker::
	lock
	faceplayer
	msgbox EcruteakCity_PokemonCenter1F_Text_PokefanM, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_PokemonCenter_EventScript_Woman::
	lock
	faceplayer
	msgbox EcruteakCity_PokemonCenter1F_Text_CooltrainerF, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_PokemonCenter_EventScript_Nerd::
	lock
	faceplayer
	msgbox EcruteakCity_PokemonCenter1F_Text_GymGuide, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_PokemonCenter_Movement_BillTop:
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

EcruteakCity_PokemonCenter_Movement_BillBot:
	walk_right
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

EcruteakCity_PokemonCenter1F_Text_Bill1:
	.string "Hi{SE_M_SUPERSONIC}I'{SE_M_MILK_DRINK}BILL{SE_M_PERISH_SONG}An{SE_M_WATERFALL}wh{SE_M_ATTRACT2}ar{SE_M_REVERSAL}you?\p"
	.string "Hmm{SE_M_SUPERSONIC}{PLAYER}{SE_M_SUPERSONIC}huh?\n"
	.string "You'v{SE_M_REVERSAL}com{SE_M_REVERSAL}a{SE_M_SPIT_UP}th{SE_M_REVERSAL}righ{SE_M_SPIT_UP}time.$"

EcruteakCity_PokemonCenter1F_Text_Bill2:
	.string "{SE_M_HEAL_BELL}jus{SE_M_SPIT_UP}finishe{SE_M_WATERFALL}adjustment{SE_M_GRASSWHISTLE}o{SE_M_ATTRACT}my\n"
	.string "POKéMO{SE_M_PSYBEAM2}STORAG{SE_M_SWORDS_DANCE}SYSTEM.\p"
	.string "Yo{SE_M_DIVE}kno{SE_M_TWISTER}tha{SE_M_SPIT_UP}P{SE_M_PSYBEAM}yo{SE_M_DIVE}us{SE_M_REVERSAL}t{SE_M_ATTRACT2}store\n"
	.string "al{SE_M_BATON_PASS}you{SE_M_SAND_TOMB}POKéMON?\p"
	.string "{SE_M_HEAL_BELL}develope{SE_M_WATERFALL}tha{SE_M_SPIT_UP}myself!\p"
	.string "No{SE_M_TWISTER}tha{SE_M_SPIT_UP}I'v{SE_M_REVERSAL}installe{SE_M_WATERFALL}thi{SE_M_GRASSWHISTLE}one,\n"
	.string "m{SE_M_YAWN}P{SE_M_PSYBEAM}i{SE_M_GRASSWHISTLE}runnin{SE_M_SANDSTORM}a{SE_M_SPIT_UP}all\l"
	.string "POKéMO{SE_M_PSYBEAM2}CENTER{SE_M_SKETCH}i{SE_M_ATTRACT}JOHT{SE_M_SOLAR_BEAM}an{SE_M_WATERFALL}KANTO.\p"
	.string "{SE_M_HEAL_BELL}hav{SE_M_REVERSAL}t{SE_M_ATTRACT2}hurr{SE_M_YAWN}o{SE_M_ATTRACT}bac{SE_M_ENCORE2}to\n"
	.string "GOLDENRO{SE_M_FAINT_ATTACK}an{SE_M_WATERFALL}se{SE_M_REVERSAL}m{SE_M_YAWN}folks{SE_M_PERISH_SONG}Feel\l"
	.string "fre{SE_M_REVERSAL}t{SE_M_ATTRACT2}visi{SE_M_SPIT_UP}anytime!\p"
	.string "Buh-bye!$"

EcruteakCity_PokemonCenter1F_Text_PokefanM:
	.string "Th{SE_M_REVERSAL}wa{SE_M_YAWN}th{SE_M_REVERSAL}KIMON{SE_M_SOLAR_BEAM}GIRL{SE_M_SKETCH}danc{SE_M_REVERSAL}is\n"
	.string "marvelous.\p"
	.string "Jus{SE_M_SPIT_UP}lik{SE_M_REVERSAL}th{SE_M_REVERSAL}wa{SE_M_YAWN}the{SE_M_YAWN}us{SE_M_REVERSAL}their\n"
	.string "POKéMON.$"

EcruteakCity_PokemonCenter1F_Text_PokefanM_Mobile:
	.string "Yo{SE_M_DIVE}mus{SE_M_SPIT_UP}b{SE_M_REVERSAL}hopin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}battl{SE_M_REVERSAL}more\n"
	.string "people{SE_M_SUPERSONIC}right?\p"
	.string "There'{SE_M_GRASSWHISTLE}apparentl{SE_M_YAWN}som{SE_M_REVERSAL}plac{SE_M_REVERSAL}where\n"
	.string "trainer{SE_M_GRASSWHISTLE}gather.\p"
	.string "Where{SE_M_SUPERSONIC}yo{SE_M_DIVE}ask?\p"
	.string "It'{SE_M_GRASSWHISTLE}{SE_M_CHARGE}littl{SE_M_REVERSAL}pas{SE_M_SPIT_UP}OLIVIN{SE_M_SWORDS_DANCE}CITY.$"

EcruteakCity_PokemonCenter1F_Text_CooltrainerF:
	.string "MORTY{SE_M_SUPERSONIC}th{SE_M_REVERSAL}GY{SE_M_GIGA_DRAIN}LEADER{SE_M_SUPERSONIC}i{SE_M_GRASSWHISTLE}soooo\n"
	.string "cool.\p"
	.string "Hi{SE_M_GRASSWHISTLE}POKéMO{SE_M_PSYBEAM2}ar{SE_M_REVERSAL}reall{SE_M_YAWN}toug{SE_M_TRI_ATTACK}too.$"

EcruteakCity_PokemonCenter1F_Text_GymGuide:
	.string "LAK{SE_M_SWORDS_DANCE}O{SE_M_LEER}RAGE…\p"
	.string "Th{SE_M_REVERSAL}appearanc{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}{SE_M_CHARGE}GYARADOS\n"
	.string "swarm…\p"
	.string "{SE_M_HEAL_BELL}smel{SE_M_BATON_PASS}{SE_M_CHARGE}conspiracy{SE_M_PERISH_SONG}{SE_M_HEAL_BELL}kno{SE_M_TWISTER}it!$"

