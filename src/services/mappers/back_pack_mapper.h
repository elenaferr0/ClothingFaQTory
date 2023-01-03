

#ifndef BACK_PACK_MAPPER_H
#define BACK_PACK_MAPPER_H

#include "mapper.h"
#include "../../models/accessories/backpack.h"
#include "size_mapper.h"
#include "material_mapper.h"

using Models::Accessories::BackPack;

namespace Services {
    class BackPackMapper : public Mapper {
        private:
            MaterialMapper materialMapper;
            SizeMapper sizeMapper;
        public:
            BackPack* operator()(const QSqlQuery& query) override;
    };

}


#endif //BACK_PACK_MAPPER_H
