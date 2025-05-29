add_library(GPIO STATIC gpio_pins.c)
target_include_directories(GPIO PUBLIC ${CMAKE_SOURCE_DIR}/include)
