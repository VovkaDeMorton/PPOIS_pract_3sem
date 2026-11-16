#pragma once
#include <iostream>

// Интерфейс для действий. Что-то делает (например, включает лампу).
class Action {
public:
    virtual ~Action() = default;
    virtual void execute() = 0;
};