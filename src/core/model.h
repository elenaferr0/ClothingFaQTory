#ifndef MODEL_H
#define MODEL_H

#include <string>

using std::string;

namespace Core {
    class Model {
    private:
        unsigned long id;
    public:
        Model(unsigned long id) : id(id) {};

        unsigned long long getId() const;

        virtual Model* clone() const = 0;

        virtual string getTableName() const = 0;
    };
}

#endif // MODEL_H
