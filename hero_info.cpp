#include"hero_info.h"

ostream& operator<<(ostream& o, Hero_Class m) {
  if (m == Hero_Class::BARBARIAN)
    o << "Barbarian";
  else if (m == Hero_Class::BARD)
    o << "Bard";
  else if (m == Hero_Class::CLERIC)
    o << "Cleric";
  else if (m == Hero_Class::DRUID)
    o << "Druid";
  else if (m == Hero_Class::FIGHTER)
    o << "Fighter";
  else if (m == Hero_Class::MONK)
    o << "Monk";
  else if (m == Hero_Class::PALADIN)
    o << "Paladin";
  else if (m == Hero_Class::RANGER)
    o << "Ranger";
  else if (m == Hero_Class::ROGUE)
    o << "Rogue";
  else if (m == Hero_Class::SORCERER)
    o << "Sorcerer";
  else if (m == Hero_Class::WARLOCK)
    o << "Warlock";
  else if (m == Hero_Class::WIZARD)
    o << "Wizard";
  else
    o << "undefined hero class [" << (int)m << "]";

  return o;
}

ostream& operator<<(ostream& o, Hero_Species m) {
  if (m == Hero_Species::DRAGONBORN)
    o << "Dragonborn";
  else if (m == Hero_Species::DWARF)
    o << "Dwarf";
  else if (m == Hero_Species::ELF)
    o << "Elf";
  else if (m == Hero_Species::GNOME)
    o << "Gnome";
  else if (m == Hero_Species::HALF_ELF)
    o << "Half-Elf";
  else if (m == Hero_Species::HALFLING)
    o << "Halfling";
  else if (m == Hero_Species::HALF_ORC)
    o << "Half-Orc";
  else if (m == Hero_Species::HUMAN)
    o << "Human";
  else if (m == Hero_Species::TIEFLING)
    o << "Tiefling";
  else
    o << "undefined hero class [" << (int)m << "]";

  return o;
}
