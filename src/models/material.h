#ifndef MATERIAL_H
#define MATERIAL_H

#include "../core/model.h"

using Core::Model;

namespace Models {
    class Material : public Model {
    public:
        enum Name { // contains database ids corresponding to this materials
            DENIM, WOOL, POLYESTER, COTTON, GOLD, SILVER, WOOD
        };

        enum UnitOfMeasure {
            GRAM, CENTIMETER
        };

        static const double GOLD_SPECIFIC_WEIGHT;
        static const double SILVER_SPECIFIC_WEIGHT;
        static const double WOOD_SPECIFIC_WEIGHT;

        Material(long id = -1,
                 string name = "",
                 string unitOfMeasure = "",
                 double costPerUnit = 0);

        Material* clone() const override;

        Name getName() const;

        void setName(string name);

        UnitOfMeasure getUnitOfMeasure() const;

        void setUnitOfMeasure(string unitOfMeasure);

        double getCostPerUnit() const;

        void setCostPerUnit(double costPerUnit);

        string getTableName() const override;

        string getNameAsString() const;

        static Name namefromString(const string&);

        string getUnitOfMeasureAsString() const;

        static UnitOfMeasure unitOfMeasureFromString(const string&);

    private:
        Name name;
        UnitOfMeasure unitOfMeasure;
        double costPerUnit;
    };
}

#endif // MATERIAL_H
