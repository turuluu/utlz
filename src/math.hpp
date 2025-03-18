
#include <algorithm>
#include <cmath>
#include <sstream>

namespace utlz
{
const double pi = std::acos(-1);

template <typename T>
T limit(T min, T max, T value)
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
