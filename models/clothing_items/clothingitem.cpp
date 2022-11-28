#include "clothingitem.h"
#include<string>

using std::string;

using Models::ClothingItem;

const double ClothingItem::SMALLEST_SIZE_TRUNK_WIDTH = 10;
const double ClothingItem::SMALLEST_SIZE_TRUNK_LENGTH = 10;

const double ClothingItem::SMALLEST_SIZE_LEG_WIDTH = 10;
const double ClothingItem::SMALLEST_SIZE_LEG_LENGTH= 10;


/*
 * computeLength and computeWidth calculate the length of the current
 * clothing item, based on the extra percentage of material required
 * to produce an item of the given size (compared to the smallest
 * size length).
 */

double ClothingItem::computeLength(bool isTopClothingItem, Size size) const {
  return (isTopClothingItem ? SMALLEST_SIZE_TRUNK_LENGTH : SMALLEST_SIZE_LEG_LENGTH)
      * (100 + size.getExtraPercentageOfMaterial()) / 100;
}

double ClothingItem::computeWidth(bool isTopClothingItem, Size size) const {
  return (isTopClothingItem ? SMALLEST_SIZE_TRUNK_WIDTH : SMALLEST_SIZE_LEG_WIDTH)
      * (100 + size.getExtraPercentageOfMaterial()) / 100;
}

ClothingItem::ClothingItem(string color, list<Material> materials, Size size,
			   bool isTopClothingItem)
  : Product(color, materials, size),
    length(computeWidth(isTopClothingItem, size)),
	   width(computeWidth(isTopClothingItem, size)){};
