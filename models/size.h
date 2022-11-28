#ifndef SIZE_H
#define SIZE_H

namespace Models {
  class Size
  {
    public:
      enum Value {XS, S, M, L, XL, ONE_SIZE};
      double getExtraPercentageOfMaterial();
      double getValue();
      Size(Value sizeName, double extraPercentageOfMaterial = 0)
	: value(sizeName), extraPercentageOfMaterial(extraPercentageOfMaterial){};

    private:
      Value value;
      double extraPercentageOfMaterial;
  };
}

#endif // SIZE_H
