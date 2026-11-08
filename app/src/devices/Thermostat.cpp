#include "Thermostat.h"
#include <string>

Thermostat::Thermostat(std::string name, EventBus& bus, int initialTemp) 
    : Device(std::move(name), bus), currentTemp(initialTemp) {}

void Thermostat::setTemperature(int temp) {
    currentTemp = temp;
    // Публикуем событие с информацией об изменении
    eventBus.publish(Event("TemperatureChanged"));
}

std::string Thermostat::getStatus() const {
    return name + ": " + std::to_string(currentTemp) + "°C";
}