#ifndef PRODUCT_H
#define PRODUCT_H

#include "./material.h"
#include "./size.h"
#include "../core/model.h"
#include "../core/iproduct_visitor.h"

#include<string>
#include<list>

using std::string;
using std::list;
using Core::Model;
using Core::IProductVisitor;

namespace Models {
    class Product : public Model {
    protected:
        string color;
        Material material;
        Size size;
        int availableQuantity;
        int soldQuantity;
        string description;
        string code;

    public:
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

        int getAvailableQuantity() const;

        int getSoldQuantity() const;

        const string& getDescription() const;

        const string& getCode() const;

        void setMaterial(const Material& material);

        void setSize(const Size& size);

        virtual void accept(IProductVisitor& visitor) = 0;
    };
}
#endif // PRODUCT_H
