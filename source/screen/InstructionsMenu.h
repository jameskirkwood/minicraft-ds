#ifndef SCREEN_INSTRUCTIONSMENU_H
#define SCREEN_INSTRUCTIONSMENU_H

#include <nds.h>
#include <memory>

#include "Menu.h"
#include "Game.h"
#include "gfx/Display.h"
#include "gfx/Font.h"

class InstructionsMenu : public Menu {

  std::shared_ptr<Menu> parent;

  gfx::Font white_font = gfx::Font(gfx::colours(0, 555, 555, 555));
  gfx::Font grey_font = gfx::Font(gfx::colours(0, 333, 333, 333));

  static const char *lines[];

public:

  InstructionsMenu(std::shared_ptr<Menu> parent) : parent(parent) {}

  void tick();
  void render();
};

#endif
