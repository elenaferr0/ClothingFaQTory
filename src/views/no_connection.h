

#ifndef NO_CONNECTION_H
#define NO_CONNECTION_H

#include <QWidget>
#include <QLabel>

namespace Views {
    class NoConnection : public QWidget {
    Q_OBJECT

    public:
        NoConnection(QWidget* parent = nullptr);
    };
}

#endif //NO_CONNECTION_H
