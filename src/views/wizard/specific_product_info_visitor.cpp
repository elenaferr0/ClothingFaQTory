

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

SpecificProductInfoVisitor::SpecificProductInfoVisitor(ProductWizardView::Mode mode)
        : layout(new QFormLayout), fieldsToRegister(QMap<QString, QWidget*>()),
          fillFields(mode == ProductWizardView::Edit) {}

void SpecificProductInfoVisitor::visitBracelet(Bracelet& bracelet) {
    buildAccessory(bracelet.getCategory());
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

    if (fillFields) {
        pearlNumberSpinBox->setValue(bracelet.getPearlNumber());
        pearlDiameterLineEdit->setText(QString::number(bracelet.getPearlDiameter()));
    }
}

void SpecificProductInfoVisitor::visitBackPack(BackPack& backPack) {
    buildAccessory(backPack.getCategory());
    QLineEdit* capacityLineEdit = new QLineEdit;
    fieldsToRegister.insert("capacity", capacityLineEdit);

    QDoubleValidator* validator = new QDoubleValidator(capacityLineEdit);
    validator->setNotation(QDoubleValidator::StandardNotation);
    validator->setRange(0, 999, 3);
    capacityLineEdit->setPlaceholderText("000.000");
    capacityLineEdit->setValidator(validator);
    layout->addRow("Capacity (in liters)", capacityLineEdit);

    if (fillFields) {
        capacityLineEdit->setText(QString::number(backPack.getCapacity()));
    }
}

void SpecificProductInfoVisitor::visitHat(Hat& hat) {
    buildAccessory(hat.getCategory());

    QButtonGroup* hatButtonGroup = new QButtonGroup;
    hatButtonGroup->setExclusive(true);

    QSize size(FORM_ICON_SIZE, FORM_ICON_SIZE);
    QRadioButton* genericHatRadio = new QRadioButton("Generic hat");
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

    if (fillFields && hat.isBaseballCap()) {
        baseballCapRadio->setChecked(true);
    } else {
        genericHatRadio->setChecked(true);
    }
}

void SpecificProductInfoVisitor::visitJeans(Jeans& jeans) {
    buildClothingItem(jeans.getGender(), jeans.areShorts());
    buildJeans(jeans.areShorts());
}

void SpecificProductInfoVisitor::visitVest(Vest& vest) {
    buildClothingItem(vest.getGender(), vest.hasSustainableMaterials());
    buildVest(vest.getHasButtons());
}

void SpecificProductInfoVisitor::visitOveralls(Overalls& overalls) {
    buildClothingItem(overalls.getGender(), overalls.hasSustainableMaterials());
    buildJeans(overalls.areShorts());
    buildVest(overalls.getHasButtons());
}

void SpecificProductInfoVisitor::buildJeans(bool areShorts) {
    QCheckBox* shortsCheckBox = new QCheckBox();
    shortsCheckBox->setCheckState(Qt::CheckState::Unchecked);
    fieldsToRegister.insert("shorts", shortsCheckBox);
    layout->addRow("Are shorts (knee height)", shortsCheckBox);

    if (fillFields) {
        shortsCheckBox->setCheckState(areShorts ? Qt::Checked : Qt::Unchecked);
    }
}

void SpecificProductInfoVisitor::buildVest(bool hasButtons) {
    QCheckBox* hasButtonsCheckBox = new QCheckBox();
    hasButtonsCheckBox->setCheckState(Qt::CheckState::Unchecked);
    hasButtonsCheckBox->setIcon(QIcon(":/assets/icons/buttons.png"));
    hasButtonsCheckBox->setIconSize(QSize(FORM_ICON_SIZE, FORM_ICON_SIZE));
    fieldsToRegister.insert("hasButtons", hasButtonsCheckBox);
    layout->addRow("Has buttons", hasButtonsCheckBox);

    if (fillFields) {
        hasButtonsCheckBox->setCheckState(hasButtons ? Qt::Checked : Qt::Unchecked);
    }
}

void SpecificProductInfoVisitor::buildAccessory(Accessory::Category category) {
    QComboBox* categoryComboBox = new QComboBox;
    categoryComboBox->addItem(QString::fromStdString(Accessory::getCategoryAsString(Accessory::GENERAL)));
    categoryComboBox->addItem(QString::fromStdString(Accessory::getCategoryAsString(Accessory::BAGS)));
    categoryComboBox->addItem(QString::fromStdString(Accessory::getCategoryAsString(Accessory::JEWELRY)));
    categoryComboBox->addItem(QString::fromStdString(Accessory::getCategoryAsString(Accessory::HATS)));
    fieldsToRegister.insert("category", categoryComboBox);
    layout->addRow("Category", categoryComboBox);

    if (fillFields) {
        categoryComboBox->setCurrentIndex(category);
    }
}

void SpecificProductInfoVisitor::buildClothingItem(ClothingItem::Gender gender, bool sustainableMaterials) {
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

    if (fillFields) {
        genderComboBox->setCurrentIndex(gender);
        sustainableMaterialsCheckBox->setCheckState(sustainableMaterials ? Qt::Checked : Qt::Unchecked);
    }
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

void SpecificProductInfoVisitor::visitMaterial(Material&) {}

void SpecificProductInfoVisitor::visitSize(Size&) {}
