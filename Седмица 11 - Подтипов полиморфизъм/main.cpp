#include <cstddef>
#include <iostream>
#include <cstring>
#include <string>
#include <variant>

class Character {
public:
  Character(const char* name, double damage, double hp)
    : name(new char[strlen(name) + 1]{}),
      damage(damage),
      hp(hp) {
    strcpy(this->name, name);
  }

  Character(const Character& other)
  : name(new char[strlen(other.name) + 1]{}),
    damage(other.damage),
    hp(other.hp) {
  strcpy(name, other.name);
  }

  ~Character() {
    delete [] name;
  }

  Character& operator=(const Character& other) {
    Character copy(other);
    swap(copy);

    return *this;
  }

  void print() const {
    std::cout << "Name: " << name << '\n'
              << "Type: " << type() << '\n'
              << "HP: " << hp << '\n'
              << "DMG: " << damage << '\n';
  }

  virtual void take_damage(double points) {
    hp = std::max(0.0, hp - points);
  }

  void deal_damage_to(Character& other) const {
    other.take_damage(get_attacking_damage());
  }

  virtual void heal(double points) {
    hp += points;
  }

  bool compare_name(const char* name) const {
    return strcmp(this->name, name) == 0;
  }

  bool is_alive() const {
    return hp > 0;
  }

  virtual Character* clone() const {
    return new Character(*this);
  }

private:
  char* name;
  double damage, hp;

  void swap(Character& other) {
    using std::swap;

    swap(name, other.name);
    swap(damage, other.damage);
    swap(hp, other.hp);
  }

protected:
  virtual const char* type() const {
    return "Ordinary Character";
  }

  virtual double get_attacking_damage() const {
    return damage;
  }
};

class Knight : public Character {
public:
  Knight(const char* name, double damage, double hp)
    : Character(name, damage, hp) {}

  void take_damage(double points) final {
    Character::take_damage(points * 0.75);
  }

  void heal(double points) final {
    Character::heal(points * 1.05);
  }

  virtual Character* clone() const {
    return new Knight(*this);
  }

private:
  const char* type() const final {
    return "Knight";
  }
};

class Archer : public Character {
public:
  Archer(const char* name, double damage, double hp)
    : Character(name, damage, hp) {}

  void take_damage(double points) final {
    Character::take_damage(points * 1.15);
  }

  virtual Character* clone() const {
    return new Archer(*this);
  }

private:
  const char* type() const final {
    return "Archer";
  }

  double get_attacking_damage() const final {
    return Character::get_attacking_damage() * 1.33;
  }
};

class Game {
public:
  Game() : characters(nullptr), size(0), capacity(0) {}
  Game(const Game& other) 
    : characters(new Character*[other.capacity]{}),
      size(other.size),
      capacity(other.capacity) {
    for (std::size_t i = 0; i < other.size; ++i) {
      characters[i] = other.characters[i]->clone();
    }
  }
  ~Game() {
    for (std::size_t i = 0; i < size; ++i) {
      delete characters[i];
    }
    delete [] characters;
  }
  Game& operator=(const Game& other) {
    Game copy(other);
    swap(copy);

    return *this;
  }

  void add(const Character& character) {
    if (size == capacity) {
      resize();
    }

    characters[size++] = character.clone();
  }

  void battle(const char* attacker, const char* target) {
    Character* attacking_character = find(attacker);
    
    if (!attacking_character) {
      std::cerr << "Missing character with name: " << attacker << '\n';
      return;
    }
    
    Character* target_character = find(target);
    if (!target_character) {
      std::cerr << "Missing character with name: " << target << '\n';
      return;
    }

    attacking_character->deal_damage_to(*target_character);

    if (!target_character->is_alive()) {
      remove(target);
      std::cout << "Character with name " << target << " has died\n";
    }
  }

  void heal(double amount) {
    for (std::size_t i = 0; i < size; ++i) {
      characters[i]->heal(amount);
    }
  }

  void print() const {
    for (std::size_t i = 0; i < size; ++i) {
      characters[i]->print();
      std::cout << '\n';
    }
  }

private:
  Character** characters;
  std::size_t size, capacity;

  void swap(Game& other) {
    using std::swap;

    swap(characters, other.characters);
    swap(size, other.size);
    swap(capacity, other.capacity);
  }

  void resize() {
    if (capacity == 0) {
      ++capacity;
    }

    Character** new_characters = new Character*[capacity *= 2]{};
    for (std::size_t i = 0; i < size; ++i) {
      new_characters[i] = characters[i];
    }

    delete [] characters;
    characters = new_characters;
  }

  Character* find(const char* name) const {
    for (std::size_t i = 0; i < size; ++i) {
      if (characters[i]->compare_name(name)) {
        return characters[i];
      }
    }

    return nullptr;
  }

  void remove(const char* name) {
    std::size_t index = 0;
    while (index < size && !characters[index]->compare_name(name)) {
      ++index;
    }

    delete characters[index];
    for (std::size_t i = index; i < size - 1; ++i) {
      std::swap(characters[i], characters[i + 1]);
    }

    --size;
  }
};

int main() {
  Character character("Pitar Pan", 10, 30);
  Knight knight("Arthur", 40, 100);
  Archer archer("Legolas", 50, 80);

  Game game;
  game.add(character);
  game.add(knight);
  game.add(archer);

  game.print();
  game.battle("Arthur", "Pitar Pan");
  game.print();
  game.battle("Legolas", "Arthur");
  game.print();
  game.add(character);
  game.print();

  return 0;
}