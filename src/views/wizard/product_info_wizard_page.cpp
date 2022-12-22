#include <QGroupBox>
#include <QLineEdit>
#include <QFormLayout>
#include <QCompleter>
#include <QRegExpValidator>
#include <QSpinBox>
#include <QTextEdit>
#include <QComboBox>
#include "product_info_wizard_page.h"
#include "create_product_wizard_view.h"

using Models::Product;
using Models::ClothingItems::Jeans;
using Models::ClothingItems::Vest;
using Models::ClothingItems::Overalls;
using Models::Accessories::BackPack;
using Models::Accessories::Bracelet;
using Models::Accessories::Hat;
using Views::Wizard::CreateProductWizardView;
using Controllers::WizardController;

ProductInfoWizardPage::ProductInfoWizardPage(const QList<QString>& materials,
                                             const QList<QString>& sizes,
                                             QWidget* parent)
        : QWizardPage(parent) {
    setTitle("Insert product information");
    QFormLayout* layout = new QFormLayout;

    QRegExpValidator* alphaNumericUnderscoresValidator = new QRegExpValidator(QRegExp("^[a-zA-Z0-9_-]*$"));

    codeLineEdit = new QLineEdit();
    codeLineEdit->setPlaceholderText("Product Code");
    codeLineEdit->setMaxLength(10);
    codeLineEdit->setValidator(alphaNumericUnderscoresValidator);
    registerField("code", codeLineEdit);
    layout->addRow("Code", codeLineEdit);

    colorButton = new SelectColorButton(nullptr, "Choose color");
    registerField("color", colorButton);
    layout->addRow("Color", colorButton);

    QSpinBox* soldQuantitySpinBox = new QSpinBox;
    soldQuantitySpinBox->setRange(0, MAX_SPIN_BOX_VALUE);
    soldQuantitySpinBox->setSingleStep(SPIN_BOX_STEP);
    registerField("soldQuantity", soldQuantitySpinBox);
    layout->addRow("Sold quantity", soldQuantitySpinBox);

    QSpinBox* availableQuantitySpinBox = new QSpinBox;
    availableQuantitySpinBox->setRange(0, MAX_SPIN_BOX_VALUE);
    availableQuantitySpinBox->setSingleStep(SPIN_BOX_STEP);
    registerField("availableQuantity", availableQuantitySpinBox);
    layout->addRow("Available quantity", availableQuantitySpinBox);

    QTextEdit* descriptionTextEdit = new QTextEdit;
    descriptionTextEdit->setMaximumHeight(75);
    registerField("description", descriptionTextEdit);
    layout->addRow("Description", descriptionTextEdit);

    QComboBox* sizeBox = new QComboBox;
    // iterate over the items to preserve the order (.addItems would not)
    for (int i = 0; i < sizes.size(); ++i) {
        sizeBox->addItem(sizes.value(i));
    }
    registerField("size", sizeBox);
    layout->addRow("Size", sizeBox);

    QComboBox* materialBox = new QComboBox;
    materialBox->addItems(materials);
    registerField("material", materialBox);
    layout->addRow("Material", materialBox);
    setLayout(layout);

}

bool ProductInfoWizardPage::validatePage() {
    bool valid = true;

    if (codeLineEdit->text().isEmpty()) {
        codeLineEdit->setStyleSheet("color: red");
        valid = false;
    } else {
        codeLineEdit->setStyleSheet("color: gray");
    }

    if (!colorButton->getColor().isValid()) {
        colorButton->setStyleSheet("color: red");
        valid = false;
    }

    return valid && QWizardPage::validatePage();
}
