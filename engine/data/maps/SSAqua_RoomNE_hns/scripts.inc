@ Johto (data/maps/SSAqua_RoomNE_hns/scripts.inc), as built into the FireRed game.

SSAqua_RoomNE_hns_MapScripts::
	.byte 0

SSAqua_RoomNE_EventScript_Noland::
	trainerbattle_single TRAINER_JOHTO_NOLAND_HNS, SSAqua_RoomNE_Text_HikerNolandSeen, SSAqua_RoomNE_Text_HikerNolandBeaten
	msgbox SSAqua_RoomNE_Text_HikerNolandAfterBattle, MSGBOX_AUTOCLOSE
	end

SSAqua_RoomNE_EventScript_Ethan::
	trainerbattle_single TRAINER_JOHTO_ETHAN_HNS, SSAqua_RoomNE_Text_PokemaniacEthanSeen, SSAqua_RoomNE_Text_PokemaniacEthanBeaten
	msgbox SSAqua_RoomNE_Text_PokemaniacEthanAfterBattle, MSGBOX_AUTOCLOSE
	end

SSAqua_RoomNE_Text_HikerNolandSeen:
	.string "Ar{SE_M_REVERSAL}yo{SE_M_DIVE}alone?\n"
	.string "The{SE_M_ATTRACT}let'{SE_M_GRASSWHISTLE}battle!$"

SSAqua_RoomNE_Text_HikerNolandBeaten:
	.string "That'{SE_M_GRASSWHISTLE}to{SE_M_ATTRACT2}muc{SE_M_TRI_ATTACK}t{SE_M_ATTRACT2}handle!$"

SSAqua_RoomNE_Text_HikerNolandAfterBattle:
	.string "{SE_M_HEAL_BELL}wonde{SE_M_SAND_TOMB}i{SE_M_ACID_ARMOR}ther{SE_M_REVERSAL}ar{SE_M_REVERSAL}any\n"
	.string "mountain{SE_M_GRASSWHISTLE}wort{SE_M_TRI_ATTACK}climbin{SE_M_SANDSTORM}i{SE_M_ATTRACT}KANTO?$"

SSAqua_RoomNE_Text_PokemaniacEthanSeen:
	.string "D{SE_M_ATTRACT2}yo{SE_M_DIVE}kno{SE_M_TWISTER}LILY?\n"
	.string "She'{SE_M_GRASSWHISTLE}{SE_M_CHARGE}ho{SE_M_SPIT_UP}D{SE_M_CONFUSE_RAY}i{SE_M_ATTRACT}KANTO.$"

SSAqua_RoomNE_Text_PokemaniacEthanBeaten:
	.string "Gyaaaah!$"

SSAqua_RoomNE_Text_PokemaniacEthanAfterBattle:
	.string "LILY'{SE_M_GRASSWHISTLE}nice{SE_M_SUPERSONIC}but\n"
	.string "MARY'{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}best!\n"
	.string "{SE_M_HEAL_BELL}wan{SE_M_SPIT_UP}t{SE_M_ATTRACT2}check\n"
	.string "ou{SE_M_SPIT_UP}JOHTO'{SE_M_GRASSWHISTLE}radio\n"
	.string "programs!$"

