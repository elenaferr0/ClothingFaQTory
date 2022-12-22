#include <QGroupBox>
#include <QLineEdit>
#include <QFormLayout>
#include <QCompleter>
#include <QRegExpValidator>
#include <QSpinBox>
#include <QTextEdit>
#include <QComboBox>
#include "product_info_wizard_page.h"

ProductInfoWizardPage::ProductInfoWizardPage(QWidget* parent,
                                             const QList<QString>& materials,
                                             const QList<QString>& sizes) : QWizardPage(parent) {
    setTitle("Insert product info");
    QFormLayout* layout = new QFormLayout;

    QRegExpValidator* alphaNumericUnderscoresValidator = new QRegExpValidator(QRegExp("^[a-zA-Z0-9_-]*$"));

    QLineEdit* codeLineEdit = new QLineEdit();
    codeLineEdit->setPlaceholderText("Product Code");
    codeLineEdit->setMaxLength(10);
    codeLineEdit->setValidator(alphaNumericUnderscoresValidator);
    layout->addRow("Code", codeLineEdit);

    SelectColorButton* colorButton = new SelectColorButton(nullptr, "Choose color");
    layout->addRow("Color", colorButton);

    QSpinBox* soldQuantitySpinBox = new QSpinBox;
    soldQuantitySpinBox->setMinimum(0);
    soldQuantitySpinBox->setSingleStep(100);
    soldQuantitySpinBox->setMaximum(99999999);
    layout->addRow("Sold quantity", soldQuantitySpinBox);

    QSpinBox* availableQuantitySpinBox = new QSpinBox;
    availableQuantitySpinBox->setMinimum(0);
    availableQuantitySpinBox->setSingleStep(100);
    availableQuantitySpinBox->setMaximum(99999999);
    layout->addRow("Available quantity", availableQuantitySpinBox);

    QTextEdit* descriptionTextEdit = new QTextEdit;
    descriptionTextEdit->setMaximumHeight(75);
    layout->addRow("Description", descriptionTextEdit);

    QComboBox* sizeBox = new QComboBox;
    // iterate over the items to preserve the order (.addItems would not)
    for (int i = 0; i < sizes.size(); ++i) {
        sizeBox->addItem(sizes.value(i));
    }
    layout->addRow("Size", sizeBox);

    QComboBox* materialBox = new QComboBox;
    materialBox->addItems(materials);
    layout->addRow("Material", materialBox);

    setLayout(layout);

}
