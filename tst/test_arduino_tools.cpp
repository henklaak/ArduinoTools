#include <arduino_tools/arduino_tools.h>
#include <gtest/gtest.h>

/**************************************************************************************************/
TEST(TestArduinoTools, All) {
  auto devices = ArduinoTools::findArduinoDevices();

  ASSERT_EQ(devices.size(), 1);
}

/**************************************************************************************************/
TEST(TestArduinoTools, diagnosticDump) { ArduinoTools::diagnosticDump(); }
