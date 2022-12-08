#ifndef MODEL_H
#define MODEL_H

#include <string>

using std::string;

namespace Core {
    class Model {
    private:
        long long id;
    public:
        // -1 means some kind of error has occurred to the upper level
        Model(long long id = -1) : id(id) {};

        long long getId() const;

        virtual Model* clone() const = 0;

        virtual string getTableName() const = 0;
    };
}

#endif // MODEL_H
