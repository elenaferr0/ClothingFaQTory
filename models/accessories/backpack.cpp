#include "backpack.h"

using Models::Accessories::BackPack;

const double BackPack::BACKPACK_HEIGHT = 30;
const double BackPack::BACKPACK_WIDTH = 20;

BackPack::BackPack(string color, list<Material> materials, double capacity)
  : Accessory(color, materials), capacity(capacity){};
