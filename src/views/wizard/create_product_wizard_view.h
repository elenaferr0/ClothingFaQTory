#ifndef CREATE_PRODUCT_WIZARD_H
#define CREATE_PRODUCT_WIZARD_H


#include <QWizard>
#include <QSet>
#include "../view.h"

namespace Views::Wizard {
    class CreateProductWizardView : public QWizard, public View {
        Q_OBJECT
        public:
            CreateProductWizardView(QWidget* parent = nullptr,
                                    const QSet<QString>& materials = QSet<QString>(),
                                    const QSet<QString>& sizes = QSet<QString>());

            void accept() override; // called when the user clicks finish
    };
}

#endif //CREATE_PRODUCT_WIZARD_H
