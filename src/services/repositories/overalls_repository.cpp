#include "overalls_repository.h"
#include "crud_repository.h"
#include "../mappers/overalls_mapper.h"
#include <QSqlRecord>

using Services::OverallsRepository;

OverallsRepository* OverallsRepository::instance;

OverallsRepository::OverallsRepository()
        : Repository("overalls"), CRUDRepository("overalls", new OverallsMapper()) {};


OverallsRepository* OverallsRepository::getInstance() {
    if (instance == nullptr) {
        instance = new OverallsRepository();
    }
    return instance;
}