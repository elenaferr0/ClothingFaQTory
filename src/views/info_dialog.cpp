
#include "info_dialog_visitor.h"
#include "info_dialog.h"

using Views::InfoDialogVisitor;

InfoDialog::InfoDialog(shared_ptr<Product> product, QWidget* parent) : QDialog(parent) {
    resize(300, 200);
    setWindowTitle("Product info");
    InfoDialogVisitor infoDialogVisitor;
    product->accept(infoDialogVisitor);
    setLayout(infoDialogVisitor.getLayout());
}
