#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "scoped.hpp"

TEST_CASE("Testing scoped guard")
{
    using namespace utlz;

    int test_val = 0;
    const int result = 42;

    {
        on_scope_exit([&]{ test_val = result; });
    }

    CHECK_EQ(test_val, result);
}