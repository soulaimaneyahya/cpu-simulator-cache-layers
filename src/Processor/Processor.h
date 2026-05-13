#pragma once

#include "Cache/Cache.h"
#include "Memory/MainMemory.h"
#include <cstdint>

class Processor
{
public:
    Processor();
    ~Processor();

    uint32_t Read(uint32_t address);

    void Write(uint32_t address, uint32_t data);

    void PrintMainMemory();

private:
    MainMemory mainMemory;
    Cache cache;
};
