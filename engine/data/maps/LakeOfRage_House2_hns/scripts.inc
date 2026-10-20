@ Johto (data/maps/LakeOfRage_House2_hns/scripts.inc), as built into the FireRed game.

LakeOfRage_House2_hns_MapScripts::
	.byte 0

LakeOfRage_House2_EventScript_Fisher::
	lock
	faceplayer
	goto_if_ge JOHTO_VAR_MAHOGANY_TOWN_STATE, 14, LakeOfRage_House2_EventScript_FisherAfterRockets
	goto_if_eq JOHTO_VAR_LAKE_OF_RAGE_FISHERMAN, 0, LakeOfRage_House2_EventScript_FisherFirstMeeting
	msgbox LakeOfRage_House2_Text_MenInBlack, MSGBOX_DEFAULT
	closemessage
	release
	end

LakeOfRage_House2_EventScript_FisherFirstMeeting::
	msgbox LakeOfRage_House2_Text_LakeHistory, MSGBOX_DEFAULT
	msgbox LakeOfRage_House2_Text_MenInBlack, MSGBOX_DEFAULT
	setvar JOHTO_VAR_LAKE_OF_RAGE_FISHERMAN, 1
	closemessage
	release
	end

LakeOfRage_House2_EventScript_FisherAfterRockets::
	goto_if_eq JOHTO_VAR_LAKE_OF_RAGE_FISHERMAN, 2, LakeOfRage_House2_EventScript_FisherAnotherMagikarp
	msgbox LakeOfRage_House2_Text_WorldsLargest, MSGBOX_DEFAULT
	msgbox LakeOfRage_House2_Text_ForMe, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, LakeOfRage_House2_EventScript_FisherNo
	getpartysize
	goto_if_eq VAR_RESULT, 1, LakeOfRage_House2_EventScript_LastMon
	special ChoosePartyMon
	waitstate
	lock
	showmoneybox 0, 0
	copyvar VAR_0x800A, VAR_0x8004
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, LakeOfRage_House2_EventScript_FisherNoMoneyBox
	removegenericmon SPECIES_MAGIKARP
	goto_if_eq VAR_RESULT, FALSE, LakeOfRage_House2_EventScript_FisherNotMagikarp
	goto_if_eq VAR_RESULT, MON_SATISFACTORY, LakeOfRage_House2_EventScript_FisherSatisfied
	goto_if_eq VAR_RESULT, MON_UNSATISFACTORY, LakeOfRage_House2_EventScript_FisherSmallMagikarp

LakeOfRage_House2_EventScript_FisherNo::
	msgbox LakeOfRage_House2_Text_Refused, MSGBOX_DEFAULT
	closemessage
	release
	end

LakeOfRage_House2_EventScript_FisherNoMoneyBox::
	msgbox LakeOfRage_House2_Text_Refused, MSGBOX_DEFAULT
	hidemoneybox
	closemessage
	release
	end

LakeOfRage_House2_EventScript_FisherNotMagikarp::
	msgbox LakeOfRage_House2_Text_NotMagikarp, MSGBOX_DEFAULT
	hidemoneybox
	closemessage
	release
	end

LakeOfRage_House2_EventScript_FisherSmallMagikarp::
	setvar JOHTO_VAR_LAKE_OF_RAGE_FISHERMAN, 2
	msgbox LakeOfRage_House2_Text_TooShort, MSGBOX_DEFAULT
	addmoney 2000
	updatemoneybox
	playse SE_SHOP
	waitse
	hidemoneybox
	closemessage
	release
	end

LakeOfRage_House2_EventScript_FisherAnotherMagikarp::
	msgbox LakeOfRage_House2_Text_ForMe, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, LakeOfRage_House2_EventScript_FisherNo
	getpartysize
	goto_if_eq VAR_RESULT, 1, LakeOfRage_House2_EventScript_LastMon
	special ChoosePartyMon
	waitstate
	lock
	showmoneybox 0, 0
	copyvar VAR_0x800A, VAR_0x8004
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, LakeOfRage_House2_EventScript_FisherNoMoneyBox
	removegenericmon SPECIES_MAGIKARP
	goto_if_eq VAR_RESULT, FALSE, LakeOfRage_House2_EventScript_FisherNotMagikarp
	goto_if_eq VAR_RESULT, MON_SATISFACTORY, LakeOfRage_House2_EventScript_FisherSatisfied
	goto_if_eq VAR_RESULT, MON_UNSATISFACTORY, LakeOfRage_House2_EventScript_FisherSmallMagikarp

LakeOfRage_House2_EventScript_LastMon::
	msgbox LakeOfRage_House2_Text_LastMon, MSGBOX_DEFAULT
	closemessage
	release
	end

LakeOfRage_House2_EventScript_FisherSatisfied::
	setvar JOHTO_VAR_LAKE_OF_RAGE_FISHERMAN, 2
	msgbox LakeOfRage_House2_Text_BigPayout, MSGBOX_DEFAULT
	addmoney 100000
	updatemoneybox
	playse SE_SHOP
	waitse
	hidemoneybox
	closemessage
	release
	end

LakeOfRage_House2_Text_LakeHistory:
	.string "LAK{SE_M_SWORDS_DANCE}O{SE_M_LEER}RAG{SE_M_SWORDS_DANCE}i{SE_M_GRASSWHISTLE}actuall{SE_M_YAWN}{SE_M_CHARGE}crater\n"
	.string "mad{SE_M_REVERSAL}b{SE_M_YAWN}rampagin{SE_M_SANDSTORM}GYARADOS.\p"
	.string "Th{SE_M_REVERSAL}crate{SE_M_SAND_TOMB}fille{SE_M_WATERFALL}u{SE_M_MORNING_SUN}wit{SE_M_TRI_ATTACK}rainwater\n"
	.string "an{SE_M_WATERFALL}th{SE_M_REVERSAL}LAK{SE_M_SWORDS_DANCE}wa{SE_M_GRASSWHISTLE}formed.\p"
	.string "That'{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}stor{SE_M_YAWN}passe{SE_M_WATERFALL}o{SE_M_ATTRACT}fro{SE_M_MILK_DRINK}my\n"
	.string "Grandpa'{SE_M_GRASSWHISTLE}great-great-grandpa.\p"
	.string "I{SE_M_SPIT_UP}use{SE_M_WATERFALL}t{SE_M_ATTRACT2}b{SE_M_REVERSAL}tha{SE_M_SPIT_UP}yo{SE_M_DIVE}coul{SE_M_WATERFALL}catch\n"
	.string "livel{SE_M_YAWN}MAGIKAR{SE_M_PETAL_DANCE}there{SE_M_SUPERSONIC}but…\p"
	.string "{SE_M_HEAL_BELL}don'{SE_M_SPIT_UP}understan{SE_M_WATERFALL}what'{SE_M_GRASSWHISTLE}happening.$"

LakeOfRage_House2_Text_MenInBlack:
	.string "Th{SE_M_REVERSAL}LAK{SE_M_SWORDS_DANCE}hasn'{SE_M_SPIT_UP}bee{SE_M_ATTRACT}norma{SE_M_BATON_PASS}since\n"
	.string "thos{SE_M_REVERSAL}me{SE_M_ATTRACT}wearin{SE_M_SANDSTORM}blac{SE_M_ENCORE2}arrived.$"

LakeOfRage_House2_Text_LastMon:
	.string "Wel{SE_M_BATON_PASS}don'{SE_M_SPIT_UP}le{SE_M_SPIT_UP}m{SE_M_REVERSAL}tak{SE_M_REVERSAL}you{SE_M_SAND_TOMB}last\n"
	.string "POKéMON!$"

LakeOfRage_House2_Text_WorldsLargest:
	.string "LAK{SE_M_SWORDS_DANCE}O{SE_M_LEER}RAG{SE_M_SWORDS_DANCE}i{SE_M_GRASSWHISTLE}bac{SE_M_ENCORE2}t{SE_M_ATTRACT2}normal.\p"
	.string "Th{SE_M_REVERSAL}MAGIKAR{SE_M_PETAL_DANCE}hav{SE_M_REVERSAL}returned.\p"
	.string "{SE_M_HEAL_BELL}ma{SE_M_YAWN}ye{SE_M_SPIT_UP}realiz{SE_M_REVERSAL}m{SE_M_YAWN}drea{SE_M_MILK_DRINK}o{SE_M_ACID_ARMOR}own-\n"
	.string "in{SE_M_SANDSTORM}th{SE_M_REVERSAL}world'{SE_M_GRASSWHISTLE}larges{SE_M_SPIT_UP}MAGIKARP.\p"
	.string "I{SE_M_ATTRACT}fact..{SE_M_PERISH_SONG}I'l{SE_M_BATON_PASS}pa{SE_M_YAWN}yo{SE_M_DIVE}¥200{SE_M_BITE}for\n"
	.string "ever{SE_M_YAWN}MAGIKAR{SE_M_PETAL_DANCE}yo{SE_M_DIVE}giv{SE_M_REVERSAL}me{SE_M_SUPERSONIC}and\l"
	.string "¥100,00{SE_M_BITE}fo{SE_M_SAND_TOMB}{SE_M_CHARGE}HUG{SE_M_SWORDS_DANCE}MAGIKARP!$"

LakeOfRage_House2_Text_ForMe:
	.string "So..{SE_M_PERISH_SONG}D{SE_M_ATTRACT2}yo{SE_M_DIVE}hav{SE_M_REVERSAL}{SE_M_CHARGE}MAGIKAR{SE_M_PETAL_DANCE}for\n"
	.string "me?$"

LakeOfRage_House2_Text_HaveMagikarp:
	.string "Ah{SE_M_SUPERSONIC}yo{SE_M_DIVE}hav{SE_M_REVERSAL}{SE_M_CHARGE}MAGIKARP{SE_M_DRAGON_RAGE}Let's\n"
	.string "se{SE_M_REVERSAL}ho{SE_M_TWISTER}bi{SE_M_SANDSTORM}tha{SE_M_SPIT_UP}bab{SE_M_YAWN}is.$"

LakeOfRage_House2_Text_BigPayout:
	.string "Wow{SE_M_DRAGON_RAGE}Thi{SE_M_GRASSWHISTLE}on{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}outstanding!\p"
	.string "{SE_M_HEAL_BELL}ti{SE_M_MORNING_SUN}m{SE_M_YAWN}ha{SE_M_SPIT_UP}t{SE_M_ATTRACT2}you!\p"
	.string "Here'{SE_M_GRASSWHISTLE}{SE_M_CHARGE}littl{SE_M_REVERSAL}somethin{SE_M_SANDSTORM}fo{SE_M_SAND_TOMB}your\n"
	.string "trouble.$"

LakeOfRage_House2_Text_Bonus:
	.string "Th{SE_M_REVERSAL}recor{SE_M_WATERFALL}i{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}importan{SE_M_SPIT_UP}thing.\p"
	.string "Thin{SE_M_ENCORE2}o{SE_M_ACID_ARMOR}tha{SE_M_SPIT_UP}a{SE_M_GRASSWHISTLE}{SE_M_CHARGE}bonus!$"

LakeOfRage_House2_Text_TooShort:
	.string "Wow{SE_M_DRAGON_RAGE}Thi{SE_M_GRASSWHISTLE}on{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}outstanding!\p"
	.string "…{SE_M_HEAL_BELL}wis{SE_M_TRI_ATTACK}{SE_M_HEAL_BELL}coul{SE_M_WATERFALL}sa{SE_M_YAWN}that{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}I've\n"
	.string "see{SE_M_ATTRACT}{SE_M_CHARGE}bigge{SE_M_SAND_TOMB}on{SE_M_REVERSAL}before.\p"
	.string "{SE_M_HEAL_BELL}gues{SE_M_GRASSWHISTLE}it'{SE_M_GRASSWHISTLE}wort{SE_M_TRI_ATTACK}something.$"

LakeOfRage_House2_Text_NotMagikarp:
	.string "What{SE_M_SING}That'{SE_M_GRASSWHISTLE}no{SE_M_SPIT_UP}{SE_M_CHARGE}MAGIKARP!$"

LakeOfRage_House2_Text_Refused:
	.string "Oh{SE_M_DIZZY_PUNCH}S{SE_M_ATTRACT2}yo{SE_M_DIVE}didn'{SE_M_SPIT_UP}ge{SE_M_SPIT_UP}on{SE_M_REVERSAL}good\n"
	.string "enoug{SE_M_TRI_ATTACK}t{SE_M_ATTRACT2}sho{SE_M_TWISTER}me{SE_M_SING}Mayb{SE_M_REVERSAL}nex{SE_M_SPIT_UP}time.$"

