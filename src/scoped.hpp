#pragma once

#include <algorithm>
#include <atomic>
#include "defs.hpp"

namespace utlz
{
template <typename Functor>
class OnScopeExit
{
    Functor cleanup;
    std::atomic<bool> is_active;

public:
    explicit OnScopeExit(Functor cleanup_function)
        : cleanup(std::move(cleanup_function))
        , is_active(true)
    {
    }

    ~OnScopeExit()
    {
        if (is_active.exchange(false))
            cleanup();
    }

    OnScopeExit() = delete;
    OnScopeExit(const OnScopeExit&) = delete;
    OnScopeExit& operator=(const OnScopeExit&) = delete;
    OnScopeExit(OnScopeExit&& other) noexcept
        : cleanup(std::move(other.cleanup))
        , is_active(other.is_active.exchange(false))
    {
    }

    void dismiss() { is_active = false; }
};

namespace detail
{
template <typename Functor>
auto on_scope_exit(Functor cleanup_function)
{
    return OnScopeExit<Functor>(std::move(cleanup_function));
}
}  // namespace detail

#define on_scope_exit_here(cleanup_function)                                \
    volatile auto VAR_CAT3(__PRETTY_FUNCTION__, _cleanup_, __LINE__) = \
        utlz::detail::on_scope_exit(cleanup_function);
}  // namespace utlz