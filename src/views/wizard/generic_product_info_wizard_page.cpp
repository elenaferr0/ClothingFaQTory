#include <QGroupBox>
#include <QLineEdit>
#include <QFormLayout>
#include <QCompleter>
#include <QTime>
#include <QRegularExpressionValidator>
#include <QRegularExpression>
#include <QRandomGenerator>
#include "generic_product_info_wizard_page.h"
#include "product_wizard_view.h"

using Models::Product;
using Models::ClothingItems::Jeans;
using Models::ClothingItems::Vest;
using Models::ClothingItems::Overalls;
using Models::Accessories::BackPack;
using Models::Accessories::Bracelet;
using Models::Accessories::Hat;
using Views::Wizard::ProductWizardView;
using Controllers::WizardController;

GenericProductInfoWizardPage::GenericProductInfoWizardPage(const QList<QString>& materials,
                                                           const QList<QString>& sizes,
                                                           Product::ProductType productType,
                                                           QWidget* parent)
        : QWizardPage(parent), parentWizard(dynamic_cast<ProductWizardView*>(parent)) {

    setTitle(parentWizard->getMode() == ProductWizardView::Create ?
             "Insert generic product information" : "Edit generic product information");
    QFormLayout* layout = new QFormLayout;

    QRegularExpression regex("^[a-zA-Z0-9_-]*$");
    QValidator* alphaNumericUnderscoresValidator = new QRegularExpressionValidator(regex, this);

    codeLineEdit = new QLineEdit();
    codeLineEdit->setPlaceholderText("Product Code");
    codeLineEdit->setMaxLength(10);
    codeLineEdit->setValidator(alphaNumericUnderscoresValidator);
    registerField("code", codeLineEdit);

    if (parentWizard->getMode() == ProductWizardView::Create) {
        QHBoxLayout* hbox = new QHBoxLayout;
        QPushButton* randomCodeButton = new QPushButton;
        randomCodeButton->setIcon(QIcon(":/assets/icons/dices.png"));
        randomCodeButton->setIconSize(QSize(25, 25));
        randomCodeButton->setObjectName("randomCodeButton");
        randomCodeButton->setToolTip("Generate a random code");
        connect(randomCodeButton, SIGNAL(clicked(bool)), this, SLOT(handleRandomCodeButtonPressed(bool)));
        hbox->addWidget(codeLineEdit);
        hbox->addWidget(randomCodeButton);
        layout->addRow("Code", hbox);
    } else {
        layout->addRow("Code", codeLineEdit);
    }

    colorButton = new SelectColorButton(nullptr, "Choose color");
    colorButton->setAutoDefault(false);
    colorButton->setDefault(true);
    // using mockColorLineEdit to register the color field
    mockColorLineEdit = new QLineEdit;
    mockColorLineEdit->setVisible(false);
    registerField("color", mockColorLineEdit);

    connect(colorButton, SIGNAL(colorChanged(const QString &)), this, SLOT(handleColorChange(const QString &)));
    layout->addRow("Color", colorButton);

    soldQuantitySpinBox = new QSpinBox;
    soldQuantitySpinBox->setRange(0, MAX_SPIN_BOX_VALUE);
    soldQuantitySpinBox->setSingleStep(SPIN_BOX_STEP);
    registerField("soldQuantity", soldQuantitySpinBox);
    layout->addRow("Sold quantity", soldQuantitySpinBox);

    availableQuantitySpinBox = new QSpinBox;
    availableQuantitySpinBox->setRange(0, MAX_SPIN_BOX_VALUE);
    availableQuantitySpinBox->setSingleStep(SPIN_BOX_STEP);
    registerField("availableQuantity", availableQuantitySpinBox);
    layout->addRow("Available quantity", availableQuantitySpinBox);

    descriptionTextEdit = new QTextEdit;
    descriptionTextEdit->setMaximumHeight(75);
    registerField("description", descriptionTextEdit, "plainText");
    layout->addRow("Description", descriptionTextEdit);

    sizeBox = new QComboBox;
    for (int i = 0; i < sizes.size(); ++i) {
        sizeBox->addItem(sizes.value(i));
    }
    registerField("size", sizeBox);
    layout->addRow("Size", sizeBox);

    materialBox = new QComboBox;
    materialBox->addItems(materials);
    registerField("material", materialBox);
    layout->addRow("Material", materialBox);

    if (parentWizard->getMode() == ProductWizardView::Edit) {
        shared_ptr<Product> product = parentWizard->getProduct();
        codeLineEdit->setText(QString::fromStdString(product->getCode()));
        codeLineEdit->setDisabled(true);
        QString hex = QString::fromStdString(product->getColor());
        mockColorLineEdit->setText(hex);
        colorButton->setColor(hex);
        soldQuantitySpinBox->setValue(product->getSoldQuantity());
        availableQuantitySpinBox->setValue(product->getAvailableQuantity());
        descriptionTextEdit->setText(QString::fromStdString(product->getDescription()));
        sizeBox->setCurrentIndex(product->getSize().getId() - 1);
        materialBox->setCurrentIndex(product->getMaterial().getId() - 1);
        registerProductTypeField(productType);
    }
    setLayout(layout);

}

bool GenericProductInfoWizardPage::validatePage() {
    bool valid = true;

    if (codeLineEdit->text().isEmpty()) {
        codeLineEdit->setStyleSheet("color: red");
        valid = false;
    } else {
        codeLineEdit->setStyleSheet("color: black");
    }

    if (!colorButton->getColor().isValid()) {
        colorButton->setStyleSheet("color: red");
        valid = false;
    }

    return valid && QWizardPage::validatePage();
}

void GenericProductInfoWizardPage::handleColorChange(const QString& hex) {
    mockColorLineEdit->setText(hex);
}

void GenericProductInfoWizardPage::cleanupPage() {
    codeLineEdit->clear();
    if (parentWizard->getMode() == ProductWizardView::Create) {
        colorButton->setColor(QColor(""));
        mockColorLineEdit->clear();
    }
    soldQuantitySpinBox->setValue(0);
    availableQuantitySpinBox->setValue(0);
    descriptionTextEdit->clear();
    sizeBox->setCurrentIndex(0);
    materialBox->setCurrentIndex(0);
    QWizardPage::cleanupPage();
}

void GenericProductInfoWizardPage::registerProductTypeField(Product::ProductType productType) {
    // The product type has to be manually registered with a mock widget to
    // allow reusing the same logic for creation (when editing a product the type cannot be changed)
    QSpinBox* mockSpinBox = new QSpinBox;
    mockSpinBox->setValue(productType);
    registerField("productType", mockSpinBox);
}

void GenericProductInfoWizardPage::handleRandomCodeButtonPressed(bool) {
    QRandomGenerator gen(QTime::currentTime().msec());
    QString randomString;
    for (int i = 0; i < 12; ++i) {
        int randomInt = gen.bounded('A', 'Z' + 1);
        randomString.append(QChar(randomInt));
    }
    codeLineEdit->setText(randomString);
    codeLineEdit->setStyleSheet("color: black");
}
