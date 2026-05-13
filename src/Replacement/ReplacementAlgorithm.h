#pragma once

#include <cstdint>

enum class ReplacementAlgorithmEnum
{
    RANDOM,
};

class ReplacementAlgorithm
{
public:
    void SetWays(uint8_t waysNumber);
    uint8_t GetWays() const;

    uint8_t GetVictim() const;

private:
    uint8_t ways = 0;
};
