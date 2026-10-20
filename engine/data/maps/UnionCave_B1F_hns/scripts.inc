@ Johto (data/maps/UnionCave_B1F_hns/scripts.inc), as built into the FireRed game.

UnionCave_B1F_hns_MapScripts::
	.byte 0

UnionCave_B1F_EventScript_HikerPhillip::
	trainerbattle_single 1284, UnionCave_B1F_Text_HikerPhillipSeen, UnionCave_B1F_Text_HikerPhillipBeaten
	msgbox UnionCave_B1F_Text_HikerPhillipAfter, MSGBOX_AUTOCLOSE
	end

UnionCave_B1F_EventScript_HikerLeonard::
	trainerbattle_single 1285, UnionCave_B1F_Text_HikerLeonardSeen, UnionCave_B1F_Text_HikerLeonardBeaten
	msgbox UnionCave_B1F_Text_HikerLeonardAfter, MSGBOX_AUTOCLOSE
	end

UnionCave_B1F_EventScript_PokemaniacAndrew::
	trainerbattle_single 1132, UnionCave_B1F_Text_PokemaniacAndrewSeen, UnionCave_B1F_Text_PokemaniacAndrewBeaten
	msgbox UnionCave_B1F_Text_PokemaniacAndrewAfter, MSGBOX_AUTOCLOSE
	end

UnionCave_B1F_EventScript_PokemaniacCalvin::
	trainerbattle_single 1133, UnionCave_B1F_Text_PokemaniacCalvinSeen, UnionCave_B1F_Text_PokemaniacCalvinBeaten
	msgbox UnionCave_B1F_Text_PokemaniacCalvinAfter, MSGBOX_AUTOCLOSE
	end

UnionCave_B1F_EventScript_Item_RockTomb::
	finditem 620
	end

UnionCave_B1F_EventScript_Item_Xdefend::
	finditem ITEM_X_DEFEND
	end

UnionCave_B1F_Text_HikerPhillipSeen:
	.string "It'{SE_M_GRASSWHISTLE}bee{SE_M_ATTRACT}{SE_M_CHARGE}whil{SE_M_REVERSAL}sinc{SE_M_REVERSAL}{SE_M_HEAL_BELL}las{SE_M_SPIT_UP}saw\n"
	.string "anothe{SE_M_SAND_TOMB}person.\p"
	.string "Don'{SE_M_SPIT_UP}b{SE_M_REVERSAL}shy{SE_M_PERISH_SONG}Let'{SE_M_GRASSWHISTLE}battle!$"

UnionCave_B1F_Text_HikerPhillipBeaten:
	.string "Uurggh…$"

UnionCave_B1F_Text_HikerPhillipAfter:
	.string "I'v{SE_M_REVERSAL}bee{SE_M_ATTRACT}los{SE_M_SPIT_UP}fo{SE_M_SAND_TOMB}{SE_M_CHARGE}lon{SE_M_SANDSTORM}time…\p"
	.string "{SE_M_HEAL_BELL}don'{SE_M_SPIT_UP}min{SE_M_WATERFALL}i{SE_M_SPIT_UP}here{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}{SE_M_HEAL_BELL}am\n"
	.string "sooo{SE_M_ATTRACT2}hungry!$"

UnionCave_B1F_Text_HikerLeonardSeen:
	.string "Wha{SE_M_SPIT_UP}d{SE_M_ATTRACT2}yo{SE_M_DIVE}know{SE_M_DRAGON_RAGE}{SE_M_BONEMERANG}visitor!$"

UnionCave_B1F_Text_HikerLeonardBeaten:
	.string "Wahahah{SE_M_DRAGON_RAGE}You'r{SE_M_REVERSAL}{SE_M_CHARGE}feist{SE_M_YAWN}one!$"

UnionCave_B1F_Text_HikerLeonardAfter:
	.string "{SE_M_HEAL_BELL}liv{SE_M_REVERSAL}dow{SE_M_ATTRACT}here.\p"
	.string "Yo{SE_M_DIVE}can{SE_M_SUPERSONIC}too{SE_M_SUPERSONIC}i{SE_M_ACID_ARMOR}you'{SE_M_WATERFALL}like.\p"
	.string "There'{SE_M_GRASSWHISTLE}plent{SE_M_YAWN}o{SE_M_ACID_ARMOR}room{SE_M_SUPERSONIC}yo{SE_M_DIVE}see.$"

UnionCave_B1F_Text_PokemaniacAndrewSeen:
	.string "Who'{SE_M_GRASSWHISTLE}there?\p"
	.string "Leav{SE_M_REVERSAL}m{SE_M_REVERSAL}an{SE_M_WATERFALL}m{SE_M_YAWN}POKéMO{SE_M_PSYBEAM2}alone!$"

UnionCave_B1F_Text_PokemaniacAndrewBeaten:
	.string "Go{SE_M_DIZZY_PUNCH}G{SE_M_ATTRACT2}away!$"

UnionCave_B1F_Text_PokemaniacAndrewAfter:
	.string "Jus{SE_M_SPIT_UP}m{SE_M_REVERSAL}an{SE_M_WATERFALL}m{SE_M_YAWN}POKéMON{SE_M_PERISH_SONG}I'{SE_M_MILK_DRINK}de-\n"
	.string "liriou{SE_M_GRASSWHISTLE}wit{SE_M_TRI_ATTACK}joy.$"

UnionCave_B1F_Text_PokemaniacCalvinSeen:
	.string "{SE_M_HEAL_BELL}cam{SE_M_REVERSAL}al{SE_M_BATON_PASS}th{SE_M_REVERSAL}wa{SE_M_YAWN}her{SE_M_REVERSAL}t{SE_M_ATTRACT2}conduct\n"
	.string "m{SE_M_YAWN}POKéMO{SE_M_PSYBEAM2}research.\p"
	.string "Le{SE_M_SPIT_UP}m{SE_M_REVERSAL}demonstrat{SE_M_REVERSAL}m{SE_M_YAWN}finding{SE_M_GRASSWHISTLE}i{SE_M_ATTRACT}a\n"
	.string "rea{SE_M_BATON_PASS}battle!$"

UnionCave_B1F_Text_PokemaniacCalvinBeaten:
	.string "Yo{SE_M_DIVE}demonstrate{SE_M_WATERFALL}o{SE_M_ATTRACT}me!$"

UnionCave_B1F_Text_PokemaniacCalvinAfter:
	.string "{SE_M_HEAL_BELL}shoul{SE_M_WATERFALL}compil{SE_M_REVERSAL}an{SE_M_WATERFALL}announc{SE_M_REVERSAL}my\n"
	.string "stud{SE_M_YAWN}findings.\p"
	.string "{SE_M_HEAL_BELL}migh{SE_M_SPIT_UP}eve{SE_M_ATTRACT}becom{SE_M_REVERSAL}famou{SE_M_GRASSWHISTLE}like\n"
	.string "PROF.ELM.$"

