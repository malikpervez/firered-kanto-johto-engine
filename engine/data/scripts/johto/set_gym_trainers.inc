@ Johto (data/scripts/set_gym_trainers.inc), as built into the FireRed game.

J_Common_EventScript_SetGymTrainers::
	switch 32776
	case 1, J_RustboroCity_Gym_SetGymTrainers
	case 2, J_DewfordTown_Gym_SetGymTrainers
	case 3, J_MauvilleCity_Gym_SetGymTrainers
	case 4, J_LavaridgeTown_Gym_SetGymTrainers
	case 5, J_PetalburgCity_Gym_SetGymTrainers
	case 6, J_FortreeCity_Gym_SetGymTrainers
	case 7, J_MossdeepCity_Gym_SetGymTrainers
	case 8, J_SootopolisCity_Gym_SetGymTrainers
	end

J_Common_EventScript_SetGymTrainers_Frlg::
	switch 32776
	case 1, J_EventScript_SetPewterGymTrainers
	case 2, J_EventScript_SetCeruleanGymTrainers
	case 3, J_EventScript_SetVermilionGymTrainers
	case 4, J_EventScript_SetCeladonGymTrainers
	case 5, J_EventScript_SetFuchsiaGymTrainers
	case 6, J_EventScript_SetSaffronGymTrainers
	case 7, J_EventScript_SetCinnabarGymTrainers
	case 8, J_EventScript_SetViridianGymTrainers
	end

J_RustboroCity_Gym_SetGymTrainers::
	settrainerflag 320
	settrainerflag 321
	settrainerflag 571
	return

J_DewfordTown_Gym_SetGymTrainers::
	settrainerflag 179
	settrainerflag 425
	settrainerflag 426
	settrainerflag 572
	settrainerflag 574
	settrainerflag 573
	return

J_MauvilleCity_Gym_SetGymTrainers::
	settrainerflag 191
	settrainerflag 194
	settrainerflag 323
	settrainerflag 649
	settrainerflag 802
	return

J_LavaridgeTown_Gym_SetGymTrainers::
	settrainerflag 201
	settrainerflag 203
	settrainerflag 205
	settrainerflag 648
	settrainerflag 650
	settrainerflag 204
	settrainerflag 202
	settrainerflag 501
	return

J_PetalburgCity_Gym_SetGymTrainers::
	settrainerflag 71
	settrainerflag 72
	settrainerflag 73
	settrainerflag 74
	settrainerflag 89
	settrainerflag 90
	settrainerflag 91
	return

J_FortreeCity_Gym_SetGymTrainers::
	settrainerflag 401
	settrainerflag 654
	settrainerflag 655
	settrainerflag 404
	settrainerflag 402
	settrainerflag 803
	return

J_MossdeepCity_Gym_SetGymTrainers::
	settrainerflag 233
	settrainerflag 234
	settrainerflag 235
	settrainerflag 244
	settrainerflag 245
	settrainerflag 246
	settrainerflag 575
	settrainerflag 582
	settrainerflag 583
	settrainerflag 584
	settrainerflag 591
	settrainerflag 585
	return

J_SootopolisCity_Gym_SetGymTrainers::
	settrainerflag 613
	settrainerflag 614
	settrainerflag 118
	settrainerflag 128
	settrainerflag 129
	settrainerflag 130
	settrainerflag 131
	settrainerflag 301
	settrainerflag 502
	settrainerflag 115
	return

J_EventScript_SetPewterGymTrainers::
	settrainerflag 52
	return

J_EventScript_SetCeruleanGymTrainers::
	settrainerflag 59
	settrainerflag 135
	return

J_EventScript_SetVermilionGymTrainers::
	settrainerflag 51
	settrainerflag 121
	settrainerflag 323
	return

J_EventScript_SetCeladonGymTrainers::
	settrainerflag 42
	settrainerflag 43
	settrainerflag 69
	settrainerflag 165
	settrainerflag 166
	settrainerflag 167
	settrainerflag 302
	return

J_EventScript_SetFuchsiaGymTrainers::
	settrainerflag 194
	settrainerflag 195
	settrainerflag 188
	settrainerflag 189
	settrainerflag 192
	settrainerflag 193
	return

J_EventScript_SetSaffronGymTrainers::
	settrainerflag 180
	settrainerflag 181
	settrainerflag 182
	settrainerflag 183
	settrainerflag 354
	settrainerflag 355
	settrainerflag 356
	return

J_EventScript_SetCinnabarGymTrainers::
	settrainerflag 83
	settrainerflag 84
	settrainerflag 85
	settrainerflag 86
	settrainerflag 115
	settrainerflag 116
	settrainerflag 117
	return

J_EventScript_SetViridianGymTrainers::
	settrainerflag 196
	settrainerflag 197
	settrainerflag 222
	settrainerflag 223
	settrainerflag 224
	settrainerflag 292
	settrainerflag 300
	settrainerflag 301
	return

J_Common_EventScript_SetGymTrainers_hns::
	switch 32776
	case 1, J_VioletCity_Gym_SetGymTrainers_hns
	case 2, J_AzaleaTown_Gym_SetGymTrainers_hns
	case 3, J_GoldenrodCity_Gym_SetGymTrainers_hns
	case 4, J_EcruteakCity_Gym_SetGymTrainers_hns
	case 5, J_CianwoodCity_Gym_SetGymTrainers_hns
	case 6, J_OlivineCity_Gym_SetGymTrainers_hns
	case 7, J_MahoganyTown_Gym_SetGymTrainers_hns
	case 8, J_BlackthornCity_Gym_SetGymTrainers_hns
	case 9, J_PewterCity_Gym_SetGymTrainers_hns
	case 10, J_CeruleanCity_Gym_SetGymTrainers_hns
	case 11, J_VermilionCity_Gym_SetGymTrainers_hns
	case 12, J_CeladonCity_Gym_SetGymTrainers_hns
	case 13, J_SaffronCity_Gym_SetGymTrainers_hns
	case 14, J_FuchsiaCity_Gym_SetGymTrainers_hns
	case 15, J_CinnabarIsland_Gym_SetGymTrainers_hns
	case 16, J_ViridianCity_Gym_SetGymTrainers_hns
	end

J_VioletCity_Gym_SetGymTrainers_hns::
	settrainerflag 1053
	settrainerflag 1054
	return

J_AzaleaTown_Gym_SetGymTrainers_hns::
	settrainerflag 1193
	settrainerflag 1194
	settrainerflag 1195
	settrainerflag 1413
	return

J_GoldenrodCity_Gym_SetGymTrainers_hns::
	settrainerflag 1068
	settrainerflag 1069
	settrainerflag 1114
	settrainerflag 1115
	return

J_EcruteakCity_Gym_SetGymTrainers_hns::
	settrainerflag 1378
	settrainerflag 1379
	settrainerflag 1386
	settrainerflag 1387
	return

J_CianwoodCity_Gym_SetGymTrainers_hns::
	settrainerflag 1324
	settrainerflag 1325
	settrainerflag 1326
	settrainerflag 1328
	return

J_OlivineCity_Gym_SetGymTrainers_hns::
	return

J_MahoganyTown_Gym_SetGymTrainers_hns::
	settrainerflag 1184
	settrainerflag 1393
	settrainerflag 1185
	settrainerflag 1394
	settrainerflag 1395
	return

J_BlackthornCity_Gym_SetGymTrainers_hns::
	settrainerflag 1083
	settrainerflag 1081
	settrainerflag 1100
	settrainerflag 1082
	settrainerflag 1099
	return

J_PewterCity_Gym_SetGymTrainers_hns::
	settrainerflag 1370
	return

J_CeruleanCity_Gym_SetGymTrainers_hns::
	settrainerflag 1254
	settrainerflag 1255
	settrainerflag 1236
	return

J_VermilionCity_Gym_SetGymTrainers_hns::
	settrainerflag 1181
	settrainerflag 1281
	settrainerflag 1322
	return

J_CeladonCity_Gym_SetGymTrainers_hns::
	settrainerflag 1076
	settrainerflag 1642
	settrainerflag 1127
	settrainerflag 1415
	return

J_SaffronCity_Gym_SetGymTrainers_hns::
	settrainerflag 1391
	settrainerflag 1331
	settrainerflag 1392
	settrainerflag 1340
	return

J_FuchsiaCity_Gym_SetGymTrainers_hns::
	settrainerflag 1070
	settrainerflag 1073
	settrainerflag 1346
	settrainerflag 1359
	return

J_CinnabarIsland_Gym_SetGymTrainers_hns::
	return

J_ViridianCity_Gym_SetGymTrainers_hns::
	return

