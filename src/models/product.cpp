#include <string>
#include "product.h"
#include "material.h"

using std::string;
using Models::Product;
using Models::Material;

Product::Product(long id,
                 string code,
                 string color,
                 Material material,
                 Size size,
                 int availableQuantity,
                 int soldQuantity,
                 string description)
        : Model(id),
          color(color),
          material(material),
          size(size),
          availableQuantity(availableQuantity),
          soldQuantity(soldQuantity),
          description(description),
          code(code) {};

const string& Product::getColor() const {
    return color;
}

const Models::Size& Product::getSize() const {
    return size;
}

const int& Product::getAvailableQuantity() const {
    return availableQuantity;
}

const int& Product::getSoldQuantity() const {
    return soldQuantity;
}

const string& Product::getDescription() const {
    return description;
}

const string& Product::getCode() const {
    return code;
}

const Material& Product::getMaterial() const {
    return material;
}


string Product::productTypeToString(Product::ProductType productType) {
    switch (productType) {
        case Jeans:
            return "Jeans";
        case Overalls:
            return "Overalls";
        case Hat:
            return "Hat";
        case Bracelet:
            return "Bracelet";
        case Vest:
            return "Vest";
        case BackPack:
        default:
            return "BackPack";
    }
}

void Models::Product::setColor(const string& color) {
    Product::color = color;
}

void Models::Product::setMaterial(const Material& material) {
    Product::material = material;
}

void Models::Product::setSize(const Size& size) {
    Product::size = size;
}

void Models::Product::setAvailableQuantity(int availableQuantity) {
    Product::availableQuantity = availableQuantity;
}

void Models::Product::setSoldQuantity(int soldQuantity) {
    Product::soldQuantity = soldQuantity;
}

void Models::Product::setDescription(const string& description) {
    Product::description = description;
}

void Models::Product::setCode(const string& code) {
    Product::code = code;
}
