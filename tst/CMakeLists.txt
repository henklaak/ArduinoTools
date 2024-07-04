include(GoogleTest)

add_executable(test_ArduinoTools)

target_sources(test_ArduinoTools
    PRIVATE
    test_arduino_tools.cpp
)

target_link_libraries(test_ArduinoTools
    PRIVATE
    ArduinoTools
    gtest_main
    Qt6::Core
)

add_test(
    NAME test_ArduinoTools
    COMMAND test_ArduinoTools
)
