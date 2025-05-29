add_library(APPL INTERFACE)
target_include_directories(APPL INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

if (${APPL_TO_BUILD} MATCHES "blinkLed")
    message(STATUS "Found blinkled application")
    add_subdirectory(blinkLed)
    target_link_libraries(APPL INTERFACE blinkLed)
endif()
