@ Johto (data/scripts/profile_man.inc), as built into the FireRed game.

J_ProfileMan_EventScript_Man::
	lock
	faceplayer
	goto_if_set 0, J_ProfileMan_EventScript_GivenProfileBefore
	msgbox J_ProfileMan_Text_CollectTrainerProfiles, MSGBOX_DEFAULT
	goto J_ProfileMan_EventScript_AskToSeeProfile
	end

J_ProfileMan_EventScript_AskToSeeProfile::
	msgbox J_ProfileMan_Text_MayISeeYourProfile, MSGBOX_DEFAULT
	multichoice 17, 6, 20, FALSE
	switch 32781
	case 0, J_ProfileMan_EventScript_CreateProfile
	case 1, J_ProfileMan_EventScript_DeclineShowProfile
	case 2, J_ProfileMan_EventScript_Info
	case 127, J_ProfileMan_EventScript_DeclineShowProfile
	end

J_ProfileMan_EventScript_Info::
	msgbox J_ProfileMan_Text_EasyChatExplanation, MSGBOX_DEFAULT
	goto J_ProfileMan_EventScript_AskToSeeProfile
	end

J_ProfileMan_EventScript_CreateProfile::
	msgbox J_ProfileMan_Text_LetsSeeItThen, MSGBOX_DEFAULT
	closemessage
	setvar 32772, 0
	call J_Common_ShowEasyChatScreen
	lock
	faceplayer
	goto_if_eq 32781, 0, J_ProfileMan_EventScript_CancelShowProfile
	goto_if_eq 32781, 1, J_ProfileMan_EventScript_ShowProfile
	end

J_ProfileMan_EventScript_CancelShowProfile::
	msgbox J_ProfileMan_Text_NotIntoItRightNow, MSGBOX_DEFAULT
	release
	end

J_ProfileMan_EventScript_ShowProfile::
	setvar 32772, 0
	special ShowEasyChatProfile
	waitmessage
	delay 80
	msgbox J_ProfileMan_Text_FantasticProfile, MSGBOX_DEFAULT
	release
	end

J_ProfileMan_EventScript_DeclineShowProfile::
	msgbox J_ProfileMan_Text_ImagineYouWouldHaveWonderfulProfile, MSGBOX_DEFAULT
	release
	end

J_ProfileMan_EventScript_GivenProfileBefore::
	msgbox J_ProfileMan_Text_YouHaveWonderfulSmile, MSGBOX_DEFAULT
	goto J_ProfileMan_EventScript_AskToSeeNewProfile
	end

J_ProfileMan_EventScript_AskToSeeNewProfile::
	msgbox J_ProfileMan_Text_MayISeeYourNewProfile, MSGBOX_DEFAULT
	multichoice 17, 6, 20, FALSE
	switch 32781
	case 0, J_ProfileMan_EventScript_CreateNewProfile
	case 1, J_ProfileMan_EventScript_DeclineNewProfile
	case 2, J_ProfileMan_EventScript_InfoNewProfile
	case 127, J_ProfileMan_EventScript_DeclineNewProfile
	end

J_ProfileMan_EventScript_InfoNewProfile::
	msgbox J_ProfileMan_Text_EasyChatExplanation, MSGBOX_DEFAULT
	goto J_ProfileMan_EventScript_AskToSeeNewProfile
	end

J_ProfileMan_EventScript_CreateNewProfile::
	msgbox J_ProfileMan_Text_EvenBetterThanLastProfile, MSGBOX_DEFAULT
	closemessage
	setvar 32772, 0
	call J_Common_ShowEasyChatScreen
	lock
	faceplayer
	goto_if_eq 32781, 0, J_ProfileMan_EventScript_CancelShowProfile
	goto_if_eq 32781, 1, J_ProfileMan_EventScript_ShowProfile
	end

J_ProfileMan_EventScript_DeclineNewProfile::
	msgbox J_ProfileMan_Text_LikeProfileWayItIs, MSGBOX_DEFAULT
	release
	end

J_ProfileMan_EventScript_Ret::
	return

J_ProfileMan_Text_CollectTrainerProfiles:
	.string "Hell{SE_M_ATTRACT2}there{SE_M_SUPERSONIC}TRAINER!\n"
	.string "You'v{SE_M_REVERSAL}go{SE_M_SPIT_UP}{SE_M_CHARGE}wonderfu{SE_M_BATON_PASS}smile{SE_M_SUPERSONIC}there.\p"
	.string "{SE_M_HEAL_BELL}hav{SE_M_REVERSAL}{SE_M_CHARGE}hobby--collectin{SE_M_SANDSTORM}th{SE_M_REVERSAL}profiles\n"
	.string "o{SE_M_ACID_ARMOR}POKéMO{SE_M_PSYBEAM2}TRAINERS.$"

J_ProfileMan_Text_MayISeeYourProfile:
	.string "So{SE_M_SUPERSONIC}ho{SE_M_TWISTER}abou{SE_M_SPIT_UP}it?\n"
	.string "Ma{SE_M_YAWN}{SE_M_HEAL_BELL}se{SE_M_REVERSAL}you{SE_M_SAND_TOMB}profile?$"

J_ProfileMan_Text_EasyChatExplanation:
	.string "Yo{SE_M_DIVE}mak{SE_M_REVERSAL}you{SE_M_SAND_TOMB}ow{SE_M_ATTRACT}profil{SE_M_REVERSAL}b{SE_M_YAWN}putting\n"
	.string "togethe{SE_M_SAND_TOMB}fou{SE_M_SAND_TOMB}word{SE_M_GRASSWHISTLE}o{SE_M_SAND_TOMB}phrases.\p"
	.string "Here{SE_M_SUPERSONIC}I'l{SE_M_BATON_PASS}sho{SE_M_TWISTER}yo{SE_M_DIVE}a{SE_M_ATTRACT}exampl{SE_M_REVERSAL}o{SE_M_ACID_ARMOR}a\n"
	.string "profil{SE_M_REVERSAL}usin{SE_M_SANDSTORM}fou{SE_M_SAND_TOMB}piece{SE_M_GRASSWHISTLE}o{SE_M_ACID_ARMOR}text.\p"
	.string "Yo{SE_M_DIVE}ca{SE_M_ATTRACT}switc{SE_M_TRI_ATTACK}thos{SE_M_REVERSAL}fou{SE_M_SAND_TOMB}piece{SE_M_GRASSWHISTLE}with\n"
	.string "othe{SE_M_SAND_TOMB}tex{SE_M_SPIT_UP}piece{SE_M_GRASSWHISTLE}an{SE_M_YAWN}whic{SE_M_TRI_ATTACK}wa{SE_M_YAWN}you\l"
	.string "lik{SE_M_REVERSAL}t{SE_M_ATTRACT2}mak{SE_M_REVERSAL}you{SE_M_SAND_TOMB}ow{SE_M_ATTRACT}profile.\p"
	.string "Ther{SE_M_REVERSAL}ar{SE_M_REVERSAL}{SE_M_CHARGE}lo{SE_M_SPIT_UP}o{SE_M_ACID_ARMOR}tex{SE_M_SPIT_UP}piece{SE_M_GRASSWHISTLE}that\n"
	.string "yo{SE_M_DIVE}ca{SE_M_ATTRACT}use.\p"
	.string "The{SE_M_YAWN}ar{SE_M_REVERSAL}arrange{SE_M_WATERFALL}i{SE_M_ATTRACT}group{SE_M_GRASSWHISTLE}like\n"
	.string "POKéMON{SE_M_SUPERSONIC}lifestyles{SE_M_SUPERSONIC}an{SE_M_WATERFALL}hobbie{SE_M_GRASSWHISTLE}so\l"
	.string "i{SE_M_SPIT_UP}i{SE_M_GRASSWHISTLE}easie{SE_M_SAND_TOMB}t{SE_M_ATTRACT2}loo{SE_M_ENCORE2}the{SE_M_MILK_DRINK}up.\p"
	.string "So{SE_M_SUPERSONIC}first{SE_M_SUPERSONIC}choos{SE_M_REVERSAL}th{SE_M_REVERSAL}grou{SE_M_MORNING_SUN}o{SE_M_ACID_ARMOR}text\n"
	.string "piece{SE_M_GRASSWHISTLE}t{SE_M_ATTRACT2}displa{SE_M_YAWN}{SE_M_CHARGE}lis{SE_M_SPIT_UP}o{SE_M_ACID_ARMOR}choices.\p"
	.string "Then{SE_M_SUPERSONIC}pic{SE_M_ENCORE2}th{SE_M_REVERSAL}choic{SE_M_REVERSAL}yo{SE_M_DIVE}want.\p"
	.string "Repea{SE_M_SPIT_UP}fo{SE_M_SAND_TOMB}th{SE_M_REVERSAL}remainin{SE_M_SANDSTORM}tex{SE_M_SPIT_UP}choices,\n"
	.string "an{SE_M_WATERFALL}you'l{SE_M_BATON_PASS}hav{SE_M_REVERSAL}you{SE_M_SAND_TOMB}ver{SE_M_YAWN}ow{SE_M_ATTRACT}profile.$"

J_ProfileMan_Text_LetsSeeItThen:
	.string "Yes{SE_M_DRAGON_RAGE}Than{SE_M_ENCORE2}you!\n"
	.string "So{SE_M_SUPERSONIC}let'{SE_M_GRASSWHISTLE}se{SE_M_REVERSAL}it{SE_M_SUPERSONIC}then.$"

J_ProfileMan_Text_ImagineYouWouldHaveWonderfulProfile:
	.string "Oh{SE_M_SUPERSONIC}no{SE_M_SUPERSONIC}really?\p"
	.string "{SE_M_HEAL_BELL}imagin{SE_M_REVERSAL}someon{SE_M_REVERSAL}lik{SE_M_REVERSAL}yo{SE_M_DIVE}woul{SE_M_WATERFALL}have\n"
	.string "{SE_M_CHARGE}wonderfu{SE_M_BATON_PASS}profile…$"

J_ProfileMan_Text_NotIntoItRightNow:
	.string "Oh{SE_M_SING}You'r{SE_M_REVERSAL}no{SE_M_SPIT_UP}int{SE_M_ATTRACT2}i{SE_M_SPIT_UP}righ{SE_M_SPIT_UP}now?\p"
	.string "Well{SE_M_SUPERSONIC}anytim{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}goo{SE_M_WATERFALL}b{SE_M_YAWN}me!$"

J_ProfileMan_Text_YouHaveWonderfulSmile:
	.string "Hell{SE_M_ATTRACT2}there{SE_M_SUPERSONIC}TRAINER!\n"
	.string "You'v{SE_M_REVERSAL}go{SE_M_SPIT_UP}{SE_M_CHARGE}wonderfu{SE_M_BATON_PASS}smile.$"

J_ProfileMan_Text_MayISeeYourNewProfile:
	.string "Ma{SE_M_YAWN}{SE_M_HEAL_BELL}se{SE_M_REVERSAL}you{SE_M_SAND_TOMB}ne{SE_M_TWISTER}profile?$"

J_ProfileMan_Text_EvenBetterThanLastProfile:
	.string "Yes{SE_M_DRAGON_RAGE}Than{SE_M_ENCORE2}you!\p"
	.string "{SE_M_HEAL_BELL}hop{SE_M_REVERSAL}it'{SE_M_GRASSWHISTLE}eve{SE_M_ATTRACT}bette{SE_M_SAND_TOMB}tha{SE_M_ATTRACT}th{SE_M_REVERSAL}profile\n"
	.string "yo{SE_M_DIVE}showe{SE_M_WATERFALL}m{SE_M_REVERSAL}before.$"

J_ProfileMan_Text_LikeProfileWayItIs:
	.string "Oh{SE_M_SUPERSONIC}yo{SE_M_DIVE}lik{SE_M_REVERSAL}you{SE_M_SAND_TOMB}profil{SE_M_REVERSAL}th{SE_M_REVERSAL}wa{SE_M_YAWN}i{SE_M_SPIT_UP}is.\p"
	.string "{SE_M_HEAL_BELL}don'{SE_M_SPIT_UP}blam{SE_M_REVERSAL}you--it'{SE_M_GRASSWHISTLE}{SE_M_CHARGE}wonderful\n"
	.string "profil{SE_M_REVERSAL}th{SE_M_REVERSAL}wa{SE_M_YAWN}i{SE_M_SPIT_UP}i{SE_M_GRASSWHISTLE}now.$"

J_ProfileMan_Text_FantasticProfile:
	.string "F-fantastic!\p"
	.string "You{SE_M_SAND_TOMB}profile{SE_M_SUPERSONIC}it'{SE_M_GRASSWHISTLE}wonderful!\n"
	.string "I{SE_M_SPIT_UP}reall{SE_M_YAWN}say{SE_M_GRASSWHISTLE}wha{SE_M_SPIT_UP}you'r{SE_M_REVERSAL}about.\p"
	.string "Why{SE_M_SUPERSONIC}anyon{SE_M_REVERSAL}hearin{SE_M_SANDSTORM}thi{SE_M_GRASSWHISTLE}profil{SE_M_REVERSAL}would\n"
	.string "b{SE_M_REVERSAL}captivate{SE_M_WATERFALL}b{SE_M_YAWN}you!\p"
	.string "Than{SE_M_ENCORE2}you!$"

J_ProfileMan_Text_YouKnowSecretSaying:
	.string "Oh?\n"
	.string "Yo{SE_M_DIVE}kno{SE_M_TWISTER}th{SE_M_REVERSAL}secre{SE_M_SPIT_UP}saying!\p"
	.string "Tha{SE_M_SPIT_UP}mean{SE_M_GRASSWHISTLE}you'r{SE_M_REVERSAL}no{SE_M_TWISTER}{SE_M_CHARGE}fello{SE_M_TWISTER}member\n"
	.string "o{SE_M_ACID_ARMOR}th{SE_M_REVERSAL}MYSTER{SE_M_MOONLIGHT}EVEN{SE_M_SWIFT}CLUB!$"

