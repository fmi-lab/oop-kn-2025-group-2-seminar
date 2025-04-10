#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include <cstddef>
#include <functional>
#include <ostream>

template <typename T> 
class LinkedList {
public:
  LinkedList() : first(nullptr), last(nullptr), size(0) {}
  LinkedList(const LinkedList<T> &other);
  LinkedList<T>& operator=(const LinkedList& other);
  ~LinkedList();

  void remove_first();
  void insert_last(const T& element);
  void reverse() noexcept;

  template <typename U>
  friend std::ostream& operator<<(std::ostream& os, const LinkedList<U>& list);

private:
  struct Node {
    Node(const T &data, Node *next = nullptr) : data(data), next(next) {}

    T data;
    Node *next;
  };

  Node *first, *last;
  std::size_t size;

  void swap(LinkedList<T>& other);
};

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T> &other)
    : size(other.size), first(nullptr), last(nullptr) {
  if (!other.first) {
    return;
  }

  last = first = new Node(other.first->data);
  Node *iter = other.first->next;

  while (iter) {
    last->next = new Node(iter->data);
    last = last->next;
    iter = iter->next;
  }
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList& other) {
  LinkedList<T> copy(other);
  swap(copy);

  return *this;
}

template <typename T>
LinkedList<T>::~LinkedList() {
  while (first) {
    remove_first();   
  }
}

template <typename T>
void LinkedList<T>::remove_first() {
  if (!first) {
    return;
  }

  if (first == last) {
    delete first;
    first = last = nullptr;
    --size;
    return;
  }

  Node* temp = first;
  first = first->next;
  delete temp;
  --size;
}

template <typename T>
void LinkedList<T>::swap(LinkedList<T>& other) {
  using std::swap;

  swap(first, other.first);
  swap(last, other.last);
  swap(size, other.size);
}

template <typename T>
void LinkedList<T>::insert_last(const T& element) {
  ++size;
  if (!first) {
    first = last = new Node(element);
    return;
  }

  last = last->next = new Node(element);
}

template <typename U>
std::ostream& operator<<(std::ostream& os, const LinkedList<U>& list) {
  typename LinkedList<U>::Node *iter = list.first;
  
  while (iter) {
    os << iter->data << ' ';
    iter = iter->next;
  }

  return os;
}

template <typename T>
void LinkedList<T>::reverse() noexcept {
  Node *prev = nullptr, *current = first, *next;
  last = first;

  while (current) {
    next = current->next;
    current->next = prev;
    prev = current;
    current = next;
  }

  first = prev;
}

#endif