#include "jeans_repository.h"
#include "crud_repository.h"
#include <QSqlRecord>

using Services::JeansRepository;

JeansRepository* JeansRepository::instance;

JeansRepository::JeansRepository()
        : Repository("jeans"), CRUDRepository("jeans", EntityMapper::jeans) {};

JeansRepository* Services::JeansRepository::getInstance() {
    if (instance == nullptr) {
        instance = new JeansRepository();
    }
    return instance;
}
