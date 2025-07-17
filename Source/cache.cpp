#include "cache.h"

#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
namespace fs = std::filesystem;

static fs::path expandUserHome(const std::string& relative)
{
    const char* home = std::getenv("HOME");
    if (!home)
    {
        throw std::runtime_error("Failed to get $HOME environment variable");
    }
    return fs::path(home) / relative;
}

WeatherData Cache::tryToGetCache(const std::string& city)
{
    WeatherData data;

    fs::path cachePath = getCachePath();
    if (!fs::exists(cachePath))
    {
        throw std::runtime_error("Cache not found");
    }

    std::ifstream file(cachePath);
    json j;
    file >> j;

    data.city = j["city"];
    if (data.city != city && !city.empty())
    {
        throw std::runtime_error("City in cache does not match requested city");
    }

    data.description = j["description"];
    data.icon = j["icon"];
    data.temperatureC = j["temperatureC"];

    std::time_t ts = j["timestamp"];
    data.fetchedTime = std::chrono::system_clock::from_time_t(ts);

    if (data.isExpired())
    {
        throw std::runtime_error("Cache is expired");
    }

    return data;
}

void Cache::store(const WeatherData& data)
{
    json j;
    j["city"] = data.city;
    j["description"] = data.description;
    j["icon"] = data.icon;
    j["temperatureC"] = data.temperatureC;
    j["timestamp"] = std::chrono::system_clock::to_time_t(data.fetchedTime);

    fs::path path = getCachePath();
    std::ofstream out(path);
    out << j.dump(4);
}

std::filesystem::path Cache::getCachePath() const
{
    fs::path path = expandUserHome(".cache/weather_cli");
    fs::create_directories(path);
    return path / "lastWeather.json";
}
