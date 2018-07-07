#ifndef GFX_BLOCK_H
#define GFX_BLOCK_H

#include "Display.h"

namespace gfx {

//-----------------------------------------------------------------------------
struct Block {
//-----------------------------------------------------------------------------
  TileId tiles[4];
  char bits[4];
};

}

#endif
