#ifndef CREATE_PRODUCT_WIZARD_H
#define CREATE_PRODUCT_WIZARD_H


#include <QWizard>
#include <QSet>
#include "../view.h"
#include "../../models/product.h"
#include "../../controllers/wizard_controller.h"

using Models::Product;
using Controllers::WizardController;

namespace Views::Wizard {
    class CreateProductWizardView : public QWizard, public View {
        Q_OBJECT
        private:
            Product* product; // product which is being constructed
        public:
            CreateProductWizardView(QWidget* parent = nullptr,
                                    const QList<QString>& materials = QList<QString>(),
                                    const QList<QString>& sizes = QList<QString>());

//            void accept() override; // called when the user clicks finish
            void setProduct(Product* product);

            Product* getProduct() const;

            WizardController* getController() const;

    };
}

#endif //CREATE_PRODUCT_WIZARD_H
