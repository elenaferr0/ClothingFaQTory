#include "error.h"

using Core::Error;

Error::Error(string type, string cause, string userMessage)
        : type(type), cause(cause), userMessage(userMessage) {}

const string& Error::getCause() const {
    return cause;
}

const string& Error::getUserMessage() const {
    return userMessage;
}

void Error::setUserMessage(const string& userMessage) {
    this->userMessage = userMessage;
}

const string& Core::Error::getType() const {
    return type;
}

Error* Core::Error::clone() const {
    return new Error(*this);
}
