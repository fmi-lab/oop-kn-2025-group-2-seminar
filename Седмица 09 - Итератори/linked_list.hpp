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

public:
  class LinkedListIterator {
  public:
    LinkedListIterator(Node* node) : node(node) {}

    LinkedListIterator& operator++() {
      return *this = LinkedListIterator(node->next);
    }

    bool operator!=(const LinkedListIterator& other) const {
      return node != other.node;
    }

    bool operator==(const LinkedListIterator& other) const {
      return !(*this != other);
    }

    operator Node*() {
      return node;
    }

    T& operator*() {
      return node->data;
    }

    const T& operator*() const {
      return node->data;
    }

  private:
    Node *node;
  };

  LinkedListIterator begin() const {
    return first;
  }

  LinkedListIterator end() const {
    return nullptr;
  }

  void insert_after(const T& element, const LinkedListIterator& position);
  void remove_at(const LinkedListIterator& position);

private:
  Node *first, *last;
  std::size_t size;

  void swap(LinkedList<T>& other);
  LinkedListIterator before(const LinkedListIterator& position) const;
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

template <typename T>
void LinkedList<T>::insert_after(
  const T& element, 
  const LinkedListIterator& position
) {
  if (position == LinkedListIterator(last)) {
    insert_last(element);
  } else {
    Node* current = static_cast<Node*>(position);
    Node* new_node = new Node(element, current->next);
    current->next = new_node;
  }
}

template <typename T>
typename LinkedList<T>::LinkedListIterator LinkedList<T>::before(
  const LinkedListIterator& position
) const {
  LinkedListIterator it = begin(), prev;
  while (it != position) {
    prev = it;
    ++it;
  }

  return prev;
}

template <typename T>
void LinkedList<T>::remove_at(const LinkedListIterator& position) {
  if (position == begin()) {
    remove_first();
  } else {
    LinkedListIterator prev = before(position);
    Node* current = static_cast<Node*>(position), *prev_node = static_cast<Node*>(prev);
    Node* next = current->next;

    if (LinkedListIterator(last) == position) {
      last = prev_node;
    }
    delete current;

    prev_node->next = next;
  }
}


#endif