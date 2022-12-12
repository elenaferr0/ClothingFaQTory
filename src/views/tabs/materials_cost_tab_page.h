#ifndef MATERIALS_COST_TAB_PAGE_H
#define MATERIALS_COST_TAB_PAGE_H
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Views::Tabs { class MaterialsCostTabPage; }
QT_END_NAMESPACE

class MaterialsCostTabPage : public QWidget {
    Q_OBJECT
private:
public:
    MaterialsCostTabPage(QWidget* parent = nullptr);
};


#endif //MATERIALS_COST_TAB_PAGE_H
