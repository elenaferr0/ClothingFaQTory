

#ifndef VIEW_INTERFACE_H
#define VIEW_INTERFACE_H


#include <QWidget>
#include "view.h"

namespace Views {
    class WidgetViewParent : public QWidget, public View {
        Q_OBJECT
        public:
            explicit WidgetViewParent(QWidget* parent = nullptr);

            virtual ~WidgetViewParent() = default;
    };

}


#endif //VIEW_INTERFACE_H
