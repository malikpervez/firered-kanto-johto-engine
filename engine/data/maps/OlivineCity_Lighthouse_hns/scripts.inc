@ Johto (data/maps/OlivineCity_Lighthouse_hns/scripts.inc), as built into the FireRed game.

OlivineCity_Lighthouse_hns_MapScripts::
	.byte 0

OlivineLighthouse_EventScript_Item_Ether::
	finditem ITEM_ETHER
	end

OlivineLighthouse_EventScript_Item_RareCandy::
	finditem ITEM_RARE_CANDY
	end

OlivineLighthouse_EventScript_Item_TMSwagger::
	finditem 668
	end

OlivineLighthouse_EventScript_Item_HyperPotion::
	finditem ITEM_HYPER_POTION
	end

OlivineLighthouse_EventScript_Item_Protein::
	finditem ITEM_PROTEIN
	end

OlivineLighthouse_EventScript_1FSailor::
	lock
	faceplayer
	msgbox OlivineLighthouse_Text_1FSailor, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineLighthouse_EventScript_1FPokefanF::
	lock
	faceplayer
	msgbox OlivineLighthouse_Text_1FPokefanF, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineLighthouse_Text_1FSailor:
	.string "Peopl{SE_M_REVERSAL}trai{SE_M_ATTRACT}a{SE_M_SPIT_UP}thi{SE_M_GRASSWHISTLE}LIGHTHOUSE.\p"
	.string "It'{SE_M_GRASSWHISTLE}no{SE_M_SPIT_UP}eas{SE_M_YAWN}t{SE_M_ATTRACT2}clim{SE_M_STRENGTH}wit{SE_M_TRI_ATTACK}all\n"
	.string "th{SE_M_REVERSAL}trainer{SE_M_GRASSWHISTLE}waitin{SE_M_SANDSTORM}inside.$"

OlivineLighthouse_Text_1FPokefanF:
	.string "I{SE_M_ATTRACT}th{SE_M_REVERSAL}past{SE_M_SUPERSONIC}POKéMO{SE_M_PSYBEAM2}use{SE_M_WATERFALL}t{SE_M_ATTRACT2}light\n"
	.string "th{SE_M_REVERSAL}se{SE_M_CHARGE}aroun{SE_M_WATERFALL}OLIVIN{SE_M_SWORDS_DANCE}a{SE_M_SPIT_UP}night.\p"
	.string "Th{SE_M_REVERSAL}LIGHTHOUS{SE_M_SWORDS_DANCE}wa{SE_M_GRASSWHISTLE}buil{SE_M_SPIT_UP}i{SE_M_ATTRACT}honor\n"
	.string "o{SE_M_ACID_ARMOR}thos{SE_M_REVERSAL}nobl{SE_M_REVERSAL}POKéMON.$"

OlivineLighthouse_EventScript_Huey::
	trainerbattle_single 1257, OlivineLighthouse_Text_SailorHueySeen, OlivineLighthouse_Text_SailorHueyBeaten, OlivineLighthouse_EventScript_RegisterHuey
	specialvar 32781, ShouldTryRematchBattle
	goto_if_eq 32781, TRUE, OlivineLighthouse_EventScript_RematchHuey
	msgbox OlivineLighthouse_Text_SailorHueyAfter, MSGBOX_AUTOCLOSE
	end

OlivineLighthouse_EventScript_RegisterHuey::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox OlivineLighthouse_Text_HueyRegister, MSGBOX_DEFAULT
	register_matchcall 1257
	release
	end

OlivineLighthouse_EventScript_RematchHuey::
	trainerbattle_rematch 1257, OlivineLighthouse_Text_HueyRematchIntro, OlivineLighthouse_Text_HueyRematchDefeat
	msgbox OlivineLighthouse_Text_HueyPostRematch, MSGBOX_AUTOCLOSE
	end

OlivineLighthouse_EventScript_GentlemanAlfred::
	trainerbattle_single 1183, OlivineLighthouse_Text_GentlemanAlfredSeen, OlivineLighthouse_Text_GentlemanAlfredBeaten
	msgbox OlivineLighthouse_Text_GentlemanAlfredAfter, MSGBOX_AUTOCLOSE
	end

OlivineLighthouse_Text_SailorHueySeen:
	.string "Me{SE_M_ATTRACT}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}se{SE_M_CHARGE}ar{SE_M_REVERSAL}always\n"
	.string "spoilin{SE_M_SANDSTORM}fo{SE_M_SAND_TOMB}{SE_M_CHARGE}goo{SE_M_WATERFALL}fight!$"

OlivineLighthouse_Text_SailorHueyBeaten:
	.string "Urf!\n"
	.string "{SE_M_HEAL_BELL}lose!$"

OlivineLighthouse_Text_SailorHueyAfter:
	.string "Wha{SE_M_SPIT_UP}power{SE_M_DRAGON_RAGE}Ho{SE_M_TWISTER}woul{SE_M_WATERFALL}yo{SE_M_DIVE}like\n"
	.string "t{SE_M_ATTRACT2}sai{SE_M_BATON_PASS}th{SE_M_REVERSAL}sea{SE_M_GRASSWHISTLE}wit{SE_M_TRI_ATTACK}me?$"

OlivineLighthouse_Text_HueyRegister:
	.string "Wha{SE_M_SPIT_UP}power{SE_M_DRAGON_RAGE}Ho{SE_M_TWISTER}woul{SE_M_WATERFALL}yo{SE_M_DIVE}like\n"
	.string "t{SE_M_ATTRACT2}sai{SE_M_BATON_PASS}th{SE_M_REVERSAL}sea{SE_M_GRASSWHISTLE}wit{SE_M_TRI_ATTACK}me?$"

OlivineLighthouse_Text_HueyRematchIntro:
	.string "Me{SE_M_ATTRACT}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}se{SE_M_CHARGE}ar{SE_M_REVERSAL}always\n"
	.string "spoilin{SE_M_SANDSTORM}fo{SE_M_SAND_TOMB}{SE_M_CHARGE}goo{SE_M_WATERFALL}fight!$"

OlivineLighthouse_Text_HueyRematchDefeat:
	.string "Urf!\n"
	.string "{SE_M_HEAL_BELL}lose!$"

OlivineLighthouse_Text_HueyPostRematch:
	.string "Wha{SE_M_SPIT_UP}power{SE_M_DRAGON_RAGE}Ho{SE_M_TWISTER}woul{SE_M_WATERFALL}yo{SE_M_DIVE}like\n"
	.string "t{SE_M_ATTRACT2}sai{SE_M_BATON_PASS}th{SE_M_REVERSAL}sea{SE_M_GRASSWHISTLE}wit{SE_M_TRI_ATTACK}me?$"

OlivineLighthouse_Text_GentlemanAlfredSeen:
	.string "Hm{SE_M_SING}Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}n{SE_M_ATTRACT2}place\n"
	.string "fo{SE_M_SAND_TOMB}playing.$"

OlivineLighthouse_Text_GentlemanAlfredBeaten:
	.string "Ah{SE_M_DRAGON_RAGE}{SE_M_HEAL_BELL}ca{SE_M_ATTRACT}se{SE_M_REVERSAL}tha{SE_M_SPIT_UP}you're\n"
	.string "serious.$"

OlivineLighthouse_Text_GentlemanAlfredAfter:
	.string "U{SE_M_MORNING_SUN}to{SE_M_MORNING_SUN}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}POKéMO{SE_M_PSYBEAM2}tha{SE_M_SPIT_UP}keeps\n"
	.string "th{SE_M_REVERSAL}LIGHTHOUS{SE_M_SWORDS_DANCE}lit.\p"
	.string "Bu{SE_M_SPIT_UP}{SE_M_HEAL_BELL}hea{SE_M_SAND_TOMB}tha{SE_M_SPIT_UP}it'{SE_M_GRASSWHISTLE}sic{SE_M_ENCORE2}now,\n"
	.string "an{SE_M_WATERFALL}can'{SE_M_SPIT_UP}b{SE_M_REVERSAL}cure{SE_M_WATERFALL}normally.$"

OlivineLighthouse_EventScript_BirdKeeperTheo::
	trainerbattle_single 1056, OlivineLighthouse_Text_BirdKeeperTheoSeen, OlivineLighthouse_Text_BirdKeeperTheoBeaten
	msgbox OlivineLighthouse_Text_BirdKeeperTheoAfter, MSGBOX_AUTOCLOSE
	end

OlivineLighthouse_EventScript_SailorTerrell::
	trainerbattle_single 1258, OlivineLighthouse_Text_SailorTerrellSeen, OlivineLighthouse_Text_SailorTerrellBeaten
	msgbox OlivineLighthouse_Text_SailorTerrellAfter, MSGBOX_AUTOCLOSE
	end

OlivineLighthouse_EventScript_GentlemanPreston::
	trainerbattle_single 1179, OlivineLighthouse_Text_GentlemanPrestonSeen, OlivineLighthouse_Text_GentlemanPrestonBeaten
	msgbox OlivineLighthouse_Text_GentlemanPrestonAfter, MSGBOX_AUTOCLOSE
	end

OlivineLighthouse_Text_BirdKeeperTheoSeen:
	.string "Wh{SE_M_YAWN}ar{SE_M_REVERSAL}yo{SE_M_DIVE}here{SE_M_SING}Ar{SE_M_REVERSAL}yo{SE_M_DIVE}just\n"
	.string "goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}gawk{SE_M_SING}{SE_M_HEAL_BELL}sugges{SE_M_SPIT_UP}yo{SE_M_DIVE}leave!$"

OlivineLighthouse_Text_BirdKeeperTheoBeaten:
	.string "Yo{SE_M_DIVE}reall{SE_M_YAWN}ar{SE_M_REVERSAL}concerne{SE_M_WATERFALL}about\n"
	.string "th{SE_M_REVERSAL}sic{SE_M_ENCORE2}POKéMON…$"

OlivineLighthouse_Text_BirdKeeperTheoAfter:
	.string "Ho{SE_M_TWISTER}th{SE_M_REVERSAL}hec{SE_M_ENCORE2}d{SE_M_ATTRACT2}yo{SE_M_DIVE}g{SE_M_ATTRACT2}up?\p"
	.string "{SE_M_HEAL_BELL}wan{SE_M_SPIT_UP}t{SE_M_ATTRACT2}visi{SE_M_SPIT_UP}th{SE_M_REVERSAL}sic{SE_M_ENCORE2}POKéMON,\n"
	.string "bu{SE_M_SPIT_UP}{SE_M_HEAL_BELL}can'{SE_M_SPIT_UP}ge{SE_M_SPIT_UP}u{SE_M_MORNING_SUN}there…$"

OlivineLighthouse_Text_SailorTerrellSeen:
	.string "Sailor{SE_M_GRASSWHISTLE}ar{SE_M_REVERSAL}bot{SE_M_TRI_ATTACK}kin{SE_M_WATERFALL}an{SE_M_WATERFALL}strong.\n"
	.string "Ho{SE_M_TWISTER}abou{SE_M_SPIT_UP}you?$"

OlivineLighthouse_Text_SailorTerrellBeaten:
	.string "Yo{SE_M_DIVE}ar{SE_M_REVERSAL}bot{SE_M_TRI_ATTACK}kin{SE_M_WATERFALL}an{SE_M_WATERFALL}strong…$"

OlivineLighthouse_Text_SailorTerrellAfter:
	.string "Ever{SE_M_YAWN}tim{SE_M_REVERSAL}{SE_M_HEAL_BELL}retur{SE_M_ATTRACT}t{SE_M_ATTRACT2}OLIVINE,\n"
	.string "{SE_M_HEAL_BELL}visi{SE_M_SPIT_UP}th{SE_M_REVERSAL}GYM.\p"
	.string "Th{SE_M_REVERSAL}GY{SE_M_GIGA_DRAIN}LEADER'{SE_M_GRASSWHISTLE}POKéMO{SE_M_PSYBEAM2}type\n"
	.string "change{SE_M_WATERFALL}withou{SE_M_SPIT_UP}m{SE_M_REVERSAL}noticing.$"

OlivineLighthouse_Text_GentlemanPrestonSeen:
	.string "{SE_M_HEAL_BELL}trave{SE_M_BATON_PASS}th{SE_M_REVERSAL}worl{SE_M_WATERFALL}t{SE_M_ATTRACT2}trai{SE_M_ATTRACT}my\n"
	.string "POKéMON{SE_M_PERISH_SONG}{SE_M_HEAL_BELL}wis{SE_M_TRI_ATTACK}t{SE_M_ATTRACT2}battl{SE_M_REVERSAL}you.$"

OlivineLighthouse_Text_GentlemanPrestonBeaten:
	.string "…sigh{SE_M_DIZZY_PUNCH}{SE_M_HEAL_BELL}mus{SE_M_SPIT_UP}trai{SE_M_ATTRACT}som{SE_M_REVERSAL}more…$"

OlivineLighthouse_Text_GentlemanPrestonAfter:
	.string "JASMIN{SE_M_SWORDS_DANCE}use{SE_M_WATERFALL}t{SE_M_ATTRACT2}us{SE_M_REVERSAL}ROCK-type\n"
	.string "POKéMO{SE_M_PSYBEAM2}lik{SE_M_REVERSAL}ONIX.$"

OlivineLighthouse_EventScript_SailorKent::
	trainerbattle_single 1259, OlivineLighthouse_Text_SailorKentSeen, OlivineLighthouse_Text_SailorKentBeaten
	msgbox OlivineLighthouse_Text_SailorKentAfter, MSGBOX_AUTOCLOSE
	end

OlivineLighthouse_EventScript_LassConnie::
	trainerbattle_single 1072, OlivineLighthouse_Text_LassConnieSeen, OlivineLighthouse_Text_LassConnieBeaten
	msgbox OlivineLighthouse_Text_LassConnieAfter, MSGBOX_AUTOCLOSE
	end

OlivineLighthouse_Text_SailorKentSeen:
	.string "JASMIN{SE_M_SWORDS_DANCE}mus{SE_M_SPIT_UP}b{SE_M_REVERSAL}worrie{SE_M_WATERFALL}sic{SE_M_ENCORE2}about\n"
	.string "th{SE_M_REVERSAL}POKéMO{SE_M_PSYBEAM2}here.\p"
	.string "Sh{SE_M_REVERSAL}won'{SE_M_SPIT_UP}eve{SE_M_ATTRACT}smil{SE_M_REVERSAL}thes{SE_M_REVERSAL}days.$"

OlivineLighthouse_Text_SailorKentBeaten:
	.string "{SE_M_HEAL_BELL}can'{SE_M_SPIT_UP}manag{SE_M_REVERSAL}{SE_M_CHARGE}smil{SE_M_REVERSAL}either…$"

OlivineLighthouse_Text_SailorKentAfter:
	.string "Speakin{SE_M_SANDSTORM}o{SE_M_ACID_ARMOR}sick{SE_M_SUPERSONIC}I'v{SE_M_REVERSAL}hear{SE_M_WATERFALL}there's\n"
	.string "{SE_M_CHARGE}goo{SE_M_WATERFALL}PHARMAC{SE_M_MOONLIGHT}i{SE_M_ATTRACT}CIANWOOD.$"

OlivineLighthouse_Text_LassConnieSeen:
	.string "JASMIN{SE_M_SWORDS_DANCE}i{SE_M_GRASSWHISTLE}thi{SE_M_GRASSWHISTLE}city'{SE_M_GRASSWHISTLE}GY{SE_M_GIGA_DRAIN}LEADER.\p"
	.string "{SE_M_HEAL_BELL}mea{SE_M_ATTRACT}t{SE_M_ATTRACT2}brin{SE_M_SANDSTORM}he{SE_M_SAND_TOMB}bac{SE_M_ENCORE2}wit{SE_M_TRI_ATTACK}me.\p"
	.string "Nobod{SE_M_YAWN}ha{SE_M_WATERFALL}bette{SE_M_SAND_TOMB}ge{SE_M_SPIT_UP}i{SE_M_ATTRACT}m{SE_M_YAWN}way!$"

OlivineLighthouse_Text_LassConnieBeaten:
	.string "Aaack{SE_M_DRAGON_RAGE}M{SE_M_YAWN}POKéMON!$"

OlivineLighthouse_Text_LassConnieAfter:
	.string "Right{SE_M_PERISH_SONG}Anybod{SE_M_YAWN}woul{SE_M_WATERFALL}b{SE_M_REVERSAL}worrie{SE_M_WATERFALL}if\n"
	.string "hi{SE_M_GRASSWHISTLE}o{SE_M_SAND_TOMB}he{SE_M_SAND_TOMB}ow{SE_M_ATTRACT}POKéMO{SE_M_PSYBEAM2}wer{SE_M_REVERSAL}hurt.\p"
	.string "I'l{SE_M_BATON_PASS}pra{SE_M_YAWN}fo{SE_M_SAND_TOMB}th{SE_M_REVERSAL}POKéMO{SE_M_PSYBEAM2}here{SE_M_SUPERSONIC}so\n"
	.string "JASMIN{SE_M_SWORDS_DANCE}ca{SE_M_ATTRACT}com{SE_M_REVERSAL}bac{SE_M_ENCORE2}t{SE_M_ATTRACT2}th{SE_M_REVERSAL}GYM.$"

OlivineLighthouse_EventScript_SailorErnest::
	trainerbattle_single 1260, OlivineLighthouse_Text_SailorErnestSeen, OlivineLighthouse_Text_SailorErnestBeaten
	msgbox OlivineLighthouse_Text_SailorErnestAfter, MSGBOX_AUTOCLOSE
	end

OlivineLighthouse_EventScript_BirdKeeperDenis::
	trainerbattle_single 1058, OlivineLighthouse_Text_BirdKeeperDenisSeen, OlivineLighthouse_Text_BirdKeeperDenisBeaten
	msgbox OlivineLighthouse_Text_BirdKeeperDenisAfter, MSGBOX_AUTOCLOSE
	end

OlivineLighthouse_Text_SailorErnestSeen:
	.string "{SE_M_HEAL_BELL}wante{SE_M_WATERFALL}t{SE_M_ATTRACT2}battl{SE_M_REVERSAL}JASMINE{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}she's\n"
	.string "no{SE_M_SPIT_UP}u{SE_M_MORNING_SUN}t{SE_M_ATTRACT2}i{SE_M_SPIT_UP}now.\p"
	.string "So{SE_M_SUPERSONIC}ho{SE_M_TWISTER}abou{SE_M_SPIT_UP}you?$"

OlivineLighthouse_Text_SailorErnestBeaten:
	.string "Whoa{SE_M_SUPERSONIC}whoa{SE_M_PERISH_SONG}You'r{SE_M_REVERSAL}overwhelming!$"

OlivineLighthouse_Text_SailorErnestAfter:
	.string "{SE_M_BONEMERANG}GY{SE_M_GIGA_DRAIN}LEADE{SE_M_MINIMIZE}isn'{SE_M_SPIT_UP}jus{SE_M_SPIT_UP}abou{SE_M_SPIT_UP}being\n"
	.string "strong.\p"
	.string "{SE_M_BONEMERANG}LEADE{SE_M_MINIMIZE}als{SE_M_ATTRACT2}need{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}be\n"
	.string "compassionate.$"

OlivineLighthouse_Text_BirdKeeperDenisSeen:
	.string "We'r{SE_M_REVERSAL}prett{SE_M_YAWN}hig{SE_M_TRI_ATTACK}u{SE_M_MORNING_SUN}here{SE_M_PERISH_SONG}M{SE_M_YAWN}bird\n"
	.string "POKéMO{SE_M_PSYBEAM2}ar{SE_M_REVERSAL}i{SE_M_ATTRACT}prim{SE_M_REVERSAL}form.$"

OlivineLighthouse_Text_BirdKeeperDenisBeaten:
	.string "Oops{SE_M_DIZZY_PUNCH}The{SE_M_YAWN}crashed…$"

OlivineLighthouse_Text_BirdKeeperDenisAfter:
	.string "M{SE_M_YAWN}POKéMO{SE_M_PSYBEAM2}learne{SE_M_WATERFALL}ho{SE_M_TWISTER}t{SE_M_ATTRACT2}us{SE_M_REVERSAL}FL{SE_M_MOONLIGHT}in\n"
	.string "CIANWOOD.\p"
	.string "Well{SE_M_SUPERSONIC}sinc{SE_M_REVERSAL}I'{SE_M_MILK_DRINK}{SE_M_CHARGE}loser{SE_M_SUPERSONIC}I'l{SE_M_BATON_PASS}FLY\n"
	.string "acros{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}sea…$"

OlivineLighthouse_EventScript_Jasmine::
	lock
	faceplayer
	goto_if_eq 20583, 3, OlivineLighthouse_EventScript_JasmineGoGetPotion
	goto_if_eq 20583, 4, OlivineLighthouse_EventScript_JasmineDeliverPotion
	msgbox OlivineLighthouse_Text_JasmineCianwoodPharmacy, MSGBOX_DEFAULT
	msgbox OlivineLighthouse_Text_JasmineGetMedicine, MSGBOX_DEFAULT
	closemessage
	setvar 20583, 3
	release
	end

OlivineLighthouse_EventScript_JasmineGoGetPotion::
	msgbox OlivineLighthouse_Text_JasmineGetMedicine2, MSGBOX_DEFAULT
	release
	end

OlivineLighthouse_EventScript_Ampharos::
	lock
	faceplayer
	goto_if_lt 20583, 5, OlivineLighthouse_EventScript_AmpharosSick
	fadescreen 3
	playse 119
	waitse
	fadescreen 2
	playmoncry 181, 0
	msgbox OlivineLighthouse_Text_AmphyPaluPalulu, MSGBOX_DEFAULT
	waitmoncry
	setflag 8661
	release
	end

OlivineLighthouse_EventScript_AmpharosSick::
	playmoncry 181, 0
	msgbox OlivineLighthouse_Text_AmphyPalPaloo, MSGBOX_DEFAULT
	waitmoncry
	msgbox OlivineLighthouse_Text_AmphyBreathingLabored, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineLighthouse_Text_JasmineCianwoodPharmacy:
	.string "JASMINE{SE_M_HEAT_WAVE}…Thi{SE_M_GRASSWHISTLE}POKéMO{SE_M_PSYBEAM2}alway{SE_M_GRASSWHISTLE}kept\n"
	.string "th{SE_M_REVERSAL}se{SE_M_CHARGE}li{SE_M_SPIT_UP}a{SE_M_SPIT_UP}night.\p"
	.string "…Bu{SE_M_SPIT_UP}i{SE_M_SPIT_UP}suddenl{SE_M_YAWN}go{SE_M_SPIT_UP}sick{SE_M_DIZZY_PUNCH}It's\n"
	.string "gaspin{SE_M_SANDSTORM}fo{SE_M_SAND_TOMB}air…\p"
	.string "…{SE_M_HEAL_BELL}understan{SE_M_WATERFALL}tha{SE_M_SPIT_UP}ther{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}a\n"
	.string "wonderfu{SE_M_BATON_PASS}PHARMAC{SE_M_MOONLIGHT}i{SE_M_ATTRACT}CIANWOOD…\p"
	.string "Bu{SE_M_SPIT_UP}that'{SE_M_GRASSWHISTLE}acros{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}sea…\n"
	.string "An{SE_M_WATERFALL}{SE_M_HEAL_BELL}can'{SE_M_SPIT_UP}leav{SE_M_REVERSAL}AMPH{SE_M_MOONLIGHT}unattended…$"

OlivineLighthouse_Text_JasmineGetMedicine:
	.string "…Ma{SE_M_YAWN}{SE_M_HEAL_BELL}as{SE_M_ENCORE2}yo{SE_M_DIVE}t{SE_M_ATTRACT2}ge{SE_M_SPIT_UP}som{SE_M_REVERSAL}medicine\n"
	.string "fo{SE_M_SAND_TOMB}me{SE_M_SING}Please?$"

OlivineLighthouse_Text_JasmineGetMedicine2:
	.string "Ther{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}wonderfu{SE_M_BATON_PASS}PHARMACY\n"
	.string "i{SE_M_ATTRACT}CIANWOOD…\p"
	.string "Bu{SE_M_SPIT_UP}that'{SE_M_GRASSWHISTLE}acros{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}sea…\n"
	.string "An{SE_M_WATERFALL}{SE_M_HEAL_BELL}can'{SE_M_SPIT_UP}leav{SE_M_REVERSAL}AMPH{SE_M_MOONLIGHT}unattended…\p"
	.string "…Ma{SE_M_YAWN}{SE_M_HEAL_BELL}as{SE_M_ENCORE2}yo{SE_M_DIVE}t{SE_M_ATTRACT2}ge{SE_M_SPIT_UP}som{SE_M_REVERSAL}medicine\n"
	.string "fo{SE_M_SAND_TOMB}me{SE_M_SING}Please?$"

OlivineLighthouse_Text_JasmineCureAmphy:
	.string "JASMINE{SE_M_HEAT_WAVE}…Wil{SE_M_BATON_PASS}tha{SE_M_SPIT_UP}medicin{SE_M_REVERSAL}cure\n"
	.string "AMPHY?$"

OlivineLighthouse_EventScript_JasmineDeliverPotion::
	msgbox OlivineLighthouse_Text_JasmineCureAmphy, MSGBOX_YESNO
	goto_if_eq 32781, FALSE, OlivineLighthouse_EventScript_JasmineRefuse
	playse 1
	removeitem ITEM_SECRET_POTION
	msgbox OlivineLighthouse_Text_PlayerHandedSecretpotion, MSGBOX_DEFAULT
	waitse
	msgbox OlivineLighthouse_Text_JasmineDontBeOffended, MSGBOX_DEFAULT
	closemessage
	turnobject 12, DIR_NORTH
	delay 20
	turnobject 13, DIR_SOUTH
	playfanfare 368
	waitfanfare
	msgbox OlivineLighthouse_Text_JasmineAmphyHowFeeling, MSGBOX_DEFAULT
	fadescreen 3
	playse 119
	waitse
	fadescreen 2
	playmoncry 181, 0
	msgbox OlivineLighthouse_Text_AmphyPaluPalulu, MSGBOX_DEFAULT
	waitmoncry
	closemessage
	applymovement 13, OlivineLighthouse_Movement_Amphy
	waitmovement 0
	applymovement 12, OlivineLighthouse_Movement_Jasmine
	msgbox OlivineLighthouse_Text_JasmineThankYou, MSGBOX_DEFAULT
	closemessage

	fadescreen 1
	playse 9
	setflag 8324
	removeobject 12
	waitse
	delay 50
	fadescreen 0
	setvar 20597, 1
	setvar 20583, 5
	setflag 8661
	clearflag 8320
	release
	end

OlivineLighthouse_Movement_Jasmine:
	face_player
	step_end

OlivineLighthouse_Movement_Amphy:
	walk_up
	jump_in_place_down
	jump_in_place_left
	jump_in_place_right
	jump_in_place_up
	face_down
	step_end

OlivineLighthouse_EventScript_JasmineRefuse::
	msgbox OlivineLighthouse_Text_JasmineISee, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineLighthouse_Text_PlayerHandedSecretpotion:
	.string "{PLAYER} hande{SE_M_WATERFALL}th{SE_M_REVERSAL}SECRE{SE_M_SWIFT}POTIO{SE_M_PSYBEAM2}to\n"
	.string "JASMINE.$"

OlivineLighthouse_Text_JasmineDontBeOffended:
	.string "JASMINE{SE_M_HEAT_WAVE}…Um{SE_M_SUPERSONIC}pleas{SE_M_REVERSAL}don'{SE_M_SPIT_UP}be\n"
	.string "offended…\p"
	.string "…AMPH{SE_M_MOONLIGHT}wil{SE_M_BATON_PASS}no{SE_M_SPIT_UP}tak{SE_M_REVERSAL}anythin{SE_M_SANDSTORM}from\n"
	.string "anyon{SE_M_REVERSAL}bu{SE_M_SPIT_UP}me…$"

OlivineLighthouse_Text_JasmineAmphyHowFeeling:
	.string "JASMINE{SE_M_HEAT_WAVE}…\p"
	.string "AMPHY{SE_M_SUPERSONIC}ho{SE_M_TWISTER}ar{SE_M_REVERSAL}yo{SE_M_DIVE}feeling?$"

OlivineLighthouse_Text_JasmineThankYou:
	.string "JASMINE{SE_M_HEAT_WAVE}…Oh{SE_M_SUPERSONIC}I'{SE_M_MILK_DRINK}s{SE_M_ATTRACT2}relieved…\p"
	.string "Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}jus{SE_M_SPIT_UP}s{SE_M_ATTRACT2}wonderful…\p"
	.string "Than{SE_M_ENCORE2}yo{SE_M_DIVE}s{SE_M_ATTRACT2}very{SE_M_SUPERSONIC}ver{SE_M_YAWN}much.\p"
	.string "…{SE_M_HEAL_BELL}wil{SE_M_BATON_PASS}retur{SE_M_ATTRACT}t{SE_M_ATTRACT2}th{SE_M_REVERSAL}GYM…\p"
	.string "I'l{SE_M_BATON_PASS}als{SE_M_ATTRACT2}war{SE_M_ATTRACT}you{SE_M_SUPERSONIC}STEE{SE_M_BRICK_BREAK}types\n"
	.string "ar{SE_M_REVERSAL}powerful.$"

OlivineLighthouse_Text_JasmineISee:
	.string "JASMINE{SE_M_HEAT_WAVE}…{SE_M_HEAL_BELL}see…\n"
	.string "…AMPHY{SE_M_SUPERSONIC}han{SE_M_SANDSTORM}on!$"

OlivineLighthouse_Text_AmphyPalPaloo:
	.string "AMPHY{SE_M_HEAT_WAVE}…\n"
	.string "…Pa{SE_M_DIZZY_PUNCH}paloo…$"

OlivineLighthouse_Text_AmphyBreathingLabored:
	.string "It{SE_M_GRASSWHISTLE}breathin{SE_M_SANDSTORM}i{SE_M_GRASSWHISTLE}terribly\n"
	.string "labored…$"

OlivineLighthouse_Text_AmphyPaluPalulu:
	.string "AMPHY{SE_M_HEAT_WAVE}Palu{SE_M_DRAGON_RAGE}Palulu!$"

