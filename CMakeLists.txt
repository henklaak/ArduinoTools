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
if(LINUX)
    FetchContent_Declare(arduino_cli
        URL https://github.com/arduino/arduino-cli/releases/download/v1.0.2/arduino-cli_1.0.2_Linux_64bit.tar.gz)
endif()
if(WIN32)
    FetchContent_Declare(arduino_cli
        URL https://github.com/arduino/arduino-cli/releases/download/v1.0.2/arduino-cli_1.0.2_Windows_64bit.zip)
endif()
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.14.0)
FetchContent_MakeAvailable(arduino_cli googletest)


#

#
add_subdirectory(src)
add_subdirectory(tst)

