#ifndef I_PRODUCT_OBSERVER_H
#define I_PRODUCT_OBSERVER_H

namespace Models {
    class Model;
}

using Models::Model;

namespace Core {
    class ObserverInterface {
        public:
            virtual void notify(Model* model) = 0;

            virtual ~ObserverInterface() = default;

    };
}
#endif //IPRODUCT_OBSERVER_H
