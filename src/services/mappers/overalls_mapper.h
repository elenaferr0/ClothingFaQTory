

#ifndef OVERALLS_MAPPER_H
#define OVERALLS_MAPPER_H

#include "mapper.h"
#include "../../models/clothing_items/overalls.h"
#include "material_mapper.h"
#include "size_mapper.h"

using Models::ClothingItems::Overalls;

namespace Services {

    class OverallsMapper : public Mapper {
        private:
            MaterialMapper materialMapper;
            SizeMapper sizeMapper;
        public:
            Overalls* operator()(const QSqlQuery& query) override;
    };

}

#endif //OVERALLS_MAPPER_H
