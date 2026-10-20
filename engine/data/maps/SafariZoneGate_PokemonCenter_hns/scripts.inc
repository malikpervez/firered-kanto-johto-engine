@ Johto (data/maps/SafariZoneGate_PokemonCenter_hns/scripts.inc), as built into the FireRed game.

SafariZoneGate_PokemonCenter_hns_MapScripts::
	map_script 3, SafariZoneGate_PokemonCenter_OnTransition
	.byte 0

SafariZoneGate_PokemonCenter_OnTransition::
	setrespawn 141
	end

SafariZoneGate_PokemonCenter_EventScript_NPC1::
	lock
	faceplayer
	msgbox SafariZoneGate_PokemonCenter_Text_NPC1, MSGBOX_DEFAULT
	closemessage
	release
	end

SafariZoneGate_PokemonCenter_EventScript_NPC2::
	lock
	faceplayer
	msgbox SafariZoneGate_PokemonCenter_Text_NPC2, MSGBOX_DEFAULT
	closemessage
	release
	end

SafariZoneGate_PokemonCenter_Text_Boy::
	lock
	faceplayer
	msgbox SafariZoneGate_PokemonCenter_Text_SafariSong, MSGBOX_DEFAULT
	closemessage
	release
	end

SafariZoneGate_PokemonCenter_Text_NPC1:
	.string "Thos{SE_M_REVERSAL}wh{SE_M_ATTRACT2}com{SE_M_REVERSAL}t{SE_M_ATTRACT2}{SE_M_CHARGE}POKéMO{SE_M_PSYBEAM2}CENTER\n"
	.string "ofte{SE_M_ATTRACT}tak{SE_M_REVERSAL}goo{SE_M_WATERFALL}car{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}thei{SE_M_SAND_TOMB}POKéMON.\p"
	.string "Wouldn'{SE_M_SPIT_UP}yo{SE_M_DIVE}agree?$"

SafariZoneGate_PokemonCenter_Text_NPC2:
	.string "Afte{SE_M_SAND_TOMB}{SE_M_CHARGE}lon{SE_M_SANDSTORM}wal{SE_M_ENCORE2}i{SE_M_ATTRACT}th{SE_M_REVERSAL}mountain{SE_M_GRASSWHISTLE}to\n"
	.string "fin{SE_M_WATERFALL}{SE_M_CHARGE}POKéMO{SE_M_PSYBEAM2}CENTER{SE_M_SUPERSONIC}whe{SE_M_ATTRACT}you're\l"
	.string "jus{SE_M_SPIT_UP}abou{SE_M_SPIT_UP}t{SE_M_ATTRACT2}fal{SE_M_BATON_PASS}flat...\p"
	.string "The{SE_M_ATTRACT}i{SE_M_SPIT_UP}feel{SE_M_GRASSWHISTLE}lik{SE_M_REVERSAL}yo{SE_M_DIVE}ar{SE_M_REVERSAL}i{SE_M_ATTRACT}paradise!$"

SafariZoneGate_PokemonCenter_Text_SafariSong:
	.string "Safari{SE_M_SUPERSONIC}safari{SE_M_SUPERSONIC}i{SE_M_SPIT_UP}i{SE_M_GRASSWHISTLE}s{SE_M_ATTRACT2}muc{SE_M_TRI_ATTACK}fun.\n"
	.string "Safari{SE_M_SUPERSONIC}safari{SE_M_SUPERSONIC}s{SE_M_ATTRACT2}interesting{SE_M_SUPERSONIC}huh!\p"
	.string "S{SE_M_ATTRACT2}man{SE_M_YAWN}POKéMO{SE_M_PSYBEAM2}ar{SE_M_REVERSAL}waitin{SE_M_SANDSTORM}fo{SE_M_SAND_TOMB}us!\p"
	.string "...That'{SE_M_GRASSWHISTLE}{SE_M_CHARGE}son{SE_M_SANDSTORM}{SE_M_HEAL_BELL}mad{SE_M_REVERSAL}up.\n"
	.string "{SE_M_HEAL_BELL}sin{SE_M_SANDSTORM}i{SE_M_SPIT_UP}whe{SE_M_ATTRACT}{SE_M_HEAL_BELL}a{SE_M_MILK_DRINK}i{SE_M_ATTRACT}th{SE_M_REVERSAL}SAFAR{SE_M_HEAL_BELL}ZONE.$"

