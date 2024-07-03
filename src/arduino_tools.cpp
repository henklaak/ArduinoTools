#include "arduino_locations.h"
#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QProcess>
#include <arduino_tools/arduino_tools.h>
#include <iostream>

#define ARDUINO_VID (9025)

Q_LOGGING_CATEGORY(arduinoTools, "arduino_tools.arduino_tools", QtInfoMsg);

/**************************************************************************************************/
QByteArray runCLI(QStringList args) {
  QProcess process;
  process.start(ARDUINO_CLI, args);
  if (!process.waitForStarted())
    throw std::runtime_error("Couldn't start arduino-cli");

  QByteArray data;

  while (process.waitForReadyRead())
    data.append(process.readAll());

  return data;
}

/**************************************************************************************************/
QMap<QString, QString> ArduinoTools::findArduinoDevices() {
  QMap<QString, QString> devices;

  QStringList args;
  args << "board"
       << "list"
       << "--json";

  auto data = runCLI(args);
  auto root_obj = QJsonDocument::fromJson(data).object();
  auto detected_ports_array = root_obj["detected_ports"].toArray();

  for (auto detected_port_value : detected_ports_array) {
    auto detected_port_obj = detected_port_value.toObject();
    auto port_obj = detected_port_obj["port"].toObject();

    auto device_name = port_obj["address"].toString();
    auto hardware_id = port_obj["hardware_id"].toString();

    devices[hardware_id] = device_name;
  }

  qCDebug(arduinoTools) << "devices: " << devices;
  return devices;
}

/**************************************************************************************************/
void ArduinoTools::diagnosticDump() {
  QString fqdn;
  {
    QStringList args;
    args << "board"
         << "list"
         << "--json";

    QByteArray data = runCLI(args);

    std::cout << ">>> arduino-cli board list --json" << std::endl;
    for (auto line : QString(data).split("\n")) {
      if (not line.isEmpty()) {
        std::cout << line.toStdString() << std::endl;
      }
    }
    std::cout << "<<<" << std::endl;

    auto root_obj = QJsonDocument::fromJson(data).object();
    auto detected_ports_array = root_obj["detected_ports"].toArray();

    for (auto detected_port_value : detected_ports_array) {
      auto detected_port_obj = detected_port_value.toObject();
      auto boards_array = detected_port_obj["matching_boards"].toArray();
      for (auto boards_value : boards_array) {
        auto boards_obj = boards_value.toObject();
        fqdn = boards_obj["fqbn"].toString();
      }
    }
  }
  {
    QStringList args;
    args << "board"
         << "details"
         << "-b" << fqdn << "--json";

    std::cout << ">>> arduino-cli board details -b " << fqdn.toStdString()
              << " --json" << std::endl;

    QByteArray data = runCLI(args);

    for (auto line : QString(data).split("\n")) {
      if (not line.isEmpty()) {
        std::cout << line.toStdString() << std::endl;
      }
    }
    std::cout << "<<<" << std::endl;
  }
}
