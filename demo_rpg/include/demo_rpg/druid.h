#pragma once
#include "types.h"
#include "playercharacter.h"

class Druid : public PlayerCharacterDelegate {
public:
  static const welltype BASEHP = (welltype)14u;
  static const welltype BASEMP = (welltype)10u;
  static const stattype BASESTR = (stattype)3u;
  static const stattype BASEINT = (stattype)5u;
  static const stattype BASEAGI = (stattype)1u;
  Druid();
private:
  void level_up() noexcept override;
};
