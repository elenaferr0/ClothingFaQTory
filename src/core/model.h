#ifndef MODEL_H
#define MODEL_H

#include <string>

using std::string;

namespace Core {
    class Model {
    private:
        int id;
    public:
        Model(int id = -1) : id(id) {};

        const int& getId() const;

        void setId(int id);

        virtual Model* clone() const = 0;

        bool found() const;

        virtual ~Model() = default;
    };
}

#endif // MODEL_H
