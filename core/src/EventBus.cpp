#include "EventBus.h"
#include <algorithm> // Библиотека для функции std::remove_if
// Изменил метод subscribe. Теперь он принимает не только слушателя, 
// но и тип события (строку), на который этот слушатель хочет подписаться.
void EventBus::subscribe(EventListener* listener, const std::string& eventType) {
    if (listener != nullptr) {
        // Я сохраняю в вектор новую структуру, которая содержит и указатель на слушателя, и его фильтр.
        listeners.push_back({listener, eventType});
    }
}

// Добавил реализацию отписки. 
// Использую идиому erase-remove: std::remove_if сдвигает ненужные элементы в конец, а erase их удаляет.
void EventBus::unsubscribe(EventListener* listener) {
    listeners.erase(
        std::remove_if(listeners.begin(), listeners.end(),
            [listener](const SubscriptionInfo& info) {
                return info.listener == listener;
            }),
        listeners.end()
    );
}

// Изменил метод publish. Теперь перед отправкой события я проверяю фильтр.
void EventBus::publish(const Event& event) {
    // Прохожусь по всем подписчикам
    for (const auto& sub : listeners) {
        // Проверяю: если eventType у подписчика пустой (значит, он подписан на всё) 
        // ИЛИ если eventType совпадает с типом текущего события — только тогда я вызываю onEvent.
        if (sub.eventType.empty() || sub.eventType == event.getType()) {
            sub.listener->onEvent(event);
        }
    }
}

void EventBus::clear() {
    listeners.clear();
}

size_t EventBus::getListenersCount() const {
    return listeners.size();
}