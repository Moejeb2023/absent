#ifndef RVARAGO_ABSENT_SYNTAX_H
#define RVARAGO_ABSENT_SYNTAX_H

#include <utility>

namespace rvarago::absent::nullable::syntax {

    /**
     * For custom types that have a different way to check if they are empty.
     */
    template <template<typename...> typename Nullable, typename A, typename... Rest>
    struct empty final {
        static constexpr auto _(Nullable<A, Rest...> const &input) noexcept -> bool {
            return !input;
        }
    };

    /**
     * For custom types that have a different way to access its wrapped value.
     */
    template <template<typename...> typename Nullable, typename A, typename... Rest>
    struct value final {
        static constexpr auto _(Nullable<A, Rest...> input) noexcept -> A {
            return *input;
        }
    };

    /**
     * For custom types that have a different way to create new instances of itself from arguments.
     */
    template <template<typename...> typename Nullable, typename... Rest>
    struct make final {
        static constexpr auto _(Rest... args) noexcept -> Nullable<Rest...> {
            return Nullable<Rest...>{std::move(args)...};
        }
    };

    /**
     * For custom types that have a different concept of empty state.
     */
    template <typename NullableIn, typename NullableOut>
    struct make_empty final {
        static constexpr auto _(NullableIn) noexcept -> NullableOut {
            return NullableOut{};
        }
    };

}

#endif //RVARAGO_ABSENT_SYNTAX_H
