#include "bracelet_repository.h"

using Services::BraceletRepository;

BraceletRepository* BraceletRepository::instance;

BraceletRepository::BraceletRepository()
        : Repository("bracelet"), CRUDRepository("bracelet", EntityMapper::bracelet) {};

BraceletRepository* BraceletRepository::getInstance() {
    if (instance == nullptr) {
        instance = new BraceletRepository();
    }
    return instance;
}