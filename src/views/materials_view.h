
#ifndef MATERIALS_VIEW_H
#define MATERIALS_VIEW_H

#include <QGridLayout>
#include <memory>
#include <list>
#include "view_interface.h"

#include "../models/material.h"

using std::shared_ptr;
using Models::Material;
using std::list;

namespace Views {
    class MaterialsView : public ViewInterface {
    Q_OBJECT
        typedef list <shared_ptr<Material>> MaterialsList;
    public:
        MaterialsView(QWidget* parent = nullptr);

        void init(const MaterialsList&);

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
