#include "tshirt.h"

using Models::ClothingItems::TShirt;

TShirt* TShirt::clone() const {
  return new TShirt(*this);
}
