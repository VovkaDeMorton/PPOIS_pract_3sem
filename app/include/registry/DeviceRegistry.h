#pragma once
#include <vector>
#include <memory>
#include <string>
#include "Device.h"

class DeviceRegistry {
private:
    // unique_ptr гарантирует, что при удалении реестра удалятся и все устройства
    std::vector<std::unique_ptr<Device>> devices;

public:
    // Добавляем устройство в реестр (передаем владение через move)
    void addDevice(std::unique_ptr<Device> device);
    
    // Получить устройство по имени
    Device* getDevice(const std::string& name);
    
    // Вывести статус всех устройств
    void printAllStatuses() const;
    
    // Получить список всех устройств (нужно для подписки на шину)
    const std::vector<std::unique_ptr<Device>>& getAllDevices() const { return devices; }
};