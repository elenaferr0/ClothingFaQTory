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

            void visitProduct(const Product& product);

            void visitAccessory(const Accessory&);

            void visitClothingItem(const ClothingItem&);

            void vestFields(const Vest&);

            void jeansFields(const Jeans&);

        public:
            FieldsGetterVisitor() = default;

            const Map <string, QVariant>& getFields() const;

            void visitBracelet(Bracelet& bracelet) override;

            void visitBackPack(BackPack& pack) override;

            void visitHat(Hat& hat) override;

            void visitJeans(Jeans& jeans) override;

            void visitVest(Vest& vest) override;

            void visitOveralls(Overalls& overalls) override;

            void visitMaterial(Material& material) override;

            void visitSize(Size& size) override;
    };

}

#endif //FIELDS_GETTER_VISITOR_H
