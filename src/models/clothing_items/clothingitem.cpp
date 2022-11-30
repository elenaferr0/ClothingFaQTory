#include "clothingitem.h"
#include<string>

using std::string;

using Models::ClothingItem;

const double ClothingItem::SMALLEST_SIZE_TRUNK_WIDTH = 10;
const double ClothingItem::SMALLEST_SIZE_TRUNK_LENGTH = 10;

const double ClothingItem::SMALLEST_SIZE_LEG_WIDTH = 10;
const double ClothingItem::SMALLEST_SIZE_LEG_LENGTH= 10;

ClothingItem::ClothingItem(string color, list<Material> materials, Size size, int availableQuantity, int soldQuantity, bool sustainableMaterials)
  : Product(color, materials, size, availableQuantity, soldQuantity), sustainableMaterials(sustainableMaterials){};

/*
 * compute length and compute width calculate the length of the current
 * clothing item, based on the extra percentage of material required
 * to produce an item of the given size (compared to the smallest
 * size length).
 */

double ClothingItem::computeLegLength() const {
  return SMALLEST_SIZE_LEG_LENGTH * (100 + size.getExtraPercentageOfMaterial()) / 100;
}

double ClothingItem::computeLegWidth() const {
  return SMALLEST_SIZE_LEG_WIDTH * (100 + size.getExtraPercentageOfMaterial()) / 100;
}

double ClothingItem::computeTrunkLength() const {
  return SMALLEST_SIZE_TRUNK_LENGTH * (100 + size.getExtraPercentageOfMaterial()) / 100;
}

double ClothingItem::computeTrunkWidth() const {
  return SMALLEST_SIZE_TRUNK_WIDTH * (100 + size.getExtraPercentageOfMaterial()) / 100;
}
