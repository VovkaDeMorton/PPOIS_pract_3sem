#pragma once
#include "Device.h"

class Thermostat : public Device {
private:
    int currentTemp;

public:
    Thermostat(std::string name, EventBus& bus, int initialTemp = 22);
    
    void setTemperature(int temp);
    int getTemperature() const { return currentTemp; }
    std::string getType() const override { return "Thermostat"; }
    std::string getStatus() const override;
};