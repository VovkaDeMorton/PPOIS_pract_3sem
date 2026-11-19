#pragma once
#include "Device.h"

class MotionSensor : public Device {
private:
    bool enabled;

public:
    MotionSensor(std::string name, EventBus& bus, bool startEnabled = true);
    
    void enable();
    void disable();
    bool isEnabled() const { return enabled; }

    void turnOn() override { enable(); }
    void turnOff() override { disable(); }

    // Метод, имитирующий обнаружение движения
    void detectMotion(); 
    std::string getStatus() const override;
    std::string getType() const override { return "MotionSensor"; }
};