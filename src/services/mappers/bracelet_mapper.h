

#ifndef _BRACELET_MAPPER_H
#define _BRACELET_MAPPER_H

#include "mapper.h"
#include "../../models/accessories/bracelet.h"
#include "material_mapper.h"
#include "size_mapper.h"

using Models::Accessories::Bracelet;

namespace Services {
    class BraceletMapper : public Mapper {
        private:
            MaterialMapper materialMapper;
            SizeMapper sizeMapper;
        public:
            Bracelet* operator()(const QSqlQuery& query) override;
    };

}


#endif //_BRACELET_MAPPER_H
