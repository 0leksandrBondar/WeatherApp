#include "weatherfetcher.h"

#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <stdexcept>

using json = nlohmann::json;

WeatherData WeatherFetcher::fetch()
{
    std::string raw = getResponse();
    auto j = json::parse(raw);

    WeatherData data;
    data.fetchedTime = std::chrono::system_clock::now();

    try
    {
        if (_city.empty())
        {
            data.city = j["nearest_area"][0]["areaName"][0]["value"];
        }
        else
        {
            data.city = _city;
        }

        data.temperatureC = j["current_condition"][0]["temp_C"];

        std::string desc = j["current_condition"][0]["weatherDesc"][0]["value"];
        data.description = desc;

        if (desc.find("rain") != std::string::npos)
        {
            data.icon = "☔";
        }
        else if (desc.find("cloud") != std::string::npos)
        {
            data.icon = "⛅";
        }
        else if (desc.find("sun") != std::string::npos || desc.find("clear") != std::string::npos)
        {
            data.icon = "☀";
        }
        else
        {
            data.icon = "🌈";
        }
    }
    catch (const std::exception& e)
    {
        throw std::runtime_error("Failed to parse JSON: " + std::string(e.what()));
    }

    return data;
}

std::string WeatherFetcher::buildUrl() const
{
    return "https://wttr.in/" + _city + "?format=j1";
}

std::string WeatherFetcher::getResponse()
{
    CURL* curl = curl_easy_init();
    std::string readBuffer;

    if (!curl)
    {
        throw std::runtime_error("Failed to initialize CURL");
    }

    std::string url = buildUrl();
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

    CURLcode res = curl_easy_perform(curl);
    long http_code = 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);

    curl_easy_cleanup(curl);

    if (res != CURLE_OK)
    {
        throw std::runtime_error("CURL error: " + std::string(curl_easy_strerror(res)));
    }

    if (http_code != 200)
    {
        std::string msg = "HTTP error code " + std::to_string(http_code);
        if (http_code == 400 || http_code == 404)
        {
            msg += " — likely incorrect city name or URL";
        }
        throw std::runtime_error(msg);
    }

    return readBuffer;
}
