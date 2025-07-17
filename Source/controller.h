#pragma once

#include <optional>
#include <string>

class Controller
{
public:
    void run(const std::optional<std::string>& cityArg, bool forceRefresh = false);

private:
    std::string _city;
};
