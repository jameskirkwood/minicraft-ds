#ifndef LEVEL_LEVELGEN_LEVELGEN_H
#define LEVEL_LEVELGEN_LEVELGEN_H

#include <nds.h>
#include <custard/types.hpp>
#include <iostream>

#include "util/Random.h"
#include "level/tile/Tile.h"

// com.mojang.ld22.level.levelgen.LevelGen
//-----------------------------------------------------------------------------
class LevelGen {
//-----------------------------------------------------------------------------

  // 20.12 fixed point used instead of double for efficiency
  typedef custard::q12 real;

  static util::Random random;

//-----------------------------------------------------------------------------
// scalar valued noise texture
//-----------------------------------------------------------------------------

  real *values;
  int w, h;

//-----------------------------------------------------------------------------
  LevelGen(int w, int h, int featureSize);
  ~LevelGen() { delete[] values; }
//-----------------------------------------------------------------------------

// sample noise texture (w and h must be powers of two)
//-----------------------------------------------------------------------------
  real& sample(int x, int y) {
//-----------------------------------------------------------------------------
    return values[(x & (w - 1)) + (y & (h - 1)) * w];
  }

// overwrite noise texture (w and h must be powers of two)
//-----------------------------------------------------------------------------
  void setSample(int x, int y, real value) {
//-----------------------------------------------------------------------------
    values[(x & (w - 1)) + (y & (h - 1)) * w] = value;
  }

//-----------------------------------------------------------------------------
// map generators
//-----------------------------------------------------------------------------
public:

  typedef unsigned char byte;
  struct mapdata { byte *map, *data; }; // in place of byte[][]

  static mapdata createAndValidateTopMap(int w, int h);
  static mapdata createAndValidateUndergroundMap(int w, int h, int depth);
  static mapdata createAndValidateSkyMap(int w, int h);

private:
  static mapdata createTopMap(int w, int h);
  static mapdata createUndergroundMap(int w, int h, int depth);
  static mapdata createSkyMap(int w, int h);
};

#endif
