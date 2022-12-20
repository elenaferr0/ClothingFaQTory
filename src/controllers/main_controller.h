

#ifndef CONTROLLER_H
#define CONTROLLER_H

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

using Services::HatRepository;
using Services::BraceletRepository;
using Services::BackPackRepository;
using Services::VestRepository;
using Services::JeansRepository;
using Services::OverallsRepository;
using Services::MaterialRepository;
using Services::SizeRepository;

namespace Views {
    class MainView;
}

using Views::MainView;

namespace Controllers {

    class MainController : public QObject {
        Q_OBJECT
        typedef list<shared_ptr<Material>> MaterialsList;
        typedef list<shared_ptr<Size>> SizesList;
        typedef Map<Product::ProductType, list<shared_ptr<Product>>> ProductsMap;
    public:
        MainController(MainView*);

        ProductsMap findAllProductsByType();

        MaterialsList findAllMaterials();

        SizesList findAllSizes();

    private:
        MainView* view;
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
#endif //CONTROLLER_H
