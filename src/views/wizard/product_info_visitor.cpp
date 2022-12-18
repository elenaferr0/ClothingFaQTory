

#include <QLabel>
#include <QGroupBox>
#include <QComboBox>
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

}

void ProductInfoVisitor::visitOveralls(Overalls& overalls) {

}

QFormLayout* ProductInfoVisitor::getLayout() const {
    return layout;
}

void ProductInfoVisitor::buildAccessoryLayoutBase() {
}

void ProductInfoVisitor::buildClothingItemLayoutBase() {

}

void ProductInfoVisitor::buildProductLayoutBase() {

}

