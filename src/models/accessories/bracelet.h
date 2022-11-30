#ifndef BRACELET_H
#define BRACELET_H
#include "src/models/accessories/accessory.h"

namespace Models::Accessories {
  class Bracelet : public Accessory
  {
    protected:
      unsigned int pearlNumber;
      double pearlDiameter;

    public:
      Bracelet(string color, list<Material> materials, unsigned int pearlNumber, double pearlDiameter = .75);
      Bracelet* clone() const override;
      double computePrice() const override;
  };
}

#endif // BRACELET_H
