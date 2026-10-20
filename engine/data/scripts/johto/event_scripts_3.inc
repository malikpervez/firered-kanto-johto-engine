@ Johto (data/event_scripts.s), as built into the FireRed game.

J_EventScript_CancelMessageBox::
	special UseBlankMessageToCancelPokemonPic
	release
	end

J_Common_EventScript_ShowBagIsFull::
	msgbox J_gText_TooBadBagIsFull, MSGBOX_DEFAULT
	release
	end

J_Common_EventScript_NoOp::
	end

J_Common_EventScript_ReleaseNoOp::
	release
	end

J_Common_EventScript_BagIsFull::
	msgbox J_gText_TooBadBagIsFull, MSGBOX_DEFAULT
	return

J_EventScript_BagIsFull::
	textcolor NPC_TEXT_COLOR_NEUTRAL
	msgbox J_gText_TooBadBagIsFull
	release
	end

J_Common_EventScript_ShowNoRoomForDecor::
	msgbox J_gText_NoRoomLeftForAnother, MSGBOX_DEFAULT
	release
	end

J_Common_EventScript_NoRoomForDecor::
	msgbox J_gText_NoRoomLeftForAnother, MSGBOX_DEFAULT
	return

J_Common_EventScript_SetAbnormalWeather::
	setweather WEATHER_ABNORMAL
	return

J_Common_EventScript_PlayGymBadgeFanfare::
	playfanfare MUS_OBTAIN_BADGE
	waitfanfare
	return

J_Common_EventScript_OutOfCenterPartyHeal::
	fadescreenswapbuffers FADE_TO_BLACK
	playfanfare MUS_HEAL
	waitfanfare
	special HealPlayerParty
	callnative UpdateFollowingPokemon
	fadescreenswapbuffers FADE_FROM_BLACK
	return

J_EventScript_RegionMap::
	lockall
	msgbox J_Common_Text_LookCloserAtMap, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	special FieldShowRegionMap
	waitstate
	releaseall
	end

J_Common_EventScript_PlayBrineysBoatMusic::
	setflag FLAG_DONT_TRANSITION_MUSIC
	playbgm MUS_SAILING, FALSE
	return

J_Common_EventScript_StopBrineysBoatMusic::
	clearflag FLAG_DONT_TRANSITION_MUSIC
	fadedefaultbgm
	return

