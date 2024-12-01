#include <string>
#include <iostream>
#include <stdexcept>

#include "hero.h"
#include "monster.h"

using namespace std;

Monster::Monster(string name, unsigned health, unsigned attack)
    : name(name), health(health), attack(attack) {
  if (name.empty())
    throw runtime_error("invalid input");

  if (health == 0 || attack == 0)
    throw runtime_error("invalid input");
}

/*
 * Health is reduced by calculate_damage(dmg), ensuring it does not fall
 * below 0
 */
void Monster::take_damage(unsigned dmg) {
  auto damage = calculate_damage(dmg);
  health = damage > health ? 0 : health - damage;
}

/* Returns true if health is 0 */
bool Monster::is_dead() const {
  return health == 0;
}

/* Format: [name, health HP, attack ATKadditional_information()] */
ostream& operator<<(ostream& o, const Monster& h) {
  o << "[" << h.name << ", " << h.health << " HP, " << h.attack << " ATK"
    << h.additional_information() << "]";

  return o;
}
