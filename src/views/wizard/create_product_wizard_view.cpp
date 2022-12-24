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
    setDefaultProperty("QTextEdit", "plainText", "textChanged");
    connect(this, SIGNAL(productCreationCompleted(Product * , Product::ProductType)),
            controller, SLOT(handleProductCreation(Product * , Product::ProductType)));
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

void CreateProductWizardView::done(int result) {
    if (result == QDialog::Accepted) {
        Product::ProductType productType = static_cast<Product::ProductType>(field("productType").toInt());
        switch (productType) {
            case Product::Jeans: {
                Jeans* jeans = dynamic_cast<Jeans*>(product);
                jeans->setSustainableMaterials(getSustainableMaterials());
                jeans->setGender(getGender());
                jeans->setShorts(field("shorts").toBool());
                break;
            }
            case Product::Overalls: {
                Overalls* overalls = dynamic_cast<Overalls*>(product);
                overalls->setSustainableMaterials(getSustainableMaterials());
                overalls->setGender(getGender());
                overalls->setShorts(field("shorts").toBool());
                overalls->setHasButtons(field("hasButtons").toBool());
                break;
            }
            case Product::Hat: {
                Hat* hat = dynamic_cast<Hat*>(product);
                hat->setCategory(getCategory());
                hat->setBaseballCap(field("baseballCap").toBool());
                break;
            }
            case Product::Bracelet: {
                Bracelet* bracelet = dynamic_cast<Bracelet*>(product);
                bracelet->setCategory(getCategory());
                bracelet->setPearlDiameter(field("pearlDiameter").toDouble());
                bracelet->setPearlNumber(field("pearlNumber").toInt());
                break;
            }
            case Product::Vest: {
                Vest* vest = dynamic_cast<Vest*>(product);
                vest->setSustainableMaterials(getSustainableMaterials());
                vest->setGender(getGender());
                vest->setHasButtons(field("hasButtons").toBool());
                break;
            }
            case Product::BackPack: {
                BackPack* backpack = dynamic_cast<BackPack*>(product);
                backpack->setCategory(getCategory());
                backpack->setCapacity(field("capacity").toDouble());
                break;
            }
        }
        emit productCreationCompleted(product,
                                      static_cast<Product::ProductType>(field("productType").toInt()));
    }
    QWizard::done(result);
}

string CreateProductWizardView::getCategory() {
    int categoryIndex = field("category").toInt();
    return Accessory::getCategoryAsString(static_cast<Accessory::Category>(categoryIndex));
}

bool CreateProductWizardView::getSustainableMaterials() {
    return field("sustainableMaterials").toBool();
}

ClothingItem::Gender CreateProductWizardView::getGender() {
    int genderIndex = field("gender").toInt();
    return static_cast<ClothingItem::Gender>(genderIndex);
}

void CreateProductWizardView::cleanupPage(int id) {
    for (int i = 0; i < id; ++i) {
        QWizardPage* page = this->page(i);
        page->cleanupPage();
    }
    QWizard::cleanupPage(id);
}
