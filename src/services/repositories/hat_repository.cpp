#include "hat_repository.h"
#include "crud_repository.h"
#include "../mappers/hat_mapper.h"
#include <QSqlRecord>

using Services::HatRepository;

HatRepository* HatRepository::instance;

HatRepository::HatRepository()
        : Repository("hat"), CRUDRepository<Hat>("hat", new HatMapper()) {};


HatRepository* Services::HatRepository::getInstance() {
    if (instance == nullptr) {
        instance = new HatRepository();
    }
    return instance;
}
