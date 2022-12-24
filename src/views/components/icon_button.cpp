
#include <QTreeWidgetItem>
#include "icon_button.h"

IconButton::IconButton(const QString& path, const QString& objName, int data, QTreeWidgetItem* row, QWidget* parent)
        : QPushButton(parent), data(data) {
    connect(this, SIGNAL(clicked(bool)), this, SLOT(handleClick(bool)));
    setIcon(QIcon(path));
    setObjectName(objName);
    setIconSize(QSize(25, 25));
}

void IconButton::handleClick(bool) {
    emit clicked(data);
}

void IconButton::handleClick(QTreeWidgetItem*) {
    emit clicked(row);

}

