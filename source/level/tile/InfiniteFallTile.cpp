#include <nds.h>

#include "InfiniteFallTile.h"

#include "gfx/Display.h"

using namespace tile;

gfx::Block InfiniteFallTile::getBlock(Level *level, int x, int y) {

  gfx::Block block;

  for (int i = 0; i < 4; i++) block.tiles[i] = gfx::display.clear;

  return block;
}
