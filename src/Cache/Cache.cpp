#include "Cache/Cache.h"
#include "Logger/LoggerService.h"
#include <array>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

CacheSet::CacheSet()
{
    replacement.SetWays(CACHE_WAYS);
}

CacheSet::~CacheSet() = default;

CacheLine *CacheSet::Find(uint32_t tag)
{
    for (uint8_t wayIndex = 0; wayIndex < CACHE_WAYS; wayIndex++)
    {
        if (lines[wayIndex].valid && lines[wayIndex].tag == tag)
        {
            return &lines[wayIndex];
        }
    }

    return nullptr;
}

CacheLine *CacheSet::Replace(uint32_t tag, uint8_t *sourceData)
{
    uint8_t victimIndex = replacement.GetVictim();

    lines[victimIndex].tag = tag;
    lines[victimIndex].valid = true;

    std::memcpy(lines[victimIndex].data.data(), sourceData, CACHE_LINE_SIZE);

    return &lines[victimIndex];
}

void Cache::Initialize(MainMemory *mainMemoryPointer)
{
    mainMemory = mainMemoryPointer;
}

uint32_t Cache::Read(uint32_t address)
{
    AddressParts addressParts(address);

    CacheLine *line = sets[addressParts.setIndex].Find(addressParts.tag);

    if (line)
    {
        LoggerService::Log("Cache hit");

        return *reinterpret_cast<uint32_t *>(&line->data[addressParts.byteOffset]);
    }

    uint32_t lineStartAddress = address & ~(CACHE_LINE_SIZE - 1);

    std::array<uint8_t, CACHE_LINE_SIZE> buffer;

    mainMemory->Read(lineStartAddress, CACHE_LINE_SIZE, buffer.data());

    CacheLine *newLine = sets[addressParts.setIndex].Replace(addressParts.tag, buffer.data());

    LoggerService::Log("Cache miss");

    return *reinterpret_cast<uint32_t *>(&newLine->data[addressParts.byteOffset]);
}

void Cache::Write(uint32_t address, uint32_t data)
{
    AddressParts addressParts(address);

    CacheLine *line = sets[addressParts.setIndex].Find(addressParts.tag);

    if (line)
    {
        {
            std::ostringstream oss;
            oss << "Writing to cache (address: 0x" << std::hex << address << ")";
            LoggerService::Log(oss.str());
        }

        *reinterpret_cast<uint32_t *>(&line->data[addressParts.byteOffset]) = data;
    }

    {
        std::ostringstream oss;
        oss << "Writing to main memory (address: 0x" << std::hex << address << ")";
        LoggerService::Log(oss.str());
    }

    mainMemory->Write(address, sizeof(uint32_t), reinterpret_cast<uint8_t *>(&data));
}
