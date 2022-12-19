

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
#include "view.h"

using Services::HatRepository;
using Services::BraceletRepository;
using Services::BackPackRepository;
using Services::VestRepository;
using Services::JeansRepository;
using Services::OverallsRepository;
using Services::MaterialRepository;
using Services::SizeRepository;

namespace Core {
    class Controller {
        typedef list<shared_ptr<Material>> MaterialsList;
        typedef list<shared_ptr<Size>> SizesList;
        typedef Map<Product::ProductType, list<shared_ptr<Material>>> ProductsMap;
    public:
        Controller();

    private:
        Error* lastError;
        View* view;
        HatRepository* hatRepository;
        BraceletRepository* braceletRepository;
        BackPackRepository* backPackRepository;
        VestRepository* vestRepository;
        JeansRepository* jeansRepository;
        OverallsRepository* overallsRepository;
        SizeRepository* sizeRepository;
        MaterialRepository* materialRepository;

        MaterialsList findAllMaterials();

        SizesList findAllSizes();

        Error* getLastError() const;

        template<class T>
        void findProductsOfType(Product::ProductType productType, ReadOnlyRepository<T>* repository, ProductsMap& map);

    };
}
#endif //CONTROLLER_H
