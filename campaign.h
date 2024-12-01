#ifndef CAMPAIGN_H_
#define CAMPAIGN_H_

#include <iostream>
#include <string>
#include <memory>
#include <map>
#include <vector>
#include <utility>

#include "hero.h"

using namespace std;

class Campaign {
 private:
  string name;

  /* Key values are the ids of the referenced objects */
  map<unsigned, weak_ptr<Hero>> heroes;

  unsigned min_level;  // Must be greater than 0.

 private:
  bool is_exist(shared_ptr<Hero> h) const;
  bool is_exist(unsigned) const;

 public:
  Campaign(string name, unsigned min_level);
  void add_hero(shared_ptr<Hero> h);
  void encounter_monster(unsigned id, Monster& m);
  unsigned remove_dead_and_expired();
  friend ostream& operator<<(ostream& o, const Campaign& p);
  shared_ptr<Hero> first_hero();
  pair<unsigned, unsigned> enter_dungeon(const vector<shared_ptr<Monster>>& v);
};

#endif /* CAMPAIGN_H_ */
