#pragma once
#include "Device.h"

class DoorLock : public Device {
private:
    bool isLocked;

public:
    DoorLock(std::string name, EventBus& bus);
    
    void lock();
    void unlock();
    void turnOn() override { lock(); }
    void turnOff() override { unlock(); }
    std::string getType() const override { return "DoorLock"; }
    std::string getStatus() const override;
};