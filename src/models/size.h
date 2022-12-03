#ifndef SIZE_H
#define SIZE_H

#include "src/core/model.h"

using Core::Model;

namespace Models {
    class Size : public Model {
    public:
        enum Value {
            XS, S, M, L, XL, ONE_SIZE
        };

        double getExtraPercentageOfMaterial() const;

        double getName() const;

        Size(unsigned long id = 0,
             Value name = Value::ONE_SIZE,
             double extraPercentageOfMaterial = 0);

    private:
        Value name;
        double extraPercentageOfMaterial;

        Size* clone() const override;
    };
}

#endif // SIZE_H
