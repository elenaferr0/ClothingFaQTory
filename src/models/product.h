#ifndef PRODUCT_H
#define PRODUCT_H

#include "./material.h"
#include "./size.h"
#include "model.h"
#include "../core/observer_interface.h"
#include "../core/visitor_interface.h"

#include<string>


using std::string;

using Models::Model;
using Core::VisitorInterface;
using Core::ObserverInterface;

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

            virtual void accept(VisitorInterface& visitor) = 0;

            void setColor(const string& color);

            void setMaterial(const Material& material);

            void setSize(const Size& size);

            void setAvailableQuantity(int availableQuantity);

            void setSoldQuantity(int soldQuantity);

            void setDescription(const string& description);

            void setCode(const string& code);
    };
}
#endif // PRODUCT_H
