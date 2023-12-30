#pragma once
#include "types.h"
#include "item.h"

class ItemManager {
public:
  static Item* CreateArmor(std::string name, CoreStats cstats, ARMORSLOT slot) {
    Item* temp_item = new Item(new Armor(name, cstats, slot));
    return temp_item;
  }

  static Item* CreateWeapon(std::string name, CoreStats cstats, WEAPONSLOT slot, damagetype min, damagetype max, bool twohanded = false) {
    Item* temp_item = new Item(new Weapon(name, cstats, slot, min, max, twohanded));
    return temp_item;
  }

  static Item* CreatePotion(std::string name, welltype heal = 1u, itemcount quant = 1u, Buff* buff = nullptr){
    Item* temp_item = new Item(new Potion(name, heal, (quant == 0) ? 1 : quant, buff));
    return temp_item;    
  }
  // Equip weapon or armor and return true. return false if failed
  // if item prev equipped in that slot, move to char backpack
  static bool equip(Item* item_to_equip, PlayerCharacter* p_char) {
    if (!p_char || !item_to_equip || !item_to_equip->GetData())
      return false;
    Armor* armor = dynamic_cast<Armor*>(item_to_equip->_data);
    if (armor) {
      // equip armor
      unsigned long long slot_num = (unsigned long long)armor->Slot;

      if (p_char->EquippedArmor[slot_num]) {
        // move old item to backpack
        MoveToBackpack(p_char->EquippedArmor[slot_num], p_char);
        EquippedArmor[slot_num] = armor;
      }
      else {
        p_char->EquippedArmor[slot_num] = item_to_equip;
      }
      return true;
    }

    Weapon* weapon = dynamic_cast<Weapon*>(item_to_equip->_data);
    if (weapon) {
      // equip weapon
      unsigned long long slot_num = (unsigned long long)weapon->Slot;

      if (p_char->EquippedWeapon[slot_num]) {
        // move old item to backpack
        MoveToBackpack(p_char->EquippedWeapon[slot_num], p_char);
        EquippedWeapon[slot_num] = armor;
      }
      else {
        p_char->EquippedWeapon[slot_num] = item_to_equip;
      }
      return true;
    }
    return false;

  }
  static bool Use(Item* item_to_use, PlayerCharacter* p_char){
    if (!item_to_use->GetData() || !item_to_use || !p_char)
      return false;
    Potion* potion = dynamic_cast<Potion*>(item_to_use->_data);
    if (potion) {
      if (potion->buff){
        applyBuff(*potion->buff);
      }
      // if max health and trying to heal, dont use
      if (pcclass->HP->isFull() && !potion->buff)
        return false; // dont use potion
      pcclass->HP->increaseCurrent(potion->HealAmount);
      potion->Quantity--;
      if (potion->Quantity == 0) {
        delete potion;
      }
      return true;
    }
    return false;
  }
  static bool MoveToBackpack(Item* item_to_move, PlayerCharacter* p_char){
    if (!p_char || !item_to_move || !item_to_move->GetData())
      return false;
    p_char->pcclass->Backpack.push_back(item_to_move);
    return true;
  }
};
