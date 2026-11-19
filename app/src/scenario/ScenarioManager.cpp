#include "ScenarioManager.h"
#include <iostream>

void ScenarioManager::registerScenario(const std::string& name, std::function<void()> action) {
    scenarios[name] = std::move(action);
}

bool ScenarioManager::activateScenario(const std::string& name) {
    auto it = scenarios.find(name);
    if (it == scenarios.end()) {
        std::cout << "Scenario not found: " << name << "\n";
        return false;
    }
    std::cout << "Activating scenario: " << name << "\n";
    it->second();
    return true;
}