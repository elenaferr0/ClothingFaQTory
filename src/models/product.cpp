#include <string>
#include "product.h"
#include "material.h"

using std::string;
using Models::Product;
using Models::Material;

Product::Product(long id,
                 string code,
                 string color,
                 list <Material> materials,
                 Size size,
                 int availableQuantity,
                 int soldQuantity,
                 string description)
        : Model(id),
          color(color),
          materials(materials),
          size(size),
          availableQuantity(availableQuantity),
          soldQuantity(soldQuantity),
          description(description),
          code(code) {};

string Product::getTableName() const {
    return "product";
}

const string& Product::getColor() const {
    return color;
}

const list <Material>& Product::getMaterials() const {
    return materials;
}

const Models::Size& Product::getSize() const {
    return size;
}

int Product::getAvailableQuantity() const {
    return availableQuantity;
}

int Product::getSoldQuantity() const {
    return soldQuantity;
}

const string& Product::getDescription() const {
    return description;
}

const string& Product::getCode() const {
    return code;
}

void Product::setColor(const string& color) {
    Product::color = color;
}

void Product::setMaterials(const list <Material>& materials) {
    Product::materials = materials;
}

void Product::setSize(const Models::Size& size) {
    Product::size = size;
}

void Product::setAvailableQuantity(int availableQuantity) {
    Product::availableQuantity = availableQuantity;
}

void Product::setSoldQuantity(int soldQuantity) {
    Product::soldQuantity = soldQuantity;
}

void Product::setDescription(const string& description) {
    Product::description = description;
}

void Product::setCode(const string& code) {
    Product::code = code;
}
