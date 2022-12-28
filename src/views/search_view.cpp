

#include <QGroupBox>
#include <QCheckBox>
#include <QFormLayout>
#include <QLineEdit>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QLabel>
#include <QComboBox>
#include "search_view.h"
#include "../controllers/search_controller.h"

using Controllers::SearchController;
using Views::SearchDialog;

SearchDialog::SearchDialog(QWidget* parent) : QDialog(parent) {
    setWindowTitle("Search for a Product");
    resize(400, 500);
    QVBoxLayout* vbox = new QVBoxLayout(this);

    productTypeGroupBox = new QGroupBox("Product Type");
    productTypeGroupBox->setCheckable(true);
    productTypeGroupBox->setChecked(true);

    QFormLayout* productTypeFormLayout = new QFormLayout;
    productTypeGroupBox->setLayout(productTypeFormLayout);

    for (int i = Product::ProductType::Jeans; i != Product::ProductType::Hat + 1; i++) {
        auto productType = static_cast<Product::ProductType>(i);
        QString title = QString::fromStdString(Product::productTypeToString(productType));
        QCheckBox* checkBox = new QCheckBox();
        productTypeFormLayout->addRow(title, checkBox);
    }
    vbox->addWidget(productTypeGroupBox);

    codeGroupBox = new QGroupBox("Code");
    codeGroupBox->setCheckable(true);
    codeGroupBox->setChecked(false);
    QFormLayout* codeFormLayout = new QFormLayout;
    codeGroupBox->setLayout(codeFormLayout);

    QRegularExpression regex("^[a-zA-Z0-9_-]*$");
    QValidator* alphaNumericUnderscoresValidator = new QRegularExpressionValidator(regex, this);

    QLineEdit* codeLineEdit = new QLineEdit;
    codeLineEdit->setPlaceholderText("Product Code");
    codeLineEdit->setValidator(alphaNumericUnderscoresValidator);
    codeFormLayout->addRow("Code (also partial)", codeLineEdit);
    vbox->addWidget(codeGroupBox);

    QGroupBox* priceRangeGroupBox = new QGroupBox("Price range");
    priceRangeGroupBox->setCheckable(true);
    priceRangeGroupBox->setChecked(false);

    QHBoxLayout* priceRangeLayout = new QHBoxLayout;
    priceRangeGroupBox->setLayout(priceRangeLayout);

    minPriceLineEdit = new QLineEdit;
    minPriceLineEdit->setPlaceholderText("Min");

    maxPriceLineEdit = new QLineEdit;
    maxPriceLineEdit->setPlaceholderText("Max");
    maxPriceLineEdit->setDisabled(true);

    QDoubleValidator* minValidator = new QDoubleValidator;
    minValidator->setNotation(QDoubleValidator::StandardNotation);
    minValidator->setRange(0, INT_MAX, 2);
    minPriceLineEdit->setValidator(minValidator);
    connect(minPriceLineEdit, SIGNAL(textChanged(const QString &)), this,
            SLOT(handleMinPriceTextChanged(const QString &)));

    maxValidator = new QDoubleValidator;
    maxValidator->setNotation(QDoubleValidator::StandardNotation);
    maxPriceLineEdit->setValidator(maxValidator);

    priceRangeLayout->addWidget(minPriceLineEdit);
    priceRangeLayout->addWidget(new QLabel("$ to"));
    priceRangeLayout->addWidget(maxPriceLineEdit);
    priceRangeLayout->addWidget(new QLabel("$"));
    priceRangeLayout->setAlignment(Qt::AlignCenter);
    vbox->addWidget(priceRangeGroupBox);

    sortGroupBox = new QGroupBox("Sorting");
    sortGroupBox->setCheckable(true);
    sortGroupBox->setChecked(false);

    QHBoxLayout* fieldSortLayout = new QHBoxLayout;
    sortGroupBox->setLayout(fieldSortLayout);

    fieldSortLayout->addWidget(new QLabel("Field"));

    QComboBox* fieldComboBox = new QComboBox;
    fieldComboBox->addItem("Code");
    fieldComboBox->addItem("Available Quantity");
    fieldComboBox->addItem("Sold quantity");
    fieldSortLayout->addWidget(fieldComboBox);

    fieldSortLayout->addWidget(new QLabel("Order"));

    QComboBox* orderComboBox = new QComboBox;
    orderComboBox->addItem("Ascendant");
    orderComboBox->addItem("Descendant");
    fieldSortLayout->addWidget(orderComboBox);

    vbox->addWidget(sortGroupBox);
}

void Views::SearchDialog::handleMinPriceTextChanged(const QString& price) {
    if (price == "") {
        maxPriceLineEdit->setDisabled(true);
    } else {
        maxPriceLineEdit->setEnabled(true);
        maxValidator->setRange(price.toDouble(), INT_MAX, 2);
    }
}