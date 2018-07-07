#include <nds.h>

#include "InstructionsMenu.h"
#include "InputHandler.h"

void InstructionsMenu::tick() {

  if (input.attack.clicked || input.menu.clicked) {
    game->setMenu(parent);
  }
}

void InstructionsMenu::render() {

  gfx::display.world_layer.hide();
  gfx::display.light_layer.hide();
  gfx::display.sky_layer.hide();

  gfx::display.gui_layer.clear(gfx::display.black);
  gfx::display.gui_layer.setScroll(-4, 0);
  gfx::display.gui_layer.show();

  white_font.draw("HOW TO PLAY", gfx::display.gui_layer, 10, 1);

  for (int i = 0; lines[i] != 0; i++) {
    grey_font.draw(lines[i], gfx::display.gui_layer, 0, 3 + i);
  }
}

const char *InstructionsMenu::lines[] = {
  "Move your character with the",
  "D-pad, press B to attack and",
  "press A to open your inventory",
  "and to interact with objects.",
  "",
  "Select an item in the inventory",
  "and press A to equip it, or",
  "press B to equip nothing.",
  "",
  "Kill the air wizard to win the",
  "game!",
  0
};
