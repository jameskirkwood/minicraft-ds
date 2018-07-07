#include <nds.h>

#include "RockTile.h"

using namespace tile;

gfx::Block RockTile::getBlock(Level *level, int x, int y) {

  if (!test_tileId) test_tileId = gfx::display.allocTile(0, gfx::colours(444, 444, 333, 333));

  gfx::Block block;

  for (int i = 0; i < 4; i++) block.tiles[i] = test_tileId;

  return block;
}
