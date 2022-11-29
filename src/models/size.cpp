#include "size.h"

using Models::Size;

double Size::getExtraPercentageOfMaterial() {
  return extraPercentageOfMaterial;
}

double Size::getValue() {
  return value;
}

Size* Size::clone() const {
  return new Size(*this);
}
