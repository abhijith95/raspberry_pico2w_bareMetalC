add_library(TIMER STATIC timer.c)
target_include_directories(TIMER PUBLIC ${CMAKE_SOURCE_DIR}/include)
