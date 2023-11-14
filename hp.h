#pragma once
#include <cstdint>

typedef std::uint16_t hptype;

class hp {
public:
    hptype getMaxHP()
    {
        return MaxHP;
    }
    hptype getCurrentHP()
    {
        return CurrentHP;
    }

    // return true if hp set succesfully
    bool setMaxHP(hptype new_max_hp)
    {
        if (new_max_hp < 1)
            return false;
        MaxHP = new_max_hp;
        if (CurrentHP > MaxHP)
            CurrentHP = MaxHP;
        return true;
    }

    void takeDamage(hptype damage)
    {
        if (damage > CurrentHP)
        {
            CurrentHP = 0;
            return;
        }
        CurrentHP -= damage;
    }

    void heal(hptype heal)
    {
        if (heal + CurrentHP > MaxHP)
        {
            CurrentHP = MaxHP;
            return;
        }
        CurrentHP += heal;
    }

    hp(){CurrentHP = 1; MaxHP = 1;}
    hp(hptype cHP, hptype mHP)
    {
        CurrentHP = cHP;
        MaxHP = mHP;
        if (CurrentHP > MaxHP)
            CurrentHP = MaxHP;
    }

private:
    hptype CurrentHP;
    hptype MaxHP;
};
