@ Johto (data/scripts/tv.inc), as built into the FireRed game.

J_EventScript_TV::
	lockall
	incrementgamestat 44
	special ResetTVShowState
	specialvar 32781, CheckForPlayersHouseNews
	goto_if_eq 32781, 2, J_EventScript_PlayersHouseMovie
	goto_if_eq 32781, 1, J_EventScript_PlayersHouseLatiNewsFlash
	goto_if_unset 0, J_EventScript_MomDadMightLikeThis1
	goto_if_set 0, J_EventScript_MomDadMightLikeThis1
	specialvar 32781, IsGabbyAndTyShowOnTheAir
	goto_if_eq 32781, TRUE, J_EventScript_DoInSearchOfTrainers
	goto J_EventScript_TryDoPokeNews
	end

J_EventScript_TryDoTVShow::
	specialvar 32772, GetRandomActiveShowIdx
	goto_if_eq 32772, 255, J_EventScript_MomDadMightLikeThis2
	specialvar 32781, GetNextActiveShowIfMassOutbreak
	goto_if_eq 32781, 255, J_EventScript_MomDadMightLikeThis2
	copyvar 32772, 32781
	specialvar 32781, GetSelectedTVShow
	goto_if_ne 32781, 0, J_EventScript_DoTVShow
	end

J_EventScript_MomDadMightLikeThis1::
	special GetMomOrDadStringForTVMessage
	msgbox J_gText_MomOrDadMightLikeThisProgram, MSGBOX_DEFAULT
	special TurnOffTVScreen
	releaseall
	end

J_EventScript_PlayersHouseMovie::
	msgbox J_PlayersHouse_1F_Text_TheresAMovieOnTV, MSGBOX_DEFAULT
	releaseall
	end

J_EventScript_PlayersHouseLatiNewsFlash::
	msgbox J_PlayersHouse_1F_Text_LatiEmergencyNewsFlash, MSGBOX_DEFAULT
	special InitRoamer
	clearflag 0
	setflag 8955
	special TurnOffTVScreen
	releaseall
	end

J_EventScript_DoTVShow::
	special DoTVShow
	waitmessage
	waitbuttonpress
	goto_if_ne 32781, TRUE, J_EventScript_DoTVShow
	goto J_EventScript_TurnOffTV
	end

J_EventScript_TurnOffTV::
	special TurnOffTVScreen
	setflag 0
	releaseall
	end

J_EventScript_MomDadMightLikeThis2::
	special GetMomOrDadStringForTVMessage
	msgbox J_gText_MomOrDadMightLikeThisProgram, MSGBOX_DEFAULT
	goto J_EventScript_TurnOffTV
	end

J_EventScript_TryDoPokeNews::
	special DoPokeNews
	goto_if_eq 32781, FALSE, J_EventScript_TryDoTVShow
	waitmessage
	waitbuttonpress
	goto J_EventScript_TurnOffTV
	end

J_EventScript_DoInSearchOfTrainers::
	special DoTVShowInSearchOfTrainers
	waitmessage
	waitbuttonpress
	goto_if_eq 32781, 0, J_EventScript_DoInSearchOfTrainers
	goto J_EventScript_TurnOffTV
	end

