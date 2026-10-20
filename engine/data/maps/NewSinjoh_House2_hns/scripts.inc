@ Johto (data/maps/NewSinjoh_House2_hns/scripts.inc), as built into the FireRed game.

NewSinjoh_House2_hns_MapScripts::
	.byte 0

NewSinjoh_House2_EventScripts_DeskLady::
	lock
	msgbox NewSinjoh_House2_DeskLady_Text MSGBOX_DEFAULT
	release
	end

NewSinjoh_House2_DeskLady_Text::
	.string "Hello{SE_M_SUPERSONIC}littl{SE_M_REVERSAL}one..\p"
	.string "Welcom{SE_M_REVERSAL}t{SE_M_ATTRACT2}Ne{SE_M_TWISTER}Sinjoh's...\n"
	.string "Well{SE_M_SUPERSONIC}yo{SE_M_DIVE}migh{SE_M_SPIT_UP}cal{SE_M_BATON_PASS}i{SE_M_SPIT_UP}{SE_M_CHARGE}library.\p"
	.string "Really{SE_M_SUPERSONIC}thi{SE_M_GRASSWHISTLE}i{SE_M_GRASSWHISTLE}wher{SE_M_REVERSAL}w{SE_M_REVERSAL}kee{SE_M_MORNING_SUN}all\n"
	.string "th{SE_M_REVERSAL}record{SE_M_GRASSWHISTLE}o{SE_M_ACID_ARMOR}ou{SE_M_SAND_TOMB}town'{SE_M_GRASSWHISTLE}history,\l"
	.string "a{SE_M_GRASSWHISTLE}wel{SE_M_BATON_PASS}a{SE_M_GRASSWHISTLE}an{SE_M_YAWN}literatur{SE_M_REVERSAL}we\l"
	.string "impor{SE_M_SPIT_UP}fro{SE_M_MILK_DRINK}othe{SE_M_SAND_TOMB}regions..$"

NewSinjoh_House2_EventScript_Torkoal::
	lock
	faceplayer
	playmoncry 324, 0
	msgbox NewSinjoh_Hosue2_Text_CryTorkoal, MSGBOX_DEFAULT
	waitmoncry
	closemessage
	release
	end

NewSinjoh_Hosue2_Text_CryTorkoal:
	.string "Tooor?$"

NewSinjoh_House2_EventScript_BookShelf_North::
	lock
	msgbox NewSinjoh_House2_Text_Bookshelf_North MSGBOX_DEFAULT
	release
	end

NewSinjoh_House2_Text_Bookshelf_North:
	.string "It'{SE_M_GRASSWHISTLE}cramme{SE_M_WATERFALL}ful{SE_M_BATON_PASS}o{SE_M_ACID_ARMOR}ancient\n"
	.string "leather-boun{SE_M_WATERFALL}books.\p"
	.string "Th{SE_M_REVERSAL}languag{SE_M_REVERSAL}i{SE_M_GRASSWHISTLE}unrecognizeable.$"

NewSinjoh_House2_EventScript_BookShelf_South::
	lock
	msgbox NewSinjoh_House2_Text_Bookshelf_South MSGBOX_DEFAULT
	release
	end

NewSinjoh_House2_Text_Bookshelf_South:
	.string "It'{SE_M_GRASSWHISTLE}cramme{SE_M_WATERFALL}ful{SE_M_BATON_PASS}o{SE_M_ACID_ARMOR}POKéMON\n"
	.string "books.\p"
	.string "Thes{SE_M_REVERSAL}loo{SE_M_ENCORE2}newe{SE_M_SAND_TOMB}an{SE_M_WATERFALL}mor{SE_M_REVERSAL}familiar.$"

