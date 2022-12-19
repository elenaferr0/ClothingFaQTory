#ifndef MODEL_H
#define MODEL_H

#include <string>
#include "visitor_interface.h"

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

        virtual void accept(VisitorInterface& visitor) = 0;
    };
}

#endif // MODEL_H
