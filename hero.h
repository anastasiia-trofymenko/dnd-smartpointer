#ifndef HERO_H_
#define HERO_H_

#include <iostream>
#include <map>
#include <string>

#include "hero_info.h"
#include "monster.h"

using namespace std;

class Hero {
 private:
  /*
   * Id which is automatically assigned consecutively for Hero objects.
   * The numbering starts with 0 and is incremented by one. The id should
   * only be incremented if no exception is thrown in the constructor
   */
  unsigned id;

  string name;
  Hero_Class hero_class;
  Hero_Species hero_species;
  unsigned level;   // Must be greater than 0 and less than 21. 1 by default.
  unsigned max_hp;  // Must be greater than 0.
  unsigned current_hp;  // Must be less than or equal to max_hp

  /*
   * A map with 6 values. The keys are Strength, Dexterity, Constitution,
   * Intelligence, Wisdom and Charisma. Less/more/other keys are not
   * allowed. The associated values must be greater than 0 and less than 21
   */
  map<string, unsigned> abilities;

  /* id counter. Required for consecutive numbering of id */
  inline static unsigned next_id;

 public:
  Hero(string name, Hero_Class hero_class, Hero_Species hero_species,
       unsigned max_hp, const map<string, unsigned>& abilities);
  virtual ~Hero() {}

  unsigned get_id() const {
    return id;
  }

  string get_name() const {
    return name;
  }

  Hero_Class get_class() const {
    return hero_class;
  }

  unsigned get_level() const {
    return level;
  }

  bool is_dead() const {
    return current_hp == 0;
  }

  unsigned level_up();
  virtual bool fight(Monster& m);

  friend ostream& operator<<(ostream& o, const Hero& obj);
};

/*
 * This task needs to be completed in the files hero.h and hero.cpp.
 * Create the class Task3, which should publicly inherit from Hero. The
 * constructor of the Task3 class requires the same parameters as the
 * constructor of the parent class, and the same conditions for the parameters
 * apply.
 *
 * The Task3 class overrides the method:
 *   bool fight(Monster& m);
 *
 * In the override, the parent class method should be called on every 3rd
 * invocation (the counting is done separately for each Hero object). In other
 * cases, no fight should occur, and the method should return false.
 *
 * Example:
 * h1 attacks m: nothing happens, returns false.
 * h1 attacks m: nothing happens, returns false.
 * h1 attacks m: the parent class method is called, and its result is returned.
 * h1 attacks m: nothing happens, returns false.
 * h1 attacks m: nothing happens, returns false.
 * h1 attacks m: the parent class method is called, and its result is returned.
 *
 * Hint:
 * You must extend the Hero class with a virtual destructor.
 * The method bool fight(Monster& m) should also be declared as virtual.
 */
class Task3 : public Hero {
 private:
  unsigned fights;

 public:
  Task3(string name, Hero_Class hero_class, Hero_Species hero_species,
        unsigned max_hp, const map<string, unsigned>& abilities);
  bool fight(Monster& m) override;
};

#endif /* HERO_H_ */
