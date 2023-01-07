#ifndef CREATE_PRODUCT_WIZARD_H
#define CREATE_PRODUCT_WIZARD_H

#include <QObject>
#include <QWizard>
#include <QSet>
#include "../view.h"
#include "../../models/product.h"
#include "../../controllers/wizard_controller.h"
#include "../main_view.h"

namespace Views {
    class MainView;
}

namespace Controllers {
    class WizardController;
}
using Views::MainView;
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

        public:
            void reject() override;

        protected:
            Mode mode;
        private:
            shared_ptr<Product> product; // product which is being constructed
            string getCategory();

            bool getSustainableMaterials();

            ClothingItem::Gender getGender();

        public:
            void setProduct(shared_ptr<Product> product);

            shared_ptr<Product> getProduct() const;

            WizardController* getController() const;

            ProductWizardView(Mode mode, MainView* mainView, QWidget* parent = nullptr,
                              const QList<QString>& materials = QList<QString>(),
                              const QList<QString>& sizes = QList<QString>(),
                              shared_ptr<Product> = nullptr,
                              Product::ProductType productType = Product::Jeans);

            Mode getMode() const;

        signals:

            void completed(shared_ptr<Product> product, Product::ProductType);

    };
}

#endif //CREATE_PRODUCT_WIZARD_H
