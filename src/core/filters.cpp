#include <algorithm>
#include "filters.h"

using Core::Filters;
using std::for_each;

QueryBuilder Filters::queryBuilder = QueryBuilder();

Core::Filters::Filters(const LinkedList<QString>& productTypes, const QString& code,
                       const QPair<double, double>& priceRange, const QPair<QString, QueryBuilder::Order>& orderByField)
        : code(code),
          priceRange(priceRange),
          productTypes(productTypes),
          orderByField(orderByField) {
}

const LinkedList<QString>& Core::Filters::getProductTypes() const {
    return productTypes;
}

const QString& Core::Filters::getCode() const {
    return code;
}

const QPair<double, double>& Core::Filters::getPriceRange() const {
    return priceRange;
}

const QPair<QString, QueryBuilder::Order>& Core::Filters::getOrderByField() const {
    return orderByField;
}