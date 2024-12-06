cmake_minimum_required(VERSION 3.15)

project(utlz)

if (MSVC)
    # Just to have the sweet-sweet named parameters, that clang++17 already has..
    set(CMAKE_CXX_STANDARD 20)
else ()
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_OSX_ARCHITECTURES "x86_64;arm64" CACHE INTERNAL "" FORCE)
endif ()
set(CMAKE_ASM_STANDARD_REQUIRED True)
#set(CMAKE_CXX_FLAGS_DEBUG "-O1")


add_subdirectory(src)
add_library(${PROJECT_NAME} INTERFACE)

option(utlz_enable_tests "Enable tests" ON)
if (utlz_enable_tests)
    message(STATUS "Tests \t\tENABLED")
    add_library(doctest INTERFACE deps/doctest/doctest.h)
    target_include_directories(doctest INTERFACE deps/doctest)
    target_include_directories(${PROJECT_NAME} INTERFACE src)

    if (DOCTEST_NO_COLORS)
        message(STATUS "Disable Doctest terminal output colors")
        target_compile_definitions(${PROJECT_NAME} INTERFACE DOCTEST_CONFIG_COLORS_NONE)
    endif()
    add_subdirectory(test)
else()
    message(STATUS "Tests \t\tDISABLED")
endif()

# https://docs.microsoft.com/en-us/cpp/build/reference/utf-8-set-source-and-executable-character-sets-to-utf-8?view=msvc-160
if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /utf-8)
endif ()

# utfcpp
#target_compile_definitions(${PROJECT_NAME} PUBLIC UTF_CPP_CPLUSPLUS=201703L)
#target_include_directories(${PROJECT_NAME} PUBLIC "deps/utfcpp")

# Harfbuzz
#set(HB_BUILD_SUBSET OFF CACHE BOOL " " FORCE)
#add_subdirectory(deps/harfbuzz)

