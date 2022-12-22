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
                                             const QSet<QString>& materials,
                                             const QSet<QString>& sizes) : QWizardPage(parent) {
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
    sizeBox->addItems(sizes.values());
    layout->addRow("Size", sizeBox);

    QComboBox* materialBox = new QComboBox;
    materialBox->addItems(materials.values());
    layout->addRow("Material", materialBox);

    setLayout(layout);

}
