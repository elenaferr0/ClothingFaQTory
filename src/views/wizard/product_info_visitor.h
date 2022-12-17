#ifndef CLOTHING_ITEM_VIEW_VISITOR_H
#define CLOTHING_ITEM_VIEW_VISITOR_H

#include <QVBoxLayout>
#include "../../core/visitor_interface.h"

using Core::VisitorInterface;

class ProductInfoVisitor : VisitorInterface {
private:
    QGridLayout* layout;
    void buildAccessoryLayoutBase();
    void buildClothingItemLayoutBase();
public:
    ProductInfoVisitor();
    void visitBracelet(Bracelet& bracelet) override;

    void visitBackPack(BackPack& pack) override;

    void visitHat(Hat& hat) override;

    void visitJeans(Jeans& jeans) override;

    void visitVest(Vest& vest) override;

    void visitOveralls(Overalls& overalls) override;

    QGridLayout* getLayout() const;

};


#endif //CLOTHING_ITEM_VIEW_VISITOR_H
