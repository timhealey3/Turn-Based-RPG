#pragma once
#include "hp.h"
#include "statblock.h"

class Hobbit : public hp, public StatBlock
{
public:
    static const  hptype HPGROWTH = (hptype)13u;
    static const stattype BASESTR = (stattype)5u;
    static const stattype BASEINT = (stattype)2u;
    
    Hobbit() : hp(HPGROWTH, HPGROWTH), StatBlock(BASESTR, BASEINT){}

private:

};
