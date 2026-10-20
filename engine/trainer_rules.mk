# party files are run through trainerproc, which is a tool that converts party data to an output file
# matching the current trainer .h formatting

AUTO_GEN_TARGETS += src/data/trainers.h
AUTO_GEN_TARGETS += src/data/trainers_frlg.h
AUTO_GEN_TARGETS += src/data/trainers_hns.h
AUTO_GEN_TARGETS += src/data/battle_partners.h
AUTO_GEN_TARGETS += test/battle/trainer_control.h
AUTO_GEN_TARGETS += test/battle/partner_control.h
AUTO_GEN_TARGETS += src/data/debug_trainers.h

ifeq ($(GAME_VERSION),FIRERED)
AUTO_GEN_TARGETS += src/data/trainers_firered_johto.h
src/data/trainers_firered_johto.h: src/data/trainers_hns.h include/constants/johto_trainers.h src/data/trainers_hns.party tools/trainerproc/firered_johto.py
	python3 tools/trainerproc/firered_johto.py --input $< --output $@ --constants include/constants/johto_trainers.h --party src/data/trainers_hns.party
endif

%.h: %.party $(TRAINERPROC)
	$(CPP) $(CPPFLAGS) -traditional-cpp - < $< | $(TRAINERPROC) -o $@ -i $< -
