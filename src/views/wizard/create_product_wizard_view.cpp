

#include "create_product_wizard_view.h"
#include "choose_product_type_wizard_page.h"
#include "product_info_wizard_page.h"

using Views::Wizard::CreateProductWizardView;

CreateProductWizardView::CreateProductWizardView(QWidget* parent,
                                                 const QList<QString>& materials,
                                                 const QList<QString>& sizes) : QWizard(parent) {
//    addPage(new ChooseProductTypeWizardPage);
    addPage(new ProductInfoWizardPage(nullptr, materials, sizes));
    setWindowTitle("Insert a new product");
}

void CreateProductWizardView::accept() {
    QDialog::accept();
}
