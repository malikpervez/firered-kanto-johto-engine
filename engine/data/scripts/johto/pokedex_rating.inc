@ Johto (data/scripts/pokedex_rating.inc), as built into the FireRed game.

J_PokedexRating_EventScript_RateInPerson::
	call_if_set 0, J_PokedexRating_EventScript_DexCompleteIntro
	call_if_unset 0, J_PokedexRating_EventScript_NormalIntro
	call J_PokedexRating_EventScript_Rate
	return

J_PokedexRating_EventScript_DexCompleteIntro::
	msgbox J_PokedexRating_Text_LoveSeeingYourPokedex
	return

J_PokedexRating_EventScript_NormalIntro::
	msgbox J_PokedexRating_Text_HowIsPokedexComingAlong
	return

J_PokedexRating_EventScript_ShowRatingMsg::
	copyvar 32772, 32777
	special GetProfOaksRatingMessage
	waitmessage
	call_if_eq 32781, FALSE, J_PokedexRating_EventScript_NormalFanfare
	call_if_eq 32781, TRUE, J_PokedexRating_EventScript_DexCompleteFanfare
	waitfanfare
	waitbuttonpress
	return

J_PokedexRating_EventScript_NormalFanfare::
	playfanfare 529
	return

J_PokedexRating_EventScript_DexCompleteFanfare::
	playfanfare 371
	return

J_PokedexRating_EventScript_Rate::
	specialvar 32781, GetFrlgPokedexCount
	copyvar 32776, 32773
	copyvar 32777, 32774
	copyvar 32778, 32781
	buffernumberstring STR_VAR_1, 32776
	buffernumberstring STR_VAR_2, 32777
	msgbox J_PokedexRating_Text_SeenXOwnedY
	call_if_unset 0, J_PokedexRating_EventScript_SetTextColor
	call J_PokedexRating_EventScript_ShowRatingMsg
	goto_if_eq 32778, FALSE, J_PokedexRating_EventScript_EndRating
	setvar 32772, 1
	specialvar 32781, GetFrlgPokedexCount
	copyvar 32776, 32773
	copyvar 32777, 32774
	buffernumberstring STR_VAR_1, 32776
	buffernumberstring STR_VAR_2, 32777
	msgbox J_PokedexRating_Text_NationalDexSeenXOwnedY
	specialvar 32781, HasAllMons
	goto_if_eq 32781, FALSE, J_PokedexRating_EventScript_DexIncomplete
	goto_if_eq 32781, TRUE, J_PokedexRating_EventScript_DexComplete
	end

J_PokedexRating_EventScript_SetTextColor::
	textcolor 0
	return

J_PokedexRating_EventScript_DexIncomplete::
	msgbox J_PokedexRating_Text_LookForwardToFilledNationalDex
	goto J_PokedexRating_EventScript_EndRating
	end

J_PokedexRating_EventScript_DexComplete::
	setflag 0
	msgbox J_PokedexRating_Text_YouveCompletedDex
	goto J_PokedexRating_EventScript_EndRating
	end

J_PokedexRating_EventScript_EndRating::
	return

