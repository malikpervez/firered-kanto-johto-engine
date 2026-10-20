@ Johto (data/maps/Route46_hns/scripts.inc), as built into the FireRed game.

Route46_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route29_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, J_SetTimeEncounters
	.byte 0

Route46_OnTransition:
	callnative SetTimeBasedEncounters
	end

Route46_EventScript_Bailey::
	trainerbattle_single TRAINER_JOHTO_BAILEY_HNS, Route46_Text_HikerBaileySeen, Route46_Text_HikerBaileyBeaten
	msgbox Route46_Text_HikerBaileyAfterBattle, MSGBOX_AUTOCLOSE
	end

Route46_EventScript_Ted::
	trainerbattle_single TRAINER_JOHTO_TED_HNS, Route46_Text_CamperTedSeen, Route46_Text_CamperTedBeaten
	msgbox Route46_Text_CamperTedAfterBattle, MSGBOX_AUTOCLOSE
	end

Route46_EventScript_Erin::
	trainerbattle_single TRAINER_JOHTO_ERIN_HNS, Route46_Text_PicnickerErinSeen, Route46_Text_PicnickerErinBeaten, Route46_EventScript_RegisterErin
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route46_EventScript_RematchErin
	msgbox Route46_Text_PicnickerErinAfterBattle, MSGBOX_AUTOCLOSE
	end

Route46_EventScript_RegisterErin::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route46_Text_ErinRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_JOHTO_ERIN_HNS
	release
	end

Route46_EventScript_RematchErin::
	trainerbattle_rematch TRAINER_JOHTO_ERIN_HNS, Route46_Text_ErinRematchIntro, Route46_Text_ErinRematchDefeat
	msgbox Route46_Text_ErinPostRematch, MSGBOX_AUTOCLOSE
	end

Route46_EventScript_Sign::
	lock
	msgbox Route46_Text_Sign, MSGBOX_SIGN
	closemessage
	release
	end

Route46_EventScript_Item_Revive::
	finditem ITEM_REVIVE
	end

Route46_Text_HikerBaileySeen:
	.string "Awright{SE_M_DRAGON_RAGE}I'l{SE_M_BATON_PASS}sho{SE_M_TWISTER}yo{SE_M_DIVE}the\n"
	.string "powe{SE_M_SAND_TOMB}o{SE_M_ACID_ARMOR}mountai{SE_M_ATTRACT}POKéMON!$"

Route46_Text_HikerBaileyBeaten:
	.string "Mercy{SE_M_DRAGON_RAGE}Yo{SE_M_DIVE}showe{SE_M_WATERFALL}m{SE_M_REVERSAL}your\n"
	.string "power!$"

Route46_Text_HikerBaileyAfterBattle:
	.string "It'{SE_M_GRASSWHISTLE}over{SE_M_PERISH_SONG}{SE_M_HEAL_BELL}don'{SE_M_SPIT_UP}mind.\n"
	.string "W{SE_M_REVERSAL}HIKER{SE_M_SKETCH}ar{SE_M_REVERSAL}lik{SE_M_REVERSAL}that.$"

Route46_Text_CamperTedSeen:
	.string "I'{SE_M_MILK_DRINK}raisin{SE_M_SANDSTORM}POKéMO{SE_M_PSYBEAM2}too!\p"
	.string "Wil{SE_M_BATON_PASS}yo{SE_M_DIVE}battl{SE_M_REVERSAL}wit{SE_M_TRI_ATTACK}me?$"

Route46_Text_CamperTedBeaten:
	.string "Wha…?$"

Route46_Text_CamperTedAfterBattle:
	.string "{SE_M_HEAL_BELL}di{SE_M_WATERFALL}m{SE_M_YAWN}bes{SE_M_SPIT_UP}bu{SE_M_SPIT_UP}cam{SE_M_REVERSAL}up\n"
	.string "short.\p"
	.string "N{SE_M_ATTRACT2}excuses--{SE_M_HEAL_BELL}admi{SE_M_SPIT_UP}{SE_M_HEAL_BELL}lost.$"

Route46_Text_PicnickerErinSeen:
	.string "{SE_M_HEAL_BELL}rais{SE_M_REVERSAL}POKéMO{SE_M_PSYBEAM2}too!\p"
	.string "Wil{SE_M_BATON_PASS}yo{SE_M_DIVE}battl{SE_M_REVERSAL}wit{SE_M_TRI_ATTACK}me?$"

Route46_Text_PicnickerErinBeaten:
	.string "Oh{SE_M_SUPERSONIC}rats!$"

Route46_Text_PicnickerErinAfterBattle:
	.string "I'v{SE_M_REVERSAL}bee{SE_M_ATTRACT}t{SE_M_ATTRACT2}man{SE_M_YAWN}GYMS{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}the\n"
	.string "GY{SE_M_GIGA_DRAIN}i{SE_M_ATTRACT}GOLDENRO{SE_M_FAINT_ATTACK}i{SE_M_GRASSWHISTLE}m{SE_M_YAWN}favorite.\p"
	.string "It'{SE_M_GRASSWHISTLE}fille{SE_M_WATERFALL}wit{SE_M_TRI_ATTACK}prett{SE_M_YAWN}flowers!$"

Route46_Text_ErinRegister:
	.string "I'v{SE_M_REVERSAL}bee{SE_M_ATTRACT}t{SE_M_ATTRACT2}man{SE_M_YAWN}GYMS{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}the\n"
	.string "GY{SE_M_GIGA_DRAIN}i{SE_M_ATTRACT}GOLDENRO{SE_M_FAINT_ATTACK}i{SE_M_GRASSWHISTLE}m{SE_M_YAWN}favorite.\p"
	.string "It'{SE_M_GRASSWHISTLE}fille{SE_M_WATERFALL}wit{SE_M_TRI_ATTACK}prett{SE_M_YAWN}flowers!$"

Route46_Text_ErinRematchIntro:
	.string "{SE_M_HEAL_BELL}rais{SE_M_REVERSAL}POKéMO{SE_M_PSYBEAM2}too!\p"
	.string "Wil{SE_M_BATON_PASS}yo{SE_M_DIVE}battl{SE_M_REVERSAL}wit{SE_M_TRI_ATTACK}me?$"

Route46_Text_ErinRematchDefeat:
	.string "Oh{SE_M_SUPERSONIC}rats!$"

Route46_Text_ErinPostRematch:
	.string "I'v{SE_M_REVERSAL}bee{SE_M_ATTRACT}t{SE_M_ATTRACT2}man{SE_M_YAWN}GYMS{SE_M_SUPERSONIC}bu{SE_M_SPIT_UP}the\n"
	.string "GY{SE_M_GIGA_DRAIN}i{SE_M_ATTRACT}GOLDENRO{SE_M_FAINT_ATTACK}i{SE_M_GRASSWHISTLE}m{SE_M_YAWN}favorite.\p"
	.string "It'{SE_M_GRASSWHISTLE}fille{SE_M_WATERFALL}wit{SE_M_TRI_ATTACK}prett{SE_M_YAWN}flowers!$"

Route46_Text_PicnickerErin2Beaten:
	.string "Aww{SE_M_DIZZY_PUNCH}{SE_M_HEAL_BELL}kee{SE_M_MORNING_SUN}losin{SE_M_SANDSTORM}al{SE_M_BATON_PASS}th{SE_M_REVERSAL}time!\p"
	.string "I'l{SE_M_BATON_PASS}jus{SE_M_SPIT_UP}hav{SE_M_REVERSAL}t{SE_M_ATTRACT2}tr{SE_M_YAWN}harder!\n"
	.string "Anyway{SE_M_SUPERSONIC}thank{SE_M_GRASSWHISTLE}fo{SE_M_SAND_TOMB}battling\n"
	.string "m{SE_M_REVERSAL}agai{SE_M_ATTRACT}an{SE_M_WATERFALL}again.\p"
	.string "Here'{SE_M_GRASSWHISTLE}tha{SE_M_SPIT_UP}presen{SE_M_SPIT_UP}fro{SE_M_MILK_DRINK}the\n"
	.string "othe{SE_M_SAND_TOMB}time.$"

Route46_Text_Sign:
	.string "ROUT{SE_M_SWORDS_DANCE}46\n"
	.string "MOUNTAI{SE_M_PSYBEAM2}RD{SE_M_PERISH_SONG}AHEAD$"

