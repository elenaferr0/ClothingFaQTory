#include "size.h"

using Models::Size;

double Size::getExtraPercentageOfMaterial() const {
  return extraPercentageOfMaterial;
}

double Size::getValue() const {
  return value;
}

Size* Size::clone() const {
  return new Size(*this);
}
