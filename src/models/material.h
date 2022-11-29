#ifndef MATERIAL_H
#define MATERIAL_H
#include "src/core/model.h"

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
      static const double GOLD_SPECIFIC_WEIGHT;
      static const double SILVER_SPECIFIC_WEIGHT;
      static const double WOOD_SPECIFIC_WEIGHT;

      Material(Material::Name name, UnitOfMeasure unitOfMeasure, double costPerUnit);
      Material* clone() const override;
  };
}

#endif // MATERIAL_H
