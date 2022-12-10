#ifndef EITHER_H
#define EITHER_H

#include <optional>
#include <variant>
#include <functional>

using std::variant;
using std::get;
using std::holds_alternative;
using std::optional;
using std::nullopt;
using std::function;
using std::reference_wrapper;
using std::ref;

namespace Core {
    template<class L, class R>// R = right (correct result), L error
    class Either {
    private:
        variant<L, R> value;
    public:

        // left() and right() are not const since the object is returned by reference
        optional<reference_wrapper<L>> left();

        optional<reference_wrapper<R>> right();

        // forceLeft() and forceRight() will result in an error if not present (but they allows less verbosity)
        // should be used only after checking current value
        L& forceLeft();

        R& forceRight();

        bool isRight() const;

        bool isLeft() const;

        Either(const L& left);

        Either(const R& left);

        static Either ofLeft(const L& left);

        static Either ofRight(const R& right);

        template<class B>
        B fold(function<B(void)> ifLeft, function<B(void)> ifRight) const;
    };

    template<class L, class R>
    Either<L, R>::Either(const L& left) {
        value = left;
    }

    template<class L, class R>
    Either<L, R>::Either(const R& right) {
        value = right;
    }

    template<class L, class R>
    optional<reference_wrapper<L>> Either<L, R>::left() {
        if (holds_alternative<L>(value)) {
            reference_wrapper<L> reference = ref(get<L>(value));
            return optional(reference);
        }
        return nullopt;
    }

    template<class L, class R>
    optional<reference_wrapper<R>> Either<L, R>::right() {
        if (holds_alternative<R>(value)) {
            reference_wrapper<R> reference = ref(get<R>(value));
            return optional(reference);
        }
        return nullopt;
    }

    template<class L, class R>
    L& Either<L, R>::forceLeft() {
        return ref(get<L>(value));
    }

    template<class L, class R>
    R& Either<L, R>::forceRight() {
        return ref(get<R>(value));
    }

    template<class L, class R>
    bool Either<L, R>::isRight() const {
        return holds_alternative<R>(value);
    }

    template<class L, class R>
    bool Either<L, R>::isLeft() const {
        return holds_alternative<L>(value);
    }

    template<class L, class R>
    Either<L, R> Either<L, R>::ofLeft(const L& left) {
        return Either<L, R>(left);
    }

    template<class L, class R>
    Either<L, R> Either<L, R>::ofRight(const R& right) {
        return Either<L, R>(right);
    }

    template<class L, class R>
    template<class B>
    B Either<L, R>::fold(function<B(void)> ifLeft, function<B(void)> ifRight) const {
        if (holds_alternative<L>(value)) {
            return ifLeft();
        }
        return ifRight();
    }
}
#endif //EITHER_H
