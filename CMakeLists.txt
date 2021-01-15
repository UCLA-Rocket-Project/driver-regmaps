cmake_minimum_required(VERSION 3.0.0)
project(driver-regmaps)
set (CMAKE_CXX_STANDARD 17)

add_subdirectory(cpp-regmap)
add_subdirectory(ads1261)

# add_subdirectory(ms5611)
# add_subdirectory(adxl375)

add_executable(FOR_CLION_TARGET main.cpp)
target_link_libraries(FOR_CLION_TARGET regmap ads1261_driver)