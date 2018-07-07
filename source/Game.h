#ifndef GAME_H
#define GAME_H

#include <memory>

#include "screen/Menu.h"
#include "entity/Player.h"
#include "level/Level.h"

// com.mojang.ld22.Game
//-----------------------------------------------------------------------------
class Game {
//-----------------------------------------------------------------------------

  Level *levels[5]; // world model
  Level *level; // reference to current level

// game state
//-----------------------------------------------------------------------------
  bool hasWon;
  int wonTimer;
  int playerDeadTime;
  int pendingLevelChange;
  int currentLevel;
//-----------------------------------------------------------------------------

// currently active menu
//-----------------------------------------------------------------------------
// The 'menu' system is an instance of the State pattern. Only one menu is
// active at a time. A menu may transition to another one by allocating an
// object on the heap that implements the Menu interface, and passing to the
// setMenu method a shared pointer to it.
// When menu is null, the Game object will run the game and draw the world.
  std::shared_ptr<Menu> menu;
//-----------------------------------------------------------------------------

public:

  int gameTime; // play time in ticks

  Player player; // player model

// switch to and take ownership of a Menu allocated using `new` \see menu
//-----------------------------------------------------------------------------
  void setMenu(Menu *new_menu) { setMenu(std::shared_ptr<Menu>(new_menu)); }
//-----------------------------------------------------------------------------

// switch to and share ownership of a Menu allocated using `new` \see menu
//-----------------------------------------------------------------------------
  template <class _Menu> void setMenu(std::shared_ptr<_Menu> new_menu) {
//-----------------------------------------------------------------------------
    // TODO: handle show and hide by storing a 'current owner' in display
    if (menu) menu->hide();
    menu = std::static_pointer_cast<Menu>(new_menu);
    if (menu) {
      menu->game = this;
      menu->show();
    }
    else show();
  }

// generate a new world
//-----------------------------------------------------------------------------
  void resetGame();
//-----------------------------------------------------------------------------

// generate a new world and exit to the main menu
//-----------------------------------------------------------------------------
  void init();
//-----------------------------------------------------------------------------

// time base event (call once per frame)
//-----------------------------------------------------------------------------
  void tick();
//-----------------------------------------------------------------------------

// ascend or descend levels and relocate the player to the destination level
//-----------------------------------------------------------------------------
  void changeLevel(int dir) {
//-----------------------------------------------------------------------------
    // level.remove(player);
    currentLevel += dir; // changes current level by dir
    level = levels[currentLevel];
    // player.x = (player.x >> 4) * 16 + 8;
    // player.y = (player.y >> 4) * 16 + 8;
    // level.add(player);
  }

// draw everything (call once per frame)
//-----------------------------------------------------------------------------
  void render();
//-----------------------------------------------------------------------------

// signal to start a level transition upon the next tick
//-----------------------------------------------------------------------------
  void scheduleLevelChange(int dir) {
//-----------------------------------------------------------------------------
    pendingLevelChange = dir; // transition will call changeLevel(dir)
  }

// signal game completion
//-----------------------------------------------------------------------------
  void won() {
//-----------------------------------------------------------------------------
    // play time stops counting now, game ends after 3 seconds at 60 fps
    wonTimer = 60 * 3;
    hasWon = true;
  }

// members with no equivalent in the original class...
//-----------------------------------------------------------------------------
private:

// graphics for rendering world
//-----------------------------------------------------------------------------
  gfx::TileId sky, health[2], stamina[2], resting[2];
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
  void show(); // set up for rendering the world
  void hide(); // release resources used for rendering the world
//-----------------------------------------------------------------------------
};

#endif
