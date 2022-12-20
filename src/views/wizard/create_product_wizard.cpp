

#include "create_product_wizard.h"
#include "choose_product_type_wizard_page.h"
#include "product_info_wizard_page.h"

using Views::Wizard::CreateProductWizard;

CreateProductWizard::CreateProductWizard(QWidget* parent, const QSet<QString>& productCodes) : QWizard(parent) {
//    addPage(new ChooseProductTypeWizardPage);
    addPage(new ProductInfoWizardPage(nullptr, productCodes));
    setWindowTitle("Insert a new product");
}

void CreateProductWizard::accept() {
    QDialog::accept();
}
