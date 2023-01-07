

#ifndef SIZE_MAPPER_H
#define SIZE_MAPPER_H

#include "../../models/size.h"
#include "mapper.h"

using Models::Size;

namespace Services {
    class SizeMapper : public Mapper {
        public:
            Size* operator()(const QSqlQuery& query) override;

            Size fromRecord(const QSqlRecord& record) const;
    };
}

#endif //SIZE_MAPPER_H
