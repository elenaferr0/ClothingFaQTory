

#ifndef INFO_DIALOG_H
#define INFO_DIALOG_H

#include "../models/product.h"
#include <memory>

using std::shared_ptr;

#include <QDialog>

using Models::Product;

class InfoDialog : public QDialog {
    public:
        InfoDialog(shared_ptr<Product> product, QWidget* parent = nullptr);
};


#endif //INFO_DIALOG_H
