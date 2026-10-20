@ Johto (data/maps/SproutTower_2F_hns/scripts.inc), as built into the FireRed game.

SproutTower_2F_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SproutTower_2F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, J_SetTimeEncounters
	.byte 0

SproutTower_2F_OnTransition:
	callnative SetTimeBasedEncounters
	end

SproutTower_2F_EventScript_SageNico::
	trainerbattle_single TRAINER_JOHTO_NICO_HNS, SproutTower_Text_SageNico_Seen, SproutTower_Text_SageNico_Beaten
	msgbox SproutTower_Text_SageNico_AfterBattle, MSGBOX_AUTOCLOSE
	end

SproutTower_2F_EventScript_SageEdmond::
	trainerbattle_single TRAINER_JOHTO_EDMOND_HNS, SproutTower_Text_SageEdmond_Seen, SproutTower_Text_SageEdmond_Beaten
	msgbox SproutTower_Text_SageEdmond_AfterBattle, MSGBOX_AUTOCLOSE
	end

SproutTower_2F_EventScript_Statue::
	lock
	msgbox SproutTower_Text_2F_Statue, MSGBOX_AUTOCLOSE
	release
	end

SproutTower_2F_EventScript_Xdefend::
	finditem ITEM_X_DEFEND
	end

SproutTower_Text_SageNico_Seen:
	.string "Howeve{SE_M_SAND_TOMB}har{SE_M_WATERFALL}w{SE_M_REVERSAL}battle,\n"
	.string "th{SE_M_REVERSAL}TOWE{SE_M_MINIMIZE}wil{SE_M_BATON_PASS}stan{SE_M_WATERFALL}strong.$"

SproutTower_Text_SageNico_Beaten:
	.string "{SE_M_HEAL_BELL}fough{SE_M_SPIT_UP}har{SE_M_WATERFALL}bu{SE_M_SPIT_UP}I'{SE_M_MILK_DRINK}to{SE_M_ATTRACT2}weak.$"

SproutTower_Text_SageNico_AfterBattle:
	.string "Th{SE_M_REVERSAL}flexibl{SE_M_REVERSAL}pilla{SE_M_SAND_TOMB}protect{SE_M_GRASSWHISTLE}the\n"
	.string "TOWER{SE_M_SUPERSONIC}eve{SE_M_ATTRACT}fro{SE_M_MILK_DRINK}earthquakes.$"

SproutTower_Text_SageEdmond_Seen:
	.string "…Swa{SE_M_YAWN}lik{SE_M_REVERSAL}leave{SE_M_GRASSWHISTLE}i{SE_M_ATTRACT}th{SE_M_REVERSAL}wind…$"

SproutTower_Text_SageEdmond_Beaten:
	.string "Oh{SE_M_SUPERSONIC}I'{SE_M_MILK_DRINK}weak!$"

SproutTower_Text_SageEdmond_AfterBattle:
	.string "{SE_M_HEAL_BELL}trie{SE_M_WATERFALL}t{SE_M_ATTRACT2}cop{SE_M_YAWN}BELLSPROUT's\n"
	.string "gentl{SE_M_REVERSAL}movement{SE_M_GRASSWHISTLE}fo{SE_M_SAND_TOMB}battle…\p"
	.string "Bu{SE_M_SPIT_UP}{SE_M_HEAL_BELL}didn'{SE_M_SPIT_UP}trai{SE_M_ATTRACT}wel{SE_M_BATON_PASS}enough.$"

SproutTower_Text_2F_Statue:
	.string "{SE_M_BONEMERANG}POKéMO{SE_M_PSYBEAM2}statue…\p"
	.string "I{SE_M_SPIT_UP}look{SE_M_GRASSWHISTLE}ver{SE_M_YAWN}distinguished.$"

