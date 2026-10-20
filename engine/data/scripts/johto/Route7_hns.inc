@ Johto (data/maps/Route7_hns/scripts.inc), as built into the FireRed game.

J_Route7_EventScript_Door::
	msgbox J_Route7_Text_LockedDoor, MSGBOX_SIGN
	end

J_Route7_Text_LockedDoor::
	.byte 0xC3, 0xE8, 0xB4, 0xE7, 0x00, 0xE0, 0xE3, 0xD7, 0xDF, 0xD9, 0xD8, 0xB0, 0xFF

	.ifdef J_Route7_Text_LockedDoor ; .size J_Route7_Text_LockedDoor, . - J_Route7_Text_LockedDoor ; .endif

