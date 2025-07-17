#include "controller.h"

#include "cache.h"
#include "consoleprinter.h"
#include "weatherfetcher.h"

#include <iostream>

void Controller::run(const std::optional<std::string>& cityArg, bool forceRefresh)
{
    ConsolePrinter printer;
    Cache cache;
    WeatherFetcher fetcher;
    WeatherData data;

    try
    {
        _city = cityArg.value_or("");
        fetcher.setCity(_city);

        bool cacheUsed = false;

        if (!forceRefresh)
        {
            try
            {
                data = cache.tryToGetCache(_city);
                cacheUsed = true;
            }
            catch (const std::exception& e)
            {
                std::cout << "(cache not used: " << e.what() << ")\n";
            }
        }

        if (!cacheUsed)
        {
            data = fetcher.fetch();
            cache.store(data);
        }

        printer.setCity(data.city);
        printer.setWeather(data);
        printer.print();
    }
    catch (const std::exception& ex)
    {
        std::cerr << "Error: " << ex.what() << std::endl;
    }
}
