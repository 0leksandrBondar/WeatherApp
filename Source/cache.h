#pragma once

#include "weatherdata.h"

#include <filesystem>

class Cache
{
public:
    WeatherData tryToGetCache(const std::string& city);
    void store(const WeatherData& data);

private:
    std::filesystem::path getCachePath() const;
};
