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
    protected:
        MaterialRepository();

        static MaterialRepository* instance;

        Map<int, Material> materials; // is not static since there's only an instance

    public:
        MaterialRepository(MaterialRepository&) = delete;

        void operator=(const MaterialRepository&) = delete;

        Either<Error, Material> findById(int id) override;

        Either<Error, Material> findByName(const Material::Name&);

        Either<Error, list<Material>> findAll() override;

        static MaterialRepository* getInstance();

    };
}
#endif // MATERIAL_REPOSITORY_H
