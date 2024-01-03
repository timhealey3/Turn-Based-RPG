#include "monster.h"
#include "random.h"

Monster::Monster(welltype hp, damagetype min, damagetype max) 
	: HP(hp, hp), MinDamage(min), MaxDamage(max)
{
}

const damagetype Monster::Attack() const noexcept
{
  // random number between minDmg and maxDmg
	return Random::NTK(MinDamage, MaxDamage);
}

const damagetype Monster::GetMinDamage() const noexcept
{
	return damagetype();
}

const damagetype Monster::GetMaxDamage() const noexcept
{
	return damagetype();
}
