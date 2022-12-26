

#ifndef MATERIAL_ICON_BUTTON_H
#define MATERIAL_ICON_BUTTON_H


#include <QToolButton>
#include "../../models/material.h"

QT_BEGIN_NAMESPACE
namespace Components { class MaterialIconButton; };
QT_END_NAMESPACE


class MaterialIconButton : public QToolButton {
    Q_OBJECT
    private:
        Material* material;
    public:
        MaterialIconButton(Material* material, QWidget* parent = nullptr);

    private slots:

        void handleClick(bool);

    signals:

        void clicked(Material*);
};


#endif //MATERIAL_ICON_BUTTON_H
