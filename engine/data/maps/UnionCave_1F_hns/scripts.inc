@ Johto (data/maps/UnionCave_1F_hns/scripts.inc), as built into the FireRed game.

UnionCave_1F_hns_MapScripts::
	.byte 0

UnionCave_1F_Trigger_Monview::
	special SpawnCameraObject
	applymovement2 127, J_Common_Movement_WalkRight1
	waitmovement 0
	applymovement2 127, J_Common_Movement_WalkRight1
	waitmovement 0
	applymovement2 127, J_Common_Movement_WalkRight1
	waitmovement 0
	applymovement2 127, J_Common_Movement_WalkRight1
	waitmovement 0
	message Route29_Text_PressAorB
	waitbuttonpress
	closemessage
	applymovement2 127, J_Common_Movement_WalkLeft1
	waitmovement 0
	applymovement2 127, J_Common_Movement_WalkLeft1
	waitmovement 0
	applymovement2 127, J_Common_Movement_WalkLeft1
	waitmovement 0
	applymovement2 127, J_Common_Movement_WalkLeft1
	waitmovement 0
	special RemoveCameraObject
	applymovement2 255, J_Common_Movement_WalkLeft1
	waitmovement 0
	end

UnionCave_1F_EventScript_HikerRussell::
	trainerbattle_single 1283, UnionCave_1F_Text_HikerRussellSeen, UnionCave_1F_Text_HikerRussellBeaten
	msgbox UnionCave_1F_Text_HikerRussellAfter, MSGBOX_AUTOCLOSE
	end

UnionCave_1F_EventScript_PokemaniacLarry::
	trainerbattle_single 1131, UnionCave_1F_Text_PokemaniacLarrySeen, UnionCave_1F_Text_PokemaniacLarryBeaten
	msgbox UnionCave_1F_Text_PokemaniacLarryAfter, MSGBOX_AUTOCLOSE
	end

UnionCave_1F_EventScript_HikerDaniel::
	trainerbattle_single 1298, UnionCave_1F_Text_HikerDanielSeen, UnionCave_1F_Text_HikerDanielBeaten
	msgbox UnionCave_1F_Text_HikerDanielAfter, MSGBOX_AUTOCLOSE
	end

UnionCave_1F_EventScript_FirebreatherBill::
	trainerbattle_single 1316, UnionCave_1F_Text_FirebreatherBillSeen, UnionCave_1F_Text_FirebreatherBillBeaten
	msgbox UnionCave_1F_Text_FirebreatherBillAfter, MSGBOX_AUTOCLOSE
	end

UnionCave_1F_EventScript_FirebreatherRay::
	trainerbattle_single 1318, UnionCave_1F_Text_FirebreatherRaySeen, UnionCave_1F_Text_FirebreatherRayBeaten
	msgbox UnionCave_1F_Text_FirebreatherRayAfter, MSGBOX_AUTOCLOSE
	end

UnionCave_1F_EventScript_Item_Potion::
	finditem ITEM_POTION
	end

UnionCave_1F_EventScript_Item_GreatBall::
	finditem ITEM_GREAT_BALL
	end

UnionCave_1F_EventScript_Item_Xattack::
	finditem ITEM_X_ATTACK
	end

UnionCave_1F_EventScript_Item_Awakening::
	finditem ITEM_AWAKENING
	end

UnionCave_1F_Text_HikerRussellSeen:
	.string "You'r{SE_M_REVERSAL}heade{SE_M_WATERFALL}t{SE_M_ATTRACT2}AZALEA{SE_M_SUPERSONIC}ar{SE_M_REVERSAL}you?\p"
	.string "Le{SE_M_SPIT_UP}m{SE_M_YAWN}POKéMO{SE_M_PSYBEAM2}se{SE_M_REVERSAL}i{SE_M_ACID_ARMOR}yo{SE_M_DIVE}ar{SE_M_REVERSAL}good\n"
	.string "enoug{SE_M_TRI_ATTACK}t{SE_M_ATTRACT2}battle.$"

UnionCave_1F_Text_HikerRussellBeaten:
	.string "Oh{SE_M_SUPERSONIC}oh{SE_M_SUPERSONIC}oh!$"

UnionCave_1F_Text_HikerRussellAfter:
	.string "Al{SE_M_BATON_PASS}right{SE_M_SUPERSONIC}then{SE_M_DRAGON_RAGE}I'v{SE_M_REVERSAL}decided.\p"
	.string "I'{SE_M_MILK_DRINK}no{SE_M_SPIT_UP}leavin{SE_M_SANDSTORM}unti{SE_M_BATON_PASS}m{SE_M_YAWN}POKéMON\n"
	.string "ge{SE_M_SPIT_UP}tougher!$"

UnionCave_1F_Text_PokemaniacLarrySeen:
	.string "{SE_M_HEAL_BELL}roa{SE_M_MILK_DRINK}fa{SE_M_SAND_TOMB}an{SE_M_WATERFALL}wid{SE_M_REVERSAL}i{SE_M_ATTRACT}searc{SE_M_TRI_ATTACK}of\n"
	.string "POKéMON.\p"
	.string "Ar{SE_M_REVERSAL}yo{SE_M_DIVE}lookin{SE_M_SANDSTORM}fo{SE_M_SAND_TOMB}POKéMO{SE_M_PSYBEAM2}too?\p"
	.string "The{SE_M_ATTRACT}you'r{SE_M_REVERSAL}m{SE_M_YAWN}collectin{SE_M_SANDSTORM}rival!$"

UnionCave_1F_Text_PokemaniacLarryBeaten:
	.string "Ugh{SE_M_PERISH_SONG}M{SE_M_YAWN}poo{SE_M_SAND_TOMB}POKéMON…$"

UnionCave_1F_Text_PokemaniacLarryAfter:
	.string "Sometimes{SE_M_SUPERSONIC}yo{SE_M_DIVE}ca{SE_M_ATTRACT}hea{SE_M_SAND_TOMB}POKéMON\n"
	.string "roar{SE_M_GRASSWHISTLE}fro{SE_M_MILK_DRINK}dee{SE_M_MORNING_SUN}insid{SE_M_REVERSAL}th{SE_M_REVERSAL}cave.$"

UnionCave_1F_Text_HikerDanielSeen:
	.string "Whoa{SE_M_DRAGON_RAGE}Wha{SE_M_SPIT_UP}{SE_M_CHARGE}surprise!\p"
	.string "{SE_M_HEAL_BELL}didn'{SE_M_SPIT_UP}expec{SE_M_SPIT_UP}t{SE_M_ATTRACT2}se{SE_M_REVERSAL}anyon{SE_M_REVERSAL}here!$"

UnionCave_1F_Text_HikerDanielBeaten:
	.string "Whoa{SE_M_DRAGON_RAGE}I'{SE_M_MILK_DRINK}beate{SE_M_ATTRACT}bi{SE_M_SANDSTORM}time!$"

UnionCave_1F_Text_HikerDanielAfter:
	.string "{SE_M_HEAL_BELL}wa{SE_M_GRASSWHISTLE}conne{SE_M_WATERFALL}int{SE_M_ATTRACT2}buyin{SE_M_SANDSTORM}a\n"
	.string "SLOWPOKETAIL.\p"
	.string "{SE_M_HEAL_BELL}fee{SE_M_BATON_PASS}sorr{SE_M_YAWN}fo{SE_M_SAND_TOMB}th{SE_M_REVERSAL}poo{SE_M_SAND_TOMB}POKéMON.$"

UnionCave_1F_Text_FirebreatherBillSeen:
	.string "ZUBAT'{SE_M_GRASSWHISTLE}SUPERSONI{SE_M_PSYBEAM}keep{SE_M_GRASSWHISTLE}confusing\n"
	.string "m{SE_M_YAWN}POKéMON.\p"
	.string "I'{SE_M_MILK_DRINK}seriousl{SE_M_YAWN}upse{SE_M_SPIT_UP}abou{SE_M_SPIT_UP}that!$"

UnionCave_1F_Text_FirebreatherBillBeaten:
	.string "{SE_M_HEAL_BELL}flame{SE_M_WATERFALL}out!$"

UnionCave_1F_Text_FirebreatherBillAfter:
	.string "O{SE_M_ATTRACT}weekends{SE_M_SUPERSONIC}yo{SE_M_DIVE}ca{SE_M_ATTRACT}hea{SE_M_SAND_TOMB}strange\n"
	.string "roar{SE_M_GRASSWHISTLE}fro{SE_M_MILK_DRINK}dee{SE_M_MORNING_SUN}i{SE_M_ATTRACT}th{SE_M_REVERSAL}cave.$"

UnionCave_1F_Text_FirebreatherRaySeen:
	.string "I{SE_M_ACID_ARMOR}it'{SE_M_GRASSWHISTLE}light{SE_M_SUPERSONIC}{SE_M_CHARGE}cav{SE_M_REVERSAL}isn'{SE_M_SPIT_UP}scary.\p"
	.string "I{SE_M_ACID_ARMOR}you'r{SE_M_REVERSAL}strong{SE_M_SUPERSONIC}POKéMO{SE_M_PSYBEAM2}aren't\n"
	.string "scary.$"

UnionCave_1F_Text_FirebreatherRayBeaten:
	.string "FLASH!$"

UnionCave_1F_Text_FirebreatherRayAfter:
	.string "It'{SE_M_GRASSWHISTLE}m{SE_M_YAWN}POKéMON'{SE_M_GRASSWHISTLE}fir{SE_M_REVERSAL}tha{SE_M_SPIT_UP}lights\n"
	.string "u{SE_M_MORNING_SUN}thi{SE_M_GRASSWHISTLE}cave.$"

