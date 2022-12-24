

#ifndef ICON_BUTTON_H
#define ICON_BUTTON_H

#include <QObject>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Views::Components { class IconButton; }
QT_END_NAMESPACE

class IconButton : public QPushButton {
    Q_OBJECT
    private:
        int data;
    public:
        IconButton(const QString& path, const QString& objName, int data, QWidget* parent);

    private slots:

        void handleClick(bool);

    signals:

        void clicked(int);
};


#endif //ICON_BUTTON_H
