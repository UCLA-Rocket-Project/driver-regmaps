add_library(ads1261_driver INTERFACE)

target_include_directories(ads1261_driver INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_sources(ads1261_driver INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/ads1261_regs.h)
