#pragma once

#include <memory>
#include <string>
#include "Command.h"
#include "DeviceRegistry.h"

class CommandParser {
private:
    DeviceRegistry& registry;

public:
    explicit CommandParser(DeviceRegistry& reg);
    std::unique_ptr<Command> parse(const std::string& line);
};