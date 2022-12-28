

#include <QGroupBox>
#include <QCheckBox>
#include <QFormLayout>
#include <QLineEdit>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QDialogButtonBox>
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
    productTypeGroupBox->setChecked(false);
    connect(productTypeGroupBox, SIGNAL(clicked()), this, SLOT(validate()));

    QFormLayout* productTypeFormLayout = new QFormLayout;
    productTypeGroupBox->setLayout(productTypeFormLayout);

    for (int i = Product::ProductType::Jeans; i != Product::ProductType::Hat + 1; i++) {
        auto productType = static_cast<Product::ProductType>(i);
        QString title = QString::fromStdString(Product::productTypeToString(productType));
        QCheckBox* checkBox = new QCheckBox(title);
        checkBox->setChecked(true);
        connect(checkBox, SIGNAL(clicked()), this, SLOT(validate()));
        productTypeFormLayout->addWidget(checkBox);
        productTypeCheckboxes.pushBack(checkBox);
    }
    vbox->addWidget(productTypeGroupBox);

    codeGroupBox = new QGroupBox("Code");
    codeGroupBox->setCheckable(true);
    codeGroupBox->setChecked(false);
    QFormLayout* codeFormLayout = new QFormLayout;
    codeGroupBox->setLayout(codeFormLayout);
    connect(codeGroupBox, SIGNAL(clicked()), this, SLOT(validate()));

    QRegularExpression regex("^[a-zA-Z0-9_-]*$");
    QValidator* alphaNumericUnderscoresValidator = new QRegularExpressionValidator(regex, this);

    codeLineEdit = new QLineEdit;
    codeLineEdit->setPlaceholderText("Product Code");
    codeLineEdit->setValidator(alphaNumericUnderscoresValidator);
    connect(codeLineEdit, SIGNAL(textChanged(const QString&)), this, SLOT(handleLineEditChanged(const QString&)));

    codeFormLayout->addRow("(also partial)", codeLineEdit);
    vbox->addWidget(codeGroupBox);

    priceRangeGroupBox = new QGroupBox("Price range");
    priceRangeGroupBox->setCheckable(true);
    priceRangeGroupBox->setChecked(false);
    connect(priceRangeGroupBox, SIGNAL(clicked()), this, SLOT(validate()));

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

    connect(minPriceLineEdit, SIGNAL(textChanged(const QString&)), this, SLOT(handleLineEditChanged(const QString&)));
    connect(maxPriceLineEdit, SIGNAL(textChanged(const QString&)), this, SLOT(handleLineEditChanged(const QString&)));

    priceRangeLayout->addWidget(minPriceLineEdit);
    priceRangeLayout->addWidget(new QLabel("$ to"));
    priceRangeLayout->addWidget(maxPriceLineEdit);
    priceRangeLayout->addWidget(new QLabel("$"));
    priceRangeLayout->setAlignment(Qt::AlignCenter);
    vbox->addWidget(priceRangeGroupBox);

    sortGroupBox = new QGroupBox("Sorting");
    sortGroupBox->setCheckable(true);
    sortGroupBox->setChecked(false);
    connect(sortGroupBox, SIGNAL(clicked()), this, SLOT(validate()));

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

    QDialogButtonBox* buttonBox = new QDialogButtonBox();
    searchButton = new QPushButton(tr("&Search"));
    searchButton->setIcon(QIcon(":/assets/icons/search.png"));
    searchButton->setDisabled(true);
    buttonBox->addButton(searchButton, QDialogButtonBox::ButtonRole::AcceptRole);
    buttonBox->addButton(QDialogButtonBox::Cancel);
    vbox->addWidget(buttonBox);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(validate()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

void Views::SearchDialog::handleMinPriceTextChanged(const QString& price) {
    if (price == "") {
        maxPriceLineEdit->setDisabled(true);
    } else {
        maxPriceLineEdit->setEnabled(true);
        maxValidator->setRange(price.toDouble(), INT_MAX, 2);
    }
}

void Views::SearchDialog::validate() {
    // check if at least a product type is checked
    bool atLeastOneChecked = false;
    for (auto p = productTypeCheckboxes.begin(); p != productTypeCheckboxes.end(); p++) {
        if ((*p)->isChecked()) {
            atLeastOneChecked = true;
            break;
        }
    }

    bool validProductType = productTypeGroupBox->isChecked() && atLeastOneChecked;

    // check if the code contains at least a letter
    bool validCode = codeGroupBox->isChecked() && codeLineEdit->text().size() > 0;

    // check if the price range was inserted and is acceptable
    bool validPrice = priceRangeGroupBox->isChecked() &&
                      minPriceLineEdit->text().size() > 0 &&
                      minPriceLineEdit->hasAcceptableInput() &&
                      maxPriceLineEdit->text().size() > 0 &&
                      maxPriceLineEdit->hasAcceptableInput();

    searchButton->setEnabled(
            validProductType ||
            validCode ||
            validPrice ||
            sortGroupBox->isChecked()
    );
}

void Views::SearchDialog::handleLineEditChanged(const QString&) {
    validate();
}
