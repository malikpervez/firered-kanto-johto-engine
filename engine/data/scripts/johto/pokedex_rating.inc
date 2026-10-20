@ Johto (data/scripts/pokedex_rating.inc), as built into the FireRed game.

J_PokedexRating_EventScript_RateInPerson::
	call_if_set JOHTO_FLAG_OAK_SAW_DEX_COMPLETION, J_PokedexRating_EventScript_DexCompleteIntro
	call_if_unset JOHTO_FLAG_OAK_SAW_DEX_COMPLETION, J_PokedexRating_EventScript_NormalIntro
	call J_PokedexRating_EventScript_Rate
	return

J_PokedexRating_EventScript_DexCompleteIntro::
	msgbox J_PokedexRating_Text_LoveSeeingYourPokedex
	return

J_PokedexRating_EventScript_NormalIntro::
	msgbox J_PokedexRating_Text_HowIsPokedexComingAlong
	return

J_PokedexRating_EventScript_ShowRatingMsg::
	copyvar VAR_0x8004, VAR_0x8009
	special GetProfOaksRatingMessage
	waitmessage
	call_if_eq VAR_RESULT, FALSE, J_PokedexRating_EventScript_NormalFanfare
	call_if_eq VAR_RESULT, TRUE, J_PokedexRating_EventScript_DexCompleteFanfare
	waitfanfare
	waitbuttonpress
	return

J_PokedexRating_EventScript_NormalFanfare::
	playfanfare MUS_RG_DEX_RATING
	return

J_PokedexRating_EventScript_DexCompleteFanfare::
	playfanfare MUS_EVOLVED
	return

J_PokedexRating_EventScript_Rate::
	specialvar VAR_RESULT, GetFrlgPokedexCount
	copyvar VAR_0x8008, VAR_0x8005
	copyvar VAR_0x8009, VAR_0x8006
	copyvar VAR_0x800A, VAR_RESULT
	buffernumberstring STR_VAR_1, VAR_0x8008
	buffernumberstring STR_VAR_2, VAR_0x8009
	msgbox J_PokedexRating_Text_SeenXOwnedY
	call_if_unset JOHTO_FLAG_OAKS_RATING_IS_VIA_PC, J_PokedexRating_EventScript_SetTextColor
	call J_PokedexRating_EventScript_ShowRatingMsg
	goto_if_eq VAR_0x800A, FALSE, J_PokedexRating_EventScript_EndRating
	setvar VAR_0x8004, 1
	specialvar VAR_RESULT, GetFrlgPokedexCount
	copyvar VAR_0x8008, VAR_0x8005
	copyvar VAR_0x8009, VAR_0x8006
	buffernumberstring STR_VAR_1, VAR_0x8008
	buffernumberstring STR_VAR_2, VAR_0x8009
	msgbox J_PokedexRating_Text_NationalDexSeenXOwnedY
	specialvar VAR_RESULT, HasAllMons
	goto_if_eq VAR_RESULT, FALSE, J_PokedexRating_EventScript_DexIncomplete
	goto_if_eq VAR_RESULT, TRUE, J_PokedexRating_EventScript_DexComplete
	end

J_PokedexRating_EventScript_SetTextColor::
	textcolor NPC_TEXT_COLOR_MALE
	return

J_PokedexRating_EventScript_DexIncomplete::
	msgbox J_PokedexRating_Text_LookForwardToFilledNationalDex
	goto J_PokedexRating_EventScript_EndRating
	end

J_PokedexRating_EventScript_DexComplete::
	setflag JOHTO_FLAG_OAK_SAW_DEX_COMPLETION
	msgbox J_PokedexRating_Text_YouveCompletedDex
	goto J_PokedexRating_EventScript_EndRating
	end

J_PokedexRating_EventScript_EndRating::
	return

