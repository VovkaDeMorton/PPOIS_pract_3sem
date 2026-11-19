#pragma once

#include <string>
#include "DeviceRegistry.h"
#include "EventBus.h"

class ConfigParser {
public:
    // Читает строки формата: DEVICE Lamp "Kitchen Lamp"
    // или DEVICE Thermostat "Bedroom" 21
    static int loadDevicesFromFile(const std::string& filepath, DeviceRegistry& registry, EventBus& bus);
};