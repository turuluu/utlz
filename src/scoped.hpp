#pragma once

#include <algorithm>
#include <atomic>
#include "defs.hpp"

namespace utlz
{
template <typename Functor>
class on_scope_exit
{
    Functor cleanup;
    std::atomic<bool> is_active;

public:
    explicit on_scope_exit(Functor cleanup_function)
        : cleanup(std::move(cleanup_function))
        , is_active(true)
    {
    }

    ~on_scope_exit()
    {
        if (is_active.exchange(false))
            cleanup();
    }

    on_scope_exit() = delete;
    on_scope_exit(const on_scope_exit&) = delete;
    on_scope_exit& operator=(const on_scope_exit&) = delete;
    on_scope_exit(on_scope_exit&& other) noexcept
        : cleanup(std::move(other.cleanup))
        , is_active(other.is_active.exchange(false))
    {
    }

    void dismiss() { is_active = false; }
};

#define on_scope_exit_here(cleanup_function)                           \
    volatile auto VAR_CAT3(__PRETTY_FUNCTION__, _cleanup_, __LINE__) = \
        utlz::on_scope_exit(std::move(cleanup_function));
}  // namespace utlz