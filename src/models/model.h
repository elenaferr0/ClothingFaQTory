#ifndef MODEL_H
#define MODEL_H

#include <string>
#include "../core/visitor_interface.h"
#include "../core/containers/linked_list.h"

using std::string;
using Core::Containers::LinkedList;
using Core::VisitorInterface;

namespace Models {
    class Model {
        private:
            int id;
        public:
            Model(int id = -1) : id(id) {};

            const int& getId() const;

            void setId(int id);

            bool found() const;

            virtual ~Model() = default;

            virtual void accept(VisitorInterface& visitor) = 0;

    };
}

#endif // MODEL_H
