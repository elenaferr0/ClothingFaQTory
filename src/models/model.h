#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <list>
#include "../core/visitor_interface.h"
#include "../core/observer_interface.h"

using std::string;
using std::list;
using Core::VisitorInterface;
using Core::ObserverInterface;

namespace Models {
    class Model {
        private:
            int id;
            list<ObserverInterface*> observers;
        public:
            Model(int id = -1) : id(id) {};

            const int& getId() const;

            void setId(int id);

            virtual Model* clone() const = 0;

            bool found() const;

            virtual ~Model() = default;

            void registerObserver(ObserverInterface* observer);

            void notifyAll();
    };
}

#endif // MODEL_H
