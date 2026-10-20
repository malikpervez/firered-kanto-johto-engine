@ Johto (data/maps/GoldenrodCity_RadioTower_4F_hns/scripts.inc), as built into the FireRed game.

GoldenrodCity_RadioTower_4F_hns_MapScripts::
	.byte 0

GoldenrodCity_RadioTower_4F4_EventScript_Sign1::
	lock
	msgbox GoldenrodCity_RadioTower_4F4_Text_Studio2Sign, MSGBOX_SIGN
	closemessage
	release
	end

GoldenrodCity_RadioTower_4F4_EventScript_Sign2::
	lock
	msgbox GoldenrodCity_RadioTower_4F4_Text_ProductionSign, MSGBOX_SIGN
	closemessage
	release
	end

GoldenrodRaidoTower4_EventScript_Grunt28::
	trainerbattle_single TRAINER_JOHTO_GRUNT_28_HNS, GoldenrodCity_RadioTower_4F4_Text_GruntF4Seen, GoldenrodCity_RadioTower_4F4_Text_GruntF4Beaten
	msgbox GoldenrodCity_RadioTower_4F4_Text_GruntF4After, MSGBOX_AUTOCLOSE
	end

GoldenrodRaidoTower4_EventScript_Grunt9::
	trainerbattle_single TRAINER_JOHTO_GRUNT_9_HNS, GoldenrodCity_RadioTower_4F4_Text_GruntM10Seen, GoldenrodCity_RadioTower_4F4_Text_GruntM10Beaten
	msgbox GoldenrodCity_RadioTower_4F4_Text_GruntM10After, MSGBOX_AUTOCLOSE
	end

GoldenrodRaidoTower4_EventScript_Proton::
	trainerbattle_single TRAINER_JOHTO_PROTON_2_HNS, GoldenrodCity_RadioTower_4F4_Text_Proton_Seen, GoldenrodCity_RadioTower_4F4_Text_Proton_Beaten
	msgbox GoldenrodCity_RadioTower_4F4_Text_Proton_After, MSGBOX_AUTOCLOSE
	end

GoldenrodCity_RadioTower_4F4_EventScript_Fisher::
	lock
	faceplayer
	msgbox GoldenrodCity_RadioTower_4F4_Text_Fisher, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_4F4_EventScript_Scientist::
	trainerbattle_single TRAINER_JOHTO_RICH_HNS, GoldenrodCity_RadioTower_4F4_Text_ScientistRichSeen, GoldenrodCity_RadioTower_4F4_Text_ScientistRichBeaten
	msgbox GoldenrodCity_RadioTower_4F4_Text_ScientistRichAfter, MSGBOX_AUTOCLOSE
	end

GoldenrodCity_RadioTower_4F4_EventScript_Mary::
	lock
	faceplayer
	goto_if_eq JOHTO_VAR_GOLDENROD_CITY_STATE, 6, GoldenrodCity_RadioTower_4F4_EventScript_Mary2
	goto_if_eq JOHTO_VAR_GOLDENROD_CITY_STATE, 7, GoldenrodCity_RadioTower_4F4_EventScript_Mary2
	goto_if_eq JOHTO_VAR_GOLDENROD_CITY_STATE, 8, GoldenrodCity_RadioTower_4F4_EventScript_Mary2
	goto_if_eq JOHTO_VAR_GOLDENROD_CITY_STATE, 9, GoldenrodCity_RadioTower_4F4_EventScript_Mary2
	goto_if_unset JOHTO_FLAG_GOT_MARY_BRIGHT_POWDER, GoldenrodCity_RadioTower_4F4_EventScript_Mary3
	msgbox GoldenrodCity_RadioTower_4F4_Text_DJMaryAfter, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_4F4_EventScript_Mary2::
	msgbox GoldenrodCity_RadioTower_4F4_Text_DJMary, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_4F4_EventScript_Mary3::
	msgbox GoldenrodCity_RadioTower_4F4_Text_DJMaryCleared, MSGBOX_DEFAULT
	closemessage
	giveitem ITEM_BRIGHT_POWDER
	goto_if_eq VAR_RESULT, FALSE, J_Common_EventScript_BagIsFull
	msgbox GoldenrodCity_RadioTower_4F4_Text_DJMaryPinkBow, MSGBOX_DEFAULT
	closemessage
	setflag JOHTO_FLAG_GOT_MARY_BRIGHT_POWDER
	closemessage
	release
	end

GoldenrodCity_RadioTower_4F4_EventScript_Meowth::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_MEOWTH, CRY_MODE_NORMAL
	msgbox GoldenrodCity_RadioTower_4F4_Text_Meowth, MSGBOX_DEFAULT
	waitmoncry
	release
	end

GoldenrodCity_RadioTower_4F4_Text_Proton_Seen:
	.string "PROTON{SE_M_HEAT_WAVE}No{SE_M_TWISTER}wai{SE_M_SPIT_UP}jus{SE_M_SPIT_UP}on{SE_M_REVERSAL}second!\p"
	.string "Aren'{SE_M_SPIT_UP}yo{SE_M_DIVE}th{SE_M_REVERSAL}on{SE_M_REVERSAL}wh{SE_M_ATTRACT2}go{SE_M_SPIT_UP}i{SE_M_ATTRACT}our\n"
	.string "wa{SE_M_YAWN}a{SE_M_SPIT_UP}SLOWPOK{SE_M_SWORDS_DANCE}WELL?\p"
	.string "{SE_M_HEAL_BELL}see..{SE_M_PERISH_SONG}You'r{SE_M_REVERSAL}doin{SE_M_SANDSTORM}al{SE_M_BATON_PASS}this\n"
	.string "becaus{SE_M_REVERSAL}yo{SE_M_DIVE}wan{SE_M_SPIT_UP}t{SE_M_ATTRACT2}mak{SE_M_REVERSAL}m{SE_M_REVERSAL}angry.\l"
	.string "B{SE_M_REVERSAL}careful!\p"
	.string "Bu{SE_M_SPIT_UP}sinc{SE_M_REVERSAL}yo{SE_M_DIVE}see{SE_M_MILK_DRINK}t{SE_M_ATTRACT2}wis{SE_M_TRI_ATTACK}it{SE_M_SUPERSONIC}I'll\n"
	.string "sho{SE_M_TWISTER}yo{SE_M_DIVE}th{SE_M_REVERSAL}ful{SE_M_BATON_PASS}exten{SE_M_SPIT_UP}o{SE_M_ACID_ARMOR}{SE_M_CHARGE}TEAM\l"
	.string "ROCKE{SE_M_SWIFT}EXECUTIVE'{SE_M_GRASSWHISTLE}wrath!$"

GoldenrodCity_RadioTower_4F4_Text_Proton_Beaten:
	.string "Phew...$"

GoldenrodCity_RadioTower_4F4_Text_Proton_After:
	.string "PROTON{SE_M_HEAT_WAVE}Yo{SE_M_DIVE}ma{SE_M_YAWN}hav{SE_M_REVERSAL}wo{SE_M_ATTRACT}this\n"
	.string "time..{SE_M_PERISH_SONG}Bu{SE_M_SPIT_UP}al{SE_M_BATON_PASS}yo{SE_M_DIVE}di{SE_M_WATERFALL}wa{SE_M_GRASSWHISTLE}make\p"
	.string "TEA{SE_M_GIGA_DRAIN}ROCKET'{SE_M_GRASSWHISTLE}wrat{SE_M_TRI_ATTACK}grow.$"

GoldenrodCity_RadioTower_4F4_Text_Fisher:
	.string "{SE_M_HEAL_BELL}listene{SE_M_WATERFALL}t{SE_M_ATTRACT2}th{SE_M_REVERSAL}radi{SE_M_ATTRACT2}whil{SE_M_REVERSAL}{SE_M_HEAL_BELL}was\n"
	.string "a{SE_M_SPIT_UP}th{SE_M_REVERSAL}RUINS.\p"
	.string "{SE_M_HEAL_BELL}hear{SE_M_WATERFALL}{SE_M_CHARGE}strang{SE_M_REVERSAL}broadcas{SE_M_SPIT_UP}there.$"

GoldenrodCity_RadioTower_4F4_Text_DJMary:
	.string "MARY{SE_M_HEAT_WAVE}Why{SE_M_SING}Wh{SE_M_YAWN}d{SE_M_ATTRACT2}{SE_M_HEAL_BELL}hav{SE_M_REVERSAL}t{SE_M_ATTRACT2}suffer\n"
	.string "throug{SE_M_TRI_ATTACK}this?\p"
	.string "MEOWTH{SE_M_SUPERSONIC}hel{SE_M_MORNING_SUN}me!$"

GoldenrodCity_RadioTower_4F4_Text_DJMaryCleared:
	.string "MARY{SE_M_HEAT_WAVE}Oh{SE_M_DRAGON_RAGE}You'r{SE_M_REVERSAL}m{SE_M_YAWN}littl{SE_M_REVERSAL}savior!\p"
	.string "Wil{SE_M_BATON_PASS}yo{SE_M_DIVE}tak{SE_M_REVERSAL}thi{SE_M_GRASSWHISTLE}a{SE_M_GRASSWHISTLE}m{SE_M_YAWN}thanks?$"

GoldenrodCity_RadioTower_4F4_Text_DJMaryPinkBow:
	.string "MARY{SE_M_HEAT_WAVE}It'{SE_M_GRASSWHISTLE}goo{SE_M_WATERFALL}fo{SE_M_SAND_TOMB}dodgin{SE_M_SANDSTORM}the\n"
	.string "enemy'{SE_M_GRASSWHISTLE}attacks.$"

GoldenrodCity_RadioTower_4F4_Text_DJMaryAfter:
	.string "MARY{SE_M_HEAT_WAVE}Pleas{SE_M_REVERSAL}tun{SE_M_REVERSAL}int{SE_M_ATTRACT2}m{SE_M_REVERSAL}o{SE_M_ATTRACT}PROF.\n"
	.string "OAK'{SE_M_SKETCH}POKéMO{SE_M_PSYBEAM2}TAL{SE_M_SNORE}show!$"

GoldenrodCity_RadioTower_4F4_Text_Meowth:
	.string "MEOWTH{SE_M_HEAT_WAVE}Meowth…$"

GoldenrodCity_RadioTower_4F4_Text_GruntM10Seen:
	.string "Yo{SE_M_DIVE}pla{SE_M_ATTRACT}t{SE_M_ATTRACT2}rescu{SE_M_REVERSAL}th{SE_M_REVERSAL}DIRECTOR?\p"
	.string "Tha{SE_M_SPIT_UP}won'{SE_M_SPIT_UP}b{SE_M_REVERSAL}possibl{SE_M_REVERSAL}becaus{SE_M_REVERSAL}I'm\n"
	.string "goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}bea{SE_M_SPIT_UP}you!$"

GoldenrodCity_RadioTower_4F4_Text_GruntM10Beaten:
	.string "No{SE_M_DRAGON_RAGE}Unbelievable!$"

GoldenrodCity_RadioTower_4F4_Text_GruntM10After:
	.string "{SE_M_HEAL_BELL}don'{SE_M_SPIT_UP}believ{SE_M_REVERSAL}it{SE_M_DRAGON_RAGE}{SE_M_HEAL_BELL}wa{SE_M_GRASSWHISTLE}beaten!$"

GoldenrodCity_RadioTower_4F4_Text_ExecutiveM2Seen:
	.string "Stop{SE_M_DRAGON_RAGE}I'{SE_M_MILK_DRINK}know{SE_M_ATTRACT}a{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}TEA{SE_M_GIGA_DRAIN}ROCKET\n"
	.string "fortress!\p"
	.string "You'r{SE_M_REVERSAL}no{SE_M_SPIT_UP}takin{SE_M_SANDSTORM}anothe{SE_M_SAND_TOMB}step!$"

GoldenrodCity_RadioTower_4F4_Text_ExecutiveM2Beaten:
	.string "Th{SE_M_REVERSAL}fortres{SE_M_GRASSWHISTLE}cam{SE_M_REVERSAL}down!$"

GoldenrodCity_RadioTower_4F4_Text_ExecutiveM2After:
	.string "You'v{SE_M_REVERSAL}earne{SE_M_WATERFALL}m{SE_M_YAWN}respect{SE_M_SUPERSONIC}s{SE_M_ATTRACT2}here's\n"
	.string "som{SE_M_REVERSAL}advice.\p"
	.string "It'{SE_M_GRASSWHISTLE}no{SE_M_SPIT_UP}to{SE_M_ATTRACT2}late{SE_M_PERISH_SONG}Yo{SE_M_DIVE}ca{SE_M_ATTRACT}stil{SE_M_BATON_PASS}turn\n"
	.string "back.$"

GoldenrodCity_RadioTower_4F4_Text_GruntF4Seen:
	.string "Don'{SE_M_SPIT_UP}{SE_M_HEAL_BELL}thin{SE_M_ENCORE2}POKéMO{SE_M_PSYBEAM2}ar{SE_M_REVERSAL}cute?\p"
	.string "I'l{SE_M_BATON_PASS}thin{SE_M_ENCORE2}m{SE_M_YAWN}POKéMO{SE_M_PSYBEAM2}ar{SE_M_REVERSAL}cute--\p"
	.string "afte{SE_M_SAND_TOMB}the{SE_M_YAWN}bea{SE_M_SPIT_UP}yours!$"

GoldenrodCity_RadioTower_4F4_Text_GruntF4Beaten:
	.string "Oh{SE_M_SUPERSONIC}no{SE_M_DRAGON_RAGE}They'r{SE_M_REVERSAL}s{SE_M_ATTRACT2}useless!$"

GoldenrodCity_RadioTower_4F4_Text_GruntF4After:
	.string "{SE_M_HEAL_BELL}lov{SE_M_REVERSAL}m{SE_M_YAWN}beautifu{SE_M_BATON_PASS}self!\p"
	.string "Wh{SE_M_ATTRACT2}care{SE_M_GRASSWHISTLE}abou{SE_M_SPIT_UP}POKéMON?$"

GoldenrodCity_RadioTower_4F4_Text_ScientistRichSeen:
	.string "Mos{SE_M_SPIT_UP}excellent.\p"
	.string "Thi{SE_M_GRASSWHISTLE}RADI{SE_M_SOLAR_BEAM}TOWE{SE_M_MINIMIZE}wil{SE_M_BATON_PASS}fulfil{SE_M_BATON_PASS}our\n"
	.string "gran{SE_M_WATERFALL}design.$"

GoldenrodCity_RadioTower_4F4_Text_ScientistRichBeaten:
	.string "Hmmm…\p"
	.string "Al{SE_M_BATON_PASS}gran{SE_M_WATERFALL}plan{SE_M_GRASSWHISTLE}com{SE_M_REVERSAL}wit{SE_M_TRI_ATTACK}snags.$"

GoldenrodCity_RadioTower_4F4_Text_ScientistRichAfter:
	.string "D{SE_M_ATTRACT2}yo{SE_M_DIVE}honestl{SE_M_YAWN}believ{SE_M_REVERSAL}yo{SE_M_DIVE}ca{SE_M_ATTRACT}stop\n"
	.string "TEA{SE_M_GIGA_DRAIN}ROCKET?$"

GoldenrodCity_RadioTower_4F4_Text_ProductionSign:
	.string "4{SE_M_LEER}PRODUCTION$"

GoldenrodCity_RadioTower_4F4_Text_Studio2Sign:
	.string "4{SE_M_LEER}STUDI{SE_M_SOLAR_BEAM}2$"

