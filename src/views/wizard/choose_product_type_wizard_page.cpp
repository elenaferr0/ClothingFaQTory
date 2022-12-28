#include <QVBoxLayout>
#include "choose_product_type_wizard_page.h"
#include "../../models/product.h"

using Models::Product;
using Views::Wizard::ChooseProductTypeWizardPage;

ChooseProductTypeWizardPage::ChooseProductTypeWizardPage(QWidget* parent)
        : QWizardPage(parent), comboBox(new QComboBox) {
    setTitle("Which type of product would you ilike to insert?");

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignCenter);

    for (int i = Product::Jeans; i != Product::Hat + 1; i++) {
        auto productType = static_cast<Product::ProductType>(i);
        QString name = QString::fromStdString(Product::productTypeToString(productType));
        comboBox->addItem(QIcon(":/assets/icons/" + name.toLower() + ".png"), name, i);
    }
    comboBox->setIconSize(QSize(25, 25));
    registerField("productType", comboBox);
    layout->addWidget(comboBox);
}

void Views::Wizard::ChooseProductTypeWizardPage::cleanupPage() {
    comboBox->setCurrentIndex(0);
    QWizardPage::cleanupPage();
}
