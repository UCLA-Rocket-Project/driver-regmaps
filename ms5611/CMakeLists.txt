add_library(ms5611 ms5611.c include/ms5611/ms5611.h)
target_include_directories(ms5611 PUBLIC include)
target_link_libraries(ms5611 regmap)