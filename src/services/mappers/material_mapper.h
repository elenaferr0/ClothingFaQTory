

#ifndef MATERIAL_MAPPER_H
#define MATERIAL_MAPPER_H

#include "../../models/material.h"
#include "mapper.h"

using Models::Material;

namespace Services {
    class MaterialMapper : public Mapper {
        public:
            Material* operator()(const QSqlQuery& query) override;

            Material fromRecord(const QSqlRecord& record) const;
    };

}
#endif //MATERIAL_MAPPER_H
