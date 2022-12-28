#include <algorithm>
#include "filter.h"

using Core::Filter;
using std::for_each;

QueryBuilder Filter::queryBuilder = QueryBuilder();

Core::Filter::Filter(const LinkedList<PType>& productTypes, const QString& code,
                     const QPair<double, double>& priceRange, const QPair<QString, QueryBuilder::Order>& orderByField)
        : code(code),
          priceRange(priceRange),
          orderByField(orderByField) {
    for (auto p = productTypes.begin(); p != productTypes.end(); p++) {
        productTypeNames.pushBack(Product::productTypeToString(*p));
    }
}

string Core::Filter::createQuery() {
    code = "%" + code + "%";

    return queryBuilder.select("*")
            .from("product")
            .join(QueryBuilder::RIGHT, "{table}", Expr("{table}.id").equals({"product.id"}))
            .where(Expr("code").ilike(code.toStdString()))
            .orderBy(orderByField.first.toStdString(), orderByField.second)
            .build();

}
