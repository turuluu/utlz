cmake_minimum_required(VERSION 3.15)

project(utlz)

if (MSVC)
    set(CMAKE_CXX_STANDARD 20)
else ()
    set(CMAKE_CXX_STANDARD 20)
    # Enable intel builds
    #    set(CMAKE_OSX_ARCHITECTURES "x86_64;arm64" CACHE INTERNAL "" FORCE)
    set(CMAKE_OSX_ARCHITECTURES "arm64" CACHE INTERNAL "" FORCE)
endif ()

add_subdirectory(src)
add_library(${PROJECT_NAME} INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/scoped.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/arrays.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/strings.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/math.hpp)
target_sources(${PROJECT_NAME} INTERFACE ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

option(utlz_enable_tests "Enable tests" OFF)
if (utlz_enable_tests)
    message(STATUS "Tests \t\tENABLED")
    add_library(doctest INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/deps/doctest/doctest.h)
    target_include_directories(doctest INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/deps/doctest)
    target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/src)

    if (DOCTEST_NO_COLORS)
        message(STATUS "Disable Doctest terminal output colors")
        target_compile_definitions(${PROJECT_NAME} INTERFACE DOCTEST_CONFIG_COLORS_NONE)
    endif ()
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)
else ()
    message(STATUS "Tests \t\tDISABLED")
endif ()

# https://docs.microsoft.com/en-us/cpp/build/reference/utf-8-set-source-and-executable-character-sets-to-utf-8?view=msvc-160
if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /utf-8)
endif ()

add_library(turuluu::${PROJECT_NAME} ALIAS ${PROJECT_NAME})