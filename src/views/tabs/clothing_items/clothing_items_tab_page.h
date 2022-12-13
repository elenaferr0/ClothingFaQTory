
#ifndef PRODUCT_TAB_H
#define PRODUCT_TAB_H

#include <QWidget>
#include <QLabel>
#include <QTableWidget>
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
    JeansRepository* jeansRepository;
    VestRepository* vestRepository;
    OverallsRepository* overallsRepository;

    QTableWidget* table;

    void updateTableContent();

public:
    ClothingItemsTabPage(QWidget* parent = nullptr);
};


#endif //PRODUCT_TAB_H
