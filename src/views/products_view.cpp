

#include <QVBoxLayout>
#include <QToolButton>
#include "products_view.h"
#include "components/product_icon_button.h"
#include <algorithm>
#include <QPainter>
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFileDialog>
#include "../services/file_export/json_exportable_decorator.h"
#include "search_dialog.h"

using Views::SearchDialog;

using std::for_each;
using std::transform;
using std::inserter;
using std::pair;
using Views::ProductsView;
using Views::SearchDialog;
using Views::Wizard::ProductWizardView;
using Controllers::WizardController;
using Controllers::MainController;
using Services::FileExport::JSONExportableDecorator;

const int ProductsView::COLUMN_COUNT = 9;

ProductsView::ProductsView(MainView* mainView, QWidget* parent) : WidgetViewParent(parent),
                                                                  priceRangeFilter(0, INT_MAX) {
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

    vector<int> colWidths = {170, 100, 300, 100, 110, 110, 150};
    for (int i = 0; i < COLUMN_COUNT - 2; ++i) {
        treeWidget->setColumnWidth(i, colWidths.at(i));
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
    connect(createButton, SIGNAL(clicked(bool)), this, SLOT(showCreateProductWizard(bool)));
    toolBar->addWidget(createButton);

    QToolButton* searchButton = new QToolButton;
    searchButton->setIcon(QIcon(":/assets/icons/search.png"));
    searchButton->setText(tr("&Search"));
    searchButton->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextUnderIcon);
    connect(searchButton, SIGNAL(clicked(bool)), this, SLOT(handleSearchButtonClicked(bool)));
    toolBar->addWidget(searchButton);

    QToolButton* exportButton = new QToolButton;
    exportButton->setIcon(QIcon(":/assets/icons/export_json.png"));
    exportButton->setText(tr("&Export to JSON"));
    exportButton->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextUnderIcon);
    connect(exportButton, SIGNAL(clicked(bool)), this, SLOT(handleExportJsonButtonClicked(bool)));
    toolBar->addWidget(exportButton);

    toolBar->setIconSize(QSize(20, 20));

    layout->addWidget(toolBar);
    layout->addWidget(treeWidget);

    // fetch all materials and sizes and store them to reuse them
    LinkedList<Material*> dbMaterials = dynamic_cast<MainController*>(controller)->findAllMaterials();
    LinkedList<Size*> dbSizes = dynamic_cast<MainController*>(controller)->findAllSizes();

    materials = QList<QString>();
    sizes = QList<QString>();

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
}

QTreeWidgetItem* ProductsView::getHeaders() const {
    QTreeWidgetItem* headers = new QTreeWidgetItem(QStringList() << "Code"
                                                                 << "Color"
                                                                 << "Description"
                                                                 << "Size"
                                                                 << "Available qt"
                                                                 << "Sold qt"
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
    double minPrice = 0;
    double maxPrice = 0;
    for (auto type = productsByType.cbegin(); type != productsByType.cend(); type++) {
        Product::ProductType productType = (*type).first;
        LinkedList<Product*> products = (*type).second;
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
            double price = (*p)->computePrice();

            if (price >= priceRangeFilter.first && price <= priceRangeFilter.second) {
                buildAndInsertChild(topLevelItemWidget, *p, productType);
            }
            if (price < minPrice) {
                minPrice = price;
            }

            if (price > maxPrice) {
                maxPrice = price;
            }
        }

        QIcon productIcon(":/assets/icons/" + productTypeName.toLower() + ".png");
        topLevelItemWidget->setIcon(0, productIcon);
        topLevelItemWidget->setFlags(topLevelItemWidget->flags() & ~Qt::ItemIsSelectable);
        if (wasCreated) {
            treeWidget->addTopLevelItem(topLevelItemWidget);
        }
    }
    priceRangeFilter = QPair(minPrice, maxPrice);
}

void ProductsView::buildAndInsertChild(QTreeWidgetItem* topLevelItemWidget,
                                       Product* product, Product::ProductType productType) {
    QStringList values = getColumnsFromProduct(product);
    QTreeWidgetItem* row = new QTreeWidgetItem(values);
    topLevelItemWidget->addChild(row);

    ProductIconButton* editButton = new ProductIconButton(":/assets/icons/edit.png", "editButton", product,
                                                          row, productType, this);
    treeWidget->setItemWidget(row, COLUMN_COUNT - 2, editButton);
    connect(editButton, SIGNAL(clicked(Product * , QTreeWidgetItem * , Product::ProductType)), this,
            SLOT(clickedEditButton(Product * , QTreeWidgetItem * , Product::ProductType)));

    ProductIconButton* deleteButton = new ProductIconButton(":/assets/icons/delete.png", "deleteButton", product,
                                                            row, productType, this);

    treeWidget->setItemWidget(row, COLUMN_COUNT - 1, deleteButton);
    connect(deleteButton, SIGNAL(clicked(Product * , QTreeWidgetItem * , Product::ProductType)), this,
            SLOT(clickedDeleteButton(Product * , QTreeWidgetItem * , Product::ProductType)));

    row->setIcon(1, drawColorIcon(product->getColor()));
}

QStringList ProductsView::getColumnsFromProduct(const Product* product) const {
    QStringList values;
    values << QString::fromStdString(product->getCode())
           << QString::fromStdString(product->getColor())
           << QString::fromStdString(product->getDescription())
           << QString::fromStdString(product->getSize().getNameAsString())
           << QString::number(product->getAvailableQuantity())
           << QString::number(product->getSoldQuantity())
           << QString::number(product->computePrice(), 'f', 2) + "$";
    return values;
}

void ProductsView::showCreateProductWizard(bool) {
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
    treeWidget->clear();
    priceRangeFilter = QPair(0, INT_MAX);
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

void Views::ProductsView::clickedEditButton(Product* product, QTreeWidgetItem*, Product::ProductType productType) {
    ProductWizardView* editProductWizard = new ProductWizardView(ProductWizardView::Edit,
                                                                 this,
                                                                 materials,
                                                                 sizes,
                                                                 product,
                                                                 productType
    );
    connect(editProductWizard, SIGNAL(completed(Product * , Product::ProductType)),
            this, SLOT(handleProductEditing(Product * , Product::ProductType)));
    editProductWizard->setAttribute(Qt::WA_DeleteOnClose);
    editProductWizard->show();
}

void
Views::ProductsView::clickedDeleteButton(Product* product, QTreeWidgetItem* row, Product::ProductType productType) {
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
        dynamic_cast<MainController*>(controller)->deleteProductById(product->getId());
        treeWidget->topLevelItem(productType)->removeChild(row);
    }
}

void Views::ProductsView::handleProductEditing(Product*, Product::ProductType) {
    rebuildTreeView();
}

void Views::ProductsView::handleExportJsonButtonClicked(bool) {
    // Save to file
    QDateTime currentTime = QDateTime::currentDateTime();
    QString defaultFileName = "/clothing_faqtory_export_" + currentTime.toString(Qt::DateFormat::ISODate) + ".json";

    QString path = QFileDialog::getSaveFileName(nullptr, "Save As", QDir::homePath() + defaultFileName,
                                                tr("JSON Files (*.json);;All Files (*)"));

    if (!path.isEmpty()) {

        QFile file(path);

        QMessageBox* resultBox = new QMessageBox(this);
        resultBox->setStandardButtons(QMessageBox::Ok);
        resultBox->setDefaultButton(QMessageBox::Ok);

        if (file.open(QIODevice::WriteOnly)) {
            ProductsMap productsMap = dynamic_cast<MainController*>(controller)->findAllProductsByType();

            QJsonObject jsonObject;
            for (auto pt = productsMap.cbegin(); pt != productsMap.cend(); pt++) {
                QJsonArray jsonArray;
                QString productTypeKey = QString::fromStdString(Product::productTypeToString((*pt).first));
                LinkedList<Product*> products = (*pt).second;
                for (auto p = products.begin(); p != products.end(); p++) {
                    JSONExportableDecorator decorator(*(*p));
                    jsonArray.append(decorator.exportData());
                }
                jsonObject.insert(productTypeKey, jsonArray);
            }
            QJsonDocument jsonDoc(jsonObject);
            file.write(jsonDoc.toJson());
            file.close();
            resultBox->setText("File saved successfully in " + path);
            resultBox->setIcon(QMessageBox::Information);
        } else {
            resultBox->setText("Something went wrong while saving the file");
            resultBox->setIcon(QMessageBox::Critical);
        }

        resultBox->show();
    }

}

void Views::ProductsView::handleSearchButtonClicked(bool) {
    searchDialog = new SearchDialog(this);
    connect(searchDialog, SIGNAL(startSearch(Filters)), this, SLOT(handleSearchDialogCompleted(Filters)));
    searchDialog->exec();
}

void Views::ProductsView::handleSearchDialogCompleted(Filters filters) {
    treeWidget->clear();
    priceRangeFilter = QPair(filters.getPriceRange());
    initTreeView(dynamic_cast<MainController*>(controller)->findAllProductsByType(&filters));
}
