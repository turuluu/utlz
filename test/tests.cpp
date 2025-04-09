#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "scoped.hpp"
#include "arrays.hpp"
#include "strings.hpp"
#include "math.hpp"

using namespace utlz;


TEST_CASE("Testing scoped guard")
{
    int test_val = 0;
    const int result = 42;

    int test_dismiss = 0;
    const int wrong_result_dismiss = 42;
    {
        auto scoped0 = on_scope_exit([&] { test_val = result; });
        auto scoped1 = on_scope_exit([&] { test_dismiss = wrong_result_dismiss; });
        scoped1.dismiss();
    }

    CHECK_EQ(test_val, result);
    CHECK_NE(test_dismiss, wrong_result_dismiss);
}

TEST_CASE("Testing scoped guard helper macro")
{
    int test_val0 = 0;
    int test_val1 = std::numeric_limits<int>::max();
    int test_val2 = std::numeric_limits<int>::min();
    const int result0 = std::numeric_limits<int>::min();
    const int result1 = std::numeric_limits<int>::lowest();
    const int result2 = 42;

    {
        on_scope_exit_here([&] { test_val0 = result0; });
        on_scope_exit_here([&] { test_val1 = result1; });
        on_scope_exit_here([&] { test_val2 = result2; });
    }

    CHECK_EQ(test_val0, result0);
    CHECK_EQ(test_val1, result1);
    CHECK_EQ(test_val2, result2);
}

struct NonTriviallyConstructible
{
    NonTriviallyConstructible() = delete;
    NonTriviallyConstructible(int x, int y)
        : z(x * y)
    {
    }
    const int z;
};

TEST_CASE("make_array forwards args into a non-trivially-constructible object")
{
    constexpr int n = 4;

    std::array<NonTriviallyConstructible, n> test_array {
        make_array<n, NonTriviallyConstructible>(2, 3)
    };
    CHECK_EQ(test_array.size(), n);
    for (const auto& e : test_array)
        CHECK_EQ(e.z, 6);
}

TEST_CASE("strings")
{
    std::vector<std::string> test_strings {};
    int i = 0;
    test_strings.push_back(to_string("foo", 1));
    CHECK_EQ(test_strings.at(0), "foo1");

    test_strings.push_back(to_string("bar", 1.1));
    CHECK_EQ(test_strings.at(++i), "bar1.1");

    test_strings.push_back(to_string("bar", std::string { "baz" }, 13, 2.4, false));
    CHECK_EQ(test_strings.at(++i), "barbaz132.40");
}

TEST_CASE("threads")
{
    CHECK_EQ(get_thread_id(), get_thread_id());
}

TEST_CASE("maths")
{
    CHECK_LT(pi - 3.14159, 0.00001);
}
