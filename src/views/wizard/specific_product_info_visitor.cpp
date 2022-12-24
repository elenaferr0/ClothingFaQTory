

#include <QLabel>
#include <QComboBox>
#include <QButtonGroup>
#include <QCheckBox>
#include <QLineEdit>
#include <QSpinBox>
#include <QRadioButton>
#include "specific_product_info_visitor.h"
#include "../../services/repositories/jeans_repository.h"

using Services::JeansRepository;
using Models::Accessory;
using Models::ClothingItem;

SpecificProductInfoVisitor::SpecificProductInfoVisitor()
        : layout(new QFormLayout), fieldsToRegister(QMap<QString, QWidget*>()) {}

void SpecificProductInfoVisitor::visitBracelet(Bracelet&) {
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

void SpecificProductInfoVisitor::visitBackPack(BackPack&) {
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

void SpecificProductInfoVisitor::visitHat(Hat&) {
    buildAccessory();
    /*QCheckBox* isBaseballHatCheckBox = new QCheckBox();
    isBaseballHatCheckBox->setCheckState(Qt::CheckState::Unchecked);
    fieldsToRegister.insert("baseballHat", isBaseballHatCheckBox);
    layout->addRow("Is baseball hat", isBaseballHatCheckBox);*/
    QButtonGroup* hatButtonGroup = new QButtonGroup;
    hatButtonGroup->setExclusive(true);

    QSize size(FORM_ICON_SIZE, FORM_ICON_SIZE);
    QRadioButton* genericHatRadio = new QRadioButton("Generic hat");
    genericHatRadio->setChecked(true);
    genericHatRadio->setIcon(QIcon(":/assets/icons/hat.png"));
    genericHatRadio->setIconSize(size);
    hatButtonGroup->addButton(genericHatRadio);
    // not needed to register the genericHatRadio since there are only 2 options
    // therefore one is deducible from the other

    QRadioButton* baseballCapRadio = new QRadioButton("Baseball cap");
    baseballCapRadio->setIcon(QIcon(":/assets/icons/cap.png"));
    baseballCapRadio->setIconSize(size);
    hatButtonGroup->addButton(baseballCapRadio);
    fieldsToRegister.insert("baseballCap", baseballCapRadio);

    layout->addRow(new QLabel("Choose the type of hat:"));
    layout->addRow(genericHatRadio);
    layout->addRow(baseballCapRadio);

}

void SpecificProductInfoVisitor::visitJeans(Jeans&) {
    buildClothingItem();
    buildJeans();
}

void SpecificProductInfoVisitor::visitVest(Vest&) {
    buildClothingItem();
    buildVest();
}

void SpecificProductInfoVisitor::visitOveralls(Overalls&) {
    buildClothingItem();
    buildJeans();
    buildVest();
}

void SpecificProductInfoVisitor::buildJeans() {
    QCheckBox* shortsCheckBox = new QCheckBox();
    shortsCheckBox->setCheckState(Qt::CheckState::Unchecked);
    fieldsToRegister.insert("shorts", shortsCheckBox);
    layout->addRow("Are shorts (knee height)", shortsCheckBox);
}

void SpecificProductInfoVisitor::buildVest() {
    QCheckBox* hasButtonsCheckBox = new QCheckBox();
    hasButtonsCheckBox->setCheckState(Qt::CheckState::Unchecked);
    hasButtonsCheckBox->setIcon(QIcon(":/assets/icons/buttons.png"));
    hasButtonsCheckBox->setIconSize(QSize(FORM_ICON_SIZE, FORM_ICON_SIZE));
    fieldsToRegister.insert("hasButtons", hasButtonsCheckBox);
    layout->addRow("Has buttons", hasButtonsCheckBox);
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
    sustainableMaterialsCheckBox->setIcon(QIcon(":/assets/icons/sustainable.png"));
    sustainableMaterialsCheckBox->setIconSize(QSize(30, 30));
    fieldsToRegister.insert("sustainableMaterials", sustainableMaterialsCheckBox);
    layout->addRow("Is made of sustainable materials", sustainableMaterialsCheckBox);
}

QFormLayout* SpecificProductInfoVisitor::getLayout() const {
    return layout;
}

const QMap<QString, QWidget*>& SpecificProductInfoVisitor::getFieldsToRegister() const {
    return fieldsToRegister;
}

void SpecificProductInfoVisitor::clean() {
    while (layout->count() > 0) {
        QLayoutItem* item = layout->takeAt(0);
        QWidget* widget = item->widget();
        layout->removeWidget(widget);
        delete widget;
    }
    fieldsToRegister.clear();
}
