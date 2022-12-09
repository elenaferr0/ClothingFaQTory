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
    public:
        MaterialRepository();

        Either<Error, Material> findById(int id) override;

        Either<Error, list<Material>> findAll() override;
    };
}
#endif // MATERIAL_REPOSITORY_H
