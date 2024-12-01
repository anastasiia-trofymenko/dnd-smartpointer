#ifndef PLAYER_H_
#define PLAYER_H_

#include <iostream>
#include <string>
#include <memory>
#include <map>

#include "campaign.h"
#include "hero_info.h"

class Player {
 private:
  string first_name;  // Must not be empty
  string last_name;   // Must not be empty

  /* Key values are the ids of the referenced objects */
  map<unsigned, shared_ptr<Hero>> heroes;

  unique_ptr<Campaign> campaign;

 public:
  Player(string first_name, string last_name);
  unsigned create_hero(const string&, Hero_Class, Hero_Species, unsigned max_hp,
                       const map<string, unsigned>&);
  void create_campaign(string name, unsigned min_level, unsigned id);
  void join_friends_campaign(Player& pfriend, unsigned id);
  void transfer_campaign(Player& pfriend);
  void campaign_encounter_monster(unsigned id, Monster& m);
  unsigned remove_dead();
  ostream& print_campaign(ostream&) const;

  friend ostream& operator<<(ostream& o, const Player& p);
};

#endif /* PLAYER_H_ */
