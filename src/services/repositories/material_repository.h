#ifndef MATERIAL_REPOSITORY_H
#define MATERIAL_REPOSITORY_H

#include "../../models/material.h"
#include "../../core/errors/error.h"
#include "../../core/errors/either.h"
#include "../../models/material.h"
#include "readonly_repository.h"

using Core::Either;
using Core::Error;
using Models::Material;
using Services::ReadOnlyRepository;

namespace Services {
    class MaterialRepository : public ReadOnlyRepository<Material> {
        private:
            MaterialRepository();

        protected:
            static MaterialRepository* instance;
            Map<int, shared_ptr<Material>> cachedMaterials; // not static since there's only one instance

        public:
            static MaterialRepository* getInstance();

            Either<Error, shared_ptr<Material>> findByName(const Material::Name&);

            Either<Error, shared_ptr<Material>> saveCostPerUnit(const Material&);

            Either<Error, shared_ptr<Material>> findById(int id) override;

            Either<Error, list<shared_ptr<Material>>> findAll() override;

    };
}
#endif // MATERIAL_REPOSITORY_H
