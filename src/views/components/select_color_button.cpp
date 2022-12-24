

#include "select_color_button.h"
#include <QColorDialog>

int SelectColorButton::LIGHTNESS_THRESHOLD = 186;

SelectColorButton::SelectColorButton(QWidget* parent, const QString& title)
        : QPushButton(parent) {
    connect(this, SIGNAL(clicked()), this, SLOT(updateColor()));
    connect(this, SIGNAL(clicked()), this, SLOT(updateBackground()));
    QPushButton::setText(title);
}

void SelectColorButton::updateBackground() {
    if (color.lightness() < LIGHTNESS_THRESHOLD) {
        setStyleSheet("color: white; background-color: " + color.name());
    } else {
        setStyleSheet("color: black; background-color: " + color.name());
    }
}

void SelectColorButton::updateColor() {
    QColor newColor = QColorDialog::getColor(color, parentWidget());
    if (newColor != color) {
        setColor(newColor);
        emit colorChanged(newColor.name());
    }
}

void SelectColorButton::setColor(const QColor& color) {
    this->color = color;
    updateBackground();
}

const QColor& SelectColorButton::getColor() const {
    return color;
}

QString SelectColorButton::getHex() const {
    return color.name();
}