@ Johto (data/maps/GoldenrodCity_BillsHouse_hns/scripts.inc), as built into the FireRed game.

GoldenrodCity_BillsHouse_hns_MapScripts::
	.byte 0

GoldenrodCity_BillsHouse_EventScript_Sister::
	lock
	faceplayer
	msgbox BillHouse_Text_SisterStorageSystem, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_BillsHouse_EventScript_Mom::
	lock
	faceplayer
	goto_if_set 10391, GoldenrodCity_BillsHouse_EventScript_Mom2
	msgbox BillHouse_Text_MomBeforeEcruteak, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_BillsHouse_EventScript_Mom2::
	msgbox BillHouse_Text_MomAfterEcruteak, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_BillsHouse_EventScript_Bill::
	lock
	faceplayer
	goto_if_unset 8708, GoldenrodCity_BillsHouse_EventScript_Bill_Eevee
	msgbox BillHouse_Text_PopWontWork, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_BillsHouse_EventScript_Bill_Eevee::
	msgbox BillHouse_Text_TakeThisEevee, MSGBOX_YESNO
	goto_if_eq 32781, FALSE, GoldenrodCity_BillsHouse_EventScript_Bill_Refused
	msgbox BillHouse_Text_CountingOnYou, MSGBOX_DEFAULT


	setvar 16385, 133
	bufferspeciesname STR_VAR_1, 133
	givenamedmon 3
	call J_Common_EventScript_GiftMonNamed



	setflag 8708
	msgbox BillHouse_Text_EeveeMayEvolve, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_BillsHouse_EventScript_Bill_Refused::
	msgbox BillHouse_Text_NoEevee, MSGBOX_DEFAULT
	closemessage
	release
	end

BillHouse_Text_TakeThisEevee:
	.string "BILL{SE_M_HEAT_WAVE}Hi{SE_M_SUPERSONIC}{PLAYER}{SE_M_DRAGON_RAGE}D{SE_M_ATTRACT2}u{SE_M_GRASSWHISTLE}{SE_M_CHARGE}favo{SE_M_SAND_TOMB}and\n"
	.string "tak{SE_M_REVERSAL}thi{SE_M_GRASSWHISTLE}EEVEE.\p"
	.string "I{SE_M_SPIT_UP}wa{SE_M_GRASSWHISTLE}lef{SE_M_SPIT_UP}i{SE_M_ATTRACT}ou{SE_M_SAND_TOMB}car{SE_M_REVERSAL}while\n"
	.string "{SE_M_HEAL_BELL}wa{SE_M_GRASSWHISTLE}awa{SE_M_YAWN}workin{SE_M_SANDSTORM}o{SE_M_ATTRACT}m{SE_M_YAWN}system.\p"
	.string "Someon{SE_M_REVERSAL}ha{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}tak{SE_M_REVERSAL}car{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}it,\n"
	.string "bu{SE_M_SPIT_UP}{SE_M_HEAL_BELL}don'{SE_M_SPIT_UP}lik{SE_M_REVERSAL}bein{SE_M_SANDSTORM}outside.\p"
	.string "Ca{SE_M_ATTRACT}{SE_M_HEAL_BELL}coun{SE_M_SPIT_UP}o{SE_M_ATTRACT}yo{SE_M_DIVE}t{SE_M_ATTRACT2}pla{SE_M_YAWN}wit{SE_M_TRI_ATTACK}it,\n"
	.string "{PLAYER}?$"

BillHouse_Text_CountingOnYou:
	.string "BILL{SE_M_HEAT_WAVE}{SE_M_HEAL_BELL}kne{SE_M_TWISTER}you'{SE_M_WATERFALL}com{SE_M_REVERSAL}through!\p"
	.string "Wa{SE_M_YAWN}t{SE_M_ATTRACT2}go{SE_M_DRAGON_RAGE}You'r{SE_M_REVERSAL}th{SE_M_REVERSAL}rea{SE_M_BATON_PASS}deal!\p"
	.string "OK{SE_M_SUPERSONIC}I'{SE_M_MILK_DRINK}countin{SE_M_SANDSTORM}o{SE_M_ATTRACT}you.\p"
	.string "Tak{SE_M_REVERSAL}goo{SE_M_WATERFALL}car{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}it!$"

BillHouse_Text_ReceivedEevee:
	.string "{PLAYER} receive{SE_M_WATERFALL}EEVEE!$"

BillHouse_Text_EeveeMayEvolve:
	.string "BILL{SE_M_HEAT_WAVE}PROF.EL{SE_M_GIGA_DRAIN}claim{SE_M_GRASSWHISTLE}EEVE{SE_M_SWORDS_DANCE}may\n"
	.string "evolv{SE_M_REVERSAL}i{SE_M_ATTRACT}ne{SE_M_TWISTER}an{SE_M_WATERFALL}unknow{SE_M_ATTRACT}ways.$"

BillHouse_Text_PartyFull:
	.string "Whoa{SE_M_SUPERSONIC}wait{SE_M_PERISH_SONG}Yo{SE_M_DIVE}can'{SE_M_SPIT_UP}carr{SE_M_YAWN}any\n"
	.string "mor{SE_M_REVERSAL}POKéMON.$"

BillHouse_Text_NoEevee:
	.string "Oh{SE_M_DIZZY_PUNCH}No{SE_M_TWISTER}wha{SE_M_SPIT_UP}t{SE_M_ATTRACT2}do?$"

BillHouse_Text_PopWontWork:
	.string "BILL{SE_M_HEAT_WAVE}M{SE_M_YAWN}pop{SE_M_SUPERSONIC}h{SE_M_REVERSAL}won'{SE_M_SPIT_UP}work{SE_M_PERISH_SONG}Al{SE_M_BATON_PASS}he\n"
	.string "doe{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}goo{SE_M_ACID_ARMOR}of{SE_M_ACID_ARMOR}al{SE_M_BATON_PASS}da{SE_M_YAWN}long.\p"
	.string "He'{SE_M_GRASSWHISTLE}gettin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}b{SE_M_REVERSAL}{SE_M_CHARGE}rea{SE_M_BATON_PASS}headache…$"

BillHouse_Text_MomBeforeEcruteak:
	.string "Oh{SE_M_SUPERSONIC}yo{SE_M_DIVE}collec{SE_M_SPIT_UP}POKéMON{SE_M_SING}M{SE_M_YAWN}son\n"
	.string "BIL{SE_M_BRICK_BREAK}i{SE_M_GRASSWHISTLE}a{SE_M_ATTRACT}expert.\p"
	.string "H{SE_M_REVERSAL}jus{SE_M_SPIT_UP}go{SE_M_SPIT_UP}calle{SE_M_WATERFALL}t{SE_M_ATTRACT2}th{SE_M_REVERSAL}POKéMON\n"
	.string "CENTE{SE_M_MINIMIZE}i{SE_M_ATTRACT}ECRUTEA{SE_M_SNORE}CITY.\p"
	.string "M{SE_M_YAWN}husban{SE_M_WATERFALL}wen{SE_M_SPIT_UP}of{SE_M_ACID_ARMOR}t{SE_M_ATTRACT2}th{SE_M_REVERSAL}GAME\n"
	.string "CORNE{SE_M_MINIMIZE}withou{SE_M_SPIT_UP}bein{SE_M_SANDSTORM}called…$"

BillHouse_Text_MomAfterEcruteak:
	.string "M{SE_M_YAWN}husban{SE_M_WATERFALL}wa{SE_M_GRASSWHISTLE}onc{SE_M_REVERSAL}know{SE_M_ATTRACT}a{SE_M_GRASSWHISTLE}a\n"
	.string "POKéMANIAC.\p"
	.string "BIL{SE_M_BRICK_BREAK}mus{SE_M_SPIT_UP}hav{SE_M_REVERSAL}take{SE_M_ATTRACT}afte{SE_M_SAND_TOMB}his\n"
	.string "father.$"

BillHouse_Text_SisterUsefulNumber:
	.string "Ar{SE_M_REVERSAL}yo{SE_M_DIVE}{SE_M_CHARGE}TRAINER?\p"
	.string "I'v{SE_M_REVERSAL}go{SE_M_SPIT_UP}{SE_M_CHARGE}usefu{SE_M_BATON_PASS}phon{SE_M_REVERSAL}number\n"
	.string "fo{SE_M_SAND_TOMB}you.$"

BillHouse_Text_RecordedBillsNumber:
	.string "{PLAYER} recorde{SE_M_WATERFALL}BILL'{SE_M_GRASSWHISTLE}number.$"

BillHouse_Text_SisterRefusedNumber:
	.string "M{SE_M_YAWN}brothe{SE_M_SAND_TOMB}mad{SE_M_REVERSAL}th{SE_M_REVERSAL}P{SE_M_PSYBEAM}POKéMON\n"
	.string "storag{SE_M_REVERSAL}system.\p"
	.string "{SE_M_HEAL_BELL}wa{SE_M_GRASSWHISTLE}goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}giv{SE_M_REVERSAL}yo{SE_M_DIVE}BILL's\n"
	.string "number…$"

BillHouse_Text_SisterPhoneFull:
	.string "Yo{SE_M_DIVE}can'{SE_M_SPIT_UP}recor{SE_M_WATERFALL}an{SE_M_YAWN}mor{SE_M_REVERSAL}numbers.$"

BillHouse_Text_SisterStorageSystem:
	.string "M{SE_M_YAWN}bi{SE_M_SANDSTORM}brothe{SE_M_SAND_TOMB}BIL{SE_M_BRICK_BREAK}mad{SE_M_REVERSAL}th{SE_M_REVERSAL}PC\n"
	.string "POKéMO{SE_M_PSYBEAM2}storag{SE_M_REVERSAL}system.$"

