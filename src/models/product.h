#ifndef PRODUCT_H
#define PRODUCT_H

#include "./material.h"
#include "./size.h"
#include "model.h"
#include "../core/observer_interface.h"
#include "../core/visitor_interface.h"

#include<string>
#include<list>

using std::string;
using std::list;
using Models::Model;
using Core::VisitorInterface;
using Core::ObserverInterface;

namespace Models {
    class Product : public Model {
    private:
        list<ObserverInterface*> observers;
    protected:
        string color;
        Material material;
        Size size;
        int availableQuantity;
        int soldQuantity;
        string description;
        string code;

        void notifyAll();

    public:
        enum ProductType {
            Jeans, Vest, Overalls, Bracelet, BackPack, Hat
        };
        static string productTypeToString(Product::ProductType);

        Product(long id = -1,
                string code = "",
                string color = "",
                Material material = Material(),
                Size size = Size(),
                int availableQuantity = 0,
                int soldQuantity = 0,
                string description = "");

        virtual double computePrice() const = 0;

        virtual ~Product() {};

        const string& getColor() const;

        const Material& getMaterial() const;

        const Size& getSize() const;

        const int& getAvailableQuantity() const;

        const int& getSoldQuantity() const;

        const string& getDescription() const;

        const string& getCode() const;

        void registerObserver(ObserverInterface* observer);
    };
}
#endif // PRODUCT_H
