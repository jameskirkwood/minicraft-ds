#ifndef LEVEL_TILE_GRASSTILE_H
#define LEVEL_TILE_GRASSTILE_H

#include "Tile.h"
#include "gfx/Display.h"
#include "gfx/TileId.h"
#include "gfx/Block.h"
#include "level/Level.h"

namespace tile {

//-----------------------------------------------------------------------------
class GrassTile : public Tile {
//-----------------------------------------------------------------------------

  gfx::TileId test = 0;

//-----------------------------------------------------------------------------
  gfx::Block getBlock(Level *level, int x, int y) {
//-----------------------------------------------------------------------------
    if (!test) test = gfx::display.allocTile(
      0, gfx::colours(353, 353, 131, 131));
    gfx::Block block;
    for (int i = 0; i < 4; i++) block.tiles[i] = test;
    return block;
  }
};

}

#endif
