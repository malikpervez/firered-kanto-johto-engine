@ Johto (data/scripts/berry_tree.inc), as built into the FireRed game.

J_BerryTreeScript::
	special ObjectEventInteractionGetBerryTreeData
	switch VAR_0x8004
	case BERRY_STAGE_SPARKLING, J_BerryTree_EventScript_Hns_NotRipe
	case BERRY_STAGE_NO_BERRY, J_BerryTree_EventScript_Hns_NotRipe
	case BERRY_STAGE_PLANTED, J_BerryTree_EventScript_Hns_NotRipe
	case BERRY_STAGE_SPROUTED, J_BerryTree_EventScript_Hns_NotRipe
	case BERRY_STAGE_TALLER, J_BerryTree_EventScript_Hns_NotRipe
	case 4, J_BerryTree_EventScript_Hns_NotRipe
	case 5, J_BerryTree_EventScript_Hns_FullyGrown
	end

J_BerryTree_EventScript_Hns_NotRipe::
	lock
	message J_BerryTree_Text_Hns_NotRipe
	waitmessage
	waitbuttonpress
	release
	end

J_BerryTree_EventScript_Hns_FullyGrown::
	buffernumberstring STR_VAR_2, VAR_0x8006
	lock
	faceplayer
	goto J_BerryTree_EventScript_Hns_PickBerry

J_BerryTree_EventScript_Hns_PickBerry::
	special ObjectEventInteractionPickBerryTree
	goto_if_eq VAR_0x8004, 0, J_BerryTree_EventScript_Hns_BagFull
	special IncrementDailyPickedBerries
	special ObjectEventInteractionRemoveBerryTree
	message J_BerryTree_Text_Hns_Picked
	playfanfare MUS_OBTAIN_BERRY
	special ObjectEventInteractionPlantBerryTree
	incrementgamestat GAME_STAT_PLANTED_BERRIES
	special IncrementDailyPlantedBerries
	waitmessage
	waitfanfare
	release
	end

J_BerryTree_EventScript_Hns_BagFull::
	message J_BerryTree_Text_Hns_BagFull
	waitmessage
	waitbuttonpress
	release
	end

J_BerryTree_EventScript_Hns_Sprout::
	message J_BerryTree_Text_Hns_Sprouted
	waitmessage
	callnative Berry_Ready
	waitbuttonpress
	release
	end

J_BerryTree_EventScript_ItemUsePlantBerry::
	end

J_BerryTree_EventScript_ItemUseWailmerPail::
	end

J_BerryTree_Text_Hns_NotRipe:
	.string "It'{SE_M_GRASSWHISTLE}{SE_M_CHARGE}BERR{SE_M_MOONLIGHT}tree!\n"
	.string "Thes{SE_M_REVERSAL}BERRIE{SE_M_SKETCH}aren'{SE_M_SPIT_UP}rip{SE_M_REVERSAL}yet.$"

J_BerryTree_Text_Hns_Picked:
	.string "{PLAYER} picke{SE_M_WATERFALL}th{SE_M_REVERSAL}{STR_VAR_2} {STR_VAR_1}.$"

J_BerryTree_Text_Hns_BagFull:
	.string "Th{SE_M_REVERSAL}BAG'{SE_M_GRASSWHISTLE}BERRIE{SE_M_SKETCH}POCKE{SE_M_SWIFT}i{SE_M_GRASSWHISTLE}full.\p"
	.string "Th{SE_M_REVERSAL}{STR_VAR_1} couldn'{SE_M_SPIT_UP}b{SE_M_REVERSAL}taken.$"

J_BerryTree_Text_Hns_Sprouted:
	.string "Th{SE_M_REVERSAL}berr{SE_M_YAWN}tre{SE_M_REVERSAL}suddenl{SE_M_YAWN}sprouted!$"

