#include "jeans.h"

using Models::ClothingItems::Jeans;


Jeans* Jeans::clone() const {
  return new Jeans(*this);
}
