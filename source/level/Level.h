#ifndef LEVEL_LEVEL_H
#define LEVEL_LEVEL_H

#include <nds.h>
#include <custard/types.hpp>

#include "tile/Tile.h"
#include "gfx/Display.h"
#include "gfx/BitmapLayer.h"
#include "entity/Player.h"
#include "util/Random.h"

// com.mojang.ld22.level.Level
//-----------------------------------------------------------------------------
struct Level {
//-----------------------------------------------------------------------------

  util::Random random;

// parameters
//-----------------------------------------------------------------------------
  custard::ivec2 shape; // width and height, originally int w, h
  int depth; // signed number of levels above ground level
//-----------------------------------------------------------------------------

// global properties
//-----------------------------------------------------------------------------
  int grassColor = 141;
  int dirtColor = depth == 1 ? 444 : depth < 0 ? 222 : 322;
  int sandColor = 550;
  int monsterDensity = depth ? 4 : 8;
//-----------------------------------------------------------------------------

  u8 *tiles, *data;

  // public List<Entity>[] entitiesInTiles;

  // public List<Entity> entities = new ArrayList<Entity>();
  // private Comparator<Entity> spriteSorter = new Comparator<Entity>() {
  //   public int compare(Entity e0, Entity e1) {
  //     if (e1.y < e0.y) return +1;
  //     if (e1.y > e0.y) return -1;
  //     return 0;
  //   }
  // };

//-----------------------------------------------------------------------------
  Level(int w, int h, int level, Level *parentLevel);
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
  void renderBackground(gfx::TileLayer layer, custard::ivec2 scroll);
//-----------------------------------------------------------------------------

  // private List<Entity> rowSprites = new ArrayList<Entity>();

  Player *player;

  // public void renderSprites(Screen screen, int xScroll, int yScroll) {
  //   int xo = xScroll >> 4;
  //   int yo = yScroll >> 4;
  //   int w = (screen.w + 15) >> 4;
  //   int h = (screen.h + 15) >> 4;

  //   screen.setOffset(xScroll, yScroll);
  //   for (int y = yo; y <= h + yo; y++) {
  //     for (int x = xo; x <= w + xo; x++) {
  //       if (x < 0 || y < 0 || x >= this.w || y >= this.h) continue;
  //       rowSprites.addAll(entitiesInTiles[x + y * this.w]);
  //     }
  //     if (rowSprites.size() > 0) {
  //       sortAndRender(screen, rowSprites);
  //     }
  //     rowSprites.clear();
  //   }
  //   screen.setOffset(0, 0);
  // }

  void renderLight(gfx::BitmapLayer layer, custard::ivec2 scroll) {
    // int xo = xScroll >> 4;
    // int yo = yScroll >> 4;
    // int w = (screen.w + 15) >> 4;
    // int h = (screen.h + 15) >> 4;

    // screen.setOffset(xScroll, yScroll);
    // int r = 4;
    // for (int y = yo - r; y <= h + yo + r; y++) {
    //   for (int x = xo - r; x <= w + xo + r; x++) {
    //     if (x < 0 || y < 0 || x >= this.w || y >= this.h) continue;
    //     List<Entity> entities = entitiesInTiles[x + y * this.w];
    //     for (int i = 0; i < entities.size(); i++) {
    //       Entity e = entities.get(i);
    //       // e.render(screen);
    //       int lr = e.getLightRadius();
    //       if (lr > 0) screen.renderLight(e.x - 1, e.y - 4, lr * 8);
    //     }
    //     int lr = getTile(x, y).getLightRadius(this, x, y);
    //     if (lr > 0) screen.renderLight(x * 16 + 8, y * 16 + 8, lr * 8);
    //   }
    // }
    // screen.setOffset(0, 0);
  }

  // private void sortAndRender(Screen screen, List<Entity> list) {
  //   Collections.sort(list, spriteSorter);
  //   for (int i = 0; i < list.size(); i++) {
  //     list.get(i).render(screen);
  //   }
  // }

// query tile type at location
//-----------------------------------------------------------------------------
  Tile *getTile(int x, int y) {
//-----------------------------------------------------------------------------
    if (x < 0 || y < 0 || x >= shape.x || y >= shape.y) return Tile::rock;
    return Tile::tiles[tiles[x + y * shape.x]];
  }

// set tile type and optionally data value at location
//-----------------------------------------------------------------------------
  void setTile(int x, int y, Tile *tile, u8 value = 0) {
//-----------------------------------------------------------------------------
    if (x < 0 || y < 0 || x >= shape.x || y >= shape.y) return;
    tiles[x + y * shape.x] = tile->id;
    data[x + y * shape.x] = value;
  }

// query data value at location
//-----------------------------------------------------------------------------
  u8 getData(int x, int y) {
//-----------------------------------------------------------------------------
    if (x < 0 || y < 0 || x >= shape.x || y >= shape.y) return 0;
    return data[x + y * shape.x];
  }

// set data value at location
//-----------------------------------------------------------------------------
  void setData(int x, int y, u8 value) {
//-----------------------------------------------------------------------------
    if (x < 0 || y < 0 || x >= shape.x || y >= shape.y) return;
    data[x + y * shape.x] = value;
  }

  // public void add(Entity entity) {
  //   if (entity instanceof Player) {
  //     player = (Player) entity;
  //   }
  //   entity.removed = false;
  //   entities.add(entity);
  //   entity.init(this);

  //   insertEntity(entity.x >> 4, entity.y >> 4, entity);
  // }

  // public void remove(Entity e) {
  //   entities.remove(e);
  //   int xto = e.x >> 4;
  //   int yto = e.y >> 4;
  //   removeEntity(xto, yto, e);
  // }

  // private void insertEntity(int x, int y, Entity e) {
  //   if (x < 0 || y < 0 || x >= w || y >= h) return;
  //   entitiesInTiles[x + y * w].add(e);
  // }

  // private void removeEntity(int x, int y, Entity e) {
  //   if (x < 0 || y < 0 || x >= w || y >= h) return;
  //   entitiesInTiles[x + y * w].remove(e);
  // }

  void trySpawn(int count) {
    // for (int i = 0; i < count; i++) {
    //   Mob mob;

    //   int minLevel = 1;
    //   int maxLevel = 1;
    //   if (depth < 0) {
    //     maxLevel = (-depth) + 1;
    //   }
    //   if (depth > 0) {
    //     minLevel = maxLevel = 4;
    //   }

    //   int lvl = random.nextInt(maxLevel - minLevel + 1) + minLevel;
    //   if (random.nextInt(2) == 0)
    //     mob = new Slime(lvl);
    //   else
    //     mob = new Zombie(lvl);

    //   if (mob.findStartPos(this)) {
    //     this.add(mob);
    //   }
    // }
  }

  void tick() {
    trySpawn(1);

    // for (int i = 0; i < w * h / 50; i++) {
    //   int xt = random.nextInt(w);
    //   int yt = random.nextInt(w);
    //   getTile(xt, yt).tick(this, xt, yt);
    // }
    // for (int i = 0; i < entities.size(); i++) {
    //   Entity e = entities.get(i);
    //   int xto = e.x >> 4;
    //   int yto = e.y >> 4;

    //   e.tick();

    //   if (e.removed) {
    //     entities.remove(i--);
    //     removeEntity(xto, yto, e);
    //   } else {
    //     int xt = e.x >> 4;
    //     int yt = e.y >> 4;

    //     if (xto != xt || yto != yt) {
    //       removeEntity(xto, yto, e);
    //       insertEntity(xt, yt, e);
    //     }
    //   }
    // }
  }

  // public List<Entity> getEntities(int x0, int y0, int x1, int y1) {
  //   List<Entity> result = new ArrayList<Entity>();
  //   int xt0 = (x0 >> 4) - 1;
  //   int yt0 = (y0 >> 4) - 1;
  //   int xt1 = (x1 >> 4) + 1;
  //   int yt1 = (y1 >> 4) + 1;
  //   for (int y = yt0; y <= yt1; y++) {
  //     for (int x = xt0; x <= xt1; x++) {
  //       if (x < 0 || y < 0 || x >= w || y >= h) continue;
  //       List<Entity> entities = entitiesInTiles[x + y * this.w];
  //       for (int i = 0; i < entities.size(); i++) {
  //         Entity e = entities.get(i);
  //         if (e.intersects(x0, y0, x1, y1)) result.add(e);
  //       }
  //     }
  //   }
  //   return result;
  // }
};

#endif
