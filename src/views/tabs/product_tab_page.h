
#ifndef PRODUCT_TAB_H
#define PRODUCT_TAB_H
#include <QWidget>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Views::Tabs { class ProductTabPage; }
QT_END_NAMESPACE

class ProductTabPage : public QWidget {
Q_OBJECT
private:
public:
    ProductTabPage(QWidget* parent = nullptr);
};


#endif //PRODUCT_TAB_H
