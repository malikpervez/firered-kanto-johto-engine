@ Johto (data/maps/Route44_hns/scripts.inc), as built into the FireRed game.

Route44_hns_MapScripts::
	map_script 3, Route44_OnTransition
	map_script 5, J_SetTimeEncounters
	.byte 0

Route44_OnTransition:
	callnative SetTimeBasedEncounters
	end

Route44_EventScript_Wilton::
	trainerbattle_single 1209, Route44_Text_FisherWilton1Seen, Route44_Text_FisherWilton1Beaten, Route44_EventScript_RegisterWilton
	goto_if_set 8942, Route44_EventScript_WiltonGiveItem
	specialvar 32781, ShouldTryRematchBattle
	goto_if_eq 32781, TRUE, Route44_EventScript_RematchWilton
	msgbox Route44_Text_FisherWiltonHugePoliwag, MSGBOX_AUTOCLOSE
	end

Route44_EventScript_RegisterWilton::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route44_Text_WiltonRegister, MSGBOX_DEFAULT
	register_matchcall 1209
	release
	end

Route44_EventScript_RematchWilton::
	trainerbattle_rematch 1209, Route44_Text_WiltonRematchIntro, Route44_Text_WiltonRematchDefeat
	msgbox Route44_Text_WiltonPostRematch, MSGBOX_AUTOCLOSE
	end

Route44_EventScript_WiltonGiveItem::
	msgbox Route44_Text_WiltonHasItem, MSGBOX_DEFAULT
	giveitem 20659
	goto_if_eq 32781, FALSE, Route44_EventScript_WiltonNoRoom
	clearflag 8942
	msgbox Route44_Text_WiltonGaveItem, MSGBOX_AUTOCLOSE
	end

Route44_EventScript_WiltonNoRoom::
	msgbox Route44_Text_WiltonNoRoom, MSGBOX_AUTOCLOSE
	end

Route44_EventScript_Edgar::
	trainerbattle_single 1210, Route44_Text_FisherEdgarSeen, Route44_Text_FisherEdgarBeaten
	msgbox Route44_Text_FisherEdgarAfter, MSGBOX_AUTOCLOSE
	end

Route44_EventScript_Vance::
	trainerbattle_single 1059, Route44_Text_BirdKeeperVance1Seen, Route44_Text_BirdKeeperVance1Beaten, Route44_EventScript_RegisterVance
	specialvar 32781, ShouldTryRematchBattle
	goto_if_eq 32781, TRUE, Route44_EventScript_RematchVance
	msgbox Route44_Text_BirdKeeperVanceBirds, MSGBOX_AUTOCLOSE
	end

Route44_EventScript_RegisterVance::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route44_Text_VanceRegister, MSGBOX_DEFAULT
	register_matchcall 1059
	release
	end

Route44_EventScript_RematchVance::
	trainerbattle_rematch 1059, Route44_Text_VanceRematchIntro, Route44_Text_VanceRematchDefeat
	msgbox Route44_Text_VancePostRematch, MSGBOX_AUTOCLOSE
	end

Route44_EventScript_Phil::
	trainerbattle_single 1337, Route44_Text_PsychicPhilSeen, Route44_Text_PsychicPhilBeaten
	msgbox Route44_Text_PsychicPhilAfter, MSGBOX_AUTOCLOSE
	end

Route44_EventScript_Zach::
	trainerbattle_single 1141, Route44_Text_PokemaniacZachSeen, Route44_Text_PokemaniacZachBeaten
	msgbox Route44_Text_PokemaniacZachAfter, MSGBOX_AUTOCLOSE
	end

Route44_EventScript_Allen::
	trainerbattle_single 1095, Route44_Text_CooltrainermAllenSeen, Route44_Text_CooltrainermAllenBeaten
	msgbox Route44_Text_CooltrainermAllenAfter, MSGBOX_AUTOCLOSE
	end

Route44_EventScript_Cybil::
	trainerbattle_single 1111, Route44_Text_CooltrainerfCybilSeen, Route44_Text_CooltrainerfCybilBeaten
	msgbox Route44_Text_CooltrainerfCybilAfter, MSGBOX_AUTOCLOSE
	end

Route44_EventScript_Sign1::
	msgbox Route44_Text_Sign1, MSGBOX_SIGN
	end

Route44_EventScript_Sign2::
	msgbox Route44_Text_Sign2, MSGBOX_SIGN
	end

Route44_EventScript_Item_MaxRepel::
	finditem ITEM_MAX_REPEL
	end

Route44_EventScript_Item_UltraBall::
	finditem ITEM_ULTRA_BALL
	end

Route44_EventScript_Item_Elixir::
	finditem ITEM_ELIXIR
	end

Route44_Text_FisherWilton1Seen:
	.string "Aack!\p"
	.string "Yo{SE_M_DIVE}mad{SE_M_REVERSAL}m{SE_M_REVERSAL}los{SE_M_REVERSAL}{SE_M_CHARGE}POLIWAG!\n"
	.string "Wha{SE_M_SPIT_UP}ar{SE_M_REVERSAL}yo{SE_M_DIVE}goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}d{SE_M_ATTRACT2}abou{SE_M_SPIT_UP}it?$"

Route44_Text_FisherWilton1Beaten:
	.string "Jus{SE_M_SPIT_UP}forge{SE_M_SPIT_UP}abou{SE_M_SPIT_UP}it.$"

Route44_Text_FisherWiltonHugePoliwag:
	.string "Tha{SE_M_SPIT_UP}POLIWA{SE_M_SWAGGER}tha{SE_M_SPIT_UP}go{SE_M_SPIT_UP}away…\n"
	.string "i{SE_M_SPIT_UP}wa{SE_M_GRASSWHISTLE}huge.\p"
	.string "{SE_M_HEAL_BELL}swea{SE_M_SAND_TOMB}i{SE_M_SPIT_UP}must'v{SE_M_REVERSAL}been\n"
	.string "1{SE_M_TAIL_WHIP}fee{SE_M_SPIT_UP}long!$"

Route44_Text_WiltonRegister:
	.string "Tha{SE_M_SPIT_UP}POLIWA{SE_M_SWAGGER}tha{SE_M_SPIT_UP}go{SE_M_SPIT_UP}away…\n"
	.string "i{SE_M_SPIT_UP}wa{SE_M_GRASSWHISTLE}huge.\p"
	.string "{SE_M_HEAL_BELL}swea{SE_M_SAND_TOMB}i{SE_M_SPIT_UP}must'v{SE_M_REVERSAL}been\n"
	.string "1{SE_M_TAIL_WHIP}fee{SE_M_SPIT_UP}long!$"

Route44_Text_WiltonRematchIntro:
	.string "Aack!\p"
	.string "Yo{SE_M_DIVE}mad{SE_M_REVERSAL}m{SE_M_REVERSAL}los{SE_M_REVERSAL}{SE_M_CHARGE}POLIWAG!\n"
	.string "Wha{SE_M_SPIT_UP}ar{SE_M_REVERSAL}yo{SE_M_DIVE}goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}d{SE_M_ATTRACT2}abou{SE_M_SPIT_UP}it?$"

Route44_Text_WiltonRematchDefeat:
	.string "Jus{SE_M_SPIT_UP}forge{SE_M_SPIT_UP}abou{SE_M_SPIT_UP}it.$"

Route44_Text_WiltonPostRematch:
	.string "Tha{SE_M_SPIT_UP}POLIWA{SE_M_SWAGGER}tha{SE_M_SPIT_UP}go{SE_M_SPIT_UP}away…\n"
	.string "i{SE_M_SPIT_UP}wa{SE_M_GRASSWHISTLE}huge.\p"
	.string "{SE_M_HEAL_BELL}swea{SE_M_SAND_TOMB}i{SE_M_SPIT_UP}must'v{SE_M_REVERSAL}been\n"
	.string "1{SE_M_TAIL_WHIP}fee{SE_M_SPIT_UP}long!$"

Route44_Text_WiltonHasItem:
	.string "Hey{SE_M_DRAGON_RAGE}{SE_M_HEAL_BELL}reele{SE_M_WATERFALL}i{SE_M_ATTRACT}something\n"
	.string "othe{SE_M_SAND_TOMB}tha{SE_M_ATTRACT}{SE_M_CHARGE}POKéMON!\p"
	.string "Here{SE_M_SUPERSONIC}yo{SE_M_DIVE}ca{SE_M_ATTRACT}hav{SE_M_REVERSAL}it!$"

Route44_Text_WiltonGaveItem:
	.string "I'l{SE_M_BATON_PASS}le{SE_M_SPIT_UP}yo{SE_M_DIVE}kno{SE_M_TWISTER}i{SE_M_ACID_ARMOR}I\n"
	.string "fis{SE_M_TRI_ATTACK}u{SE_M_MORNING_SUN}anythin{SE_M_SANDSTORM}else!$"

Route44_Text_WiltonNoRoom:
	.string "Hmm{SE_M_SUPERSONIC}you{SE_M_SAND_TOMB}BA{SE_M_SWAGGER}i{SE_M_GRASSWHISTLE}full.\p"
	.string "Com{SE_M_REVERSAL}bac{SE_M_ENCORE2}whe{SE_M_ATTRACT}yo{SE_M_DIVE}hav{SE_M_REVERSAL}room.$"

Route44_Text_FisherEdgarSeen:
	.string "{SE_M_HEAL_BELL}fis{SE_M_TRI_ATTACK}unti{SE_M_BATON_PASS}{SE_M_HEAL_BELL}can'{SE_M_SPIT_UP}anymore.\p"
	.string "{SE_M_HEAL_BELL}als{SE_M_ATTRACT2}battl{SE_M_REVERSAL}unti{SE_M_BATON_PASS}{SE_M_HEAL_BELL}drop.\p"
	.string "That'{SE_M_GRASSWHISTLE}m{SE_M_YAWN}relationshi{SE_M_MORNING_SUN}wit{SE_M_TRI_ATTACK}my\n"
	.string "POKéMON.$"

Route44_Text_FisherEdgarBeaten:
	.string "Hmmmm{SE_M_DIZZY_PUNCH}Thi{SE_M_GRASSWHISTLE}isn'{SE_M_SPIT_UP}right.$"

Route44_Text_FisherEdgarAfter:
	.string "That'{SE_M_GRASSWHISTLE}10{SE_M_BITE}win{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}10{SE_M_HEADBUTT}losses.\p"
	.string "{SE_M_HEAL_BELL}won'{SE_M_SPIT_UP}battl{SE_M_REVERSAL}agai{SE_M_ATTRACT}fo{SE_M_SAND_TOMB}{SE_M_CHARGE}while.$"

Route44_Text_BirdKeeperVance1Seen:
	.string "D{SE_M_ATTRACT2}yo{SE_M_DIVE}kno{SE_M_TWISTER}abou{SE_M_SPIT_UP}th{SE_M_REVERSAL}legendary\n"
	.string "bir{SE_M_WATERFALL}POKéMON?$"

Route44_Text_BirdKeeperVance1Beaten:
	.string "Whew{SE_M_DRAGON_RAGE}You'r{SE_M_REVERSAL}ho{SE_M_SPIT_UP}stuff.$"

Route44_Text_BirdKeeperVanceBirds:
	.string "ARTICUNO{SE_M_SUPERSONIC}ZAPDO{SE_M_SKETCH}an{SE_M_WATERFALL}MOLTRE{SE_M_SKETCH}are\n"
	.string "th{SE_M_REVERSAL}thre{SE_M_REVERSAL}legendar{SE_M_YAWN}bir{SE_M_WATERFALL}POKéMON.\p"
	.string "{SE_M_HEAL_BELL}hear{SE_M_WATERFALL}ther{SE_M_REVERSAL}ar{SE_M_REVERSAL}othe{SE_M_SAND_TOMB}legendary\n"
	.string "birds{SE_M_SUPERSONIC}though.$"

Route44_Text_VanceRegister:
	.string "ARTICUNO{SE_M_SUPERSONIC}ZAPDO{SE_M_SKETCH}an{SE_M_WATERFALL}MOLTRE{SE_M_SKETCH}are\n"
	.string "th{SE_M_REVERSAL}thre{SE_M_REVERSAL}legendar{SE_M_YAWN}bir{SE_M_WATERFALL}POKéMON.\p"
	.string "{SE_M_HEAL_BELL}hear{SE_M_WATERFALL}ther{SE_M_REVERSAL}ar{SE_M_REVERSAL}othe{SE_M_SAND_TOMB}legendary\n"
	.string "birds{SE_M_SUPERSONIC}though.$"

Route44_Text_VanceRematchIntro:
	.string "D{SE_M_ATTRACT2}yo{SE_M_DIVE}kno{SE_M_TWISTER}abou{SE_M_SPIT_UP}th{SE_M_REVERSAL}legendary\n"
	.string "bir{SE_M_WATERFALL}POKéMON?$"

Route44_Text_VanceRematchDefeat:
	.string "Whew{SE_M_DRAGON_RAGE}You'r{SE_M_REVERSAL}ho{SE_M_SPIT_UP}stuff.$"

Route44_Text_VancePostRematch:
	.string "ARTICUNO{SE_M_SUPERSONIC}ZAPDO{SE_M_SKETCH}an{SE_M_WATERFALL}MOLTRE{SE_M_SKETCH}are\n"
	.string "th{SE_M_REVERSAL}thre{SE_M_REVERSAL}legendar{SE_M_YAWN}bir{SE_M_WATERFALL}POKéMON.\p"
	.string "{SE_M_HEAL_BELL}hear{SE_M_WATERFALL}ther{SE_M_REVERSAL}ar{SE_M_REVERSAL}othe{SE_M_SAND_TOMB}legendary\n"
	.string "birds{SE_M_SUPERSONIC}though.$"

Route44_Text_PsychicPhilSeen:
	.string "I'{SE_M_MILK_DRINK}gonn{SE_M_CHARGE}win{SE_M_SUPERSONIC}fo{SE_M_SAND_TOMB}sure!$"

Route44_Text_PsychicPhilBeaten:
	.string "Arrgh{SE_M_DIZZY_PUNCH}That'{SE_M_GRASSWHISTLE}{SE_M_CHARGE}shockin{SE_M_SANDSTORM}loss…$"

Route44_Text_PsychicPhilAfter:
	.string "It'{SE_M_GRASSWHISTLE}importan{SE_M_SPIT_UP}t{SE_M_ATTRACT2}hav{SE_M_REVERSAL}conviction\n"
	.string "o{SE_M_ATTRACT}you{SE_M_SAND_TOMB}side.$"

Route44_Text_PokemaniacZachSeen:
	.string "I'l{SE_M_BATON_PASS}d{SE_M_ATTRACT2}anythin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}ge{SE_M_SPIT_UP}m{SE_M_YAWN}hands\n"
	.string "o{SE_M_ATTRACT}rar{SE_M_REVERSAL}POKéMON!$"

Route44_Text_PokemaniacZachBeaten:
	.string "Oooh{SE_M_SUPERSONIC}you{SE_M_SAND_TOMB}POKéMO{SE_M_PSYBEAM2}ar{SE_M_REVERSAL}so\n"
	.string "appealing.$"

Route44_Text_PokemaniacZachAfter:
	.string "I{SE_M_ACID_ARMOR}{SE_M_CHARGE}POKéMO{SE_M_PSYBEAM2}ha{SE_M_GRASSWHISTLE}differen{SE_M_SPIT_UP}colors\n"
	.string "fro{SE_M_MILK_DRINK}usual{SE_M_SUPERSONIC}it'{SE_M_GRASSWHISTLE}mor{SE_M_REVERSAL}valuable.\p"
	.string "What{SE_M_SING}Yo{SE_M_DIVE}mea{SE_M_ATTRACT}that'{SE_M_GRASSWHISTLE}no{SE_M_SPIT_UP}true?$"

Route44_Text_CooltrainermAllenSeen:
	.string "{SE_M_HEAL_BELL}ca{SE_M_ATTRACT}tel{SE_M_BATON_PASS}you'r{SE_M_REVERSAL}{SE_M_CHARGE}goo{SE_M_WATERFALL}trainer\n"
	.string "b{SE_M_YAWN}lookin{SE_M_SANDSTORM}a{SE_M_SPIT_UP}you.\p"
	.string "I'{SE_M_MILK_DRINK}goo{SE_M_WATERFALL}a{SE_M_SPIT_UP}POKéMON{SE_M_SUPERSONIC}an{SE_M_WATERFALL}{SE_M_HEAL_BELL}can\n"
	.string "se{SE_M_REVERSAL}tha{SE_M_SPIT_UP}yo{SE_M_DIVE}ar{SE_M_REVERSAL}too.$"

Route44_Text_CooltrainermAllenBeaten:
	.string "Tch{SE_M_DRAGON_RAGE}It'{SE_M_GRASSWHISTLE}{SE_M_CHARGE}tota{SE_M_BATON_PASS}los{SE_M_GRASSWHISTLE}o{SE_M_ATTRACT}m{SE_M_YAWN}part.$"

Route44_Text_CooltrainermAllenAfter:
	.string "Wow{SE_M_PERISH_SONG}Yo{SE_M_DIVE}hav{SE_M_REVERSAL}{SE_M_CHARGE}lo{SE_M_SPIT_UP}o{SE_M_ACID_ARMOR}BADGES.\p"
	.string "N{SE_M_ATTRACT2}wonde{SE_M_SAND_TOMB}you'r{SE_M_REVERSAL}s{SE_M_ATTRACT2}tough.\p"
	.string "{SE_M_HEAL_BELL}wonde{SE_M_SAND_TOMB}i{SE_M_ACID_ARMOR}ECRUTEA{SE_M_SNORE}GYM'{SE_M_GRASSWHISTLE}MORTY\n"
	.string "i{SE_M_GRASSWHISTLE}stil{SE_M_BATON_PASS}i{SE_M_ATTRACT}training?\p"
	.string "H{SE_M_REVERSAL}reall{SE_M_YAWN}hammere{SE_M_WATERFALL}me.$"

Route44_Text_CooltrainerfCybilSeen:
	.string "Yo{SE_M_DIVE}loo{SE_M_ENCORE2}strong.\p"
	.string "Goo{SE_M_WATERFALL}trainer{SE_M_GRASSWHISTLE}see{SE_M_ENCORE2}tough\n"
	.string "opponent{SE_M_GRASSWHISTLE}instinctively.$"

Route44_Text_CooltrainerfCybilBeaten:
	.string "Nope{SE_M_DRAGON_RAGE}Thi{SE_M_GRASSWHISTLE}won'{SE_M_SPIT_UP}d{SE_M_ATTRACT2}a{SE_M_SPIT_UP}all.$"

Route44_Text_CooltrainerfCybilAfter:
	.string "W{SE_M_REVERSAL}al{SE_M_BATON_PASS}ge{SE_M_SPIT_UP}bette{SE_M_SAND_TOMB}b{SE_M_YAWN}experiencing\n"
	.string "man{SE_M_YAWN}battles.\p"
	.string "{SE_M_HEAL_BELL}battle{SE_M_WATERFALL}{SE_M_CHARGE}lo{SE_M_SPIT_UP}t{SE_M_ATTRACT2}becom{SE_M_REVERSAL}wha{SE_M_SPIT_UP}I\n"
	.string "a{SE_M_MILK_DRINK}today--a{SE_M_ATTRACT}elite.$"

Route44_Text_Sign1:
	.string "ROUT{SE_M_SWORDS_DANCE}44\n"
	.string "IC{SE_M_SWORDS_DANCE}PAT{SE_M_SWAGGER2}AHEAD$"

Route44_Text_Sign2:
	.string "ROUT{SE_M_SWORDS_DANCE}44\p"
	.string "MAHOGAN{SE_M_MOONLIGHT}TOW{SE_M_PSYBEAM2}{SE_M_PAY_DAY}BLACKTHOR{SE_M_PSYBEAM2}CITY$"

