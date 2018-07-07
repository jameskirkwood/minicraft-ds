#ifndef GFX_FONT_H
#define GFX_FONT_H

#include <nds.h>

#include "TileId.h"
#include "TileLayer.h"

namespace gfx {

//-----------------------------------------------------------------------------
class Font {
//-----------------------------------------------------------------------------

  static u8 char_glyphOffsets[95];

  u32 palette;

  mutable TileId tileIds[55];

public:

  Font(u32 palette) : palette(palette) {
    for (int i = 0; i < 55; i++) tileIds[i] = 0;
  }

  ~Font();

  void draw(const char *text, TileLayer layer, int x, int y) const;
};

}

#endif
