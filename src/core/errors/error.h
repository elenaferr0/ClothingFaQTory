#ifndef ERROR_H
#define ERROR_H

#include<string>

using std::string;

namespace Core {
    class Error {
        private:
            string type;
            string cause;
            string userMessage;

        public:
            Error(string type = "", string cause = "Generic error", string userMessage = "");

            const string& getCause() const;

            const string& getUserMessage() const;

            const string& getType() const;

            void setUserMessage(const string&);
    };
}


#endif //ERROR_H
