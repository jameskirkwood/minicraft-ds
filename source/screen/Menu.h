#ifndef SCREEN_MENU_H
#define SCREEN_MENU_H

#include <memory>

class Game; // forward-declare callback class to avoid a dependency cycle :(

// confusingly named 'view-controller-state' base class
//-----------------------------------------------------------------------------
struct Menu : public std::enable_shared_from_this<Menu> {
//-----------------------------------------------------------------------------

// callback interface (set before calling any methods)
//-----------------------------------------------------------------------------
  Game *game;
//-----------------------------------------------------------------------------

  virtual ~Menu() {};

// time base (call once per frame)
//-----------------------------------------------------------------------------
  virtual void tick() {};
//-----------------------------------------------------------------------------

// draw to global display (call once per frame)
//-----------------------------------------------------------------------------
  virtual void render() = 0;
//-----------------------------------------------------------------------------

// acquire/release resources required for rendering
//-----------------------------------------------------------------------------
  virtual void show() {};
  virtual void hide() {};
//-----------------------------------------------------------------------------

  // static void renderItemList(
  //   int x0, int y0, int x1, int y1,
  //   std::vector<ListItem *> listItems,
  //   int selected);
};

#endif
