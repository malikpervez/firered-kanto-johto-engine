@ Johto (data/scripts/move_tutors.inc), as built into the FireRed game.

J_SlateportCity_PokemonFanClub_EventScript_SwaggerTutor::
	lock
	faceplayer
	move_tutor MOVE_SWAGGER, J_MoveTutor_Text_SwaggerTeach, J_MoveTutor_Text_SwaggerWhichMon, J_MoveTutor_EventScript_SwaggerDeclined, J_MoveTutor_EventScript_SwaggerTaught, 0
	release
	end

J_MoveTutor_EventScript_SwaggerDeclined::
	msgbox J_MoveTutor_Text_SwaggerDeclined, MSGBOX_DEFAULT
	release
	end

J_MoveTutor_EventScript_SwaggerTaught::
	msgbox J_MoveTutor_Text_SwaggerTaught, MSGBOX_DEFAULT
	release
	end

J_MauvilleCity_EventScript_RolloutTutor::
	lock
	faceplayer
	move_tutor MOVE_ROLLOUT, J_MoveTutor_Text_RolloutTeach, J_MoveTutor_Text_RolloutWhichMon, J_MoveTutor_EventScript_RolloutDeclined, J_MoveTutor_EventScript_RolloutTaught, 0
	release
	end

J_MoveTutor_EventScript_RolloutDeclined::
	msgbox J_MoveTutor_Text_RolloutDeclined, MSGBOX_DEFAULT
	release
	end

J_MoveTutor_EventScript_RolloutTaught::
	msgbox J_MoveTutor_Text_RolloutTaught, MSGBOX_DEFAULT
	release
	end

J_VerdanturfTown_PokemonCenter_1F_EventScript_FuryCutterTutor::
	lock
	faceplayer
	move_tutor MOVE_FURY_CUTTER, J_MoveTutor_Text_FuryCutterTeach, J_MoveTutor_Text_FuryCutterWhichMon, J_MoveTutor_EventScript_FuryCutterDeclined, J_MoveTutor_EventScript_FuryCutterTaught, 0
	end

J_MoveTutor_EventScript_FuryCutterDeclined::
	msgbox J_MoveTutor_Text_FuryCutterDeclined, MSGBOX_DEFAULT
	release
	end

J_MoveTutor_EventScript_FuryCutterTaught::
	msgbox J_MoveTutor_Text_FuryCutterTaught, MSGBOX_DEFAULT
	release
	end

J_LavaridgeTown_House_EventScript_MimicTutor::
	lock
	faceplayer
	move_tutor MOVE_MIMIC, J_MoveTutor_MimicTeach, J_MoveTutor_Text_MimicWhichMon, J_MoveTutor_EventScript_MimicDeclined, J_MoveTutor_EventScript_MimicTaught, 0
	end

J_MoveTutor_EventScript_MimicDeclined::
	msgbox J_MoveTutor_MimicDeclined, MSGBOX_DEFAULT
	release
	end

J_MoveTutor_EventScript_MimicTaught::
	msgbox J_MoveTutor_Text_MimicTaught, MSGBOX_DEFAULT
	release
	end

J_FallarborTown_Mart_EventScript_MetronomeTutor::
	lock
	faceplayer
	move_tutor MOVE_METRONOME, J_MoveTutor_Text_MetronomeTeach, J_MoveTutor_Text_MetronomeWhichMon, J_MoveTutor_EventScript_MetronomeDeclined, J_MoveTutor_EventScript_MetronomeTaught, 0
	end

J_MoveTutor_EventScript_MetronomeDeclined::
	msgbox J_MoveTutor_Text_MetronomeDeclined, MSGBOX_DEFAULT
	release
	end

J_MoveTutor_EventScript_MetronomeTaught::
	msgbox J_MoveTutor_Text_MetronomeTaught, MSGBOX_DEFAULT
	release
	end

J_FortreeCity_House2_EventScript_SleepTalkTutor::
	lock
	faceplayer
	move_tutor MOVE_SLEEP_TALK, J_MoveTutor_Text_SleepTalkTeach, J_MoveTutor_Text_SleepTalkWhichMon, J_MoveTutor_EventScript_SleepTalkDeclined, J_MoveTutor_EventScript_SleepTalkTaught, 0
	end

J_MoveTutor_EventScript_SleepTalkDeclined::
	msgbox J_MoveTutor_Text_SleepTalkDeclined, MSGBOX_DEFAULT
	release
	end

J_MoveTutor_EventScript_SleepTalkTaught::
	msgbox J_MoveTutor_Text_SleepTalkTaught, MSGBOX_DEFAULT
	release
	end

J_LilycoveCity_DepartmentStoreRooftop_EventScript_SubstituteTutor::
	lock
	faceplayer
	move_tutor MOVE_SUBSTITUTE, J_MoveTutor_Text_SubstituteTeach, J_MoveTutor_Text_SubstituteWhichMon, J_MoveTutor_EventScript_SubstituteDeclined, J_MoveTutor_EventScript_SubstituteTaught, 0
	end

J_MoveTutor_EventScript_SubstituteDeclined::
	msgbox J_MoveTutor_Text_SubstituteDeclined, MSGBOX_DEFAULT
	release
	end

J_MoveTutor_EventScript_SubstituteTaught::
	msgbox J_MoveTutor_Text_SubstituteTaught, MSGBOX_DEFAULT
	release
	end

J_MossdeepCity_EventScript_DynamicPunchTutor::
	lock
	faceplayer
	move_tutor MOVE_DYNAMIC_PUNCH, J_MoveTutor_Text_DynamicPunchTeach, J_MoveTutor_Text_DynamicPunchWhichMon, J_MoveTutor_EventScript_DynamicPunchDeclined, J_MoveTutor_EventScript_DynamicPunchTaught, 0
	end

J_MoveTutor_EventScript_DynamicPunchDeclined::
	msgbox J_MoveTutor_Text_DynamicPunchDeclined, MSGBOX_DEFAULT
	release
	end

J_MoveTutor_EventScript_DynamicPunchTaught::
	msgbox J_MoveTutor_Text_DynamicPunchTaught, MSGBOX_DEFAULT
	release
	end

J_SootopolisCity_PokemonCenter_1F_EventScript_DoubleEdgeTutor::
	lock
	faceplayer
	move_tutor MOVE_DOUBLE_EDGE, J_MoveTutor_Text_DoubleEdgeTeach, J_MoveTutor_Text_DoubleEdgeWhichMon, J_MoveTutor_EventScript_DoubleEdgeDeclined, J_MoveTutor_EventScript_DoubleEdgeTaught, 0
	end

J_MoveTutor_EventScript_DoubleEdgeDeclined::
	msgbox J_MoveTutor_Text_DoubleEdgeDeclined, MSGBOX_DEFAULT
	release
	end

J_MoveTutor_EventScript_DoubleEdgeTaught::
	msgbox J_MoveTutor_Text_DoubleEdgeTaught, MSGBOX_DEFAULT
	release
	end

J_PacifidlogTown_PokemonCenter_1F_EventScript_ExplosionTutor::
	lock
	faceplayer
	move_tutor MOVE_EXPLOSION, J_MoveTutor_Text_ExplosionTeach, J_MoveTutor_Text_ExplosionWhichMon, J_MoveTutor_EventScript_ExplosionDeclined, J_MoveTutor_EventScript_ExplosionTaught, 0
	end

J_MoveTutor_EventScript_ExplosionDeclined::
	msgbox J_MoveTutor_Text_ExplosionDeclined, MSGBOX_DEFAULT
	release
	end

J_MoveTutor_EventScript_ExplosionTaught::
	msgbox J_MoveTutor_Text_ExplosionTaught, MSGBOX_DEFAULT
	release
	end

J_IlexForest_EventScript_HeadbuttMoveTutor::
	lock
	faceplayer
	move_tutor MOVE_HEADBUTT, J_MoveTutor_Text_HeadbuttTeach, J_MoveTutor_Text_HeadbuttWhichMon, J_MoveTutor_EventScript_HeadbuttDeclined, J_MoveTutor_EventScript_HeadbuttTaught
	end

J_MoveTutor_EventScript_HeadbuttDeclined::
	msgbox J_MoveTutor_Text_HeadbuttDeclined, MSGBOX_DEFAULT
	release
	end

J_MoveTutor_EventScript_HeadbuttTaught::
	setflag 8704
	msgbox J_MoveTutor_Text_HeadbuttTaught, MSGBOX_DEFAULT
	release
	end

J_MoveTutor_EventScript_OpenPartyMenu::
	special ChooseMonForMoveTutor
	waitstate
	lock
	faceplayer
	return

J_MoveTutor_EventScript_OpenBox::
	chooseboxmon SELECT_PC_MON_MOVE_TUTOR
	waitstate
	lock
	faceplayer
	return

J_MoveTutor_EventScript_CanOnlyBeLearnedOnce::
	msgbox J_MoveTutor_Text_ThisMoveCanOnlyBeLearnedOnce, MSGBOX_YESNO
	return

J_MoveTutor_AfterChooseBoxMon::
	waitstate
	special CanTeachMoveBoxMon
	waitstate
	return

