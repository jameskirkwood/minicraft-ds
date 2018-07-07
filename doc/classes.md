[TOC]

# sound

## Sound ✅

This class exactly matches the interface of the corresponding class in the original Minicraft. Some instances are exposed as static member variables. Calling the method `play()` on any of these will cause the associated sound to play without blocking.

### Static Members

- `playerHurt`
- `playerDeath`
- `monsterHurt`
- `test`
- `pickup`
- `bossdeath`
- `craft`

# gfx (graphics)

## Display

### Description

The global **Display** object, `DISPLAY`, represents the graphics engine which will render MinicraftDS' graphics. The `DISPLAY` has three tile based layers, one bitmap layer and a sprite layer, all of which can be reordered. All graphics use the same 216-colour fixed general-purpose palette. All three tile based layers share a set of hardware tiles. Hardware tiles can be added to the set and removed when no longer needed by the tile based layers. Hardware tiles are added to the set by their index in the sprite sheet. Each sprite sheet tile uses a four-colour palette, which is applied to it in order to produce a hardware tile. The four-colour palette is a 4-tuple of 8-bit indices into the global palette. The colour tuple can generated using the `colours` utility function.

### Public Interface

- Display::`Display()` (no equivalent)
  configures the VRAM and graphics engines to support drawing operations
- TileId Display::`allocTile(int resIndex, u32 palette)` (no equivalent)
  generates a hardware tile for rendering the tile at sprite sheet index `resIndex` with indirect colour palette `palette`
  returns the ID of the generated hardware tile
- void Display::`freeTile(TileId tileId)` (no equivalent)
  removes a hardware tile from the store by its ID
- static u32 Display::`colours(int a, int b, int c, int d)` (Color.get(int a, int b, int c, int d))
  packs four 3-digit decimal 6-level-per-channel colour values into a palette of four 8-bit colour indices
- static u32 Display::`colour(int d)` (Color.get(int d))
  maps 3-digit decimal 6-level-per-channel colour values into 8-bit colour indices into the 216-colour fixed general-purpose palette
- TileLayer Display::`sky_layer` (no equivalent)
  used for the parallax background in the sky level, as well as half-tile offset text rendering in menus
- TileLayer Display::`world_layer` (no equivalent)
  used for the level terrain
- TileLayer Display::`gui_layer` (no equivalent)
  used for menus
- BitmapLayer Display::`light_layer` (no equivalent)
  used for the lighting overlay in underground levels

### VRAM Usage

| Region                                   | Size                   | Purpose            |
| ---------------------------------------- | ---------------------- | ------------------ |
| Map Bases 28 and 29                      | 4K (64x32 16b entries) | World Layer Map    |
| Map Base 30                              | 2K (32x32 16b entries) | Sky Layer Map      |
| Map Base 31                              | 2K (32x32 16b entries) | GUI Layer Map      |
| Tile/BMP Bases 0 to 2 and first half of 3 | 56K (896 8bpp tiles)   | Global Tile Store  |
| Tile/BMP Bases 4 to 7                    | 64K (256x256 px 8bpp)  | Light Layer Bitmap |

### The Tile Store

A LIFO linked list is stored in the unoccupied entries in tile memory. Initially the tile memory is filled with numbers 1…896, and the top of the free stack is entry 0. Each insertion, the top is moved to the entry pointed to by the free cell, except when the top is entry 896 (past the end) in which case a null tile is returned. When an entry is deleted, the top moves to that entry, and its previous position is stored in place of the removed tile.

# screen (menus)

## Menu ✅

The abstract base class for `*Menu` classes. These function as controllers in the MVC model. All 'menus' have a `tick()` method (time base) and a `render()` method (draws to the global display object). Menus often need to allocate resources and configure state before drawing, so `show()` and `hide()` must be called to set up and clean up any such resources and state.

## TitleMenu ✅
