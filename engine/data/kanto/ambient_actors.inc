
KantoAmbient_ViridianCity_House1_EventScript_Rattey::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_RATTATA, CRY_MODE_NORMAL
	msgbox KantoAmbient_ViridianCity_House1_Text_Rattey, MSGBOX_DEFAULT
	waitmoncry
	release
	end

KantoAmbient_CeruleanCity_House3_EventScript_Kangaskhan::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_KANGASKHAN, CRY_MODE_NORMAL
	msgbox KantoAmbient_CeruleanHouse_Text_Kangaskhan, MSGBOX_DEFAULT
	waitmoncry
	release
	end

KantoAmbient_CeruleanCity_House3_EventScript_Zubat::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ZUBAT, CRY_MODE_NORMAL
	msgbox KantoAmbient_CeruleanHouse_Text_Zubat, MSGBOX_DEFAULT
	waitmoncry
	release
	end

KantoAmbient_SaffronCity_CopyCatsHouse_1F_EventScript_Blissey::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_BLISSEY, CRY_MODE_NORMAL
	msgbox KantoAmbient_CopycatsHouse1F_Text_Blissey, MSGBOX_DEFAULT
	waitmoncry
	release
	end

KantoAmbient_VermilionCity_FanClub_EventScript_Bayleef::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_BAYLEEF, CRY_MODE_NORMAL
	msgbox KantoAmbient_PokemonFanClub_Text_Bayleef, MSGBOX_DEFAULT
	waitmoncry
	release
	end



KantoAmbient_ViridianCity_House1_Text_Rattey:
	.string "RATTEY: Kikiii!$"
KantoAmbient_CeruleanHouse_Text_Kangaskhan:
	.string "KANGASKHAN: Garu garuu.$"
KantoAmbient_CeruleanHouse_Text_Zubat:
	.string "ZUBAT: Zuba zubaa.$"
KantoAmbient_CopycatsHouse1F_Text_Blissey:
	.string "BLISSEY: Bliisii!$"
KantoAmbient_PokemonFanClub_Text_Bayleef:
	.string "BAYLEEF: Li liif!$"



KantoAmbient_CeladonCity_Condominiums_1F_EventScript_Skitty::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_SKITTY, CRY_MODE_NORMAL
	msgbox KantoAmbient_CeladonCity_Condominiums_1F_Text_1, MSGBOX_DEFAULT
	waitmoncry
	release
	end

KantoAmbient_CeladonCity_Condominiums_1F_Text_1:
	.string "SKITTY: Miyao?$"

KantoAmbient_CeruleanCity_House2_EventScript_Diglett::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_DIGLETT, CRY_MODE_NORMAL
	msgbox KantoAmbient_CeruleanCity_House2_Text_1, MSGBOX_DEFAULT
	waitmoncry
	release
	end

KantoAmbient_CeruleanCity_House2_Text_1:
	.string "DIGLETT: Dug dug.$"

KantoAmbient_LavenderTown_VolunteerPokemonHouse_EventScript_Marowak::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_MAROWAK, CRY_MODE_NORMAL
	msgbox KantoAmbient_LavenderTown_VolunteerPokemonHouse_Text_1, MSGBOX_DEFAULT
	waitmoncry
	msgbox KantoAmbient_LavenderTown_VolunteerPokemonHouse_Text_2, MSGBOX_DEFAULT
	closemessage
	release
	end

KantoAmbient_LavenderTown_VolunteerPokemonHouse_Text_1:
	.string ".............................$"

KantoAmbient_LavenderTown_VolunteerPokemonHouse_Text_2:
	.string "The MAROWAK is quiet, though it\n"
	.string "appears quite happy.$"

