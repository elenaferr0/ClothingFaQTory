#ifndef GENERIC_PRODUCT_INFO_WIZARD_PAGE_H
#define GENERIC_PRODUCT_INFO_WIZARD_PAGE_H

#include "../../models/product.h"
#include "../../controllers/wizard_controller.h"
#include <QWizardPage>
#include <QLineEdit>
#include <QSpinBox>
#include <QTextEdit>
#include <QComboBox>
#include <QSet>
#include <limits>
#include "../components/select_color_button.h"

QT_BEGIN_NAMESPACE
namespace Views::Wizard { class InsertProductInfoWizardPage; }
QT_END_NAMESPACE

using Models::Product;
using Controllers::WizardController;
using Views::Wizard::ProductWizardView;

class GenericProductInfoWizardPage : public QWizardPage {
    Q_OBJECT
    private:
        static const int MAX_SPIN_BOX_VALUE = INT_MAX;
        static const int SPIN_BOX_STEP = 100;
        QLineEdit* codeLineEdit;
        SelectColorButton* colorButton;
        QSpinBox* soldQuantitySpinBox;
        QSpinBox* availableQuantitySpinBox;
        QTextEdit* descriptionTextEdit;
        QComboBox* sizeBox;
        QComboBox* materialBox;
        ProductWizardView* parentWizard;
        QLineEdit* mockColorLineEdit;

        void registerProductTypeField(Product::ProductType productType);

    public:
        GenericProductInfoWizardPage(const QList<QString>&,
                                     const QList<QString>&,
                                     Product::ProductType productType,
                                     QWidget* parent = nullptr);

        bool validatePage() override;

        void cleanupPage() override;

    private slots:

        void handleColorChange(const QString&);

        void handleRandomCodeButtonPressed(bool);
};


#endif //GENERIC_PRODUCT_INFO_WIZARD_PAGE_H
