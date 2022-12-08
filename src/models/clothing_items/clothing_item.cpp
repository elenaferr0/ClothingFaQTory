#include "clothing_item.h"
#include<string>

using std::string;

using Models::ClothingItem;

const double ClothingItem::SMALLEST_SIZE_TRUNK_WIDTH = 10;
const double ClothingItem::SMALLEST_SIZE_TRUNK_LENGTH = 10;

const double ClothingItem::SMALLEST_SIZE_LEG_WIDTH = 10;
const double ClothingItem::SMALLEST_SIZE_LEG_LENGTH = 10;

ClothingItem::ClothingItem(
        long id,
        string code,
        string color,
        list <Material> materials,
        Size size,
        int availableQuantity,
        int soldQuantity,
        string description,
        bool sustainableMaterials,
        Gender gender)
        : Product(id,
                  code,
                  color,
                  materials,
                  size,
                  availableQuantity,
                  soldQuantity,
                  description),
          sustainableMaterials(sustainableMaterials),
          gender(gender) {};

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

string ClothingItem::getTableName() const {
    return "clothing_item";
}