#ifndef MATERIAL_REPOSITORY_H
#define MATERIAL_REPOSITORY_H
#include "src/models/material.h"
#include "src/core/errors/either.h"
#include "src/core/errors/error.h"
#include "src/services/repositories/repository.h"

using Core::Either;
using Core::Error;
using Models::Material;
using Services::Repository;

namespace Services{
class MaterialRepository : public Repository<Material> {
public:
    MaterialRepository();

    Either <Error, Material> save(Material& entity) override;

    Either <Error, list<Material>> saveAll(list <Material>& entities) override;

    optional <Error> deleteT(const Material& entity) override;

    Either <Error, Material> findById(int id) override;

    Either <Error, list<Material>> findAll() override;
};
}
#endif // MATERIAL_REPOSITORY_H
