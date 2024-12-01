#ifndef TASKS_H_
#define TASKS_H_

#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <numeric>
#include <cctype>
#include <utility>

#include "player.h"
#include "hero.h"
#include "hero_info.h"
#include "monster.h"

using namespace std;

static string modify_name(string name) {
  for (size_t ii{2}; ii < name.length(); ii += 3)
    name[ii] = toupper(name[ii]);

  return name;
}

vector<shared_ptr<Monster>> task1(const vector<shared_ptr<Monster>>& v) {
  vector<shared_ptr<Monster>> res;

  auto it1 = max_element(v.begin(), v.end(), [](const auto& a, const auto& b) {
    return a->get_health() < b->get_health();
  });

  auto it2 = min_element(v.begin(), v.end(), [](const auto& a, const auto& b) {
    return a->get_health() < b->get_health();
  });

  unsigned health;
  if (it1 != v.end() && it2 != v.end())
    health = (*it1)->get_health() * (*it2)->get_health();

  auto it3 = max_element(v.begin(), v.end(), [](const auto& a, const auto& b) {
    return a->get_attack() < b->get_attack();
  });

  unsigned attack;
  if (it3 != v.end())
    attack = (*it3)->get_attack();

  for (auto& m : v) {
    auto name = modify_name(m->get_name());
    res.push_back(make_shared<Standard_Monster>(name, health, attack));
  }

  return res;
}

/*
 * The task needs to be completed in tasks.h
 * Create the class SuperTask. This class has a private instance variable:
 *   vector<weak_ptr<Hero>> heroes;
 *
 * which is initialized in the constructor:
 *   SuperTask(const vector<shared_ptr<Hero>>& heroes);
 *
 * The SuperTask class includes a public method:
 *   vector<shared_ptr<Hero>>
 *   filtering(const vector<pair<char, HeroClass>>& cl) const;
 *
 * This method returns a list of pointers to the heroes referenced in the heroes
 * instance variable that, for a pair in cl, contain the corresponding character
 * in their name and belong to the associated class.
 * The relative order of pointers in the returned vector must match their order
 * in the heroes instance variable, and this, in turn, must match their order in
 * the heroes constructor parameter. Duplicate entries in the lists do not need
 * special handling
 */
class Super_Task {
 private:
  vector<weak_ptr<Hero>> heroes;

 public:
  explicit Super_Task(const vector<shared_ptr<Hero>>& list) {
    for (auto& h : list)
      heroes.push_back(h);
  }

  vector<shared_ptr<Hero>>
  filtering(const vector<pair<char, Hero_Class>>& cl) const {
    vector<shared_ptr<Hero>> res;
    for (auto& e : cl) {
      auto it = find_if(heroes.begin(), heroes.end(), [&](const auto& hero) {
        auto sp = hero.lock();

        /* Check object validity */
        if (!sp)
          return false;

        /* Check character in name */
        if (sp->get_name().find(e.first) == string::npos)
          return false;

        /* Check hero class */
        return sp->get_class() == e.second;
      });

      if (it != heroes.end())
        res.push_back((*it).lock());
    }

    return res;
  }
};

#endif /* TASKS_H_ */
