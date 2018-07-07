#include <nds.h>

#include "Level.h"

#include "levelgen/LevelGen.h"

using custard::ivec2;
using custard::range;
using custard::range2;
using gfx::display;

//-----------------------------------------------------------------------------
Level::Level(int w, int h, int level, Level *parentLevel) :
shape(w, h), depth(level) {
//-----------------------------------------------------------------------------
  LevelGen::mapdata maps;

  if (level == 0) maps = LevelGen::createAndValidateTopMap(w, h);
  else if (level < 0) {
    maps = LevelGen::createAndValidateUndergroundMap(w, h, -level);
  }
  else maps = LevelGen::createAndValidateSkyMap(w, h);

  tiles = maps.map;
  data = maps.data;

  if (parentLevel) {
    for (auto pos : range2(w, h)) {
      if (parentLevel->getTile(pos.x, pos.y) == Tile::stairsDown) {
        Tile *gird = level ? Tile::dirt : Tile::hardRock;
        setTile(pos.x - 1, pos.y - 1, gird, 0);
        setTile(pos.x,     pos.y - 1, gird, 0);
        setTile(pos.x + 1, pos.y - 1, gird, 0);
        setTile(pos.x - 1, pos.y,     gird, 0);
        setTile(pos.x,     pos.y,     Tile::stairsUp, 0);
        setTile(pos.x + 1, pos.y,     gird, 0);
        setTile(pos.x - 1, pos.y + 1, gird, 0);
        setTile(pos.x,     pos.y + 1, gird, 0);
        setTile(pos.x + 1, pos.y + 1, gird, 0);
      }
    }
  }

  // entitiesInTiles = new ArrayList[w * h];
  // for (int i = 0; i < w * h; i++) {
  //   entitiesInTiles[i] = new ArrayList<Entity>();
  // }

  // if (level==1) {
  //   AirWizard aw = new AirWizard();
  //   aw.x = w*8;
  //   aw.y = h*8;
  //   add(aw);
  // }

  // TODO REMOVE
  // cells = new Cell[w * h];
  // for (int i = 0; i < h; i++) for (int j = 0; j < w; j++) {
  //   cells[i * w + j].tile = Tile::rock->id;
  // }
}

//-----------------------------------------------------------------------------
void Level::renderBackground(gfx::TileLayer layer, ivec2 scroll) {
//-----------------------------------------------------------------------------
  for (auto disp_pos : range((display.shape >> 4) + 1)) {
    auto pos = (scroll >> 4) + disp_pos;
    auto block = getTile(pos.x, pos.y)->getBlock(this, pos.x, pos.y);
    for (int k = 0; k < 4; k++) layer.drawTile(
      block.tiles[k],
      ((disp_pos.x & 15) << 1) | (k & 1),
      ((disp_pos.y | (disp_pos.x & 16)) << 1) | (k >> 1),
      block.bits[k]);
  }
}
