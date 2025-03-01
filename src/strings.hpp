#pragma once

#include <sstream>
#include <string>

namespace utlz
{
template<typename... T>
std::string
to_string(T... obj)
{
    return (std::stringstream{} << ... << obj).str();
}

std::string get_thread_id();

}