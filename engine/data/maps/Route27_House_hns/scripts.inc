@ Johto (data/maps/Route27_House_hns/scripts.inc), as built into the FireRed game.

Route27_House_hns_MapScripts::
	.byte 0

Route27_House_EventScript_Woman::
	lock
	faceplayer
	goto_if_unset 8717, Route27_House_EventScript_WomanBeforeGiven
	msgbox SandstormHouse_Text_TM37Description, MSGBOX_DEFAULT
	closemessage
	release
	end

Route27_House_EventScript_WomanBeforeGiven::
	msgbox SandstormHouse_Text_Woman1, MSGBOX_DEFAULT
	specialvar 32781, GetLeadMonFriendshipScore
	goto_if_ge 32781, 4, Route27_House_EventScript_WomanHighFriendship
	playfirstmoncry
	applymovement 0xFE J_FollowerLookAway
	waitmovement 0xFE
	applymovement 0xFE J_Common_Movement_QuestionMark
	waitmovement 0xFE
	msgbox SandstormHouse_Text_DisloyalMon, MSGBOX_DEFAULT
	closemessage
	release
	end

Route27_House_EventScript_WomanHighFriendship::
	playfirstmoncry
	applymovement 0xFE J_FollowerDance
	waitmovement 0
	applymovement 0xFE J_ContestHall_Movement_Heart
	waitmovement 0
	msgbox SandstormHouse_Text_LoyalMon, MSGBOX_DEFAULT
	giveitem 618
	setflag 8717
	msgbox SandstormHouse_Text_TM37Description, MSGBOX_DEFAULT
	closemessage
	release
	end

Route27_Movement_FollowerJump:
	jump_in_place_down
	jump_in_place_down
	step_end

SandstormHouse_Text_Woman1:
	.string "Wher{SE_M_REVERSAL}ar{SE_M_REVERSAL}yo{SE_M_DIVE}of{SE_M_ACID_ARMOR}t{SE_M_ATTRACT2}with\n"
	.string "POKéMON?\p"
	.string "POKéMO{SE_M_PSYBEAM2}LEAGUE?\p"
	.string "Ar{SE_M_REVERSAL}you{SE_M_SAND_TOMB}POKéMO{SE_M_PSYBEAM2}loya{SE_M_BATON_PASS}enoug{SE_M_TRI_ATTACK}for\n"
	.string "yo{SE_M_DIVE}t{SE_M_ATTRACT2}win?\p"
	.string "Le{SE_M_SPIT_UP}m{SE_M_REVERSAL}see…$"

SandstormHouse_Text_LoyalMon:
	.string "Ah{SE_M_DRAGON_RAGE}You{SE_M_SAND_TOMB}POKéMO{SE_M_PSYBEAM2}trust{SE_M_GRASSWHISTLE}yo{SE_M_DIVE}very\n"
	.string "much.\p"
	.string "It'{SE_M_GRASSWHISTLE}nic{SE_M_REVERSAL}t{SE_M_ATTRACT2}se{SE_M_REVERSAL}{SE_M_CHARGE}goo{SE_M_WATERFALL}trainer.\p"
	.string "Here{SE_M_PERISH_SONG}{SE_M_BONEMERANG}gif{SE_M_SPIT_UP}fo{SE_M_SAND_TOMB}you{SE_M_SAND_TOMB}journey.$"

SandstormHouse_Text_TM37Description:
	.string "TM3{SE_M_MIST}happen{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}b{SE_M_REVERSAL}SANDSTORM.\p"
	.string "It'{SE_M_GRASSWHISTLE}{SE_M_CHARGE}mov{SE_M_REVERSAL}tha{SE_M_SPIT_UP}inflict{SE_M_GRASSWHISTLE}damage\n"
	.string "o{SE_M_ATTRACT}bot{SE_M_TRI_ATTACK}battlers.\p"
	.string "It'{SE_M_GRASSWHISTLE}fo{SE_M_SAND_TOMB}advance{SE_M_WATERFALL}trainer{SE_M_GRASSWHISTLE}only.\p"
	.string "Us{SE_M_REVERSAL}i{SE_M_SPIT_UP}i{SE_M_ACID_ARMOR}yo{SE_M_DIVE}dare{SE_M_PERISH_SONG}Goo{SE_M_WATERFALL}luck!$"

SandstormHouse_Text_DisloyalMon:
	.string "I{SE_M_ACID_ARMOR}i{SE_M_SPIT_UP}doesn'{SE_M_SPIT_UP}com{SE_M_REVERSAL}t{SE_M_ATTRACT2}trus{SE_M_SPIT_UP}you\n"
	.string "som{SE_M_REVERSAL}more{SE_M_SUPERSONIC}i{SE_M_SPIT_UP}coul{SE_M_WATERFALL}b{SE_M_REVERSAL}toug{SE_M_TRI_ATTACK}going.\p"
	.string "Trus{SE_M_SPIT_UP}i{SE_M_GRASSWHISTLE}th{SE_M_REVERSAL}ti{SE_M_REVERSAL}tha{SE_M_SPIT_UP}bind{SE_M_GRASSWHISTLE}POKéMON\n"
	.string "an{SE_M_WATERFALL}trainers.$"

