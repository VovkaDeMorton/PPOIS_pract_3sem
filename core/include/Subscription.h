#pragma once
#include "EventBus.h"

// Это наша RAII-обертка. 
// Она хранит ссылку на шину и указатель на слушателя.
class Subscription {
private:
    EventBus& bus;
    EventListener* listener;

public:
    // При создании объекта мы запоминаем шину и слушателя, 
    // И СРАЗУ ЖЕ ПОДПИСЫВАЕМ его на события!
    Subscription(EventBus& b, EventListener* l) : bus(b), listener(l) {
        bus.subscribe(listener); // <--- ВОТ ЭТА СТРОЧКА БЫЛА ПРОПУЩЕНА
    }

    // При уничтожении объекта (когда он выходит из области видимости) 
    // автоматически вызывается деструктор, который отписывает слушателя.
    ~Subscription() {
        bus.unsubscribe(listener);
    }

    // Запрещаем копирование, чтобы случайно не отписать слушателя дважды
    Subscription(const Subscription&) = delete;
    Subscription& operator=(const Subscription&) = delete;
};