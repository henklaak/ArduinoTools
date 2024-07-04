find_program(ARDUINO_CLI
    REQUIRED
    NO_CACHE
    NO_DEFAULT_PATH
    NAMES arduino-cli arduino-cli.exe
    PATHS ${arduino_cli_SOURCE_DIR}
)

configure_file(
    arduino_locations.h.in
    arduino_locations.h
)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_library(ArduinoTools SHARED)

target_sources(ArduinoTools
    PRIVATE
    arduino_tools.cpp
    ${PROJECT_SOURCE_DIR}/include/arduino_tools/arduino_tools.h
    arduino_locations.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/arduino_locations.h
)

target_include_directories(ArduinoTools
    PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
)

target_link_libraries(ArduinoTools
    PRIVATE
    Qt6::Core
)
