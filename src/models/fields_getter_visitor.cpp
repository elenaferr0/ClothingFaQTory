

#include "fields_getter_visitor.h"

using Models::FieldsGetterVisitor;

void FieldsGetterVisitor::visitBracelet(Bracelet& bracelet) {
    visitAccessory(bracelet);
    fields.put("pearl_number", bracelet.getPearlNumber());
    fields.put("pearl_diameter", bracelet.getPearlDiameter());
}

void FieldsGetterVisitor::visitBackPack(BackPack& backPack) {
    visitAccessory(backPack);
    fields.put("capacity", backPack.getCapacity());
}

void FieldsGetterVisitor::visitHat(Hat& hat) {
    visitAccessory(hat);
    fields.put("is_baseball_cap", hat.isBaseballCap());
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

void FieldsGetterVisitor::visitAccessory(const Accessory& accessory) {
    visitProduct(accessory);
    fields.put("category", QString::fromStdString(Accessory::getCategoryAsString(accessory.getCategory())));
}

void FieldsGetterVisitor::visitClothingItem(const ClothingItem& clothingItem) {
    visitProduct(clothingItem);
    fields.put("sustainable_materials", clothingItem.hasSustainableMaterials());
    fields.put("gender", QString::fromStdString(ClothingItem::getGenderAsString(clothingItem.getGender())));
}

void FieldsGetterVisitor::visitProduct(const Product& product) {
    fields.put("code", QString::fromStdString(product.getCode()));
    fields.put("color", QString::fromStdString(product.getColor()));
    fields.put("sold_quantity", product.getSoldQuantity());
    fields.put("available_quantity", product.getAvailableQuantity());
    fields.put("description", QString::fromStdString(product.getDescription()));
    if (useNameForForeignKeys) {
        fields.put("size", QString::fromStdString(product.getSize().getNameAsString()));
        fields.put("material", QString::fromStdString(product.getMaterial().getNameAsString()));
    } else {
        fields.put("size_id", product.getSize().getId());
        fields.put("material_id", product.getMaterial().getId());
    }
}

void FieldsGetterVisitor::vestFields(const Vest& vest) {
    fields.put("has_buttons", vest.getHasButtons());
}

void FieldsGetterVisitor::jeansFields(const Jeans& jeans) {
    fields.put("shorts", jeans.areShorts());
}

void Models::FieldsGetterVisitor::visitMaterial(Material& material) {
    fields.put("name", QString::fromStdString(material.getNameAsString()));
    fields.put("cost_per_unit", material.getCostPerUnit());
    fields.put("unit_of_measure", QString::fromStdString(material.getUnitOfMeasureAsString()));
}

void Models::FieldsGetterVisitor::visitSize(Size& size) {
    fields.put("name", QString::fromStdString(size.getNameAsString()));
    fields.put("extra_percentage_of_material", size.getExtraPercentageOfMaterial());
}

const Map<string, QVariant>& Models::FieldsGetterVisitor::getFields() const {
    return fields;
}

Models::FieldsGetterVisitor::FieldsGetterVisitor(bool useNameForForeignKeys)
        : fields(Map<string, QVariant>()),
          useNameForForeignKeys(useNameForForeignKeys) {

}

void Models::FieldsGetterVisitor::clear() {
    fields.eraseAll();
}
