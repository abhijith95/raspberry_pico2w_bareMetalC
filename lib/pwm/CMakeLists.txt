add_library(PWM STATIC pwm_ctrl.c)
target_include_directories(PWM PUBLIC ${CMAKE_SOURCE_DIR}/include)
