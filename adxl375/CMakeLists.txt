add_library(adxl375 INTERFACE)
target_include_directories(adxl375 INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include/)
target_sources(adxl375 INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include/adxl375/adxl375.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/adxl375/adxl375_defs.h)
target_link_libraries(adxl375 INTERFACE regmap)