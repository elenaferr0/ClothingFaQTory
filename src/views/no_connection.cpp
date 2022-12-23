

#include <QHBoxLayout>
#include "no_connection.h"

using Views::NoConnection;

NoConnection::NoConnection(QWidget* parent)
        : QWidget(parent) {
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignCenter);

    QPixmap image(":assets/icons/no_connection.png");
    QLabel* icon = new QLabel();
    icon->setPixmap(image.scaledToHeight(80));
    icon->setAlignment(Qt::AlignCenter);
    layout->addWidget(icon);
    QLabel* title = new QLabel("Whoops! Something went wrong while connecting to the DB");
    QFont font = title->font();
    font.setBold(true);
    font.setPointSize(18);
    title->setFont(font);
    title->setAlignment(Qt::AlignCenter);
    layout->addWidget(title);

    QLabel* message = new QLabel(
            "Keep in mind that if your network has some restrictions, ClothingFaQTory might not work.\n"
            "If the problem persists, try with another network"
    );

    message->setAlignment(Qt::AlignCenter);
    font = message->font();
    font.setPointSize(14);
    message->setFont(font);
    layout->addWidget(message);
}
