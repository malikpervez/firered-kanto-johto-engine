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
	textcolor 3
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
	setweather 15
	return

J_Common_EventScript_PlayGymBadgeFanfare::
	playfanfare 369
	waitfanfare
	return

J_Common_EventScript_OutOfCenterPartyHeal::
	fadescreenswapbuffers 1
	playfanfare 368
	waitfanfare
	special HealPlayerParty
	callnative UpdateFollowingPokemon
	fadescreenswapbuffers 0
	return

J_EventScript_RegionMap::
	lockall
	msgbox J_Common_Text_LookCloserAtMap, MSGBOX_DEFAULT
	fadescreen 1
	special FieldShowRegionMap
	waitstate
	releaseall
	end

J_Common_EventScript_PlayBrineysBoatMusic::
	setflag 16385
	playbgm 431, FALSE
	return

J_Common_EventScript_StopBrineysBoatMusic::
	clearflag 16385
	fadedefaultbgm
	return

