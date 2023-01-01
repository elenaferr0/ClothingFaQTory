#include <QVariant>
#include "specific_product_info_wizard_page.h"
#include "product_wizard_view.h"
#include <memory>

using std::make_shared;
using std::static_pointer_cast;
using Views::Wizard::SpecificProductInfoWizardPage;
using Views::Wizard::ProductWizardView;

SpecificProductInfoWizardPage::SpecificProductInfoWizardPage(QWidget* parent)
        : QWizardPage(parent),
          parentWizard(dynamic_cast<ProductWizardView*>(parent)),
          visitor(SpecificProductInfoVisitor(parentWizard->getMode())) {
    setWindowTitle(parentWizard->getMode() == ProductWizardView::Create ? "Insert specific product info"
                                                                        : "Edit specific product info");
}

void SpecificProductInfoWizardPage::initializePage() {
    Product::ProductType productType = static_cast<Product::ProductType>(field("productType").toInt());
    // create a shared_ptr<Product> which has a type value of one of the concrete classes.
    // this allows using the visitor pattern to create a different page
    // based on the product type

    if (parentWizard->getMode() == ProductWizardView::Edit) {
        setProductFields(parentWizard->getProduct());
    } else {
        shared_ptr<Product> product;

        switch (productType) {
            case Product::Jeans: {
                shared_ptr<Jeans> jeans = make_shared<Jeans>();
                product = static_pointer_cast<Product>(jeans);
                break;
            }
            case Product::Overalls: {
                shared_ptr<Overalls> overalls = make_shared<Overalls>();
                product = static_pointer_cast<Product>(overalls);
                break;
            }
            case Product::Hat: {
                shared_ptr<Hat> hat = make_shared<Hat>();
                product = static_pointer_cast<Product>(hat);
                break;
            }
            case Product::Bracelet: {
                shared_ptr<Bracelet> bracelet = make_shared<Bracelet>();
                product = static_pointer_cast<Product>(bracelet);
                break;
            }
            case Product::Vest: {
                shared_ptr<Vest> vest = make_shared<Vest>();
                product = static_pointer_cast<Product>(vest);
                break;
            }
            case Product::BackPack: {
                shared_ptr<BackPack> backpack = make_shared<BackPack>();
                product = static_pointer_cast<Product>(backpack);
                break;
            }
        }
        setProductFields(product);
        parentWizard->setProduct(product);
    }

    parentWizard->getProduct()->accept(visitor);
    setLayout(visitor.getLayout());

    auto fieldsToRegister = visitor.getFieldsToRegister();
    for (const auto& entry: fieldsToRegister.toStdMap()) {
        registerField(entry.first, entry.second);
    }
    QWizardPage::initializePage();
}

void SpecificProductInfoWizardPage::setProductFields(shared_ptr<Product> product) {
    product->setCode(field("code").toString().toStdString());
    product->setColor(field("color").toString().toStdString());
    product->setSoldQuantity(field("soldQuantity").toInt());
    product->setAvailableQuantity(field("availableQuantity").toInt());
    product->setDescription(field("description").toString().toStdString());

    int sizeId = field("size").toInt() + 1; // in the combobox the ids start from 0
    product->setSize(*parentWizard->getController()->findSizeById(sizeId));

    int materialId = field("material").toInt() + 1;
    product->setMaterial(*parentWizard->getController()->findMaterialById(materialId));
}

void Views::Wizard::SpecificProductInfoWizardPage::cleanupPage() {
    visitor.clean();
    QWizardPage::cleanupPage();
}

