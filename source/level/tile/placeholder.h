#ifndef LEVEL_TILE_PLACEHOLDER_H
#define LEVEL_TILE_PLACEHOLDER_H

#include "Tile.h"
#include "gfx/Display.h"
#include "gfx/TileId.h"
#include "gfx/Block.h"
#include "level/Level.h"

namespace tile {

// for testing purposes, no equivalent in original code
//-----------------------------------------------------------------------------
class placeholder : public Tile {
//-----------------------------------------------------------------------------

  gfx::TileId tid = 0;
  int colours;

public:

//-----------------------------------------------------------------------------
   placeholder(int c) : colours(gfx::colours(c, c, c, c)) {}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
  gfx::Block getBlock(Level *level, int x, int y) {
//-----------------------------------------------------------------------------
    if (!tid) tid = gfx::display.allocTile(0, colours);
    gfx::Block block;
    for (int i = 0; i < 4; i++) block.tiles[i] = tid;
    return block;
  }
};

}

#endif
