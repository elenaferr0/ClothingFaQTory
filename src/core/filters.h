

#ifndef FILTER_H
#define FILTER_H

#include <QObject>
#include "db/querybuilder.h"
#include "../models/product.h"

using Models::Product;
using Core::Db::QueryBuilder;

namespace Core {
    class Filters {
        private:
            static QueryBuilder queryBuilder;

            QString code;
            QPair<double, double> priceRange;
            LinkedList<QString> productTypes;
            QPair<QString, QueryBuilder::Order> orderByField;

        public:
            Filters(const LinkedList<QString>& productTypes = LinkedList<QString>(),
                    const QString& code = "",
                    const QPair<double, double>& priceRange = QPair(0, INT_MAX),
                    const QPair<QString, QueryBuilder::Order>& orderByField = QPair("", QueryBuilder::ASC));

            Filters() = default;

            const LinkedList<QString>& getProductTypes() const;

            const QString& getCode() const;

            const QPair<double, double>& getPriceRange() const;

            const QPair<QString, QueryBuilder::Order>& getOrderByField() const;
    };

}

#endif //FILTER_H
