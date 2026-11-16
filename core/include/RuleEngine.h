#pragma once
#include <vector>
#include <memory>
#include "EventBus.h"
#include "Rule.h"

class RuleEngine {
private:
    EventBus& bus;
    std::vector<std::shared_ptr<Rule>> rules;

public:
    RuleEngine(EventBus& b);
    
    // Добавить новое правило в систему
    void addRule(std::shared_ptr<Rule> rule);
};