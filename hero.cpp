#include <iostream>
#include <string>
#include <algorithm>
#include <stdexcept>

#include "hero.h"
#include "monster.h"

/* The current_hp are initially equal to max_hp */
Hero::Hero(string name, Hero_Class hero_class, Hero_Species hero_species,
           unsigned max_hp, const map<string, unsigned>& abilities)
    :
    id(next_id),
    name(name),
    hero_class(hero_class),
    hero_species(hero_species),
    level(1),
    max_hp(max_hp),
    current_hp(max_hp),
    abilities(abilities) {
  if (name.empty())
    throw runtime_error("invalid input");

  if (level <= 0 || level >= 21)
    throw runtime_error("invalid input");

  if (max_hp <= 0)
    throw runtime_error("invalid input");

  /* current_hp Must be less than or equal to max_hp */
  if (current_hp > max_hp)
    throw runtime_error("invalid input");

  if (abilities.size() != 6)
    throw runtime_error("invalid input");

  for (const auto& [key, value] : abilities) {
    if (value <= 0 || value >= 21)
      throw runtime_error("invalid input");
  }

  /* Increment the ID only after successful validation */
  next_id++;
}

/*
 * If the level is less than 20, it is increased by 1. The new level is
 * returned
 */
unsigned Hero::level_up() {
  if (level < 20)
    level++;

  return level;
}

/*
 * If current_hp of the this object(hero) is greater than 0, damage is dealt to
 * m(the amount of damage is the product of the level of hero with the highest
 * value of its abilities. The exact effect of the damage is defined in the
 * monster classes in the methods take_damage). If m is not defeated, m attacks
 * hero and analogously reduces the current_hp of hero by the
 * amount defined in the monster object attack(the value of current_hp must not
 * fall below 0). The attacks are repeated alternately until either hero or m
 * has no more current_hp. If hero has won(i.e. current_hp greater than 0),true
 * is to be returned, other wise false.
 */
bool Hero::fight(Monster& m) {
  if (!current_hp)
    return false;

  /* Fight until either the hero or the monster dies */
  while (true) {
    auto it = max_element(abilities.begin(), abilities.end(),
        [](const auto& a, const auto& b) {
          return a.second < b.second;
        });

    auto max_ability = it->second;
    auto damage = level * max_ability;
    m.take_damage(damage);
    if (m.is_dead())
      return true;

    current_hp = current_hp < m.get_attack() ? 0 : current_hp - m.get_attack();
    if (!current_hp)
      return false;
  }
}

/*
 * Format:
 * [id, name, (hero_class, hero_species, level), {abilities.charisma,
 * abilities.constitution, abilities.dexterity, ...}, (current_hp/max_hp) HP]
 */
ostream& operator<<(ostream& o, const Hero& obj) {
  o << "[";
  o << obj.id << ", " << obj.name << ", (" << obj.hero_class << ", "
    << obj.hero_species << ", " << obj.level << "), {";

  string sep;
  for (const auto& [key, value] : obj.abilities) {
    o << sep << value;
    sep = ", ";
  }

  o << "}, (" << obj.current_hp << "/" << obj.max_hp << ") HP]";
  return o;
}

Task3::Task3(string name, Hero_Class hero_class, Hero_Species hero_species,
             unsigned max_hp, const map<string, unsigned>& abilities)
    :
    Hero(name, hero_class, hero_species, max_hp, abilities),
    fights{0} {
}

bool Task3::fight(Monster& m) {
  fights++;
  if (fights % 3)
    return false;

  return Hero::fight(m);
}
