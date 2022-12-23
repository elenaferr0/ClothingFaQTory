

#ifndef WIZARD_CONTROLLER_H
#define WIZARD_CONTROLLER_H

#include <QObject>
#include "controller.h"
#include "../services/repositories/material_repository.h"
#include "../services/repositories/size_repository.h"
#include "../services/repositories/hat_repository.h"
#include "../services/repositories/backpack_repository.h"
#include "../services/repositories/bracelet_repository.h"
#include "../services/repositories/vest_repository.h"
#include "../services/repositories/jeans_repository.h"
#include "../services/repositories/overalls_repository.h"
#include "../services/repositories/material_repository.h"
#include "../views/products_view.h"
#include "../views/main_view.h"
#include "controller.h"
#include "../services/repositories/size_repository.h"

using Services::HatRepository;
using Services::BraceletRepository;
using Services::BackPackRepository;
using Services::VestRepository;
using Services::JeansRepository;
using Services::OverallsRepository;
using Services::MaterialRepository;
using Services::SizeRepository;

namespace Controllers {
    class WizardController : public Controller {
        Q_OBJECT
        private:
            MaterialRepository* materialRepository;
            SizeRepository* sizeRepository;
            HatRepository* hatRepository;
            BraceletRepository* braceletRepository;
            BackPackRepository* backPackRepository;
            VestRepository* vestRepository;
            JeansRepository* jeansRepository;
            OverallsRepository* overallsRepository;

            void save(Jeans*);

            void save(Hat*);

            void save(Bracelet*);

            void save(BackPack*);

            void save(Vest*);

            void save(Overalls*);


        public:
            WizardController(View*);

            shared_ptr<Material> findMaterialByName(const QString&);

            shared_ptr<Size> findSizeByName(const QString&);

        public slots:

            void handleProductCreation(Product* product, Product::ProductType productType);
    };
}

#endif //WIZARD_CONTROLLER_H
