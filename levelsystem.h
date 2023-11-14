#pragma once
#include <cstdint>
typedef std::uint64_t exptype;
typedef std::uint64_t leveltype;

class LevelSystem {
public:
    // level up needs more exp every level up
    static const exptype LEVEL2AT = 100u;

    LevelSystem() { 
        CurrentLevel = 1u; 
        CurrentEXP = 0u; 
        EXPToNextLevel = LEVEL2AT;
    }

    void gainEXP(exptype gained_exp){
        CurrentEXP += gained_exp;
        check_if_level();
    }

protected:
    leveltype CurrentLevel;
    exptype CurrentEXP;
    exptype EXPToNextLevel;

    void check_if_level() {

        if (CurrentEXP > EXPToNextLevel){
            CurrentLevel++;
        };

        static const leveltype LEVELSCALAR = 2u;

    }
};
