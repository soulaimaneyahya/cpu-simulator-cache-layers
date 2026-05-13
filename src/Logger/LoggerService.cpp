#include "Logger/LoggerService.h"
#include <iostream>

void LoggerService::Log(const std::string &message)
{
    std::cout << message << std::endl;
}
