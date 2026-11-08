#include "MotionSensor.h"

MotionSensor::MotionSensor(std::string name, EventBus& bus) : Device(std::move(name), bus) {}

void MotionSensor::detectMotion() {
    eventBus.publish(Event("MotionDetected"));
}

std::string MotionSensor::getStatus() const {
    return name + ": Ready to detect";
}