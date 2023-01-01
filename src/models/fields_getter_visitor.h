#ifndef FIELDS_GETTER_VISITOR_H
#define FIELDS_GETTER_VISITOR_H

#include "../core/visitor_interface.h"
#include "../core/containers/map.h"
#include <string>
#include <QVariantList>
#include "../models/accessories/accessory.h"
#include "../models/clothing_items/clothing_item.h"
#include "../models/accessories/hat.h"
#include "../models/accessories/hat.h"
#include "../models/accessories/backpack.h"
#include "../models/accessories/bracelet.h"
#include "../models/clothing_items/vest.h"
#include "../models/clothing_items/overalls.h"
#include "../models/clothing_items/jeans.h"
#include "../models/product.h"

using std::string;
using Core::Containers::Map;
using Models::Product;
using Models::Accessory;
using Models::ClothingItem;
using Models::Accessories::Hat;
using Models::Accessories::Bracelet;
using Models::Accessories::BackPack;
using Models::ClothingItems::Jeans;
using Models::ClothingItems::Overalls;
using Models::ClothingItems::Vest;


namespace Models {
    class FieldsGetterVisitor : public VisitorInterface {
        private:
            Map <string, QVariant> fields;
            bool useNameForForeignKeys;
            bool includeTableName;
            bool includeId;

            void visitProduct(const Product& product, const string& table);

            void visitAccessory(const Accessory&, const string& table);

            void visitClothingItem(const ClothingItem&, const string& table);

            void vestFields(const Vest&, const string& table);

            void jeansFields(const Jeans&, const string& table);

        public:
            static const bool USE_NAME_FOR_FOREIGN_KEYS = true;
            static const bool USE_ID_FOR_FOREIGN_KEYS = false;
            static const bool INCLUDE_TABLE_NAME = true;
            static const bool EXCLUDE_TABLE_NAME = false;
            static const bool EXCLUDE_ID = false;
            static const bool INCLUDE_ID = true;

            FieldsGetterVisitor(bool useNameForForeignKeys = false, bool includeTableName = false,
                                bool includeId = false);

            const Map <string, QVariant>& getFields() const;

            void visitBracelet(Bracelet& bracelet) override;

            void visitBackPack(BackPack& pack) override;

            void visitHat(Hat& hat) override;

            void visitJeans(Jeans& jeans) override;

            void visitVest(Vest& vest) override;

            void visitOveralls(Overalls& overalls) override;

            void visitMaterial(Material& material) override;

            void visitSize(Size& size) override;

            void clear();
    };

}

#endif //FIELDS_GETTER_VISITOR_H
