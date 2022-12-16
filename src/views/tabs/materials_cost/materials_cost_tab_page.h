#ifndef MATERIALS_COST_TAB_PAGE_H
#define MATERIALS_COST_TAB_PAGE_H
#include <QWidget>
#include <QGridLayout>
#include "../../../services/repositories/material_repository.h"

using Services::MaterialRepository;

QT_BEGIN_NAMESPACE
namespace Views::Tabs { class MaterialsCostTabPage; }
QT_END_NAMESPACE

class MaterialsCostTabPage : public QWidget {
    Q_OBJECT
private:
    MaterialRepository* materialRepository;
    QGridLayout* gridLayout;
    static int COLUMN_COUNT;
    void createGrid();
public:
    MaterialsCostTabPage(QWidget* parent = nullptr);
    void updateGrid();
};


#endif //MATERIALS_COST_TAB_PAGE_H
