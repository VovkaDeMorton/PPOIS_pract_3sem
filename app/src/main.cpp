#include <iostream>
#include "EventBus.h"
#include "RuleEngine.h"

// --- Тестовое условие: всегда истинно ---
class AlwaysTrue : public Condition {
public:
    bool isSatisfied(const Event& event) const override { return true; }
};

// --- Тестовое действие: просто печатает текст ---
class PrintAction : public Action {
private:
    std::string message;
public:
    PrintAction(std::string msg) : message(msg) {}
    void execute() override { std::cout << "[ACTION] " << message << "\n"; }
};

int main() {
    std::cout << "Smart Home System - Testing Rule Engine...\n";
    
    EventBus bus;
    RuleEngine engine(bus);

    // 1. Создаем правило: Если пришло "MotionDetected" -> Выполнить PrintAction
    auto condition = std::make_shared<AlwaysTrue>();
    auto action = std::make_shared<PrintAction>("Turning ON the light!");
    auto motionRule = std::make_shared<Rule>(condition, action, "MotionDetected");

    // 2. Добавляем правило в движок (он сам подпишет его на шину)
    engine.addRule(motionRule);

    std::cout << "\nTotal listeners on bus: " << bus.getListenersCount() << "\n";

    // 3. Публикуем событие движения. Должно сработать правило!
    std::cout << "\n--- Publishing MotionDetected ---\n";
    bus.publish(Event("MotionDetected"));

    // 4. Публикуем другое событие. Правило должно проигнорировать.
    std::cout << "\n--- Publishing TempChanged ---\n";
    bus.publish(Event("TempChanged"));

    // 5. Очищаем шину
    bus.clear();
    std::cout << "\nBus cleared. Listeners: " << bus.getListenersCount() << "\n";

    return 0;
}