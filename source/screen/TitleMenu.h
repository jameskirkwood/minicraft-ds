#ifndef SCREEN_TITLEMENU_H
#define SCREEN_TITLEMENU_H

#include <nds.h>
#include <string>
#include <memory>

#include "Menu.h"
#include "Game.h"
#include "gfx/Display.h"
#include "gfx/Font.h"
#include "gfx/TitleGraphic.h"

//-----------------------------------------------------------------------------
class TitleMenu : public Menu {
//-----------------------------------------------------------------------------

  static const char *options[3];
  static const int options_len = 3;

  gfx::Font unselected_font = gfx::Font(gfx::colours(0, 222, 222, 222));
  gfx::Font   selected_font = gfx::Font(gfx::colours(0, 555, 555, 555));
  gfx::Font       dark_font = gfx::Font(gfx::colours(0, 111, 111, 111));

  gfx::TitleGraphic title_graphic;

  void drawOption(std::string option, int y, bool selected);

// state
//-----------------------------------------------------------------------------
  int selected = 0;
//-----------------------------------------------------------------------------

public:

//-----------------------------------------------------------------------------
  void tick();
  void render();
//-----------------------------------------------------------------------------
};

#endif
