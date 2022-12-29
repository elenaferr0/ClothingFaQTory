#include <QPainter>
#include <QPen>
#include "color_icon.h"

ColorIcon::ColorIcon(const string& hex) {
    const QColor color(QString::fromStdString(hex));
    pixmap = new QPixmap(COLOR_ICON_SIZE, COLOR_ICON_SIZE);
    pixmap->fill(color);
    QPainter painter(pixmap);
    QPen pen;
    pen.setWidth(3);
    pen.setColor(Qt::black);
    painter.setPen(pen);
    painter.drawRect(0, 0, COLOR_ICON_SIZE, COLOR_ICON_SIZE);
    this->addPixmap(*pixmap);
}

QPixmap* ColorIcon::getPixmap() const {
    return pixmap;
}
