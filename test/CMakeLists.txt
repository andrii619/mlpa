
# Add your test files here
add_executable(mlpalogger_tests
    ${CMAKE_SOURCE_DIR}/test/BasicTest.cc
)

add_clangformat_to_target(mlpalogger_tests)

target_link_libraries(mlpalogger_tests
    PRIVATE
    gtest_main
)

target_include_directories(mlpa_tests PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

# Register the test with CTest
include(GoogleTest)
gtest_discover_tests(mlpalogger_tests)
