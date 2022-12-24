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
    class CreateProductWizardView : public QWizard, public View {
        Q_OBJECT
        protected:
            void done(int result) override;

            void cleanupPage(int id) override;

        private:
            Product* product; // product which is being constructed
            string getCategory();

            bool getSustainableMaterials();

            ClothingItem::Gender getGender();

        public:
            CreateProductWizardView(QWidget* parent = nullptr,
                                    const QList<QString>& materials = QList<QString>(),
                                    const QList<QString>& sizes = QList<QString>());

            void setProduct(Product* product);

            Product* getProduct() const;

            WizardController* getController() const;

        signals:

            void productCreationCompleted(Product* product, Product::ProductType);

    };
}

#endif //CREATE_PRODUCT_WIZARD_H
