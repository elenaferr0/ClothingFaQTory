#include "delete_only_repository.h"

using Services::DeleteOnlyRepository;
DeleteOnlyRepository* DeleteOnlyRepository::instance;

optional<Error> DeleteOnlyRepository::deleteById(int id) {
    string sql = Repository::queryBuilder.deleteT()
            .from(table)
            .where(Expr("id").equals({"?"}))
            .build();

    QSqlQuery query = Repository::exec(sql, QVariant::fromValue<int>(id));
    query.next();

    optional<Error> hasError = Repository::hasError(query);

    if (hasError.has_value()) {
        qCritical() << QString::fromStdString(
                hasError.value().getCause());
    }
    return hasError;
}

DeleteOnlyRepository::DeleteOnlyRepository(const string& table) : Repository(table) {}

DeleteOnlyRepository* DeleteOnlyRepository::getInstance(const string& table) {
    if (instance == nullptr) {
        instance = new DeleteOnlyRepository(table);
    }
    return instance;
}
