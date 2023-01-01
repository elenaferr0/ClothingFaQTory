

#include "fields_getter_visitor.h"

using Models::FieldsGetterVisitor;

void FieldsGetterVisitor::visitBracelet(Bracelet& bracelet) {
    string table = "";
    if (includeTableName) {
        table = "bracelet.";
    }
    visitAccessory(bracelet, table);
    fields.put(table + "pearl_number", bracelet.getPearlNumber());
    fields.put(table + "pearl_diameter", bracelet.getPearlDiameter());
}

void FieldsGetterVisitor::visitBackPack(BackPack& backPack) {
    string table = "";
    if (includeTableName) {
        table = "backpack.";
    }
    visitAccessory(backPack, table);
    fields.put(table + "capacity", backPack.getCapacity());
}

void FieldsGetterVisitor::visitHat(Hat& hat) {
    string table = "";
    if (includeTableName) {
        table = "hat.";
    }
    visitAccessory(hat, table);

    fields.put(table + "is_baseball_cap", hat.isBaseballCap());
}

void FieldsGetterVisitor::visitJeans(Jeans& jeans) {
    string table = "";
    if (includeTableName) {
        table = "jeans.";
    }
    visitClothingItem(jeans, table);
    jeansFields(jeans, table);
}

void FieldsGetterVisitor::visitVest(Vest& vest) {
    string table = "";
    if (includeTableName) {
        table = "vest.";
    }
    visitClothingItem(vest, table);
    vestFields(vest, table);
}

void FieldsGetterVisitor::visitOveralls(Overalls& overalls) {
    string table = "";
    if (includeTableName) {
        table = "overalls.";
    }
    visitClothingItem(overalls, table);
    vestFields(overalls, table);
    jeansFields(overalls, table);
}

void FieldsGetterVisitor::visitAccessory(const Accessory& accessory, const string& table) {
    visitProduct(accessory, table);
    fields.put(table + "category", QString::fromStdString(Accessory::getCategoryAsString(accessory.getCategory())));
}

void FieldsGetterVisitor::visitClothingItem(const ClothingItem& clothingItem, const string& table) {
    visitProduct(clothingItem, table);
    fields.put(table + "sustainable_materials", clothingItem.hasSustainableMaterials());
    fields.put(table + "gender", QString::fromStdString(ClothingItem::getGenderAsString(clothingItem.getGender())));
}

void FieldsGetterVisitor::visitProduct(const Product& product, const string& table) {
    if (includeId) {
        fields.put(table + "id", product.getId());
    }
    fields.put(table + "code", QString::fromStdString(product.getCode()));
    fields.put(table + "color", QString::fromStdString(product.getColor()));
    fields.put(table + "sold_quantity", product.getSoldQuantity());
    fields.put(table + "available_quantity", product.getAvailableQuantity());
    fields.put(table + "description", QString::fromStdString(product.getDescription()));
    if (useNameForForeignKeys) {
        fields.put(table + "size", QString::fromStdString(product.getSize().getNameAsString()));
        fields.put(table + "material", QString::fromStdString(product.getMaterial().getNameAsString()));
    } else {
        fields.put(table + "size_id", product.getSize().getId());
        fields.put(table + "material_id", product.getMaterial().getId());
    }
}

void FieldsGetterVisitor::vestFields(const Vest& vest, const string& table) {
    fields.put(table + "has_buttons", vest.getHasButtons());
}

void FieldsGetterVisitor::jeansFields(const Jeans& jeans, const string& table) {
    fields.put(table + "shorts", jeans.areShorts());
}

void Models::FieldsGetterVisitor::visitMaterial(Material& material) {
    string table = "";

    if (includeTableName) {
        table = "material.";
    }

    fields.put(table + "name", QString::fromStdString(material.getNameAsString()));
    fields.put(table + "cost_per_unit", material.getCostPerUnit());
    fields.put(table + "unit_of_measure", QString::fromStdString(material.getUnitOfMeasureAsString()));
}

void Models::FieldsGetterVisitor::visitSize(Size& size) {
    string table = "";

    if (includeTableName) {
        table = "size.";
    }

    fields.put(table + "name", QString::fromStdString(size.getNameAsString()));
    fields.put(table + "extra_percentage_of_material", size.getExtraPercentageOfMaterial());
}

const Map<string, QVariant>& Models::FieldsGetterVisitor::getFields() const {
    return fields;
}

Models::FieldsGetterVisitor::FieldsGetterVisitor(bool useNameForForeignKeys, bool includeTableName, bool includeId)
        : fields(Map<string, QVariant>()),
          useNameForForeignKeys(useNameForForeignKeys),
          includeTableName(includeTableName),
          includeId(includeId) {}

void Models::FieldsGetterVisitor::clear() {
    fields.eraseAll();
}
