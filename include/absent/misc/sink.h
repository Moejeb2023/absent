#ifndef RVARAGO_ABSENT_SINK_H
#define RVARAGO_ABSENT_SINK_H

#include <tuple>
#include <utility>

namespace rvarago::absent {

    template <typename Function, typename... Ts>
    struct Sink {

        template <typename... Args>
        explicit Sink(Function producer, Args&&... args)
        : _fn{std::forward<Function>(producer)},
          _args{std::forward<Args>(args)...} {}

        template <typename T>
        constexpr decltype(auto) operator()(T&&) {
            return call_helper(_args, std::index_sequence_for<Ts...>());
        }

    private:

        template<std::size_t... Is>
        constexpr decltype(auto) call_helper(std::tuple<Ts...> const& tuple, std::index_sequence<Is...>) {
            return _fn(std::get<Is>(tuple)...);
        }

        Function _fn;
        std::tuple<Ts...> _args;
    };

}

#endif //RVARAGO_ABSENT_SINK_H
