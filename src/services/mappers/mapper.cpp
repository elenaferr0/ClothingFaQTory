#include "mapper.h"
#include <QDebug>

using Services::Mapper;

string Mapper::toString(const QSqlError::ErrorType& errorType) {
    switch (errorType) {
        case QSqlError::ConnectionError:
            return "Connection Error";
        case QSqlError::StatementError:
            return "Statement Error";
        case QSqlError::TransactionError:
            return "Transaction Error";
        case QSqlError::UnknownError:
            return "Unknown Error";
        default:
            return "";
    }
}

Services::Mapper::Mapper() : lastError(nullptr) {}

Services::Mapper::~Mapper() {
    delete lastError;
}

Error* Mapper::getAndResetError() {
    if (!lastError) {
        return nullptr;
    }
    Error* temp = lastError->clone();
    lastError = nullptr;
    return temp;
}

void Services::Mapper::checkQuery(const QSqlQuery& query) {
    if (query.size() == 0) {
        return;
    }

    if (query.lastError().isValid()) { // error occurred
        lastError = new Error(toString(query.lastError().type()), query.lastError().text().toStdString());
        return;
    }

}
