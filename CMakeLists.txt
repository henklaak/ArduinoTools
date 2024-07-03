cmake_minimum_required(VERSION 3.27)

project(ArduinoTools
        VERSION 2024.07.03.0
        DESCRIPTION "ArduinoTools"
        LANGUAGES CXX)

find_package(Qt6 COMPONENTS Core REQUIRED)

set(CMAKE_CXX_STANDARD 23)
set(CXX_STANDARD_REQUIRED ON)

#
include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)
FetchContent_Declare(arduino_cli
    URL https://github.com/arduino/arduino-cli/releases/download/v1.0.2/arduino-cli_1.0.2_Linux_64bit.tar.gz
)
FetchContent_MakeAvailable(arduino_cli)

find_program(ARDUINO_CLI
    REQUIRED
    NO_CACHE
    NO_DEFAULT_PATH
    NAMES arduino-cli arduino-cli.exe
    PATHS ${arduino_cli_SOURCE_DIR})

message(${ARDUINO_CLI})

configure_file(src/arduino_locations.h.in ${CMAKE_CURRENT_LIST_DIR}/src/arduino_locations.h)
#

add_library(ArduinoTools SHARED)
target_sources(ArduinoTools
    PRIVATE
    src/arduino_tools.cpp
    src/arduino_locations.h
    include/arduino_tools/arduino_tools.h)
target_include_directories(ArduinoTools
  PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>)
target_link_libraries(ArduinoTools
  PRIVATE
  Qt6::Core)

#

find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(test_ArduinoTools)
target_sources(test_ArduinoTools
    PRIVATE
    src/arduino_tools.cpp
    src/arduino_locations.h
    include/arduino_tools/arduino_tools.h
    tst/test_arduino_tools.cpp)
target_include_directories(test_ArduinoTools
  PRIVATE
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>)

target_link_libraries(
  test_ArduinoTools
  GTest::gtest_main
  Qt6::Core
)

add_test(
    NAME test_ArduinoTools
    COMMAND test_ArduinoTools)
