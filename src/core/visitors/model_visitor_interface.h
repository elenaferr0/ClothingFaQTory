#ifndef MODEL_VISITOR_INTERFACE_H
#define MODEL_VISITOR_INTERFACE_H

namespace Models {
    class Material;

    class Size;

    namespace Accessories {
        class Bracelet;

        class BackPack;

        class Hat;
    }

    namespace ClothingItems {
        class Jeans;

        class Vest;

        class Overalls;
    }
}

using Models::Material;
using Models::Size;
using Models::Accessories::Bracelet;
using Models::Accessories::BackPack;
using Models::Accessories::Hat;

using Models::ClothingItems::Jeans;
using Models::ClothingItems::Vest;
using Models::ClothingItems::Overalls;

namespace Core::Visitors {
    class ModelVisitorInterface {
        public:
            virtual ~ModelVisitorInterface() = default;

            virtual void visitBracelet(Bracelet&) = 0;

            virtual void visitBackPack(BackPack&) = 0;

            virtual void visitHat(Hat&) = 0;

            virtual void visitJeans(Jeans&) = 0;

            virtual void visitVest(Vest&) = 0;

            virtual void visitOveralls(Overalls&) = 0;

            virtual void visitMaterial(Material&) = 0;

            virtual void visitSize(Size&) = 0;
    };
}
#endif //MODEL_VISITOR_INTERFACE_H
