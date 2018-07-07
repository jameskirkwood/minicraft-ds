#ifndef UTIL_RANDOM_H
#define UTIL_RANDOM_H

#include <random>
#include <custard/types.hpp>

namespace util {

// java.util.Random
//-----------------------------------------------------------------------------
class Random {
//-----------------------------------------------------------------------------

  std::minstd_rand generator;

public:

// random 20.12 fixed point value in range [0, 1], for efficiency
//-----------------------------------------------------------------------------
  custard::q12 nextFloat() {
//-----------------------------------------------------------------------------
    return std::uniform_real_distribution<float>()(generator);
  }

//-----------------------------------------------------------------------------
  int nextInt(int range) {
//-----------------------------------------------------------------------------
    return std::uniform_int_distribution<int>(0, range - 1)(generator);
  }
};

}

#endif
