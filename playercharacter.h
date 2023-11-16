#pragma once
#include "statblock.h"
#include "pointwell.h"
#include <cstdint>
#include <string>
#include <memory>
typedef std::uint64_t exptype;
typedef std::uint64_t leveltype;


class PlayerCharacterDelegate : public StatBlock {
public:
    static const exptype LEVEL2AT = 100u;

    PlayerCharacterDelegate() { 
        CurrentLevel = 1u; 
        CurrentEXP = 0u; 
        EXPToNextLevel = LEVEL2AT;
        HP = std::make_unique<PointWell>();
    }

    void gainEXP(exptype gained_exp){
        CurrentEXP += gained_exp;
        while (check_if_level()) {}
    }

    leveltype getLevel() {
        return CurrentLevel;
    }

    exptype getCurrentEXP() {
        return CurrentEXP;
    }
    
    exptype getEXPToNextLevel(){
        return EXPToNextLevel;
    }

    virtual void LevelUp() = 0;
    virtual std::string getClassName() = 0;

    std::unique_ptr<PointWell> HP;

protected:
    leveltype CurrentLevel;
    exptype CurrentEXP;
    exptype EXPToNextLevel;

    bool check_if_level() {
        static const leveltype LEVELSCALAR = 2u;
        if (CurrentEXP >= EXPToNextLevel){
            CurrentLevel++;
            LevelUp();
            EXPToNextLevel *= LEVELSCALAR;
            return true;
        }
        return false;
    }
};

class Cleric : public PlayerCharacterDelegate
{
public:
    static const wellType BASEHP = (wellType)14u;
    static const stattype BASESTR = (stattype)2u;
    static const stattype BASEINT = (stattype)3u;
    
    Cleric() : PlayerCharacterDelegate(){
        HP->setMax(BASEHP);
        HP->increaseCurrent(BASEHP);
        increaseStats(BASESTR, BASEINT);
    }
    std::string getClassName() override {return std::string("cleric");}
private:
    void LevelUp() override{
        HP->setMax((wellType)((BASEHP/2.f) + HP->getMax()));
        increaseStats((stattype)((BASESTR+1u)/2.f), (stattype)((BASEINT+1u)/2.f));
    }
};


class PlayerCharacter {
private:
    PlayerCharacterDelegate* pcclass;
public:
    PlayerCharacter() = delete;
    PlayerCharacter(PlayerCharacterDelegate* pc) : pcclass(pc){}
    std::string getClassName(){pcclass->getClassName();}
};
