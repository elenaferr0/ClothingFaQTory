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

namespace Core {
    template<class L, class R>// R = right (correct result), L error
    class Either {
    private:
        variant <L, R> value;
    public:
        optional <L> left() const;

        optional <R> right() const;

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
    optional <L> Either<L, R>::left() const {
        if (holds_alternative<L>(value)) {
            return optional(get<L>(value));
        }
        return nullopt;
    }

    template<class L, class R>
    optional <R> Either<L, R>::right() const {
        if (holds_alternative<R>(value)) {
            return optional(get<R>(value));
        }
        return nullopt;
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
