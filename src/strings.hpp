#pragma once

#include <cstddef>
#include <sstream>
#include <string>

// File:line print format for specific IDEs
#ifndef FILE_LOC
#    define FILE_LOC utlz::to_string(__FILE__, ":", __LINE__)
#endif

// Thread, Stack, Location debug print helper
#ifndef UTLZ_TSL_PRINT_ENABLED
#    define UTLZ_TSL_PRINT_ENABLED 0
#endif

#if UTLZ_TSL_PRINT_ENABLED
#    ifndef PRINT_TSL
#        if defined(_MSC_VER)
#            ifndef __PRETTY_FUNCTION__
#                define __PRETTY_FUNCTION__ __FUNCSIG__
#            endif
#        endif

#        include <cstdio>
#        define PRINT_TSL                                  \
            do                                             \
            {                                              \
                std::printf("T[ %s ]\tS[ %s ]\tL[ %s ]\n", \
                            utlz::get_thread_id().c_str(), \
                            __PRETTY_FUNCTION__,           \
                            FILE_LOC.c_str());             \
                std::fflush(nullptr);                      \
            } while (0);
#    else
#        define PRINT_TSL ;
#    endif  // TSL
#endif

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

