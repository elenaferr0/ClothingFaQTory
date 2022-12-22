#ifndef CREATE_PRODUCT_WIZARD_H
#define CREATE_PRODUCT_WIZARD_H


#include <QWizard>
#include <QSet>
#include "../view.h"
#include "../../models/product.h"

using Models::Product;
namespace Views::Wizard {
    class CreateProductWizardView : public QWizard, public View {
        Q_OBJECT
        private:
            Product* product; // product which is being constructed
        public:
            CreateProductWizardView(QWidget* parent = nullptr,
                                    const QList<QString>& materials = QList<QString>(),
                                    const QList<QString>& sizes = QList<QString>());

            void accept() override; // called when the user clicks finish
            void setFields(Product* product);
    };
}

#endif //CREATE_PRODUCT_WIZARD_H
