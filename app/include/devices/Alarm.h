#pragma once
#include "Device.h"
#include "EventListener.h"

// Множественное наследование: это и устройство, и слушатель событий
class Alarm : public Device, public EventListener {
private:
    bool isActive;
    bool isArmed;

public:
    Alarm(std::string name, EventBus& bus);
    
    void arm();
    void disarm();
    void reset();
    void trigger();
    // Переопределяем метод из EventListener
    void onEvent(const Event& event) override;
    std::string getStatus() const override;
    std::string getType() const override { return "Alarm"; }
};