#pragma once
#include "Device.h"

class DoorLock : public Device {
private:
    bool isLocked;

public:
    DoorLock(std::string name, EventBus& bus);
    
    void lock();
    void unlock();
    std::string getStatus() const override;
};