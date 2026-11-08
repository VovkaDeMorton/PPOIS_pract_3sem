#pragma once
#include "Device.h"
#include "EventListener.h"

// Множественное наследование: это и устройство, и слушатель событий
class Alarm : public Device, public EventListener {
private:
    bool isActive;

public:
    Alarm(std::string name, EventBus& bus);
    
    void trigger();
    // Переопределяем метод из EventListener
    void onEvent(const Event& event) override;
    std::string getStatus() const override;
};