#pragma once

#include <array>
#include <cstddef>
#include <utility>

namespace utlz
{
template <typename T, typename... Args, std::size_t... sizes>
constexpr std::array<T, sizeof...(sizes)>
make_array_impl(std::index_sequence<sizes...>, Args&&... args)
{
    return {{(static_cast<void>(sizes), T(std::forward<Args>(args)...))...}};
}

template <std::size_t N, typename T, typename... Args>
constexpr std::array<T, N> make_array(Args&&... args)
{
    return make_array_impl<T>(std::make_index_sequence<N>(), std::forward<Args>(args)...);
}
}
