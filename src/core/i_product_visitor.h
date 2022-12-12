#ifndef I_VISITOR_H
#define I_VISITOR_H

#include "../models/accessories/backpack.h"
#include "../models/accessories/bracelet.h"
#include "../models/accessories/hat.h"
#include "../models/clothing_items/jeans.h"
#include "../models/clothing_items/overalls.h"

using Models::Accessories::BackPack;
using Models::Accessories::Bracelet;
using Models::Accessories::Hat;
using Models::ClothingItems::Jeans;
using Models::ClothingItems::Overalls;

namespace Core {
    class IProductVisitor {
    public:
        virtual void visitBackPack(BackPack&) = 0;

        virtual void visitBracelet(Bracelet&) = 0;

        virtual void visitHat(Hat&) = 0;

        virtual void visitJeans(Jeans&) = 0;

        virtual void visitOveralls(Overalls&) = 0;

        virtual void visitVest(Vest&) = 0;

        virtual ~IProductVisitor() = default;

    };

}

#endif //I_VISITOR_H
