@ Johto (data/maps/RuinsOfAlph_B1F_hns/scripts.inc), as built into the FireRed game.

RuinsOfAlph_B1F_hns_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, RuinsOfAlph_B1F_OnFrame
	.byte 0

RuinsOfAlph_B1F_OnFrame::
	map_script_2 JOHTO_VAR_RUINSOFALPH_STATE, 1, RuinsOfAlph_B1F_EventScript_Presence
	.2byte 0

RuinsOfAlph_B1F_EventScript_Presence::
	lock
	msgbox RuinsOfAlph_B1F_Text_Presence, MSGBOX_DEFAULT
	closemessage
	setvar JOHTO_VAR_RUINSOFALPH_STATE, 0
	release
	end

RuinsOfAlph_B1F_EventScript_Teacher::
	lock
	faceplayer
	msgbox RuinsOfAlph_B1F_Text_Teacher, MSGBOX_DEFAULT
	release
	end

RuinsOfAlph_B1F_EventScript_Hiker::
	lock
	faceplayer
	msgbox RuinsOfAlph_B1F_Text_Hiker, MSGBOX_DEFAULT
	release
	end

RuinsOfAlph_B1F_EventScript_Gramps::
	lock
	faceplayer
	msgbox RuinsOfAlph_B1F_Text_Gramps, MSGBOX_DEFAULT
	release
	end

RuinsOfAlph_PuzzleAndRewardChambers_EventScript_HelixFossil::
	finditem ITEM_HELIX_FOSSIL
	end

RuinsOfAlph_PuzzleAndRewardChambers_EventScript_DomeFossil::
	finditem ITEM_DOME_FOSSIL
	end

RuinsOfAlph_PuzzleAndRewardChambers_EventScript_OldAmber::
	finditem ITEM_OLD_AMBER
	end

RuinsOfAlph_PuzzleAndRewardChambers_EventScript_GSBALL::
	finditem ITEM_GS_BALL
	end

RuinsOfAlph_B1F_Text_Presence:
	.string "Ther{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}strang{SE_M_REVERSAL}presenc{SE_M_REVERSAL}here.$"

RuinsOfAlph_B1F_Text_Hiker:
	.string "Thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}{SE_M_CHARGE}bi{SE_M_SANDSTORM}room{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}there's\n"
	.string "nothin{SE_M_SANDSTORM}here.$"

RuinsOfAlph_B1F_Text_Teacher:
	.string "Thi{SE_M_GRASSWHISTLE}plac{SE_M_REVERSAL}ha{SE_M_GRASSWHISTLE}{SE_M_CHARGE}mystical\n"
	.string "qualit{SE_M_YAWN}t{SE_M_ATTRACT2}it.\p"
	.string "I{SE_M_SPIT_UP}feel{SE_M_GRASSWHISTLE}sor{SE_M_SPIT_UP}o{SE_M_ACID_ARMOR}ethereal\n"
	.string "even.$"

RuinsOfAlph_B1F_Text_Gramps:
	.string "Ancien{SE_M_SPIT_UP}building{SE_M_GRASSWHISTLE}ar{SE_M_REVERSAL}often\n"
	.string "tomb{SE_M_GRASSWHISTLE}o{SE_M_ACID_ARMOR}kings.\p"
	.string "Lik{SE_M_REVERSAL}th{SE_M_REVERSAL}pyramids{SE_M_SUPERSONIC}for\n"
	.string "instance.$"

