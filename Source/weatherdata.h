#pragma once

#include <chrono>
#include <string>

struct WeatherData
{
    std::string city;
    std::string description;
    std::string icon;
    std::string temperatureC;
    std::chrono::system_clock::time_point fetchedTime;

    bool isExpired() const
    {
        using namespace std::chrono;
        return system_clock::now() - fetchedTime > minutes(10);
    }
};
