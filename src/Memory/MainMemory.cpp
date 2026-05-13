#include "Memory/MainMemory.h"
#include <array>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <memory>

MainMemory::MainMemory()
{
    memory = std::make_unique<std::array<uint8_t, MAIN_MEMORY_SIZE>>();
    memory->fill(0x00);
}

MainMemory::~MainMemory() = default;

void MainMemory::Read(uint32_t startAddress, uint32_t size, uint8_t *destination) const
{
    std::cout << "Reading from main memory (startAddress: 0x" << std::hex << startAddress << std::dec
              << ", size: " << size << ")\n";

    std::memcpy(destination, &memory.get()->at(startAddress), size);
}

void MainMemory::Write(uint32_t startAddress, uint32_t size, const uint8_t *source)
{
    std::cout << "Writing to main memory (startAddress: 0x" << std::hex << startAddress << std::dec
              << ", size: " << size << ")\n";

    std::memcpy(&memory.get()->at(startAddress), source, size);
}

void MainMemory::Print() const
{
    const uint32_t ROWS = 24;
    const uint32_t COLUMNS = 12;

    for (uint32_t rowIndex = 0; rowIndex < ROWS; rowIndex++)
    {
        for (uint32_t columnIndex = 0; columnIndex < COLUMNS; columnIndex++)
        {
            uint32_t index = rowIndex * COLUMNS + columnIndex;

            std::cout << "0x" << std::setw(2) << std::setfill('0') << std::hex
                      << static_cast<unsigned>(memory->at(index)) << std::dec << ' ';
        }

        std::cout << std::endl;
    }

    for (uint32_t i = 0; i < 80; i++)
    {
        std::cout << "-";
    }

    std::cout << std::endl;
}
