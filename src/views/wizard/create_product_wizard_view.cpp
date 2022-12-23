

#include "create_product_wizard_view.h"
#include "choose_product_type_wizard_page.h"
#include "generic_product_info_wizard_page.h"
#include "specific_product_info_wizard_page.h"

using Views::Wizard::CreateProductWizardView;
using Views::Wizard::ChooseProductTypeWizardPage;

CreateProductWizardView::CreateProductWizardView(QWidget* parent,
                                                 const QList<QString>& materials,
                                                 const QList<QString>& sizes) : QWizard(parent) {
    controller = new WizardController(this);
    addPage(new ChooseProductTypeWizardPage(this));
    addPage(new GenericProductInfoWizardPage(materials, sizes, this));
    addPage(new SpecificProductInfoWizardPage(this));
    setWindowTitle("Insert a new product");
}

void CreateProductWizardView::setProduct(Product* product) {
    this->product = product;
}

WizardController* CreateProductWizardView::getController() const {
    return dynamic_cast<WizardController*>(controller);
}

Product* CreateProductWizardView::getProduct() const {
    return product;
}
