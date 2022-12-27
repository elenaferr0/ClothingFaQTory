

#include <QLineEdit>
#include <QDoubleValidator>
#include <QFormLayout>
#include <QLabel>
#include <QDialogButtonBox>
#include "edit_material_cost_box.h"

EditMaterialCostMessageBox::EditMaterialCostMessageBox(Material* material, QWidget* parent)
        : QDialog(parent), material(material) {
    setWindowTitle("Edit " + QString::fromStdString(material->getNameAsString()).toLower() + " price");

    QFormLayout* layout = new QFormLayout(this);

    QLineEdit* priceLineEdit = new QLineEdit;
    priceLineEdit->setText(QString::number(material->getCostPerUnit()));
    priceLineEdit->setPlaceholderText("0000.00");
    connect(priceLineEdit, SIGNAL(textChanged(const QString &)), this, SLOT(handleTextChanged(const QString &)));

    QDoubleValidator* validator = new QDoubleValidator(priceLineEdit);
    validator->setNotation(QDoubleValidator::StandardNotation);
    validator->setRange(0, INT_MAX, 2);
    priceLineEdit->setValidator(validator);
    QLabel* oldPriceLabel = new QLabel("Old price: " + QString::number(material->getCostPerUnit()) + "$/" +
                                       QString::fromStdString(material->getUnitOfMeasureAsString()));
    oldPriceLabel->setAlignment(Qt::AlignLeft);
    layout->addWidget(oldPriceLabel);

    QHBoxLayout* hbox = new QHBoxLayout;
    hbox->addWidget(priceLineEdit);
    hbox->addWidget(new QLabel("$/" + QString::fromStdString(material->getUnitOfMeasureAsString())));
    layout->addRow("New price", hbox);

    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    layout->addWidget(buttonBox);

    resize(300, 100);
}

void EditMaterialCostMessageBox::handleTextChanged(const QString& cost) {
    material->setCostPerUnit(cost.toDouble());
}
