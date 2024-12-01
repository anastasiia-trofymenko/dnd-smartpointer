#ifndef MONSTER_H_
#define MONSTER_H_

#include <iostream>
#include <string>

using namespace std;

class Monster {
 private:
  string name;      // Must not be empty.
  unsigned health;  // Must not be 0.
  unsigned attack;  // Must not be 0.

 public:
  Monster(string name, unsigned health, unsigned attack);
  virtual ~Monster() {}  // Default Destructor.

  virtual unsigned calculate_damage(unsigned dmg) const = 0;
  virtual string additional_information() const = 0;

  string get_name() const {
    return name;
  }

  unsigned get_health() const {
    return health;
  }

  /*
   * Health is reduced by calculate_damage(dmg) ensuring it does not
   * fall below 0
   */
  void take_damage(unsigned dmg);

  /* Returns true if health is 0 */
  bool is_dead() const;

  unsigned get_attack() const {
    return attack;
  }

  /* Format: [name, health HP, attack ATKadditional_information()] */
  friend ostream& operator<<(ostream& o, const Monster& h);
};

class Elite_Monster : public Monster {
 private:
  unsigned defense;  // Must not be 0.

 public:
  Elite_Monster(string name, unsigned health, unsigned attack, unsigned defense)
      :
      Monster(name, health, attack),
      defense(defense) {
    if (defense == 0)
      throw runtime_error("invalid input");
  }

  /*
   * dmg is reduced by defense, not falling below 0. The calculated value should
   * be returned
   */
  unsigned calculate_damage(unsigned dmg) const {
    return dmg < defense ? 0 : dmg - defense;
  }

  /* Returns “, defense DEF” */
  string additional_information() const {
    return ", " + to_string(defense) + " DEF";
  }
};

class Standard_Monster : public Monster {
 public:
  Standard_Monster(string name, unsigned health, unsigned attack)
      : Monster(name, health, attack) {}

  /* Returns dmg */
  unsigned calculate_damage(unsigned dmg) const {
    return dmg;
  }

  /* Returns an empty string */
  string additional_information() const {
    return "";
  }
};

#endif /* MONSTER_H_ */
