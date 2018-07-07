#ifndef GFX_DISPLAY_H
#define GFX_DISPLAY_H

#include <nds.h>
#include <custard/display.hpp>
#include <custard/types.hpp>

#include "TileLayer.h"
#include "BitmapLayer.h"
#include "TileId.h"

namespace gfx {

//-----------------------------------------------------------------------------
class Display {
//-----------------------------------------------------------------------------

// configuration
//-----------------------------------------------------------------------------
  static const int       tbase = 0; // tile base for shared tile free list
  static const int world_mbase = 28; // map base for terrain
  static const int   sky_mbase = 30; // map base for sky
  static const int   gui_mbase = 31; // map base for GUI
  static const int light_bbase = 4; // bmp base for darkness overlay
//-----------------------------------------------------------------------------
  static const u16 freelist_size = 896; // max size of shared tile free list
//-----------------------------------------------------------------------------

  u16 freelist_head; // head of shared tile free list

  custard::display::config config;

public:

  static const int TILES_WIDE = 32;
  static const int TILES_HIGH = 24;
  const int w = 8 * TILES_WIDE;
  const int h = 8 * TILES_HIGH;
  const custard::ivec2 shape = custard::ivec2(w, h);

// layers for drawing
//-----------------------------------------------------------------------------
  TileLayer     sky_layer = TileLayer(0,   sky_mbase, tbase, BgSize_T_256x256);
  TileLayer   world_layer = TileLayer(1, world_mbase, tbase, BgSize_T_512x256);
  TileLayer     gui_layer = TileLayer(2,   gui_mbase, tbase, BgSize_T_256x256);
  BitmapLayer light_layer = BitmapLayer(3, light_bbase);
//-----------------------------------------------------------------------------

  Display();

// update display control registers (call during vertical blanking)
//-----------------------------------------------------------------------------
  void commit() { bgUpdate(); }
//-----------------------------------------------------------------------------

// allocate a tile from the sprite sheet using a given palette
//-----------------------------------------------------------------------------
  TileId allocTile(int resIndex, u32 palette);
//-----------------------------------------------------------------------------

// free a previously allocated tile
//-----------------------------------------------------------------------------
  void freeTile(TileId tileId);
//-----------------------------------------------------------------------------

// automatic tile ids
//-----------------------------------------------------------------------------
  TileId clear;
  TileId black;
//-----------------------------------------------------------------------------
};

// global display instance
// avoids the overhead of storing many pointers to an architectural singleton
//-----------------------------------------------------------------------------
extern Display display;
//-----------------------------------------------------------------------------

// generate a colour from its three-digit (RGB) decimal-coded senary
//-----------------------------------------------------------------------------
inline u32 colour(int d) {
//-----------------------------------------------------------------------------
  if (d < 0) return 0;
  int r = d / 100 % 10;
  int g = d / 10 % 10;
  int b = d % 10;
  return 1 + r * 36 + g * 6 + b;
}

// generate a 4-colour palette from four decimal-coded senary colours
//-----------------------------------------------------------------------------
inline u32 colours(int a, int b, int c, int d) {
//-----------------------------------------------------------------------------
  return (colour(d) <<24) + (colour(c) <<16) + (colour(b) <<8) + colour(a);
}

}

#endif
