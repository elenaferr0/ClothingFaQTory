

#ifndef FILTER_H
#define FILTER_H

#include <QObject>
#include "../db/querybuilder.h"
#include "../../models/product.h"

using Models::Product;
using Core::Db::QueryBuilder;

namespace Core {
    class Filter {
        private:
            static QueryBuilder queryBuilder;
            typedef Product::ProductType PType;

            LinkedList<string> productTypeNames;
            QString code;
            QPair<double, double> priceRange;
            QPair<QString, QueryBuilder::Order> orderByField;

        public:
            Filter(const LinkedList<PType>& productTypes,
                   const QString& code,
                   const QPair<double, double>& priceRange = QPair(0, INT_MAX),
                   const QPair<QString, QueryBuilder::Order>& orderByField = QPair("code", QueryBuilder::ASC));

            Filter() = default;

            string createQuery();
    };

}

#endif //FILTER_H
