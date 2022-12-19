

#include <QVBoxLayout>
#include <QToolButton>
#include "products_view.h"

using Views::ProductsView;

int ProductsView::COLUMN_COUNT = 5;

ProductsView::ProductsView(ProductsMap& productsByType, QWidget* parent) :
        productsByType(productsByType), ViewInterface(parent) {
    init();
}

void ProductsView::init() {
    treeWidget = new QTreeWidget;
    treeWidget->setHeaderHidden(true);
    treeWidget->setAnimated(true);
    treeWidget->setIconSize(QSize(30, 30));
    treeWidget->setFocusPolicy(Qt::NoFocus);

    initTreeView();

    for (int i = 0; i < COLUMN_COUNT; ++i) {
        treeWidget->setColumnWidth(i, 180);
    }

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignTop);

    toolBar = new QToolBar(this);
    toolBar->setMovable(false);

    QToolButton* createButton = new QToolButton;
    createButton->setIcon(QIcon(":/assets/icons/add.png"));
    createButton->setText(tr("Create &New"));
    createButton->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextUnderIcon);
    connect(createButton, SIGNAL(clicked(bool)), this, SLOT(showWizard(bool)));
    toolBar->addWidget(createButton);

    QToolButton* searchButton = new QToolButton;
    searchButton->setIcon(QIcon(":/assets/icons/search.png"));
    searchButton->setText(tr("&Search"));
    searchButton->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextUnderIcon);
//    connect(searchButton, SIGNAL(clicked(bool)), this, SLOT(showNewProduct::ProductTypeChooserWindow(bool)));
    toolBar->addWidget(searchButton);

    toolBar->setIconSize(QSize(15, 15));

    layout->addWidget(toolBar);
    layout->addWidget(treeWidget);
}

void Views::ProductsView::notify(Product& product) {
    // update tree widget of the given product
}

QTreeWidgetItem* ProductsView::getHeaders() {
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

void ProductsView::initTreeView() {
    for (auto type = productsByType.cbegin(); type != productsByType.cend(); type++) {
        Product::ProductType productType = (*type).first;
        list<shared_ptr<Product>> products = (*type).second;
        QString productTypeName = QString::fromStdString(Product::productTypeToString(productType));

        QTreeWidgetItem* topLevelItemWidget = new QTreeWidgetItem(QStringList() << productTypeName);

        // remove all existing children
        for (int i = 0; i < topLevelItemWidget->childCount(); ++i) {
            topLevelItemWidget->removeChild(topLevelItemWidget->child(i));
        }

        if (products.size() > 0) {
            QTreeWidgetItem* headers = getHeaders();
            topLevelItemWidget->addChild(headers);
        }

        for (auto p = products.begin(); p != products.end(); p++) {
            QStringList columns;
            columns << QString::fromStdString((*p)->getCode())
                    << QString::fromStdString((*p)->getColor())
                    << QString::fromStdString((*p)->getDescription())
                    << QString::fromStdString((*p)->getSize().getNameAsString())
                    << QString::number((*p)->computePrice(), 'f', 2) + "$";

            QTreeWidgetItem* child = new QTreeWidgetItem(columns);
            topLevelItemWidget->addChild(child);
        }

        QIcon productIcon(":/assets/icons/" + productTypeName.toLower() + ".png");
        topLevelItemWidget->setIcon(0, productIcon);
        topLevelItemWidget->setFlags(topLevelItemWidget->flags() & ~Qt::ItemIsSelectable);
    }
}
