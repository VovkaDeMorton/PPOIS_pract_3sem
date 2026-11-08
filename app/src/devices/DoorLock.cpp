#include "DoorLock.h"

DoorLock::DoorLock(std::string name, EventBus& bus) : Device(std::move(name), bus), isLocked(true) {}

void DoorLock::lock() {
    if (!isLocked) {
        isLocked = true;
        eventBus.publish(Event("DoorLocked"));
    }
}

void DoorLock::unlock() {
    if (isLocked) {
        isLocked = false;
        eventBus.publish(Event("DoorUnlocked"));
    }
}

std::string DoorLock::getStatus() const {
    return name + ": " + (isLocked ? "LOCKED" : "UNLOCKED");
}