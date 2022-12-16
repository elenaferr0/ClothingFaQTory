#include "size.h"

using Models::Size;

Size::Size(long id,
           string name,
           double extraPercentageOfMaterial)
        : Model(id),
          name(nameFromString(name)),
          extraPercentageOfMaterial(extraPercentageOfMaterial) {}

const double& Size::getExtraPercentageOfMaterial() const {
    return extraPercentageOfMaterial;
}

const Size::Name& Size::getName() const {
    return name;
}

Size* Size::clone() const {
    return new Size(*this);
}

string Size::getNameAsString() const {
    switch (name) {
        case XS:
            return "XS";
        case S:
            return "S";
        case M:
            return "M";
        case L:
            return "L";
        case XL:
            return "XL";
        case XXL:
            return "XXL";
        case ONE_SIZE:
        default:
            return "ONE SIZE";
    }
}

Size::Name Size::nameFromString(const string& name) {
    if (name == "XS") {
        return XS;
    } else if (name == "S") {
        return S;
    } else if (name == "M") {
        return M;
    } else if (name == "L") {
        return L;
    } else if (name == "XL") {
        return XL;
    } else if (name == "XXL") {
        return XXL;
    } else {
        return ONE_SIZE;
    }
}
