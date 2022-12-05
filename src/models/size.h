#ifndef SIZE_H
#define SIZE_H

#include "src/core/model.h"

using Core::Model;

namespace Models {
    class Size : public Model {
    public:

        double getExtraPercentageOfMaterial() const;

	string getName() const;

        Size(unsigned long id = 0,
	     string name = "",
             double extraPercentageOfMaterial = 0);

        string getTableName() const override;
	string fromString(string) const;
	void setName(string name);
	void setExtraPercentageOfMaterial(double extraPercentageOfMaterial);
    private:
	string name;
        double extraPercentageOfMaterial;

        Size* clone() const override;
    };
}

#endif // SIZE_H
