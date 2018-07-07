#ifndef GFX_FRAME_H
#define GFX_FRAME_H

#include <nds.h>
#include <vector>

#include "TileId.h"
#include "TileLayer.h"
#include "Font.h"

namespace gfx {

//-----------------------------------------------------------------------------
class Frame {
//-----------------------------------------------------------------------------

  static TileId box_tileIds[4];
  static bool box_tileIds_initialised;

  static Font title_font;

public:

  static void render(const char *title, int x0, int y0, int x1, int y1);
};

}

#endif
