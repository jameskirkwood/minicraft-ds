#ifndef LEVEL_TILE_ROCKTILE_H
#define LEVEL_TILE_ROCKTILE_H

#include "Tile.h"
#include "gfx/Display.h"
#include "gfx/TileId.h"
#include "gfx/Block.h"
#include "level/Level.h"

namespace tile {

class RockTile : public Tile {

private:

  gfx::TileId test_tileId = 0;

  gfx::Block getBlock(Level *level, int x, int y);
};

}

#endif
