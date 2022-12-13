

#include <QLabel>
#include "product_info_visitor.h"
#include "../../services/repositories/jeans_repository.h"

using Services::JeansRepository;

void ProductInfoVisitor::visitBracelet(Bracelet& bracelet) {

}

void ProductInfoVisitor::visitBackPack(BackPack& pack) {

}

void ProductInfoVisitor::visitHat(Hat& hat) {

}

void ProductInfoVisitor::visitJeans(Jeans& jeans) {
    QLabel* title = new QLabel("Jeans");
    layout->addWidget(title);

    JeansRepository* jeansRepository = JeansRepository::getInstance();
    Either<Error, list<Jeans>> entitiesOrError = jeansRepository->findAll();

    QWidget* widget = entitiesOrError.fold<QWidget*>(
            [entitiesOrError]() -> QLabel* {
                return new QLabel(QString::fromStdString(entitiesOrError.forceLeft().getMessage()));
            },
            [entitiesOrError]() -> QWidget* {
                const list<Jeans>& entities = entitiesOrError.forceRight();
                auto* label = new QLabel();
                for (auto it = entities.begin(); it != entities.end(); it++) {
                    label->setText(label->text() + QString::fromStdString((*it).getDescription()));
                }
                return label;
            }
    );
    layout->addWidget(widget);

}

void ProductInfoVisitor::visitVest(Vest& vest) {

}

void ProductInfoVisitor::visitOveralls(Overalls& overalls) {

}

QVBoxLayout* ProductInfoVisitor::getLayout() const {
    return layout;
}
