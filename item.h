#pragma once
#include "corestats.h"
#include "item_manager.h"
#include <string>
#include <typeinfo>

class ItemDelegate {
public:
    std::string Name;
    virtual const char* GetType() = 0;
protected:
    ItemDelegate(std::string name) : Name(name) {}
};

class Item {
public:
  
private:
  ItemDelegate *_data;
  Item(ItemDelegate* item) : _data(item){}
  friend class ItemManager;
};

class EquipmentDelegate : public ItemDelegate {
public:
  const std::uint32_t UniqueId;
  CoreStats Stats;
protected:
  EquipmentDelegate(std::string name, CoreStats cstats);
private:
};

enum class ARMORSLOT { HELMET, CHEST, LEGS, BOOTS, GLOVES, RING1, RING2, NECK, NUM_SLOTS };  // NUM SLOTS FOR MAKING ARRAYS OF ARMOR SLOTS
class Armor final : public EquipmentDelegate {
public:
  ARMORSLOT Slot;
private:
  Armor(std::string name, CoreStats cstats, ARMORSLOT slot) : EquipmentDelegate(name, cstats), Slot(slot) {}
  const char* GetType() override { return typeid(*this).name(); };
  Armor() = delete;
  Armor(const Armor&) = delete;
  Armor(const Armor&&) = delete;
  friend class ItemManager;
};

enum class WEAPONSLOT { MELEE, RANGED, NUM_SLOTS };
class Weapon final : public EquipmentDelegate {
public:
  WEAPONSLOT Slot;
  damagetype MinDamage;
  damagetype MaxDamage;
  bool is2H;
private:
  Weapon(std::string name, CoreStats cstats, WEAPONSLOT slot, damagetype min, damagetype max, bool twohanded = false)
    : EquipmentDelegate(name, cstats), Slot(slot), MinDamage(min), MaxDamage(max), is2H(twohanded) {
  }
  const char* GetType() override { return typeid(*this).name(); };
  Weapon() = delete;
  Weapon(const Weapon&) = delete;
  Weapon(const Weapon&&) = delete;
  friend class ItemManager;
};
