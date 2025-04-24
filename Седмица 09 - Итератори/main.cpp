#include <iostream>
#include "sorted.hpp"
#include "linked_list.hpp"

int main() {
  int def[] = {3, 5, 4, 5};
  Sorted<int> arr;
  arr.add(3).add(5).add(4).add(6);

  for (int x : arr) {
    std::cout << x << ' ';
  }
  std::cout << '\n';

  typename Sorted<int>::ReverseIterator begin = arr.rbegin();
  typename Sorted<int>::ReverseIterator end = arr.rend();

  for (; begin != end; ++begin) {
    int x = *begin;
    std::cout << x << ' ';
  }
  std::cout << '\n';

  LinkedList<int> list;
  list.insert_last(1);

  list.insert_after(10, list.begin());

  list.insert_last(2);
  list.insert_last(3);
  list.insert_last(4);

  typename LinkedList<int>::LinkedListIterator it = list.begin();
  ++it;

  list.insert_after(9, it);

  for (int x : list) {
    std::cout << x << ' ';
  }
  std::cout << '\n';

  return 0;
}