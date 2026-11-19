#include "Alarm.h"
#include <iostream>

Alarm::Alarm(std::string name, EventBus& bus) : Device(std::move(name), bus), isActive(false), isArmed(true) {}

void Alarm::arm() {
    if (!isArmed) {
        isArmed = true;
        eventBus.publish(Event("AlarmArmed"));
    }
}

void Alarm::disarm() {
    bool changed = isArmed || isActive;
    isArmed = false;
    isActive = false;
    if (changed) {
        eventBus.publish(Event("AlarmDisarmed"));
    }
}

void Alarm::reset() {
    if (isActive) {
        isActive = false;
        eventBus.publish(Event("AlarmReset"));
    }
}

void Alarm::trigger() {
    if (!isArmed) {
        return;
    }
    if (!isActive) {
        isActive = true;
        eventBus.publish(Event("AlarmTriggered"));
    }
}

void Alarm::onEvent(const Event& event) {
    // Если датчик движения зафиксировал движение, включаем тревогу
    if (event.getType() == "MotionDetected" && !isActive) {
        std::cout << "\n[Alarm] Motion detected! Triggering alarm!\n";
        trigger();
    }
}

std::string Alarm::getStatus() const {
    return name + ": " + (isActive ? "ACTIVE!" : "Standby");
}