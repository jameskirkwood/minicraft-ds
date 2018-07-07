#ifndef SCREEN_ABOUTMENU_H
#define SCREEN_ABOUTMENU_H

#include <nds.h>
#include <memory>

#include "Menu.h"
#include "Game.h"
#include "gfx/Display.h"
#include "gfx/Font.h"

class AboutMenu : public Menu {

  std::shared_ptr<Menu> parent;

  gfx::Font title_font = gfx::Font(gfx::colours(0, 555, 555, 555));
  gfx::Font body_font = gfx::Font(gfx::colours(0, 333, 333, 333));
  gfx::Font bold_font = gfx::Font(gfx::colours(0, 555, 551, 551));

  static const char *lines[];

public:

  AboutMenu(std::shared_ptr<Menu> parent) : parent(parent) {}

  void tick();
  void render();
};

#endif
