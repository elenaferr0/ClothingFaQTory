

#ifndef INFO_DIALOG_VISITOR_H
#define INFO_DIALOG_VISITOR_H

#include "../core/visitor_interface.h"
#include "../models/product.h"
#include "../models/accessories/accessory.h"
#include "../models/clothing_items/clothing_item.h"
#include "../models/clothing_items/jeans.h"
#include "../models/clothing_items/vest.h"
#include "../models/clothing_items/overalls.h"
#include "../models/accessories/hat.h"
#include "../models/accessories/bracelet.h"
#include "../models/accessories/backpack.h"
#include <QObject>
#include <QFormLayout>

using Models::Accessory;
using Models::Product;
using Models::ClothingItem;
using Models::ClothingItems::Jeans;
using Models::ClothingItems::Vest;
using Models::ClothingItems::Overalls;
using Models::Accessories::Hat;
using Models::Accessories::BackPack;
using Models::Accessories::Bracelet;
using Models::ClothingItem;
using Models::ClothingItem;
using Core::VisitorInterface;

namespace Views {
    class InfoDialogVisitor : public VisitorInterface {
        private:
            QFormLayout* layout;
        static const int ICON_SIZE = 30;

            void visitProduct(Product& product);

            void visitAccessory(Accessory& accessory);

            void visitClothingItem(ClothingItem& clothingItem);

            void visitMaterial(Material& material) override;

            void visitSize(Size& size) override;

        public:
            InfoDialogVisitor();

            QFormLayout* getLayout() const;

            void visitBracelet(Bracelet& bracelet) override;

            void visitBackPack(BackPack& backPack) override;

            void visitHat(Hat& hat) override;

            void visitJeans(Jeans& jeans) override;

            void visitVest(Vest& vest) override;

            void visitOveralls(Overalls& overalls) override;

            void buildJeans(Jeans& jeans);

            void buildVest(Vest& vest);
    };

}


#endif //INFO_DIALOG_VISITOR_H
