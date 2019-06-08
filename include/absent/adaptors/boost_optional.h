#ifndef RVARAGO_ABSENT_BOOST_OPTIONAL_H
#define RVARAGO_ABSENT_BOOST_OPTIONAL_H

#ifdef WITH_ADAPTOR_FOR_BOOST_OPTIONAL

#include <boost/optional.hpp>

namespace rvarago::absent::syntax {

    template <typename Mapper, typename A>
    struct nullable<boost::optional, Mapper, A> final {

        static constexpr auto bind(boost::optional<A> input, Mapper fn) -> decltype(fn(std::declval<A>())) {
            if (!input) {
                return decltype(fn(std::declval<A>())){};
            }
            return fn(std::move(input.value()));
        }

    };

}

#endif

#endif // RVARAGO_ABSENT_BOOST_OPTIONAL_H
