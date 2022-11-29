#include "overalls.h"

using Models::ClothingItems::Overalls;

Overalls* Overalls::clone() const {
  return new Overalls(*this);
}
