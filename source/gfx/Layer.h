#ifndef GFX_LAYER_H
#define GFX_LAYER_H

#include <nds.h>

namespace gfx {

//-----------------------------------------------------------------------------
class Layer {
//-----------------------------------------------------------------------------

protected:

  int bgId;

public:

  void hide() {
    bgHide(bgId);
  }

  void show() {
    bgShow(bgId);
  }

  void setScroll(int x, int y) {
    bgSetScroll(bgId, x, y);
  }

  void setPriority(unsigned int priority) {
    bgSetPriority(bgId, priority);
  }
};

}

#endif
