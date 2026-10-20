@ Johto (data/scripts/secret_power_tm.inc), as built into the FireRed game.

J_Route111_Text_MakingRoomUseTMToMakeYourOwn:
	.string "What'{SE_M_GRASSWHISTLE}that?\n"
	.string "Wha{SE_M_SPIT_UP}a{SE_M_MILK_DRINK}{SE_M_HEAL_BELL}doing?\p"
	.string "I'{SE_M_MILK_DRINK}thinkin{SE_M_SANDSTORM}abou{SE_M_SPIT_UP}makin{SE_M_SANDSTORM}m{SE_M_YAWN}ow{SE_M_ATTRACT}room\n"
	.string "her{SE_M_REVERSAL}usin{SE_M_SANDSTORM}{SE_M_CHARGE}POKéMO{SE_M_PSYBEAM2}move.\p"
	.string "{SE_M_HEAL_BELL}know{SE_M_DRAGON_RAGE}I'l{SE_M_BATON_PASS}giv{SE_M_REVERSAL}yo{SE_M_DIVE}thi{SE_M_GRASSWHISTLE}TM.\n"
	.string "Wil{SE_M_BATON_PASS}yo{SE_M_DIVE}us{SE_M_REVERSAL}i{SE_M_SPIT_UP}t{SE_M_ATTRACT2}mak{SE_M_REVERSAL}you{SE_M_SAND_TOMB}ow{SE_M_ATTRACT}room?$"

J_Route111_Text_ExplainSecretPower:
	.string "Fin{SE_M_WATERFALL}{SE_M_CHARGE}bi{SE_M_SANDSTORM}tre{SE_M_REVERSAL}tha{SE_M_SPIT_UP}look{SE_M_GRASSWHISTLE}lik{SE_M_REVERSAL}i{SE_M_SPIT_UP}might\n"
	.string "dro{SE_M_MORNING_SUN}som{SE_M_REVERSAL}vines.\p"
	.string "Us{SE_M_REVERSAL}SECRE{SE_M_SWIFT}POWE{SE_M_MINIMIZE}i{SE_M_ATTRACT}fron{SE_M_SPIT_UP}o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}tree.\n"
	.string "Som{SE_M_REVERSAL}vine{SE_M_GRASSWHISTLE}shoul{SE_M_WATERFALL}ge{SE_M_SPIT_UP}fre{SE_M_REVERSAL}an{SE_M_WATERFALL}drop\l"
	.string "down{SE_M_SUPERSONIC}s{SE_M_ATTRACT2}yo{SE_M_DIVE}ca{SE_M_ATTRACT}clim{SE_M_STRENGTH}th{SE_M_REVERSAL}tree.\p"
	.string "You'l{SE_M_BATON_PASS}fin{SE_M_WATERFALL}{SE_M_CHARGE}lo{SE_M_SPIT_UP}o{SE_M_ACID_ARMOR}spac{SE_M_REVERSAL}fo{SE_M_SAND_TOMB}putting\n"
	.string "you{SE_M_SAND_TOMB}favorit{SE_M_REVERSAL}things.\p"
	.string "It'l{SE_M_BATON_PASS}b{SE_M_REVERSAL}you{SE_M_SAND_TOMB}ow{SE_M_ATTRACT}secre{SE_M_SPIT_UP}room…\n"
	.string "{SE_M_BONEMERANG}SECRE{SE_M_SWIFT}BASE!\p"
	.string "Yo{SE_M_DIVE}shoul{SE_M_WATERFALL}mak{SE_M_REVERSAL}one{SE_M_SUPERSONIC}too.\p"
	.string "Anothe{SE_M_SAND_TOMB}thing{SE_M_SUPERSONIC}yo{SE_M_DIVE}don'{SE_M_SPIT_UP}alway{SE_M_GRASSWHISTLE}have\n"
	.string "t{SE_M_ATTRACT2}mak{SE_M_REVERSAL}you{SE_M_SAND_TOMB}SECRE{SE_M_SWIFT}BAS{SE_M_SWORDS_DANCE}i{SE_M_ATTRACT}{SE_M_CHARGE}tree.\p"
	.string "Tr{SE_M_YAWN}usin{SE_M_SANDSTORM}SECRE{SE_M_SWIFT}POWE{SE_M_MINIMIZE}o{SE_M_ATTRACT}roc{SE_M_ENCORE2}walls\n"
	.string "tha{SE_M_SPIT_UP}hav{SE_M_REVERSAL}smal{SE_M_BATON_PASS}indent{SE_M_GRASSWHISTLE}i{SE_M_ATTRACT}them.\p"
	.string "I'{SE_M_MILK_DRINK}goin{SE_M_SANDSTORM}t{SE_M_ATTRACT2}loo{SE_M_ENCORE2}fo{SE_M_SAND_TOMB}othe{SE_M_SAND_TOMB}places{SE_M_SUPERSONIC}too.\n"
	.string "Okay{SE_M_SUPERSONIC}bye!$"

J_Route111_Text_DontWantThis:
	.string "Oh{SE_M_SUPERSONIC}yo{SE_M_DIVE}don'{SE_M_SPIT_UP}wan{SE_M_SPIT_UP}this?\n"
	.string "I{SE_M_ACID_ARMOR}yo{SE_M_DIVE}chang{SE_M_REVERSAL}you{SE_M_SAND_TOMB}mind{SE_M_SUPERSONIC}tel{SE_M_BATON_PASS}me{SE_M_SUPERSONIC}okay?$"

J_Route111_Text_DontHaveAnyRoom:
	.string "Oh{SE_M_SUPERSONIC}yo{SE_M_DIVE}don'{SE_M_SPIT_UP}hav{SE_M_REVERSAL}an{SE_M_YAWN}roo{SE_M_MILK_DRINK}fo{SE_M_SAND_TOMB}this.\p"
	.string "I'l{SE_M_BATON_PASS}hol{SE_M_WATERFALL}o{SE_M_ATTRACT}t{SE_M_ATTRACT2}it{SE_M_SUPERSONIC}s{SE_M_ATTRACT2}com{SE_M_REVERSAL}bac{SE_M_ENCORE2}fo{SE_M_SAND_TOMB}it\n"
	.string "anothe{SE_M_SAND_TOMB}time{SE_M_SUPERSONIC}okay?$"

J_Route111_EventScript_SecretPowerMan::
	lock
	faceplayer
	msgbox J_Route111_Text_MakingRoomUseTMToMakeYourOwn, MSGBOX_YESNO
	goto_if_eq 32781, YES, J_Route111_EventScript_GiveSecretPower
	msgbox J_Route111_Text_DontWantThis, MSGBOX_DEFAULT
	release
	end

J_Route111_EventScript_GiveSecretPower::
	giveitem 624
	goto_if_eq 32781, FALSE, J_Route111_EventScript_NoRoomForSecretPower
	msgbox J_Route111_Text_ExplainSecretPower, MSGBOX_DEFAULT
	closemessage
	setflag 0
	clearflag 0
	call_if_eq 32780, DIR_WEST, J_Route111_EventScript_SecretPowerManExit
	call_if_eq 32780, DIR_EAST, J_Route111_EventScript_SecretPowerManExit
	call_if_eq 32780, DIR_NORTH, J_Route111_EventScript_SecretPowerManExitNorth
	removeobject 32783
	release
	end

J_Route111_EventScript_SecretPowerManExit::
	applymovement 32783, J_Route111_Movement_SecretPowerManExit
	waitmovement 0
	return

J_Route111_EventScript_SecretPowerManExitNorth::
	applymovement 32783, J_Route111_Movement_SecretPowerManExitNorth
	waitmovement 0
	return

J_Route111_EventScript_NoRoomForSecretPower::
	msgbox J_Route111_Text_DontHaveAnyRoom, MSGBOX_DEFAULT
	release
	end

J_Route111_Movement_SecretPowerManExit:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	step_end

J_Route111_Movement_SecretPowerManExitNorth:
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	step_end

