@ Johto (data/scripts/tv.inc), as built into the FireRed game.

J_EventScript_TV::
	lockall
	incrementgamestat GAME_STAT_WATCHED_TV
	special ResetTVShowState
	specialvar VAR_RESULT, CheckForPlayersHouseNews
	goto_if_eq VAR_RESULT, PLAYERS_HOUSE_TV_MOVIE, J_EventScript_PlayersHouseMovie
	goto_if_eq VAR_RESULT, PLAYERS_HOUSE_TV_LATI, J_EventScript_PlayersHouseLatiNewsFlash
	goto_if_unset FLAG_SYS_TV_START, J_EventScript_MomDadMightLikeThis1
	goto_if_set FLAG_SYS_TV_WATCH, J_EventScript_MomDadMightLikeThis1
	specialvar VAR_RESULT, IsGabbyAndTyShowOnTheAir
	goto_if_eq VAR_RESULT, TRUE, J_EventScript_DoInSearchOfTrainers
	goto J_EventScript_TryDoPokeNews
	end

J_EventScript_TryDoTVShow::
	specialvar VAR_0x8004, GetRandomActiveShowIdx
	goto_if_eq VAR_0x8004, 255, J_EventScript_MomDadMightLikeThis2
	specialvar VAR_RESULT, GetNextActiveShowIfMassOutbreak
	goto_if_eq VAR_RESULT, 255, J_EventScript_MomDadMightLikeThis2
	copyvar VAR_0x8004, VAR_RESULT
	specialvar VAR_RESULT, GetSelectedTVShow
	goto_if_ne VAR_RESULT, 0, J_EventScript_DoTVShow
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
	clearflag FLAG_SYS_TV_LATIAS_LATIOS
	setflag JOHTO_FLAG_LATIOS_OR_LATIAS_ROAMING
	special TurnOffTVScreen
	releaseall
	end

J_EventScript_DoTVShow::
	special DoTVShow
	waitmessage
	waitbuttonpress
	goto_if_ne VAR_RESULT, TRUE, J_EventScript_DoTVShow
	goto J_EventScript_TurnOffTV
	end

J_EventScript_TurnOffTV::
	special TurnOffTVScreen
	setflag FLAG_SYS_TV_WATCH
	releaseall
	end

J_EventScript_MomDadMightLikeThis2::
	special GetMomOrDadStringForTVMessage
	msgbox J_gText_MomOrDadMightLikeThisProgram, MSGBOX_DEFAULT
	goto J_EventScript_TurnOffTV
	end

J_EventScript_TryDoPokeNews::
	special DoPokeNews
	goto_if_eq VAR_RESULT, FALSE, J_EventScript_TryDoTVShow
	waitmessage
	waitbuttonpress
	goto J_EventScript_TurnOffTV
	end

J_EventScript_DoInSearchOfTrainers::
	special DoTVShowInSearchOfTrainers
	waitmessage
	waitbuttonpress
	goto_if_eq VAR_RESULT, 0, J_EventScript_DoInSearchOfTrainers
	goto J_EventScript_TurnOffTV
	end

