#ifndef SIZE_H
#define SIZE_H

#include "model.h"

using Models::Model;

namespace Models {
    class Size : public Model {
        public:
            enum Name { // contains the corresponding ids in the db
                XS = 1, S = 2, M = 3, L = 4, XL = 5, XXL = 6, ONE_SIZE = 7
            };

            const double& getExtraPercentageOfMaterial() const;

            const Name& getName() const;

            Size(int id = -1,
                 const string& name = "",
                 double extraPercentageOfMaterial = 0);

            string getNameAsString() const;

            static Name nameFromString(const string&);

        private:
            Name name;
            double extraPercentageOfMaterial;

            Size* clone() const override;
    };
}

#endif // SIZE_H
