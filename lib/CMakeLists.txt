add_subdirectory(gpio)
add_subdirectory(timer)
add_subdirectory(pwm)

add_library(LIB INTERFACE)
target_link_libraries(LIB INTERFACE GPIO TIMER PWM)
