#ifndef SIZE_H
#define SIZE_H
#include "src/core/model.h"

using Core::Model;

namespace Models {
  class Size: public Model
  {
    public:
      enum Value {XS, S, M, L, XL, ONE_SIZE};
      double getExtraPercentageOfMaterial() const;
      double getValue() const;
      Size(Value sizeName, double extraPercentageOfMaterial = 0)
	: value(sizeName), extraPercentageOfMaterial(extraPercentageOfMaterial){};
      Size(){};

    private:
      Value value;
      double extraPercentageOfMaterial;
      Size* clone() const override;
  };
}

#endif // SIZE_H
