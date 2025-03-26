# Utilities for C++

Personal utilities for C++

## Usage

Add as a submodule

    mkdir deps
    git submodule add https://github.com/turuluu/utlz.git deps/utlz

Add configuration to CMakeLists.txt

    add_subdirectory(deps/utlz)
    target_link_libraries(${PROJECT_NAME} PRIVATE turuluu::utlz)

## Examples

[timelines](https://github.com/turuluu/timelines)

## Enable tests

    cmake -B build -Dutlz_enable_tests:BOOL=ON -G Ninja