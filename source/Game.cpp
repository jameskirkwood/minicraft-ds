#include <nds.h>
#include <custard/types.hpp>

#include "Game.h"

#include "gfx/Display.h"
#include "gfx/Font.h"
#include "gfx/Frame.h"

#include "screen/TitleMenu.h"

#include "InputHandler.h"

using gfx::display;
using gfx::colours;
using custard::ivec2;

//-----------------------------------------------------------------------------
void Game::resetGame() {
//-----------------------------------------------------------------------------
  playerDeadTime = 0;
  wonTimer = 0;
  gameTime = 0;
  hasWon = false;
  currentLevel = 3;

  levels[4] = new Level(128, 128, 1, nullptr);
  levels[3] = new Level(128, 128, 0, levels[4]);
  // TODO: postpone lower level generation until first entering them to reduce
  // waiting time
  levels[2] = new Level(128, 128, -1, levels[3]);
  levels[1] = new Level(128, 128, -2, levels[2]);
  levels[0] = new Level(128, 128, -3, levels[1]);

  level = levels[currentLevel];
  // player.findStartPos(level);
  // level.add(player);
  for (int i = 0; i < 5; i++) levels[i]->trySpawn(5000);
}

//-----------------------------------------------------------------------------
void Game::init() {
//-----------------------------------------------------------------------------
  level = nullptr;
  setMenu(new TitleMenu());
}

//-----------------------------------------------------------------------------
void Game::tick() {
//-----------------------------------------------------------------------------
  // if (!player.removed && !hasWon) gameTime++;

  // input.tick();
  if (menu) menu->tick();
  else {
    // if (player.removed) {
    //   playerDeadTime++;
    //   if (playerDeadTime > 60) {
    //     setMenu(new DeadMenu());
    //   }
    // } else {
    //   if (pendingLevelChange != 0) {
    //     setMenu(new LevelTransitionMenu(pendingLevelChange));
    //     pendingLevelChange = 0;
    //   }
    // }
    if (wonTimer > 0 && --wonTimer == 0) {
      // setMenu(new WonMenu());
    }
    level->tick();
    // Tile.tickCount++;

    // BEGIN TESTING AREA
    player.x += input.right.down - input.left.down;
    player.y += input.down.down - input.up.down;
    if (input.attack.down || input.menu.down) level->setTile(
      player.x >> 4, player.y >> 4, Tile::infiniteFall);
    // END TESTING AREA
  }
}

//-----------------------------------------------------------------------------
void Game::render() {
//-----------------------------------------------------------------------------
  if (level) {
    ivec2 scroll = ivec2(player.x, player.y + 8) - (display.shape >> 1);
    scroll = scroll.max(16).min(level->shape * 16 - display.shape - 16);

    display.sky_layer.setScroll((scroll.x >> 2) & 7, (scroll.y >> 2) & 7);
    display.world_layer.setScroll(scroll.x & 15, scroll.y & 15);

    if (currentLevel > 3) display.sky_layer.clear(sky);

    level->renderBackground(display.world_layer, scroll);

    // level.renderSprites(scroll.x, scroll.y);

    // if (currentLevel < 3) {
    //   lightScreen.clear(0);
    //   level.renderLight(lightScreen, xScroll, yScroll);
    //   screen.overlay(lightScreen, xScroll, yScroll);
    // }

    for (int y = 0; y < display.TILES_HIGH; y++) {
      for (int x = 0; x < display.TILES_WIDE; x++) {
        auto tile = (display.TILES_HIGH - y > 2) ? display.clear : display.black;
        display.gui_layer.drawTile(tile, x, y, 0);
      }
    }

    for (int i = 0; i < 10; i++) {
      auto tile = (i < player.health) ? health[1] : health[0];
      display.gui_layer.drawTile(tile, i, display.TILES_HIGH - 2, 0);

      if (player.staminaRechargeDelay > 0) {
        tile = resting[player.staminaRechargeDelay / 4 % 2 == 0];
      }
      else tile = stamina[i < player.stamina];
      display.gui_layer.drawTile(tile, i, display.TILES_HIGH - 1, 0);
    }

    // if (player.activeItem != null) {
    //   player.activeItem.renderInventory(screen, 10 * 8, screen.h - 16);
    // }
  }

  if (menu) menu->render();
}

//-----------------------------------------------------------------------------
void Game::show() {
//-----------------------------------------------------------------------------

  sky = display.allocTile(0, colours(20, 20, 121, 121));

  health[1] = display.allocTile(0 + 12 * 32, colours(0, 200, 500, 533));
  health[0] = display.allocTile(0 + 12 * 32, colours(0, 100, 0, 0));

  stamina[1] = display.allocTile(1 + 12 * 32, colours(0, 220, 550, 553));
  stamina[0] = display.allocTile(1 + 12 * 32, colours(0, 110, 0, 0));

  resting[1] = display.allocTile(1 + 12 * 32, colours(0, 555, 0, 0));
  resting[0] = display.allocTile(1 + 12 * 32, colours(0, 110, 0, 0));

  display.sky_layer.show();
  display.sky_layer.setPriority(3);

  display.world_layer.show();
  display.world_layer.setPriority(2);

  display.gui_layer.show();
  display.gui_layer.setPriority(0);
}

//-----------------------------------------------------------------------------
void Game::hide() {
//-----------------------------------------------------------------------------

  display.freeTile(sky);
  display.freeTile(health[1]);
  display.freeTile(health[0]);
  display.freeTile(stamina[1]);
  display.freeTile(stamina[0]);
  display.freeTile(resting[1]);
  display.freeTile(resting[0]);
}
