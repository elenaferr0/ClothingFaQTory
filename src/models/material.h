#ifndef MATERIAL_H
#define MATERIAL_H
#include "src/core/model.h"

using Core::Model;

namespace Models {
  class Material : public Model
  {
    public:
      enum Name{ DENIM, WOOL, POLYESTER, COTTON, GOLD, SILVER, WOOD };
      enum UnitOfMeasure { GRAM, CENTIMETER };

      static const double GOLD_SPECIFIC_WEIGHT;
      static const double SILVER_SPECIFIC_WEIGHT;
      static const double WOOD_SPECIFIC_WEIGHT;

      Material(Material::Name name = COTTON,
	       UnitOfMeasure unitOfMeasure = CENTIMETER,
	       double costPerUnit = 0);

      Material* clone() const override;
      Name getName() const;
      double getCostPerUnit() const;

    private:
      Name name;
      UnitOfMeasure unitOfMeasure;
      double costPerUnit;

  };
}

#endif // MATERIAL_H
