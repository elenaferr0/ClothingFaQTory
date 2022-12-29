

#ifndef EMPTY_STATE_H
#define EMPTY_STATE_H


#include <QWidget>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Views::Components { class EmptyState; };
QT_END_NAMESPACE

class EmptyState : public QWidget {
    Q_OBJECT
    public:
        EmptyState(QWidget* parent = nullptr);
};


#endif //EMPTY_STATE_H
