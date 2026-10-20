@ Johto (data/maps/GoldenrodCity_hns/scripts.inc), as built into the FireRed game.

GoldenrodCity_hns_MapScripts::
	map_script 3, CharacterStory_GoldenrodTransition
	.byte 0

GoldenrodCity_EventScript_Trigger::
	call_if_unset JOHTO_FLAG_SHOWN_ELM_TOGEPI, GoldenrodCity_Elm_Togepi_Call
	setflag JOHTO_FLAG_VISITED_GOLDENROD_CITY
	setflag JOHTO_FLAG_HIDE_GOLDENROD_ROCKETS
	setflag JOHTO_FLAG_HIDE_GOLDENROD_BILL
	setflag JOHTO_FLAG_HIDE_GOLDENROD_UNDERGROUND_KIMONO
	setflag JOHTO_FLAG_HIDE_GOLDENROD_UNDERGROUND_SILVER
	setflag JOHTO_FLAG_HIDE_ROCKET_GOLDENROD_RADIOTOWER_1
	setflag JOHTO_FLAG_HIDE_GOLDENROD_RADIOTOWER_PETREL
	setflag JOHTO_FLAG_HIDE_GOLDENROD_RADIOTOWER_DIRECTOR_2

	clearflag JOHTO_FLAG_HIDE_GOLDENROD_BEAUTY
	clearflag JOHTO_FLAG_HIDE_GOLDENROD_ROCKET_SCOUT
	clearflag JOHTO_FLAG_HIDE_GOLDENROD_NPCS
	clearflag JOHTO_FLAG_GOT_RETURN
	clearflag JOHTO_FLAG_GOT_FRUSTRATION
	clearflag JOHTO_FLAG_RECEIVED_BIKE
	clearflag JOHTO_FLAG_RECEIVED_SQUIRTBOTTLE
	clearflag JOHTO_FLAG_GOT_EEVEE
	clearflag JOHTO_FLAG_SYS_PC_LANETTE
	clearflag JOHTO_FLAG_RETURNED_MACHINE_PART
	clearflag JOHTO_FLAG_UNLOCKED_GOLDENROD_UNDERGROUND_DOOR
	clearflag JOHTO_FLAG_GOLDENROD_MACHOKE_1
	clearflag JOHTO_FLAG_GOLDENROD_MACHOKE_2
	clearflag JOHTO_FLAG_GOLDENROD_MACHOKE_3
	clearflag JOHTO_FLAG_COMPLETED_SWITCHES
	clearflag JOHTO_FLAG_ENABLE_RADIO
	clearflag JOHTO_FLAG_KANTO_RADIO_GOT
	clearflag JOHTO_FLAG_GOLDENROD_NPC_TRADE_COMPLETED
	clearflag JOHTO_FLAG_GOT_SUNNY_DAY
	clearflag JOHTO_FLAG_HIDE_RADIOTOWER_GATE
	clearflag JOHTO_FLAG_HIDE_GOLDENROD_RADIOTOWER_DIRECTOR
	clearflag JOHTO_FLAG_GOT_MARY_BRIGHT_POWDER
	clearflag JOHTO_FLAG_GOT_QUICK_CLAW
	clearflag JOHTO_FLAG_GOT_MAGNET

	setvar JOHTO_VAR_BUG_CONTEST_STATE, 0
	setvar JOHTO_VAR_KENYA, 0
	setvar JOHTO_VAR_LUGIA_OR_HOOH, 0
	setvar JOHTO_VAR_TRAIN, 0
	setvar JOHTO_VAR_ELEVATOR, 0
	setvar JOHTO_VAR_GOLDENROD_CITY_STATE, 1
	release
	end

GoldenrodCity_Trigger_Music::
	goto_if_lt JOHTO_VAR_GOLDENROD_CITY_STATE, 6, GoldenrodCity_Trigger_MusicNotYet
	goto_if_ge JOHTO_VAR_GOLDENROD_CITY_STATE, 11, GoldenrodCity_Trigger_MusicNotYet
	fadenewbgm ((558 + 1) + 0x40)
	special ShowMapNamePopup
	setvar VAR_TEMP_0, 1
	end

GoldenrodCity_Trigger_Music2::
	goto_if_lt JOHTO_VAR_GOLDENROD_CITY_STATE, 6, GoldenrodCity_Trigger_MusicNotYet
	goto_if_ge JOHTO_VAR_GOLDENROD_CITY_STATE, 11, GoldenrodCity_Trigger_MusicNotYet
	fadedefaultbgm
	special ShowMapNamePopup
	setvar VAR_TEMP_0, 1
	end

GoldenrodCity_Trigger_MusicNotYet::
	special ShowMapNamePopup
	setvar VAR_TEMP_0, 1
	end

GoldenrodCity_Elm_Togepi_Call::
	lock
	setspeaker GoldenrodCity_Text_ElmName
	pokenavcall GoldenrodCity_Text_ElmCall
	waitmessage
	delay 30
	release
	return

GoldenrodCity_EventScript_PokefanM::
	lock
	faceplayer
	msgbox GoldenrodCity_Text_PokefanM, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_EventScript_Youngster::
	msgbox GoldenrodCity_Text_Youngster1, MSGBOX_NPC
	end

GoldenrodCity_EventScript_Youngster2::
	msgbox GoldenrodCity_Text_Youngster2, MSGBOX_NPC
	end

GoldenrodCity_EventScript_CooltrainerF::
	lock
	faceplayer
	goto_if_set JOHTO_FLAG_HIDE_GOLDENROD_ROCKET_SCOUT, GoldenrodCity_EventScript_CooltrainerFCleared
	msgbox GoldenrodCity_Text_CooltrainerF1, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_EventScript_CooltrainerFCleared::
	msgbox GoldenrodCity_Text_CooltrainerF1_Cleared, MSGBOX_NPC
	end

GoldenrodCity_EventScript_Lass::
	lock
	faceplayer
	msgbox GoldenrodCity_Text_Lass, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_EventScript_Gramps::
	lock
	faceplayer
	msgbox GoldenrodCity_Text_Gramps, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_EventScript_NameRaterSign::
	msgbox GoldenrodCity_Text_NameRaterSign, MSGBOX_SIGN
	end

GoldenrodCity_EventScript_RocketScout::
	lock
	msgbox GoldenrodCity_Text_RocketScout1, MSGBOX_DEFAULT
	closemessage
	PLAYSE SE_PIN
	applymovement LOCALID_GOLDENROD_ROCKET_SCOUT, J_Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_GOLDENROD_ROCKET_SCOUT
	faceplayer
	msgbox GoldenrodCity_Text_RocketScout2, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_GOLDENROD_ROCKET_SCOUT, DIR_NORTH
	release
	end

GoldenrodCity_EventScript_Rocket1::
	lock
	faceplayer
	msgbox GoldenrodCity_Text_Rocket1, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_EventScript_Rocket2::
	lock
	faceplayer
	msgbox GoldenrodCity_Text_Rocket2, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_EventScript_Rocket3::
	lock
	faceplayer
	msgbox GoldenrodCity_Text_Rocket3, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_EventScript_Rocket4::
	lock
	faceplayer
	msgbox GoldenrodCity_Text_Rocket4, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_EventScript_Rocket5::
	lock
	faceplayer
	msgbox GoldenrodCity_Text_Rocket5, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_EventScript_Rocket6::
	lock
	faceplayer
	msgbox GoldenrodCity_Text_Rocket6, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_EventScript_Woman::
	lock
	faceplayer
	msgbox GoldenrodCity_Text_Woman, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_EventScript_Hiker::
	lock
	faceplayer
	goto_if_set JOHTO_FLAG_DAY_POKEMON, GoldenrodCity_EventScript_Hiker2
	msgbox GoldenrodCity_Text_HikerDay, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_EventScript_Hiker2::
	msgbox GoldenrodCity_Text_HikerNight, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_EventScript_Snubbull::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_SNUBBULL, CRY_MODE_NORMAL
	msgbox GoldenrodCity_Text_Snubbull, MSGBOX_DEFAULT
	waitmoncry
	release
	end

GoldenrodCity_EventScript_Mime::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_MR_MIME, CRY_MODE_NORMAL
	msgbox GoldenrodCity_Text_MrMime, MSGBOX_DEFAULT
	waitmoncry
	release
	end

GoldenrodCity_EventScript_SignUnderground::
	lock
	msgbox GoldenrodCity_Text_UndergroundSouthSign, MSGBOX_SIGN
	closemessage
	release
	end

GoldenrodCity_EventScript_SignDept::
	lock
	msgbox GoldenrodCity_Text_DeptStoreSign, MSGBOX_SIGN
	closemessage
	release
	end

GoldenrodCity_EventScript_SignBike::
	lock
	msgbox GoldenrodCity_Text_BikeShopSign, MSGBOX_SIGN
	closemessage
	release
	end

GoldenrodCity_EventScript_SignTrain::
	lock
	msgbox GoldenrodCity_Text_StationSign, MSGBOX_SIGN
	closemessage
	release
	end

GoldenrodCity_EventScript_SignGym::
	lock
	msgbox GoldenrodCity_Text_GymSign, MSGBOX_SIGN
	closemessage
	release
	end

GoldenrodCity_EventScript_SignFlower::
	lock
	msgbox GoldenrodCity_Text_FlowerShopSign, MSGBOX_SIGN
	closemessage
	release
	end

GoldenrodCity_EventScript_SignRadio::
	lock
	msgbox GoldenrodCity_Text_RadioTowerSign, MSGBOX_SIGN
	closemessage
	release
	end

GoldenrodCity_EventScript_SignGameCorner::
	lock
	msgbox GoldenrodCity_Text_GameCornerSign, MSGBOX_SIGN
	closemessage
	release
	end

GoldenrodCity_EventScript_Beauty::
	lock
	faceplayer
	msgbox GoldenrodCity_Text_Beauty, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_Text_Beauty:
	.string "Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}GOLDENRO{SE_M_FAINT_ATTACK}GYM!\p"
	.string "Ou{SE_M_SAND_TOMB}leade{SE_M_SAND_TOMB}WHITNE{SE_M_MOONLIGHT}i{SE_M_GRASSWHISTLE}no{SE_M_SPIT_UP}here\n"
	.string "righ{SE_M_SPIT_UP}now{SE_M_PERISH_SONG}Sh{SE_M_REVERSAL}migh{SE_M_SPIT_UP}b{SE_M_REVERSAL}a{SE_M_SPIT_UP}the\l"
	.string "RADI{SE_M_SOLAR_BEAM}TOWER.$"

GoldenrodCity_Text_Woman:
	.string "{SE_M_HEAL_BELL}use{SE_M_WATERFALL}t{SE_M_ATTRACT2}trai{SE_M_ATTRACT}i{SE_M_ATTRACT}WHITNEY'{SE_M_GRASSWHISTLE}GYM,\n"
	.string "bu{SE_M_SPIT_UP}al{SE_M_BATON_PASS}he{SE_M_SAND_TOMB}cryin{SE_M_SANDSTORM}gav{SE_M_REVERSAL}m{SE_M_REVERSAL}a\l"
	.string "headache.$"

GoldenrodCity_Text_HikerDay:
	.string "Whe{SE_M_ATTRACT}{SE_M_HEAL_BELL}wen{SE_M_SPIT_UP}int{SE_M_ATTRACT2}th{SE_M_REVERSAL}GAM{SE_M_SWORDS_DANCE}CORNER\n"
	.string "i{SE_M_SPIT_UP}wa{SE_M_GRASSWHISTLE}nigh{SE_M_SPIT_UP}time..{SE_M_PERISH_SONG}Ho{SE_M_TWISTER}lon{SE_M_SANDSTORM}wa{SE_M_GRASSWHISTLE}I\l"
	.string "i{SE_M_ATTRACT}there?!$"

GoldenrodCity_Text_HikerNight:
	.string "Whe{SE_M_ATTRACT}{SE_M_HEAL_BELL}wen{SE_M_SPIT_UP}int{SE_M_ATTRACT2}th{SE_M_REVERSAL}GAM{SE_M_SWORDS_DANCE}CORNER\n"
	.string "i{SE_M_SPIT_UP}wa{SE_M_GRASSWHISTLE}da{SE_M_YAWN}time..{SE_M_PERISH_SONG}Ho{SE_M_TWISTER}lon{SE_M_SANDSTORM}wa{SE_M_GRASSWHISTLE}I\l"
	.string "i{SE_M_ATTRACT}there?!$"

GoldenrodCity_Text_Snubbull:
	.string "SNUBBULL{SE_M_HEAT_WAVE}SNUUUBUUUULL!$"

GoldenrodCity_Text_MrMime:
	.string "............................$"

GoldenrodCity_Text_ElmName:
	.string "PROF.ELM$"

GoldenrodCity_Text_ElmCall:
	.string "PROF.ELM{SE_M_HEAT_WAVE}Hello{SE_M_SUPERSONIC}{PLAYER}?\n"
	.string "Ha{SE_M_GRASSWHISTLE}tha{SE_M_SPIT_UP}EG{SE_M_SWAGGER}hatche{SE_M_WATERFALL}yet?\p"
	.string "Onc{SE_M_REVERSAL}i{SE_M_SPIT_UP}hatches{SE_M_SUPERSONIC}don'{SE_M_SPIT_UP}forge{SE_M_SPIT_UP}to\n"
	.string "brin{SE_M_SANDSTORM}i{SE_M_SPIT_UP}b{SE_M_YAWN}th{SE_M_REVERSAL}lab{SE_M_DRAGON_RAGE}{SE_M_HEAL_BELL}nee{SE_M_WATERFALL}to\l"
	.string "se{SE_M_REVERSAL}it!$"

GoldenrodCity_Text_PokefanM:
	.string "The{SE_M_YAWN}buil{SE_M_SPIT_UP}th{SE_M_REVERSAL}ne{SE_M_TWISTER}RADI{SE_M_SOLAR_BEAM}TOWER\n"
	.string "t{SE_M_ATTRACT2}replac{SE_M_REVERSAL}th{SE_M_REVERSAL}ol{SE_M_WATERFALL}creak{SE_M_YAWN}one.$"

GoldenrodCity_Text_Youngster1:
	.string "{SE_M_HEAL_BELL}kno{SE_M_TWISTER}there'{SE_M_GRASSWHISTLE}{SE_M_CHARGE}ne{SE_M_TWISTER}BIK{SE_M_SWORDS_DANCE}SHOP,\n"
	.string "bu{SE_M_SPIT_UP}{SE_M_HEAL_BELL}can'{SE_M_SPIT_UP}fin{SE_M_WATERFALL}i{SE_M_SPIT_UP}anywhere.$"

GoldenrodCity_Text_CooltrainerF1:
	.string "I{SE_M_GRASSWHISTLE}tha{SE_M_SPIT_UP}ma{SE_M_ATTRACT}i{SE_M_ATTRACT}blac{SE_M_ENCORE2}dresse{SE_M_WATERFALL}up\n"
	.string "lik{SE_M_REVERSAL}{SE_M_CHARGE}TEA{SE_M_GIGA_DRAIN}ROCKE{SE_M_SWIFT}member?\p"
	.string "Ho{SE_M_TWISTER}silly!$"

GoldenrodCity_Text_CooltrainerF1_Cleared:
	.string "Wa{SE_M_GRASSWHISTLE}tha{SE_M_SPIT_UP}ma{SE_M_ATTRACT}i{SE_M_ATTRACT}blac{SE_M_ENCORE2}reall{SE_M_YAWN}part\n"
	.string "o{SE_M_ACID_ARMOR}TEA{SE_M_GIGA_DRAIN}ROCKET{SE_M_SING}{SE_M_HEAL_BELL}can'{SE_M_SPIT_UP}believ{SE_M_REVERSAL}it!$"

GoldenrodCity_Text_CooltrainerF2:
	.string "Th{SE_M_REVERSAL}RADI{SE_M_SOLAR_BEAM}TOWE{SE_M_MINIMIZE}i{SE_M_ATTRACT}GOLDENRO{SE_M_FAINT_ATTACK}CITY\n"
	.string "i{SE_M_GRASSWHISTLE}quit{SE_M_REVERSAL}th{SE_M_REVERSAL}landmark.\p"
	.string "They'r{SE_M_REVERSAL}runnin{SE_M_SANDSTORM}{SE_M_CHARGE}campaig{SE_M_ATTRACT}now.\p"
	.string "They'l{SE_M_BATON_PASS}giv{SE_M_REVERSAL}yo{SE_M_DIVE}{SE_M_CHARGE}shin{SE_M_YAWN}new\n"
	.string "RADI{SE_M_SOLAR_BEAM}i{SE_M_ACID_ARMOR}yo{SE_M_DIVE}ca{SE_M_ATTRACT}pas{SE_M_GRASSWHISTLE}thei{SE_M_SAND_TOMB}quiz.$"

GoldenrodCity_Text_CooltrainerF2_GotCard:
	.string "Oh{SE_M_SUPERSONIC}you{SE_M_SAND_TOMB}POKéGEA{SE_M_MINIMIZE}alread{SE_M_YAWN}works\n"
	.string "a{SE_M_GRASSWHISTLE}{SE_M_CHARGE}radio!$"

GoldenrodCity_Text_Youngster2:
	.string "E-he-he-he…\p"
	.string "{SE_M_HEAL_BELL}go{SE_M_SPIT_UP}i{SE_M_ATTRACT}troubl{SE_M_REVERSAL}fo{SE_M_SAND_TOMB}playin{SE_M_SANDSTORM}in\n"
	.string "th{SE_M_REVERSAL}DEPT.STOR{SE_M_SWORDS_DANCE}basement.$"

GoldenrodCity_Text_Lass:
	.string "Tha{SE_M_SPIT_UP}ma{SE_M_ATTRACT}insid{SE_M_REVERSAL}rate{SE_M_GRASSWHISTLE}your\n"
	.string "POKéMO{SE_M_PSYBEAM2}nicknames.\p"
	.string "H{SE_M_REVERSAL}ca{SE_M_ATTRACT}eve{SE_M_ATTRACT}renam{SE_M_REVERSAL}them.$"

GoldenrodCity_Text_Gramps:
	.string "Whew{SE_M_DRAGON_RAGE}Thi{SE_M_GRASSWHISTLE}tow{SE_M_ATTRACT}i{SE_M_GRASSWHISTLE}s{SE_M_ATTRACT2}big,\n"
	.string "{SE_M_HEAL_BELL}can'{SE_M_SPIT_UP}fin{SE_M_WATERFALL}anythin{SE_M_SANDSTORM}a{SE_M_SPIT_UP}all.$"

GoldenrodCity_Text_RocketScout1:
	.string "S{SE_M_ATTRACT2}thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}RADI{SE_M_SOLAR_BEAM}TOWER…$"

GoldenrodCity_Text_RocketScout2:
	.string "Wha{SE_M_SPIT_UP}d{SE_M_ATTRACT2}yo{SE_M_DIVE}want{SE_M_SUPERSONIC}pest?\n"
	.string "Scra{SE_M_MILK_DRINK}already!$"

GoldenrodCity_Text_Rocket1:
	.string "Sta{SE_M_YAWN}ou{SE_M_SPIT_UP}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}way!\n"
	.string "Bea{SE_M_SPIT_UP}it{SE_M_SUPERSONIC}kid!$"

GoldenrodCity_Text_Rocket2:
	.string "Tak{SE_M_REVERSAL}ove{SE_M_SAND_TOMB}th{SE_M_REVERSAL}RADI{SE_M_SOLAR_BEAM}TOWER…\p"
	.string "What{SE_M_SING}It'{SE_M_GRASSWHISTLE}non{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}you{SE_M_SAND_TOMB}business!$"

GoldenrodCity_Text_Rocket3:
	.string "POKéMON{SE_M_SING}They'r{SE_M_REVERSAL}jus{SE_M_SPIT_UP}tools\n"
	.string "w{SE_M_REVERSAL}us{SE_M_REVERSAL}t{SE_M_ATTRACT2}mak{SE_M_REVERSAL}money!$"

GoldenrodCity_Text_Rocket4:
	.string "Ou{SE_M_SAND_TOMB}drea{SE_M_MILK_DRINK}wil{SE_M_BATON_PASS}soo{SE_M_ATTRACT}com{SE_M_REVERSAL}true…\p"
	.string "I{SE_M_SPIT_UP}wa{SE_M_GRASSWHISTLE}{SE_M_CHARGE}long{SE_M_SUPERSONIC}har{SE_M_WATERFALL}struggle…$"

GoldenrodCity_Text_Rocket5:
	.string "Hey{SE_M_SUPERSONIC}brat{SE_M_DRAGON_RAGE}Yo{SE_M_DIVE}don'{SE_M_SPIT_UP}belon{SE_M_SANDSTORM}here!\n"
	.string "Ge{SE_M_SPIT_UP}los{SE_M_SPIT_UP}already!$"

GoldenrodCity_Text_Rocket6:
	.string "Com{SE_M_REVERSAL}an{SE_M_WATERFALL}tast{SE_M_REVERSAL}th{SE_M_REVERSAL}terro{SE_M_SAND_TOMB}of\n"
	.string "TEA{SE_M_GIGA_DRAIN}ROCKET!$"

GoldenrodCity_Text_StationSign:
	.string "GOLDENRO{SE_M_FAINT_ATTACK}CIT{SE_M_MOONLIGHT}STATION$"

GoldenrodCity_Text_RadioTowerSign:
	.string "GOLDENRO{SE_M_FAINT_ATTACK}CIT{SE_M_MOONLIGHT}RADI{SE_M_SOLAR_BEAM}TOWER$"

GoldenrodCity_Text_DeptStoreSign:
	.string "Ful{SE_M_BATON_PASS}Selectio{SE_M_ATTRACT}o{SE_M_ACID_ARMOR}POKéMO{SE_M_PSYBEAM2}Goods!\p"
	.string "GOLDENRO{SE_M_FAINT_ATTACK}CIT{SE_M_MOONLIGHT}DEPT.STORE$"

GoldenrodCity_Text_GymSign:
	.string "GOLDENRO{SE_M_FAINT_ATTACK}CIT{SE_M_MOONLIGHT}POKéMO{SE_M_PSYBEAM2}GYM\n"
	.string "LEADER{SE_M_HEAT_WAVE}WHITNEY\p"
	.string "Th{SE_M_REVERSAL}Incredibl{SE_M_YAWN}Prett{SE_M_YAWN}Girl!$"

GoldenrodCity_Text_CitySign:
	.string "GOLDENRO{SE_M_FAINT_ATTACK}CITY\p"
	.string "Th{SE_M_REVERSAL}Festiv{SE_M_REVERSAL}Cit{SE_M_YAWN}o{SE_M_ACID_ARMOR}Opulen{SE_M_SPIT_UP}Charm$"

GoldenrodCity_Text_BikeShopSign:
	.string "Th{SE_M_REVERSAL}Worl{SE_M_WATERFALL}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}Cycl{SE_M_REVERSAL}Path!\n"
	.string "BIK{SE_M_SWORDS_DANCE}SHOP$"

GoldenrodCity_Text_GameCornerSign:
	.string "You{SE_M_SAND_TOMB}Playground!\p"
	.string "GOLDENRO{SE_M_FAINT_ATTACK}CIT{SE_M_MOONLIGHT}GAM{SE_M_SWORDS_DANCE}CORNER$"

GoldenrodCity_Text_NameRaterSign:
	.string "NAM{SE_M_SWORDS_DANCE}RATER\p"
	.string "Ge{SE_M_SPIT_UP}You{SE_M_SAND_TOMB}POKéMO{SE_M_PSYBEAM2}Nickname{SE_M_GRASSWHISTLE}Rated$"

GoldenrodCity_Text_UndergroundNorthSign:
	.string "UNDERGROUN{SE_M_FAINT_ATTACK}ENTRANCE$"

GoldenrodCity_Text_UndergroundSouthSign:
	.string "UNDERGROUN{SE_M_FAINT_ATTACK}ENTRANCE$"

GoldenrodCity_Text_FlowerShopSign:
	.string "Bloomin{SE_M_SANDSTORM}Beautifu{SE_M_BATON_PASS}FLOWE{SE_M_MINIMIZE}SHOP$"

GoldenrodCity_Text_MoveTutorAsk:
	.string "{SE_M_HEAL_BELL}ca{SE_M_ATTRACT}teac{SE_M_TRI_ATTACK}you{SE_M_SAND_TOMB}POKéMO{SE_M_PSYBEAM2}some\n"
	.string "amazin{SE_M_SANDSTORM}moves!\p"
	.string "Shoul{SE_M_WATERFALL}{SE_M_HEAL_BELL}teac{SE_M_TRI_ATTACK}one?$"

GoldenrodCity_Text_MoveTutorCost:
	.string "It'l{SE_M_BATON_PASS}cos{SE_M_SPIT_UP}yo{SE_M_DIVE}100{SE_M_BITE}coins.\n"
	.string "Okay?$"

GoldenrodCity_Text_MoveTutorDecline:
	.string "Aww{SE_M_DIZZY_PUNCH}Bu{SE_M_SPIT_UP}thes{SE_M_REVERSAL}move{SE_M_GRASSWHISTLE}ar{SE_M_REVERSAL}great!$"

GoldenrodCity_Text_MoveTutorWhich:
	.string "Wahahah{SE_M_DRAGON_RAGE}Yo{SE_M_DIVE}won'{SE_M_SPIT_UP}regre{SE_M_SPIT_UP}it!\p"
	.string "Whic{SE_M_TRI_ATTACK}mov{SE_M_REVERSAL}shoul{SE_M_WATERFALL}{SE_M_HEAL_BELL}teach?$"

GoldenrodCity_Text_MoveTutorNoCash:
	.string "To{SE_M_ATTRACT2}bad{SE_M_PERISH_SONG}Gues{SE_M_GRASSWHISTLE}I'l{SE_M_BATON_PASS}nee{SE_M_WATERFALL}to\n"
	.string "ge{SE_M_SPIT_UP}som{SE_M_REVERSAL}cas{SE_M_TRI_ATTACK}fro{SE_M_MILK_DRINK}home…$"

GoldenrodCity_Text_MoveTutorUnderstand:
	.string "I{SE_M_ACID_ARMOR}yo{SE_M_DIVE}understan{SE_M_WATERFALL}thi{SE_M_GRASSWHISTLE}move,\n"
	.string "you'v{SE_M_REVERSAL}mad{SE_M_REVERSAL}i{SE_M_SPIT_UP}a{SE_M_GRASSWHISTLE}{SE_M_CHARGE}trainer.$"

GoldenrodCity_Text_MoveTutorFarewell:
	.string "Wahahah{SE_M_DRAGON_RAGE}Farewell{SE_M_SUPERSONIC}kid!$"

GoldenrodCity_Text_MoveTutorBut:
	.string "B-but…$"

GoldenrodCity_Text_MoveTutorNotEnoughCoins:
	.string "…Yo{SE_M_DIVE}don'{SE_M_SPIT_UP}hav{SE_M_REVERSAL}enoug{SE_M_TRI_ATTACK}coins…$"

CharacterStory_GoldenrodTransition::
	call JT_GoldenrodVisibility
	end

