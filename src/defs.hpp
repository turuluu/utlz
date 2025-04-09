#pragma once

#ifndef VAR_CAT3_
#    define VAR_CAT3_(a, b, c) a##b##c
#endif
#ifndef VAR_CAT3
#    define VAR_CAT3(a, b, c) VAR_CAT3_(a, b, c)
#endif

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
