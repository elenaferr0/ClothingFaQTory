#include <QVBoxLayout>
#include <QHeaderView>
#include <QToolButton>
#include <QPushButton>
#include "clothing_items_tab_page.h"
#include "../../mainwindow.h"
#include "../../wizard/create_product_wizard.h"

using Models::Product;

int ClothingItemsTabPage::COLUMN_COUNT = 5;

ClothingItemsTabPage::ClothingItemsTabPage(QWidget* parent)
        : QWidget(parent) {

    treeWidget = new QTreeWidget;
    treeWidget->setHeaderHidden(true);
    treeWidget->setAnimated(true);
    treeWidget->setIconSize(QSize(30, 30));
    treeWidget->setFocusPolicy(Qt::NoFocus);

    populateTree();
    for (int i = 0; i < COLUMN_COUNT; ++i) {
        treeWidget->setColumnWidth(i, 180);
    }

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignTop);

    toolBar = new QToolBar(this);
    toolBar->setMovable(false);

    QToolButton* createButton = new QToolButton;
    createButton->setIcon(QIcon(":/assets/icons/add.png"));
    createButton->setText("Create New");
    createButton->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextUnderIcon);
    connect(createButton, SIGNAL(clicked(bool)), this, SLOT(showWizard(bool)));
    toolBar->addWidget(createButton);

    QToolButton* searchButton = new QToolButton;
    searchButton->setIcon(QIcon(":/assets/icons/search.png"));
    searchButton->setText("Search");
    searchButton->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextUnderIcon);
//    connect(searchButton, SIGNAL(clicked(bool)), this, SLOT(showNewProduct::ProductTypeChooserWindow(bool)));
    toolBar->addWidget(searchButton);

    toolBar->setIconSize(QSize(15, 15));

    layout->addWidget(toolBar);
    layout->addWidget(treeWidget);

}

void ClothingItemsTabPage::populateTree() {
    treeWidget->clear();
    treeWidget->setColumnCount(COLUMN_COUNT);
    for (int i = Product::Jeans; i != Product::Hat + 1; i++) {
        auto topLevelItem = static_cast<Product::ProductType>(i);
        updateTopLevelItem(topLevelItem);
    }
}

void ClothingItemsTabPage::updateTopLevelItem(Product::ProductType topLevelItem) {
    switch (topLevelItem) {
        case Product::Jeans:
            update(Product::Jeans, Product::productTypeToString(Product::Jeans), JeansRepository::getInstance(), "jeans.png");
            return;
        case Product::Vest:
            update(Product::Vest, Product::productTypeToString(Product::Vest), VestRepository::getInstance(), "vest.png");
            return;
        case Product::Overalls:
            update(Product::Overalls, Product::productTypeToString(Product::Overalls), OverallsRepository::getInstance(), "overalls.png");
            return;
        case Product::Bracelet:
            update(Product::Bracelet, Product::productTypeToString(Product::Bracelet), BraceletRepository::getInstance(), "bracelet.png");
            return;
        case Product::BackPack:
            update(Product::BackPack, Product::productTypeToString(Product::BackPack), BackPackRepository::getInstance(), "backpack.png");
            return;
        case Product::Hat:
            update(Product::Hat, Product::productTypeToString(Product::Hat), HatRepository::getInstance(), "hat.png");
            return;
    }
}

template<class T>
void ClothingItemsTabPage::update(Product::ProductType topLevelItem,
                                  string title,
                                  ReadOnlyRepository<T>* repository,
                                  QString iconFileName) {
    bool wasCreated = false;
    QTreeWidgetItem* topLevelItemWidget = treeWidget->topLevelItem(topLevelItem);

    if (topLevelItemWidget == nullptr) { // if it didn't already exist
        topLevelItemWidget = new QTreeWidgetItem(QStringList() << QString::fromStdString(title));
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

        QIcon productIcon(":/assets/icons/" + iconFileName);
        topLevelItemWidget->setIcon(0, productIcon);
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

void ClothingItemsTabPage::showWizard(bool) {
    CreateProductWizard* wizard = new CreateProductWizard();
    wizard->exec();
}