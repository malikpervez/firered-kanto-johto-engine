
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

KantoAmbient_SaffronCity_CopyCatsHouse_1F_EventScript_Ditto::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_DITTO, CRY_MODE_NORMAL
	msgbox KantoAmbient_CopycatsHouse1F_Text_Ditto, MSGBOX_DEFAULT
	waitmoncry
	release
	end

KantoAmbient_VermilionCity_FanClub_EventScript_Clefairy::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_CLEFAIRY, CRY_MODE_NORMAL
	msgbox KantoAmbient_PokemonFanClub_Text_Clefairy, MSGBOX_DEFAULT
	waitmoncry
	release
	end



KantoAmbient_ViridianCity_House1_Text_Rattey:
	.string "RATTEY: Kikiii!$"
KantoAmbient_CeruleanHouse_Text_Kangaskhan:
	.string "KANGASKHAN: Garu garuu.$"
KantoAmbient_CeruleanHouse_Text_Zubat:
	.string "ZUBAT: Zuba zubaa.$"
KantoAmbient_CopycatsHouse1F_Text_Ditto:
	.string "DITTO: Dii-tto!$"
KantoAmbient_PokemonFanClub_Text_Clefairy:
	.string "CLEFAIRY: Pippi!$"



KantoAmbient_CeladonCity_Condominiums_1F_EventScript_Meowth::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_MEOWTH, CRY_MODE_NORMAL
	msgbox KantoAmbient_CeladonCity_Condominiums_1F_Text_1, MSGBOX_DEFAULT
	waitmoncry
	release
	end

KantoAmbient_CeladonCity_Condominiums_1F_Text_1:
	.string "MEOWTH: Meow?$"

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

