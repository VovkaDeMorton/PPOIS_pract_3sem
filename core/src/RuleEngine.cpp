#include "RuleEngine.h"

RuleEngine::RuleEngine(EventBus& b) : bus(b) {}

void RuleEngine::addRule(std::shared_ptr<Rule> rule) {
    if (rule) {
        rules.push_back(rule);
        bus.subscribe(rule.get()); 
    }
}