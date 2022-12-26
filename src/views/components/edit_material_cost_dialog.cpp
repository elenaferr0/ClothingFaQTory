

#include <QLineEdit>
#include <QDoubleValidator>
#include <QFormLayout>
#include <QLabel>
#include "edit_material_cost_dialog.h"
#include <limits>

EditMaterialCostDialog::EditMaterialCostDialog(Material* material, QWidget* parent) : QDialog(parent) {
    setWindowTitle("Edit " + QString::fromStdString(material->getNameAsString()).toLower() + " price");

    QFormLayout* layout = new QFormLayout;

    QLineEdit* priceLineEdit = new QLineEdit;
    priceLineEdit->setText(QString::number(material->getCostPerUnit()));
    priceLineEdit->setPlaceholderText("0000.00");

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
    hbox->addWidget(new QLabel("$/" +
                               QString::fromStdString(material->getUnitOfMeasureAsString())));

    layout->addRow("New price", hbox);
    setLayout(layout);
    resize(300, 100);
}
