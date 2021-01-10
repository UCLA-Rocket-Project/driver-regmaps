add_library(regmap INTERFACE)
target_include_directories(regmap INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_sources(regmap INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include/regmap/regmap.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/regmap/bitstuff.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/regmap/bus.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/regmap/endianfix.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/regmap/utils.h)

add_subdirectory(test)