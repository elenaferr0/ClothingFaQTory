#include "size.h"

using Models::Size;

Size::Size(unsigned long id,
           Size::Value name,
           double extraPercentageOfMaterial)
        : Model(id),
          name(name),
          extraPercentageOfMaterial(extraPercentageOfMaterial) {}

double Size::getExtraPercentageOfMaterial() const {
    return extraPercentageOfMaterial;
}

double Size::getName() const {
    return name;
}

Size* Size::clone() const {
    return new Size(*this);
}
