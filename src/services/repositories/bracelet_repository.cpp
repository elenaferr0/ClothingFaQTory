#include "bracelet_repository.h"
#include "../mappers/bracelet_mapper.h"

using Services::BraceletRepository;

BraceletRepository* BraceletRepository::instance;

BraceletRepository::BraceletRepository()
        : Repository("bracelet"), CRUDRepository("bracelet", new BraceletMapper()) {};

BraceletRepository* BraceletRepository::getInstance() {
    if (instance == nullptr) {
        instance = new BraceletRepository();
    }
    return instance;
}