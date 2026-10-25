#include "EventBus.h"

void EventBus::subscribe(EventListener* listener) {
    // Проверка на дурака: не добавляем пустой указатель (nullptr)
    if (listener != nullptr) {
        listeners.push_back(listener);
    }
}

void EventBus::publish(const Event& event) {
    // Проходимся по всему списку подписчиков (range-based for)
    for (EventListener* listener : listeners) {
        // Полиморфизм в действии: вызываем onEvent у каждого объекта
        // Каждый объект (логгер, лампа) выполнит СВОЮ версию этого метода
        listener->onEvent(event);
    }
}