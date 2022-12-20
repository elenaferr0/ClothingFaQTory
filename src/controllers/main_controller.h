

#ifndef MAIN_CONTROLLER_H
#define MAIN_CONTROLLER_H

#include "../services/repositories/hat_repository.h"
#include "../services/repositories/backpack_repository.h"
#include "../services/repositories/bracelet_repository.h"
#include "../services/repositories/vest_repository.h"
#include "../services/repositories/jeans_repository.h"
#include "../services/repositories/overalls_repository.h"
#include "../services/repositories/material_repository.h"
#include "../services/repositories/size_repository.h"
#include "../views/products_view.h"
#include "../views/main_view.h"
#include "controller.h"

using Services::HatRepository;
using Services::BraceletRepository;
using Services::BackPackRepository;
using Services::VestRepository;
using Services::JeansRepository;
using Services::OverallsRepository;
using Services::MaterialRepository;
using Services::SizeRepository;

namespace Views {
    class View;
}

using Views::View;

namespace Controllers {

    class MainController : public Controller {
        Q_OBJECT
            typedef list<shared_ptr<Material>> MaterialsList;
            typedef list<shared_ptr<Size>> SizesList;
            typedef Map<Product::ProductType, list<shared_ptr<Product>>> ProductsMap;
        public:
            MainController(View*);

            ProductsMap findAllProductsByType();

            MaterialsList findAllMaterials();

            SizesList findAllSizes();

        private:
            HatRepository* hatRepository;
            BraceletRepository* braceletRepository;
            BackPackRepository* backPackRepository;
            VestRepository* vestRepository;
            JeansRepository* jeansRepository;
            OverallsRepository* overallsRepository;
            SizeRepository* sizeRepository;
            MaterialRepository* materialRepository;


            template<class T>
            void findProductsOfType(Product::ProductType productType, CRUDRepository<T>* repository, ProductsMap& map);

        signals:

            void databaseError(Error*);
    };
}
#endif //MAIN_CONTROLLER_H
