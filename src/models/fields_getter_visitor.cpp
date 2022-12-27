

#include "fields_getter_visitor.h"

void FieldsGetterVisitor::visitBracelet(Bracelet& bracelet) {
    visitAccessory(bracelet);
    fields.pushBack("pearl_number");
    params << bracelet.getPearlNumber();
    fields.pushBack("pearl_diameter");
    params << bracelet.getPearlDiameter();
}

void FieldsGetterVisitor::visitBackPack(BackPack& backPack) {
    visitAccessory(backPack);
    fields.pushBack("capacity");
    params << backPack.getCapacity();
}

void FieldsGetterVisitor::visitHat(Hat& hat) {
    visitAccessory(hat);
    fields.pushBack("is_baseball_cap");
    params << hat.isBaseballCap();
}

void FieldsGetterVisitor::visitJeans(Jeans& jeans) {
    visitClothingItem(jeans);
    jeansFields(jeans);
}

void FieldsGetterVisitor::visitVest(Vest& vest) {
    visitClothingItem(vest);
    vestFields(vest);
}

void FieldsGetterVisitor::visitOveralls(Overalls& overalls) {
    visitClothingItem(overalls);
    vestFields(overalls);
    jeansFields(overalls);
}

const LinkedList<string>& FieldsGetterVisitor::getFields() const {
    return fields;
}

const QVariantList& FieldsGetterVisitor::getParams() const {
    return params;
}

void FieldsGetterVisitor::visitAccessory(const Accessory& accessory) {
    visitProduct(accessory);
    fields.pushBack("category");
    params << QString::fromStdString(Accessory::getCategoryAsString(accessory.getCategory()));
}

void FieldsGetterVisitor::visitClothingItem(const ClothingItem& clothingItem) {
    visitProduct(clothingItem);
    fields.pushBack("sustainable_materials");
    params << clothingItem.hasSustainableMaterials();

    fields.pushBack("gender");
    params << QString::fromStdString(ClothingItem::getGenderAsString(clothingItem.getGender()));
}

void FieldsGetterVisitor::visitProduct(const Product& product) {
    fields = {"code",
              "color",
              "sold_quantity",
              "available_quantity",
              "description",
              "size_id",
              "material_id"};

    params << QString::fromStdString(product.getCode())
           << QString::fromStdString(product.getColor())
           << product.getSoldQuantity()
           << product.getAvailableQuantity()
           << QString::fromStdString(product.getDescription())
           << product.getSize().getId()
           << product.getMaterial().getId();
}

void FieldsGetterVisitor::vestFields(const Vest& vest) {
    fields.pushBack("has_buttons");
    params << vest.getHasButtons();
}

void FieldsGetterVisitor::jeansFields(const Jeans& jeans) {
    fields.pushBack("shorts");
    params << jeans.areShorts();
}
