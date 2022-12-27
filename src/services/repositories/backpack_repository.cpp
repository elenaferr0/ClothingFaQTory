#include "backpack_repository.h"

using Services::BackPackRepository;

BackPackRepository* BackPackRepository::instance;

BackPackRepository::BackPackRepository()
        : Repository("backpack"), CRUDRepository("backpack", EntityMapper::backPack) {};

BackPackRepository* BackPackRepository::getInstance() {
    if (instance == nullptr) {
        instance = new BackPackRepository();
    }
    return instance;
}