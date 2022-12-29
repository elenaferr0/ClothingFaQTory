

#include <QVBoxLayout>
#include "empty_state.h"

EmptyState::EmptyState(QWidget* parent) : QWidget(parent) {
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setMargin(30);
    layout->setSpacing(30);

    QLabel* image = new QLabel;
    image->setAlignment(Qt::AlignCenter);
    QPixmap pixmap(":/assets/empty_state.svg");
    image->setPixmap(pixmap.scaledToHeight(200));
    layout->addWidget(image);

    QLabel* text = new QLabel("No product was found");
    QFont* font = new QFont;
    font->setPointSize(13);
    font->setBold(true);
    text->setFont(*font);
    text->setAlignment(Qt::AlignCenter);
    layout->addWidget(text);

}
