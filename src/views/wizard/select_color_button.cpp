

#include "select_color_button.h"
#include <QColorDialog>

SelectColorButton::SelectColorButton(QWidget* parent, const QString& text)
        : QPushButton(parent) {
    connect(this, SIGNAL(clicked()), this, SLOT(changeColor()));
    connect(this, SIGNAL(clicked()), this, SLOT(updateColor()));
    setText(text);
}

void SelectColorButton::updateColor() {
    setStyleSheet("background-color: " + color.name());
}

void SelectColorButton::changeColor() {
    QColor newColor = QColorDialog::getColor(color, parentWidget());
    if (newColor != color) {
        setColor(newColor);
    }
}

void SelectColorButton::setColor(const QColor& color) {
    this->color = color;
    updateColor();
}

const QColor& SelectColorButton::getColor() const {
    return color;
}