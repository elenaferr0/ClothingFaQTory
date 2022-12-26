

#include "material_icon_button.h"

MaterialIconButton::MaterialIconButton(Material* material, QWidget* parent) :
        QToolButton(parent), material(material) {
    connect(this, SIGNAL(clicked(bool)), this, SLOT(handleClick(bool)));

}

void MaterialIconButton::handleClick(bool) {
    emit clicked(material);
}
