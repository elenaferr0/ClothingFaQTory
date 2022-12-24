

#include "icon_button.h"

IconButton::IconButton(const QString& path, const QString& objName, int data, QWidget* parent)
        : QPushButton(parent), data(data) {
    connect(this, SIGNAL(clicked(bool)), this, SLOT(handleClick(bool)));
    setIcon(QIcon(path));
    setObjectName(objName);
    setIconSize(QSize(25, 25));
}

void IconButton::handleClick(bool) {
    emit clicked(data);
}

