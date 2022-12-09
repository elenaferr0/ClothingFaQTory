#include "model.h"

using Core::Model;

long long Model::getId() const {
    return id;
}

void Model::setId(long long id) {
    this->id = id;
}

bool Core::Model::found() const {
    return id != -1;
}
