

#ifndef EDIT_MATERIAL_COST_DIALOG_H
#define EDIT_MATERIAL_COST_DIALOG_H


#include <QMessageBox>
#include "../../models/material.h"


using std::shared_ptr;

QT_BEGIN_NAMESPACE
namespace Views::Components { class EditMaterialCostMessageBox; };
QT_END_NAMESPACE

class EditMaterialCostMessageBox : public QDialog {
    Q_OBJECT
    private:
        shared_ptr<Material> material;
    public:
        EditMaterialCostMessageBox(shared_ptr<Material> material, QWidget* parent = nullptr);

    private slots:

        void handleTextChanged(const QString&);
};


#endif //EDIT_MATERIAL_COST_DIALOG_H
