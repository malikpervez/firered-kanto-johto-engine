#include "global.h"
#include "save.h"
unsigned int b0_SaveBlock1_total = sizeof(struct SaveBlock1);
unsigned int b0_SaveBlock1_align = __alignof__(struct SaveBlock1);
unsigned int b0_SaveBlock1_offset_saveVersion = __builtin_offsetof(struct SaveBlock1, saveVersion);
unsigned int b0_SaveBlock1_size_saveVersion = sizeof(((struct SaveBlock1 *)0)->saveVersion);
unsigned int b0_SaveBlock1_offset_pos = __builtin_offsetof(struct SaveBlock1, pos);
unsigned int b0_SaveBlock1_size_pos = sizeof(((struct SaveBlock1 *)0)->pos);
unsigned int b0_SaveBlock1_offset_location = __builtin_offsetof(struct SaveBlock1, location);
unsigned int b0_SaveBlock1_size_location = sizeof(((struct SaveBlock1 *)0)->location);
unsigned int b0_SaveBlock1_offset_continueGameWarp = __builtin_offsetof(struct SaveBlock1, continueGameWarp);
unsigned int b0_SaveBlock1_size_continueGameWarp = sizeof(((struct SaveBlock1 *)0)->continueGameWarp);
unsigned int b0_SaveBlock1_offset_dynamicWarp = __builtin_offsetof(struct SaveBlock1, dynamicWarp);
unsigned int b0_SaveBlock1_size_dynamicWarp = sizeof(((struct SaveBlock1 *)0)->dynamicWarp);
unsigned int b0_SaveBlock1_offset_lastHealLocation = __builtin_offsetof(struct SaveBlock1, lastHealLocation);
unsigned int b0_SaveBlock1_size_lastHealLocation = sizeof(((struct SaveBlock1 *)0)->lastHealLocation);
unsigned int b0_SaveBlock1_offset_escapeWarp = __builtin_offsetof(struct SaveBlock1, escapeWarp);
unsigned int b0_SaveBlock1_size_escapeWarp = sizeof(((struct SaveBlock1 *)0)->escapeWarp);
unsigned int b0_SaveBlock1_offset_savedMusic = __builtin_offsetof(struct SaveBlock1, savedMusic);
unsigned int b0_SaveBlock1_size_savedMusic = sizeof(((struct SaveBlock1 *)0)->savedMusic);
unsigned int b0_SaveBlock1_offset_weather = __builtin_offsetof(struct SaveBlock1, weather);
unsigned int b0_SaveBlock1_size_weather = sizeof(((struct SaveBlock1 *)0)->weather);
unsigned int b0_SaveBlock1_offset_weatherCycleStage = __builtin_offsetof(struct SaveBlock1, weatherCycleStage);
unsigned int b0_SaveBlock1_size_weatherCycleStage = sizeof(((struct SaveBlock1 *)0)->weatherCycleStage);
unsigned int b0_SaveBlock1_offset_flashLevel = __builtin_offsetof(struct SaveBlock1, flashLevel);
unsigned int b0_SaveBlock1_size_flashLevel = sizeof(((struct SaveBlock1 *)0)->flashLevel);
unsigned int b0_SaveBlock1_offset_mapLayoutId = __builtin_offsetof(struct SaveBlock1, mapLayoutId);
unsigned int b0_SaveBlock1_size_mapLayoutId = sizeof(((struct SaveBlock1 *)0)->mapLayoutId);
unsigned int b0_SaveBlock1_offset_mapView = __builtin_offsetof(struct SaveBlock1, mapView);
unsigned int b0_SaveBlock1_size_mapView = sizeof(((struct SaveBlock1 *)0)->mapView);
unsigned int b0_SaveBlock1_offset_playerPartyCount = __builtin_offsetof(struct SaveBlock1, playerPartyCount);
unsigned int b0_SaveBlock1_size_playerPartyCount = sizeof(((struct SaveBlock1 *)0)->playerPartyCount);
unsigned int b0_SaveBlock1_offset_playerParty = __builtin_offsetof(struct SaveBlock1, playerParty);
unsigned int b0_SaveBlock1_size_playerParty = sizeof(((struct SaveBlock1 *)0)->playerParty);
unsigned int b0_SaveBlock1_offset_money = __builtin_offsetof(struct SaveBlock1, money);
unsigned int b0_SaveBlock1_size_money = sizeof(((struct SaveBlock1 *)0)->money);
unsigned int b0_SaveBlock1_offset_coins = __builtin_offsetof(struct SaveBlock1, coins);
unsigned int b0_SaveBlock1_size_coins = sizeof(((struct SaveBlock1 *)0)->coins);
unsigned int b0_SaveBlock1_offset_registeredItem = __builtin_offsetof(struct SaveBlock1, registeredItem);
unsigned int b0_SaveBlock1_size_registeredItem = sizeof(((struct SaveBlock1 *)0)->registeredItem);
unsigned int b0_SaveBlock1_offset_pcItems = __builtin_offsetof(struct SaveBlock1, pcItems);
unsigned int b0_SaveBlock1_size_pcItems = sizeof(((struct SaveBlock1 *)0)->pcItems);
unsigned int b0_SaveBlock1_offset_bag = __builtin_offsetof(struct SaveBlock1, bag);
unsigned int b0_SaveBlock1_size_bag = sizeof(((struct SaveBlock1 *)0)->bag);
unsigned int b0_SaveBlock1_offset_pokeblocks = __builtin_offsetof(struct SaveBlock1, pokeblocks);
unsigned int b0_SaveBlock1_size_pokeblocks = sizeof(((struct SaveBlock1 *)0)->pokeblocks);
#if FREE_EXTRA_SEEN_FLAGS_SAVEBLOCK1 == FALSE
unsigned int b0_SaveBlock1_offset_filler1 = __builtin_offsetof(struct SaveBlock1, filler1);
unsigned int b0_SaveBlock1_size_filler1 = sizeof(((struct SaveBlock1 *)0)->filler1);
#endif
unsigned int b0_SaveBlock1_offset_berryBlenderRecords = __builtin_offsetof(struct SaveBlock1, berryBlenderRecords);
unsigned int b0_SaveBlock1_size_berryBlenderRecords = sizeof(((struct SaveBlock1 *)0)->berryBlenderRecords);
unsigned int b0_SaveBlock1_offset_saveVersionMagic = __builtin_offsetof(struct SaveBlock1, saveVersionMagic);
unsigned int b0_SaveBlock1_size_saveVersionMagic = sizeof(((struct SaveBlock1 *)0)->saveVersionMagic);
unsigned int b0_SaveBlock1_offset_unused_9C6 = __builtin_offsetof(struct SaveBlock1, unused_9C6);
unsigned int b0_SaveBlock1_size_unused_9C6 = sizeof(((struct SaveBlock1 *)0)->unused_9C6);
#if FREE_MATCH_CALL == FALSE
unsigned int b0_SaveBlock1_offset_trainerRematchStepCounter = __builtin_offsetof(struct SaveBlock1, trainerRematchStepCounter);
unsigned int b0_SaveBlock1_size_trainerRematchStepCounter = sizeof(((struct SaveBlock1 *)0)->trainerRematchStepCounter);
unsigned int b0_SaveBlock1_offset_trainerRematches = __builtin_offsetof(struct SaveBlock1, trainerRematches);
unsigned int b0_SaveBlock1_size_trainerRematches = sizeof(((struct SaveBlock1 *)0)->trainerRematches);
#endif
unsigned int b0_SaveBlock1_offset_objectEvents = __builtin_offsetof(struct SaveBlock1, objectEvents);
unsigned int b0_SaveBlock1_size_objectEvents = sizeof(((struct SaveBlock1 *)0)->objectEvents);
unsigned int b0_SaveBlock1_offset_objectEventTemplates = __builtin_offsetof(struct SaveBlock1, objectEventTemplates);
unsigned int b0_SaveBlock1_size_objectEventTemplates = sizeof(((struct SaveBlock1 *)0)->objectEventTemplates);
unsigned int b0_SaveBlock1_offset_flags = __builtin_offsetof(struct SaveBlock1, flags);
unsigned int b0_SaveBlock1_size_flags = sizeof(((struct SaveBlock1 *)0)->flags);
unsigned int b0_SaveBlock1_offset_vars = __builtin_offsetof(struct SaveBlock1, vars);
unsigned int b0_SaveBlock1_size_vars = sizeof(((struct SaveBlock1 *)0)->vars);
unsigned int b0_SaveBlock1_offset_gameStats = __builtin_offsetof(struct SaveBlock1, gameStats);
unsigned int b0_SaveBlock1_size_gameStats = sizeof(((struct SaveBlock1 *)0)->gameStats);
unsigned int b0_SaveBlock1_offset_berryTrees = __builtin_offsetof(struct SaveBlock1, berryTrees);
unsigned int b0_SaveBlock1_size_berryTrees = sizeof(((struct SaveBlock1 *)0)->berryTrees);
unsigned int b0_SaveBlock1_offset_secretBases = __builtin_offsetof(struct SaveBlock1, secretBases);
unsigned int b0_SaveBlock1_size_secretBases = sizeof(((struct SaveBlock1 *)0)->secretBases);
unsigned int b0_SaveBlock1_offset_playerRoomDecorations = __builtin_offsetof(struct SaveBlock1, playerRoomDecorations);
unsigned int b0_SaveBlock1_size_playerRoomDecorations = sizeof(((struct SaveBlock1 *)0)->playerRoomDecorations);
unsigned int b0_SaveBlock1_offset_playerRoomDecorationPositions = __builtin_offsetof(struct SaveBlock1, playerRoomDecorationPositions);
unsigned int b0_SaveBlock1_size_playerRoomDecorationPositions = sizeof(((struct SaveBlock1 *)0)->playerRoomDecorationPositions);
unsigned int b0_SaveBlock1_offset_decorationDesks = __builtin_offsetof(struct SaveBlock1, decorationDesks);
unsigned int b0_SaveBlock1_size_decorationDesks = sizeof(((struct SaveBlock1 *)0)->decorationDesks);
unsigned int b0_SaveBlock1_offset_decorationChairs = __builtin_offsetof(struct SaveBlock1, decorationChairs);
unsigned int b0_SaveBlock1_size_decorationChairs = sizeof(((struct SaveBlock1 *)0)->decorationChairs);
unsigned int b0_SaveBlock1_offset_decorationPlants = __builtin_offsetof(struct SaveBlock1, decorationPlants);
unsigned int b0_SaveBlock1_size_decorationPlants = sizeof(((struct SaveBlock1 *)0)->decorationPlants);
unsigned int b0_SaveBlock1_offset_decorationOrnaments = __builtin_offsetof(struct SaveBlock1, decorationOrnaments);
unsigned int b0_SaveBlock1_size_decorationOrnaments = sizeof(((struct SaveBlock1 *)0)->decorationOrnaments);
unsigned int b0_SaveBlock1_offset_decorationMats = __builtin_offsetof(struct SaveBlock1, decorationMats);
unsigned int b0_SaveBlock1_size_decorationMats = sizeof(((struct SaveBlock1 *)0)->decorationMats);
unsigned int b0_SaveBlock1_offset_decorationPosters = __builtin_offsetof(struct SaveBlock1, decorationPosters);
unsigned int b0_SaveBlock1_size_decorationPosters = sizeof(((struct SaveBlock1 *)0)->decorationPosters);
unsigned int b0_SaveBlock1_offset_decorationDolls = __builtin_offsetof(struct SaveBlock1, decorationDolls);
unsigned int b0_SaveBlock1_size_decorationDolls = sizeof(((struct SaveBlock1 *)0)->decorationDolls);
unsigned int b0_SaveBlock1_offset_decorationCushions = __builtin_offsetof(struct SaveBlock1, decorationCushions);
unsigned int b0_SaveBlock1_size_decorationCushions = sizeof(((struct SaveBlock1 *)0)->decorationCushions);
unsigned int b0_SaveBlock1_offset_tvShows = __builtin_offsetof(struct SaveBlock1, tvShows);
unsigned int b0_SaveBlock1_size_tvShows = sizeof(((struct SaveBlock1 *)0)->tvShows);
unsigned int b0_SaveBlock1_offset_pokeNews = __builtin_offsetof(struct SaveBlock1, pokeNews);
unsigned int b0_SaveBlock1_size_pokeNews = sizeof(((struct SaveBlock1 *)0)->pokeNews);
unsigned int b0_SaveBlock1_offset_outbreakPokemonSpecies = __builtin_offsetof(struct SaveBlock1, outbreakPokemonSpecies);
unsigned int b0_SaveBlock1_size_outbreakPokemonSpecies = sizeof(((struct SaveBlock1 *)0)->outbreakPokemonSpecies);
unsigned int b0_SaveBlock1_offset_outbreakLocationMapNum = __builtin_offsetof(struct SaveBlock1, outbreakLocationMapNum);
unsigned int b0_SaveBlock1_size_outbreakLocationMapNum = sizeof(((struct SaveBlock1 *)0)->outbreakLocationMapNum);
unsigned int b0_SaveBlock1_offset_outbreakLocationMapGroup = __builtin_offsetof(struct SaveBlock1, outbreakLocationMapGroup);
unsigned int b0_SaveBlock1_size_outbreakLocationMapGroup = sizeof(((struct SaveBlock1 *)0)->outbreakLocationMapGroup);
unsigned int b0_SaveBlock1_offset_outbreakPokemonLevel = __builtin_offsetof(struct SaveBlock1, outbreakPokemonLevel);
unsigned int b0_SaveBlock1_size_outbreakPokemonLevel = sizeof(((struct SaveBlock1 *)0)->outbreakPokemonLevel);
unsigned int b0_SaveBlock1_offset_outbreakUnused1 = __builtin_offsetof(struct SaveBlock1, outbreakUnused1);
unsigned int b0_SaveBlock1_size_outbreakUnused1 = sizeof(((struct SaveBlock1 *)0)->outbreakUnused1);
unsigned int b0_SaveBlock1_offset_outbreakUnused2 = __builtin_offsetof(struct SaveBlock1, outbreakUnused2);
unsigned int b0_SaveBlock1_size_outbreakUnused2 = sizeof(((struct SaveBlock1 *)0)->outbreakUnused2);
unsigned int b0_SaveBlock1_offset_outbreakPokemonMoves = __builtin_offsetof(struct SaveBlock1, outbreakPokemonMoves);
unsigned int b0_SaveBlock1_size_outbreakPokemonMoves = sizeof(((struct SaveBlock1 *)0)->outbreakPokemonMoves);
unsigned int b0_SaveBlock1_offset_outbreakUnused3 = __builtin_offsetof(struct SaveBlock1, outbreakUnused3);
unsigned int b0_SaveBlock1_size_outbreakUnused3 = sizeof(((struct SaveBlock1 *)0)->outbreakUnused3);
unsigned int b0_SaveBlock1_offset_outbreakPokemonProbability = __builtin_offsetof(struct SaveBlock1, outbreakPokemonProbability);
unsigned int b0_SaveBlock1_size_outbreakPokemonProbability = sizeof(((struct SaveBlock1 *)0)->outbreakPokemonProbability);
unsigned int b0_SaveBlock1_offset_outbreakDaysLeft = __builtin_offsetof(struct SaveBlock1, outbreakDaysLeft);
unsigned int b0_SaveBlock1_size_outbreakDaysLeft = sizeof(((struct SaveBlock1 *)0)->outbreakDaysLeft);
unsigned int b0_SaveBlock1_offset_gabbyAndTyData = __builtin_offsetof(struct SaveBlock1, gabbyAndTyData);
unsigned int b0_SaveBlock1_size_gabbyAndTyData = sizeof(((struct SaveBlock1 *)0)->gabbyAndTyData);
unsigned int b0_SaveBlock1_offset_easyChatProfile = __builtin_offsetof(struct SaveBlock1, easyChatProfile);
unsigned int b0_SaveBlock1_size_easyChatProfile = sizeof(((struct SaveBlock1 *)0)->easyChatProfile);
unsigned int b0_SaveBlock1_offset_easyChatBattleStart = __builtin_offsetof(struct SaveBlock1, easyChatBattleStart);
unsigned int b0_SaveBlock1_size_easyChatBattleStart = sizeof(((struct SaveBlock1 *)0)->easyChatBattleStart);
unsigned int b0_SaveBlock1_offset_easyChatBattleWon = __builtin_offsetof(struct SaveBlock1, easyChatBattleWon);
unsigned int b0_SaveBlock1_size_easyChatBattleWon = sizeof(((struct SaveBlock1 *)0)->easyChatBattleWon);
unsigned int b0_SaveBlock1_offset_easyChatBattleLost = __builtin_offsetof(struct SaveBlock1, easyChatBattleLost);
unsigned int b0_SaveBlock1_size_easyChatBattleLost = sizeof(((struct SaveBlock1 *)0)->easyChatBattleLost);
unsigned int b0_SaveBlock1_offset_mail = __builtin_offsetof(struct SaveBlock1, mail);
unsigned int b0_SaveBlock1_size_mail = sizeof(((struct SaveBlock1 *)0)->mail);
unsigned int b0_SaveBlock1_offset_unlockedTrendySayings = __builtin_offsetof(struct SaveBlock1, unlockedTrendySayings);
unsigned int b0_SaveBlock1_size_unlockedTrendySayings = sizeof(((struct SaveBlock1 *)0)->unlockedTrendySayings);
unsigned int b0_SaveBlock1_offset_oldMan = __builtin_offsetof(struct SaveBlock1, oldMan);
unsigned int b0_SaveBlock1_size_oldMan = sizeof(((struct SaveBlock1 *)0)->oldMan);
unsigned int b0_SaveBlock1_offset_dewfordTrends = __builtin_offsetof(struct SaveBlock1, dewfordTrends);
unsigned int b0_SaveBlock1_size_dewfordTrends = sizeof(((struct SaveBlock1 *)0)->dewfordTrends);
unsigned int b0_SaveBlock1_offset_contestWinners = __builtin_offsetof(struct SaveBlock1, contestWinners);
unsigned int b0_SaveBlock1_size_contestWinners = sizeof(((struct SaveBlock1 *)0)->contestWinners);
unsigned int b0_SaveBlock1_offset_daycare = __builtin_offsetof(struct SaveBlock1, daycare);
unsigned int b0_SaveBlock1_size_daycare = sizeof(((struct SaveBlock1 *)0)->daycare);
#if FREE_LINK_BATTLE_RECORDS == FALSE
unsigned int b0_SaveBlock1_offset_linkBattleRecords = __builtin_offsetof(struct SaveBlock1, linkBattleRecords);
unsigned int b0_SaveBlock1_size_linkBattleRecords = sizeof(((struct SaveBlock1 *)0)->linkBattleRecords);
#endif
unsigned int b0_SaveBlock1_offset_giftRibbons = __builtin_offsetof(struct SaveBlock1, giftRibbons);
unsigned int b0_SaveBlock1_size_giftRibbons = sizeof(((struct SaveBlock1 *)0)->giftRibbons);
unsigned int b0_SaveBlock1_offset_externalEventData = __builtin_offsetof(struct SaveBlock1, externalEventData);
unsigned int b0_SaveBlock1_size_externalEventData = sizeof(((struct SaveBlock1 *)0)->externalEventData);
unsigned int b0_SaveBlock1_offset_externalEventFlags = __builtin_offsetof(struct SaveBlock1, externalEventFlags);
unsigned int b0_SaveBlock1_size_externalEventFlags = sizeof(((struct SaveBlock1 *)0)->externalEventFlags);
unsigned int b0_SaveBlock1_offset_roamer = __builtin_offsetof(struct SaveBlock1, roamer);
unsigned int b0_SaveBlock1_size_roamer = sizeof(((struct SaveBlock1 *)0)->roamer);
#ifdef FIRERED
unsigned int b0_SaveBlock1_offset_roamerPadding = __builtin_offsetof(struct SaveBlock1, roamerPadding);
unsigned int b0_SaveBlock1_size_roamerPadding = sizeof(((struct SaveBlock1 *)0)->roamerPadding);
#else
unsigned int b0_SaveBlock1_offset_roamerPadding = __builtin_offsetof(struct SaveBlock1, roamerPadding);
unsigned int b0_SaveBlock1_size_roamerPadding = sizeof(((struct SaveBlock1 *)0)->roamerPadding);
#endif
#if FREE_ENIGMA_BERRY == FALSE
unsigned int b0_SaveBlock1_offset_enigmaBerry = __builtin_offsetof(struct SaveBlock1, enigmaBerry);
unsigned int b0_SaveBlock1_size_enigmaBerry = sizeof(((struct SaveBlock1 *)0)->enigmaBerry);
#endif
#if FREE_MYSTERY_GIFT == FALSE
unsigned int b0_SaveBlock1_offset_mysteryGift = __builtin_offsetof(struct SaveBlock1, mysteryGift);
unsigned int b0_SaveBlock1_size_mysteryGift = sizeof(((struct SaveBlock1 *)0)->mysteryGift);
#endif
unsigned int b0_SaveBlock1_offset_dexSeen = __builtin_offsetof(struct SaveBlock1, dexSeen);
unsigned int b0_SaveBlock1_size_dexSeen = sizeof(((struct SaveBlock1 *)0)->dexSeen);
unsigned int b0_SaveBlock1_offset_dexPadding1 = __builtin_offsetof(struct SaveBlock1, dexPadding1);
unsigned int b0_SaveBlock1_size_dexPadding1 = sizeof(((struct SaveBlock1 *)0)->dexPadding1);
unsigned int b0_SaveBlock1_offset_dexCaught = __builtin_offsetof(struct SaveBlock1, dexCaught);
unsigned int b0_SaveBlock1_size_dexCaught = sizeof(((struct SaveBlock1 *)0)->dexCaught);
unsigned int b0_SaveBlock1_offset_dexPadding2 = __builtin_offsetof(struct SaveBlock1, dexPadding2);
unsigned int b0_SaveBlock1_size_dexPadding2 = sizeof(((struct SaveBlock1 *)0)->dexPadding2);
#if FREE_TRAINER_HILL == FALSE
unsigned int b0_SaveBlock1_offset_trainerHillTimes = __builtin_offsetof(struct SaveBlock1, trainerHillTimes);
unsigned int b0_SaveBlock1_size_trainerHillTimes = sizeof(((struct SaveBlock1 *)0)->trainerHillTimes);
#endif
#if FREE_MYSTERY_EVENT_BUFFERS == FALSE
unsigned int b0_SaveBlock1_offset_ramScript = __builtin_offsetof(struct SaveBlock1, ramScript);
unsigned int b0_SaveBlock1_size_ramScript = sizeof(((struct SaveBlock1 *)0)->ramScript);
#endif
unsigned int b0_SaveBlock1_offset_recordMixingGift = __builtin_offsetof(struct SaveBlock1, recordMixingGift);
unsigned int b0_SaveBlock1_size_recordMixingGift = sizeof(((struct SaveBlock1 *)0)->recordMixingGift);
unsigned int b0_SaveBlock1_offset_lilycoveLady = __builtin_offsetof(struct SaveBlock1, lilycoveLady);
unsigned int b0_SaveBlock1_size_lilycoveLady = sizeof(((struct SaveBlock1 *)0)->lilycoveLady);
unsigned int b0_SaveBlock1_offset_trainerNameRecords = __builtin_offsetof(struct SaveBlock1, trainerNameRecords);
unsigned int b0_SaveBlock1_size_trainerNameRecords = sizeof(((struct SaveBlock1 *)0)->trainerNameRecords);
#if FREE_UNION_ROOM_CHAT == FALSE
unsigned int b0_SaveBlock1_offset_registeredTexts = __builtin_offsetof(struct SaveBlock1, registeredTexts);
unsigned int b0_SaveBlock1_size_registeredTexts = sizeof(((struct SaveBlock1 *)0)->registeredTexts);
#endif
#if FREE_TRAINER_HILL == FALSE
unsigned int b0_SaveBlock1_offset_trainerHill = __builtin_offsetof(struct SaveBlock1, trainerHill);
unsigned int b0_SaveBlock1_size_trainerHill = sizeof(((struct SaveBlock1 *)0)->trainerHill);
#endif
unsigned int b0_SaveBlock1_offset_waldaPhrase = __builtin_offsetof(struct SaveBlock1, waldaPhrase);
unsigned int b0_SaveBlock1_size_waldaPhrase = sizeof(((struct SaveBlock1 *)0)->waldaPhrase);
#if FREE_TRAINER_TOWER == FALSE && IS_FRLG
unsigned int b0_SaveBlock1_offset_towerChallengeId = __builtin_offsetof(struct SaveBlock1, towerChallengeId);
unsigned int b0_SaveBlock1_size_towerChallengeId = sizeof(((struct SaveBlock1 *)0)->towerChallengeId);
unsigned int b0_SaveBlock1_offset_trainerTower = __builtin_offsetof(struct SaveBlock1, trainerTower);
unsigned int b0_SaveBlock1_size_trainerTower = sizeof(((struct SaveBlock1 *)0)->trainerTower);
#endif
#if IS_FRLG
unsigned int b0_SaveBlock1_offset_rivalName = __builtin_offsetof(struct SaveBlock1, rivalName);
unsigned int b0_SaveBlock1_size_rivalName = sizeof(((struct SaveBlock1 *)0)->rivalName);
unsigned int b0_SaveBlock1_offset_route5DayCareMon = __builtin_offsetof(struct SaveBlock1, route5DayCareMon);
unsigned int b0_SaveBlock1_size_route5DayCareMon = sizeof(((struct SaveBlock1 *)0)->route5DayCareMon);
#endif
#if IS_HNS
unsigned int b0_SaveBlock1_offset_momSavings = __builtin_offsetof(struct SaveBlock1, momSavings);
unsigned int b0_SaveBlock1_size_momSavings = sizeof(((struct SaveBlock1 *)0)->momSavings);
#endif
unsigned int b0_SaveBlock2_total = sizeof(struct SaveBlock2);
unsigned int b0_SaveBlock2_align = __alignof__(struct SaveBlock2);
unsigned int b0_SaveBlock2_offset_playerName = __builtin_offsetof(struct SaveBlock2, playerName);
unsigned int b0_SaveBlock2_size_playerName = sizeof(((struct SaveBlock2 *)0)->playerName);
unsigned int b0_SaveBlock2_offset_playerGender = __builtin_offsetof(struct SaveBlock2, playerGender);
unsigned int b0_SaveBlock2_size_playerGender = sizeof(((struct SaveBlock2 *)0)->playerGender);
unsigned int b0_SaveBlock2_offset_specialSaveWarpFlags = __builtin_offsetof(struct SaveBlock2, specialSaveWarpFlags);
unsigned int b0_SaveBlock2_size_specialSaveWarpFlags = sizeof(((struct SaveBlock2 *)0)->specialSaveWarpFlags);
unsigned int b0_SaveBlock2_offset_playerTrainerId = __builtin_offsetof(struct SaveBlock2, playerTrainerId);
unsigned int b0_SaveBlock2_size_playerTrainerId = sizeof(((struct SaveBlock2 *)0)->playerTrainerId);
unsigned int b0_SaveBlock2_offset_playTimeHours = __builtin_offsetof(struct SaveBlock2, playTimeHours);
unsigned int b0_SaveBlock2_size_playTimeHours = sizeof(((struct SaveBlock2 *)0)->playTimeHours);
unsigned int b0_SaveBlock2_offset_playTimeMinutes = __builtin_offsetof(struct SaveBlock2, playTimeMinutes);
unsigned int b0_SaveBlock2_size_playTimeMinutes = sizeof(((struct SaveBlock2 *)0)->playTimeMinutes);
unsigned int b0_SaveBlock2_offset_playTimeSeconds = __builtin_offsetof(struct SaveBlock2, playTimeSeconds);
unsigned int b0_SaveBlock2_size_playTimeSeconds = sizeof(((struct SaveBlock2 *)0)->playTimeSeconds);
unsigned int b0_SaveBlock2_offset_playTimeVBlanks = __builtin_offsetof(struct SaveBlock2, playTimeVBlanks);
unsigned int b0_SaveBlock2_size_playTimeVBlanks = sizeof(((struct SaveBlock2 *)0)->playTimeVBlanks);
unsigned int b0_SaveBlock2_offset_optionsButtonMode = __builtin_offsetof(struct SaveBlock2, optionsButtonMode);
unsigned int b0_SaveBlock2_size_optionsButtonMode = sizeof(((struct SaveBlock2 *)0)->optionsButtonMode);
unsigned int b0_SaveBlock2_offset_pokedex = __builtin_offsetof(struct SaveBlock2, pokedex);
unsigned int b0_SaveBlock2_size_pokedex = sizeof(((struct SaveBlock2 *)0)->pokedex);
unsigned int b0_SaveBlock2_offset_filler_90 = __builtin_offsetof(struct SaveBlock2, filler_90);
unsigned int b0_SaveBlock2_size_filler_90 = sizeof(((struct SaveBlock2 *)0)->filler_90);
unsigned int b0_SaveBlock2_offset_localTimeOffset = __builtin_offsetof(struct SaveBlock2, localTimeOffset);
unsigned int b0_SaveBlock2_size_localTimeOffset = sizeof(((struct SaveBlock2 *)0)->localTimeOffset);
unsigned int b0_SaveBlock2_offset_lastBerryTreeUpdate = __builtin_offsetof(struct SaveBlock2, lastBerryTreeUpdate);
unsigned int b0_SaveBlock2_size_lastBerryTreeUpdate = sizeof(((struct SaveBlock2 *)0)->lastBerryTreeUpdate);
unsigned int b0_SaveBlock2_offset_gcnLinkFlags = __builtin_offsetof(struct SaveBlock2, gcnLinkFlags);
unsigned int b0_SaveBlock2_size_gcnLinkFlags = sizeof(((struct SaveBlock2 *)0)->gcnLinkFlags);
unsigned int b0_SaveBlock2_offset_encryptionKey = __builtin_offsetof(struct SaveBlock2, encryptionKey);
unsigned int b0_SaveBlock2_size_encryptionKey = sizeof(((struct SaveBlock2 *)0)->encryptionKey);
unsigned int b0_SaveBlock2_offset_playerApprentice = __builtin_offsetof(struct SaveBlock2, playerApprentice);
unsigned int b0_SaveBlock2_size_playerApprentice = sizeof(((struct SaveBlock2 *)0)->playerApprentice);
unsigned int b0_SaveBlock2_offset_apprentices = __builtin_offsetof(struct SaveBlock2, apprentices);
unsigned int b0_SaveBlock2_size_apprentices = sizeof(((struct SaveBlock2 *)0)->apprentices);
unsigned int b0_SaveBlock2_offset_berryCrush = __builtin_offsetof(struct SaveBlock2, berryCrush);
unsigned int b0_SaveBlock2_size_berryCrush = sizeof(((struct SaveBlock2 *)0)->berryCrush);
#if FREE_POKEMON_JUMP == FALSE
unsigned int b0_SaveBlock2_offset_pokeJump = __builtin_offsetof(struct SaveBlock2, pokeJump);
unsigned int b0_SaveBlock2_size_pokeJump = sizeof(((struct SaveBlock2 *)0)->pokeJump);
#endif
unsigned int b0_SaveBlock2_offset_berryPick = __builtin_offsetof(struct SaveBlock2, berryPick);
unsigned int b0_SaveBlock2_size_berryPick = sizeof(((struct SaveBlock2 *)0)->berryPick);
#if FREE_RECORD_MIXING_HALL_RECORDS == FALSE
unsigned int b0_SaveBlock2_offset_hallRecords1P = __builtin_offsetof(struct SaveBlock2, hallRecords1P);
unsigned int b0_SaveBlock2_size_hallRecords1P = sizeof(((struct SaveBlock2 *)0)->hallRecords1P);
unsigned int b0_SaveBlock2_offset_hallRecords2P = __builtin_offsetof(struct SaveBlock2, hallRecords2P);
unsigned int b0_SaveBlock2_size_hallRecords2P = sizeof(((struct SaveBlock2 *)0)->hallRecords2P);
#endif
unsigned int b0_SaveBlock2_offset_contestLinkResults = __builtin_offsetof(struct SaveBlock2, contestLinkResults);
unsigned int b0_SaveBlock2_size_contestLinkResults = sizeof(((struct SaveBlock2 *)0)->contestLinkResults);
unsigned int b0_SaveBlock2_offset_frontier = __builtin_offsetof(struct SaveBlock2, frontier);
unsigned int b0_SaveBlock2_size_frontier = sizeof(((struct SaveBlock2 *)0)->frontier);
unsigned int b0_SaveBlock2_offset_rivalName = __builtin_offsetof(struct SaveBlock2, rivalName);
unsigned int b0_SaveBlock2_size_rivalName = sizeof(((struct SaveBlock2 *)0)->rivalName);
unsigned int b0_SaveBlock3_total = sizeof(struct SaveBlock3);
unsigned int b0_SaveBlock3_align = __alignof__(struct SaveBlock3);
unsigned int b0_SaveBlock3_offset_fakeRTC = __builtin_offsetof(struct SaveBlock3, fakeRTC);
unsigned int b0_SaveBlock3_size_fakeRTC = sizeof(((struct SaveBlock3 *)0)->fakeRTC);
#if FNPC_ENABLE_NPC_FOLLOWERS
unsigned int b0_SaveBlock3_offset_NPCfollower = __builtin_offsetof(struct SaveBlock3, NPCfollower);
unsigned int b0_SaveBlock3_size_NPCfollower = sizeof(((struct SaveBlock3 *)0)->NPCfollower);
#endif
#if OW_SHOW_ITEM_DESCRIPTIONS == OW_ITEM_DESCRIPTIONS_FIRST_TIME
unsigned int b0_SaveBlock3_offset_itemFlags = __builtin_offsetof(struct SaveBlock3, itemFlags);
unsigned int b0_SaveBlock3_size_itemFlags = sizeof(((struct SaveBlock3 *)0)->itemFlags);
#endif
#if USE_DEXNAV_SEARCH_LEVELS == TRUE
unsigned int b0_SaveBlock3_offset_dexNavSearchLevels = __builtin_offsetof(struct SaveBlock3, dexNavSearchLevels);
unsigned int b0_SaveBlock3_size_dexNavSearchLevels = sizeof(((struct SaveBlock3 *)0)->dexNavSearchLevels);
#endif
unsigned int b0_SaveBlock3_offset_dexNavChain = __builtin_offsetof(struct SaveBlock3, dexNavChain);
unsigned int b0_SaveBlock3_size_dexNavChain = sizeof(((struct SaveBlock3 *)0)->dexNavChain);
#if APRICORN_TREE_COUNT > 0
unsigned int b0_SaveBlock3_offset_apricornTrees = __builtin_offsetof(struct SaveBlock3, apricornTrees);
unsigned int b0_SaveBlock3_size_apricornTrees = sizeof(((struct SaveBlock3 *)0)->apricornTrees);
#endif
unsigned int b0_SaveBlock3_offset_challengeSettings = __builtin_offsetof(struct SaveBlock3, challengeSettings);
unsigned int b0_SaveBlock3_size_challengeSettings = sizeof(((struct SaveBlock3 *)0)->challengeSettings);
unsigned int b0_SaveBlock3_offset_registeredItemHold = __builtin_offsetof(struct SaveBlock3, registeredItemHold);
unsigned int b0_SaveBlock3_size_registeredItemHold = sizeof(((struct SaveBlock3 *)0)->registeredItemHold);
unsigned int b0_roamer_count = ROAMER_COUNT;
unsigned int b0_roamer_size = sizeof(struct Roamer);
unsigned int b0_sector_data_size = SECTOR_DATA_SIZE;
unsigned int b0_sector_total_size = sizeof(struct SaveSector);
unsigned int b0_saveblock1_capacity = SECTOR_DATA_SIZE * (SECTOR_ID_SAVEBLOCK1_END - SECTOR_ID_SAVEBLOCK1_START + 1);
unsigned int b0_saveblock3_capacity = SAVE_BLOCK_3_CHUNK_SIZE * NUM_SECTORS_PER_SLOT;
unsigned int b0_sector_saveblock1_start = SECTOR_ID_SAVEBLOCK1_START;
unsigned int b0_sector_saveblock1_end = SECTOR_ID_SAVEBLOCK1_END;
unsigned int b0_sector_count = SECTORS_COUNT;
unsigned int b0_sector_per_slot = NUM_SECTORS_PER_SLOT;
unsigned int b0_save_version = SAVE_VERSION;
