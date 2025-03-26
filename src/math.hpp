#pragma once

#include <algorithm>
#if __cplusplus > 201703L
#    include <numbers>
#else
#    include <cmath>
#endif

namespace utlz
{
#if __cplusplus > 201703L
using std::numbers::pi;
#else
inline const double pi = std::acos(-1);
#endif

template <typename T>
constexpr T limit(T min, T max, T value)
{
    return std::min(max, std::max(min, value));
}

template <typename T>
struct interval
{
    T start {};
    T end {};
};
}  // namespace utlz
