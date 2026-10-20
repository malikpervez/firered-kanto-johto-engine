@ Johto (data/maps/Route35_hns/scripts.inc), as built into the FireRed game.

Route35_hns_MapScripts::
	map_script 3, Route35_OnTransition
	map_script 5, J_SetTimeEncounters
	.byte 0

Route35_OnTransition:
	callnative SetTimeBasedEncounters
	end

Route35_EventScript_CamperIvan::
	trainerbattle_single 1357, Route35_Text_CamperIvanSeen, Route35_Text_CamperIvanBeaten
	msgbox Route35_Text_CamperIvanAfter, MSGBOX_AUTOCLOSE
	end

Route35_EventScript_CamperElliot::
	trainerbattle_single 1358, Route35_Text_CamperElliotSeen, Route35_Text_CamperElliotBeaten
	msgbox Route35_Text_CamperElliotAfter, MSGBOX_AUTOCLOSE
	end

Route35_EventScript_PicnickerBrooke::
	trainerbattle_single 1344, Route35_Text_PicnickerBrookeSeen, Route35_Text_PicnickerBrookeBeaten
	msgbox Route35_Text_PicnickerBrookeAfter, MSGBOX_AUTOCLOSE
	end

Route35_EventScript_PicnickerKim::
	trainerbattle_single 1345, Route35_Text_PicnickerKimSeen, Route35_Text_PicnickerKimBeaten
	msgbox Route35_Text_PicnickerKimAfter, MSGBOX_AUTOCLOSE
	end

Route35_EventScript_BirdKeeperBryan::
	trainerbattle_single 1055, Route35_Text_BirdKeeperBryanSeen, Route35_Text_BirdKeeperBryanBeaten
	msgbox Route35_Text_BirdKeeperBryanAfter, MSGBOX_AUTOCLOSE
	end

Route35_EventScript_JugglerIrwin::
	trainerbattle_single 1320, Route35_Text_JugglerIrwinSeen, Route35_Text_JugglerIrwinBeaten, Route35_EventScript_RegisterIrwin
	specialvar 32781, ShouldTryRematchBattle
	goto_if_eq 32781, TRUE, Route35_EventScript_RematchIrwin
	msgbox Route35_Text_JugglerIrwinAfter, MSGBOX_AUTOCLOSE
	end

Route35_EventScript_RegisterIrwin::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route35_Text_IrwinRegister, MSGBOX_DEFAULT
	register_matchcall 1320
	release
	end

Route35_EventScript_RematchIrwin::
	trainerbattle_rematch 1320, Route35_Text_JugglerIrwinSeen, Route35_Text_JugglerIrwinBeaten
	msgbox Route35_Text_JugglerIrwinAfter, MSGBOX_AUTOCLOSE
	end

Route35_EventScript_BugCatcherArnie::
	trainerbattle_single 1196, Route35_Text_BugCatcherArnieSeen, Route35_Text_BugCatcherArnieBeaten, Route35_EventScript_RegisterArnie
	specialvar 32781, ShouldTryRematchBattle
	goto_if_eq 32781, TRUE, Route35_EventScript_RematchArnie
	msgbox Route35_Text_BugCatcherArnieAfter, MSGBOX_AUTOCLOSE
	end

Route35_EventScript_RegisterArnie::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route35_Text_ArnieRegister, MSGBOX_DEFAULT
	register_matchcall 1196
	release
	end

Route35_EventScript_RematchArnie::
	trainerbattle_rematch 1196, Route35_Text_ArnieRematchIntro, Route35_Text_ArnieRematchDefeat
	msgbox Route35_Text_ArniePostRematch, MSGBOX_AUTOCLOSE
	end

Route35_EventScript_FirebreatherWalt::
	trainerbattle_single 1317, Route35_Text_FirebreatherWaltSeen, Route35_Text_FirebreatherWaltBeaten
	msgbox Route35_Text_FirebreatherWaltAfter, MSGBOX_AUTOCLOSE
	end

Route35_EventScript_PolicemanDirk::
	trainerbattle_single 1423, Route35_Text_OfficerDirkSeen, Route35_Text_OfficerDirkBeaten
	msgbox Route35_Text_OfficerDirkAfter, MSGBOX_AUTOCLOSE
	end

Route35_EventScript_Sign1::
	lock
	msgbox Route35_Text_Sign, MSGBOX_SIGN
	closemessage
	release
	end

Route35_EventScript_Sign2::
	lock
	msgbox Route35_Text_Sign2, MSGBOX_SIGN
	closemessage
	release
	end

Route35_EventScript_Item_Payback::
	finditem 647
	end

Route35_EventScript_Item_Nugget::
	finditem ITEM_BIG_NUGGET
	end

Route35_EventScript_Item_ParalyzeHeal::
	finditem ITEM_PARALYZE_HEAL
	end

Route35_Text_CamperIvanSeen:
	.string "I'v{SE_M_REVERSAL}bee{SE_M_ATTRACT}gettin{SE_M_SANDSTORM}POKéMO{SE_M_PSYBEAM2}dat{SE_M_CHARGE}off\n"
	.string "m{SE_M_YAWN}radio{SE_M_PERISH_SONG}{SE_M_HEAL_BELL}thin{SE_M_ENCORE2}I'{SE_M_MILK_DRINK}good.$"

Route35_Text_CamperIvanBeaten:
	.string "{SE_M_HEAL_BELL}give!$"

Route35_Text_CamperIvanAfter:
	.string "Musi{SE_M_HYPER_BEAM}o{SE_M_ATTRACT}th{SE_M_REVERSAL}radi{SE_M_ATTRACT2}change{SE_M_GRASSWHISTLE}the\n"
	.string "mood{SE_M_GRASSWHISTLE}o{SE_M_ACID_ARMOR}wil{SE_M_WATERFALL}POKéMON.$"

Route35_Text_CamperElliotSeen:
	.string "I'{SE_M_MILK_DRINK}gonn{SE_M_CHARGE}sho{SE_M_TWISTER}m{SE_M_YAWN}girlfrien{SE_M_WATERFALL}I'm\n"
	.string "ho{SE_M_SPIT_UP}stuff!$"

Route35_Text_CamperElliotBeaten:
	.string "{SE_M_HEAL_BELL}wis{SE_M_TRI_ATTACK}yo{SE_M_DIVE}woul{SE_M_WATERFALL}hav{SE_M_REVERSAL}los{SE_M_SPIT_UP}fo{SE_M_SAND_TOMB}me…$"

Route35_Text_CamperElliotAfter:
	.string "{SE_M_HEAL_BELL}wa{SE_M_GRASSWHISTLE}humiliate{SE_M_WATERFALL}i{SE_M_ATTRACT}fron{SE_M_SPIT_UP}o{SE_M_ACID_ARMOR}my\n"
	.string "girlfriend…$"

Route35_Text_PicnickerBrookeSeen:
	.string "M{SE_M_YAWN}boyfriend'{SE_M_GRASSWHISTLE}weak{SE_M_SUPERSONIC}s{SE_M_ATTRACT2}{SE_M_HEAL_BELL}can'{SE_M_SPIT_UP}rely\n"
	.string "o{SE_M_ATTRACT}him.$"

Route35_Text_PicnickerBrookeBeaten:
	.string "Oh{SE_M_SUPERSONIC}my{SE_M_DRAGON_RAGE}You'r{SE_M_REVERSAL}s{SE_M_ATTRACT2}strong!$"

Route35_Text_PicnickerBrookeAfter:
	.string "{SE_M_HEAL_BELL}ca{SE_M_ATTRACT}coun{SE_M_SPIT_UP}o{SE_M_ATTRACT}m{SE_M_YAWN}POKéMO{SE_M_PSYBEAM2}mor{SE_M_REVERSAL}than\n"
	.string "m{SE_M_YAWN}boyfriend.$"

Route35_Text_PicnickerKimSeen:
	.string "Ar{SE_M_REVERSAL}yo{SE_M_DIVE}goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}th{SE_M_REVERSAL}GYM{SE_M_SING}M{SE_M_REVERSAL}too!$"

Route35_Text_PicnickerKimBeaten:
	.string "Oh{SE_M_PERISH_SONG}{SE_M_HEAL_BELL}couldn'{SE_M_SPIT_UP}win…$"

Route35_Text_PicnickerKimAfter:
	.string "Th{SE_M_REVERSAL}GY{SE_M_GIGA_DRAIN}BADGE{SE_M_SKETCH}ar{SE_M_REVERSAL}pretty{SE_M_PERISH_SONG}{SE_M_HEAL_BELL}collect\n"
	.string "them.$"

Route35_Text_BirdKeeperBryanSeen:
	.string "Wha{SE_M_SPIT_UP}kind{SE_M_GRASSWHISTLE}o{SE_M_ACID_ARMOR}BALL{SE_M_SKETCH}d{SE_M_ATTRACT2}yo{SE_M_DIVE}use?$"

Route35_Text_BirdKeeperBryanBeaten:
	.string "Yikes{SE_M_DRAGON_RAGE}No{SE_M_SPIT_UP}fas{SE_M_SPIT_UP}enough!$"

Route35_Text_BirdKeeperBryanAfter:
	.string "Som{SE_M_REVERSAL}POKéMO{SE_M_PSYBEAM2}fle{SE_M_REVERSAL}righ{SE_M_SPIT_UP}away.\p"
	.string "Tr{SE_M_YAWN}catchin{SE_M_SANDSTORM}the{SE_M_MILK_DRINK}wit{SE_M_TRI_ATTACK}KURT's\n"
	.string "FAS{SE_M_SWIFT}BALL.\p"
	.string "Wheneve{SE_M_SAND_TOMB}{SE_M_HEAL_BELL}fin{SE_M_WATERFALL}{SE_M_CHARGE}ASPEA{SE_M_MINIMIZE}BERRY{SE_M_SUPERSONIC}I\n"
	.string "tak{SE_M_REVERSAL}i{SE_M_SPIT_UP}t{SE_M_ATTRACT2}KURT.\p"
	.string "H{SE_M_REVERSAL}turn{SE_M_GRASSWHISTLE}i{SE_M_SPIT_UP}int{SE_M_ATTRACT2}{SE_M_CHARGE}custo{SE_M_MILK_DRINK}BALL.$"

Route35_Text_JugglerIrwinSeen:
	.string "Behol{SE_M_WATERFALL}m{SE_M_YAWN}gracefu{SE_M_BATON_PASS}BAL{SE_M_BRICK_BREAK}dexterity!$"

Route35_Text_JugglerIrwinBeaten:
	.string "Whew{SE_M_DRAGON_RAGE}Tha{SE_M_SPIT_UP}wa{SE_M_GRASSWHISTLE}{SE_M_CHARGE}jolt!$"

Route35_Text_JugglerIrwinAfter:
	.string "{SE_M_HEAL_BELL}wa{SE_M_GRASSWHISTLE}goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}dazzl{SE_M_REVERSAL}yo{SE_M_DIVE}wit{SE_M_TRI_ATTACK}my\n"
	.string "priz{SE_M_REVERSAL}POKéMON.\p"
	.string "Bu{SE_M_SPIT_UP}you{SE_M_SAND_TOMB}prowes{SE_M_GRASSWHISTLE}electrifie{SE_M_WATERFALL}me!$"

Route35_Text_BugCatcherArnieSeen:
	.string "I'l{SE_M_BATON_PASS}g{SE_M_ATTRACT2}anywher{SE_M_REVERSAL}i{SE_M_ACID_ARMOR}bu{SE_M_SANDSTORM}POKéMON\n"
	.string "appea{SE_M_SAND_TOMB}there.$"

Route35_Text_BugCatcherArnieBeaten:
	.string "Huh{SE_M_SING}{SE_M_HEAL_BELL}shouldn'{SE_M_SPIT_UP}hav{SE_M_REVERSAL}los{SE_M_SPIT_UP}that…$"

Route35_Text_BugCatcherArnieAfter:
	.string "M{SE_M_YAWN}VENONA{SE_M_SWIFT}wo{SE_M_ATTRACT}m{SE_M_REVERSAL}th{SE_M_REVERSAL}Bug-Catching\n"
	.string "Contes{SE_M_SPIT_UP}a{SE_M_SPIT_UP}th{SE_M_REVERSAL}NATIONA{SE_M_BRICK_BREAK}PARK.$"

Route35_Text_IrwinRegister:
	.string "{SE_M_HEAL_BELL}wa{SE_M_GRASSWHISTLE}goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}dazzl{SE_M_REVERSAL}yo{SE_M_DIVE}wit{SE_M_TRI_ATTACK}my\n"
	.string "priz{SE_M_REVERSAL}POKéMON.\p"
	.string "Bu{SE_M_SPIT_UP}you{SE_M_SAND_TOMB}prowes{SE_M_GRASSWHISTLE}electrifie{SE_M_WATERFALL}me!$"

Route35_Text_ArnieRegister:
	.string "M{SE_M_YAWN}VENONA{SE_M_SWIFT}wo{SE_M_ATTRACT}m{SE_M_REVERSAL}th{SE_M_REVERSAL}Bug-Catching\n"
	.string "Contes{SE_M_SPIT_UP}a{SE_M_SPIT_UP}th{SE_M_REVERSAL}NATIONA{SE_M_BRICK_BREAK}PARK.$"

Route35_Text_ArnieRematchIntro:
	.string "I'l{SE_M_BATON_PASS}g{SE_M_ATTRACT2}anywher{SE_M_REVERSAL}i{SE_M_ACID_ARMOR}bu{SE_M_SANDSTORM}POKéMON\n"
	.string "appea{SE_M_SAND_TOMB}there.$"

Route35_Text_ArnieRematchDefeat:
	.string "Huh{SE_M_SING}{SE_M_HEAL_BELL}shouldn'{SE_M_SPIT_UP}hav{SE_M_REVERSAL}los{SE_M_SPIT_UP}that…$"

Route35_Text_ArniePostRematch:
	.string "M{SE_M_YAWN}VENONA{SE_M_SWIFT}wo{SE_M_ATTRACT}m{SE_M_REVERSAL}th{SE_M_REVERSAL}Bug-Catching\n"
	.string "Contes{SE_M_SPIT_UP}a{SE_M_SPIT_UP}th{SE_M_REVERSAL}NATIONA{SE_M_BRICK_BREAK}PARK.$"

Route35_Text_BugCatcherArnieYanma:
	.string "Wow{SE_M_DIZZY_PUNCH}Loo{SE_M_ENCORE2}a{SE_M_SPIT_UP}al{SE_M_BATON_PASS}thos{SE_M_REVERSAL}YANMA!\p"
	.string "I'{SE_M_MILK_DRINK}s{SE_M_ATTRACT2}blow{SE_M_ATTRACT}away{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}can'{SE_M_SPIT_UP}move.$"

Route35_Text_FirebreatherWaltSeen:
	.string "I'{SE_M_MILK_DRINK}practicin{SE_M_SANDSTORM}m{SE_M_YAWN}fir{SE_M_REVERSAL}breathing.$"

Route35_Text_FirebreatherWaltBeaten:
	.string "Ow{SE_M_DRAGON_RAGE}{SE_M_HEAL_BELL}scorche{SE_M_WATERFALL}th{SE_M_REVERSAL}ti{SE_M_MORNING_SUN}o{SE_M_ACID_ARMOR}m{SE_M_YAWN}nose!$"

Route35_Text_FirebreatherWaltAfter:
	.string "Th{SE_M_REVERSAL}POKéMO{SE_M_PSYBEAM2}Marc{SE_M_TRI_ATTACK}o{SE_M_ATTRACT}th{SE_M_REVERSAL}radio\n"
	.string "lure{SE_M_GRASSWHISTLE}wil{SE_M_WATERFALL}POKéMON.$"

Route35_Text_OfficerDirkSeen:
	.string "Dange{SE_M_SAND_TOMB}lurk{SE_M_GRASSWHISTLE}i{SE_M_ATTRACT}th{SE_M_REVERSAL}night!$"

Route35_Text_OfficerDirkBeaten:
	.string "Whoops!$"

Route35_Text_OfficerDirkAfter:
	.string "Yo{SE_M_DIVE}know{SE_M_SUPERSONIC}nigh{SE_M_SPIT_UP}tim{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}fu{SE_M_ATTRACT}i{SE_M_ATTRACT}its\n"
	.string "ow{SE_M_ATTRACT}ways.\p"
	.string "Bu{SE_M_SPIT_UP}don'{SE_M_SPIT_UP}overd{SE_M_ATTRACT2}it{SE_M_SUPERSONIC}OK?$"

Route35_Text_OfficerDirkTough:
	.string "You{SE_M_SAND_TOMB}POKéMO{SE_M_PSYBEAM2}loo{SE_M_ENCORE2}prett{SE_M_YAWN}tough.\p"
	.string "Yo{SE_M_DIVE}coul{SE_M_WATERFALL}g{SE_M_ATTRACT2}anywher{SE_M_REVERSAL}safely.$"

Route35_Text_Sign:
	.string "ROUT{SE_M_SWORDS_DANCE}35$"

Route35_Text_Sign2:
	.string "NATIONA{SE_M_BRICK_BREAK}PAR{SE_M_SNORE}GATE$"

