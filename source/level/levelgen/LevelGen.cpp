#include <custard/types.hpp>

#include "LevelGen.h"

using custard::range;
using custard::max;
using custard::abs;
using custard::pow;

// TODO: clean up code

util::Random LevelGen::random;

//-----------------------------------------------------------------------------
LevelGen::LevelGen(int w, int h, int featureSize) : w(w), h(h) {
//-----------------------------------------------------------------------------
  std::cout << "LevelGen(" << w << "," << h << "," << featureSize << ")" <<
    std::endl;
  values = new real[w * h];

  int step = featureSize;

  for (int y = 0; y < h; y += step) for (int x = 0; x < w; x += step) {
    sample(x, y) = random.nextFloat() * 2 - 1;
  }

  real scale = 1.0 / w;
  real scaleMod = 1;
  do {
    int half = step / 2;
    for (int y = 0; y < w; y += step) for (int x = 0; x < w; x += step) {
      real a = sample(x,        y       );
      real b = sample(x + step, y       );
      real c = sample(x,        y + step);
      real d = sample(x + step, y + step);

      real e = ((a + b + c + d) >> 2);
      e += ((random.nextFloat() << 1) - 1) * step * scale;
      sample(x + half, y + half) = e;
    }
    for (int y = 0; y < w; y += step) for (int x = 0; x < w; x += step) {
      real a = sample(x,        y       );
      real b = sample(x + step, y       );
      real c = sample(x,        y + step);
      real d = sample(x + half, y + half);
      real e = sample(x + half, y - half);
      real f = sample(x - half, y + half);

      real H = ((a + b + d + e) >> 2);
      H += ((random.nextFloat() << 1) - 1) * step * scale >> 1;
      real g = ((a + c + d + f) >> 2);
      g += ((random.nextFloat() << 1) - 1) * step * scale >> 1;
      sample(x + half, y       ) = H;
      sample(x,        y + half) = g;
    }
    step >>= 1;
    scale *= (scaleMod + 0.8);
    scaleMod *= 0.3;
  }
  while (step > 1);
}

#define LEVEL_LEVELGEN_LEVEL_CHECK(type, offs, test) \
  if (count[Tile::type->id + offs] test) { \
    std::cout << #type << count[Tile::type->id + offs] << ' ' << \
      #test << std::endl; \
    continue; \
  }

//-----------------------------------------------------------------------------
LevelGen::mapdata LevelGen::createAndValidateTopMap(int w, int h) {
//-----------------------------------------------------------------------------
  std::cout << "createAndValidateTopMap(" << w << "," << h << ")" << std::endl;
  do {
    mapdata result = createTopMap(w, h);

    int *count = new int[256]();
    for (int i : range(w * h)) count[result.map[i]]++;

    LEVEL_LEVELGEN_LEVEL_CHECK(rock, 0, < 100)
    LEVEL_LEVELGEN_LEVEL_CHECK(sand, 0, < 100)
    LEVEL_LEVELGEN_LEVEL_CHECK(grass, 0, < 100)
    LEVEL_LEVELGEN_LEVEL_CHECK(tree, 0, < 100)
    LEVEL_LEVELGEN_LEVEL_CHECK(stairsDown, 0, < 2)

    delete[] count;
    return result;
  }
  while (true);
}

//-----------------------------------------------------------------------------
LevelGen::mapdata LevelGen::createAndValidateUndergroundMap(
  int w, int h, int depth) {
//-----------------------------------------------------------------------------
  std::cout << "createAndValidateUndergroundMap(" << w << "," << h << "," <<
    depth << ")" << std::endl;
  do {
    mapdata result = createUndergroundMap(w, h, depth);

    int *count = new int[256]();
    for (int i : range(w * h)) count[result.map[i]]++;

    LEVEL_LEVELGEN_LEVEL_CHECK(rock, 0, < 100)
    LEVEL_LEVELGEN_LEVEL_CHECK(dirt, 0, < 100)
    LEVEL_LEVELGEN_LEVEL_CHECK(ironOre, depth - 1, < 20)
    if (depth < 3) LEVEL_LEVELGEN_LEVEL_CHECK(stairsDown, 0, < 2)

    delete[] count;
    return result;
  }
  while (true);
}

//-----------------------------------------------------------------------------
LevelGen::mapdata LevelGen::createAndValidateSkyMap(int w, int h) {
//-----------------------------------------------------------------------------
  std::cout << "createAndValidateSkyMap(" << w << "," << h << ")" << std::endl;
  do {
    mapdata result = createSkyMap(w, h);

    int *count = new int[256]();
    for (int i : range(w * h)) count[result.map[i]]++;

    LEVEL_LEVELGEN_LEVEL_CHECK(cloud, 0, < 2000)
    LEVEL_LEVELGEN_LEVEL_CHECK(stairsDown, 0, < 2)

    delete[] count;
    return result;
  }
  while (true);
}

//-----------------------------------------------------------------------------
LevelGen::mapdata LevelGen::createTopMap(int w, int h) {
//-----------------------------------------------------------------------------
  std::cout << "createTopMap(" << w << "," << h << ")" << std::endl;

  LevelGen mnoise1(w, h, 16);
  LevelGen mnoise2(w, h, 16);
  LevelGen mnoise3(w, h, 16);

  LevelGen noise1(w, h, 32);
  LevelGen noise2(w, h, 32);

  byte *map = new byte[w * h];
  byte *data = new byte[w * h];
  for (int y : range(h)) for (int x : range(w)) {
    int i = x + y * w;

    real val = abs(noise1.values[i] - noise2.values[i]) * 3 - 2;
    real mval = abs(mnoise1.values[i] - mnoise2.values[i]);
    mval = abs(mval - mnoise3.values[i]) * 3 - 2;

    real xd = abs(x / (w - 1.0) * 2 - 1);
    real yd = abs(y / (h - 1.0) * 2 - 1);
    real dist = pow(max(xd, yd), 16);
    val = val + 1 - dist * 20;

    if (val < -0.5) map[i] = Tile::water->id;
    else if (val > 0.5 && mval < -1.5) map[i] = Tile::rock->id;
    else map[i] = Tile::grass->id;
  }

  for (int i = 0; i < w * h / 2800; i++) {
    int xs = random.nextInt(w);
    int ys = random.nextInt(h);
    for (int k = 0; k < 10; k++) {
      int x = xs + random.nextInt(21) - 10;
      int y = ys + random.nextInt(21) - 10;
      for (int j = 0; j < 100; j++) {
        int xo = x + random.nextInt(5) - random.nextInt(5);
        int yo = y + random.nextInt(5) - random.nextInt(5);
        for (int yy = yo - 1; yy <= yo + 1; yy++) {
          for (int xx = xo - 1; xx <= xo + 1; xx++) {
            if (xx >= 0 && yy >= 0 && xx < w && yy < h) {
              if (map[xx + yy * w] == Tile::grass->id) {
                map[xx + yy * w] = Tile::sand->id;
              }
            }
          }
        }
      }
    }
  }

  for (int i = 0; i < w * h / 400; i++) {
    int x = random.nextInt(w);
    int y = random.nextInt(h);
    for (int j = 0; j < 200; j++) {
      int xx = x + random.nextInt(15) - random.nextInt(15);
      int yy = y + random.nextInt(15) - random.nextInt(15);
      if (xx >= 0 && yy >= 0 && xx < w && yy < h) {
        if (map[xx + yy * w] == Tile::grass->id) {
          map[xx + yy * w] = Tile::tree->id;
        }
      }
    }
  }

  for (int i = 0; i < w * h / 400; i++) {
    int x = random.nextInt(w);
    int y = random.nextInt(h);
    int col = random.nextInt(4);
    for (int j = 0; j < 30; j++) {
      int xx = x + random.nextInt(5) - random.nextInt(5);
      int yy = y + random.nextInt(5) - random.nextInt(5);
      if (xx >= 0 && yy >= 0 && xx < w && yy < h) {
        if (map[xx + yy * w] == Tile::grass->id) {
          map[xx + yy * w] = Tile::flower->id;
          data[xx + yy * w] = col + random.nextInt(4) * 16;
        }
      }
    }
  }

  for (int i = 0; i < w * h / 100; i++) {
    int xx = random.nextInt(w);
    int yy = random.nextInt(h);
    if (xx >= 0 && yy >= 0 && xx < w && yy < h) {
      if (map[xx + yy * w] == Tile::sand->id) {
        map[xx + yy * w] = Tile::cactus->id;
      }
    }
  }

  int count = 0;
  for (int i = 0; i < w * h / 100; i++) {
    int x = random.nextInt(w - 2) + 1;
    int y = random.nextInt(h - 2) + 1;

    bool good = true;
    for (int yy = y - 1; yy <= y + 1 && good; yy++) {
      for (int xx = x - 1; xx <= x + 1 && good; xx++) {
        if (map[xx + yy * w] != Tile::rock->id) good = false;
      }
    }

    if (good) {
      map[x + y * w] = Tile::stairsDown->id;
      if (++count == 4) break;
    }
  }

  return mapdata { map, data };
}

//-----------------------------------------------------------------------------
LevelGen::mapdata LevelGen::createUndergroundMap(int w, int h, int depth) {
//-----------------------------------------------------------------------------
  std::cout << "createUndergroundMap(" << w << "," << h << "," << depth <<
    ")" << std::endl;

  LevelGen mnoise1(w, h, 16);
  LevelGen mnoise2(w, h, 16);
  LevelGen mnoise3(w, h, 16);

  LevelGen nnoise1(w, h, 16);
  LevelGen nnoise2(w, h, 16);
  LevelGen nnoise3(w, h, 16);

  LevelGen wnoise1(w, h, 16);
  LevelGen wnoise2(w, h, 16);
  LevelGen wnoise3(w, h, 16);

  LevelGen noise1(w, h, 32);
  LevelGen noise2(w, h, 32);

  byte *map = new byte[w * h];
  byte *data = new byte[w * h];
  for (int y : range(h)) for (int x : range(w)) {
    int i = x + y * w;

    real val = abs(noise1.values[i] - noise2.values[i]) * 3 - 2;

    real mval = abs(mnoise1.values[i] - mnoise2.values[i]);
    mval = abs(mval - mnoise3.values[i]) * 3 - 2;

    real nval = abs(nnoise1.values[i] - nnoise2.values[i]);
    nval = abs(nval - nnoise3.values[i]) * 3 - 2;

    real wval = abs(wnoise1.values[i] - wnoise2.values[i]);
    wval = abs(nval - wnoise3.values[i]) * 3 - 2;

    real xd = abs(x / (w - 1.0) * 2 - 1);
    real yd = abs(y / (h - 1.0) * 2 - 1);
    real dist = pow(max(xd, yd), 16);
    val = val + 1 - dist * 20;

    if (val > -2 && wval < -2.0 + (depth) / 2 * 3) {
      if (depth > 2) map[i] = Tile::lava->id;
      else map[i] = Tile::water->id;
    }
    else if (val > -2 && (mval < -1.7 || nval < -1.4)) {
      map[i] = Tile::dirt->id;
    }
    else map[i] = Tile::rock->id;
  }

  int r = 2;
  for (int i = 0; i < w * h / 400; i++) {
    int x = random.nextInt(w);
    int y = random.nextInt(h);
    for (int j = 0; j < 30; j++) {
      int xx = x + random.nextInt(5) - random.nextInt(5);
      int yy = y + random.nextInt(5) - random.nextInt(5);
      if (xx >= r && yy >= r && xx < w - r && yy < h - r) {
        if (map[xx + yy * w] == Tile::rock->id) {
          map[xx + yy * w] = Tile::ironOre->id + depth - 1;
        }
      }
    }
  }

  if (depth < 3) {
    int count = 0;
    for (int i = 0; i < w * h / 100; i++) {
      int x = random.nextInt(w - 20) + 10;
      int y = random.nextInt(h - 20) + 10;

      bool good = true;
      for (int yy = y - 1; yy <= y + 1 && good; yy++) {
        for (int xx = x - 1; xx <= x + 1 && good; xx++) {
          if (map[xx + yy * w] != Tile::rock->id) good = false;
        }
      }

      if (good) {
        map[x + y * w] = Tile::stairsDown->id;
        if (++count == 4) break;
      }
    }
  }

  return mapdata { map, data };
}

//-----------------------------------------------------------------------------
LevelGen::mapdata LevelGen::createSkyMap(int w, int h) {
//-----------------------------------------------------------------------------
  std::cout << "createSkyMap(" << w << "," << h << ")" << std::endl;

  LevelGen noise1(w, h, 8);
  LevelGen noise2(w, h, 8);

  byte *map = new byte[w * h];
  byte *data = new byte[w * h];
  for (int y : range(h)) for (int x : range(w)) {
    int i = x + y * w;

    real val = abs(noise1.values[i] - noise2.values[i]) * 3 - 2;

    real xd = abs(x / (w - 1.0) * 2 - 1);
    real yd = abs(y / (h - 1.0) * 2 - 1);
    real dist = pow(max(xd, yd), 16);
    val = -val * 1 - 2.2;
    val = val + 1 - dist * 20;

    map[i] = val < -0.25 ? Tile::infiniteFall->id : Tile::cloud->id;
  }

  for (int i = 0; i < w * h / 50; i++) {
    int x = random.nextInt(w - 2) + 1;
    int y = random.nextInt(h - 2) + 1;

    bool good = true;
    for (int yy = y - 1; yy <= y + 1 && good; yy++) {
      for (int xx = x - 1; xx <= x + 1 && good; xx++) {
        if (map[xx + yy * w] != Tile::cloud->id) good = false;
      }
    }

    if (good) map[x + y * w] = Tile::cloudCactus->id;
  }

  int count = 0;
  for (int i : range(w * h)) {
    int x = random.nextInt(w - 2) + 1;
    int y = random.nextInt(h - 2) + 1;

    bool good = true;
    for (int yy = y - 1; yy <= y + 1 && good; yy++) {
      for (int xx = x - 1; xx <= x + 1 && good; xx++) {
        if (map[xx + yy * w] != Tile::cloud->id) good = false;
      }
    }

    if (good) {
      map[x + y * w] = Tile::stairsDown->id;
      if (++count == 2) break;
    }
  }

  return mapdata { map, data };
}

// void LevelGen::main(String[] args) {
//   int d = 0;
//   while (true) {
//     int w = 128;
//     int h = 128;

//     byte *map = LevelGen.createAndValidateTopMap(w, h)[0];
//     // byte *map = LevelGen.createAndValidateUndergroundMap(
//     //   w, h, (d++ % 3) + 1)[0];
//     // byte *map = LevelGen.createAndValidateSkyMap(w, h)[0];

//     BufferedImage img = new BufferedImage(w, h, BufferedImage.TYPE_INT_RGB);
//     int *pixels = new int[w * h];
//     for (int y = 0; y < h; y++) {
//       for (int x = 0; x < w; x++) {
//         int i = x + y * w;

//         if (map[i] == Tile::water->id) pixels[i] = 0x000080;
//         if (map[i] == Tile::grass->id) pixels[i] = 0x208020;
//         if (map[i] == Tile::rock->id) pixels[i] = 0xa0a0a0;
//         if (map[i] == Tile::dirt->id) pixels[i] = 0x604040;
//         if (map[i] == Tile::sand->id) pixels[i] = 0xa0a040;
//         if (map[i] == Tile::tree->id) pixels[i] = 0x003000;
//         if (map[i] == Tile::lava->id) pixels[i] = 0xff2020;
//         if (map[i] == Tile::cloud->id) pixels[i] = 0xa0a0a0;
//         if (map[i] == Tile::stairsDown->id) pixels[i] = 0xffffff;
//         if (map[i] == Tile::stairsUp->id) pixels[i] = 0xffffff;
//         if (map[i] == Tile::cloudCactus->id) pixels[i] = 0xff00ff;
//       }
//     }
//     img.setRGB(0, 0, w, h, pixels, 0, w);
//     JOptionPane.showMessageDialog(null, null, "Another",
//       JOptionPane.YES_NO_OPTION, new ImageIcon(img.getScaledInstance(
//         w * 4, h * 4, Image.SCALE_AREA_AVERAGING)));
//   }
// }
