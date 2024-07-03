#ifndef ARDUINO_TOOLS_ARDUINO_TOOLS_H
#define ARDUINO_TOOLS_ARDUINO_TOOLS_H

#include <QLoggingCategory>
#include <QStringList>

namespace ArduinoTools {

[[nodiscard]] QMap<QString, QString> findArduinoDevices();

void diagnosticDump();

} // namespace ArduinoTools

Q_DECLARE_LOGGING_CATEGORY(arduinoTools)

#endif
