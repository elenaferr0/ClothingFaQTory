

#ifndef SPECIFIC_PRODUCT_INFO_WIZARD_PAGE_H
#define SPECIFIC_PRODUCT_INFO_WIZARD_PAGE_H


#include <QWizardPage>
#include "specific_product_info_visitor.h"
#include "../../models/product.h"
#include "../../models/clothing_items/jeans.h"
#include "../../models/clothing_items/overalls.h"
#include "../../models/clothing_items/vest.h"
#include "../../models/accessories/hat.h"
#include "../../models/accessories/bracelet.h"
#include "../../models/accessories/backpack.h"
#include "product_wizard_view.h"

using Models::Product;
using Models::Accessories::Hat;
using Models::Accessories::Bracelet;
using Models::Accessories::BackPack;
using Models::ClothingItems::Overalls;
using Models::ClothingItems::Jeans;
using Models::ClothingItems::Vest;

namespace Views::Wizard {
    class SpecificProductInfoWizardPage : public QWizardPage {
        Q_OBJECT
        private:
            ProductWizardView* parentWizard;
            SpecificProductInfoVisitor visitor;

            void setProductFields(Product* product);

        public:
            SpecificProductInfoWizardPage(QWidget* parent = nullptr);

            void cleanupPage() override;

            void initializePage() override;
    };

}

#endif //SPECIFIC_PRODUCT_INFO_WIZARD_PAGE_H
