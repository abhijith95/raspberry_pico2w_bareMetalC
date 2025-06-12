add_library(APPL INTERFACE)
target_include_directories(APPL INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

message(STATUS "Found blinkled application")
add_subdirectory(blinkLed)
add_subdirectory(smoothLed)
target_link_libraries(APPL INTERFACE blinkLed smoothLed)
