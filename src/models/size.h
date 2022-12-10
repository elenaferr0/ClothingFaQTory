#ifndef SIZE_H
#define SIZE_H

#include "../core/model.h"

using Core::Model;

namespace Models {
    class Size : public Model {
    public:
        enum Name { // contains the corresponding ids in the db
            XS = 1, S = 2, M = 3, L = 4, XL = 5, XXL = 6, ONE_SIZE = 7
        };

        double getExtraPercentageOfMaterial() const;

        Name getName() const;

        Size(long id = -1,
             string name = "",
             double extraPercentageOfMaterial = 0);

        string getTableName() const override;

        void setName(string name);

        void setExtraPercentageOfMaterial(double extraPercentageOfMaterial);

        string getNameAsString() const;
        static Name nameFromString(const string&);

    private:
        Name name;
        double extraPercentageOfMaterial;

        Size* clone() const override;
    };
}

#endif // SIZE_H
