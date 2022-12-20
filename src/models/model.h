#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <list>
#include "../core/visitors/model_visitor_interface.h"
#include "../core/observer_interface.h"

using std::string;
using std::list;
using Core::Visitors::ModelVisitorInterface;
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

            virtual void accept(ModelVisitorInterface& visitor) = 0;

            void registerObserver(ObserverInterface* observer);

            void notifyAll();
    };
}

#endif // MODEL_H
