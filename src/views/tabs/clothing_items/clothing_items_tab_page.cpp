#include <QVBoxLayout>
#include <QHeaderView>
#include "clothing_items_tab_page.h"

unsigned int ClothingItemsTabPage::COLUMN_COUNT = 5;

ClothingItemsTabPage::ClothingItemsTabPage(QWidget* parent)
        : QWidget(parent),
          jeansRepository(JeansRepository::getInstance()),
          vestRepository(VestRepository::getInstance()),
          overallsRepository(OverallsRepository::getInstance()) {

    treeWidget = new QTreeWidget;
    treeWidget->setHeaderHidden(true);
    treeWidget->setAnimated(true);
    treeWidget->setIconSize(QSize(30, 30));

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignTop);
    layout->addWidget(treeWidget);
    updateTableContent();

}

void ClothingItemsTabPage::updateTableContent() {
    treeWidget->clear();
    treeWidget->setColumnCount(COLUMN_COUNT);
    for (int i = Jeans; i != Hat; i++) {
        auto topLevelItem = static_cast<TopLevelItem>(i);
        updateOnly(topLevelItem);
    }
}

void ClothingItemsTabPage::updateOnly(TopLevelItem topLevelItem) {
    switch (topLevelItem) {
        case Jeans:
            updateJeans();
            return;
        case Vest:
        case Overalls:
        case Bracelet:
        case BackPack:
        case Hat:
            return;
    }
}

void ClothingItemsTabPage::updateJeans() {
    bool wasCreated = false;
    QTreeWidgetItem* jeansItem = treeWidget->topLevelItem(Jeans);

    if (jeansItem == nullptr) {
        jeansItem = new QTreeWidgetItem(QStringList() << "Jeans");
        wasCreated = true;
    }

    // remove all children
    for (int i = 0; i < jeansItem->childCount(); ++i) {
        jeansItem->removeChild(jeansItem->child(i));
    }

    Either<Error, list<Models::ClothingItems::Jeans>> jeansOrError = jeansRepository->findAll();
    if (jeansOrError.isRight()) {
        list<Models::ClothingItems::Jeans> jeans = jeansOrError.forceRight();

        QTreeWidgetItem* headers = getHeaders(Jeans);
        jeansItem->addChild(headers);

        for (auto it = jeans.begin(); it != jeans.end(); it++) {
            QStringList columns;
            columns << QString::fromStdString((*it).getCode())
                    << QString::fromStdString((*it).getColor())
                    << QString::fromStdString((*it).getDescription())
                    << QString::fromStdString((*it).getSize().getNameAsString())
                    << QString::number((*it).computePrice(), 'f', 2) + "$";

            QTreeWidgetItem* child = new QTreeWidgetItem(columns);
            jeansItem->addChild(child);
        }

        QIcon icon(":/assets/icons/jeans.png");
        jeansItem->setIcon(0, icon);
        if (wasCreated) {
            treeWidget->addTopLevelItem(jeansItem);
        }

    } else {
        qCritical() << QString::fromStdString(jeansOrError.forceLeft().getMessage());
    }
}

QTreeWidgetItem* ClothingItemsTabPage::getHeaders(TopLevelItem topLevelItem) {
    QTreeWidgetItem* headers = new QTreeWidgetItem(QStringList() << "Code"
                                                                 << "Color"
                                                                 << "Description"
                                                                 << "Size"
                                                                 << "Price");
    QFont font = QFont();
    font.setBold(true);

    for (int i = 0; i < COLUMN_COUNT; ++i) {
        headers->setFont(i, font);
        treeWidget->setColumnWidth(i, 200);
    }


    return headers;
}
