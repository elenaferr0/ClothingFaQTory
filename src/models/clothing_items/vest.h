#ifndef Vest_H
#define Vest_H

#include "clothing_item.h"

namespace Models::ClothingItems {
    class Vest : public virtual ClothingItem {
    private:
        bool hasButtons;
    public:
        bool getHasButtons() const;

        void setHasButtons(bool hasButtons);

    private:
        static const unsigned int N_BUTTONS;
        static const double BUTTON_DIAMETER;
    public:
        Vest(long id = -1,
             string code = "",
             string color = "",
             Material material = Material(),
             Size size = Size(),
             int availableQuantity = 0,
             int soldQuantity = 0,
             string description = "",
             bool sustainableMaterials = false,
             string gender = "",
             bool hasButtons = false);

        double computePrice() const override;

        Vest* clone() const override;

        void accept(IProductVisitor& visitor) override;
    };

}
#endif // Vest_H
