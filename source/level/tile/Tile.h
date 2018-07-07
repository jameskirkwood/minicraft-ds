#ifndef LEVEL_TILE_TILE_H
#define LEVEL_TILE_TILE_H

#include "gfx/Block.h"

class Level; // level/Level.h

//-----------------------------------------------------------------------------
class Tile {
//-----------------------------------------------------------------------------

  static u8 freeId;

public:

// tile types by ID
//-----------------------------------------------------------------------------
  static Tile *tiles[256];
//-----------------------------------------------------------------------------

// tile types by name
//-----------------------------------------------------------------------------
  static Tile
    *grass,  *rock,  *water,  *flower,  *tree,  *dirt, *sand, *cactus, *hole,
    *treeSapling,  *cactusSapling,  *farmland,  *wheat,  *lava,  *stairsDown,
    *stairsUp, *infiniteFall, *cloud, *hardRock, *ironOre, *goldOre, *gemOre,
    *cloudCactus;
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// tile type interface
//-----------------------------------------------------------------------------

  u8 id; // ID of tile type (useful if looked up by name)

// automatically assign IDs to up to 256 tile types
//-----------------------------------------------------------------------------
  Tile() : id(freeId++) { tiles[id] = this; }
//-----------------------------------------------------------------------------

  virtual gfx::Block getBlock(Level *level, int x, int y) = 0;
};

#endif
