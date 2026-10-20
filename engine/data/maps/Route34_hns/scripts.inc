@ Johto (data/maps/Route34_hns/scripts.inc), as built into the FireRed game.

Route34_hns_MapScripts::
	map_script 3, Route34_OnTransition
	map_script 5, J_SetTimeEncounters
	.byte 0

Route34_OnTransition:
	specialvar 32781, GetDaycareState
	call_if_eq 32781, 1, Route34_MapScript_EggReady
	callnative SetTimeBasedEncounters
	end

Route34_MapScript_EggReady::
	setobjectxyperm 12, 30, 34
	return

Route34_EventScript_YoungsterSamuel::
	trainerbattle_single 1035, Route34_Text_YoungsterSamuel_Seen, Route34_Text_YoungsterSamuel_Beaten
	msgbox Route34_Text_YoungsterSamuel_After, MSGBOX_AUTOCLOSE
	end

Route34_EventScript_YoungsterIan::
	trainerbattle_single 1036, Route34_Text_YoungsterIan_Seen, Route34_Text_YoungsterIan_Beaten
	msgbox Route34_Text_YoungsterIan_After, MSGBOX_AUTOCLOSE
	end

Route34_EventScript_CamperTodd::
	trainerbattle_single 1356, Route34_Text_CamperTodd_Seen, Route34_Text_CamperTodd_Beaten, Route34_EventScript_RegisterTodd
	specialvar 32781, ShouldTryRematchBattle
	goto_if_eq 32781, TRUE, Route34_EventScript_RematchTodd
	msgbox Route34_Text_CamperTodd_After, MSGBOX_AUTOCLOSE
	end

Route34_EventScript_RegisterTodd::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route34_Text_ToddRegister, MSGBOX_DEFAULT
	register_matchcall 1356
	release
	end

Route34_EventScript_RematchTodd::
	trainerbattle_rematch 1356, Route34_Text_ToddRematchIntro, Route34_Text_ToddRematchDefeat
	msgbox Route34_Text_ToddPostRematch, MSGBOX_AUTOCLOSE
	end

Route34_EventScript_PicnickerGina::
	trainerbattle_single 1343, Route34_Text_PicnickerGina_Seen, Route34_Text_PicnickerGina_Beaten, Route34_EventScript_RegisterGina
	specialvar 32781, ShouldTryRematchBattle
	goto_if_eq 32781, TRUE, Route34_EventScript_RematchGina
	msgbox Route34_Text_PicnickerGina_After, MSGBOX_AUTOCLOSE
	end

Route34_EventScript_RegisterGina::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route34_Text_GinaRegister, MSGBOX_DEFAULT
	register_matchcall 1343
	release
	end

Route34_EventScript_RematchGina::
	trainerbattle_rematch 1343, Route34_Text_PicnickerGina_Seen, Route34_Text_PicnickerGina_Beaten
	msgbox Route34_Text_PicnickerGina_After, MSGBOX_AUTOCLOSE
	end

Route34_EventScript_OfficerKeith::
	trainerbattle_single 1422, Route34_Text_OfficerKeith_Seen, Route34_Text_OfficerKeith_Win
	msgbox Route34_Text_OfficerKeith_After, MSGBOX_AUTOCLOSE
	end

Route34_EventScript_PokefanMBrandon::
	trainerbattle_single 1402, Route34_Text_PokefanBrandon_Seen, Route34_Text_PokefanBrandon_Beaten
	msgbox Route34_Text_PokefanBrandon_After, MSGBOX_AUTOCLOSE
	end

Route34_EventScript_Irene::
	trainerbattle_single 1102, Route34_Text_CooltrainerIrene_Seen, Route34_Text_CooltrainerIrene_Beaten
	msgbox Route34_Text_CooltrainerIrene_After2, MSGBOX_AUTOCLOSE
	end

Route34_EventScript_Jenn::
	trainerbattle_single 1112, Route34_Text_CooltrainerJenn_Seen, Route34_Text_CooltrainerJenn_Beaten
	msgbox Route34_Text_CooltrainerJenn_After2, MSGBOX_AUTOCLOSE
	end

Route34_EventScript_Kate::
	trainerbattle_single 1101, Route34_Text_CooltrainerKate_Seen, Route34_Text_CooltrainerKate_Beaten
	msgbox Route34_Text_CooltrainerKate_After, MSGBOX_AUTOCLOSE
	end

Route34_EventScript_Sign1::
	lock
	msgbox Route34_Text_Sign_Route34, MSGBOX_SIGN
	closemessage
	release
	end

Route34_EventScript_Sign2::
	lock
	msgbox Route34_Text_Sign_DayCare, MSGBOX_SIGN
	closemessage
	release
	end

Route34_EventScript_Sign3::
	lock
	msgbox Route34_Text_TrainerTips, MSGBOX_SIGN
	closemessage
	release
	end

Route34_EventScript_Item_SoftSand::
	finditem ITEM_SOFT_SAND
	end

Route34_EventScript_Item_RareCandy::
	finditem ITEM_RARE_CANDY
	end

Route34_EventScript_Item_Embargo::
	finditem 644
	end

Route34_Text_YoungsterSamuel_Seen:
	.string "Hey{SE_M_DRAGON_RAGE}I'{SE_M_MILK_DRINK}lookin{SE_M_SANDSTORM}fo{SE_M_SAND_TOMB}MANKEY!$"

Route34_Text_YoungsterSamuel_Beaten:
	.string "Beate{SE_M_ATTRACT}b{SE_M_YAWN}{SE_M_CHARGE}passin{SE_M_SANDSTORM}stranger!$"

Route34_Text_YoungsterSamuel_After:
	.string "I'{SE_M_MILK_DRINK}goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}trai{SE_M_ATTRACT}eve{SE_M_ATTRACT}harder.\p"
	.string "Afte{SE_M_SAND_TOMB}all{SE_M_SUPERSONIC}I'{SE_M_MILK_DRINK}tryin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}become\n"
	.string "{SE_M_CHARGE}GY{SE_M_GIGA_DRAIN}LEADER.$"

Route34_Text_YoungsterIan_Seen:
	.string "I'{SE_M_MILK_DRINK}th{SE_M_REVERSAL}bes{SE_M_SPIT_UP}i{SE_M_ATTRACT}m{SE_M_YAWN}clas{SE_M_GRASSWHISTLE}at\n"
	.string "POKéMON.$"

Route34_Text_YoungsterIan_Beaten:
	.string "No{SE_M_DRAGON_RAGE}Ther{SE_M_REVERSAL}ar{SE_M_REVERSAL}bette{SE_M_SAND_TOMB}trainers…$"

Route34_Text_YoungsterIan_After:
	.string "I'{SE_M_MILK_DRINK}tryin{SE_M_SANDSTORM}har{SE_M_WATERFALL}s{SE_M_ATTRACT2}{SE_M_HEAL_BELL}ca{SE_M_ATTRACT}b{SE_M_REVERSAL}the\n"
	.string "sta{SE_M_SAND_TOMB}i{SE_M_ATTRACT}m{SE_M_YAWN}class.$"

Route34_Text_CamperTodd_Seen:
	.string "I'{SE_M_MILK_DRINK}confiden{SE_M_SPIT_UP}i{SE_M_ATTRACT}m{SE_M_YAWN}abilit{SE_M_YAWN}to\n"
	.string "rais{SE_M_REVERSAL}POKéMON.\p"
	.string "Wan{SE_M_SPIT_UP}t{SE_M_ATTRACT2}see?$"

Route34_Text_CamperTodd_Beaten:
	.string "Di{SE_M_WATERFALL}{SE_M_HEAL_BELL}scre{SE_M_TWISTER}u{SE_M_MORNING_SUN}m{SE_M_YAWN}training?$"

Route34_Text_CamperTodd_After:
	.string "Mayb{SE_M_REVERSAL}{SE_M_HEAL_BELL}shoul{SE_M_WATERFALL}tak{SE_M_REVERSAL}on{SE_M_REVERSAL}t{SE_M_ATTRACT2}DAY-CARE,\n"
	.string "o{SE_M_SAND_TOMB}mayb{SE_M_REVERSAL}us{SE_M_REVERSAL}som{SE_M_REVERSAL}items…$"

Route34_Text_ToddRegister:
	.string "Mayb{SE_M_REVERSAL}{SE_M_HEAL_BELL}shoul{SE_M_WATERFALL}tak{SE_M_REVERSAL}on{SE_M_REVERSAL}t{SE_M_ATTRACT2}DAY-CARE,\n"
	.string "o{SE_M_SAND_TOMB}mayb{SE_M_REVERSAL}us{SE_M_REVERSAL}som{SE_M_REVERSAL}items…$"

Route34_Text_ToddRematchIntro:
	.string "I'{SE_M_MILK_DRINK}confiden{SE_M_SPIT_UP}i{SE_M_ATTRACT}m{SE_M_YAWN}abilit{SE_M_YAWN}to\n"
	.string "rais{SE_M_REVERSAL}POKéMON.\p"
	.string "Wan{SE_M_SPIT_UP}t{SE_M_ATTRACT2}see?$"

Route34_Text_ToddRematchDefeat:
	.string "Di{SE_M_WATERFALL}{SE_M_HEAL_BELL}scre{SE_M_TWISTER}u{SE_M_MORNING_SUN}m{SE_M_YAWN}training?$"

Route34_Text_ToddPostRematch:
	.string "Mayb{SE_M_REVERSAL}{SE_M_HEAL_BELL}shoul{SE_M_WATERFALL}tak{SE_M_REVERSAL}on{SE_M_REVERSAL}t{SE_M_ATTRACT2}DAY-CARE,\n"
	.string "o{SE_M_SAND_TOMB}mayb{SE_M_REVERSAL}us{SE_M_REVERSAL}som{SE_M_REVERSAL}items…$"

Route34_Text_GinaRegister:
	.string "You'r{SE_M_REVERSAL}to{SE_M_ATTRACT2}stron{SE_M_SANDSTORM}t{SE_M_ATTRACT2}b{SE_M_REVERSAL}a\n"
	.string "practic{SE_M_REVERSAL}partner.$"

Route34_Text_PicnickerGina_Seen:
	.string "Ar{SE_M_REVERSAL}yo{SE_M_DIVE}{SE_M_CHARGE}TRAINER?\p"
	.string "Let'{SE_M_GRASSWHISTLE}hav{SE_M_REVERSAL}{SE_M_CHARGE}practic{SE_M_REVERSAL}battle.$"

Route34_Text_PicnickerGina_Beaten:
	.string "Oh{SE_M_SUPERSONIC}no{SE_M_DRAGON_RAGE}{SE_M_HEAL_BELL}jus{SE_M_SPIT_UP}can'{SE_M_SPIT_UP}win…$"

Route34_Text_PicnickerGina_After:
	.string "You'r{SE_M_REVERSAL}to{SE_M_ATTRACT2}stron{SE_M_SANDSTORM}t{SE_M_ATTRACT2}b{SE_M_REVERSAL}a\n"
	.string "practic{SE_M_REVERSAL}partner.$"

Route34_Text_OfficerKeith_Seen:
	.string "Wh{SE_M_ATTRACT2}goe{SE_M_GRASSWHISTLE}there?\n"
	.string "Wha{SE_M_SPIT_UP}ar{SE_M_REVERSAL}yo{SE_M_DIVE}u{SE_M_MORNING_SUN}to?$"

Route34_Text_OfficerKeith_Win:
	.string "You'r{SE_M_REVERSAL}{SE_M_CHARGE}toug{SE_M_TRI_ATTACK}littl{SE_M_REVERSAL}kid.$"

Route34_Text_OfficerKeith_After:
	.string "Yep{SE_M_SUPERSONIC}nothin{SE_M_SANDSTORM}wron{SE_M_SANDSTORM}today.\p"
	.string "B{SE_M_REVERSAL}goo{SE_M_WATERFALL}an{SE_M_WATERFALL}sta{SE_M_YAWN}ou{SE_M_SPIT_UP}o{SE_M_ACID_ARMOR}trouble.$"

Route34_Text_OfficerKeith_Daytime:
	.string "I'{SE_M_MILK_DRINK}o{SE_M_ATTRACT}patro{SE_M_BATON_PASS}fo{SE_M_SAND_TOMB}suspicious\n"
	.string "individuals.$"

Route34_Text_PokefanBrandon_Seen:
	.string "{SE_M_HEAL_BELL}jus{SE_M_SPIT_UP}go{SE_M_SPIT_UP}m{SE_M_YAWN}POKéMO{SE_M_PSYBEAM2}bac{SE_M_ENCORE2}from\n"
	.string "DAY-CARE.\p"
	.string "Let'{SE_M_GRASSWHISTLE}se{SE_M_REVERSAL}ho{SE_M_TWISTER}muc{SE_M_TRI_ATTACK}stronge{SE_M_SAND_TOMB}i{SE_M_SPIT_UP}got!$"

Route34_Text_PokefanBrandon_Beaten:
	.string "Wh{SE_M_YAWN}doe{SE_M_GRASSWHISTLE}i{SE_M_SPIT_UP}en{SE_M_WATERFALL}thi{SE_M_GRASSWHISTLE}way?$"

Route34_Text_PokefanBrandon_After:
	.string "M{SE_M_YAWN}POKéMO{SE_M_PSYBEAM2}cam{SE_M_REVERSAL}bac{SE_M_ENCORE2}wit{SE_M_TRI_ATTACK}ne{SE_M_TWISTER}moves.\p"
	.string "Tha{SE_M_SPIT_UP}confounde{SE_M_WATERFALL}m{SE_M_REVERSAL}t{SE_M_ATTRACT2}n{SE_M_ATTRACT2}end!$"

Route34_Text_Sign_IlexForest:
	.string "ILE{SE_M_LOCK_ON}FOREST\n"
	.string "THROUG{SE_M_SWAGGER2}TH{SE_M_SWORDS_DANCE}GATE$"

Route34_Text_Sign_Route34:
	.string "ROUT{SE_M_SWORDS_DANCE}34\n"
	.string "GOLDENRO{SE_M_FAINT_ATTACK}CIT{SE_M_MOONLIGHT}{SE_M_PAY_DAY}AZALE{SE_M_BONEMERANG}TOWN\p"
	.string "ILE{SE_M_LOCK_ON}FORES{SE_M_SWIFT}SOMEWHER{SE_M_SWORDS_DANCE}BETWEEN$"

Route34_Text_TrainerTips:
	.string "TRAINE{SE_M_MINIMIZE}TIPS\p"
	.string "BERR{SE_M_MOONLIGHT}tree{SE_M_GRASSWHISTLE}gro{SE_M_TWISTER}ne{SE_M_TWISTER}BERRIES\n"
	.string "severa{SE_M_BATON_PASS}time{SE_M_GRASSWHISTLE}{SE_M_CHARGE}day.\p"
	.string "Not{SE_M_REVERSAL}whic{SE_M_TRI_ATTACK}tree{SE_M_GRASSWHISTLE}bea{SE_M_SAND_TOMB}which\n"
	.string "BERRIES.$"

Route34_Text_CooltrainerIrene_Seen:
	.string "IRENE{SE_M_HEAT_WAVE}Wh{SE_M_ATTRACT2}ar{SE_M_REVERSAL}you?!$"

Route34_Text_CooltrainerIrene_Beaten:
	.string "IRENE{SE_M_HEAT_WAVE}Ohhh{SE_M_DRAGON_RAGE}You'r{SE_M_REVERSAL}to{SE_M_ATTRACT2}strong!$"

Route34_Text_CooltrainerIrene_After1:
	.string "IRENE{SE_M_HEAT_WAVE}M{SE_M_YAWN}siste{SE_M_SAND_TOMB}KAT{SE_M_SWORDS_DANCE}wil{SE_M_BATON_PASS}ge{SE_M_SPIT_UP}you\n"
	.string "fo{SE_M_SAND_TOMB}this!$"

Route34_Text_CooltrainerIrene_After2:
	.string "IRENE{SE_M_HEAT_WAVE}Isn'{SE_M_SPIT_UP}thi{SE_M_GRASSWHISTLE}beac{SE_M_TRI_ATTACK}great?\p"
	.string "It'{SE_M_GRASSWHISTLE}ou{SE_M_SAND_TOMB}secre{SE_M_SPIT_UP}littl{SE_M_REVERSAL}getaway!$"

Route34_Text_CooltrainerJenn_Seen:
	.string "JENN{SE_M_HEAT_WAVE}Wha{SE_M_SPIT_UP}the...?\n"
	.string "Wha{SE_M_SPIT_UP}ar{SE_M_REVERSAL}yo{SE_M_DIVE}doing?$"

Route34_Text_CooltrainerJenn_Beaten:
	.string "JENN{SE_M_HEAT_WAVE}S{SE_M_ATTRACT2}sorry{SE_M_SUPERSONIC}IRENE{SE_M_DRAGON_RAGE}Dea{SE_M_SAND_TOMB}Sis!$"

Route34_Text_CooltrainerJenn_After1:
	.string "JENN{SE_M_HEAT_WAVE}Don'{SE_M_SPIT_UP}ge{SE_M_SPIT_UP}cocky{SE_M_DRAGON_RAGE}M{SE_M_YAWN}sister\n"
	.string "KAT{SE_M_SWORDS_DANCE}i{SE_M_GRASSWHISTLE}tough!$"

Route34_Text_CooltrainerJenn_After2:
	.string "JENN{SE_M_HEAT_WAVE}Sunligh{SE_M_SPIT_UP}make{SE_M_GRASSWHISTLE}you{SE_M_SAND_TOMB}body\n"
	.string "stronger.$"

Route34_Text_CooltrainerKate_Seen:
	.string "KATE{SE_M_HEAT_WAVE}{SE_M_HEAL_BELL}mus{SE_M_SPIT_UP}pa{SE_M_YAWN}yo{SE_M_DIVE}bac{SE_M_ENCORE2}for\n"
	.string "takin{SE_M_SANDSTORM}car{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}m{SE_M_YAWN}sisters!$"

Route34_Text_CooltrainerKate_Beaten:
	.string "KATE{SE_M_HEAT_WAVE}No{SE_M_DRAGON_RAGE}{SE_M_HEAL_BELL}can'{SE_M_SPIT_UP}believ{SE_M_REVERSAL}{SE_M_HEAL_BELL}lost.$"

Route34_Text_CooltrainerKate_GiveSoftSand:
	.string "KATE{SE_M_HEAT_WAVE}Yo{SE_M_DIVE}ar{SE_M_REVERSAL}s{SE_M_ATTRACT2}strong.\n"
	.string "W{SE_M_REVERSAL}los{SE_M_SPIT_UP}wit{SE_M_TRI_ATTACK}n{SE_M_ATTRACT2}excuses...\p"
	.string "Here{SE_M_SUPERSONIC}tak{SE_M_REVERSAL}this!$"

Route34_Text_CooltrainerKate_After:
	.string "KATE{SE_M_HEAT_WAVE}I'{SE_M_MILK_DRINK}sorr{SE_M_YAWN}w{SE_M_REVERSAL}jumpe{SE_M_WATERFALL}you.\p"
	.string "W{SE_M_REVERSAL}neve{SE_M_SAND_TOMB}expecte{SE_M_WATERFALL}anyon{SE_M_REVERSAL}t{SE_M_ATTRACT2}find\n"
	.string "u{SE_M_GRASSWHISTLE}here{SE_M_PERISH_SONG}Yo{SE_M_DIVE}sur{SE_M_REVERSAL}startle{SE_M_WATERFALL}us.$"

Route34_Text_Sign_DayCare:
	.string "DAY-CARE\p"
	.string "LE{SE_M_SWIFT}U{SE_M_SKETCH}RAIS{SE_M_SWORDS_DANCE}YOU{SE_M_MINIMIZE}POKéMO{SE_M_PSYBEAM2}FO{SE_M_MINIMIZE}YOU!$"

