

#include <QLabel>
#include <QGroupBox>
#include <QComboBox>
#include <QCheckBox>
#include "product_info_visitor.h"
#include "../../services/repositories/jeans_repository.h"
#include "select_color_button.h"

using Services::JeansRepository;

ProductInfoVisitor::ProductInfoVisitor() : layout(new QFormLayout) {}

void ProductInfoVisitor::visitBracelet(Bracelet& bracelet) {

}

void ProductInfoVisitor::visitBackPack(BackPack& pack) {

}

void ProductInfoVisitor::visitHat(Hat& hat) {

}

void ProductInfoVisitor::visitJeans(Jeans& jeans) {

}

void ProductInfoVisitor::visitVest(Vest& vest) {
    QCheckBox* checkBox = new QCheckBox();
    checkBox->setCheckState(Qt::CheckState::Unchecked);
    layout->addRow("Has Buttons", checkBox);
}

void ProductInfoVisitor::visitOveralls(Overalls& overalls) {

}

QFormLayout* ProductInfoVisitor::getLayout() const {
    return layout;
}