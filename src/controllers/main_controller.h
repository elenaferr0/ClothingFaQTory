

#ifndef MAIN_CONTROLLER_H
#define MAIN_CONTROLLER_H

#include <QObject>
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
using Services::DeleteOnlyRepository;

namespace Views {
    class View;
}

using Views::View;

namespace Controllers {

    class MainController : public Controller {
        Q_OBJECT
            typedef LinkedList<shared_ptr<Material>> MaterialsList;
            typedef Map<Product::ProductType, LinkedList<shared_ptr<Product>>> ProductsMap;
            typedef LinkedList<shared_ptr<Size>> SizesList;
        public:
            MainController(View*);

            ProductsMap findAllProductsByType(Filters* filters = nullptr);

            MaterialsList findAllMaterials();

            SizesList findAllSizes();

            void deleteProductById(int id);

            void saveCostPerUnit(shared_ptr<Material> material);

        private:
            HatRepository* hatRepository;
            SizeRepository* sizeRepository;
            BraceletRepository* braceletRepository;
            BackPackRepository* backPackRepository;
            VestRepository* vestRepository;
            JeansRepository* jeansRepository;
            OverallsRepository* overallsRepository;
            MaterialRepository* materialRepository;
            DeleteOnlyRepository* productRepository;

            template<class T>
            void findAllProductsByTypeHelper(Product::ProductType productType,
                                             CRUDRepository<T>* repository,
                                             ProductsMap& map,
                                             Filters* filters = nullptr);

    };
}
#endif //MAIN_CONTROLLER_H
