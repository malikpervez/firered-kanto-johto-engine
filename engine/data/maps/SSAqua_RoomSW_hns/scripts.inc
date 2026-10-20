@ Johto (data/maps/SSAqua_RoomSW_hns/scripts.inc), as built into the FireRed game.

SSAqua_RoomSW_hns_MapScripts::
	.byte 0

SSAqua_RoomSW_EventScript_Cassie::
	trainerbattle_single 1119, SSAqua_RoomSW_Text_BeautyCassieSeen, SSAqua_RoomSW_Text_BeautyCassieBeaten
	msgbox SSAqua_RoomSW_Text_BeautyCassieAfterBattle, MSGBOX_AUTOCLOSE
	end

SSAqua_RoomSW_EventScript_Clyde::
	trainerbattle_single 1280, SSAqua_RoomSW_Text_GuitaristClydeSeen, SSAqua_RoomSW_Text_GuitaristClydeBeaten
	msgbox SSAqua_RoomSW_Text_GuitaristClydeAfterBattle, MSGBOX_AUTOCLOSE
	end

SSAqua_RoomSW_Text_BeautyCassieSeen:
	.string "I'{SE_M_MILK_DRINK}tryin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}forge{SE_M_SPIT_UP}m{SE_M_YAWN}woes.\n"
	.string "Let'{SE_M_GRASSWHISTLE}battle!$"

SSAqua_RoomSW_Text_BeautyCassieBeaten:
	.string "M{SE_M_YAWN}hear{SE_M_SPIT_UP}weeps…$"

SSAqua_RoomSW_Text_BeautyCassieAfterBattle:
	.string "{SE_M_BONEMERANG}voyag{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}bes{SE_M_SPIT_UP}fo{SE_M_SAND_TOMB}gettin{SE_M_SANDSTORM}over\n"
	.string "{SE_M_CHARGE}broke{SE_M_ATTRACT}heart.\p"
	.string "Bu{SE_M_SPIT_UP}{SE_M_CHARGE}FAS{SE_M_SWIFT}SHI{SE_M_PETAL_DANCE}tri{SE_M_MORNING_SUN}i{SE_M_GRASSWHISTLE}to{SE_M_ATTRACT2}short\n"
	.string "fo{SE_M_SAND_TOMB}grieving.$"

SSAqua_RoomSW_Text_GuitaristClydeSeen:
	.string "I'{SE_M_MILK_DRINK}goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}auditio{SE_M_ATTRACT}m{SE_M_YAWN}songs\n"
	.string "a{SE_M_SPIT_UP}GOLDENROD'{SE_M_GRASSWHISTLE}RADI{SE_M_SOLAR_BEAM}STATION.$"

SSAqua_RoomSW_Text_GuitaristClydeBeaten:
	.string "Yowza{SE_M_DRAGON_RAGE}Tota{SE_M_BATON_PASS}distortion!$"

SSAqua_RoomSW_Text_GuitaristClydeAfterBattleMobile:
	.string "{SE_M_HEAL_BELL}wa{SE_M_GRASSWHISTLE}goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}mak{SE_M_REVERSAL}m{SE_M_YAWN}debu{SE_M_SPIT_UP}at\n"
	.string "th{SE_M_REVERSAL}BATTL{SE_M_SWORDS_DANCE}TOWER…\p"
	.string "{SE_M_HEAL_BELL}shoul{SE_M_WATERFALL}g{SE_M_ATTRACT2}bac{SE_M_ENCORE2}t{SE_M_ATTRACT2}VERMILIO{SE_M_PSYBEAM2}and\n"
	.string "red{SE_M_ATTRACT2}m{SE_M_YAWN}training…$"

SSAqua_RoomSW_Text_GuitaristClydeAfterBattle:
	.string "Speakin{SE_M_SANDSTORM}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}RADI{SE_M_SOLAR_BEAM}STATION,\n"
	.string "what'{SE_M_GRASSWHISTLE}thi{SE_M_GRASSWHISTLE}week'{SE_M_GRASSWHISTLE}luck{SE_M_YAWN}number?$"

