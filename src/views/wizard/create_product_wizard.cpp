

#include "create_product_wizard.h"
#include "choose_product_type_wizard_page.h"
#include "product_info_wizard_page.h"

CreateProductWizard::CreateProductWizard(QWidget* parent) : QWizard(parent) {
    addPage(new ChooseProductTypeWizardPage);
    addPage(new ProductInfoWizardPage);
    setWindowTitle("Insert a new product");
}

void CreateProductWizard::accept() {
    QDialog::accept();
}
