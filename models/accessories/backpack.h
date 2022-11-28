#ifndef BACKPACK_H
#define BACKPACK_H
#include <string>
#include "models/accessories/accessory.h"

using std::string;

namespace Models::Accessories {
  class BackPack : public Accessory
  {
    protected:
      /*
       * static constants used to estimate the backpack size
       * for price calculation
       * assumption: all backpacks have same height and depth,
       * only capacity and width changes
       */
      static const double BACKPACK_HEIGHT; // in cm
      static const double BACKPACK_WIDTH;  // in cm

      double capacity; // in iters
    public:
      BackPack(string color, list<Material> materials, double capacity);
  };
}

#endif // BACKPACK_H
