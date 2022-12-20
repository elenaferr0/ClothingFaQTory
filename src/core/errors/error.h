#ifndef ERROR_H
#define ERROR_H

#include<string>

using std::string;

namespace Core {
    class Error {
        private:
            string userMessage;
            string cause;
            string type;
        public:
            Error(string type = "", string cause = "Generic error", string userMessage = "");

            const string& getCause() const;

            const string& getUserMessage() const;

            void setUserMessage(const string&);
    };
}


#endif //ERROR_H
