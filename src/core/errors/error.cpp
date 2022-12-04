#include "error.h"

Error::Error(string message) : message(message) {}

string Error::getMessage() const {
    return message;
}