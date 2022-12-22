

#include "create_product_wizard_view.h"
#include "choose_product_type_wizard_page.h"
#include "product_info_wizard_page.h"

using Views::Wizard::CreateProductWizardView;

CreateProductWizardView::CreateProductWizardView(QWidget* parent,
                                                 const QList<QString>& materials,
                                                 const QList<QString>& sizes) : QWizard(parent) {
//    addPage(new ChooseProductTypeWizardPage);
    addPage(new ProductInfoWizardPage(materials, sizes));
    setWindowTitle("Insert a new product");
}

void CreateProductWizardView::accept() {
    Product::ProductType productType = static_cast<Product::ProductType>(field("productType").toInt());

    // create a Product* which has a dynamic value of a concrete class
    // this allows using the visitor pattern to create a different page
    // based on the product type

    switch (productType) { // set
        case Product::Jeans: {
            Jeans* jeans = new Jeans;
            setFields(jeans);
            break;
        }
        case Product::Overalls: {
            Overalls* overalls = new Overalls;
            setFields(overalls);
            break;
        }
        case Product::Hat: {
            Hat* hat = new Hat;
            setFields(hat);
            break;
        }
        case Product::Bracelet: {
            Bracelet* bracelet = new Bracelet;
            setFields(bracelet);
            break;
        }
        case Product::Vest: {
            Vest* vest = new Vest;
            setFields(vest);
            break;
        }
        case Product::BackPack: {
            BackPack* backpack = new BackPack;
            setFields(backpack);
            break;
        }
    }
    QDialog::accept();
}

void CreateProductWizardView::setFields(Product* product) {
    product->setCode(field("code").toString().toStdString());
    product->setColor(field("color").toString().toStdString());
    product->setSoldQuantity(field("soldQuantity").toInt());
    product->setAvailableQuantity(field("availableQuantity").toInt());
    product->setDescription(field("description").toString().toStdString());
    QString sizeName = field("size").toString();
    product->setSize(*dynamic_cast<WizardController*>(controller)->findSizeByName(sizeName));
    QString materialName = field("material").toString();
    product->setMaterial(*dynamic_cast<WizardController*>(controller)->findMaterialByName(materialName));
}