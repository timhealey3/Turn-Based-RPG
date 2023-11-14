#pragma once
#include <cstdint>

typedef std::uint16_t stattype;

class StatBlock {    
    // 0xFF
    stattype Strength;
    stattype Intellect;
public:
    StatBlock() { Strength = (stattype)1u; Intellect = 1u; }
    explicit StatBlock(stattype s, stattype i) { 
        Strength = s;
        Intellect = i;
    }
    stattype getStrength() { return Strength; }
    stattype getIntellect() { return Intellect; }
};
