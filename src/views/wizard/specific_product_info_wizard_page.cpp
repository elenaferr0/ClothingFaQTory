#include <QVariant>
#include "specific_product_info_wizard_page.h"
#include "create_product_wizard_view.h"

using Views::Wizard::SpecificProductInfoWizardPage;
using Views::Wizard::CreateProductWizardView;

SpecificProductInfoWizardPage::SpecificProductInfoWizardPage(QWidget* parent)
        : QWizardPage(parent),
          visitor(SpecificProductInfoVisitor()),
          parentWizard(dynamic_cast<CreateProductWizardView*>(parent)) {

}

void SpecificProductInfoWizardPage::initializePage() {
    Product::ProductType productType = static_cast<Product::ProductType>(field("productType").toInt());

    // create a Product* which has a type value of one of the concrete classes.
    // this allows using the visitor pattern to create a different page
    // based on the product type

    switch (productType) { // set
        case Product::Jeans: {
            Jeans* jeans = new Jeans;
            setFields(jeans);
            parentWizard->setProduct(jeans);
            break;
        }
        case Product::Overalls: {
            Overalls* overalls = new Overalls;
            setFields(overalls);
            parentWizard->setProduct(overalls);
            break;
        }
        case Product::Hat: {
            Hat* hat = new Hat;
            setFields(hat);
            parentWizard->setProduct(hat);
            break;
        }
        case Product::Bracelet: {
            Bracelet* bracelet = new Bracelet;
            setFields(bracelet);
            parentWizard->setProduct(bracelet);
            break;
        }
        case Product::Vest: {
            Vest* vest = new Vest;
            setFields(vest);
            parentWizard->setProduct(vest);
            break;
        }
        case Product::BackPack: {
            BackPack* backpack = new BackPack;
            setFields(backpack);
            parentWizard->setProduct(backpack);
            break;
        }
    }

    parentWizard->getProduct()->accept(visitor);
    setLayout(visitor.getLayout());

    auto fieldsToRegister = visitor.getFieldsToRegister();
    for (const auto& entry: fieldsToRegister.toStdMap()) {
        registerField(entry.first, entry.second);
    }
    QWizardPage::initializePage();
}

void SpecificProductInfoWizardPage::setFields(Product* product) {
    product->setCode(field("code").toString().toStdString());
    product->setColor(field("color").toString().toStdString()); // TODO fix color
    product->setSoldQuantity(field("soldQuantity").toInt());
    product->setAvailableQuantity(field("availableQuantity").toInt());
    product->setDescription(field("description").toString().toStdString());

    QString sizeName = field("size").toString();
    product->setSize(*parentWizard->getController()->findSizeByName(sizeName));

    QString materialName = field("material").toString();
    product->setMaterial(*parentWizard->getController()->findMaterialByName(materialName));
}
