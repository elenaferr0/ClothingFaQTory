#ifndef MATERIAL_H
#define MATERIAL_H

#include "model.h"
#include "../core/visitor_interface.h"

using Models::Model;
using Core::VisitorInterface;

namespace Models {
    class Material : public Model {
        public:
            enum Name { // contains database ids corresponding to this cachedMaterials
                DENIM = 1,
                WOOL = 2,
                POLYESTER = 3,
                COTTON = 4,
                GOLD = 5,
                SILVER = 6,
                WOOD = 7
            };

            enum UnitOfMeasure {
                GRAM, METER
            };

            static const double GOLD_SPECIFIC_WEIGHT;
            static const double SILVER_SPECIFIC_WEIGHT;
            static const double WOOD_SPECIFIC_WEIGHT;

            Material(long id = -1,
                     string name = "",
                     string unitOfMeasure = "",
                     double costPerUnit = 0);

            Material* clone() const override;

            const Name& getName() const;

            string getNameAsString() const;

            const double& getCostPerUnit() const;

            static Name namefromString(const string&);

            static UnitOfMeasure unitOfMeasureFromString(const string&);

            string getUnitOfMeasureAsString() const;

            void setCostPerUnit(double costPerUnit);

        private:
            Name name;
            UnitOfMeasure unitOfMeasure;
            double costPerUnit;

    };
}

#endif // MATERIAL_H
