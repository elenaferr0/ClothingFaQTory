

#include <QVBoxLayout>
#include <QToolButton>
#include <QDebug>
#include "products_view.h"
#include "../controllers/wizard_controller.h"
#include "../controllers/main_controller.h"
#include <algorithm>

using std::transform;
using std::inserter;
using std::pair;
using Views::ProductsView;
using Views::Wizard::CreateProductWizardView;
using Controllers::WizardController;
using Controllers::MainController;

int ProductsView::COLUMN_COUNT = 5;

ProductsView::ProductsView(QWidget* parent) : ObserverWidgetView(parent) {
    setController(new MainController(this));
}

void ProductsView::init(const ProductsMap& productsByType) {
    this->productsByType = productsByType;

    treeWidget = new QTreeWidget;
    treeWidget->setHeaderHidden(true);
    treeWidget->setAnimated(true);
    treeWidget->setIconSize(QSize(30, 30));
    treeWidget->setFocusPolicy(Qt::NoFocus);
    treeWidget->setColumnCount(COLUMN_COUNT);

    if (productsByType.getSize() > 0) {
        initTreeView();
    }

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

QTreeWidgetItem* ProductsView::getHeaders() const {
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
    list<shared_ptr<Material>> dbMaterials = dynamic_cast<MainController*>(controller)->findAllMaterials();
    list<shared_ptr<Size>> dbSizes = dynamic_cast<MainController*>(controller)->findAllSizes();

    QList<QString> materials = QList<QString>();
    QList<QString> sizes = QList<QString>();

    transform(dbMaterials.begin(),
              dbMaterials.end(),
              inserter(materials, materials.begin()),
              [](const shared_ptr<Material> material) {
                  return QString::fromStdString(material->getNameAsString());
              });

    transform(dbSizes.begin(),
              dbSizes.end(),
              inserter(sizes, sizes.begin()),
              [](const shared_ptr<Size> size) {
                  return QString::fromStdString(size->getNameAsString());
              });

    CreateProductWizardView* createProductWizard = new CreateProductWizardView(this,
                                                                               QSet<QString>(materials.begin(),
                                                                                             materials.end()),
                                                                               QSet<QString>(sizes.begin(),
                                                                                             sizes.end()));
    createProductWizard->setController(new WizardController(createProductWizard));
    createProductWizard->setAttribute(Qt::WA_DeleteOnClose);
    createProductWizard->show();
}

void Views::ProductsView::rebuildTreeView() {
    productsByType = dynamic_cast<MainController*>(controller)->findAllProductsByType();
    initTreeView();
}
