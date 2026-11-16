#pragma once
#include <memory>
#include <string>
#include "EventListener.h"
#include "Condition.h"
#include "Action.h"

class Rule : public EventListener {
private:
    std::shared_ptr<Condition> condition;
    std::shared_ptr<Action> action;
    std::string targetEventType; // На какое событие реагирует правило

public:
    Rule(std::shared_ptr<Condition> cond, std::shared_ptr<Action> act, const std::string& eventType);
    
    // Переопределяем метод из EventListener
    void onEvent(const Event& event) override;
};