#pragma once
#include "Event.h"

// Интерфейс для условий. Проверяет, подходит ли событие под какое-то правило.
class Condition {
public:
    virtual ~Condition() = default;
    virtual bool isSatisfied(const Event& event) const = 0;
};