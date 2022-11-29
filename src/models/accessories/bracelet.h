#ifndef BRACELET_H
#define BRACELET_H
#include "src/models/accessories/accessory.h"

namespace Models::Accessories {
  class Bracelet : public Accessory
  {
    protected:
      unsigned int pearlNumber;
      double pearlDiameter;

      // assumption: the material of the bracelet is either of GOLD, SILVER or WOOD

    public:
      Bracelet(string color, list<Material> materials, unsigned int pearlNumber, double pearlDiameter);
      Bracelet* clone() const override;
      double computePrice() const override;
  };
}

#endif // BRACELET_H
