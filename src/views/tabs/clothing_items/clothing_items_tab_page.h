
#ifndef PRODUCT_TAB_H
#define PRODUCT_TAB_H

#include <QWidget>
#include <QLabel>
#include <QTableWidget>
#include <QTreeWidget>
#include "../../../core/containers/map.h"
#include "../../../services/repositories/jeans_repository.h"
#include "../../../services/repositories/vest_repository.h"
#include "../../../services/repositories/overalls_repository.h"

using Core::Containers::Map;
using Services::JeansRepository;
using Services::VestRepository;
using Services::OverallsRepository;

QT_BEGIN_NAMESPACE
namespace Views::Tabs::ClothingItems { class ClothingItemsTabPage; }
QT_END_NAMESPACE

class ClothingItemsTabPage : public QWidget {
Q_OBJECT
private:
    static unsigned int COLUMN_COUNT;
    enum TopLevelItem {Jeans, Vest, Overalls, Bracelet, BackPack, Hat};

    JeansRepository* jeansRepository;
    VestRepository* vestRepository;
    OverallsRepository* overallsRepository;

    QTreeWidget* treeWidget;
    QTreeWidgetItem* getHeaders(TopLevelItem topLevelItem);
    void updateJeans();
public:
    ClothingItemsTabPage(QWidget* parent = nullptr);
    void updateOnly(TopLevelItem topLevelItem);
    void updateTableContent();
};


#endif //PRODUCT_TAB_H
