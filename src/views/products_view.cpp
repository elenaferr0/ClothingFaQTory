

#include <QVBoxLayout>
#include <QToolButton>
#include "products_view.h"
#include "components/icon_button.h"
#include <algorithm>
#include <QPainter>
#include <QPushButton>
#include <QMessageBox>

using std::transform;
using std::inserter;
using std::pair;
using Views::ProductsView;
using Views::Wizard::ProductWizardView;
using Controllers::WizardController;
using Controllers::MainController;

int ProductsView::COLUMN_COUNT = 7;

ProductsView::ProductsView(MainView* mainView, QWidget* parent) : ObserverWidgetView(parent) {
    setController(new MainController(this));
    connect(controller, SIGNAL(databaseError(Error * )), mainView, SLOT(handleDatabaseError(Error * )));
}

void ProductsView::init(const ProductsMap& productsByType) {

    treeWidget = new QTreeWidget;
    treeWidget->setHeaderHidden(true);
    treeWidget->setAnimated(true);
    treeWidget->setIconSize(QSize(30, 30));
    treeWidget->setFocusPolicy(Qt::NoFocus);
    treeWidget->setColumnCount(COLUMN_COUNT);
    treeWidget->setSelectionMode(QAbstractItemView::NoSelection);

    if (productsByType.getSize() > 0) {
        initTreeView(productsByType);
    }

    for (int i = 0; i < COLUMN_COUNT - 2; ++i) {
        treeWidget->setColumnWidth(i, 170);
    }
    treeWidget->setColumnWidth(COLUMN_COUNT - 2, 50);
    treeWidget->setColumnWidth(COLUMN_COUNT - 1, 50);

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

void Views::ProductsView::notify(Model*) {
    // TODO handle notify event
}

QTreeWidgetItem* ProductsView::getHeaders() const {
    QTreeWidgetItem* headers = new QTreeWidgetItem(QStringList() << "Code"
                                                                 << "Color"
                                                                 << "Description"
                                                                 << "Size"
                                                                 << "Calculated price"
                                                                 << "Edit"
                                                                 << "Delete");
    QFont font = QFont();
    font.setBold(true);

    for (int i = 0; i < COLUMN_COUNT; ++i) {
        headers->setFont(i, font);
    }


    return headers;
}

void ProductsView::initTreeView(const ProductsMap& productsByType) {
    for (auto type = productsByType.cbegin(); type != productsByType.cend(); type++) {
        Product::ProductType productType = (*type).first;
        LinkedList<Product*> products = productsByType.get(productType).value();
        QString productTypeName = QString::fromStdString(Product::productTypeToString(productType));
        QTreeWidgetItem* topLevelItemWidget = treeWidget->topLevelItem(productType);

        bool wasCreated = false;
        if (topLevelItemWidget == nullptr) {
            topLevelItemWidget = new QTreeWidgetItem(QStringList() << productTypeName);
            wasCreated = true;
        } else {
            for (int i = 0; i < topLevelItemWidget->childCount(); i++) {
                topLevelItemWidget->removeChild(topLevelItemWidget->child(i));
            }
        }

        if (products.getSize() > 0) {
            QTreeWidgetItem* headers = getHeaders();
            topLevelItemWidget->addChild(headers);
        }

        for (auto p = products.begin(); p != products.end(); p++) {
            buildAndInsertChild(topLevelItemWidget, *p, productType);
        }

        QIcon productIcon(":/assets/icons/" + productTypeName.toLower() + ".png");
        topLevelItemWidget->setIcon(0, productIcon);
        topLevelItemWidget->setFlags(topLevelItemWidget->flags() & ~Qt::ItemIsSelectable);
        if (wasCreated) {
            treeWidget->addTopLevelItem(topLevelItemWidget);
        }
    }
}

void ProductsView::buildAndInsertChild(QTreeWidgetItem* topLevelItemWidget,
                                       Product* product, Product::ProductType productType) {
    QStringList values;
    values << QString::fromStdString(product->getCode())
           << QString::fromStdString(product->getColor())
           << QString::fromStdString(product->getDescription())
           << QString::fromStdString(product->getSize().getNameAsString())
           << QString::number(product->computePrice(), 'f', 2) + "$";
    QTreeWidgetItem* row = new QTreeWidgetItem(values);
    topLevelItemWidget->addChild(row);

    IconButton* editButton = new IconButton(":/assets/icons/edit.png", "editButton", product->getId(),
                                            row, productType, this);
    treeWidget->setItemWidget(row, COLUMN_COUNT - 2, editButton);
    connect(editButton, SIGNAL(clicked(int, QTreeWidgetItem * , Product::ProductType)), this,
            SLOT(clickedEditButton(int, QTreeWidgetItem * , Product::ProductType)));

    IconButton* deleteButton = new IconButton(":/assets/icons/delete.png", "deleteButton", product->getId(),
                                              row, productType, this);

    treeWidget->setItemWidget(row, COLUMN_COUNT - 1, deleteButton);
    connect(deleteButton, SIGNAL(clicked(int, QTreeWidgetItem * , Product::ProductType)), this,
            SLOT(clickedDeleteButton(int, QTreeWidgetItem * , Product::ProductType)));

    row->setIcon(1, drawColorIcon(product->getColor()));
}

void ProductsView::showWizard(bool) {
    LinkedList<Material*> dbMaterials = dynamic_cast<MainController*>(controller)->findAllMaterials();
    LinkedList<Size*> dbSizes = dynamic_cast<MainController*>(controller)->findAllSizes();

    QList<QString> materials = QList<QString>();
    QList<QString> sizes = QList<QString>();

    transform(dbMaterials.begin(),
              dbMaterials.end(),
              inserter(materials, materials.end()),
              [](const Material* material) {
                  return QString::fromStdString(material->getNameAsString());
              });

    transform(dbSizes.begin(),
              dbSizes.end(),
              inserter(sizes, sizes.end()),
              [](const Size* size) {
                  return QString::fromStdString(size->getNameAsString());
              });

    ProductWizardView* createProductWizard = new ProductWizardView(ProductWizardView::Create,
                                                                   this,
                                                                   materials,
                                                                   sizes);
    connect(createProductWizard, SIGNAL(completed(Product * , Product::ProductType)),
            this, SLOT(handleProductCreation(Product * , Product::ProductType)));
    createProductWizard->setAttribute(Qt::WA_DeleteOnClose);
    createProductWizard->show();
}

void Views::ProductsView::rebuildTreeView() {
    initTreeView(dynamic_cast<MainController*>(controller)->findAllProductsByType());
}

QIcon Views::ProductsView::drawColorIcon(const string& hex) {
    const QColor color(QString::fromStdString(hex));
    QPixmap pixmap(COLOR_ICON_SIZE, COLOR_ICON_SIZE);
    pixmap.fill(color);
    QPainter painter(&pixmap);
    QPen pen;
    pen.setWidth(3);
    pen.setColor(Qt::black);
    painter.setPen(pen);
    painter.drawRect(0, 0, COLOR_ICON_SIZE, COLOR_ICON_SIZE);
    QIcon icon(pixmap);
    return icon;
}

void Views::ProductsView::handleProductCreation(Product* product, Product::ProductType type) {
    buildAndInsertChild(treeWidget->topLevelItem(type), product, type);
}

void Views::ProductsView::clickedEditButton(int id, QTreeWidgetItem* row, Product::ProductType productType) {
    qInfo() << "edit Id: " << id;
}

void Views::ProductsView::clickedDeleteButton(int id, QTreeWidgetItem* row, Product::ProductType productType) {
    QMessageBox* errorBox = new QMessageBox;
    errorBox->setWindowTitle("Delete product");
    errorBox->setText("### Do you really want to delete this product?");
    errorBox->setInformativeText("This change cannot be reverted");
    errorBox->setTextFormat(Qt::MarkdownText);
    errorBox->setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    errorBox->setDefaultButton(QMessageBox::Cancel);
    errorBox->setAttribute(Qt::WA_DeleteOnClose);
    errorBox->resize(300, 200);
    int result = errorBox->exec();

    if (result == QMessageBox::Yes) {
        dynamic_cast<MainController*>(controller)->deleteProductById(id);
        treeWidget->topLevelItem(productType)->removeChild(row);
    }
}
