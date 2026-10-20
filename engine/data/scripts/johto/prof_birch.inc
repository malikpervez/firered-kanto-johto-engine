@ Johto (data/scripts/prof_birch.inc), as built into the FireRed game.

J_ProfBirch_EventScript_UpdateLocation::
	goto_if_eq 20597, 0, J_Common_EventScript_NopReturn
	goto_if_set 10387, J_ProfBirch_EventScript_MoveToLab
	call_if_eq 20537, 0, J_ProfBirch_EventScript_MoveToLab
	call_if_eq 20537, 1, J_ProfBirch_EventScript_MoveToLab
	call_if_eq 20537, 2, J_ProfBirch_EventScript_MoveToRoute101
	call_if_eq 20537, 3, J_ProfBirch_EventScript_MoveToRoute101
	call_if_eq 20537, 4, J_ProfBirch_EventScript_MoveToRoute103
	call_if_eq 20537, 5, J_ProfBirch_EventScript_MoveToRoute103
	call_if_eq 20537, 6, J_ProfBirch_EventScript_MoveToLab
	call_if_eq 20537, 7, J_ProfBirch_EventScript_MoveToLab
	return

J_ProfBirch_EventScript_MoveToLab::
	clearflag 0
	clearflag 0
	setflag 0
	setflag 0
	return

J_ProfBirch_EventScript_MoveToRoute101::
	clearflag 0
	setflag 0
	setflag 0
	setflag 0
	return

J_ProfBirch_EventScript_MoveToRoute103::
	clearflag 0
	setflag 0
	setflag 0
	setflag 0
	return

J_ProfBirch_EventScript_RatePokedexOrRegister::
	lock
	faceplayer

	goto_if_eq 20580, 3, J_ProfBirch_EventScript_GoFindMrPokemon
	goto_if_eq 20580, 4, J_ProfBirch_EventScript_Robbery

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
	goto_if_eq 32781, NO, J_ProfBirch_EventScript_DeclineRating
	call J_ProfBirch_EventScript_RatePokedex
	release
	end

J_ProfBirch_EventScript_DeclineRating::
	msgbox J_gBirchDexRatingText_Cancel, MSGBOX_DEFAULT
	release
	end

J_ProfBirch_EventScript_ShowRatingMessage::
	copyvar 32772, 32777
	special ShowPokedexRatingMessage
	waitmessage
	waitbuttonpress
	return

J_ProfBirch_EventScript_RatePokedex::
	setvar 32772, 0
	specialvar 32781, ScriptGetPokedexInfo
	copyvar 32776, 32773
	copyvar 32777, 32774
	copyvar 32778, 32781
	buffernumberstring STR_VAR_1, 32776
	buffernumberstring STR_VAR_2, 32777
	msgbox J_gBirchDexRatingText_SoYouveSeenAndCaught, MSGBOX_DEFAULT
	call J_ProfBirch_EventScript_ShowRatingMessage
	goto_if_eq 32778, 0, J_Common_EventScript_NopReturn
	setvar 32772, 1
	specialvar 32781, ScriptGetPokedexInfo
	copyvar 32776, 32773
	copyvar 32777, 32774
	buffernumberstring STR_VAR_1, 32776
	buffernumberstring STR_VAR_2, 32777
	msgbox J_gBirchDexRatingText_OnANationwideBasis, MSGBOX_DEFAULT
	return

