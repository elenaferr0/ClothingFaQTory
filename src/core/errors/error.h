#ifndef ERROR_H
#define ERROR_H

#include<string>

using std::string;

class Error {
private:
    string message;
public:
    // allow implicit construction
    Error(string message = "");

    string getMessage() const;
};


#endif //ERROR_H
