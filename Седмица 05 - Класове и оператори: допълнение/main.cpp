#include <cstddef>
#include <functional>
#include <iostream>
#include <cstring>
#include <ostream>
  
class String {
public:
  String(const char* str);
  String(const String& other);
  ~String();
  String& operator=(const String& other);

  bool operator==(const String& other) const noexcept;
private:
  char* str;
  std::size_t capacity;
};

template <typename T>
class DynArray {
public:
  explicit DynArray(std::size_t initial_capacity = 0);
  DynArray(const DynArray<T>& other);
  ~DynArray();
  DynArray<T>& operator=(const DynArray<T>& other);

  void push_back();
  T* find(std::function<bool(const T&)> predicate) const noexcept {
    for (std::size_t i = 0; i < size; ++i) {
      if (predicate(data[i])) {
        return &data[i];
      }
    }

    return nullptr;
  }
private:
  T* data;
  std::size_t size, capacity;
};

class Dish {
public:
  Dish(const String& name, double price, double calories, unsigned quantity);

  bool operator<(const Dish& other) const noexcept;
  friend std::ostream& operator<<(std::ostream& os, const Dish& dish);
  friend std::istream& operator>>(std::istream& is, Dish& dish);
private:
  String name;
  double price, calories;
  unsigned quantity;
};

class Menu {
public:
  Menu(const DynArray<Dish>& menu = DynArray<Dish>());

  void add_dish(const Dish& dish);
  Dish* find(double price) const noexcept;
private:
  DynArray<Dish> dishes;
};

class Cook {
public:
  // TODO:
  enum class Rank {
    KitchenPorter,
    JuniorChef,
    HeadChef
  };
private:
  String name;
  Rank rank;
  DynArray<Dish> dishes;
};

int main() {
  DynArray<Dish> d;
  DynArray<String> g(10);
  g.find([](const String& other){
    return other == "Gosho";
  });

  Menu menu(d);
  Menu menu1;

  Cook::Rank r = Cook::Rank::KitchenPorter;
  return 0;
}