#include "CommandParser.h"
#include <iostream>
#include <sstream>
#include "Lamp.h"
#include "DoorLock.h"
#include "MotionSensor.h"
#include "Thermostat.h"
#include "Alarm.h"

namespace {

    class StatusCommand : public Command {
    private:
        const DeviceRegistry& reg;
    public:
        explicit StatusCommand(const DeviceRegistry& r) : reg(r) {}
        void execute() override { reg.printAllStatuses(); }
    };

    class LampCommand : public Command {
    private:
        Lamp* lamp;
        bool turnOnFlag;
    public:
        LampCommand(Lamp* l, bool on) : lamp(l), turnOnFlag(on) {}
        void execute() override {
            if (!lamp) {
                std::cout << "Lamp not found\n";
                return;
            }
            if (turnOnFlag) lamp->turnOn();
            else lamp->turnOff();
            std::cout << lamp->getStatus() << "\n";
        }
    };

    class TempCommand : public Command {
    private:
        Thermostat* thermo;
        int temp;
    public:
        TempCommand(Thermostat* t, int val) : thermo(t), temp(val) {}
        void execute() override {
            if (!thermo) {
                std::cout << "Thermostat not found\n";
                return;
            }
            thermo->setTemperature(temp);
            std::cout << thermo->getStatus() << "\n";
        }
    };

    class MotionCommand : public Command {
    private:
        MotionSensor* sensor;
    public:
        explicit MotionCommand(MotionSensor* s) : sensor(s) {}
        void execute() override {
            if (!sensor) {
                std::cout << "MotionSensor not found\n";
                return;
            }
            sensor->detectMotion();
        }
    };

    std::string readName(std::istringstream& iss) {
        iss >> std::ws;
        if (iss.peek() == '"') {
            iss.get();
            std::string quoted;
            std::getline(iss, quoted, '"');
            return quoted;
        }
        std::string word;
        iss >> word;
        return word;
    }

} // namespace

CommandParser::CommandParser(DeviceRegistry& reg) : registry(reg) {}

std::unique_ptr<Command> CommandParser::parse(const std::string& line) {
    std::istringstream iss(line);
    std::string cmd;
    if (!(iss >> cmd)) {
        return nullptr;
    }

    if (cmd == "status") {
        return std::make_unique<StatusCommand>(registry);
    }
    if (cmd == "lamp_on" || cmd == "lamp_off") {
        std::string name = readName(iss);
        auto* lamp = dynamic_cast<Lamp*>(registry.getDevice(name));
        return std::make_unique<LampCommand>(lamp, cmd == "lamp_on");
    }
    if (cmd == "temp") {
        std::string name = readName(iss);
        int value = 0;
        if (iss >> value) {
            auto* thermo = dynamic_cast<Thermostat*>(registry.getDevice(name));
            return std::make_unique<TempCommand>(thermo, value);
        }
    }
    if (cmd == "motion") {
        std::string name = readName(iss);
        auto* sensor = dynamic_cast<MotionSensor*>(registry.getDevice(name));
        return std::make_unique<MotionCommand>(sensor);
    }
    return nullptr;
}