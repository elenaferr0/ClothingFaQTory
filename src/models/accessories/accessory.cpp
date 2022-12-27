#include "accessory.h"
#include<string>

using Models::Accessory;
using Models::Product;
using std::string;

Accessory::Accessory(
        int id,
        const string& code,
        const string& color,
        const Material& material,
        const Size& size,
        int availableQuantity,
        int soldQuantity,
        const string& description,
        const string& category)
        : Product(id,
                  code,
                  color,
                  material,
                  size,
                  availableQuantity,
                  soldQuantity,
                  description),
          category(categoryFromString(category)) {}

string Accessory::getCategoryAsString(Category category) {
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

const Accessory::Category& Accessory::getCategory() const {
    return category;
}

void Accessory::setCategory(const string& category) {
    this->category = categoryFromString(category);
}
