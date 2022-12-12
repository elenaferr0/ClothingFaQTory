

#ifndef NO_CONNECTION_H
#define NO_CONNECTION_H

#include <QWidget>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Views { class NoConnection; };
QT_END_NAMESPACE

class NoConnection : public QWidget {
Q_OBJECT

private:
    QLabel* icon;
    QLabel* message;

public:
    NoConnection(QWidget* parent = nullptr);
};


#endif //NO_CONNECTION_H
