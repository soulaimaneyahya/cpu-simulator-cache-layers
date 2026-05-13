#pragma once

#include <array>
#include <cstdint>
#include <memory>

class MainMemory
{
public:
    static constexpr uint32_t MAIN_MEMORY_SIZE = 4 * 1024 * 1024;

    MainMemory();
    ~MainMemory();

    void Read(uint32_t startAddress, uint32_t size, uint8_t *destination) const;

    void Write(uint32_t startAddress, uint32_t size, const uint8_t *source);

    void Print() const;

private:
    std::unique_ptr<std::array<uint8_t, MAIN_MEMORY_SIZE>> memory;
};
