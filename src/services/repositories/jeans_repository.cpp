#include "jeans_repository.h"
#include "crud_repository.h"
#include "../mappers/jeans_mapper.h"
#include <QSqlRecord>

using Services::JeansRepository;

JeansRepository* JeansRepository::instance;

JeansRepository::JeansRepository()
        : Repository("jeans"), CRUDRepository("jeans", new JeansMapper()) {};

JeansRepository* Services::JeansRepository::getInstance() {
    if (instance == nullptr) {
        instance = new JeansRepository();
    }
    return instance;
}
