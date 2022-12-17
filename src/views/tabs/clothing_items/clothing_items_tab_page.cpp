#include <QVBoxLayout>
#include <QHeaderView>
#include <QToolButton>
#include <QPushButton>
#include "clothing_items_tab_page.h"
#include "../../mainwindow.h"
#include "../../product_type_button.h"

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
    connect(createButton, SIGNAL(clicked(bool)), this, SLOT(showNewProductTypeChooserWindow(bool)));
    toolBar->addWidget(createButton);

    QToolButton* searchButton = new QToolButton;
    searchButton->setIcon(QIcon(":/assets/icons/search.png"));
    searchButton->setText("Search");
    searchButton->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextUnderIcon);
//    connect(searchButton, SIGNAL(clicked(bool)), this, SLOT(showNewProductTypeChooserWindow(bool)));
    toolBar->addWidget(searchButton);

    toolBar->setIconSize(QSize(15, 15));

    layout->addWidget(toolBar);
    layout->addWidget(treeWidget);

}

void ClothingItemsTabPage::populateTree() {
    treeWidget->clear();
    treeWidget->setColumnCount(COLUMN_COUNT);
    for (int i = Jeans; i != Hat + 1; i++) {
        auto topLevelItem = static_cast<ProductType>(i);
        updateTopLevelItem(topLevelItem);
    }
}

void ClothingItemsTabPage::updateTopLevelItem(ProductType topLevelItem) {
    switch (topLevelItem) {
        case Jeans:
            update(Jeans, productTypeToString(Jeans), JeansRepository::getInstance(), "jeans.png");
            return;
        case Vest:
            update(Vest, productTypeToString(Vest), VestRepository::getInstance(), "vest.png");
            return;
        case Overalls:
            update(Overalls, productTypeToString(Overalls), OverallsRepository::getInstance(), "overalls.png");
            return;
        case Bracelet:
            update(Bracelet, productTypeToString(Bracelet), BraceletRepository::getInstance(), "bracelet.png");
            return;
        case BackPack:
            update(BackPack, productTypeToString(BackPack), BackPackRepository::getInstance(), "backpack.png");
            return;
        case Hat:
            update(Hat, productTypeToString(Hat), HatRepository::getInstance(), "hat.png");
            return;
    }
}

template<class T>
void ClothingItemsTabPage::update(ProductType topLevelItem, QString title, ReadOnlyRepository<T>* repository,
                                  QString iconFileName) {
    bool wasCreated = false;
    QTreeWidgetItem* topLevelItemWidget = treeWidget->topLevelItem(topLevelItem);

    if (topLevelItemWidget == nullptr) { // if it didn't already exist
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

void ClothingItemsTabPage::showNewProductTypeChooserWindow(bool) {
    QDialog* dialog = new QDialog(this);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->setModal(true);
    dialog->setWindowTitle("Choose product type to insert");
    dialog->setMinimumSize(QSize(400, 400));
    QVBoxLayout* layout = new QVBoxLayout(dialog);

    for (int i = Jeans; i < Hat + 1; i++) {
        ProductType productType = static_cast<ProductType>(i);
        ProductTypeButton* button = new ProductTypeButton(dialog, productType);
        button->setText(productTypeToString(productType));
        connect(button, SIGNAL(clicked(int)), this, SLOT(handleProductTypeChoice(int)));
        connect(button, SIGNAL(clicked()), dialog, SLOT(close()));
        layout->addWidget(button);
    }

    dialog->exec();
}

void ClothingItemsTabPage::handleProductTypeChoice(int choice) {
    qInfo() << choice;
}

QString ClothingItemsTabPage::productTypeToString(ProductType productType) {
    switch (productType) {
        case Jeans:
            return "Jeans";
        case Overalls:
            return "Overalls";
        case Hat:
            return "Hat";
        case Bracelet:
            return "Bracelet";
        case Vest:
            return "Vest";
        case BackPack:
        default:
            return "BackPack";
    }
}
