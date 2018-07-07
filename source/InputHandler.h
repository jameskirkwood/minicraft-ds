#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <nds.h>

//-----------------------------------------------------------------------------
struct InputHandler {
//-----------------------------------------------------------------------------

  struct Key { volatile bool down, clicked; };

// key states
//-----------------------------------------------------------------------------
  Key up, down, left, right;
  Key attack, menu;
//-----------------------------------------------------------------------------

// read keypad (call once per frame)
//-----------------------------------------------------------------------------
  void tick() {
//-----------------------------------------------------------------------------
    scanKeys();

    up.down     = keysHeld() & KEY_UP;
    down.down   = keysHeld() & KEY_DOWN;
    left.down   = keysHeld() & KEY_LEFT;
    right.down  = keysHeld() & KEY_RIGHT;
    attack.down = keysHeld() & KEY_B;
    menu.down   = keysHeld() & KEY_A;

    up.clicked     = keysDown() & KEY_UP;
    down.clicked   = keysDown() & KEY_DOWN;
    left.clicked   = keysDown() & KEY_LEFT;
    right.clicked  = keysDown() & KEY_RIGHT;
    attack.clicked = keysDown() & KEY_B;
    menu.clicked   = keysDown() & KEY_A;
  }
};

// global instances
//-----------------------------------------------------------------------------
extern InputHandler input;
//-----------------------------------------------------------------------------

#endif
