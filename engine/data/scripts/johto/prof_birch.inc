@ Johto (data/scripts/prof_birch.inc), as built into the FireRed game.

J_ProfBirch_EventScript_UpdateLocation::
	goto_if_eq JOHTO_VAR_PETALBURG_GYM_STATE, 0, J_Common_EventScript_NopReturn
	goto_if_set JOHTO_FLAG_SYS_GAME_CLEAR, J_ProfBirch_EventScript_MoveToLab
	call_if_eq JOHTO_VAR_BIRCH_STATE, 0, J_ProfBirch_EventScript_MoveToLab
	call_if_eq JOHTO_VAR_BIRCH_STATE, 1, J_ProfBirch_EventScript_MoveToLab
	call_if_eq JOHTO_VAR_BIRCH_STATE, 2, J_ProfBirch_EventScript_MoveToRoute101
	call_if_eq JOHTO_VAR_BIRCH_STATE, 3, J_ProfBirch_EventScript_MoveToRoute101
	call_if_eq JOHTO_VAR_BIRCH_STATE, 4, J_ProfBirch_EventScript_MoveToRoute103
	call_if_eq JOHTO_VAR_BIRCH_STATE, 5, J_ProfBirch_EventScript_MoveToRoute103
	call_if_eq JOHTO_VAR_BIRCH_STATE, 6, J_ProfBirch_EventScript_MoveToLab
	call_if_eq JOHTO_VAR_BIRCH_STATE, 7, J_ProfBirch_EventScript_MoveToLab
	return

J_ProfBirch_EventScript_MoveToLab::
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_BIRCH
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_UNKNOWN_0x380
	setflag FLAG_HIDE_ROUTE_101_BIRCH
	setflag FLAG_HIDE_ROUTE_103_BIRCH
	return

J_ProfBirch_EventScript_MoveToRoute101::
	clearflag FLAG_HIDE_ROUTE_101_BIRCH
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_BIRCH
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_UNKNOWN_0x380
	setflag FLAG_HIDE_ROUTE_103_BIRCH
	return

J_ProfBirch_EventScript_MoveToRoute103::
	clearflag FLAG_HIDE_ROUTE_103_BIRCH
	setflag FLAG_HIDE_ROUTE_101_BIRCH
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_BIRCH
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_UNKNOWN_0x380
	return

J_ProfBirch_EventScript_RatePokedexOrRegister::
	lock
	faceplayer

	goto_if_eq JOHTO_VAR_NEWBARKTOWN_LABSTATE, 3, J_ProfBirch_EventScript_GoFindMrPokemon
	goto_if_eq JOHTO_VAR_NEWBARKTOWN_LABSTATE, 4, J_ProfBirch_EventScript_Robbery

J_ProfBirch_EventScript_GoFindMrPokemon::
	msgbox J_gElmDexRatingText_GoFindMrPokemon, MSGBOX_DEFAULT
	release
	end

J_ProfBirch_EventScript_Robbery::
	msgbox J_gElmDexRatingText_Robbery, MSGBOX_DEFAULT
	release
	end

J_ProfBirch_EventScript_AskRatePokedex::
	msgbox J_gBirchDexRatingText_AreYouCurious, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, J_ProfBirch_EventScript_DeclineRating
	call J_ProfBirch_EventScript_RatePokedex
	release
	end

J_ProfBirch_EventScript_DeclineRating::
	msgbox J_gBirchDexRatingText_Cancel, MSGBOX_DEFAULT
	release
	end

J_ProfBirch_EventScript_ShowRatingMessage::
	copyvar VAR_0x8004, VAR_0x8009
	special ShowPokedexRatingMessage
	waitmessage
	waitbuttonpress
	return

J_ProfBirch_EventScript_RatePokedex::
	setvar VAR_0x8004, 0
	specialvar VAR_RESULT, ScriptGetPokedexInfo
	copyvar VAR_0x8008, VAR_0x8005
	copyvar VAR_0x8009, VAR_0x8006
	copyvar VAR_0x800A, VAR_RESULT
	buffernumberstring STR_VAR_1, VAR_0x8008
	buffernumberstring STR_VAR_2, VAR_0x8009
	msgbox J_gBirchDexRatingText_SoYouveSeenAndCaught, MSGBOX_DEFAULT
	call J_ProfBirch_EventScript_ShowRatingMessage
	goto_if_eq VAR_0x800A, 0, J_Common_EventScript_NopReturn
	setvar VAR_0x8004, 1
	specialvar VAR_RESULT, ScriptGetPokedexInfo
	copyvar VAR_0x8008, VAR_0x8005
	copyvar VAR_0x8009, VAR_0x8006
	buffernumberstring STR_VAR_1, VAR_0x8008
	buffernumberstring STR_VAR_2, VAR_0x8009
	msgbox J_gBirchDexRatingText_OnANationwideBasis, MSGBOX_DEFAULT
	return

