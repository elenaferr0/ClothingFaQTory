#ifndef MATERIAL_H
#define MATERIAL_H
#include "core/model.h"

using Core::Model;

namespace Models {
  class Material : public Model
  {
      enum Name{ DENIM, WOOL, POLYESTER, COTTON, GOLD, SILVER };
      enum UnitOfMeasure { GRAM, CENTIMETER };

      Name name;
      UnitOfMeasure unitOfMeasure;
      double costPerUnit;

    public:
      Material(Material::Name name, UnitOfMeasure unitOfMeasure, double costPerUnit);
  };
}

#endif // MATERIAL_H
