#include "backpack_repository.h"
#include "../mappers/back_pack_mapper.h"

using Services::BackPackRepository;

BackPackRepository* BackPackRepository::instance;

BackPackRepository::BackPackRepository()
        : Repository("backpack"), CRUDRepository("backpack", new BackPackMapper()) {};

BackPackRepository* BackPackRepository::getInstance() {
    if (instance == nullptr) {
        instance = new BackPackRepository();
    }
    return instance;
}