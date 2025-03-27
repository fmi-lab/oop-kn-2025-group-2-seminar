#include <iostream>
#include "sorted.hpp"

int main() {
  int def[] = {3, 5, 4, 5};
  Sorted<int> arr;
  arr.add(3).add(5).add(4).add(6);

  std::cout << arr;

  Sorted<int> arr2(def, 4);
  std::cout << arr2;
  return 0;
}