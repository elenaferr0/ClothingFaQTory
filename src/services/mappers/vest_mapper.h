

#ifndef VEST_MAPPER_H
#define VEST_MAPPER_H

#include "mapper.h"
#include "../../models/clothing_items/vest.h"
#include "size_mapper.h"
#include "material_mapper.h"

using Models::ClothingItems::Vest;
namespace Services {
    class VestMapper : public Mapper {
        private:
            MaterialMapper materialMapper;
            SizeMapper sizeMapper;
        public:
            Vest* operator()(const QSqlQuery& query) override;
    };

}

#endif //VEST_MAPPER_H
