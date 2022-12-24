#ifndef CHOOSE_PRODUCT_TYPE_WIZARD_PAGE_H
#define CHOOSE_PRODUCT_TYPE_WIZARD_PAGE_H


#include <QWizardPage>
#include <QComboBox>

namespace Views::Wizard {
    class ChooseProductTypeWizardPage : public QWizardPage {
        Q_OBJECT
        private:
            QComboBox* comboBox;
        public:
            ChooseProductTypeWizardPage(QWidget* parent = nullptr);

            void cleanupPage() override;
    };
}


#endif //CHOOSE_PRODUCT_TYPE_WIZARD_PAGE_H
