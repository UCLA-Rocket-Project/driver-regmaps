add_library(ms5611 INTERFACE ../ads1261/ads1261_regs.h)
target_include_directories(ms5611 INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include/)
target_sources(ms5611 INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include/ms5611/ms5611.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/ms5611/ms5611_defs.h)
target_link_libraries(ms5611 INTERFACE regmap)