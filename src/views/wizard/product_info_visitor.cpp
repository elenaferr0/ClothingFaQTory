

#include <QLabel>
#include "product_info_visitor.h"
#include "../../services/repositories/jeans_repository.h"

using Services::JeansRepository;

ProductInfoVisitor::ProductInfoVisitor() : layout(new QGridLayout){}

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

QGridLayout* ProductInfoVisitor::getLayout() const {
    return layout;
}

void ProductInfoVisitor::buildAccessoryLayoutBase() {

}

void ProductInfoVisitor::buildClothingItemLayoutBase() {

}

