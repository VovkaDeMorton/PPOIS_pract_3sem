#pragma once
#include <string>
#include <utility> 
#include "EventBus.h"

// Абстрактный базовый класс для всех устройств
class Device {
protected:
    std::string name;
    // Ссылка на шину событий. Ссылка (&), а не указатель (*), 
    // так как устройство не может существовать без шины.
    EventBus& eventBus;

public:
    Device(std::string deviceName, EventBus& bus) 
        : name(std::move(deviceName)), eventBus(bus) {}
    
    virtual ~Device() = default;

    std::string getName() const { return name; }

    // Чисто виртуальный метод. У каждого устройства должен быть 
    // способ вывести свой статус в консоль или лог.
    virtual std::string getStatus() const = 0;
    virtual std::string getType() const = 0;

    virtual void turnOn() {}
    virtual void turnOff() {}
};