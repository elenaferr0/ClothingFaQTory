#ifndef Vest_H
#define Vest_H

#include "clothing_item.h"

namespace Models::ClothingItems {
    class Vest : public virtual ClothingItem {
        private:
            bool hasButtons;
        public:
            const bool& getHasButtons() const;

            void setHasButtons(bool hasButtons);

        private:
            static const unsigned int N_BUTTONS;
            static const double BUTTON_DIAMETER;
        public:
            Vest(int id = -1,
                 const string& code = "",
                 const string& color = "",
                 const Material& material = Material(),
                 const Size& size = Size(),
                 int availableQuantity = 0,
                 int soldQuantity = 0,
                 const string& description = "",
                 bool sustainableMaterials = false,
                 const string& gender = "",
                 bool hasButtons = false);

            double computePrice() const override;

            void accept(VisitorInterface& visitor) override;
    };

}
#endif // Vest_H
