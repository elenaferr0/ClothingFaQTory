#include <QVBoxLayout>
#include <QHeaderView>
#include "clothing_items_tab_page.h"

unsigned int ClothingItemsTabPage::COLUMN_COUNT = 5;

ClothingItemsTabPage::ClothingItemsTabPage(QWidget* parent)
        : QWidget(parent) {

    treeWidget = new QTreeWidget;
    treeWidget->setHeaderHidden(true);
    treeWidget->setAnimated(true);
    treeWidget->setIconSize(QSize(30, 30));

    updateTreeContent();

    for (int i = 0; i < COLUMN_COUNT; ++i) {
        treeWidget->setColumnWidth(i, 180);
    }

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignTop);
    layout->addWidget(treeWidget);
}

void ClothingItemsTabPage::updateTreeContent() {
    treeWidget->clear();
    treeWidget->setColumnCount(COLUMN_COUNT);
    for (int i = Jeans; i != Hat + 1; i++) {
        auto topLevelItem = static_cast<TopLevelItem>(i);
        updateTopLevelItem(topLevelItem);
    }
}

void ClothingItemsTabPage::updateTopLevelItem(TopLevelItem topLevelItem) {
    switch (topLevelItem) {
        case Jeans:
            update(Jeans, "Jeans", JeansRepository::getInstance(), "jeans.png");
            return;
        case Vest:
            update(Vest, "Vests", VestRepository::getInstance(), "vest.png");
            return;
        case Overalls:
            update(Overalls, "Overalls", OverallsRepository::getInstance(), "overalls.png");
            return;
        case Bracelet:
            update(Bracelet, "Bracelets", BraceletRepository::getInstance(), "bracelet.png");
            return;
        case BackPack:
            update(BackPack, "BackPacks", BackPackRepository::getInstance(), "backpack.png");
            return;
        case Hat:
            update(Hat, "Hats", HatRepository::getInstance(), "hat.png");
            return;
    }
}

template<class T>
void ClothingItemsTabPage::update(TopLevelItem topLevelItem, QString title, ReadOnlyRepository<T>* repository,
                                  QString iconFileName) {
    bool wasCreated = false;
    QTreeWidgetItem* topLevelItemWidget = treeWidget->topLevelItem(topLevelItem);

    if (topLevelItemWidget == nullptr) {
        topLevelItemWidget = new QTreeWidgetItem(QStringList() << title);
        wasCreated = true;
    }

    // remove all existing children
    for (int i = 0; i < topLevelItemWidget->childCount(); ++i) {
        topLevelItemWidget->removeChild(topLevelItemWidget->child(i));
    }

    Either<Error, list<T>> entitiesOrError = repository->findAll();
    if (entitiesOrError.isRight()) {
        list<T> entities = entitiesOrError.forceRight();

        if (entities.size() > 0) {
            QTreeWidgetItem* headers = getHeaders();
            topLevelItemWidget->addChild(headers);
        }

        for (auto it = entities.begin(); it != entities.end(); it++) {
            QStringList columns;
            columns << QString::fromStdString((*it).getCode())
                    << QString::fromStdString((*it).getColor())
                    << QString::fromStdString((*it).getDescription())
                    << QString::fromStdString((*it).getSize().getNameAsString())
                    << QString::number((*it).computePrice(), 'f', 2) + "$";

            QTreeWidgetItem* child = new QTreeWidgetItem(columns);
            topLevelItemWidget->addChild(child);
        }

        QIcon icon(":/assets/icons/" + iconFileName);
        topLevelItemWidget->setIcon(0, icon);
        topLevelItemWidget->setFlags(topLevelItemWidget->flags() & ~Qt::ItemIsSelectable);

        if (wasCreated) {
            treeWidget->addTopLevelItem(topLevelItemWidget);
        }
    } else {
        qCritical() << QString::fromStdString(entitiesOrError.forceLeft().getMessage());
    }
}

QTreeWidgetItem* ClothingItemsTabPage::getHeaders() {
    QTreeWidgetItem* headers = new QTreeWidgetItem(QStringList() << "Code"
                                                                 << "Color"
                                                                 << "Description"
                                                                 << "Size"
                                                                 << "Calculated price");
    QFont font = QFont();
    font.setBold(true);

    for (int i = 0; i < COLUMN_COUNT; ++i) {
        headers->setFont(i, font);
    }


    return headers;
}
