

#ifndef VIEW_H
#define VIEW_H


#include "../controllers/controller.h"
#include "../models/product.h"
#include <memory>
#include "products_view.h"

using std::shared_ptr;
using Views::ProductsView;

namespace Controllers {
    class Controller;
}

using Controllers::Controller;

namespace Views {
    class View {
        typedef Map<Product::ProductType, list<shared_ptr<Product>>> ProductsMap;

    public:
        View();

    protected:
        Controller* controller;
        ProductsView* productsView;
    public:
        ProductsView* getProductsView() const;
    };

}


#endif //VIEW_H
