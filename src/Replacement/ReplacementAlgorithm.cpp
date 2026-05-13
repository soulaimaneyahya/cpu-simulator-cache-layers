#include "Replacement/ReplacementAlgorithm.h"
#include <cstdlib>

void ReplacementAlgorithm::SetWays(uint8_t waysNumber)
{
    ways = waysNumber;
}

uint8_t ReplacementAlgorithm::GetWays() const
{
    return ways;
}

uint8_t ReplacementAlgorithm::GetVictim() const
{
    return ways ? static_cast<uint8_t>(rand() % ways) : 0;
}
