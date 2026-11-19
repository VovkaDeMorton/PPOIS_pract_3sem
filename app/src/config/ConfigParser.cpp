#include "ConfigParser.h"
#include <fstream>
#include <memory>
#include <sstream>
#include "Lamp.h"
#include "DoorLock.h"
#include "MotionSensor.h"
#include "Thermostat.h"
#include "Alarm.h"

namespace {
    std::string parseName(std::istringstream& iss) {
        iss >> std::ws;
        if (iss.peek() == '"') {
            iss.get();
            std::string s;
            std::getline(iss, s, '"');
            return s;
        }
        std::string s;
        iss >> s;
        return s;
    }
} // namespace

int ConfigParser::loadDevicesFromFile(const std::string& filepath, DeviceRegistry& registry, EventBus& bus) {
    std::ifstream in(filepath);
    if (!in.is_open()) {
        return 0;
    }

    int count = 0;
    std::string line;
    while (std::getline(in, line)) {
        if (line.empty() || line[0] == '#') continue;
        std::istringstream iss(line);
        std::string tag, type;
        if (!(iss >> tag >> type) || tag != "DEVICE") continue;

        std::string name = parseName(iss);
        if (name.empty()) continue;

        if (type == "Lamp") {
            registry.addDevice(std::make_unique<Lamp>(name, bus));
            ++count;
        }
        else if (type == "DoorLock") {
            registry.addDevice(std::make_unique<DoorLock>(name, bus));
            ++count;
        }
        else if (type == "MotionSensor") {
            registry.addDevice(std::make_unique<MotionSensor>(name, bus));
            ++count;
        }
        else if (type == "Thermostat") {
            int temp = 22;
            std::string tempStr;
            if (iss >> tempStr) { // Если после имени есть хоть какой-то текст
                try {
                    temp = std::stoi(tempStr); // Пробуем перевести в число
                }
                catch (const std::exception&) {
                    // Если там буквы или слишком большое число — 
                    // stoi кинет исключение. Мы его ловим и оставляем temp = 22.
                }
            }
            registry.addDevice(std::make_unique<Thermostat>(name, bus, temp));
            ++count;
        }
        else if (type == "Alarm") {
            auto alarm = std::make_unique<Alarm>(name, bus);
            bus.subscribe(alarm.get(), "MotionDetected");
            registry.addDevice(std::move(alarm));
            ++count;
        }
    }
    return count;
}