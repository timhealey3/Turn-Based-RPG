#pragma once
#include <cstdint>

typedef std::uint16_t wellType;

class PointWell {
public:
    wellType getMax()
    {
        return Max;
    }
    wellType getCurrent()
    {
        return Current;
    }

    // return true if hp set succesfully
    bool setMax(wellType new_max)
    {
        if (new_max < 1)
            return false;
        Max = new_max;
        if (Current > Max)
            Current = Max;
        return true;
    }

    void reduceCurrent(wellType damage)
    {
        if (damage > Current)
        {
            Current = 0;
            return;
        }
        Current -= damage;
    }

    void increaseCurrent(wellType amount)
    {
        if (amount + Current > Max)
        {
            Current = Max;
            return;
        }
        Current += amount;
    }

    PointWell(){Current = 1; Max = 1;}
    PointWell(wellType cHP, wellType mHP)
    {
        Current = cHP;
        Max = mHP;
        if (Current > Max)
            Current = Max;
    }

private:
    wellType Current;
    wellType Max;
};
