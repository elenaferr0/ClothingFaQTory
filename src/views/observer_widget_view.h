

#ifndef VIEW_INTERFACE_H
#define VIEW_INTERFACE_H


#include <QWidget>
#include "../core/observer_interface.h"
#include "view.h"

using Core::ObserverInterface;

namespace Views {
    class ObserverWidgetView : public QWidget, public ObserverInterface, public View {
        Q_OBJECT
        public:
            explicit ObserverWidgetView(QWidget* parent = nullptr);

            virtual ~ObserverWidgetView() = default;
    };

}


#endif //VIEW_INTERFACE_H
