#include <absent/misc/sink.h>
#include <absent/absent.h>

#include <optional>
#include <string>

#include <gtest/gtest.h>

namespace {

    using namespace rvarago::absent;

    struct person final {};
    struct address final {};

    TEST(foo, bar) {
        auto const foo = [] { return std::optional{person{}}; };
        auto const bar = [](auto const &, auto const &) { return std::optional{address{}}; };
        auto const baz = [](auto const &) { return 42; };

        auto const chain_result = foo() >> Sink{bar, 1, 2} | baz;

        EXPECT_TRUE(chain_result);
        EXPECT_EQ(std::optional{42}, chain_result);
    }

    TEST(foo, bar2) {
        auto const foo = [] { return std::optional{person{}}; };
        auto const bar = []() -> std::optional<address> { return std::nullopt; };
        auto const baz = [](auto const &) { return 42; };

        EXPECT_FALSE(foo() >> Sink{bar} | baz);
    }

}
