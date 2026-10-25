#pragma once
#include "Event.h"

// Абстрактный класс (интерфейс) для всех, кто хочет "слушать" события
class EventListener {
public:
    // Виртуальный деструктор для безопасного удаления наследников
    virtual ~EventListener() = default;
    
    // Чисто виртуальный метод (= 0)
    // Любой класс, который наследуется от EventListener, ОБЯЗАН реализовать этот метод.
    virtual void onEvent(const Event& event) = 0;
};