#include <iostream>
#include "EventBus.h"
#include "DeviceRegistry.h"
#include "Lamp.h"
#include "Thermostat.h"
#include "MotionSensor.h"
#include "DoorLock.h"
#include "Alarm.h"

int main() {
    EventBus bus;
    
    // 1. Создаем реестр
    DeviceRegistry registry;

    // 2. Создаем устройства и добавляем их в реестр
    registry.addDevice(std::make_unique<Lamp>("Living Room Lamp", bus));
    registry.addDevice(std::make_unique<Thermostat>("Main Thermostat", bus));
    registry.addDevice(std::make_unique<MotionSensor>("Hall Sensor", bus));
    registry.addDevice(std::make_unique<DoorLock>("Front Door", bus));
    
    // Создаем сигнализацию отдельно, чтобы подписать её на события
    auto alarm = std::make_unique<Alarm>("Security Alarm", bus);
    bus.subscribe(alarm.get()); // Подписываем сигнализацию на шину
    registry.addDevice(std::move(alarm));

    // 3. Тестируем генерацию событий
    std::cout << "Turning on lamp...\n";
    dynamic_cast<Lamp*>(registry.getDevice("Living Room Lamp"))->turnOn();

    std::cout << "\nSimulating motion...\n";
    dynamic_cast<MotionSensor*>(registry.getDevice("Hall Sensor"))->detectMotion();

    std::cout << "\n";
    registry.printAllStatuses();

    return 0;
}