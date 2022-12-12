#ifndef IPRODUCT_VISITOR_H
#define IPRODUCT_VISITOR_H

namespace Models::Accessories {
    class Bracelet;

    class BackPack;

    class Hat;
}

namespace Models::ClothingItems {
    class Jeans;

    class Vest;

    class Overalls;
}

using Models::Accessories::Bracelet;
using Models::Accessories::BackPack;
using Models::Accessories::Hat;

using Models::ClothingItems::Jeans;
using Models::ClothingItems::Vest;
using Models::ClothingItems::Overalls;

namespace Core {
    class IProductVisitor {
    public:
        virtual ~IProductVisitor() = default;

        virtual void visitBracelet(Bracelet&) = 0;

        virtual void visitBackPack(BackPack&) = 0;

        virtual void visitHat(Hat&) = 0;

        virtual void visitJeans(Jeans&) = 0;

        virtual void visitVest(Vest&) = 0;

        virtual void visitOveralls(Overalls&) = 0;
    };
}
#endif //IPRODUCT_VISITOR_H
