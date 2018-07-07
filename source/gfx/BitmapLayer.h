#ifndef GFX_BITMAPLAYER_H
#define GFX_BITMAPLAYER_H

#include <nds.h>

#include "Layer.h"

namespace gfx {

//-----------------------------------------------------------------------------
struct BitmapLayer : public Layer {
//-----------------------------------------------------------------------------

  BitmapLayer(int bgIndex, int bmpBase) {
    bgId = bgInit(bgIndex, BgType_Bmp8, BgSize_B8_256x256, bmpBase, 0);
  }

  void drawTwoPixels(u8 colour0, u8 colour1, int x, int y) {
    bgGetGfxPtr(bgId)[(y << 7) + (x >> 1)] = colour0 | (colour1 << 8);
  }
};

}

#endif
