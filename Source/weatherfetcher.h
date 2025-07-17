#pragma once

#include "weatherdata.h"

class WeatherFetcher
{
public:
    void setCity(const std::string& city = "") { _city = city; }

    WeatherData fetch();

private:
    std::string _city;

    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output)
    {
        output->append((char*)contents, size * nmemb);
        return size * nmemb;
    }

    std::string buildUrl() const;
    std::string getResponse();
};
