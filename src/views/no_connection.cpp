

#include <QHBoxLayout>
#include "no_connection.h"

NoConnection::NoConnection(QWidget* parent)
        : QWidget(parent) {
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignCenter);

    QPixmap image(":assets/icons/no_connection.png");
    icon = new QLabel();
    icon->setPixmap(image.scaledToHeight(100));
    icon->setAlignment(Qt::AlignCenter);
    layout->addWidget(icon);
    message = new QLabel("Whoops! Something went wrong while connecting to the DB\nCheck your connection and retry");
    message->setAlignment(Qt::AlignCenter);
    layout->addWidget(message);
}
