#ifndef SPECIFIC_PRODUCT_INFO_VISITOR_H
#define SPECIFIC_PRODUCT_INFO_VISITOR_H

#include <QFormLayout>
#include <QMap>
#include "../../core/visitor_interface.h"
#include "product_wizard_view.h"

using Core::VisitorInterface;
using Views::Wizard::ProductWizardView;

class SpecificProductInfoVisitor : public VisitorInterface {
    private:
        static const int FORM_ICON_SIZE = 25;
        QFormLayout* layout;

        void buildAccessory(Accessory::Category category);

        void buildClothingItem(ClothingItem::Gender gender, bool sustainableMaterials);

        void buildJeans(bool areShorts);

        void buildVest(bool hasButtons);

        QMap<QString, QWidget*> fieldsToRegister;
        bool fillFields;
    public:
        SpecificProductInfoVisitor(ProductWizardView::Mode mode);

        void visitBracelet(Bracelet& bracelet) override;

        void visitBackPack(BackPack& pack) override;

        void visitHat(Hat& hat) override;

        void visitJeans(Jeans& jeans) override;

        void visitVest(Vest& vest) override;

        void visitOveralls(Overalls& overalls) override;

        QFormLayout* getLayout() const;

        const QMap<QString, QWidget*>& getFieldsToRegister() const;

        void clean();

};


#endif //SPECIFIC_PRODUCT_INFO_VISITOR_H
