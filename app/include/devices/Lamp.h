#pragma once
#include "Device.h"

class Lamp : public Device {
private:
    bool isOn;

public:
    Lamp(std::string name, EventBus& bus);
    
    void turnOn();
    void turnOff();
    std::string getStatus() const override;
};