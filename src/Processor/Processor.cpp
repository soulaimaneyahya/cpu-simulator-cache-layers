#include "Processor/Processor.h"
#include <iostream>

Processor::Processor()
{
    cache.Initialize(&mainMemory);
}

Processor::~Processor() = default;

uint32_t Processor::Read(uint32_t address)
{
    return cache.Read(address);
}

void Processor::Write(uint32_t address, uint32_t data)
{
    cache.Write(address, data);
}

void Processor::PrintMainMemory()
{
    mainMemory.Print();
}
