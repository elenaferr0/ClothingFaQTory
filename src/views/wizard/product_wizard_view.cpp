#include "product_wizard_view.h"
#include "choose_product_type_wizard_page.h"
#include "generic_product_info_wizard_page.h"
#include "specific_product_info_wizard_page.h"

using Views::Wizard::ProductWizardView;
using Views::Wizard::ChooseProductTypeWizardPage;

ProductWizardView::ProductWizardView(Mode mode,
                                     QWidget* parent,
                                     const QList<QString>& materials,
                                     const QList<QString>& sizes,
                                     Product* product,
                                     Product::ProductType productType)
        : QWizard(parent), product(product), mode(mode) {
    controller = new WizardController(this);
    if (mode == Mode::Create) {
        addPage(new ChooseProductTypeWizardPage(this));
    }
    addPage(new GenericProductInfoWizardPage(materials, sizes, productType, this));
    addPage(new SpecificProductInfoWizardPage(this));
    setWindowTitle(mode == Create ? "Insert a new product" : "Edit product");

    setDefaultProperty("QTextEdit", "plainText", "textChanged");

    connect(this, SIGNAL(completed(Product * , Product::ProductType)),
            controller, SLOT(handleProductEditAndCreate(Product * , Product::ProductType)));

}

void ProductWizardView::setProduct(Product* product) {
    this->product = product;
}

WizardController* ProductWizardView::getController() const {
    return dynamic_cast<WizardController*>(controller);
}

Product* ProductWizardView::getProduct() const {
    return product;
}

void ProductWizardView::done(int result) {
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
        emit completed(product,
                       static_cast<Product::ProductType>(field("productType").toInt()));
    }
    QWizard::done(result);
}

string ProductWizardView::getCategory() {
    int categoryIndex = field("category").toInt();
    return Accessory::getCategoryAsString(static_cast<Accessory::Category>(categoryIndex));
}

bool ProductWizardView::getSustainableMaterials() {
    return field("sustainableMaterials").toBool();
}

ClothingItem::Gender ProductWizardView::getGender() {
    int genderIndex = field("gender").toInt();
    return static_cast<ClothingItem::Gender>(genderIndex);
}

void ProductWizardView::cleanupPage(int id) {
    for (int i = 0; i < id; ++i) {
        QWizardPage* page = this->page(i);
        page->cleanupPage();
    }
    QWizard::cleanupPage(id);
}

ProductWizardView::Mode Views::Wizard::ProductWizardView::getMode() const {
    return mode;
}
