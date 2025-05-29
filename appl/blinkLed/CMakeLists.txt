add_library(blinkLed STATIC blinkLed.c)
target_include_directories(blinkLed PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(blinkLed PRIVATE LIB)
target_compile_definitions(blinkLed PRIVATE "APPL_BLINKLED=1")
