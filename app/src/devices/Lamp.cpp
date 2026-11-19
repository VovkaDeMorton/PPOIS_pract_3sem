#include "Lamp.h"
#include <utility> // Добавлено для std::move

Lamp::Lamp(std::string name, EventBus& bus) :
    Device(std::move(name), bus), isOn(false) {}

void Lamp::turnOn() {
    if (!isOn) {
        isOn = true;
        eventBus.publish(Event("LampTurnedOn"));
    }
}

void Lamp::turnOff() {
    if (isOn) {
        isOn = false;
        eventBus.publish(Event("LampTurnedOff"));
    }
}

std::string Lamp::getStatus() const {
    return name + ": " + (isOn ? "ON" : "OFF");
}