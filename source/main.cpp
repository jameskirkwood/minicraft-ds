#include <nds.h>
#include <iostream>

#include "Game.h"
#include "InputHandler.h"

#include "gfx/Display.h"

//-----------------------------------------------------------------------------
Game game;
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
int main() {
//-----------------------------------------------------------------------------
  defaultExceptionHandler();
  consoleDemoInit();
  game.init();
  while (true) {
    swiWaitForVBlank();

    cpuStartTiming(0);

    game.render();
    gfx::display.commit();
    input.tick();
    game.tick();

    std::cout << cpuEndTiming() * 60 / float(BUS_CLOCK) << std::endl;
  }
}
