

#include <QLabel>
#include <QComboBox>
#include <QCheckBox>
#include "specific_product_info_visitor.h"
#include "../../services/repositories/jeans_repository.h"

using Services::JeansRepository;
using Models::Accessory;
using Models::ClothingItem;

SpecificProductInfoVisitor::SpecificProductInfoVisitor()
        : layout(new QFormLayout), fieldsToRegister(QMap<QString, QWidget*>()) {}

void SpecificProductInfoVisitor::visitBracelet(Bracelet& bracelet) {
    // pearl nr
    // pearl diameter
}

void SpecificProductInfoVisitor::visitBackPack(BackPack& pack) {
    // capacity
}

void SpecificProductInfoVisitor::visitHat(Hat& hat) {
    // is baseball hat
    QCheckBox* isBaseballHatCheckBox = new QCheckBox();
    isBaseballHatCheckBox->setCheckState(Qt::CheckState::Unchecked);
    fieldsToRegister.insert("baseballHat", isBaseballHatCheckBox);
    layout->addRow("Is baseball hat", isBaseballHatCheckBox);
}

void SpecificProductInfoVisitor::visitJeans(Jeans& jeans) {
    // shorts
    QCheckBox* shortsCheckBox = new QCheckBox();
    shortsCheckBox->setCheckState(Qt::CheckState::Unchecked);
    fieldsToRegister.insert("shorts", shortsCheckBox);
    layout->addRow("Are shorts", shortsCheckBox);
}

void SpecificProductInfoVisitor::visitVest(Vest& vest) {
    // has buttons
    QCheckBox* hasButtonsCheckBox = new QCheckBox();
    hasButtonsCheckBox->setCheckState(Qt::CheckState::Unchecked);
    fieldsToRegister.insert("hasButtons", hasButtonsCheckBox);
    layout->addRow("Has Buttons", hasButtonsCheckBox);
}

void SpecificProductInfoVisitor::visitOveralls(Overalls& overalls) {
    visitVest(overalls);
    visitJeans(overalls);
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
    QCheckBox* sustainableMaterialsCheckBox = new QCheckBox;
    sustainableMaterialsCheckBox->setCheckState(Qt::Unchecked);
    fieldsToRegister.insert("sustainableMaterials", sustainableMaterialsCheckBox);
    layout->addRow("Made of sustainable materials", sustainableMaterialsCheckBox);

    QComboBox* genderComboBox = new QComboBox;
    genderComboBox->addItem(QString::fromStdString(ClothingItem::getGenderAsString(ClothingItem::MEN)));
    genderComboBox->addItem(QString::fromStdString(ClothingItem::getGenderAsString(ClothingItem::WOMEN)));
    genderComboBox->addItem(QString::fromStdString(ClothingItem::getGenderAsString(ClothingItem::UNISEX)));
    fieldsToRegister.insert("gender", genderComboBox);
    layout->addRow("Gender", genderComboBox);
}

QFormLayout* SpecificProductInfoVisitor::getLayout() const {
    return layout;
}

const QMap<QString, QWidget*>& SpecificProductInfoVisitor::getFieldsToRegister() const {
    return fieldsToRegister;
}
