

#ifndef EDIT_MATERIAL_COST_DIALOG_H
#define EDIT_MATERIAL_COST_DIALOG_H


#include <QDialog>
#include "../../models/material.h"

class EditMaterialCostDialog : public QDialog {
    public:
        EditMaterialCostDialog(Material* material, QWidget* parent = nullptr);

};


#endif //EDIT_MATERIAL_COST_DIALOG_H
