
#ifndef MATERIALS_VIEW_H
#define MATERIALS_VIEW_H

#include <QGridLayout>
#include <list>
#include "observer_widget_view.h"
#include "../controllers/main_controller.h"
#include "main_view.h"
#include "../models/material.h"

using Models::Material;
using std::list;

namespace Views {
    class MainView;

    class MaterialsView : public ObserverWidgetView {
        Q_OBJECT
            typedef list<Material*> MaterialsList;
        public:
            MaterialsView(MainView* mainView, QWidget* parent = nullptr);

            void init();

        private:
            QGridLayout* gridLayout;
            static int COLUMN_COUNT;
            MaterialsList materials;

            void initGrid();

        public:
            void notify(Model* model) override;
    };
}


#endif //MATERIALS_VIEW_H
