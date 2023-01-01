

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
#include "filter_dialog.h"
#include "components/color_icon.h"
#include "info_dialog.h"

using Views::FilterDialog;

using std::for_each;
using std::transform;
using std::inserter;
using std::pair;
using Views::ProductsView;
using Views::FilterDialog;
using Views::Wizard::ProductWizardView;
using Controllers::WizardController;
using Controllers::MainController;
using Services::FileExport::JSONExportableDecorator;

ProductsView::ProductsView(MainView* mainView, QWidget* parent) : WidgetViewParent(parent),
                                                                  priceRangeFilter(0, Views::FilterDialog::MAX_PRICE),
                                                                  mainView(mainView) {
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

    stack = new QStackedWidget;
    QVBoxLayout* verticalLayout = new QVBoxLayout(this);
    toolBar = new QToolBar(this);
    verticalLayout->addWidget(toolBar);

    EmptyState* emptyState = new EmptyState;
    stack->insertWidget(EMPTY_STATE_IDX, emptyState);
    stack->insertWidget(TREE_VIEW_IDX, treeWidget);
    verticalLayout->addWidget(stack);

    filterButton = new QToolButton;
    exportButton = new QToolButton;
    initTreeView(productsByType);

    vector<int> colWidths = {170, 100, 300, 100, 110, 110, 150, 50, 70, 50};
    for (int i = 0; i < COLUMN_COUNT; ++i) {
        treeWidget->setColumnWidth(i, colWidths.at(i));
    }

    verticalLayout->setAlignment(Qt::AlignTop);

    toolBar->setMovable(false);

    QToolButton* createButton = new QToolButton;
    createButton->setIcon(QIcon(":/assets/icons/add.png"));
    createButton->setText(tr("Create &New"));
    createButton->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextUnderIcon);
    connect(createButton, SIGNAL(clicked()), this, SLOT(showCreateProductWizard()));
    toolBar->addWidget(createButton);

    filterButton->setIcon(QIcon(":/assets/icons/filter.png"));
    filterButton->setText(tr("&Filter"));
    filterButton->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextUnderIcon);
    connect(filterButton, SIGNAL(clicked()), this, SLOT(handleFilterButtonClicked()));
    toolBar->addWidget(filterButton);

    exportButton->setIcon(QIcon(":/assets/icons/export_json.png"));
    exportButton->setText(tr("&Export to JSON"));
    exportButton->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextUnderIcon);
    connect(exportButton, SIGNAL(clicked()), this, SLOT(handleExportJsonButtonClicked()));
    toolBar->addWidget(exportButton);

    // create a totally right aligned (invisible) button that clears all the filters
    QWidget* rightAlignedWidget = new QWidget;
    QHBoxLayout* rightAlignedLayout = new QHBoxLayout;
    rightAlignedWidget->setLayout(rightAlignedLayout);

    clearFiltersButton = new QToolButton;
    clearFiltersButton->setIcon(QIcon(":/assets/icons/clear_filters.png"));
    clearFiltersButton->setObjectName("clearFiltersButton");
    clearFiltersButton->setText(tr("&Clear filters"));
    clearFiltersButton->setVisible(false);
    clearFiltersButton->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextBesideIcon);
    connect(clearFiltersButton, SIGNAL(clicked()), this, SLOT(handleClearFilterButtonClicked()));

    rightAlignedLayout->addStretch();
    rightAlignedLayout->addWidget(clearFiltersButton);
    toolBar->addWidget(rightAlignedWidget);

    toolBar->setIconSize(QSize(20, 20));

    // fetch all materials and sizes and store them to reuse them
    LinkedList<shared_ptr<Material>> dbMaterials = dynamic_cast<MainController*>(controller)->findAllMaterials();
    LinkedList<shared_ptr<Size>> dbSizes = dynamic_cast<MainController*>(controller)->findAllSizes();

    materials = QList<QString>();
    sizes = QList<QString>();

    transform(dbMaterials.begin(),
              dbMaterials.end(),
              inserter(materials, materials.end()),
              [](const shared_ptr<Material> material) {
                  return QString::fromStdString(material->getNameAsString());
              });

    transform(dbSizes.begin(),
              dbSizes.end(),
              inserter(sizes, sizes.end()),
              [](const shared_ptr<Size> size) {
                  return QString::fromStdString(size->getNameAsString());
              });
}

QTreeWidgetItem* ProductsView::getHeaders() const {
    QTreeWidgetItem* headers = new QTreeWidgetItem(QStringList() << "Code"
                                                                 << "Color"
                                                                 << "Description"
                                                                 << "Size"
                                                                 << "Available qt."
                                                                 << "Sold qt."
                                                                 << "Calculated price"
                                                                 << "Edit"
                                                                 << "Delete"
                                                                 << "Info");
    QFont font = QFont();
    font.setBold(true);

    for (int i = 0; i < COLUMN_COUNT; ++i) {
        headers->setFont(i, font);
    }


    return headers;
}

void ProductsView::initTreeView(const ProductsMap& productsByType) {
    bool areAllEmpty = true;

    for (auto type = productsByType.cbegin(); type != productsByType.cend(); type++) {
        Product::ProductType productType = (*type).first;
        LinkedList<shared_ptr<Product>> products = (*type).second;
        if (!products.isEmpty()) {
            areAllEmpty = false;
        }
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
        }

        QIcon productIcon(":/assets/icons/" + productTypeName.toLower() + ".png");
        topLevelItemWidget->setIcon(0, productIcon);
        topLevelItemWidget->setFlags(topLevelItemWidget->flags() & ~Qt::ItemIsSelectable);
        if (wasCreated) {
            treeWidget->addTopLevelItem(topLevelItemWidget);
        }
    }

    if (areAllEmpty) {
        stack->setCurrentIndex(EMPTY_STATE_IDX);
        filterButton->setDisabled(true);
        exportButton->setDisabled(true);
    } else {
        stack->setCurrentIndex(TREE_VIEW_IDX);
        filterButton->setEnabled(true);
        exportButton->setEnabled(true);
    }

}

void ProductsView::buildAndInsertChild(QTreeWidgetItem* topLevelItemWidget,
                                       shared_ptr<Product> product, Product::ProductType productType) {
    stack->setCurrentIndex(TREE_VIEW_IDX);
    QStringList values = getColumnsFromProduct(product);
    QTreeWidgetItem* row = new QTreeWidgetItem(values);

    if (topLevelItemWidget->childCount() == 0) {
        QTreeWidgetItem* headers = getHeaders();
        topLevelItemWidget->addChild(headers);
    }
    topLevelItemWidget->addChild(row);

    ProductIconButton* editButton = new ProductIconButton(product, row, productType, this);
    editButton->setIcon(QIcon(":/assets/icons/edit.png"));
    editButton->setObjectName("editButton");

    treeWidget->setItemWidget(row, COLUMN_COUNT - 3, editButton);
    connect(editButton, SIGNAL(clicked(shared_ptr<Product>, QTreeWidgetItem * , Product::ProductType)), this,
            SLOT(clickedEditButton(shared_ptr<Product>, QTreeWidgetItem * , Product::ProductType)));

    ProductIconButton* deleteButton = new ProductIconButton(product, row, productType, this);

    deleteButton->setIcon(QIcon(":/assets/icons/delete.png"));
    deleteButton->setObjectName("deleteButton");

    treeWidget->setItemWidget(row, COLUMN_COUNT - 2, deleteButton);
    connect(deleteButton, SIGNAL(clicked(shared_ptr<Product>, QTreeWidgetItem * , Product::ProductType)), this,
            SLOT(clickedDeleteButton(shared_ptr<Product>, QTreeWidgetItem * , Product::ProductType)));

    ProductIconButton* infoButton = new ProductIconButton(product, row, productType, this);
    infoButton->setIcon(QIcon(":/assets/icons/info.png"));
    infoButton->setObjectName("infoButton");
    treeWidget->setItemWidget(row, COLUMN_COUNT - 1, infoButton);

    connect(infoButton, SIGNAL(clicked(shared_ptr<Product>, QTreeWidgetItem * , Product::ProductType)), this,
            SLOT(clickedInfoButton(shared_ptr<Product>, QTreeWidgetItem * , Product::ProductType)));

    row->setIcon(1, ColorIcon(product->getColor())); // icon representing the product's color
}

QStringList ProductsView::getColumnsFromProduct(const shared_ptr<Product> product) const {
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

void ProductsView::showCreateProductWizard() {
    ProductWizardView* createProductWizard = new ProductWizardView(ProductWizardView::Create,
                                                                   mainView,
                                                                   this,
                                                                   materials,
                                                                   sizes);
    connect(createProductWizard, SIGNAL(completed(shared_ptr<Product>, Product::ProductType)),
            this, SLOT(handleProductCreation(shared_ptr<Product>, Product::ProductType)));
    createProductWizard->setAttribute(Qt::WA_DeleteOnClose);
    createProductWizard->show();
}

void Views::ProductsView::rebuildTreeView() {
    treeWidget->clear();
    priceRangeFilter = QPair(0, Views::FilterDialog::MAX_PRICE);
    initTreeView(dynamic_cast<MainController*>(controller)->findAllProductsByType());
}

void Views::ProductsView::handleProductCreation(shared_ptr<Product> product, Product::ProductType type) {
    buildAndInsertChild(treeWidget->topLevelItem(type), product, type);
}

void Views::ProductsView::clickedEditButton(shared_ptr<Product> product, QTreeWidgetItem*,
                                            Product::ProductType productType) {
    ProductWizardView* editProductWizard = new ProductWizardView(ProductWizardView::Edit,
                                                                 mainView,
                                                                 this,
                                                                 materials,
                                                                 sizes,
                                                                 product,
                                                                 productType
    );
    connect(editProductWizard, SIGNAL(completed(shared_ptr<Product>, Product::ProductType)),
            this, SLOT(handleProductEditing(shared_ptr<Product>, Product::ProductType)));
    editProductWizard->setAttribute(Qt::WA_DeleteOnClose);
    editProductWizard->show();
}

void
Views::ProductsView::clickedDeleteButton(shared_ptr<Product> product, QTreeWidgetItem* row,
                                         Product::ProductType productType) {
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
        if (treeWidget->topLevelItem(productType)->childCount() == 1) { // has only the header
            treeWidget->topLevelItem(productType)->removeChild(treeWidget->topLevelItem(productType)->child(0));
        }
    }
}

void Views::ProductsView::handleProductEditing(shared_ptr<Product>, Product::ProductType) {
    rebuildTreeView();
}

void Views::ProductsView::handleExportJsonButtonClicked() {
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
                LinkedList<shared_ptr<Product>> products = (*pt).second;
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

void Views::ProductsView::handleFilterButtonClicked() {
    FilterDialog* filterDialog = new FilterDialog(this);
    filterDialog->setAttribute(Qt::WA_DeleteOnClose);
    connect(filterDialog, SIGNAL(startFiltering(Filters)), this, SLOT(handleFilterDialogCompleted(Filters)));
    filterDialog->exec();
}

void Views::ProductsView::handleFilterDialogCompleted(Filters filters) {
    treeWidget->clear();
    priceRangeFilter = QPair(filters.getPriceRange());
    initTreeView(dynamic_cast<MainController*>(controller)->findAllProductsByType(&filters));
    clearFiltersButton->setVisible(true);
}

void Views::ProductsView::handleClearFilterButtonClicked() {
    clearFiltersButton->setVisible(false);
    rebuildTreeView();
}

void Views::ProductsView::clickedInfoButton(shared_ptr<Product> product, QTreeWidgetItem*, Product::ProductType) {
    InfoDialog* infoDialog = new InfoDialog(product);
    infoDialog->show();
}
