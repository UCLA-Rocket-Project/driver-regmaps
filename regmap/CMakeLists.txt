add_library(regmap regmap.c include/regmap/bitmask.h include/regmap/byteorder.h include/regmap/driver_impl.h include/regmap/regmap.h)
target_include_directories(regmap PUBLIC include)