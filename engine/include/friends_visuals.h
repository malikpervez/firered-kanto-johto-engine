#ifndef GUARD_FRIENDS_VISUALS_H
#define GUARD_FRIENDS_VISUALS_H

// A bounded picture of home, not a map, warp destination, or player service.
// The scene owner must hide it before menus, battles, map changes, or exit.
// FALSE means allocation/window ownership prevented presentation; no game
// state is written and the caller must not count that visual as executed.
bool8 FriendsVisuals_ShowHome(void);
void FriendsVisuals_HideHome(void);
bool8 FriendsVisuals_IsShowing(void);

#endif
