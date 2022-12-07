#include "size.h"

using Models::Size;

Size::Size(long id,
	   string name,
           double extraPercentageOfMaterial)
        : Model(id),
          name(name),
          extraPercentageOfMaterial(extraPercentageOfMaterial) {}

double Size::getExtraPercentageOfMaterial() const {
    return extraPercentageOfMaterial;
}

string Size::getName() const {
    return name;
}

Size* Size::clone() const {
    return new Size(*this);
}

string Size::getTableName() const {
    return "size";
}

void Size::setName(string name){
  this->name = name;
}

void Size::setExtraPercentageOfMaterial(double extraPercentageOfMaterial){
  this->extraPercentageOfMaterial = extraPercentageOfMaterial;
}
