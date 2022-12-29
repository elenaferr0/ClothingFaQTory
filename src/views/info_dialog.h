

#ifndef INFO_DIALOG_H
#define INFO_DIALOG_H

#include "../models/product.h"
#include <QDialog>

using Models::Product;

class InfoDialog : public QDialog {
    public:
        InfoDialog(Product* product, QWidget* parent = nullptr);
};


#endif //INFO_DIALOG_H
