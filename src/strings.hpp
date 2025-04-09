#pragma once

#include <cstddef>
#include <sstream>
#include <string>

namespace utlz
{
template <typename... T>
std::string to_string(T... obj)
{
    return (std::stringstream {} << ... << obj).str();
}

std::string get_thread_id();

std::size_t length(const char* cstr);

static void dbg(auto&&... args)
{
#ifndef NDEBUG
    std::stringstream ss;
    (ss << ... << args) << std::endl;
    std::printf(ss.str().c_str());
#endif
}

}  // namespace utlz

