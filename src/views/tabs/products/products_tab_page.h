
#ifndef PRODUCT_TAB_H
#define PRODUCT_TAB_H

#include <QWidget>
#include <QLabel>
#include <QTableWidget>
#include <QTreeWidget>
#include <QToolBar>
#include <QVBoxLayout>
#include "../../../core/containers/map.h"
#include "../../../services/repositories/jeans_repository.h"
#include "../../../services/repositories/vest_repository.h"
#include "../../../services/repositories/overalls_repository.h"
#include "../../../services/repositories/bracelet_repository.h"
#include "../../../services/repositories/backpack_repository.h"
#include "../../../services/repositories/hat_repository.h"

using Core::Containers::Map;
using Services::JeansRepository;
using Services::VestRepository;
using Services::OverallsRepository;
using Services::BraceletRepository;
using Services::BackPackRepository;
using Services::HatRepository;
using Models::Product;

QT_BEGIN_NAMESPACE
namespace Views::Tabs::ClothingItems { class ClothingItemsTabPage; }
QT_END_NAMESPACE

class ProductsTabPage : public QWidget {
Q_OBJECT
private:
    static int COLUMN_COUNT;

    QTreeWidget* treeWidget;
    QToolBar* toolBar;

    QTreeWidgetItem* getHeaders();

    QSet<QString> productCodes; // list of all product codes used for the completer widget

    template<class T>
    void update(Product::ProductType topLevelItem,
                string title,
                ReadOnlyRepository<T>* repository,
                QString iconFileName);

public:
    ProductsTabPage(QWidget* parent = nullptr);

    void updateTopLevelItem(Product::ProductType topLevelItem);

    void populateTree();

private slots:
    void showWizard(bool);
};


#endif //PRODUCT_TAB_H
