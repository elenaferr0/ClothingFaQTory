

#ifndef MATERIAL_ICON_BUTTON_H
#define MATERIAL_ICON_BUTTON_H


#include <QToolButton>
#include "../../models/material.h"


using std::shared_ptr;
QT_BEGIN_NAMESPACE
namespace Views::Components { class MaterialIconButton; };
QT_END_NAMESPACE


class MaterialIconButton : public QToolButton {
    Q_OBJECT
    private:
        shared_ptr<Material> material;
    public:
        MaterialIconButton(shared_ptr<Material> material, QWidget* parent = nullptr);

    private slots:

        void handleClick(bool);

    signals:

        void clicked(shared_ptr<Material>);
};


#endif //MATERIAL_ICON_BUTTON_H
