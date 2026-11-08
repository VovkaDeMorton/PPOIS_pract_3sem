#pragma once
#include <vector>
#include <string>
#include "Event.h"
#include "EventListener.h"

// Добавил эту структуру, чтобы хранить не только самого слушателя, 
// но и то, на какое конкретно событие он подписан.
struct SubscriptionInfo {
    EventListener* listener;
    std::string eventType; // Если строка пустая — значит, слушатель хочет получать ВСЕ события
};

class EventBus {
private:
    // Раньше хранил просто указатели (std::vector<EventListener*>), 
    // но теперь мнужно хранить еще и фильтр, поэтому используем новую структуру.
    std::vector<SubscriptionInfo> listeners;

public:
    // Добавил второй параметр eventType. 
    // По умолчанию он равен пустой строке, чтобы старый код (без фильтра) продолжал работать.
    void subscribe(EventListener* listener, const std::string& eventType = "");

    // Добавил метод для отписки. Он нужен для умной обертки Subscription (RAII).
    void unsubscribe(EventListener* listener);
    
    void publish(const Event& event);
};