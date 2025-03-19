#include "strings.hpp"

#include <cstddef>
#include <string>
#include <thread>

namespace utlz
{
std::string get_thread_id()
{
    return to_string(std::this_thread::get_id());
}

std::size_t length(const char* cstr)
{
    return strlen(cstr);
}
}  // namespace utlz
