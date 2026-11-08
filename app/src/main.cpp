#include <iostream>
#include "EventBus.h"
#include "Subscription.h"

// Наш тестовый слушатель. Добавил ему имя, чтобы в консоли было видно, 
// кто именно получает событие (ALL-LOGGER или MOTION-LOGGER).
class Logger : public EventListener {
private:
    std::string name;
public:
    Logger(std::string n) : name(n) {}
    
    void onEvent(const Event& event) override {
        std::cout << "[" << name << "] Received event: " << event.getType() << "\n";
    }
};

int main() {
    std::cout << "Smart Home System - Testing Event Filters & RAII...\n";
    
    EventBus bus;
    
    // ТЕСТ 1: Фильтрация событий
    Logger allLogger("ALL-LOGGER");
    Logger motionLogger("MOTION-LOGGER");
    
    bus.subscribe(&allLogger);                      // Слушает всё
    bus.subscribe(&motionLogger, "MotionDetected"); // Слушает только движение
    
    std::cout << "\n--- Test 1: Publishing MotionDetected ---\n";
    bus.publish(Event("MotionDetected"));

    std::cout << "\n--- Test 2: Publishing TempChanged ---\n";
    bus.publish(Event("TempChanged"));

    // ТЕСТ 2: RAII Автоотписка (новый шаг)
    std::cout << "\n--- Test 3: Testing RAII Subscription ---\n";
    {
        // Создаем временного логгера и умную обертку для него
        Logger tempLogger("TEMP-LOGGER");
        Subscription sub(bus, &tempLogger);
        
        std::cout << "Publishing while TEMP-LOGGER is alive:\n";
        bus.publish(Event("MotionDetected")); // Слышат все трое (allLogger, motionLogger, tempLogger)
    } // ВОТ ЗДЕСЬ срабатывает деструктор Subscription! tempLogger отписывается.

    std::cout << "\nPublishing after TEMP-LOGGER is destroyed:\n";
    bus.publish(Event("MotionDetected")); // Слышат только allLogger и motionLogger

    return 0;
}