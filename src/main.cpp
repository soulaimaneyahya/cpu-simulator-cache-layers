#include "Logger/LoggerService.h"
#include "Processor/Processor.h"
#include <iomanip>
#include <sstream>

int main()
{
    Processor cpu;

    cpu.PrintMainMemory();

    uint32_t data = cpu.Read(0x20);
    {
        std::ostringstream oss;
        oss << "CPU-Cache Value: 0x" << std::hex << data;
        LoggerService::Log(oss.str());
    }

    data = cpu.Read(0x20);
    {
        std::ostringstream oss;
        oss << "CPU-Cache Value: 0x" << std::hex << data;
        LoggerService::Log(oss.str());
    }

    return 0;
}
