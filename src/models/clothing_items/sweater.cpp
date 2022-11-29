#include "sweater.h"

using Models::ClothingItems::Sweater;

Sweater* Sweater::clone() const {
  return new Sweater(*this);
}
