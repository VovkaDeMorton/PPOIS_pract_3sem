#include <iostream>
#include "EventBus.h"

// Тестовый слушатель. Он наследуется от нашего интерфейса
class Logger : public EventListener {
public:
    // Ключевое слово override говорит компилятору
    // "Я переопределяю виртуальный метод из базового класса"
    // Это защищает от опечаток в названии метода.
    void onEvent(const Event& event) override {
        std::cout << "[Logger] Received event: " << event.getType() << "\n";
    }
};

int main() {
    std::cout << "Smart Home System - Starting...\n";
    
    // 1. Создаем шину и наш логгер
    EventBus bus;
    Logger logger;
    
    // 2. Подписываем логгер на шину
    bus.subscribe(&logger);
    
    // 3. Создаем событие и публикуем его в шину
    Event motionEvent("MotionDetected");
    bus.publish(motionEvent);

    return 0;
}