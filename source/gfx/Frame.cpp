#include <nds.h>

#include "gfx/Frame.h"

#include "gfx/Display.h"
#include "gfx/TileId.h"

using namespace gfx;

void Frame::render(const char *title, int x0, int y0, int x1, int y1) {

  if (!box_tileIds_initialised) {
    for (int i = 0; i < 3; i++) {
      box_tileIds[i] = display.allocTile(13 * 32 + i, colours(-1, 1, 5, 445));
    }
    box_tileIds[3] = display.allocTile(13 * 32 + 2, colours(5, 5, 5, 5));
    box_tileIds_initialised = true;
  }

  for (int y = y0; y <= y1; y++) {
    for (int x = x0; x <= x1; x++) {
      if (x == x0 && y == y0)
        display.gui_layer.drawTile(box_tileIds[0], x, y, 0);
      else if (x == x1 && y == y0)
        display.gui_layer.drawTile(box_tileIds[0], x, y, 1);
      else if (x == x0 && y == y1)
        display.gui_layer.drawTile(box_tileIds[0], x, y, 2);
      else if (x == x1 && y == y1)
        display.gui_layer.drawTile(box_tileIds[0], x, y, 3);
      else if (y == y0)
        display.gui_layer.drawTile(box_tileIds[1], x, y, 0);
      else if (y == y1)
        display.gui_layer.drawTile(box_tileIds[1], x, y, 2);
      else if (x == x0)
        display.gui_layer.drawTile(box_tileIds[2], x, y, 0);
      else if (x == x1)
        display.gui_layer.drawTile(box_tileIds[2], x, y, 1);
      else
        display.gui_layer.drawTile(box_tileIds[3], x, y, 1);
    }
  }

  title_font.draw(title, display.gui_layer, x0 + 1, y0);
}

TileId Frame::box_tileIds[4];
bool Frame::box_tileIds_initialised = false;

Font Frame::title_font(colours(5, 5, 5, 550));
