#include <nds.h>

#include "AboutMenu.h"
#include "InputHandler.h"

void AboutMenu::tick() {

  if (input.attack.clicked || input.menu.clicked) {
    game->setMenu(parent);
  }
}

void AboutMenu::render() {

  gfx::display.world_layer.hide();
  gfx::display.light_layer.hide();
  gfx::display.sky_layer.hide();

  gfx::display.gui_layer.clear(gfx::display.black);
  gfx::display.gui_layer.setScroll(-4, 0);
  gfx::display.gui_layer.show();

  title_font.draw("About Minicraft(DS)", gfx::display.gui_layer, 6, 1);

  for (int i = 0; lines[i] != 0; i++) {
    body_font.draw(lines[i], gfx::display.gui_layer, 0, 3 + i);
  }

  bold_font.draw("Thank you, Notch, for", gfx::display.gui_layer, 5, 21);
  bold_font.draw("creating Minicraft.", gfx::display.gui_layer, 6, 22);
}

const char *AboutMenu::lines[] = {
  "The original Minicraft was",
  "developed by Markus \"Notch\"",
  "Persson for the 22nd Ludum Dare",
  "game programming competition",
  "in December 2011.",
  "",
  "Minicraft DS is my ongoing eff-",
  "ort to port Notch's \"Minicraft\"",
  "for Nintendo DS using devkitPro",
  "+ libnds for fun and education.",
  "",
  "For more information, visit:",
  "https://github.com/jameskirkwoo",
  "d/minicraft-ds",
  "",
  VERSION,
  "THIS IS A WORK IN PROGRESS!",
  0
};
