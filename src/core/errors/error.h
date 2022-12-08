#ifndef ERROR_H
#define ERROR_H

#include<string>

using std::string;

namespace Core {
    class Error {
    private:
        string userMessage;
        string cause;
    public:
        // allow implicit construction
        Error(
                string cause = "",
                string userMessage = "Generic error"
        );

        string getMessage() const;
    };
}


#endif //ERROR_H
