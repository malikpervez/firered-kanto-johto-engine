#ifndef GUARD_FRIENDS_CAMERA_H
#define GUARD_FRIENDS_CAMERA_H

// Begin1 means an owned asynchronous task will resume the script once;
// Begin2 means a validated existing HOLD, return synchronously without waitstate.
// Begin0 means unavailable: leave without a scene receipt.
// Return FALSE means inactive only. An active fault remains locked for diagnosis.
void Special_FriendsCameraBegin(void);
void Special_FriendsCameraReturn(void);
// Native map setup owns rebuilding its camera/sprites. Clear private ownership
// only; never apply an old map's coordinates to a newly loaded map.
void FriendsCamera_OnMapLoad(void);
u16 FriendsCamera_GetFault(void);

#endif
