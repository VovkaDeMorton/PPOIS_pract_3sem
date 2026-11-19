#pragma once

#include <functional>
#include <string>
#include <unordered_map>

class ScenarioManager {
private:
    std::unordered_map<std::string, std::function<void()>> scenarios;
public:
    void registerScenario(const std::string& name, std::function<void()> action);
    bool activateScenario(const std::string& name);
};