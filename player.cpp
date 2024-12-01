#include <iostream>
#include <string>
#include <stdexcept>
#include <utility>

#include "player.h"

using namespace std;

Player::Player(string first_name, string last_name)
    :
    first_name(first_name),
    last_name(last_name) {
  if (first_name.empty() || last_name.empty())
    throw runtime_error("invalid input");
}

/*
 * Creates a hero,adds the object to the heroes-map and returns the id of the
 * object
 */
unsigned Player::create_hero(const string& name, Hero_Class hero_class,
                             Hero_Species hero_species, unsigned max_hp,
                             const map<string, unsigned>& abilities) {
  auto h = make_shared<Hero>(name, hero_class, hero_species, max_hp, abilities);
  heroes[h->get_id()] = h;

  return h->get_id();
}

/*
 * Creates a campaign for the this object and the hero object of this with the
 * id is added to the campaign immediately, if possible. If there is no suitable
 * hero object or the addition fails,an exception of type runtime_error is
 * thrown. If there is already a campaign, the old campaign is deleted
 */
void Player::create_campaign(string name, unsigned min_level, unsigned id) {
  campaign = make_unique<Campaign>(name, min_level);  // campaign.reset(...)
  auto it = heroes.find(id);
  if (it == heroes.end())
    throw runtime_error("failed to create a campaign: undefined hero id");

  campaign->add_hero(it->second);
}

/*
 * If pfriend has a campaign, an attempt is made to add the hero object of
 * this with the ID id to the campaign of pfriend. If there is no campaign or
 * the desired hero object does not exist or the addition fails, an exception of
 * type runtime_error is thrown. A hero object can be represented in several
 * campaigns
 */
void Player::join_friends_campaign(Player& pfriend, unsigned id) {
  if (!pfriend.campaign)
    throw runtime_error("no campaingts");

  auto it = heroes.find(id);
  if (it == heroes.end())
    throw runtime_error("failed to join a campaign: undefined hero id");

  pfriend.campaign->add_hero(it->second);
}

/*
 * Transfers the campaign from this to pfriend. If the this object does not have
 * a campaign, an exception of the type runtime_error must be thrown. If pfriend
 * already has a campaign, the campaign of pfriend is deleted
 */
void Player::transfer_campaign(Player& pfriend) {
  if (!campaign)
    throw runtime_error("no campaingts");

  pfriend.campaign = std::move(campaign);
}

void Player::campaign_encounter_monster(unsigned id, Monster& m) {
  if (!campaign)
    throw runtime_error("no campaingts");

  campaign->encounter_monster(id, m);
}

/*
 * Removes all pointers from map if the current_hp of the referenced object is 0.
 * The number of removed pointers is returned
 */
unsigned Player::remove_dead() {
  unsigned count{0};
  map<unsigned, shared_ptr<Hero>> temp;
  for (auto& it : heroes) {
    auto &sp = it.second;
    if (sp && !sp->is_dead())
      temp[it.first] = sp;
    else
      count++;
  }

  heroes = temp;
  return count;
}

/* If a campaign exists, it should be output, otherwise[]should be output */
ostream& Player::print_campaign(ostream& o) const {
  if (campaign)
    o << *campaign;
  else
    o << "[]";

  return o;
}

/* Format: [first_name last_name, {heroes0, ..., heroesn}, print_campaign()] */
ostream& operator<<(ostream& o, const Player& p) {
  o << "[" << p.first_name << " " << p.last_name << ", {";
  string sep;
  for (auto& pair : p.heroes) {
    o << sep << *pair.second;
    sep = ", ";
  }

  o << "}, ";
  p.print_campaign(o);
  o << "]";

  return o;
}
