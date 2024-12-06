#pragma once

#ifndef VAR_CAT3_
    #define VAR_CAT3_(a, b, c) a##b##c
#endif
#ifndef VAR_CAT3
#define VAR_CAT3(a, b, c) VAR_CAT3_(a, b, c)
#endif

