#ifndef GFX_TITLEGRAPHIC_H
#define GFX_TITLEGRAPHIC_H

#include <nds.h>

#include "Display.h"
#include "TileId.h"

namespace gfx {

//-----------------------------------------------------------------------------
class TitleGraphic {
//-----------------------------------------------------------------------------

  TileId tileIds[13][2];

public:

  TitleGraphic() {
    for (int y = 0; y < 2; y++) {
      for (int x = 0; x < 13; x++) {
        tileIds[x][y] = display.allocTile(x + (y + 6) * 32, colours(0, 10, 131, 551));
      }
    }
  }

  ~TitleGraphic() {
    for (int y = 0; y < 2; y++) {
      for (int x = 0; x < 13; x++) {
        display.freeTile(tileIds[x][y]);
      }
    }
  }

  void render(TileLayer layer, int x0, int y0) {
    for (int y = 0; y < 2; y++) {
      for (int x = 0; x < 13; x++) {
        layer.drawTile(tileIds[x][y], x0 + x, y0 + y);
      }
    }
  }
};

}

#endif
