

#ifndef JEANS_MAPPER_H
#define JEANS_MAPPER_H

#include "mapper.h"
#include "../../models/clothing_items/jeans.h"
#include "material_mapper.h"
#include "size_mapper.h"

using Models::ClothingItems::Jeans;

namespace Services {

    class JeansMapper : public Mapper {
        private:
            MaterialMapper materialMapper;
            SizeMapper sizeMapper;
        public:
            Jeans* operator()(const QSqlQuery& query) override;
    };

}

#endif //JEANS_MAPPER_H
