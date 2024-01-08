#include "druid.h"
#include "pc_macros.h"

Druid::Druid() : PlayerCharacterDelegate() {
    MP = std::make_unique<PointWell>(BASEMP, BASEMP);  // be sure to init before PCCONSTRUCT MACRO
    PCCONSTRUCT;
    Abilities.emplace_back(new Ability("Heal", 2u, nullptr, 2u, 1u, ABILITYTARGET::ALLY, ABILITYSCALER::INT));
}

void Druid::level_up() noexcept {
    LEVELUP;
    if (GetLevel() == 2) {
        Abilities.emplace_back(new Ability("Smite", 2u, nullptr, 2u, 1u, ABILITYTARGET::ENEMY, ABILITYSCALER::INT));
    }
}