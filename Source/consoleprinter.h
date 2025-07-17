#pragma once
#include "weatherdata.h"

class ConsolePrinter
{
public:
    void setCity(const std::string& city) { _city = city; }
    void setWeather(const WeatherData& data) { _data = data; }

    void print();

private:
    std::string _city;
    WeatherData _data;
};
