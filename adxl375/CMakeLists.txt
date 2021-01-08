add_library(adxl375 adxl375.c adxl375_regmap.h include/adxl375/adxl375.h)
target_include_directories(adxl375 PUBLIC include)
target_link_libraries(adxl375 regmap)