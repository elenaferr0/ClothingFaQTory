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

void Product::setSize(const Models::Size& size) {
    Product::size = size;
}

const Material& Product::getMaterial() const {
    return material;
}

void Models::Product::setMaterial(const Material& material) {
    this->material = material;
}

void Models::Product::registerObserver(IProductObserver* observer) {
    observers.push_back(observer);
}

void Models::Product::notifyAll() {
    for (auto it = observers.begin(); it != observers.end(); it++) {
        (*it)->notify(*this);
    }
}
