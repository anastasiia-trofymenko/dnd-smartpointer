#include <iostream>
#include <string>
#include <algorithm>
#include <stdexcept>

#include "campaign.h"

using namespace std;

Campaign::Campaign(string name, unsigned min_level)
    : name(name), min_level(min_level) {
  if (name.empty() || min_level <= 0)
    throw runtime_error("invalid input");
}

bool Campaign::is_exist(shared_ptr<Hero> h) const {
  auto it = find_if(heroes.begin(), heroes.end(), [&](const auto& pair) {
    return pair.second.lock() == h;
  });

  if (it == heroes.end())
    return false;

  return true;
}

bool Campaign::is_exist(unsigned id) const {
  auto it = heroes.find(id);
  return it != heroes.end();
}

/*
 * If h is already part of the campaign or the level of h is not at least
 * min_level, an exception of type runtime_error must be thrown.
 */
void Campaign::add_hero(shared_ptr<Hero> h) {
  if (is_exist(h) || h->get_level() < min_level)
    throw runtime_error("specified hero is already present or does not "
                        "meet the requirements");

  heroes[h->get_id()] = h;
}

/*
 * If a hero object with the id is present in the campaign, the hero object fights
 * against m. If the hero object wins, it rises a level (level_up)
 */
void Campaign::encounter_monster(unsigned id, Monster& m) {
  if (!is_exist(id))
    return;

  auto pHero = heroes[id].lock();
  if (pHero->fight(m))
    pHero->level_up();
}

/*
 * Removes all pointers from map for which the referenced object no longer
 * exists or current_hp of the referenced object is 0. The number of removed
 * pointers is returned
 */
unsigned Campaign::remove_dead_and_expired() {
  unsigned count{0};

  /* for (auto it = heroes.begin(); it != heroes.end();) {
    auto sp = it->second.lock();
    if (sp && !sp->is_dead()) {
      it++;
      continue;
    }

    heroes.erase(it);
    count++;
  } */

  /*
   * For some reason the above solution doesn't work, an exception occurs when
   * re-freeing memory [during heroes.erase(it)]. Thus, we use a workaround in which
   * we save all valid pointers in a temporary map, which we then replace the original
   * map with.
   */

  map<unsigned, weak_ptr<Hero>> temp;
  for (auto& it : heroes) {
    auto sp = it.second.lock();
    if (sp && !sp->is_dead())
      temp[it.first] = sp;
    else
      count++;
  }

  heroes = temp;
  return count;
}

/* Format: [name Campaign, Min_Level min_level, {heroes0, ..., heroesn}] */
ostream& operator<<(ostream& o, const Campaign& p) {
  o << "[" << p.name << " Campaign, Min_Level " << p.min_level << ", {";
  string sep;
  for (auto& pair : p.heroes) {
    auto sp = pair.second.lock();
    if (!sp)
      continue;

    o << sep << *sp;
    sep = ", ";
  }

  o << "}]";
  return o;
}

shared_ptr<Hero> Campaign::first_hero() {
  auto search = find_if(heroes.begin(), heroes.end(), [](auto& a) {
    auto sp = a.second.lock();
    if (!sp)
      return false;

    return !sp->is_dead();
  });

  if (search == heroes.end())
    return nullptr;

  return search->second.lock();
}

pair<unsigned, unsigned>
Campaign::enter_dungeon(const vector<shared_ptr<Monster>>& v) {
  unsigned wins{0};
  unsigned lost{0};
  shared_ptr<Hero> hero;

  for (auto& m : v) {
    hero = first_hero();

    if (!hero || !hero->fight(*m)) {
      lost++;
      continue;
    }

    wins++;
  }

  return make_pair(wins, lost);
}
