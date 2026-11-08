#pragma once
#include "Device.h"

class MotionSensor : public Device {
public:
    MotionSensor(std::string name, EventBus& bus);
    
    // Метод, имитирующий обнаружение движения
    void detectMotion(); 
    std::string getStatus() const override;
};