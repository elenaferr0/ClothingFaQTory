#ifndef CREATE_PRODUCT_WIZARD_H
#define CREATE_PRODUCT_WIZARD_H


#include <QWizard>
#include <QSet>
#include "../view.h"

namespace Views::Wizard {
    class CreateProductWizard : public QWizard, public View {
        Q_OBJECT
        public:
            CreateProductWizard(QWidget* parent = nullptr, const QSet<QString>& productCodes = QSet<QString>());

            void accept() override; // called when the user clicks finish
    };
}

#endif //CREATE_PRODUCT_WIZARD_H
