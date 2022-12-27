#include "overalls_repository.h"
#include "crud_repository.h"
#include <QSqlRecord>

using Services::OverallsRepository;

OverallsRepository* OverallsRepository::instance;

OverallsRepository::OverallsRepository()
        : Repository("overalls"), CRUDRepository("overalls", EntityMapper::overalls) {};


OverallsRepository* OverallsRepository::getInstance() {
    if (instance == nullptr) {
        instance = new OverallsRepository();
    }
    return instance;
}