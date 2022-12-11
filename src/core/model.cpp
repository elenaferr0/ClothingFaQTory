#include "model.h"

using Core::Model;

int Model::getId() const {
    return id;
}

void Model::setId(int id) {
    this->id = id;
}

bool Core::Model::found() const {
    return id != -1;
}
