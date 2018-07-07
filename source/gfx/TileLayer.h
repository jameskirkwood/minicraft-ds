#ifndef GFX_TILELAYER_H
#define GFX_TILELAYER_H

#include <nds.h>

#include "Layer.h"
#include "TileId.h"

namespace gfx {

//-----------------------------------------------------------------------------
struct TileLayer : public Layer {
//-----------------------------------------------------------------------------

  TileLayer(int bgIndex, int mapBase, int tileBase, BgSize size) {
    bgId = bgInit(bgIndex, BgType_Text8bpp, size, mapBase, tileBase);
  }

  void drawTile(TileId tileId, int x, int y, int bits = 0) {
    bgGetMapPtr(bgId)[(y << 5) + x] = (tileId - 1) | (bits << 10);
  }

  void clear(TileId tileId, int bits = 0) {
    for (int x = 0; x < 32; x++) {
      for (int y = 0; y < 24; y++) {
        drawTile(tileId, x, y, bits);
      }
    }
  }
};

}

#endif
