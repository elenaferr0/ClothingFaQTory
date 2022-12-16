
#ifndef PRODUCT_TAB_H
#define PRODUCT_TAB_H

#include <QWidget>
#include <QLabel>
#include <QTableWidget>
#include <QTreeWidget>
#include <QToolBar>
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

QT_BEGIN_NAMESPACE
namespace Views::Tabs::ClothingItems { class ClothingItemsTabPage; }
QT_END_NAMESPACE

class ClothingItemsTabPage : public QWidget {
Q_OBJECT
private:
    static int COLUMN_COUNT;
    enum TopLevelItem {
        Jeans, Vest, Overalls, Bracelet, BackPack, Hat
    };

    QTreeWidget* treeWidget;
    QToolBar* toolBar;

    QTreeWidgetItem* getHeaders();

    template<class T>
    void update(TopLevelItem topLevelItem,
                QString title,
                ReadOnlyRepository<T>* repository,
                QString iconFileName);

public:
    ClothingItemsTabPage(QWidget* parent = nullptr);

    void updateTopLevelItem(TopLevelItem topLevelItem);

    void updateTreeContent();
};


#endif //PRODUCT_TAB_H
