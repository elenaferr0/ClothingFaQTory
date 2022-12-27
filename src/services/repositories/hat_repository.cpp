#include "hat_repository.h"
#include "crud_repository.h"
#include <QSqlRecord>

using Services::HatRepository;

HatRepository* HatRepository::instance;

HatRepository::HatRepository()
        : Repository("hat"), CRUDRepository<Hat>("hat", EntityMapper::hat) {};


HatRepository* Services::HatRepository::getInstance() {
    if (instance == nullptr) {
        instance = new HatRepository();
    }
    return instance;
}
