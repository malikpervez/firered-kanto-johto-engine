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
	.string "It's a BERRY tree!\n"
	.string "These BERRIES aren't ripe yet.$"

J_BerryTree_Text_Hns_Picked:
	.string "{PLAYER} picked the {STR_VAR_2} {STR_VAR_1}.$"

J_BerryTree_Text_Hns_BagFull:
	.string "The BAG's BERRIES POCKET is full.\p"
	.string "The {STR_VAR_1} couldn't be taken.$"

J_BerryTree_Text_Hns_Sprouted:
	.string "The berry tree suddenly sprouted!$"

