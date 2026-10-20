@ Johto (data/maps/MtMortar_1F_North_hns/scripts.inc), as built into the FireRed game.

MtMortar_1F_North_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MtMortar_1F_North_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, J_SetTimeEncounters
	.byte 0

MtMortar_1F_North_OnTransition:
	callnative SetTimeBasedEncounters
	end

MtMortar_1F_North_EventScript_Item_MaxRepel::
	finditem ITEM_MAX_REPEL
	end

MtMortar_1F_North_EventScript_Item_EscapeRope::
	finditem ITEM_ESCAPE_ROPE
	end

MtMortar_1F_North_EventScript_Item_MaxPotion::
	finditem ITEM_MAX_POTION
	end

MtMortar_1F_North_EventScript_Item_Protector::
	finditem ITEM_PROTECTOR
	end

MtMortar_1F_North_EventScript_Item_UltraBall::
	finditem ITEM_ULTRA_BALL
	end

MtMortar_1F_North_EventScript_Item_FullIncense::
	finditem ITEM_REVIVE
	end

MtMortar_1F_North_EventScript_Item_KingsRock::
	finditem ITEM_KINGS_ROCK
	end

MtMortar_1F_North_EventScript_Miller::
	trainerbattle_single TRAINER_JOHTO_MILLER_HNS, MountMortar2_Text_PokemaniacMillerSeen, MountMortar2_Text_PokemaniacMillerBeaten
	msgbox MountMortar2_Text_PokemaniacMillerAfter, MSGBOX_AUTOCLOSE
	end

MtMortar_1F_North_EventScript_Markus::
	trainerbattle_single TRAINER_JOHTO_MARKUS_HNS, MountMortar2_Text_SupernerdMarkusSeen, MountMortar2_Text_SupernerdMarkusBeaten
	msgbox MountMortar2_Text_SupernerdMarkusAfter, MSGBOX_AUTOCLOSE
	end

MountMortar2_Text_PokemaniacMillerSeen:
	.string "I'{SE_M_MILK_DRINK}no{SE_M_SPIT_UP}losin{SE_M_SANDSTORM}thi{SE_M_GRASSWHISTLE}time!$"

MountMortar2_Text_PokemaniacMillerBeaten:
	.string "{SE_M_HEAL_BELL}los{SE_M_SPIT_UP}t{SE_M_ATTRACT2}som{SE_M_REVERSAL}kid...?$"

MountMortar2_Text_PokemaniacMillerAfter:
	.string "{SE_M_BONEMERANG}whil{SE_M_REVERSAL}back{SE_M_SUPERSONIC}thi{SE_M_GRASSWHISTLE}karat{SE_M_REVERSAL}dude\n"
	.string "wante{SE_M_WATERFALL}t{SE_M_ATTRACT2}battle.\p"
	.string "H{SE_M_REVERSAL}wa{SE_M_GRASSWHISTLE}ridiculousl{SE_M_YAWN}good.\n"
	.string "H{SE_M_REVERSAL}jus{SE_M_SPIT_UP}thrashe{SE_M_WATERFALL}u{SE_M_GRASSWHISTLE}silly.\p"
	.string "H{SE_M_REVERSAL}wen{SE_M_SPIT_UP}i{SE_M_ATTRACT}deepe{SE_M_SAND_TOMB}sayin{SE_M_SANDSTORM}it\n"
	.string "wa{SE_M_GRASSWHISTLE}fo{SE_M_SAND_TOMB}hi{SE_M_GRASSWHISTLE}training.\p"
	.string "{SE_M_HEAL_BELL}wonde{SE_M_SAND_TOMB}ho{SE_M_TWISTER}h{SE_M_REVERSAL}is?$"

MountMortar2_Text_SupernerdMarkusSeen:
	.string "Hey{SE_M_DRAGON_RAGE}HUGH!$"

MountMortar2_Text_SupernerdMarkusBeaten:
	.string "{SE_M_HEAL_BELL}mistoo{SE_M_ENCORE2}yo{SE_M_DIVE}fo{SE_M_SAND_TOMB}someone\n"
	.string "else…$"

MountMortar2_Text_SupernerdMarkusAfter:
	.string "{SE_M_HEAL_BELL}cam{SE_M_REVERSAL}t{SE_M_ATTRACT2}explor{SE_M_REVERSAL}MT.MORTAR,\n"
	.string "bu{SE_M_SPIT_UP}{SE_M_HEAL_BELL}go{SE_M_SPIT_UP}separate{SE_M_WATERFALL}fro{SE_M_MILK_DRINK}my\l"
	.string "partner…\p"
	.string "Di{SE_M_WATERFALL}yo{SE_M_DIVE}ru{SE_M_ATTRACT}int{SE_M_ATTRACT2}{SE_M_CHARGE}trainer\n"
	.string "wh{SE_M_ATTRACT2}use{SE_M_GRASSWHISTLE}{SE_M_CHARGE}SEADR{SE_M_BONEMERANG}tha{SE_M_SPIT_UP}knows\l"
	.string "WATERFALL?$"

