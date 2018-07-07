#include <_ansi.h> // sassert
#include <custard/vram.hpp>

#include "Display.h"
#include "assets/icons.h"

using namespace gfx;

//-----------------------------------------------------------------------------
Display gfx::display;
//-----------------------------------------------------------------------------

// Notch's 216-colour general purpose palette
//-----------------------------------------------------------------------------
static void generatePalette(u16 *base) {
//-----------------------------------------------------------------------------

  *(base++) = 0; // black backdrop

  for (int r = 0; r < 6; r++) {
    for (int g = 0; g < 6; g++) {
      for (int b = 0; b < 6; b++) {

        int rr = (r * 255 / 5);
        int gg = (g * 255 / 5);
        int bb = (b * 255 / 5);
        int mid = (rr * 30 + gg * 59 + bb * 11) / 100;
        int r1 = ((rr + mid * 1) / 2) * 230 / 255 + 10;
        int g1 = ((gg + mid * 1) / 2) * 230 / 255 + 10;
        int b1 = ((bb + mid * 1) / 2) * 230 / 255 + 10;

        // convert 24 bit RGB to 15 bit colour for display
        *(base++) = RGB15(r1 >> 3, g1 >> 3, b1 >> 3);
      }
    }
  }
}

//-----------------------------------------------------------------------------
Display::Display() {
//-----------------------------------------------------------------------------

  // initialise graphics hardware
  config.graphics_TTTE(); // three text and one extended background
  config.set_main();
  custard::vram::main::bg::A_128(); // 128 kB at base of main background memory
  lcdMainOnTop();
  powerOn(POWER_ALL_2D);

  // initialise base palette
  generatePalette(BG_PALETTE);

  // initialise tile free list
  for (u16 i = 0; i < freelist_size; i++) BG_TILE_RAM(tbase)[i << 5] = i + 1;
  freelist_head = 0;

  // allocate automatic tiles
  clear = allocTile(0, colours(-1, -1, -1, -1));
  black = allocTile(0, colours( 0,  0,  0,  0));
}

//-----------------------------------------------------------------------------
TileId Display::allocTile(int resIndex, u32 palette) {
//-----------------------------------------------------------------------------

  sassert(freelist_head != freelist_size, "Tile Store Overflowed");
  if (freelist_head == freelist_size) return 0; // return null tile on overflow

  // 2bpp 8x8 tile in sprite sheet
  const u16 *source = &iconsTiles[resIndex * 8];

  // 8bpp 8x8 tile in VRAM and its index
  u16 *tile_entry = &(BG_TILE_RAM(tbase)[freelist_head << 5]);
  int tile_index = freelist_head;

  // pop the tile from the free list
  freelist_head = *tile_entry;

  // render tile from sprite sheet to VRAM
  // TODO: see if BIOS BitUnPack is faster
  for (int y = 0; y < 8; y++) {
    u16 row = *(source++);
    for (int x = 0; x < 4; x++) {
      tile_entry[y * 4 + x]  = (palette >> (       (row & 3) * 8)) & 255;
      tile_entry[y * 4 + x] |= (palette >> (((row >> 2) & 3) * 8)) << 8;
      row >>= 4;
    }
  }

  return tile_index + 1;
}

//-----------------------------------------------------------------------------
void Display::freeTile(TileId id) {
//-----------------------------------------------------------------------------

  if (id == 0) return; // null tile cannot be freed
  BG_TILE_RAM(tbase)[(id - 1) << 5] = freelist_head; // link to head
  freelist_head = id - 1; // make new head
}
