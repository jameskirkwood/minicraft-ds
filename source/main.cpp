#include <nds.h>
#include <iostream>
#include <iomanip>

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

    auto t = cpuEndTiming();

    consoleClear();
    std::cout << VERSION << std::endl;
    std::cout << std::setprecision(3) << t * 6000 / float(BUS_CLOCK);
    std::cout << "% CPU" << std::endl;
  }
}
