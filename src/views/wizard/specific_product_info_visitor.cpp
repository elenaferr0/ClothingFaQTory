

#include <QLabel>
#include <QComboBox>
#include <QCheckBox>
#include <QLineEdit>
#include <QSpinBox>
#include "specific_product_info_visitor.h"
#include "../../services/repositories/jeans_repository.h"

using Services::JeansRepository;
using Models::Accessory;
using Models::ClothingItem;

SpecificProductInfoVisitor::SpecificProductInfoVisitor()
        : layout(new QFormLayout), fieldsToRegister(QMap<QString, QWidget*>()) {}

void SpecificProductInfoVisitor::visitBracelet(Bracelet& bracelet) {
    buildAccessory();
    QSpinBox* pearlNumberSpinBox = new QSpinBox;
    pearlNumberSpinBox->setRange(0, 100);
    pearlNumberSpinBox->setSingleStep(1);
    fieldsToRegister.insert("pearlNumber", pearlNumberSpinBox);
    layout->addRow("Pearl number", pearlNumberSpinBox);

    QLineEdit* pearlDiameterLineEdit = new QLineEdit;
    fieldsToRegister.insert("pearlDiameter", pearlDiameterLineEdit);
    pearlDiameterLineEdit->setPlaceholderText("00.0000");

    QDoubleValidator* validator = new QDoubleValidator(pearlDiameterLineEdit);
    validator->setNotation(QDoubleValidator::StandardNotation);
    validator->setDecimals(4);
    validator->setBottom(2);
    pearlDiameterLineEdit->setValidator(validator);
    layout->addRow("Pearl diameter (in cm)", pearlDiameterLineEdit);
}

void SpecificProductInfoVisitor::visitBackPack(BackPack& pack) {
    buildAccessory();
    QLineEdit* capacityLineEdit = new QLineEdit;
    fieldsToRegister.insert("capacity", capacityLineEdit);

    QDoubleValidator* validator = new QDoubleValidator(capacityLineEdit);
    validator->setNotation(QDoubleValidator::StandardNotation);
    validator->setRange(0, 999, 3);
    capacityLineEdit->setPlaceholderText("000.000");
    capacityLineEdit->setValidator(validator);
    layout->addRow("Capacity (in liters)", capacityLineEdit);
}

void SpecificProductInfoVisitor::visitHat(Hat& hat) {
    buildAccessory();
    QCheckBox* isBaseballHatCheckBox = new QCheckBox();
    isBaseballHatCheckBox->setCheckState(Qt::CheckState::Unchecked);
    fieldsToRegister.insert("baseballHat", isBaseballHatCheckBox);
    layout->addRow("Is baseball hat", isBaseballHatCheckBox);
}

void SpecificProductInfoVisitor::visitJeans(Jeans& jeans) {
    buildClothingItem();
    buildJeans();
}

void SpecificProductInfoVisitor::visitVest(Vest& vest) {
    buildClothingItem();
    buildVest();
}

void SpecificProductInfoVisitor::visitOveralls(Overalls& overalls) {
    buildClothingItem();
    buildJeans();
    buildVest();
}

void SpecificProductInfoVisitor::buildJeans() {
    QCheckBox* shortsCheckBox = new QCheckBox();
    shortsCheckBox->setCheckState(Qt::CheckState::Unchecked);
    fieldsToRegister.insert("shorts", shortsCheckBox);
    layout->addRow("Are shorts", shortsCheckBox);
}

void SpecificProductInfoVisitor::buildVest() {
    QCheckBox* hasButtonsCheckBox = new QCheckBox();
    hasButtonsCheckBox->setCheckState(Qt::CheckState::Unchecked);
    fieldsToRegister.insert("hasButtons", hasButtonsCheckBox);
    layout->addRow("Has Buttons", hasButtonsCheckBox);
}

void SpecificProductInfoVisitor::buildAccessory() {
    QComboBox* categoryComboBox = new QComboBox;
    categoryComboBox->addItem(QString::fromStdString(Accessory::getCategoryAsString(Accessory::GENERAL)));
    categoryComboBox->addItem(QString::fromStdString(Accessory::getCategoryAsString(Accessory::BAGS)));
    categoryComboBox->addItem(QString::fromStdString(Accessory::getCategoryAsString(Accessory::HATS)));
    categoryComboBox->addItem(QString::fromStdString(Accessory::getCategoryAsString(Accessory::JEWELRY)));
    fieldsToRegister.insert("category", categoryComboBox);
    layout->addRow("Category", categoryComboBox);
}

void SpecificProductInfoVisitor::buildClothingItem() {
    QComboBox* genderComboBox = new QComboBox;
    genderComboBox->addItem(QString::fromStdString(ClothingItem::getGenderAsString(ClothingItem::UNISEX)));
    genderComboBox->addItem(QString::fromStdString(ClothingItem::getGenderAsString(ClothingItem::MEN)));
    genderComboBox->addItem(QString::fromStdString(ClothingItem::getGenderAsString(ClothingItem::WOMEN)));
    fieldsToRegister.insert("gender", genderComboBox);
    layout->addRow("Gender", genderComboBox);

    QCheckBox* sustainableMaterialsCheckBox = new QCheckBox;
    sustainableMaterialsCheckBox->setCheckState(Qt::Unchecked);
    fieldsToRegister.insert("sustainableMaterials", sustainableMaterialsCheckBox);
    layout->addRow("Made of sustainable materials", sustainableMaterialsCheckBox);
}

QFormLayout* SpecificProductInfoVisitor::getLayout() const {
    return layout;
}

const QMap<QString, QWidget*>& SpecificProductInfoVisitor::getFieldsToRegister() const {
    return fieldsToRegister;
}
