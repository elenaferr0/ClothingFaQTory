

#include <QLabel>
#include "info_dialog_visitor.h"
#include "components/color_icon.h"

Views::InfoDialogVisitor::InfoDialogVisitor() : layout(new QFormLayout) {}

void Views::InfoDialogVisitor::visitBracelet(Bracelet& bracelet) {
    visitAccessory(bracelet);
    layout->addRow("Pearl number", new QLabel(QString::number(bracelet.getPearlNumber())));
    layout->addRow("Pearl diameter", new QLabel(QString::number(bracelet.getPearlDiameter()) + " cm"));
}

void Views::InfoDialogVisitor::visitBackPack(BackPack& backPack) {
    visitAccessory(backPack);
    layout->addRow("Capacity", new QLabel(QString::number(backPack.getCapacity(), 'f', 2) + "L"));
}

void Views::InfoDialogVisitor::visitHat(Hat& hat) {
    visitAccessory(hat);
    QHBoxLayout* hatTypeLayout = new QHBoxLayout;
    hatTypeLayout->setAlignment(Qt::AlignLeft);
    QString type = hat.isBaseballCap() ? "Baseball cap" : "Generic hat";
    hatTypeLayout->addWidget(new QLabel(type));
    QLabel* icon = new QLabel();
    QString path = ":/assets/icons/";
    path += (hat.isBaseballCap() ? "cap.png" : "hat.png");
    icon->setPixmap(QPixmap(path).scaledToHeight(ICON_SIZE));
    hatTypeLayout->addWidget(icon);
    layout->addRow("Hat type", hatTypeLayout);
}

void Views::InfoDialogVisitor::visitJeans(Jeans& jeans) {
    visitClothingItem(jeans);
    buildJeans(jeans);
}

void Views::InfoDialogVisitor::visitVest(Vest& vest) {
    visitClothingItem(vest);
    buildVest(vest);
}

void Views::InfoDialogVisitor::visitOveralls(Overalls& overalls) {
    visitClothingItem(overalls);
    buildVest(overalls);
    buildJeans(overalls);
}

void Views::InfoDialogVisitor::buildJeans(Jeans& jeans) {
    QString length = jeans.areShorts() ? "Knee height" : "Full length";
    layout->addRow("Length", new QLabel(length));
}

void Views::InfoDialogVisitor::buildVest(Vest& vest) {
    if (vest.getHasButtons()) {
        QLabel* icon = new QLabel;
        icon->setPixmap(QPixmap(":/assets/icons/buttons.png").scaledToHeight(ICON_SIZE));
        layout->addRow("Has buttons", icon);
    }
}

void Views::InfoDialogVisitor::visitMaterial(Material&) {}

void Views::InfoDialogVisitor::visitSize(Size&) {}


void Views::InfoDialogVisitor::visitProduct(Product& product) {
    layout->addRow("Code", new QLabel(QString::fromStdString(product.getCode())));

    QHBoxLayout* colorLayout = new QHBoxLayout;
    colorLayout->setAlignment(Qt::AlignLeft);
    auto icon = new ColorIcon(product.getColor());

    QLabel* iconColorLabel = new QLabel;
    QPixmap pixmap = icon->getPixmap()->scaledToHeight(ICON_SIZE);
    iconColorLabel->setPixmap(pixmap);
    colorLayout->addWidget(iconColorLabel);
    colorLayout->addWidget(new QLabel(QString::fromStdString(product.getColor())));

    layout->addRow("Color", colorLayout);
    layout->addRow("Sold quantity", new QLabel(QString::number(product.getSoldQuantity())));
    layout->addRow("Available quantity", new QLabel(QString::number(product.getAvailableQuantity())));

    if (product.getDescription() != "") {
        layout->addRow("Description", new QLabel(QString::fromStdString(product.getDescription())));
    }
    layout->addRow("Size", new QLabel(QString::fromStdString(product.getSize().getNameAsString())));
    layout->addRow("Material", new QLabel(QString::fromStdString(product.getMaterial().getNameAsString())));
    layout->addRow("Calculated price", new QLabel(QString::number(product.computePrice(), 'f', 2) + "$"));
}

void Views::InfoDialogVisitor::visitAccessory(Accessory& accessory) {
    visitProduct(accessory);
    QString category = QString::fromStdString(Accessory::getCategoryAsString(accessory.getCategory()));
    layout->addRow("Category", new QLabel(category));
}

void Views::InfoDialogVisitor::visitClothingItem(ClothingItem& clothingItem) {
    visitProduct(clothingItem);
    if (clothingItem.hasSustainableMaterials()) {
        QLabel* sustainableMaterialsIcon = new QLabel;
        sustainableMaterialsIcon->setPixmap(QPixmap(":/assets/icons/sustainable.png").scaledToHeight(ICON_SIZE));
        layout->addRow("Is made of sustainable materials", sustainableMaterialsIcon);
    }
    QString gender = QString::fromStdString(ClothingItem::getGenderAsString(clothingItem.getGender()));
    layout->addRow("Gender", new QLabel(gender));
}

QFormLayout* Views::InfoDialogVisitor::getLayout() const {
    return layout;
}

