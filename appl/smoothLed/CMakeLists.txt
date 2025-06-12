add_library(smoothLed STATIC smoothLed.c)
target_include_directories(smoothLed PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(smoothLed PRIVATE LIB)
target_compile_definitions(smoothLed PRIVATE "APPL_SMOOTHLED=1")
