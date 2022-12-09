#ifndef PRODUCT_H
#define PRODUCT_H

#include "./material.h"
#include "./size.h"
#include "../core/model.h"

#include<string>
#include<list>

using std::string;
using std::list;
using Core::Model;

namespace Models {
    class Product : public Model {
    protected:
        string color;
        list <Material> materials;
        Size size;
        int availableQuantity;
        int soldQuantity;
        string description;
        string code;

    public:
        Product(long id = -1,
                string code = "",
                string color = "",
                list <Material> materials = list<Material>(),
                Size size = Size(),
                int availableQuantity = 0,
                int soldQuantity = 0,
                string description = "");

        virtual double computePrice() const = 0;

        string getTableName() const override;

        virtual ~Product() {};

        const string& getColor() const;

        const list <Material>& getMaterials() const;

        const Size& getSize() const;

        int getAvailableQuantity() const;

        int getSoldQuantity() const;

        const string& getDescription() const;

        const string& getCode() const;

        void setColor(const string& color);

        void setMaterials(const list <Material>& materials);

        void setSize(const Size& size);

        void setAvailableQuantity(int availableQuantity);

        void setSoldQuantity(int soldQuantity);

        void setDescription(const string& description);

        void setCode(const string& code);
    };
}
#endif // PRODUCT_H
