#include <iostream>
#include <fstream>
#include "linked_list.hpp"

int main() {
  LinkedList<int> list;
  list.insert_last(1);
  list.insert_last(2);
  list.insert_last(3);
  list.insert_last(4);

  LinkedList<int> copy(list);
  copy.reverse();
  std::cout << copy << '\n';
  copy.remove_first();

  std::cout << copy << '\n';
  std::ofstream file("list.txt");
  file << list << '\n';

  file.close();
  return 0;
}