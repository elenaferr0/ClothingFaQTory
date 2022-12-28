

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
#include <QMessageBox>
#include "search_dialog.h"

using Views::SearchDialog;
using std::for_each;

const int SearchDialog::MAX_PRICE = 99999999;
QVector<QString> SearchDialog::sortableFields = {"Code", "Available quantity", "Sold quantity"};

SearchDialog::SearchDialog(QWidget* parent) : QDialog(parent) {
    setWindowTitle("Search for a Product");
    resize(500, 600);
    QVBoxLayout* vbox = new QVBoxLayout(this);

    productTypeGroupBox = new QGroupBox("Product Type");
    productTypeGroupBox->setCheckable(true);
    productTypeGroupBox->setChecked(false);
    connect(productTypeGroupBox, SIGNAL(clicked()), this, SLOT(validate()));

    QFormLayout* productTypeFormLayout = new QFormLayout;
    productTypeError = new QLabel("Check at least one product type");
    productTypeError->setVisible(false);
    productTypeError->setObjectName("errorLabel");
    productTypeFormLayout->addWidget(productTypeError);
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
    codeError = new QLabel("Code should not be empty");
    codeError->setVisible(false);
    codeError->setObjectName("errorLabel");
    codeFormLayout->addWidget(codeError);
    connect(codeGroupBox, SIGNAL(clicked()), this, SLOT(validate()));

    QRegularExpression regex("^[a-zA-Z0-9_-]*$");
    QValidator* alphaNumericUnderscoresValidator = new QRegularExpressionValidator(regex, this);

    codeLineEdit = new QLineEdit;
    codeLineEdit->setPlaceholderText("Product Code");
    codeLineEdit->setValidator(alphaNumericUnderscoresValidator);
    codeGroupBox->setLayout(codeFormLayout);
    connect(codeLineEdit, SIGNAL(textChanged(const QString&)), this, SLOT(handleLineEditChanged(const QString&)));

    codeFormLayout->addRow("(also partial)", codeLineEdit);
    codeFormLayout->setAlignment(Qt::AlignLeft);
    vbox->addWidget(codeGroupBox);

    priceRangeGroupBox = new QGroupBox("Price range");
    priceRangeGroupBox->setCheckable(true);
    priceRangeGroupBox->setChecked(false);
    connect(priceRangeGroupBox, SIGNAL(clicked()), this, SLOT(validate()));

    QVBoxLayout* priceRangeLayout = new QVBoxLayout;
    priceError = new QLabel("Both values are mandatory and min price must be smaller than max price");
    priceError->setVisible(false);
    priceError->setObjectName("errorLabel");
    priceRangeLayout->addWidget(priceError);
    priceRangeGroupBox->setLayout(priceRangeLayout);

    minPriceLineEdit = new QLineEdit;
    minPriceLineEdit->setPlaceholderText("Min");

    maxPriceLineEdit = new QLineEdit;
    maxPriceLineEdit->setPlaceholderText("Max");
    maxPriceLineEdit->setDisabled(true);

    QDoubleValidator* minValidator = new QDoubleValidator;
    minValidator->setNotation(QDoubleValidator::StandardNotation);
    minValidator->setRange(0, MAX_PRICE, 2);
    minPriceLineEdit->setValidator(minValidator);
    connect(minPriceLineEdit, SIGNAL(textChanged(const QString &)), this,
            SLOT(handleMinPriceTextChanged(const QString &)));

    maxValidator = new QDoubleValidator;
    maxValidator->setNotation(QDoubleValidator::StandardNotation);
    maxPriceLineEdit->setValidator(maxValidator);

    connect(minPriceLineEdit, SIGNAL(textChanged(const QString&)), this, SLOT(handleLineEditChanged(const QString&)));
    connect(maxPriceLineEdit, SIGNAL(textChanged(const QString&)), this, SLOT(handleLineEditChanged(const QString&)));

    QHBoxLayout* priceInputLayout = new QHBoxLayout;
    priceInputLayout->addWidget(minPriceLineEdit);
    priceInputLayout->addWidget(new QLabel("$ to"));
    priceInputLayout->addWidget(maxPriceLineEdit);
    priceInputLayout->addWidget(new QLabel("$"));
    priceInputLayout->setAlignment(Qt::AlignCenter);
    priceRangeLayout->addLayout(priceInputLayout);
    vbox->addWidget(priceRangeGroupBox);

    sortGroupBox = new QGroupBox("Sorting");
    sortGroupBox->setCheckable(true);
    sortGroupBox->setChecked(false);
    connect(sortGroupBox, SIGNAL(clicked()), this, SLOT(validate()));

    QHBoxLayout* fieldSortLayout = new QHBoxLayout;
    fieldSortLayout->setAlignment(Qt::AlignLeft);
    sortGroupBox->setLayout(fieldSortLayout);

    fieldSortLayout->addWidget(new QLabel("Field"));

    sortFieldComboBox = new QComboBox;
    for (int i = 0; i < sortableFields.size(); ++i) {
        sortFieldComboBox->addItem(sortableFields.value(i));
    }

    fieldSortLayout->addWidget(sortFieldComboBox);

    fieldSortLayout->addWidget(new QLabel("Order"));

    orderComboBox = new QComboBox;
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

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(completed()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

void Views::SearchDialog::handleMinPriceTextChanged(const QString& price) {
    if (price == "") {
        maxPriceLineEdit->setDisabled(true);
    } else {
        maxPriceLineEdit->setEnabled(true);
        maxValidator->setRange(price.toDouble(), MAX_PRICE, 2);
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
    productTypeError->setVisible(!atLeastOneChecked && productTypeGroupBox->isChecked());

    // check if the code contains at least a letter
    bool validCode = codeGroupBox->isChecked() && codeLineEdit->text().size() > 0;
    codeError->setVisible(codeLineEdit->text().size() == 0 && codeGroupBox->isChecked());

    // check if the price range was inserted and is acceptable
    bool validPrice = priceRangeGroupBox->isChecked() &&
                      minPriceLineEdit->text().size() > 0 &&
                      minPriceLineEdit->hasAcceptableInput() &&
                      maxPriceLineEdit->text().size() > 0 &&
                      maxPriceLineEdit->hasAcceptableInput();
    // set visible only if is checked and not valid
    priceError->setVisible(!validPrice && priceRangeGroupBox->isChecked());

    searchButton->setEnabled(validProductType ||
                             validCode ||
                             validPrice ||
                             sortGroupBox->isChecked());
}

void Views::SearchDialog::handleLineEditChanged(const QString&) {
    validate();
}

void Views::SearchDialog::completed() {
    LinkedList<QString> productTypes;
    if (productTypeGroupBox->isChecked()) {
        for_each(
                productTypeCheckboxes.begin(),
                productTypeCheckboxes.end(),
                [&](QCheckBox* checkBox) {
                    if (checkBox->isChecked()) {
                        productTypes.pushBack(checkBox->text());
                    }
                }
        );
    }

    QString code;
    if (codeGroupBox->isChecked()) {
        code = codeLineEdit->text();
    }

    QPair<double, double> priceRange;
    if (priceRangeGroupBox->isChecked()) {
        priceRange = QPair(minPriceLineEdit->text().toDouble(), maxPriceLineEdit->text().toDouble());
    } else {
        priceRange = QPair(0, MAX_PRICE);
    }

    if (sortGroupBox->isChecked()) {
        QPair<QString, QueryBuilder::Order> sorting;
        sorting = QPair(sortFieldComboBox->currentIndex(),
                        static_cast<QueryBuilder::Order>(orderComboBox->currentIndex()));
        emit accept();
        emit startSearch(Filters(productTypes, code, priceRange, sorting));
        return;
    }

    emit accept();
    emit startSearch(Filters(productTypes, code, priceRange));
}
