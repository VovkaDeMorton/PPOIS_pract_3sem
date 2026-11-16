#include "Rule.h"

Rule::Rule(std::shared_ptr<Condition> cond, std::shared_ptr<Action> act, const std::string& eventType)
    : condition(cond), action(act), targetEventType(eventType) {}

void Rule::onEvent(const Event& event) {
    // Если событие того типа, на который мы подписаны...
    if (event.getType() == targetEventType) {
        // ...и условие выполняется...
        if (condition && condition->isSatisfied(event)) {
            // ...то выполняем действие!
            if (action) action->execute();
        }
    }
}