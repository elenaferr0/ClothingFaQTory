

#include "material_icon_button.h"

MaterialIconButton::MaterialIconButton(Material* material, int row, int col, QWidget* parent) :
        material(material),
        row(row),
        col(col),
        QToolButton(parent) {
    connect(this, SIGNAL(clicked(bool)), this, SLOT(handleClick(bool)));

}

void MaterialIconButton::handleClick(bool) {
    emit clicked(material, row, col);
}
