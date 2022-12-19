

#ifndef VIEW_INTERFACE_H
#define VIEW_INTERFACE_H


#include <QWidget>
#include "../core/observer_interface.h"

using Core::ObserverInterface;

namespace Views {
    class ViewInterface : public QWidget, public ObserverInterface {
    Q_OBJECT
    public:
        explicit ViewInterface(QWidget* parent = nullptr);

        virtual ~ViewInterface() = default;

    public:
        virtual void init() = 0;
    };

}


#endif //VIEW_INTERFACE_H
