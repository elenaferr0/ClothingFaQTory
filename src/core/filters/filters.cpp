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

string Core::Filters::createQuery() {
    code = "%" + code + "%";

    return queryBuilder.select("*")
            .from("product")
            .join(QueryBuilder::RIGHT, "{table}", Expr("{table}.id").equals({"product.id"}))
            .where(Expr("code").ilike(code.toStdString()))
            .orderBy(orderByField.first.toStdString(), orderByField.second)
            .build();

}
