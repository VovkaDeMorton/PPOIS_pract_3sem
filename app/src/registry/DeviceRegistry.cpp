#include "DeviceRegistry.h"
#include <iostream>
#include <utility> // Добавлено для std::move

void DeviceRegistry::addDevice(std::unique_ptr<Device> device) {
    if (device) {
        devices.push_back(std::move(device));
    }
}

Device* DeviceRegistry::getDevice(const std::string& name) {
    for (const auto& dev : devices) {
        if (dev->getName() == name) {
            return dev.get();
        }
    }
    return nullptr;
}

void DeviceRegistry::printAllStatuses() const {
    std::cout << "--- Device Statuses ---\n";
    for (const auto& dev : devices) {
        std::cout << dev->getStatus() << "\n";
    }
    std::cout << "-----------------------\n";
}