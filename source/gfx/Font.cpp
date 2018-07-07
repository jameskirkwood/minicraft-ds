#include <nds.h>

#include "Font.h"

#include "Display.h"

using namespace gfx;

Font::~Font() {

  for (u32 i = 0; i < 55; i++) {
    if (tileIds[i]) gfx::display.freeTile(tileIds[i]);
  }
}

void Font::draw(const char *text, TileLayer layer, int x, int y) const {

  for (u32 i = 0; text[i] != 0; i++) {
    u8 glyphOffset = char_glyphOffsets[text[i] - ' '];
    if (tileIds[glyphOffset] == 0) {
      tileIds[glyphOffset] = gfx::display.allocTile(30 * 32 + glyphOffset + (glyphOffset < 26 ? 0 : 6), palette);
    }
    layer.drawTile(tileIds[glyphOffset], x + i, y, 0);
  }
}

u8 Font::char_glyphOffsets[95] = {
  54, 38, 41, 39, 39, 47, 39, 40,
  48, 49, 39, 43, 37, 42, 36, 45,
  26, 27, 28, 29, 30, 31, 32, 33,
  34, 35, 52, 53, 50, 44, 51, 39,
  39,  0,  1,  2,  3,  4,  5,  6,
   7,  8,  9, 10, 11, 12, 13, 14,
  15, 16, 17, 18, 19, 20, 21, 22,
  23, 24, 25, 39, 46, 39, 39, 39,
  39,  0,  1,  2,  3,  4,  5,  6,
   7,  8,  9, 10, 11, 12, 13, 14,
  15, 16, 17, 18, 19, 20, 21, 22,
  23, 24, 25, 39, 39, 39, 39
};
