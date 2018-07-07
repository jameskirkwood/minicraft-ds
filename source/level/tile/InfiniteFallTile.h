#ifndef LEVEL_TILE_INFINITEFALLTILE_H
#define LEVEL_TILE_INFINITEFALLTILE_H

#include "Tile.h"
#include "gfx/Display.h"
#include "gfx/TileId.h"
#include "gfx/Block.h"
#include "level/Level.h"

namespace tile {

class InfiniteFallTile : public Tile {

private:

  gfx::Block getBlock(Level *level, int x, int y);
};

}

#endif
