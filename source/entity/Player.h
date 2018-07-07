#ifndef PLAYER_H
#define PLAYER_H

class Player {

public:

  int health;
  int stamina;
  int staminaRechargeDelay;
  int x, y;

  Player() : health(10), stamina(10), staminaRechargeDelay(0), x(0), y(0) {}
};

#endif
