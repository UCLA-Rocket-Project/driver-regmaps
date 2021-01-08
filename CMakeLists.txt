cmake_minimum_required(VERSION 3.0.0)
project(driver-regmaps C)

include_directories(inc)

add_subdirectory(regmap)
add_subdirectory(ms5611)
add_subdirectory(adxl375)

add_executable(test test.c)
target_link_libraries(test regmap)