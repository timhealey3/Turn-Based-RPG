#pragma once
#include "types.h"
#include "statblock.h"
#include "pointwell.h"
#include "ability.h"
#include "item.h"
#include <memory>
#include <string>
#include <vector>


class PlayerCharacterDelegate : public StatBlock {
public:
    static const exptype LEVEL2AT = 100u;

    PlayerCharacterDelegate() : StatBlock(0u, 0u){
        CurrentLevel = (leveltype)1u; 
        CurrentEXP = (exptype)0u; 
        EXPToNextLevel = LEVEL2AT;
        HP = std::make_unique<PointWell>(1u, 1u);
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

    void applyBuff(Buff b) {
        addNewBuff(b);
    }

    std::vector<Buff> getBuffList() {
        return Buffs;
    }
    virtual void LevelUp() = 0;
    virtual std::string getClassName() = 0;

    std::unique_ptr<PointWell> HP;
    std::unique_ptr<PointWell> MP;
    std::vector<Ability> Abilities;

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

#define PCCONSTRUCT \
HP->setMax(BASEHP);\
HP->increaseCurrent(BASEHP);\
if (MP) {\
MP->setMax(BASEMP);\
MP->increaseCurrent(BASEMP);\
}\
increaseStats(BASESTR, BASEINT, BASEAGI);

#define LEVELUP \
HP->setMax((wellType)((BASEHP/2.f) + HP->getMax()));\
HP->increaseCurrent((wellType)(BASEHP/2.f));\
if (MP) {\
MP->setMax((wellType)((BASEMP/2.f) + HP->getMax()));\
MP->increaseCurrent((wellType)(BASEMP/2.f));\
}\
increaseStats((stattype)((BASESTR+1u)/2.f), (stattype)((BASEINT+1u)/2.f), (stattype)((BASEAGI + 1u) / 2.f));

class Cleric : public PlayerCharacterDelegate {
public:
    static const wellType BASEHP = (wellType)14u;
    static const wellType BASEMP = (wellType)10u;
    static const stattype BASESTR = (stattype)3u;
    static const stattype BASEINT = (stattype)5u;
    static const stattype BASEAGI = (stattype)1u;
    std::string getClassName() override { return std::string("Cleric");}
    Cleric() : PlayerCharacterDelegate() {  // be sure to init before PCCONSTUCT MACRO
        MP = std::make_unique<PointWell>((wellType)BASEMP, (wellType)BASEMP);
        PCCONSTRUCT
        Abilities.emplace_back("Heal", 2u, 1u, ABILITYTARGET::ALLY, 2u, ABILITYSCALER::INT);
    }
private:
    void LevelUp() override{
        LEVELUP
        if (CurrentLevel == 2) {
            Abilities.emplace_back("Smite", 2u, 1u, ABILITYTARGET::ENEMY, 2u, ABILITYSCALER::INT);
        }
    }
};


class PlayerCharacter {
private:
    PlayerCharacterDelegate* pcclass;
    Item* EquippedArmor[(unsigned long long)ARMORSLOT::NUM_SLOTS];
    Item* EquippedWeapons[(unsigned long long)WEAPONSLOT::NUM_SLOTS];
    friend class ItemManager;
public:
  PlayerCharacter(PlayerCharacterDelegate* pc) : pcclass(pc) {
    auto i = 0;
    for (i = 0; i < (unsigned long long)ARMORSLOT::NUM_SLOTS; i++) {
      EquippedArmor[i] = nullptr;
    }
    for (i = 0; i < (unsigned long long)WEAPONSLOT::NUM_SLOTS; i++) {
      EquippedWeapons[i] = nullptr;
    }
  }
  ~PlayerCharacter() {
    delete pcclass;
    pcclass = nullptr;
    auto i = 0;
    for (i = 0; i < (unsigned long long)ARMORSLOT::NUM_SLOTS; i++) {
      if (EquippedArmor[i]) {
        delete EquippedArmor[i];
        EquippedArmor[i] = nullptr;
      }
    }
    for (i = 0; i < (unsigned long long)WEAPONSLOT::NUM_SLOTS; i++) {
      if (EquippedWeapons[i]) {
        delete EquippedWeapons[i];
        EquippedWeapons[i] = nullptr;
      }
    }
  }
  std::string getClassName() { return pcclass->getClassName(); }
  leveltype getLevel() { return pcclass->getLevel(); }
  exptype getCurrentEXP() { return pcclass->getCurrentEXP(); }
  exptype getEXPToNextLevel() { return pcclass->getEXPToNextLevel(); }
  wellType getCurrentHP() { return pcclass->HP->getCurrent(); }
  wellType getMaxHP() { return pcclass->HP->getMax(); }

  wellType getCurrentMP() { 
    if (pcclass->MP)
      return pcclass->MP->getCurrent();
    else
      return 0;
  }
  wellType getMaxMP() {
    if (pcclass->MP)
      return pcclass->MP->getMax();
    else
      return 0;
  }
  // get
  stattype getStrength() { return pcclass->getStrength(); }
  stattype getIntellect() { return pcclass->getIntellect(); }
  stattype getAgility() { return pcclass->getAgility(); }
  stattype getArmor() { return pcclass->getArmor(); }
  stattype getElementRes() { return pcclass->getElementRes(); }

  stattype getTotalStrength() {
    stattype str_from_armor = 0;
    for (auto i = 0; i < (unsigned long long)ARMORSLOT::NUM_SLOTS; i++) {
      if (EquippedArmor[i]) {
        str_from_armor += EquippedArmor[i]->Stats.Strength;
      }
    }
    stattype str_from_weapons = 0;
    for (auto i = 0; i < (unsigned long long)WEAPONSLOT::NUM_SLOTS; i++) {
      if (EquippedWeapons[i]) {
        str_from_weapons += EquippedWeapons[i]->Stats.Strength;
      }
    }
    return pcclass->getTotalStrength() + str_from_armor + str_from_weapons;
  }

  stattype getTotalIntellect() {
    stattype int_from_armor = 0;
    for (auto i = 0; i < (unsigned long long)ARMORSLOT::NUM_SLOTS; i++) {
      if (EquippedArmor[i]) {
        int_from_armor += EquippedArmor[i]->Stats.Intellect;
      }
    }
    stattype int_from_weapons = 0;
    for (auto i = 0; i < (unsigned long long)WEAPONSLOT::NUM_SLOTS; i++) {
      if (EquippedWeapons[i]) {
        int_from_weapons += EquippedWeapons[i]->Stats.Intellect;
      }
    }
    return pcclass->getTotalIntellect() + int_from_armor + int_from_weapons;
  }
  stattype getTotalAgility() {
    stattype agil_from_armor = 0;
    for (auto i = 0; i < (unsigned long long)ARMORSLOT::NUM_SLOTS; i++) {
      if (EquippedArmor[i]) {
        agil_from_armor += EquippedArmor[i]->Stats.Intellect;
      }
    }
    stattype agil_from_weapons = 0;
    for (auto i = 0; i < (unsigned long long)WEAPONSLOT::NUM_SLOTS; i++) {
      if (EquippedWeapons[i]) {
        agil_from_weapons += EquippedWeapons[i]->Stats.Agility;
      }
    }
    return pcclass->getTotalAgility() + agil_from_armor + agil_from_weapons;
  }
  stattype getTotalArmor() {
    // get all armor from equipped armor
    stattype armor_from_armor = 0;
    for (auto i = 0; i < (unsigned long long)ARMORSLOT::NUM_SLOTS; i++) {
      if (EquippedArmor[i]) {
        armor_from_armor += EquippedArmor[i]->Stats.Armor;
      }
    }
    stattype armor_from_weapons = 0;
    for (auto i = 0; i < (unsigned long long)WEAPONSLOT::NUM_SLOTS; i++) {
      if (EquippedWeapons[i]) {
        armor_from_weapons += EquippedWeapons[i]->Stats.Armor;
      }
    }
    return pcclass->getTotalArmor() + armor_from_armor + armor_from_weapons;
  }

  stattype getTotalElementRes() {
    stattype resist_from_armor = 0;
    for (auto i = 0; i < (unsigned long long)ARMORSLOT::NUM_SLOTS; i++) {
      if (EquippedArmor[i]) {
        resist_from_armor += EquippedArmor[i]->Stats.ElementRes;
      }
    }
    stattype elres_from_weapons = 0;
    for (auto i = 0; i < (unsigned long long)WEAPONSLOT::NUM_SLOTS; i++) {
      if (EquippedWeapons[i]) {
        elres_from_weapons += EquippedWeapons[i]->Stats.ElementRes;
      }
    }
    return pcclass->getTotalElementRes() + resist_from_armor + elres_from_weapons;
  }

  std::vector<Ability> getAbilityList() { return pcclass->Abilities; }
  std::vector<Buff> getBuffList() { return pcclass->getBuffList(); }
  std::vector<Item*> Backpack;
  EquipmentDelegate* getEquippedArmorAt(unsigned long long i) {
    return (dynamic_cast<Armor*>(EquippedArmor[i]));
  }

  EquipmentDelegate* getEquippedWeaponAt(unsigned long long i) {
    return (dynamic_cast<Weapon*>(EquippedWeapons[i]));
  }

  // Modifiers
  void gainEXP(exptype amt) { pcclass->gainEXP(amt); }
  void takeDamage(welltype amt) { pcclass->HP->reduceCurrent(amt); }
  void heal(welltype amt) { pcclass->HP->increaseCurrent(amt); }

  void applyBuff(Buff buff) {
    pcclass->applyBuff(buff);
  }
  // delete constructor
  PlayerCharacter() = delete;
  PlayerCharacter(const PlayerCharacter&) = delete;
  PlayerCharacter(const PlayerCharacter&&) = delete;
};
