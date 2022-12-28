

#ifndef FILTER_H
#define FILTER_H

#include <QObject>
#include "../db/querybuilder.h"
#include "../../models/product.h"

using Models::Product;
using Core::Db::QueryBuilder;

namespace Core {
    class Filters {
        private:
            static QueryBuilder queryBuilder;

            typedef Product::ProductType PType;

            LinkedList<QString> productTypes;
            QString code;
            QPair<double, double> priceRange;
            QPair<QString, QueryBuilder::Order> orderByField;

        public:
            Filters(const LinkedList<QString>& productTypes = LinkedList<QString>(),
                    const QString& code = "",
                    const QPair<double, double>& priceRange = QPair(0, INT_MAX),
                    const QPair<QString, QueryBuilder::Order>& orderByField = QPair("code", QueryBuilder::ASC));

            Filters() = default;

            string createQuery();
    };

}

#endif //FILTER_H
