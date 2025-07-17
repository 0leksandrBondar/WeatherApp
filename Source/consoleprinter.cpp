#include "consoleprinter.h"

#include <iostream>

void ConsolePrinter::print()
{
    std::cout << "Weather for: " << _data.city << "\n";
    std::cout << "Temperature: " << _data.temperatureC << "°C\n";
    std::cout << "Condition: " << _data.description << " " << _data.icon << "\n";
}
