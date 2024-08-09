#ifndef RNG_H
#define RNG_H

#include <cstdlib>

class RNG {
public:
  static float random_float() {
    return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
  }

  static int random_int(int max) { return rand() % max; }
};

#endif // !RNG_H
