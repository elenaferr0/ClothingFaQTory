

#ifndef PRODUCT_TYPE_BUTTON_H
#define PRODUCT_TYPE_BUTTON_H


#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Views { class ProductTypeButton; }
QT_END_NAMESPACE

class ProductTypeButton : public QPushButton {
Q_OBJECT
private:
    int productType;
public:
    ProductTypeButton(int productType = -1, QWidget* parent = nullptr);

signals:
    void clicked(int);
private slots:
    void handleClick(bool);
};


#endif //PRODUCT_TYPE_BUTTON_H
