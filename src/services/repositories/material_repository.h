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
            Map<int, Material*> cachedMaterials; // not static since there's only one instance

        public:
            static MaterialRepository* getInstance();

            Either<Error, Material*> findByName(const Material::Name&);

            Either<Error, Material*> saveCostPerUnit(Material*);

            Either<Error, Material*> findById(int id) override;

            Either<Error, list<Material*>> findAll() override;

            ~MaterialRepository();

    };
}
#endif // MATERIAL_REPOSITORY_H
