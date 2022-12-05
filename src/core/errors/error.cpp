#include "error.h"
using Core::Error;

Error::Error(string userMessage, string cause)
  : userMessage(userMessage), cause(cause) {}

string Error::getMessage() const {
    return userMessage;
}
