#ifndef GFX_TILESET_H
#define GFX_TILESET_H

#include <nds.h>
#include <vector>
#include <_ansi.h> // sassert

#include "TileId.h"

namespace gfx {

//-----------------------------------------------------------------------------
class TileSet {
//-----------------------------------------------------------------------------

private:

  // Coordinates of the top left tile of the resource in the sprite sheet
  char res_x, res_y;

  // Width and height in tiles of the resource in the sprite sheet
  char res_w, res_h;

  u32 palette;

  std::vector<TileId> tileIds;

  u32 references;

public:

  TileSet(int res_x, int res_y, int res_w, int res_h, u32 palette) :
    res_x(res_x), res_y(res_y), res_w(res_w), res_h(res_h),
    palette(palette),
    tileIds(res_w * res_h, 0),
    references(0) {}

  ~TileSet() {
    sassert(references == 0, "TileSet In Use Upon Destruction");
    for (int i = 0; i < res_w * res_h; i++) {
      if (tileIds[i]) DISPLAY.freeTile(tileIds[i]);
    }
  }

  void obtain() {
    if (references++ == 0) {
      for (int y = 0; y < res_h; y++) {
        for (int x = 0; x < res_w; x++) {
          tileIds[y * res_w + x] = DISPLAY::allocTile((res_y + y) * 32 + (res_x + x), palette);
        }
      }
    }
  }

  void release() {
    sassert(references > 0, "Released TileSet Not Obtained");
    if (--references == 0) {
      for (int i = 0; i < res_w * res_h; i++) {
        if (tileIds[i]) DISPLAY.freeTile(tileIds[i]);
      }
    }
  }

  TileId get(int tile_x, int tile_y) const {
    sassert(references > 0, "Accessed TileSet Not Obtained");
    return tileIds[tile_y * w + tile_x];
  }
};

}

#endif
