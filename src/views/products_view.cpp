

#include <QVBoxLayout>
#include <QToolButton>
#include <QDebug>
#include "products_view.h"
#include "../controllers/wizard_controller.h"

using Views::ProductsView;
using Views::Wizard::CreateProductWizard;
using Controllers::WizardController;

int ProductsView::COLUMN_COUNT = 5;

ProductsView::ProductsView(QWidget* parent) : ObserverWidgetView(parent) {}

void ProductsView::init(const ProductsMap& productsByType) {
    this->productsByType = productsByType;

    treeWidget = new QTreeWidget;
    treeWidget->setHeaderHidden(true);
    treeWidget->setAnimated(true);
    treeWidget->setIconSize(QSize(30, 30));
    treeWidget->setFocusPolicy(Qt::NoFocus);
    treeWidget->setColumnCount(COLUMN_COUNT);

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

void Views::ProductsView::notify(Model* model) {
    // TODO handle notify event
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
        treeWidget->addTopLevelItem(topLevelItemWidget);
    }
}

void ProductsView::showWizard(bool) {
    CreateProductWizard* createProductWizard = new CreateProductWizard(this);
    createProductWizard->setController(new WizardController(createProductWizard));
    createProductWizard->show();
}
