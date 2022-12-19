#ifndef SELECT_COLOR_BUTTON_H
#define SELECT_COLOR_BUTTON_H


#include <QPushButton>
#include <QColor>

QT_BEGIN_NAMESPACE
namespace Views::Wizard { class SelectColorButton; }
QT_END_NAMESPACE

class SelectColorButton : public QPushButton {
Q_OBJECT
public:
    SelectColorButton(QWidget* parent = nullptr, const QString& = "");

    void setColor(const QColor& color);

    const QColor& getColor() const;

public slots:

    void updateColor();

    void changeColor();

private:
    static int LIGHTNESS_THRESHOLD;
    QColor color;
};

#endif //SELECT_COLOR_BUTTON_H
