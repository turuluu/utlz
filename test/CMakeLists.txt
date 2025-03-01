set(TARGET_NAME test_${PROJECT_NAME})

add_executable(${TARGET_NAME} tests.cpp )
target_link_libraries(${TARGET_NAME} doctest ${PROJECT_NAME})
add_test(NAME ${TARGET_NAME} COMMAND ${TARGET_NAME})
