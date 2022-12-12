

#ifndef PRODUCT_MENU_H
#define PRODUCT_MENU_H

#include <QWidget>
#include <QTabWidget>
#include <QLabel>

class ProductMenu : public QWidget {
Q_OBJECT
private:
    QTabWidget* tabWidget;
public:
    ProductMenu(QWidget* parent = nullptr);
};


#endif //PRODUCT_MENU_H
