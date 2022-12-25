#ifndef CREATE_PRODUCT_WIZARD_H
#define CREATE_PRODUCT_WIZARD_H

#include <QObject>
#include <QWizard>
#include <QSet>
#include "../view.h"
#include "../../models/product.h"
#include "../../controllers/wizard_controller.h"

namespace Controllers {
    class WizardController;
}

using Models::Product;
using Controllers::WizardController;

namespace Views::Wizard {
    class ProductWizardView : public QWizard, public View {
        Q_OBJECT
        public:

            enum Mode {
                Edit, Create
            };

        protected:
            void done(int result) override;

            void cleanupPage(int id) override;

            Mode mode;
        private:
            Product* product; // product which is being constructed
            string getCategory();

            bool getSustainableMaterials();

            ClothingItem::Gender getGender();

        public:
            void setProduct(Product* product);

            Product* getProduct() const;

            WizardController* getController() const;

            ProductWizardView(Mode mode, QWidget* parent = nullptr,
                              const QList<QString>& materials = QList<QString>(),
                              const QList<QString>& sizes = QList<QString>(),
                              Product* = nullptr);

            Mode getMode() const;

        signals:

            void completed(Product* product, Product::ProductType);

    };
}

#endif //CREATE_PRODUCT_WIZARD_H
