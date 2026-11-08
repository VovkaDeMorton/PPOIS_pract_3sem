#include "Alarm.h"
#include <iostream>

Alarm::Alarm(std::string name, EventBus& bus) : Device(std::move(name), bus), isActive(false) {}

void Alarm::onEvent(const Event& event) {
    // Если датчик движения зафиксировал движение, включаем тревогу
    if (event.getType() == "MotionDetected" && !isActive) {
        std::cout << "\n[Alarm] Motion detected! Triggering alarm!\n";
        trigger();
    }
}

void Alarm::trigger() {
    isActive = true;
    eventBus.publish(Event("AlarmTriggered"));
}

std::string Alarm::getStatus() const {
    return name + ": " + (isActive ? "ACTIVE!" : "Standby");
}