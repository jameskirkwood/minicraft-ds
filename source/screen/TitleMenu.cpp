#include <nds.h>
#include <string>

#include "sound/Sound.h"
#include "InputHandler.h"

#include "screen/TitleMenu.h"
#include "screen/InstructionsMenu.h"
#include "screen/AboutMenu.h"

//-----------------------------------------------------------------------------
const char *TitleMenu::options[] = { "Start game", "How to play", "About" };
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
void TitleMenu::drawOption(std::string option, int y, bool selected) {
//-----------------------------------------------------------------------------
  const gfx::Font& font = selected ? selected_font : unselected_font;
  const char *name = (selected ? ("> " + option + " <") : option).c_str();
  const gfx::TileLayer& layer = option.length() & 1 ?
    gfx::display.sky_layer : gfx::display.gui_layer;
  const int x = (32 - option.length()) / 2 - selected * 2;
  font.draw(name, layer, x, y);
}

//-----------------------------------------------------------------------------
void TitleMenu::tick() {
//-----------------------------------------------------------------------------
  selected += input.down.clicked - input.up.clicked;
  selected = (selected + options_len) % options_len;

  if (input.attack.clicked || input.menu.clicked) {
    if (selected == 0) {
      Sound::test.play();
      game->resetGame();
      game->setMenu(nullptr);
    }
    if (selected == 1) game->setMenu(new InstructionsMenu(shared_from_this()));
    if (selected == 2) game->setMenu(new        AboutMenu(shared_from_this()));
  }
}

//-----------------------------------------------------------------------------
void TitleMenu::render() {
//-----------------------------------------------------------------------------
  gfx::display.world_layer.hide();
  gfx::display.light_layer.hide();

  gfx::display.gui_layer.clear(gfx::display.black);
  gfx::display.gui_layer.setScroll(0, 0);
  gfx::display.gui_layer.show();

  gfx::display.sky_layer.clear(gfx::display.clear);
  gfx::display.sky_layer.setScroll(-4, 0);
  gfx::display.sky_layer.show();

  title_graphic.render(gfx::display.sky_layer, 9, 8);

  for (int i = 0; i < options_len; i++) {
    drawOption(options[i], 13 + i, i == selected);
  }

  dark_font.draw("(D-Pad, A and B)",
    gfx::display.gui_layer, 8, gfx::display.TILES_HIGH - 1);
}
