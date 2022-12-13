#include <QVBoxLayout>
#include <QHeaderView>
#include "clothing_items_tab_page.h"
#include "../product_info_visitor.h"

ClothingItemsTabPage::ClothingItemsTabPage(QWidget* parent)
        : QWidget(parent),
          jeansRepository(JeansRepository::getInstance()),
          vestRepository(VestRepository::getInstance()),
          overallsRepository(OverallsRepository::getInstance()) {

    QStringList labels;
    labels
            << QStringLiteral("Product Type")
            << QStringLiteral("Code")
            << QStringLiteral("Color")
            << QStringLiteral("Description")
            << QStringLiteral("Size")
            << QStringLiteral("Price");

    table = new QTableWidget(0, labels.size(), this);

    table->setHorizontalHeaderLabels(labels);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->verticalHeader()->setVisible(false);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionBehavior(QAbstractItemView::SelectItems);
    table->setSelectionMode(QAbstractItemView::SingleSelection);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignTop);

    layout->addWidget(table);
    updateTableContent();

}

void ClothingItemsTabPage::updateTableContent() {
    table->clearContents();
    table->setRowCount(0);

    Either<Error, list<Jeans>> jeansOrError = jeansRepository->findAll();

    if (jeansOrError.isRight()) {
        list<Jeans> jeans = jeansOrError.forceRight();
        for (auto it = jeans.begin(); it != jeans.end(); it++) {
            table->setRowCount(table->rowCount() + 1);

            int row = table->rowCount() - 1;
            int col = -1;

            QIcon icon(":/assets/icons/jeans.png");
            table->setItem(row, ++col, new QTableWidgetItem(icon, "Jeans", 0));
            table->setItem(row, ++col, new QTableWidgetItem(QString::fromStdString((*it).getCode())));
            table->setItem(row, ++col, new QTableWidgetItem(QString::fromStdString((*it).getColor()), 0));
            table->setItem(row, ++col, new QTableWidgetItem(QString::fromStdString((*it).getDescription()), 0));
            table->setItem(row, ++col,
                           new QTableWidgetItem(QString::fromStdString((*it).getSize().getNameAsString()), 0));
            table->setItem(row, ++col, new QTableWidgetItem(QString::number((*it).computePrice(), 'f', 2) + "$", 0));

        }
    }

    Either<Error, list<Vest>> vestsOrError = vestRepository->findAll();

    if (vestsOrError.isRight()) {
        list<Vest> vests = vestsOrError.forceRight();
        for (auto it = vests.begin(); it != vests.end(); it++) {
            table->setRowCount(table->rowCount() + 1);

            int row = table->rowCount() - 1;
            int col = -1;

            QIcon icon(":/assets/icons/vest.png");
            table->setItem(row, ++col, new QTableWidgetItem(icon, "Vest", 0));
            table->setItem(row, ++col, new QTableWidgetItem(QString::fromStdString((*it).getCode())));
            table->setItem(row, ++col, new QTableWidgetItem(QString::fromStdString((*it).getColor()), 0));
            table->setItem(row, ++col, new QTableWidgetItem(QString::fromStdString((*it).getDescription()), 0));
            table->setItem(row, ++col,
                           new QTableWidgetItem(QString::fromStdString((*it).getSize().getNameAsString()), 0));
            table->setItem(row, ++col, new QTableWidgetItem(QString::number((*it).computePrice(), 'f', 2) + "$", 0));

        }
    }
}
