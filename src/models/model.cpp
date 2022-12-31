#include "model.h"

using Models::Model;

const int& Model::getId() const {
    return id;
}

void Model::setId(int id) {
    this->id = id;
}

