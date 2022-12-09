#include "accessory.h"
#include<string>

using Models::Accessory;
using Models::Product;
using std::string;

Accessory::Accessory(
        long id,
        string code,
        string color,
        list<Material> materials,
        Size size,
        int availableQuantity,
        int soldQuantity,
        string description,
        string category)
        : Product(id,
                  code,
                  color,
                  materials,
                  size,
                  availableQuantity,
                  soldQuantity,
                  description),
          category(categoryFromString(category)) {}

string Accessory::getTableName() const {
    return "accessory";
}

string Accessory::getCategoryAsString() const {
    switch (category) {
        case BAGS:
            return "BAGS";
        case JEWELRY:
            return "JEWELRY";
        case HATS:
            return "HATS";
        case GENERAL:
        default:
            return "GENERAL";
    }
}

Accessory::Category Accessory::categoryFromString(const string& category) {
    if (category == "BAGS") {
        return BAGS;
    } else if (category == "JEWELRY") {
        return JEWELRY;
    } else if (category == "HATS") {
        return HATS;
    } else {
        return GENERAL;
    }
}

Accessory::Category Accessory::getCategory() const {
    return category;
}

void Accessory::setCategory(const string& category) {
    this->category = categoryFromString(category);
}
