#pragma once
#include "types.h"
#include "corestats.h"
#include "buff.h"
#include <vector>
typedef std::int16_t stattype;

class StatBlock { 
    CoreStats base;
    CoreStats statsFromBuffs;

public:
    explicit StatBlock(stattype s = 1, stattype i = 1, stattype a = 1, stattype arm = 0, stattype elres = 0) { 
        base.Strength = s;
        base.Intellect = i;
        base.Agility = a;
        base.Armor = arm;
        base.ElementRes = elres;
    }
    stattype getStrength() { return base.Strength; }
    stattype getIntellect() { return base.Intellect; }
    stattype getAgility() {return base.Agility;}
    stattype getArmor() {return base.Armor;}
    stattype getElementRes() {return base.ElementRes;}

    stattype getTotalStrength() { return base.Strength + statsFromBuffs.Strength; }
    stattype getTotalIntellect() { return base.Intellect + statsFromBuffs.Intellect; }
    stattype getTotalAgility() {return base.Agility  + statsFromBuffs.Intellect;}
    stattype getTotalArmor() {return base.Armor + statsFromBuffs.Armor;}
    stattype getTotalElementRes() {return base.ElementRes + statsFromBuffs.ElementRes;}

protected:
    void addNewBuff(Buff b) {
        for (auto& buff : Buffs) {
        if (b.Name == buff.Name) {
            buff.Duration = b.Duration;
            return;
        }
        }
        Buffs.push_back(b);
        recalculate_buffs();
    }
    
    std::vector<Buff> Buffs;
    void increaseStats(stattype s = 0, stattype i = 0, stattype a = 0, stattype arm = 0, stattype elres = 0){
        base.Strength += s;
        base.Intellect += i;
        base.Agility += a;
        base.Armor += arm;
        base.ElementRes += elres;
    }
    void increaseStats(CoreStats cs){
        base += cs;
    }
private:
    void recalculate_buffs(){

    CoreStats tmp_total;

    for (const auto& b : Buffs) {
      if (b.isDebuff) {
        tmp_total -= b.BuffedStats;
      }
      else {
        tmp_total += b.BuffedStats;
      }
    }

    statsFromBuffs = tmp_total;

    }
};
