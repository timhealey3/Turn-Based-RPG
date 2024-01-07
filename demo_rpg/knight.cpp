#include "knight.h"
#include "pc_macros.h"

Knight::Knight() : PlayerCharacterDelegate() {
    //MP = std::make_unique<PointWell>(BASEMP, BASEMP);  // be sure to init before PCCONSTRUCT MACRO
    PCCONSTRUCT;

}
void Knight::level_up() noexcept {
    LEVELUP;
    if (GetLevel() == 2) {
        Abilities.emplace_back(new Ability("Power Attack", 4u, nullptr, 0u, 3u, ABILITYTARGET::ENEMY, ABILITYSCALER::STR));
    }
    else if (GetLevel() == 3) {
        Abilities.emplace_back(new Ability("Healing Surge", 4u, nullptr, 0u, 4u, ABILITYTARGET::SELF, ABILITYSCALER::NONE));
    }
}