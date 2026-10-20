@ Johto (data/maps/Route45_hns/scripts.inc), as built into the FireRed game.

Route45_hns_MapScripts::
	.byte 0

Route45_EventScript_Erik::
	trainerbattle_single 1287, Route45_Text_HikerErikSeen, Route45_Text_HikerErikBeaten
	msgbox Route45_Text_HikerErikAfter, MSGBOX_AUTOCLOSE
	end

Route45_EventScript_Michael::
	trainerbattle_single 1288, Route45_Text_HikerMichaelSeen, Route45_Text_HikerMichaelBeaten
	msgbox Route45_Text_HikerMichaelAfter, MSGBOX_AUTOCLOSE
	end

Route45_EventScript_Parry::
	trainerbattle_single 1289, Route45_Text_HikerParrySeen, Route45_Text_HikerParryBeaten, Route45_EventScript_RegisterParry
	specialvar 32781, ShouldTryRematchBattle
	goto_if_eq 32781, TRUE, Route45_EventScript_RematchParry
	msgbox Route45_Text_HikerParryAfter, MSGBOX_AUTOCLOSE
	end

Route45_EventScript_RegisterParry::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route45_Text_ParryRegister, MSGBOX_DEFAULT
	register_matchcall 1289
	release
	end

Route45_EventScript_RematchParry::
	trainerbattle_rematch 1289, Route45_Text_ParryRematchIntro, Route45_Text_ParryRematchDefeat
	msgbox Route45_Text_ParryPostRematch, MSGBOX_AUTOCLOSE
	end

Route45_EventScript_Timothy::
	trainerbattle_single 1290, Route45_Text_HikerTimothySeen, Route45_Text_HikerTimothyBeaten
	msgbox Route45_Text_HikerTimothyAfter, MSGBOX_AUTOCLOSE
	end

Route45_EventScript_Kenji::
	trainerbattle_single 1323, Route45_Text_BlackbeltKenjiSeen, Route45_Text_BlackbeltKenjiBeaten, Route45_EventScript_RegisterKenji
	goto_if_set 8946, Route45_EventScript_KenjiGiveItem
	specialvar 32781, ShouldTryRematchBattle
	goto_if_eq 32781, TRUE, Route45_EventScript_RematchKenji
	msgbox Route45_Text_BlackbeltKenjiAfter, MSGBOX_AUTOCLOSE
	end

Route45_EventScript_RegisterKenji::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route45_Text_KenjiRegister, MSGBOX_DEFAULT
	register_matchcall 1323
	release
	end

Route45_EventScript_RematchKenji::
	trainerbattle_rematch 1323, Route45_Text_KenjiRematchIntro, Route45_Text_KenjiRematchDefeat
	msgbox Route45_Text_KenjiPostRematch, MSGBOX_AUTOCLOSE
	end

Route45_EventScript_KenjiGiveItem::
	msgbox Route45_Text_KenjiHasItem, MSGBOX_DEFAULT
	giveitem 20624
	goto_if_eq 32781, FALSE, Route45_EventScript_KenjiNoRoom
	clearflag 8946
	msgbox Route45_Text_KenjiGaveItem, MSGBOX_AUTOCLOSE
	end

Route45_EventScript_KenjiNoRoom::
	msgbox Route45_Text_KenjiNoRoom, MSGBOX_AUTOCLOSE
	end

Route45_EventScript_Ryan::
	trainerbattle_single 1085, Route45_Text_CooltrainermRyanSeen, Route45_Text_CooltrainermRyanBeaten
	msgbox Route45_Text_CooltrainermRyanAfter, MSGBOX_AUTOCLOSE
	end

Route45_EventScript_Kelly::
	trainerbattle_single 1103, Route45_Text_CooltrainerfKellySeen, Route45_Text_CooltrainerfKellyBeaten
	msgbox Route45_Text_CooltrainerfKellyAfter, MSGBOX_AUTOCLOSE
	end

Route45_EventScript_Quentin::
	trainerbattle_single 1373, Route45_Text_CamperQuentinSeen, Route45_Text_CamperQuentinBeaten
	msgbox Route45_Text_CamperQuentinAfter, MSGBOX_AUTOCLOSE
	end

Route45_EventScript_Sign::
	msgbox Route45_Text_Sign, MSGBOX_SIGN
	end

Route45_EventScript_Item_Elixir::
	finditem ITEM_ELIXIR
	end

Route45_EventScript_Item_Max_Potion::
	finditem ITEM_MAX_POTION
	end

Route45_EventScript_Item_Full_Heal::
	finditem ITEM_FULL_HEAL
	end

Route45_EventScript_Item_Nugget::
	finditem ITEM_NUGGET
	end

Route45_Text_HikerErikSeen:
	.string "B{SE_M_REVERSAL}prepare{SE_M_WATERFALL}fo{SE_M_SAND_TOMB}anything!\p"
	.string "Le{SE_M_SPIT_UP}m{SE_M_REVERSAL}se{SE_M_REVERSAL}i{SE_M_ACID_ARMOR}you{SE_M_SAND_TOMB}POKéMO{SE_M_PSYBEAM2}have\n"
	.string "bee{SE_M_ATTRACT}raise{SE_M_WATERFALL}properly!$"

Route45_Text_HikerErikBeaten:
	.string "Oh{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}los{SE_M_SPIT_UP}that!$"

Route45_Text_HikerErikAfter:
	.string "I'l{SE_M_BATON_PASS}hea{SE_M_WATERFALL}bac{SE_M_ENCORE2}t{SE_M_ATTRACT2}BLACKTHORN's\n"
	.string "IC{SE_M_SWORDS_DANCE}PAT{SE_M_SWAGGER2}an{SE_M_WATERFALL}trai{SE_M_ATTRACT}som{SE_M_REVERSAL}more.$"

Route45_Text_HikerMichaelSeen:
	.string "Yo{SE_M_DRAGON_RAGE}You'r{SE_M_REVERSAL}spunky{SE_M_DRAGON_RAGE}Bu{SE_M_SPIT_UP}yo{SE_M_DIVE}know\n"
	.string "what?\p"
	.string "Whe{SE_M_ATTRACT}i{SE_M_SPIT_UP}come{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}sheer\n"
	.string "spunkiness{SE_M_SUPERSONIC}I'{SE_M_MILK_DRINK}th{SE_M_REVERSAL}man!$"

Route45_Text_HikerMichaelBeaten:
	.string "M{SE_M_YAWN}POKéMO{SE_M_PSYBEAM2}weren'{SE_M_SPIT_UP}spunk{SE_M_YAWN}enough!$"

Route45_Text_HikerMichaelAfter:
	.string "Boy{SE_M_SUPERSONIC}d{SE_M_ATTRACT2}{SE_M_HEAL_BELL}lov{SE_M_REVERSAL}H{SE_M_PETAL_DANCE}UP{SE_M_DRAGON_RAGE}Mmmm{SE_M_SUPERSONIC}yum!\p"
	.string "{SE_M_HEAL_BELL}kee{SE_M_MORNING_SUN}drinkin{SE_M_SANDSTORM}m{SE_M_YAWN}POKéMON's!\p"
	.string "{SE_M_HEAL_BELL}can'{SE_M_SPIT_UP}hel{SE_M_MORNING_SUN}it!$"

Route45_Text_HikerParrySeen:
	.string "M{SE_M_YAWN}POKéMO{SE_M_PSYBEAM2}ar{SE_M_REVERSAL}powe{SE_M_SAND_TOMB}packed!$"

Route45_Text_HikerParryBeaten:
	.string "Wahahah{SE_M_DRAGON_RAGE}I'{SE_M_MILK_DRINK}th{SE_M_REVERSAL}bi{SE_M_SANDSTORM}loser!$"

Route45_Text_HikerParryAfter:
	.string "I'{SE_M_MILK_DRINK}no{SE_M_SPIT_UP}muc{SE_M_TRI_ATTACK}goo{SE_M_WATERFALL}a{SE_M_SPIT_UP}thinking,\n"
	.string "see?\p"
	.string "So{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}jus{SE_M_SPIT_UP}plo{SE_M_TWISTER}ahea{SE_M_WATERFALL}wit{SE_M_TRI_ATTACK}power!$"

Route45_Text_ParryRegister:
	.string "I'{SE_M_MILK_DRINK}no{SE_M_SPIT_UP}muc{SE_M_TRI_ATTACK}goo{SE_M_WATERFALL}a{SE_M_SPIT_UP}thinking,\n"
	.string "see?\p"
	.string "So{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}jus{SE_M_SPIT_UP}plo{SE_M_TWISTER}ahea{SE_M_WATERFALL}wit{SE_M_TRI_ATTACK}power!$"

Route45_Text_ParryRematchIntro:
	.string "M{SE_M_YAWN}POKéMO{SE_M_PSYBEAM2}ar{SE_M_REVERSAL}powe{SE_M_SAND_TOMB}packed!$"

Route45_Text_ParryRematchDefeat:
	.string "Wahahah{SE_M_DRAGON_RAGE}I'{SE_M_MILK_DRINK}th{SE_M_REVERSAL}bi{SE_M_SANDSTORM}loser!$"

Route45_Text_ParryPostRematch:
	.string "I'{SE_M_MILK_DRINK}no{SE_M_SPIT_UP}muc{SE_M_TRI_ATTACK}goo{SE_M_WATERFALL}a{SE_M_SPIT_UP}thinking,\n"
	.string "see?\p"
	.string "So{SE_M_SUPERSONIC}{SE_M_HEAL_BELL}jus{SE_M_SPIT_UP}plo{SE_M_TWISTER}ahea{SE_M_WATERFALL}wit{SE_M_TRI_ATTACK}power!$"

Route45_Text_HikerTimothySeen:
	.string "Wh{SE_M_YAWN}d{SE_M_ATTRACT2}{SE_M_HEAL_BELL}clim{SE_M_STRENGTH}mountains?\p"
	.string "Becaus{SE_M_REVERSAL}they'r{SE_M_REVERSAL}there.\p"
	.string "Wh{SE_M_YAWN}d{SE_M_ATTRACT2}{SE_M_HEAL_BELL}trai{SE_M_ATTRACT}POKéMON?\p"
	.string "Becaus{SE_M_REVERSAL}they'r{SE_M_REVERSAL}there!$"

Route45_Text_HikerTimothyBeaten:
	.string "Losses{SE_M_DIZZY_PUNCH}They'r{SE_M_REVERSAL}ther{SE_M_REVERSAL}too!$"

Route45_Text_HikerTimothyAfter:
	.string "Th{SE_M_REVERSAL}bes{SE_M_SPIT_UP}thin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}eve{SE_M_SAND_TOMB}happe{SE_M_ATTRACT}to\n"
	.string "m{SE_M_REVERSAL}wa{SE_M_GRASSWHISTLE}discoverin{SE_M_SANDSTORM}POKéMON.$"

Route45_Text_HikerParryGivesIron:
	.string "{SE_M_HEAL_BELL}jus{SE_M_SPIT_UP}can'{SE_M_SPIT_UP}fin{SE_M_WATERFALL}{SE_M_CHARGE}wa{SE_M_YAWN}t{SE_M_ATTRACT2}win!\p"
	.string "Kee{SE_M_MORNING_SUN}i{SE_M_SPIT_UP}up!\p"
	.string "Oh{SE_M_SUPERSONIC}an{SE_M_WATERFALL}tak{SE_M_REVERSAL}thi{SE_M_GRASSWHISTLE}-{SE_M_PAY_DAY}it'{SE_M_GRASSWHISTLE}the\n"
	.string "gif{SE_M_SPIT_UP}yo{SE_M_DIVE}couldn'{SE_M_SPIT_UP}tak{SE_M_REVERSAL}whe{SE_M_ATTRACT}we\n"
	.string "las{SE_M_SPIT_UP}met.$"

Route45_Text_BlackbeltKenjiSeen:
	.string "{SE_M_HEAL_BELL}wa{SE_M_GRASSWHISTLE}trainin{SE_M_SANDSTORM}her{SE_M_REVERSAL}alone.\p"
	.string "Behol{SE_M_WATERFALL}th{SE_M_REVERSAL}fruit{SE_M_GRASSWHISTLE}o{SE_M_ACID_ARMOR}m{SE_M_YAWN}labor!$"

Route45_Text_BlackbeltKenjiBeaten:
	.string "Waaaargh!$"

Route45_Text_BlackbeltKenjiAfter:
	.string "Thi{SE_M_GRASSWHISTLE}call{SE_M_GRASSWHISTLE}fo{SE_M_SAND_TOMB}extrem{SE_M_REVERSAL}measures.\p"
	.string "{SE_M_HEAL_BELL}mus{SE_M_SPIT_UP}tak{SE_M_REVERSAL}t{SE_M_ATTRACT2}th{SE_M_REVERSAL}hill{SE_M_GRASSWHISTLE}an{SE_M_WATERFALL}train\n"
	.string "i{SE_M_ATTRACT}solitude.$"

Route45_Text_KenjiRegister:
	.string "Thi{SE_M_GRASSWHISTLE}call{SE_M_GRASSWHISTLE}fo{SE_M_SAND_TOMB}extrem{SE_M_REVERSAL}measures.\p"
	.string "{SE_M_HEAL_BELL}mus{SE_M_SPIT_UP}tak{SE_M_REVERSAL}t{SE_M_ATTRACT2}th{SE_M_REVERSAL}hill{SE_M_GRASSWHISTLE}an{SE_M_WATERFALL}train\n"
	.string "i{SE_M_ATTRACT}solitude.$"

Route45_Text_KenjiRematchIntro:
	.string "{SE_M_HEAL_BELL}wa{SE_M_GRASSWHISTLE}trainin{SE_M_SANDSTORM}her{SE_M_REVERSAL}alone.\p"
	.string "Behol{SE_M_WATERFALL}th{SE_M_REVERSAL}fruit{SE_M_GRASSWHISTLE}o{SE_M_ACID_ARMOR}m{SE_M_YAWN}labor!$"

Route45_Text_KenjiRematchDefeat:
	.string "Waaaargh!$"

Route45_Text_KenjiPostRematch:
	.string "Thi{SE_M_GRASSWHISTLE}call{SE_M_GRASSWHISTLE}fo{SE_M_SAND_TOMB}extrem{SE_M_REVERSAL}measures.\p"
	.string "{SE_M_HEAL_BELL}mus{SE_M_SPIT_UP}tak{SE_M_REVERSAL}t{SE_M_ATTRACT2}th{SE_M_REVERSAL}hill{SE_M_GRASSWHISTLE}an{SE_M_WATERFALL}train\n"
	.string "i{SE_M_ATTRACT}solitude.$"

Route45_Text_KenjiHasItem:
	.string "Hey{SE_M_DRAGON_RAGE}I'{SE_M_MILK_DRINK}takin{SE_M_SANDSTORM}{SE_M_CHARGE}brea{SE_M_ENCORE2}from\n"
	.string "training.\p"
	.string "{SE_M_HEAL_BELL}foun{SE_M_WATERFALL}somethin{SE_M_SANDSTORM}goo{SE_M_WATERFALL}whil{SE_M_REVERSAL}I\n"
	.string "wa{SE_M_GRASSWHISTLE}out{SE_M_PERISH_SONG}Here{SE_M_SUPERSONIC}tak{SE_M_REVERSAL}it!$"

Route45_Text_KenjiGaveItem:
	.string "Us{SE_M_REVERSAL}i{SE_M_SPIT_UP}well!\p"
	.string "{SE_M_HEAL_BELL}nee{SE_M_WATERFALL}t{SE_M_ATTRACT2}ge{SE_M_SPIT_UP}bac{SE_M_ENCORE2}t{SE_M_ATTRACT2}my\n"
	.string "training{SE_M_PERISH_SONG}Oooooaaarrrgh!$"

Route45_Text_KenjiNoRoom:
	.string "Hmm{SE_M_SUPERSONIC}you{SE_M_SAND_TOMB}BA{SE_M_SWAGGER}i{SE_M_GRASSWHISTLE}full.\p"
	.string "Com{SE_M_REVERSAL}bac{SE_M_ENCORE2}whe{SE_M_ATTRACT}yo{SE_M_DIVE}hav{SE_M_REVERSAL}room.$"

Route45_Text_BlackbeltKenjiMorning:
	.string "I'{SE_M_MILK_DRINK}goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}trai{SE_M_ATTRACT}{SE_M_CHARGE}bi{SE_M_SPIT_UP}more\n"
	.string "befor{SE_M_REVERSAL}{SE_M_HEAL_BELL}brea{SE_M_ENCORE2}fo{SE_M_SAND_TOMB}lunch.$"

Route45_Text_BlackbeltKenjiNight:
	.string "W{SE_M_REVERSAL}ha{SE_M_WATERFALL}plent{SE_M_YAWN}o{SE_M_ACID_ARMOR}res{SE_M_SPIT_UP}a{SE_M_SPIT_UP}lunch{SE_M_SUPERSONIC}so\p"
	.string "no{SE_M_TWISTER}we'r{SE_M_REVERSAL}al{SE_M_BATON_PASS}read{SE_M_YAWN}t{SE_M_ATTRACT2}g{SE_M_ATTRACT2}again!\p"
	.string "We'r{SE_M_REVERSAL}goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}trai{SE_M_ATTRACT}again!$"

Route45_Text_CooltrainermRyanSeen:
	.string "Wha{SE_M_SPIT_UP}ar{SE_M_REVERSAL}you{SE_M_SAND_TOMB}thought{SE_M_GRASSWHISTLE}on\n"
	.string "raisin{SE_M_SANDSTORM}POKéMON?$"

Route45_Text_CooltrainermRyanBeaten:
	.string "You'v{SE_M_REVERSAL}wo{SE_M_ATTRACT}m{SE_M_YAWN}respect.$"

Route45_Text_CooltrainermRyanAfter:
	.string "{SE_M_HEAL_BELL}se{SE_M_REVERSAL}you'r{SE_M_REVERSAL}raisin{SE_M_SANDSTORM}you{SE_M_SAND_TOMB}POKéMON\n"
	.string "wit{SE_M_TRI_ATTACK}care.\p"
	.string "Th{SE_M_REVERSAL}bon{SE_M_WATERFALL}yo{SE_M_DIVE}buil{SE_M_WATERFALL}wil{SE_M_BATON_PASS}sav{SE_M_REVERSAL}you\n"
	.string "i{SE_M_ATTRACT}toug{SE_M_TRI_ATTACK}situations.$"

Route45_Text_CooltrainerfKellySeen:
	.string "Wha{SE_M_SPIT_UP}i{SE_M_GRASSWHISTLE}you{SE_M_SAND_TOMB}battl{SE_M_REVERSAL}strategy?\p"
	.string "I{SE_M_SPIT_UP}i{SE_M_GRASSWHISTLE}foolis{SE_M_TRI_ATTACK}t{SE_M_ATTRACT2}us{SE_M_REVERSAL}stron{SE_M_SANDSTORM}moves\n"
	.string "indiscriminately.$"

Route45_Text_CooltrainerfKellyBeaten:
	.string "Fine{SE_M_PERISH_SONG}{SE_M_HEAL_BELL}lost.$"

Route45_Text_CooltrainerfKellyAfter:
	.string "I'{SE_M_MILK_DRINK}no{SE_M_SPIT_UP}i{SE_M_ATTRACT}favo{SE_M_SAND_TOMB}o{SE_M_ACID_ARMOR}overly\n"
	.string "powerfu{SE_M_BATON_PASS}moves.\p"
	.string "{SE_M_HEAL_BELL}wan{SE_M_SPIT_UP}t{SE_M_ATTRACT2}win{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}{SE_M_HEAL_BELL}als{SE_M_ATTRACT2}don't\n"
	.string "wan{SE_M_SPIT_UP}t{SE_M_ATTRACT2}har{SE_M_MILK_DRINK}POKéMON.$"

Route45_Text_CamperQuentinSeen:
	.string "I'{SE_M_MILK_DRINK}really{SE_M_SUPERSONIC}reall{SE_M_YAWN}tough!$"

Route45_Text_CamperQuentinBeaten:
	.string "{SE_M_HEAL_BELL}wa{SE_M_GRASSWHISTLE}toug{SE_M_TRI_ATTACK}a{SE_M_SPIT_UP}th{SE_M_REVERSAL}TRAINE{SE_M_MINIMIZE}HILL…$"

Route45_Text_CamperQuentinAfter:
	.string "Hav{SE_M_REVERSAL}yo{SE_M_DIVE}bee{SE_M_ATTRACT}t{SE_M_ATTRACT2}th{SE_M_REVERSAL}TRAINE{SE_M_MINIMIZE}HILL?\p"
	.string "{SE_M_HEAL_BELL}never{SE_M_SUPERSONIC}eve{SE_M_SAND_TOMB}los{SE_M_REVERSAL}there{SE_M_SUPERSONIC}but…$"

Route45_Text_Sign:
	.string "ROUT{SE_M_SWORDS_DANCE}45\n"
	.string "MOUNTAI{SE_M_PSYBEAM2}RD{SE_M_PERISH_SONG}AHEAD$"

