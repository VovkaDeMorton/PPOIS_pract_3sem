#pragma once
#include <vector>
#include "Event.h"
#include "EventListener.h"

// Сама шина событий. Она хранит список подписчиков и рассылает им события
class EventBus {
private:
    // Вектор указателей на слушателей. 
    // Мы храним именно указатели (*), чтобы шина не копировала объекты.
    std::vector<EventListener*> listeners;

public:
    // Метод для подписки на события
    void subscribe(EventListener* listener);
    
    // Метод для публикации (рассылки) события всем подписчикам
    void publish(const Event& event);
};