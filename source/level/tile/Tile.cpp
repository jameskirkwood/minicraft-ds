#include <nds.h>

#include "Tile.h"
#include "placeholder.h"

#include "GrassTile.h"
#include "RockTile.h"
#include "InfiniteFallTile.h"

u8 Tile::freeId = 0;

Tile *Tile::tiles[256];

Tile *Tile::grass = new tile::placeholder(131);
Tile *Tile::rock = new tile::placeholder(444);
Tile *Tile::water = new tile::placeholder(3); // new WaterTile();
Tile *Tile::flower = new tile::placeholder(331); // new FlowerTile();
Tile *Tile::tree = new tile::placeholder(10); // new TreeTile();
Tile *Tile::dirt = new tile::placeholder(211); // new DirtTile();
Tile *Tile::sand = new tile::placeholder(441); // new SandTile();
Tile *Tile::cactus = new tile::placeholder(454); // new CactusTile();
Tile *Tile::hole = new tile::placeholder(505); // new HoleTile();
Tile *Tile::treeSapling = new tile::placeholder(505); // new SaplingTile(grass, tree);
Tile *Tile::cactusSapling = new tile::placeholder(505); // new SaplingTile(sand, cactus);
Tile *Tile::farmland = new tile::placeholder(505); // new FarmTile();
Tile *Tile::wheat = new tile::placeholder(505); // new WheatTile();
Tile *Tile::lava = new tile::placeholder(511); // new LavaTile();
Tile *Tile::stairsDown = new tile::placeholder(5); // new StairsTile(false);
Tile *Tile::stairsUp = new tile::placeholder(500); // new StairsTile(true);
Tile *Tile::infiniteFall = new tile::InfiniteFallTile();
Tile *Tile::cloud = new tile::placeholder(555); // new CloudTile();
Tile *Tile::hardRock = new tile::placeholder(111); // new HardRockTile();
Tile *Tile::ironOre = new tile::placeholder(432); // new OreTile(Resource::ironOre);
Tile *Tile::goldOre = new tile::placeholder(342); // new OreTile(Resource::goldOre);
Tile *Tile::gemOre = new tile::placeholder(234); // new OreTile(Resource::gem);
Tile *Tile::cloudCactus = new tile::placeholder(505); // new CloudCactusTile();
