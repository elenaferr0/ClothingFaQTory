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

        Size(long id = -1,
             string name = "",
             double extraPercentageOfMaterial = 0);

        string getNameAsString() const;

        static Name nameFromString(const string&);

        void accept(Core::VisitorInterface& visitor) override;

    private:
        Name name;
        double extraPercentageOfMaterial;

        Size* clone() const override;
    };
}

#endif // SIZE_H
