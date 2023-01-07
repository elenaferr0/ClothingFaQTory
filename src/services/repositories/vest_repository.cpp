#include "vest_repository.h"
#include "crud_repository.h"
#include "../mappers/vest_mapper.h"
#include <QSqlRecord>

using Services::VestRepository;

VestRepository* VestRepository::instance;

VestRepository::VestRepository()
        : Repository("vest"), CRUDRepository("vest", new VestMapper()) {};

VestRepository* VestRepository::getInstance() {
    if (instance == nullptr) {
        instance = new VestRepository();
    }
    return instance;
}