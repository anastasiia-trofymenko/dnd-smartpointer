#ifndef HERO_INFO_H_
#define HERO_INFO_H_

#include <iostream>

using namespace std;

enum class Hero_Class {
  BARBARIAN,
  BARD,
  CLERIC,
  DRUID,
  FIGHTER,
  MONK,
  PALADIN,
  RANGER,
  ROGUE,
  SORCERER,
  WARLOCK,
  WIZARD
};

enum class Hero_Species {
  DRAGONBORN,
  DWARF,
  ELF,
  GNOME,
  HALF_ELF,
  HALFLING,
  HALF_ORC,
  HUMAN,
  TIEFLING
};

ostream& operator<<(ostream& o, Hero_Class m);
ostream& operator<<(ostream& o, Hero_Species m);

#endif /* HERO_INFO_H_ */
