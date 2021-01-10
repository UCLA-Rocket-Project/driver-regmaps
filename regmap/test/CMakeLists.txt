add_executable(test-regmap
        main.cpp
        static_tests.cpp
        test_common.h
        unit_test_framework.h)
target_include_directories(test-regmap PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include/)