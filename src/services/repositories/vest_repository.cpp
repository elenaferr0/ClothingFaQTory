#include "vest_repository.h"
#include "crud_repository.h"
#include <QSqlRecord>

using Services::VestRepository;

VestRepository* VestRepository::instance;

VestRepository::VestRepository()
        : Repository("vest"), CRUDRepository("vest", EntityMapper::vest) {};

VestRepository* VestRepository::getInstance() {
    if (instance == nullptr) {
        instance = new VestRepository();
    }
    return instance;
}