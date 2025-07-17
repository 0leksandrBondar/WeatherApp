#include "controller.h"

#include <iostream>
#include <optional>

int main(int argc, char* argv[])
{
    std::optional<std::string> city;
    bool forceRefresh = false;

    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];

        if (arg == "--refresh")
        {
            forceRefresh = true;
        }
        else if (arg == "--help")
        {
            std::cout << "Usage: weather [city] [--refresh]\n"
                         "  city        - name of the city (optional)\n"
                         "  --refresh   - refresh weather from API, ignore cache\n"
                         "  --help      - show this help message\n";
            return 0;
        }
        else
        {
            city = arg;
        }
    }

    Controller ctrl;
    ctrl.run(city, forceRefresh);
    return 0;
}
