

#ifndef HAT_MAPPER_H
#define HAT_MAPPER_H

#include "../../models/accessories/hat.h"
#include "mapper.h"
#include "material_mapper.h"
#include "size_mapper.h"

using Models::Accessories::Hat;

namespace Services {
    class HatMapper : public Mapper {
        private:
            MaterialMapper materialMapper;
            SizeMapper sizeMapper;
        public:
            Hat* operator()(const QSqlQuery& query) override;
    };
}


#endif //HAT_MAPPER_H
