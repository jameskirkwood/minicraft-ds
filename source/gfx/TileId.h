#ifndef GFX_TILEID_H
#define GFX_TILEID_H

namespace gfx {

// TileId is part of the Display interface and represents a tile in BG VRAM.
// The ID 0 will never be assigned, so can be used as a null value.
typedef u16 TileId;

}

#endif
