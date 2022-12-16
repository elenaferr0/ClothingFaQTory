#include "model.h"

using Core::Model;

const int& Model::getId() const {
    return id;
}

void Model::setId(int id) {
    this->id = id;
}

bool Core::Model::found() const {
    return id != -1;
}
