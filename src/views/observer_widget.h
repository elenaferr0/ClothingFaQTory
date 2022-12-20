

#ifndef VIEW_INTERFACE_H
#define VIEW_INTERFACE_H


#include <QWidget>
#include "../core/observer_interface.h"

using Core::ObserverInterface;

namespace Views {
    class ObserverWidget : public QWidget, public ObserverInterface {
        Q_OBJECT
        public:
            explicit ObserverWidget(QWidget* parent = nullptr);

            virtual ~ObserverWidget() = default;
    };

}


#endif //VIEW_INTERFACE_H
