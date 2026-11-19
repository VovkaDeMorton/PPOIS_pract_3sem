#include "MotionSensor.h"

MotionSensor::MotionSensor(std::string name, EventBus& bus, bool startEnabled) :
    Device(std::move(name), bus), enabled(startEnabled) {}

void MotionSensor::enable() {
    if (!enabled) {
        enabled = true;
        eventBus.publish(Event("MotionSensorEnabled"));
    }
}

void MotionSensor::disable() {
    if (enabled) {
        enabled = false;
        eventBus.publish(Event("MotionSensorDisabled"));
    }
}

void MotionSensor::detectMotion() {
    if (!enabled) {
        return;
    }
    eventBus.publish(Event("MotionDetected"));
}

std::string MotionSensor::getStatus() const {
    return name + ": " + (enabled ? "Armed / Ready to detect" : "Disabled");
}